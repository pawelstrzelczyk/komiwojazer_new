#include "generator.hpp"
#include "punkt.hpp"
//#include "queue.hpp"
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
	//qu q;

	std::queue<punkt::pkt> Q;
	srand(time(0));
	ifstream in;
	gen.instanceGenerator(25, 1000);
	in.open("berlin52.txt");

	int i = 0, colonySize = 30;
	double evaporation = 0.15;
	int liczba;
	in >> liczba;
	const int liczba_ = liczba;
	double **distances = new double *[liczba_], **visibility = new double *[liczba_], **pheromone = new double *[liczba_], *oneAntdistance = new double[colonySize];
	int** routes = new int*[colonySize];
	for (int i = 0; i < liczba_; i++)
	{
		distances[i] = new double[liczba_];
		visibility[i] = new double[liczba_];
		pheromone[i] = new double[liczba_];
		routes[i] = new int[liczba_];
	}
	for (int i = 0; i < liczba_; i++)
	{
		for (int j = 0; j < liczba_; j++)
		{
			distances[i][j] = 0;
			visibility[i][j] = 0;
			if (i != j)
				pheromone[i][j] = 0.0001;
			else
				pheromone[i][j] = 0;
		}
	}
	for (int i = 0; i < colonySize; i++)
	{
		oneAntdistance[i] = 0;
		for (int j = 0; j < liczba_; j++)
		{
			if (j != 0)
				routes[i][j] = 0;
			else
				routes[i][j] = rand() % liczba_;
		}
	}

	punkt::pkt tab[1001];
	int x, y, id;

	while (!in.eof())
	{
		in >> id >> x >> y;
		tab[i].setId(id);
		tab[i].setX(x);
		tab[i].setY(y);
		i++;
	}

	//Q.push(tab[0]);
	//tsp.komiwojazer(liczba_, tab, Q);
	double MIN = 1000000;
	double* best = new double[liczba_];
	int* bestOfAll = new int[liczba_];
	for (int i = 0; i < 500; i++)
	{
		tsp.ants(liczba_, colonySize, tab, distances, visibility, pheromone, routes);
		tsp.pherAct(liczba_, evaporation, colonySize, pheromone, routes, distances);
		best = tsp.countCost(liczba_, colonySize, distances, routes);
		for (int i = 0; i < colonySize; i++)
		{
			if (best[i] < MIN)
			{
				MIN = best[i];
				for (int j = 0; j < liczba_; j++)
				{
					bestOfAll[j] = routes[i][j];
				}
			}
		}
	}
	cout << endl
		 << MIN << endl;
	for (int j = 0; j < liczba_; j++)
	{
		cout << bestOfAll[j] << " ";
	}
	/*ofstream out;
	out.open("visibility.csv");
	for (int i = 0; i < liczba_; i++)
	{
		for (int j = 0; j < liczba_; j++)
		{
			out << visibility[i][j] << ";";
		}
		out << endl;
	}
	out.close();
	out.open("routes.csv");
	for (int i = 0; i < colonySize; i++)
	{
		for (int j = 0; j < liczba_; j++)
		{
			out << routes[i][j] << ";";
		}
		out << endl;
	}
	out.close();
	out.open("pheromone.csv");
	for (int i = 0; i < liczba_; i++)
	{
		for (int j = 0; j < liczba_; j++)
		{
			out << pheromone[i][j] << ";";
		}
		out << endl;
	}
	out.close();*/
	//punkt::pkt t[1001];
	//q.printQueue(Q);
	//q.returnQueue(Q, t);

	/*const int temp_size = liczba_*2;
	int tab_pomX[liczba_];
	int tab_pomY[liczba_];
	int i=0;
	while(!Q.empty()){
	tab_pomX[i] = Q.front().getX();
	tab_pomY[i] = Q.front().getY();
	 Q.pop();
	}*/
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "Window");
	while (window.isOpen())
	{
		sf::Font font;
		font.loadFromFile("times.ttf");
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		float temp2 = 0;
		float temp1 = 0;
		sf::VertexArray lines(sf::LineStrip, liczba_ + 1);
		for (int i = 0; i < liczba_; i++)
		{
			temp1 = tab[bestOfAll[i]].getX();
			temp2 = tab[bestOfAll[i]].getY();
			sf::String str;

			string z = "";
			z += char((tab[bestOfAll[i]].getId() / 10) % 10 + '0');
			z += char(tab[bestOfAll[i]].getId() % 10 + '0');

			sf::Text entity(z, font, 30);
			entity.setPosition(temp1, temp2);
			window.draw(entity);
			lines[i].position = sf::Vector2f(temp1, temp2);
		}

		window.draw(lines);
		window.display();
	}
	delete[] routes;
	delete[] distances;
	delete[] visibility;
	delete[] oneAntdistance;
	delete[] pheromone;
}