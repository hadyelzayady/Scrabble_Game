#include"Client.h"
static WebSocket::pointer ws = NULL;
std::string playerNameString = "ahmed";
std::vector<uint8_t> playerName;

int main()
{
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
			if (message[0] == MessageTypes::NAME && c1.getState()==States::INIT)
			{
				c1.sendInitState(ws, playerNameString);
				c1.setState(States::READY);
			}
			if (message[0] == MessageTypes::START && c1.getState() == States::READY)
			{
				readyStruct_formated info;
				info = c1.decodeReadyState(message);
				if (info.order == 1)
				{
					cout << "It is your turn now" << endl;
					c1.setState(States::THINKING);
				}
				else c1.setState(States::IDLE);
			}
		}
		if (c1.getState() == States::THINKING)
		{
			int action;
			vector<string> s = { "A","B" };
			cin >> action;
			if (action == MessageTypes::PASS)
			{
				c1.sendPass(ws);
			}
			if (action == MessageTypes::EXCHANGE)
			{
				c1.sendExchange(ws, s);
			}
			if (action == MessageTypes::PLAY)
			{

			}

		}
	}

	ws->close(); 
}
