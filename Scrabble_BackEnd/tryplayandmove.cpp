#include "move.h"
int main() {
	Move * m = new Move();
	Play * a = new Play();
	a->set_Letter('A');
	pair<int, int> c;
	c.first = 3;
	c.second = 4;
	a->set_Cooridantes(c);
	m->addPlay(*a);
	vector< Play>  P = m->getPlaysPointer();
	cout << P.begin()->get_Letter() << endl;
	cout << P.begin()->get_Cooridantes().first << endl;
	cout << P.begin()->get_Cooridantes().second << endl;
	system("pause");
	return 0;
}