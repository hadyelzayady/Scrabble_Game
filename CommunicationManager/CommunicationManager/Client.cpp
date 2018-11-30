#include "Client.h"
#include "functions.h"

Client::Client()
{
	state = States::INIT;
}
void Client::setState(States s)
{
	this->state = s;
}
States Client::getState()
{
	return this->state;
}

vector<uint8_t> Client::encodeInitState(string name)
{
	vector<uint8_t> playerName;
	playerName.clear();
	playerName.push_back(MessageTypes::NAME);
	playerName.resize(name.length() + 1);
	memcpy(playerName.data() + 1, name.data(), name.length());
	return playerName;
}
vector<uint8_t> Client::encodeTiles(vector<string>v)
{
	vector<uint8_t> tiles;
	tiles.clear();
	tiles.resize(v.size());
	memcpy(tiles.data(), v.data(), v.size());
	return tiles;
}

void Client::sendInitState(unique_ptr<WebSocket> &ws, string name)
{
	ws->sendBinary(encodeInitState(name));
}
readyStruct_formated Client::decodeReadyState(std::vector<uint8_t>& message)
{
	readyStruct ready;
	readyStruct_formated ready_formated;
	unsigned int bufferOffset = 0;

	memcpy(&ready.type, message.data()+ bufferOffset,sizeof(ready.type));
	bufferOffset += sizeof(ready.type);
	ready_formated.type = int(ready.type);
	cout << "type: "<< int(ready.type) << endl;

	memcpy(&ready.order, message.data() + bufferOffset, sizeof(ready.order));
	bufferOffset += sizeof(ready.order);
	ready_formated.type = int(ready.order);
	cout << "Order: "<< int(ready.order) << endl;

	ready.tiles.resize(7);
	memcpy(ready.tiles.data() , message.data()+ bufferOffset,7);
	bufferOffset += ready.tiles.size();
	vector<int> v(ready.tiles.begin(), ready.tiles.end());
	ready_formated.tiles = convertToletters(v);

	cout << "number of tiles: "<<ready.tiles.size()<<endl;
	cout << "tiles recieved: ";
	for (int i = 0; i<int(ready.tiles.size()); i++)
		if(i!= int(ready.tiles.size()))
		cout << int(ready.tiles[i]) << " ";
	cout<< endl;
	cout << "tiles recieved: ";
	for (int i = 0; i<int(ready_formated.tiles.size()); i++)
		if (i != int(ready_formated.tiles.size()))
			cout << ready_formated.tiles[i] << " ";
	cout << endl;

	ready.board.resize(225);
	memcpy(ready.board.data(), message.data() + bufferOffset, 225);
	bufferOffset += ready.board.size();
	vector<int> v2(ready.board.begin(), ready.board.end());
	vector<char>board = convertToletters(v2);

	int count = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			ready_formated.board[i][j] = board[count];
			cout << ready_formated.board[i][j] << " ";
			count++;
		}
		cout << endl;
	}

	memcpy(&ready.score, message.data() + bufferOffset, sizeof(ready.score));
	bufferOffset += sizeof(ready.score);
	ready_formated.score = int(ready.score);
	cout << "myscore: " << ready.score << endl;

	memcpy(&ready.opponentScore, message.data() + bufferOffset, sizeof(ready.opponentScore));
	bufferOffset += sizeof(ready.opponentScore);
	ready_formated.opponentScore = int(ready.opponentScore);
	cout << "OpponentScore: " << ready.opponentScore << endl;

	memcpy(&ready.playerTime, message.data() + bufferOffset, sizeof(ready.playerTime));
	bufferOffset += sizeof(ready.playerTime);
	cout << "myTime: " << ready.playerTime << endl;

	memcpy(&ready.totalTime, message.data() + bufferOffset, sizeof(ready.totalTime));
	bufferOffset += sizeof(ready.totalTime);
	cout << "totalTime: " << ready.totalTime << endl;

	return ready_formated;

}

void Client::sendPass(unique_ptr<WebSocket> &ws)
{
	vector<uint8_t> pass;
	pass.push_back(MessageTypes::PASS);
	ws->sendBinary(pass);
}

void Client::sendExchange(unique_ptr<WebSocket> &ws, vector<string> tiles)
{
	vector<uint8_t> exchange;
	vector<uint8_t> tiles =this->encodeTiles(tiles);
	exchange.push_back(MessageTypes::EXCHANGE);
	exchange.insert(exchange.end(), tiles.begin(), tiles.end());
	ws->sendBinary(exchange);
}

Client::~Client()
{
}
