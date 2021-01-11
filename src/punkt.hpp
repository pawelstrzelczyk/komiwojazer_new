#pragma once
#include <queue>
class punkt
{
public:
	class pkt
	{
	private:
		double x;
		double y;
		int id;

	public:
		bool flag = false;
		void setX(double X)
		{
			this->x = X;
		}
		void setY(double Y)
		{
			this->y = Y;
		}
		void setId(int id)
		{
			this->id = id;
		}
		int getX()
		{
			return this->x;
		}
		int getY()
		{
			return this->y;
		}
		int getId()
		{
			return this->id;
		}
	};
	double square(double a)
	{
		return a * a;
	}

	double odleglosc(pkt a, pkt b)
	{
		return sqrt(square(double(a.getY()) - double(b.getY())) + square(double(a.getX()) - double(b.getX())));
	}
};
