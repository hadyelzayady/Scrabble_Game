#pragma once
#include<vector>
#include <string>
using namespace std;

template<class myType> 
void displayVector(vector<myType>v)
{
	for (int i = 0; i<int(v.size()); i++)
			cout << v[i] << " ";
	cout << endl;

}
vector<char> convertToletters(vector<int>v)
{
	vector<char>result;
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		if (v[i] == 0)
			result.push_back('.');
		else if (v[i] == 100)
			result.push_back('[]');
		else if (v[i] > 100)
			result.push_back((char)v[i]-101+'A');
		else
			result.push_back((char)(v[i] + 'A' - 1));
	
	}
	return result;
}


vector<int> convertToNumbers(vector<char>v)
{
	vector<int>result;
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		if (v[i] == '.')
			result.push_back(0);
		else if (v[i] == '[]')
			result.push_back(100);
		else
			result.push_back((int)(v[i] - 'A' + 1));

	}
	return result;

}
string timeFormat(int32_t time)
{
	string Stime;
	int sign = (time > 0) ? 1 : ((time < 0) ? -1 : 0);
	int utime = trunc(time *sign);
	cout << "time: " << time << endl;
	int ms = utime % 1000;
	cout << "ms: " << ms << endl;
	int s = int( utime / 1000) % 60;
	cout << "s: " << s << endl;
	int m = int(utime / 60000);
	cout << "m: " << m << endl;
	Stime = m + s + ms;
	return Stime;

}