#pragma once
using namespace std;
#include "punkt.hpp"
punkt point;
class TSP
{
public:
	void ants(int n, punkt::pkt tab[], double** distances, double** visibility, double** pheromone, int** routes)
	{
		int colonySize = 30;
		double** visibilityTemp = new double*[n];
		double* probability = new double[n];
		double* p = new double[n];
		double alpha = 2, beta = 4, sum = 0, r;
		for (int i = 0; i < n; i++)
			visibilityTemp[i] = new double[n];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				pheromone[i][j] = 0.0001;
				distances[i][j] = point.odleglosc(tab[i], tab[j]);
				if (i == j)
				{
					visibility[i][j] = 0;
				}
				else
					visibility[i][j] = double(1 / distances[i][j]);
				visibility[i][0] = 0;
			}
		}
		for (int i = 0; i < colonySize; i++)
		{
			for (int a = 0; a < n; a++)
			{
				for (int b = 0; b < n; b++)
				{
					visibilityTemp[a][b] = visibility[a][b];
				}
			}
			for (int j = 0; j < n - 1; j++)
			{
				int current = routes[i][j];
				for (int a = 0; a < n; a++)
				{
					visibilityTemp[a][current] = 0;
				}
				for (int a = 0; a < n; a++)
				{
					probability[a] = pow(pheromone[current][a], alpha) * pow(visibilityTemp[current][a], beta);
					sum += probability[a];
				}
				for (int a = 0; a < n; a++)
				{
					p[a] = (1 / sum) * p[a];
				}
				sum = 0;
				r = ((double)rand() / (RAND_MAX));

				for (int k = 0; k < n; k++)
				{
					sum += p[k];

					if (r <= sum)
					{
						routes[i][j + 1] = k;

						break;
					}
				}
			}
		}
	}

	void komiwojazer(int n, punkt::pkt tab[], queue<punkt::pkt>& Q)
	{
		int v;
		double calaodleglosc = 0;
		punkt::pkt min_pkt = tab[0];
		tab[0].flag = true;
		for (int i = 1; i < n; i++)
		{
			double min = 1000000000;
			double aktualnaOdleglosc = 1000000000;
			v = 0;

			for (int j = 1; j < n; j++)
			{
				if (tab[j].flag == false)
					aktualnaOdleglosc = point.odleglosc(min_pkt, tab[j]);

				if (aktualnaOdleglosc < min && tab[j].flag == false)
				{
					min = aktualnaOdleglosc;
					cout << min << " "
						 << "(" << j << ") ";

					v = j;
				}
			}
			min_pkt = tab[v];
			cout << endl;
			calaodleglosc += min;

			tab[v].flag = true;
			Q.push(tab[v]);
		}
		calaodleglosc += point.odleglosc(tab[0], tab[v]);
		Q.push(tab[0]);
		cout << endl
			 << "Calkowita odleglosc: " << calaodleglosc << endl;
	}
};