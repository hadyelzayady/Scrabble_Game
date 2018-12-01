#include"Client.h"
static WebSocket::pointer ws = NULL;
std::string playerNameString = "ahmed";
std::vector<uint8_t> playerName;

int main()
{
	int p = 1;
	Client c1;
#ifdef _WIN32
	INT rc;
	WSADATA wsaData;

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc) {
		printf("WSAStartup Failed.\n");
		return 1;
	}
#endif
		std::unique_ptr<WebSocket> ws(WebSocket::from_url("ws://localhost:8080"));
		assert(ws);
		vector<char>tiles(7);
		int count;
		uTime time;
		std::vector<uint8_t> message;
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
					cout << "info.order: " << info.order << endl;
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
						time = c1.decodeTime(message);
						c1.setState(States::THINKING);
					}
					if (message[0] == MessageTypes::EXCHANGE)
					{
						tiles = c1.decodeTiles(message);
						c1.setState(States::IDLE);
					}
				}
				else if (c1.getState() == States::AWAIT_PLAY_RESPONSE)
				{
					if (message[0] == MessageTypes::INVALID)
					{
						time = c1.decodeTime(message);
						c1.setState(States::THINKING);
					}
					else if (message[0] == MessageTypes::CHALLENGE_REJECTED)
					{
						c1.decodeChallengeRejected(message, tiles, time);
						c1.setState(States::THINKING);
					}
					else if (message[0] == MessageTypes::NO_CHALLENGE)
					{
						c1.decodeTiles(message);//gets tiles
						c1.setState(States::IDLE);
					}
					else if (message[0] == MessageTypes::CHALLENGE_ACCEPTED)
						c1.setState(States::IDLE);
				}
				else if (c1.getState() == States::IDLE)
				{
					if (message[0] == MessageTypes::PASS)
					{
						time = c1.decodeTime(message);
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
						c1.setState(States::AWAIT_AGENT_CHALLENGE);

					}
				}
				else if (c1.getState() == States::AWAIT_AGENT_CHALLENGE)
				{
					if (message[0] == MessageTypes::NO_CHALLENGE)
					{
						time = c1.decodeTime(message);
						c1.setState(States::THINKING);

					}
				}
				else if (c1.getState() == States::AWAIT_CHALLENGE_RESPONSE)
				{
					if (message[0] == MessageTypes::NO_CHALLENGE || message[0] == MessageTypes::CHALLENGE_ACCEPTED)
					{
						time = c1.decodeTime(message);
						c1.setState(States::THINKING);

					}
					else if (message[0] == MessageTypes::CHALLENGE_REJECTED)
						c1.setState(States::IDLE);
				}
				if (message[0] == MessageTypes::END)
				{
					cout << "GAME OVER" << endl;
					c1.decodeEndGame(message);
					c1.setState(States::READY);
				}
			}
			else
			{

				if (c1.getState() == States::AWAIT_AGENT_CHALLENGE)
				{
					MessageTypes agent = MessageTypes::CHALLENGE;
					if (agent == MessageTypes::NO_CHALLENGE)
					{
						c1.sendNoChallenge(ws);
						c1.setState(States::THINKING);
					}
					else if (agent == MessageTypes::CHALLENGE)
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
				vector<char> s = { 'I','.','.','.','.','.','.' };
				playMove move;
				move.direction = 0;
				move.Scolumn = 8;
				move.Srow = 9;
				move.tiles = s;
				move.score = 4;
				//cin >> action;
				if (action == MessageTypes::PASS)
				{

					c1.sendPass(ws);
					cout << "pass sent" << endl;
					c1.setState(States::IDLE);
				}
				else if (action == MessageTypes::EXCHANGE)
				{
					cout << "exchange request" << endl;
					c1.sendExchange(ws, s);
					c1.setState(States::AWAIT_EXCHANGE_RESPONSE);
				}
				else if (action == MessageTypes::PLAY)
				{
					cout << "playing" << endl;
					c1.sendPlay(ws, move);
					c1.setState(AWAIT_PLAY_RESPONSE);
				}

			}

		}
		ws->close();
}
