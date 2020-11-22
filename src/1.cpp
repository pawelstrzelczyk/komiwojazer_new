#include "generator.hpp"
#include "punkt.hpp"
#include "queue.hpp"
#include "tsp.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>

int main()
{
	generator gen;
	TSP tsp;
	qu q;
	std::queue<punkt::pkt> Q;
	srand(time(0));
	ifstream in;
	gen.instanceGenerator(25, 1000);
	in.open("dane.txt");

	int i = 0;
	int liczba;
	in >> liczba;
	const int liczba_ = liczba;

	punkt::pkt tab[100];
	int x, y, id;

	while (!in.eof())
	{
		in >> id >> x >> y;
		tab[i].setId(id);
		tab[i].setX(x);
		tab[i].setY(y);
		i++;
	}

	Q.push(tab[0]);
	tsp.komiwojazer(liczba_, tab, Q);
	q.printQueue(Q);
}