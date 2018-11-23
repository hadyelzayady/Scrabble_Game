#pragma once
class Utilities {
	long double factorialDB[100];
public:
	long double Cparta(int K, int r);
	long double Cpartb(int N, int n);
	long double Cpartc(int N, int K, int n, int r);
	long double factorial(int n);
	void setFactorialDB();
	Utilities();
	~Utilities();
};
