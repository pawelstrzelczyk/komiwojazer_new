#pragma once
#include "punkt.hpp"
#include <queue>

class qu
{
public:
	template <typename T>
	void printQueue(T& Q)
	{
		while (!Q.empty())
		{
			std::cout << "(" << Q.front().getX() << "," << Q.front().getY() << ")\n";
			Q.pop();
		}
	}
};