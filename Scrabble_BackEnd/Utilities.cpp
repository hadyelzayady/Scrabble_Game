#include "Utilities.h"



int Utilities::C(int n, int r)
{
	return factorial(n)/(factorial(r)*factorial(n-r));
}

int Utilities::factorial(int n)
{
	if (n > 1)
		return n * factorial(n - 1);
	else
		return 1;
}

Utilities::Utilities()
{
}


Utilities::~Utilities()
{
}
