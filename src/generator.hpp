#pragma once
#include <fstream>
#include <iostream>

class generator
{
public:
	void instanceGenerator(int n, int range)
	{

		std::ofstream out;
		out.open("dane.txt");
		int x, y;
		out << n << std::endl;
		for (int i = 1; i <= n; i++)
		{
			x = rand() % range;
			y = rand() % range;
			out << i << " " << x << " " << y << std::endl;
		}
		out.close();
	};
};
