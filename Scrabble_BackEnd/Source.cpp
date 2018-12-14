#include"Client.h"
#include"functions2.h"
#include"communication_server.hpp"
#include "GameManager.h"
#include "Logger.h"
static WebSocket::pointer ws = NULL;

std::vector<uint8_t> playerName;

int main()
{
	Client c1;
	playMove move;
	//ask TA when if there is letter mid board
	communication::server soc(2019);
	soc.start(); //blocking till GUI connects 

#ifdef _WIN32
	INT rc;
	WSADATA wsaData;

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc) {
		printf("WSAStartup Failed.\n");
		return 1;
	}
#endif

	std::string read = soc.receive();
	playerStart player = parseStart(read);

	Player * agent = new Player(player.PlayerName);
	
	std::string playerNameString = agent->playerName;
	
	if (player.mode == "0")
	{
		std::unique_ptr<WebSocket> ws(WebSocket::from_url(player.connection));
		assert(ws);
		
		int count;
		int bagCount = 100;
		int selectedMoveIndex;
		Move* selectedMove = NULL;
		uTime time;
		fromatedTime Stime;
		std::vector<uint8_t> message;
		vector<char> exchangedTiles;
		TileLookUp * TL = new TileLookUp();

		Gaddag *g = new Gaddag("../Text/SOWPODS.txt");

		cout << "Initialising Board..." << endl;
		Board * b = NULL;
		b->computeCrossSets(g->root);

		MidGameManager * midMan = new MidGameManager(TL, g);
		PreEndGameManager * preEndMan = new PreEndGameManager(TL, g);
		ProbabilityManager * PM = new ProbabilityManager();
		Logger logger;

		

		while (ws->getReadyState() != WebSocket::CLOSED) {
			bool gotMessage = false;
			ws->poll();
			ws->dispatchBinary([gotMessageOut = &gotMessage, messageOut = &message, ws = ws.get()](const std::vector<uint8_t>& message) {
				*gotMessageOut = true;
				*messageOut = message;

			});
			if (gotMessage)
			{
				cout << int(message[0]) << endl;
				if (message[0] == MessageTypes::NAME && c1.getState() == States::INIT)
				{
					c1.sendInitState(ws, playerNameString);
					c1.setState(States::READY);
				}
				else if (message[0] == MessageTypes::START && c1.getState() == States::READY)
				{
					readyStruct_formated info;
					info = c1.decodeReadyState(message);
					soc.send_message("1," + string(info.tiles.begin(), info.tiles.end()) + "," + to_string(info.score) + "," + to_string(info.opponentScore) + "," + to_string(info.playerTime) + "," + to_string(info.totalTime));
					
					// Initialising board
					if (b) delete b;
					b = new Board(info.board);
					
					// Initialising Rack
					if (agent->rack) delete agent->rack;
					agent->rack = new Rack();
					for (int i = 0, ilen = info.tiles.size(); i < ilen; i++) {
						agent->rack->addTile(info.tiles[i]);
					}

					int tilesLeft = 100 - (agent->rack->list.size() + b->getBoardLetters().length());
					if (tilesLeft <= 7) {
						bagCount = 0;
					}
					else {
						bagCount = tilesLeft - 7;
					}
					// Initialising Score
					agent->playerScore = info.score;


					if (info.order == 1)
					{
						cout << "It is your turn now" << endl;
						c1.setState(States::THINKING);
					}
					else c1.setState(States::IDLE);
				}
				else if (c1.getState() == States::AWAIT_EXCHANGE_RESPONSE)
				{
					if (message[0] == MessageTypes::INVALID)
					{
						Stime = c1.decodeTime(message);
						for (int i = 0, ilen = exchangedTiles.size(); i < ilen; i++) {
							agent->rack->addTile(exchangedTiles[i]);
						}
						c1.setState(States::THINKING);
					}
					if (message[0] == MessageTypes::EXCHANGE)
					{
						vector<char> tiles(7);
						tiles = c1.decodeTiles(message);
						for (int i = 0, ilen = tiles.size(); i < ilen; i++) {
							agent->rack->addTile(tiles[i]);
						}
						soc.send_message("3," + string(exchangedTiles.begin(), exchangedTiles.end()) + "," + string(tiles.begin(), tiles.end()));
						c1.setState(States::IDLE);
					}
				}
				else if (c1.getState() == States::AWAIT_PLAY_RESPONSE)
				{
					if (message[0] == MessageTypes::INVALID)
					{
						Stime = c1.decodeTime(message);
						c1.sendPass(ws);
						c1.setState(States::IDLE);
						//c1.setState(States::THINKING);
					}
					else if (message[0] == MessageTypes::CHALLENGE_REJECTED)
					{
						vector<char> tiles(7);
						// TODO: Add score of the move
						agent->rack->commitMove(selectedMove);
						b->commitMove(*selectedMove);
						// FIXME: Modify sth with time
						c1.decodeChallengeRejected(message, tiles, time);
						soc.send_message("6," + string(tiles.begin(),tiles.end()));
						c1.setState(States::THINKING);
					}
					else if (message[0] == MessageTypes::NO_CHALLENGE)
					{
						vector<char>new_tiles = c1.decodeTiles(message);//gets tiles
						soc.send_message("5," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score) + "," + string(new_tiles.begin(), new_tiles.end()));
						//cout << "5," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score) + "," + string(new_tiles.begin(), new_tiles.end()) << endl;
						agent->rack->commitMove(selectedMove);
						b->commitMove(*selectedMove);
						for (int i = 0, ilen = new_tiles.size(); i < ilen; i++) {
							agent->rack->addTile(new_tiles[i]);
						}
					}
					else if (message[0] == MessageTypes::CHALLENGE_ACCEPTED)
					{
						soc.send_message("7," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score));
						cout << "7," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score) << endl;
						c1.setState(States::IDLE);
					}
				}
				else if (c1.getState() == States::IDLE)
				{
					if (message[0] == MessageTypes::PASS)
					{
						Stime = c1.decodeTime(message);
						c1.setState(States::THINKING);
					}
					else if (message[0] == MessageTypes::EXCHANGE)
					{
						c1.decodeIdleExchange(message, count, time); //get time and count.
						c1.setState(States::THINKING);
					}
					else if (message[0] == MessageTypes::PLAY)
					{
						player2Move_formated play2move;
						play2move = c1.decodePlay(message);
						soc.send_message("4," + to_string(play2move.Scolumn) + "," + to_string(play2move.Srow) + "," + to_string(play2move.direction) + "," + string(play2move.tiles.begin(), play2move.tiles.end()) + "," + to_string(play2move.score));
						play2move.tiles = remove_char(play2move.tiles, '.');
						// TODO: Finish this function call
						//b->formatOponentMove(play2move, )
						c1.setState(States::AWAIT_AGENT_CHALLENGE);

					}
				}
				else if (c1.getState() == States::AWAIT_AGENT_CHALLENGE)
				{
					if (message[0] == MessageTypes::NO_CHALLENGE)
					{
						Stime = c1.decodeTime(message);
						//soc.send_message("11,"+to_string(time.playerTime+",")
						c1.setState(States::THINKING);
					}

				}
				else if (c1.getState() == States::AWAIT_CHALLENGE_RESPONSE)
				{
					if (message[0] == MessageTypes::NO_CHALLENGE || message[0] == MessageTypes::CHALLENGE_ACCEPTED)
					{
						Stime = c1.decodeTime(message);
						c1.setState(States::THINKING);
					}
					else if (message[0] == MessageTypes::CHALLENGE_REJECTED)
						c1.setState(States::IDLE);
				}
				if (message[0] == MessageTypes::END)
				{
					cout << "GAME OVER" << endl;
					endMove end = c1.decodeEndGame(message);
					soc.send_message("10," + to_string(end.score) + "," + to_string(end.opponentScore));
					c1.setState(States::READY);
				}
			}
			else
			{

				if (c1.getState() == States::AWAIT_AGENT_CHALLENGE)
				{
					MessageTypes myAgent = MessageTypes::CHALLENGE;

					// Agent decides if he wants to challenge

					if (myAgent == MessageTypes::NO_CHALLENGE)
					{
						c1.sendNoChallenge(ws);
						c1.setState(States::THINKING);
					}
					else if (myAgent == MessageTypes::CHALLENGE)
					{
						c1.sendChallenge(ws);
						c1.setState(States::AWAIT_CHALLENGE_RESPONSE);
					}
				}
			}


			if (c1.getState() == States::THINKING)
			{
				cout << "Thinking" << endl;
				MessageTypes action = PLAY;
				
				vector <Move> MoveList;
				g->findWords(agent->rack->getRackTiles(), MoveList, b);
				if (MoveList.size() == 0) {
					MessageTypes action = PASS;
					c1.sendPass(ws);
					c1.setState(States::IDLE);
					//continue;
				}
				else {
					if (bagCount > 7) {
						selectedMoveIndex = midMan->getBestMove(MoveList, agent->rack, b);
					}
					else {
						cout << "PreEnd" << endl;
						selectedMoveIndex = preEndMan->Blocking(&MoveList, agent->rack, b, PM);
					}

					//cout << "Move Chosen: ";
					//logger.PrintMove(&MoveList[selectedMoveIndex]);
					
					move.reset();
					
					selectedMove = &MoveList[selectedMoveIndex];
					b->formatMyMove(MoveList[selectedMoveIndex], move);
					
					c1.sendPlay(ws, move);
					c1.setState(AWAIT_PLAY_RESPONSE);
					//logger.PrintMoveStruct(moveStruct);
					/*
					b->commitMove(MoveList[selectedMoveIndex]);
					b->computeCrossSets(g->root);
					players[playerTurn]->rack->commitMove(&MoveList[selectedMoveIndex]);
					while (players[playerTurn]->rack->list.size() < RACK_SIZE) {
						if (!bag->hasLetters())break;
						players[playerTurn]->rack->addTile(bag->draw());
					}*/
				}
				// TODO: Add case for swapping
				/*if (action == MessageTypes::EXCHANGE)
				{
					cout << "exchange request" << endl;
					c1.sendExchange(ws, str);
					c1.setState(States::AWAIT_EXCHANGE_RESPONSE);
				}*/
			}

		}
		ws->close();
	}
	else {
		int score = 10; //function should calculate score
		c1.setState(States::READY);
		while (soc.isConnected())
		{//game started send rack to human 
			if (c1.getState() == States::READY)
			{
				// function generating rack for agent and human.
				string human_rack = "1,ABCDEFG,0,0,600000,1200000";
				string agent_rack = "GHIJKLM";
				soc.send_message(human_rack);
				soc.receive();
				//soc.send_message("t0,");
				//soc.receive();
				c1.setState(States::IDLE);

			}

			if (c1.getState() == States::IDLE)
			{
				std::string message = soc.receive();
				if (message[1] == '4')//play
				{
					humanMove move = parsePlay(message);
					cout << move.Scolumn << " " << move.Srow << " " << move.direction << endl;
					displayVector<char>(move.tiles);
					// function validating human move
					string human_validity = "VALID";
					if (human_validity == "VALID")
					{
						soc.send_message("G12,t1," + to_string(score));
						soc.receive();
						c1.setState(States::AWAIT_AGENT_CHALLENGE);//human waits for his play response
					}
					else
					{
						soc.send_message("G94,t0");
						soc.receive();
						c1.setState(States::IDLE);
					}

				}
				else if (message[1] == '2')//human passed
				{
					soc.send_message("t1,");
					soc.receive();
					c1.setState(States::THINKING);//human passed agent turn to play
				}
				else if (message[1] == '3')
				{
					//human sent exchange waiting for response
					//function to send Exchanged tiles to human
					message.erase(0);
					message.erase(1);
					message.erase(2);
					int bag = 8;//checks tiles in bag
					string oldTiles = message;
					string exchagedTiles = "TYZ....";
					if (bag > 7)
					{
						soc.send_message("G11,t1," + oldTiles + "," + exchagedTiles);
						soc.receive();
						c1.setState(States::THINKING);
					}
					else
					{
						soc.send_message("G93,t0");
						soc.receive();
						c1.setState(States::IDLE);
					}
				}
			}
			if (c1.getState() == States::THINKING)
			{
				MessageTypes action = PLAY; // function to determine the action.
				if (action == MessageTypes::PASS)
				{

					soc.send_message("A2,t0");
					soc.receive();
					cout << "pass sent" << endl;
					c1.setState(States::IDLE);
				}
				else if (action == MessageTypes::EXCHANGE)
				{
					soc.send_message("A3,t1");
					soc.receive();
					//function for exchange of agent tiles.
					c1.setState(States::AWAIT_EXCHANGE_RESPONSE);
				}
				else if (action == MessageTypes::PLAY)
				{
					string playValidity = "VALID";
					if (playValidity == "INVALID")
					{
						soc.send_message("A9,t1");
						soc.receive();
						c1.setState(States::THINKING);
					}
					else
					{
						soc.send_message("A4,t0," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score));
						cout << "playing" << endl;
						cout << "A4,t0," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score) << endl;
						soc.receive();
						//function checking validity of Play.
						c1.setState(States::AWAIT_PLAY_RESPONSE);
					}
				}

			}
			if (c1.getState() == AWAIT_PLAY_RESPONSE)
			{

				string message = soc.receive();

				if (message[1] == '6')
				{// function to check challenge type.
					string Challenge = "CHALLENGE_ACCEPTED";
					if (Challenge == "CHALLENGE_ACCEPTED")
					{
						soc.send_message("G7,t0," + to_string(score));//send agent score
						cout << "G7,t0," + to_string(score) << endl;
						soc.receive();
						c1.setState(States::IDLE);
					}
					else
					{
						soc.send_message("G8,t1");// challenge rejected.
											  //function to receive new tiles.
						soc.receive();
						c1.setState(States::THINKING);
					}
				}
				else if (message[1] == '5')
				{
					// NOchallenge from human.
					// function to receive new tiles.
					soc.send_message("t0");
					soc.receive();
					c1.setState(States::IDLE);
				}

			}
			if (c1.getState() == AWAIT_EXCHANGE_RESPONSE)
			{
				//return of exchange function "INVALID" or new tiles.
				string exchangeResponse = "INVALID";

				if (exchangeResponse == "INVALID")
				{
					soc.send_message("A9,t1");
					soc.receive();
					c1.setState(States::THINKING);
				}
				else
				{
					// add new tiles to agent rack.
					soc.send_message("A11,t0");
					soc.receive();
					c1.setState(States::IDLE);
				}
			}
			if (c1.getState() == AWAIT_CHALLENGE_RESPONSE)
			{
				// function has 2 returns {CHALLENGE ACCEPTED,CHALLENGE REJECTED}
				string challengeResponse = "CHALLENGE_ACCEPTED";
				if (challengeResponse == "CHALLENGE_ACCEPTED")
				{
					soc.send_message("A7,t1," + to_string(score));//human score to be penalized
					soc.receive();
					c1.setState(States::THINKING);
				}
				else if (challengeResponse == "CHALLENGE REJECTED")
				{
					soc.send_message("A8,t0");
					soc.receive();
					c1.setState(States::IDLE);
				}
			}
			if (c1.getState() == AWAIT_AGENT_CHALLENGE)
			{
				// function to return agent wants to challenge or not.
				string agentChallenge = "NO Challenge";
				if (agentChallenge == "NO Challenge")
				{
					soc.send_message("A5,t1,");
					soc.receive();
					c1.setState(States::THINKING);
				}
				else
				{
					soc.send_message("A6,t1");
					soc.receive();
					c1.setState(States::AWAIT_CHALLENGE_RESPONSE);
				}
				// if time is over means that agent don't  want to challenge and go to thinking state.don't know how to implement.
			}
		}

	}
	system("pause");
}