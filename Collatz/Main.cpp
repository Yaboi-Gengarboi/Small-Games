// Collatz
// Main.cpp
// Created on 2023-02-16 by Justyn Durnford
// Last modified on 2023-02-16 by Justyn Durnford
// 

#include <fstream>
using std::ofstream;

#include <functional>
using std::function;

#include <iostream>
using std::cout;

#include <string>
using std::string;
using std::stoi;
using std::to_string;

ofstream fout;

void collatz_3nplus1(unsigned int n)
{
	fout.open("3n+1\\" + to_string(n) + ".txt");

	function<void(unsigned int)> write = [](unsigned int i)
	{
		cout << i << '\n';
		fout << i << '\n';
	};

	while (n > 1)
	{
		write(n);

		if (n % 2 == 0)
			n /= 2;
		else
			n = 3 * n + 1;
	}

	if (n == 1)
		write(1);
}

void collatz_2nplus2(unsigned int n)
{
	fout.open("2n+2\\" + to_string(n) + ".txt");

	function<void(unsigned int)> write = [](unsigned int i)
	{
		cout << i << '\n';
		fout << i << '\n';
	};

	while (n > 1)
	{
		write(n);

		if (n % 2 == 0)
			n /= 2;
		else
			n = 2 * n + 2;
	}

	if (n == 1)
		write(1);
}

int main(int argc, char** argv)
{
	collatz_3nplus1(28);
	collatz_2nplus2(28);
	return 0;
}