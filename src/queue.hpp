#pragma once
#include "punkt.hpp"
#include <queue>

class qu
{
public:
	template <typename T>
	void printQueue(T Q)
	{
		while (!Q.empty())
		{
			std::cout << "(" << Q.front().getX() << "," << Q.front().getY() << ")\n";
			Q.pop();
		}
	}
	template <typename T>
	void returnQueue(T& Q, punkt::pkt tablica[])
	{
		int i = Q.size() - 1;
		while (!Q.empty())
		{
			tablica[i] = Q.front();
			i--;
			Q.pop();
		}
	}
};