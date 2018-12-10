//#include"Client.h"
//#include"functions2.h"
//#include"communication_server.hpp"
//#include "GameManager.h"
//#include "Logger.h"
//static WebSocket::pointer ws = NULL;
//
//std::vector<uint8_t> playerName;
//
//int main(int argc, char *argv[])
//{
//	communication::server guiSocket(2019);
//	guiSocket.start(); //blocking till GUI connects 
//	std::string read = guiSocket.receive();
//	playerStart player = parseStart(read);
//	char modeOfOperation = argv[1][0];
//	switch (modeOfOperation)
//	{
//	case 'A':
//		Player * agent = new Player(player.PlayerName);
//		//Player * opponent = new Player("My Opponent");
//		#ifdef _WIN32
//				INT rc;
//				WSADATA wsaData;
//				rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
//				if (rc) {
//					printf("WSAStartup Failed.\n");
//					return 1;
//				}
//		#endif
//				std::string playerNameString = agent->playerName;
//				std::unique_ptr<WebSocket> ws(WebSocket::from_url(player.connection));
//				assert(ws);
//
//				// Part Added
//				// int p = 1;
//				Client c1;
//				// playMove move;
//
//				//vector<char>tiles(7);
//				int count;
//				uTime time;
//				std::vector<uint8_t> message;
//
//				cout << "Initialising TileLookup...";
//				TileLookUp * TL = new TileLookUp();
//				cout << "Done" << endl;
//
//
//				cout << "Building GADDAG..." << endl;
//				Gaddag *g = new Gaddag("../Text/SOWPODS.txt");
//				cout << "Done" << endl;
//
//
//				cout << "Initialising Board..." << endl;
//				Board * b;
//
//				cout << "Done" << endl;
//
//				//################################### Managers ########################################
//				MidGameManager * midMan = new MidGameManager(TL, g);
//
//
//
//
//				Logger logger;
//
//				// Game Starts
//				while (ws->getReadyState() != WebSocket::CLOSED) {
//					bool gotMessage = false;
//					ws->poll();
//					ws->dispatchBinary([gotMessageOut = &gotMessage, messageOut = &message, ws = ws.get()](const std::vector<uint8_t>& message) {
//						*gotMessageOut = true;
//						*messageOut = message;
//
//					});
//					if (gotMessage)
//					{
//						//cout << int(message[0]) << endl;
//						if (message[0] == MessageTypes::NAME && c1.getState() == States::INIT)
//						{
//							c1.sendInitState(ws, playerNameString);
//							c1.setState(States::READY);
//						}
//						else if (message[0] == MessageTypes::START && c1.getState() == States::READY)
//						{
//							readyStruct_formated info;
//							info = c1.decodeReadyState(message);
//							guiSocket.send_message("1," + string(info.tiles.begin(), info.tiles.end()) + "," + to_string(info.score) + "," + to_string(info.opponentScore) + "," + to_string(info.playerTime) + "," + to_string(info.totalTime));
//							//cout << "info.order: " << info.order << endl;
//							b = new Board(info.board);
//
//
//							int rackSize = info.tiles.size();
//							for (int i = 0; i < rackSize; i++) {
//								agent->rack->addTile(info.tiles[i]);
//							}
//							
//							agent->playerScore = info.score;
//							
//							if (info.order == 1)
//							{
//								//cout << "It is your turn now" << endl;
//								c1.setState(States::THINKING);
//							}
//							else c1.setState(States::IDLE);
//						}
//						else if (c1.getState() == States::AWAIT_EXCHANGE_RESPONSE)
//						{
//							if (message[0] == MessageTypes::INVALID)
//							{
//								time = c1.decodeTime(message);
//								c1.setState(States::THINKING);
//							}
//							if (message[0] == MessageTypes::EXCHANGE)
//							{
//								tiles = c1.decodeTiles(message);
//								guiSocket.send_message("3," + string(str.begin(), str.end()) + "," + string(tiles.begin(), tiles.end()));
//								c1.setState(States::IDLE);
//							}
//						}
//						else if (c1.getState() == States::AWAIT_PLAY_RESPONSE)
//						{
//							if (message[0] == MessageTypes::INVALID)
//							{
//								time = c1.decodeTime(message);
//								c1.setState(States::THINKING);
//							}
//							else if (message[0] == MessageTypes::CHALLENGE_REJECTED)
//							{
//								c1.decodeChallengeRejected(message, tiles, time);
//								c1.setState(States::THINKING);
//							}
//							else if (message[0] == MessageTypes::NO_CHALLENGE)
//							{
//								vector<char>new_tiles = c1.decodeTiles(message);//gets tiles
//								guiSocket.send_message("5," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score) + "," + string(new_tiles.begin(), new_tiles.end()));
//								cout << "5," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score) + "," + string(new_tiles.begin(), new_tiles.end()) << endl;
//							}
//							else if (message[0] == MessageTypes::CHALLENGE_ACCEPTED)
//							{
//								guiSocket.send_message("7," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score));
//								cout << "7," + to_string(move.Scolumn) + "," + to_string(move.Srow) + "," + to_string(move.direction) + "," + string(move.tiles.begin(), move.tiles.end()) + "," + to_string(move.score) << endl;
//								c1.setState(States::IDLE);
//
//							}
//						}
//						else if (c1.getState() == States::IDLE)
//						{
//							if (message[0] == MessageTypes::PASS)
//							{
//								time = c1.decodeTime(message);
//								c1.setState(States::THINKING);
//							}
//							else if (message[0] == MessageTypes::EXCHANGE)
//							{
//								c1.decodeIdleExchange(message, count, time); //get time and count.
//								c1.setState(States::THINKING);
//							}
//							else if (message[0] == MessageTypes::PLAY)
//							{
//								player2Move_formated play2move;
//								play2move = c1.decodePlay(message);
//								guiSocket.send_message("4," + to_string(play2move.Scolumn) + "," + to_string(play2move.Srow) + "," + to_string(play2move.direction) + "," + string(play2move.tiles.begin(), play2move.tiles.end()) + "," + to_string(play2move.score));
//								c1.setState(States::AWAIT_AGENT_CHALLENGE);
//
//							}
//						}
//						else if (c1.getState() == States::AWAIT_AGENT_CHALLENGE)
//						{
//							if (message[0] == MessageTypes::NO_CHALLENGE)
//							{
//								time = c1.decodeTime(message);
//								c1.setState(States::THINKING);
//
//							}
//						}
//						else if (c1.getState() == States::AWAIT_CHALLENGE_RESPONSE)
//						{
//							if (message[0] == MessageTypes::NO_CHALLENGE || message[0] == MessageTypes::CHALLENGE_ACCEPTED)
//							{
//								time = c1.decodeTime(message);
//								c1.setState(States::THINKING);
//
//							}
//							else if (message[0] == MessageTypes::CHALLENGE_REJECTED)
//								c1.setState(States::IDLE);
//						}
//						if (message[0] == MessageTypes::END)
//						{
//							cout << "GAME OVER" << endl;
//							endMove end = c1.decodeEndGame(message);
//							guiSocket.send_message("10," + to_string(end.score) + "," + to_string(end.opponentScore));
//							c1.setState(States::READY);
//						}
//					}
//					else
//					{
//
//						if (c1.getState() == States::AWAIT_AGENT_CHALLENGE)
//						{
//							MessageTypes agent = MessageTypes::CHALLENGE;
//							if (agent == MessageTypes::NO_CHALLENGE)
//							{
//								c1.sendNoChallenge(ws);
//								c1.setState(States::THINKING);
//							}
//							else if (agent == MessageTypes::CHALLENGE)
//							{
//								c1.sendChallenge(ws);
//								c1.setState(States::AWAIT_CHALLENGE_RESPONSE);
//							}
//						}
//					}
//
//
//					if (c1.getState() == States::THINKING)
//					{
//
//						vector <Move> MoveList;
//						g->findWords(agent->rack->getRackTiles(), MoveList, b);
//						int selectedMoveIndex = midMan->getBestMove(MoveList, agent->rack, b);
//						// cout << "Thinking" << endl;
//						// Selected Move: MoveList[selectedMoveIndex]
//						MessageTypes action = PLAY;
//
//						//playMove move;
//						move.direction = 0;
//						move.Scolumn = 7;
//						move.Srow = 11;
//						move.tiles = str;
//						move.score = 4;
//						//cin >> action;
//						if (action == MessageTypes::PASS)
//						{
//
//							c1.sendPass(ws);
//							cout << "pass sent" << endl;
//							c1.setState(States::IDLE);
//						}
//						else if (action == MessageTypes::EXCHANGE)
//						{
//							cout << "exchange request" << endl;
//							c1.sendExchange(ws, str);
//							c1.setState(States::AWAIT_EXCHANGE_RESPONSE);
//						}
//						else if (action == MessageTypes::PLAY)
//						{
//							cout << "playing" << endl;
//							c1.sendPlay(ws, move);
//							c1.setState(AWAIT_PLAY_RESPONSE);
//						}
//
//					}
//
//				}
//				ws->close();
//
//		break;
//	case 'P':
//		
//		break;
//	default:
//
//		break;
//	}
//	
//	system("pause");
//}