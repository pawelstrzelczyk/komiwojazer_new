#pragma once
using namespace std;
#include "punkt.hpp"
punkt point;
class TSP
{
public:
	void komiwojazer(int n, punkt::pkt tab[], queue<punkt::pkt>& Q)
	{
		double calaodleglosc = 0;
		punkt::pkt min_pkt = tab[0];
		tab[0].flag = false;
		for (int i = 1; i < n; i++)
		{
			double min = 1000000000;
			double aktualnaOdleglosc = 1000000000;
			int v = 0;

			for (int j = 1; j < n; j++)
			{
				if (tab[j].flag == false)
					aktualnaOdleglosc = point.odleglosc(min_pkt, tab[j]);

				if (aktualnaOdleglosc < min && tab[j].flag == false)
				{
					min = aktualnaOdleglosc;
					cout << min << " ";
					min_pkt = tab[j];
					v = j;
				}
			}
			cout << endl;
			calaodleglosc += min;

			tab[v].flag = true;
			Q.push(min_pkt);
		}
		Q.push(tab[0]);
		cout << endl
			 << "Calkowita odleglosc: " << calaodleglosc << endl;
	}
};