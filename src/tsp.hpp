#pragma once
using namespace std;
#include "punkt.hpp"
punkt point;

class TSP
{
public:
	double power(double base, int power)
	{
		double result = 1;
		for (int i = 0; i < power; i++)
		{
			result *= base;
		}
		return result;
	}
	void printTab(int n, int s, double** routes)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < s; j++)
			{
				cout << routes[i][j] << " ";
			}
			cout << endl;
		}
	}
	double* countCost(int n, int colonySize, double**& distances, int**& routes)
	{
		double distance = 0;
		double* arr = 0;
		arr = new double[colonySize];
		for (int i = 0; i < colonySize; i++)
		{
			distance = 0;
			for (int j = 0; j < n; j++)
			{
				distance += distances[routes[i][j]][routes[i][j + 1]];
			}
			arr[i] = distance;
		}

		return arr;
	}

	void pherAct(int n, double p, int colonySize, double**& pheromone, int**& routes, double**& distances, double Q)
	{
		double* arr = new double[colonySize];
		arr = countCost(n, colonySize, distances, routes);
		for (int i = 0; i < colonySize; i++)
		{

			for (int j = 0; j < n; j++)
			{
				pheromone[routes[i][j]][routes[i][j + 1]] = double(1 - p) * pheromone[routes[i][j]][routes[i][j + 1]] + double(Q / arr[i]);
			}
		}
	}

	void ants(int n, int colonySize, punkt::pkt tab[], double**& distances, double**& visibility, double**& pheromone, int**& routes, int alpha, int beta)
	{

		double** visibilityTemp = new double*[n];
		double* probability = new double[n];
		double* p = new double[n];
		double sum = 0, r;
		int current = 0;
		for (int i = 0; i < n; i++)
			visibilityTemp[i] = new double[n];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				distances[i][j] = point.odleglosc(tab[i], tab[j]);
				if (i == j)
				{
					visibility[i][j] = 0;
				}
				else
					visibility[i][j] = double(1 / distances[i][j]);
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

			for (int j = 0; j < n; j++)
			{
				current = routes[i][j];
				sum = 0;
				for (int a = 0; a < n; a++)
				{
					visibilityTemp[a][current] = 0;
					probability[a] = 0;
				}

				for (int a = 0; a < n; a++)
				{
					if (visibilityTemp[current][a] != 0)
						probability[a] = power(pheromone[current][a], alpha) * power(visibilityTemp[current][a], beta);
					else
						probability[a] = 0;
					sum += probability[a];
				}

				for (int a = 0; a < n; a++)
				{
					p[a] = probability[a] / sum;
				}

				sum = 0;
				r = ((double)rand() / (RAND_MAX)); //losowanie z zakresu (0,1]

				for (int k = 0; k < n; k++)
				{
					sum += p[k];

					if (visibilityTemp[current][k] != 0 && r <= sum && k != current)
					{
						routes[i][j + 1] = k;

						break;
					}
				}
				routes[i][n] = routes[i][0];
			}
		}

		delete[] probability;
		for (int i = 0; i < n; i++)
			delete[] visibilityTemp[i];
		delete[] visibilityTemp;
		delete[] p;
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