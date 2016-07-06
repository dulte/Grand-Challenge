#include "block.h"
//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>
#include <cmath>
#include <algorithm>
#include "getVar.h"

using namespace std;



	block::block(){


	    //retrieves the variables this class needs
        getVar *pGetVar = new getVar();

        blockHeight = int(pGetVar->get("height"));
        blockWidth = int(pGetVar->get("width"));
        numberOfBlocks = blockWidth*blockHeight;



        k = pGetVar->get("k");
        //nu = pGetVar->get("nu");
        dt = pGetVar->get("dt");

        L = pGetVar->get("L");
        M = pGetVar->get("M");

        d = L / (blockWidth - 1); 	// Distance between blocks in block chain
		m = M / numberOfBlocks;

        nu = sqrt(0.1*k*m);

        delete pGetVar; //By deleting this pointer the destructor should close the files

	};
	bool block::returnState() { return false; };
	void block::connectConnectors(){};
	double block::returnFricForce(){return 0;};
	void block::isOneDim(bool _oneDim){};
	double block::normalForce(){return 0;}
	double block::returnPusherForce(){return 0;}



	double lenght(double x1, double y1, double x2, double y2)
	{
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	//block(const block&) = default;

	void block::setData(double x, double y,int xID_, int yID_)
	{
		xPos = x;
		yPos = y;
		springAttachmentPoint = x;

		xID = xID_;
		yID = yID_;
	}

	void block::fillNeigbours(vector<vector<shared_ptr<block>>> &blocks)
	{

		for (int m = int(yID) - 1; m <= int(yID) + 1; m++)
		{
			for (int n = int(xID) - 1; n <= int(xID) + 1; n++)
			{
				if (((m == this->yID) && (n == this->xID)))
				{
				}
				else
				{

					if ((m >= 0 && m <= blockHeight -1) && (n >= 0 && n <= blockWidth -1))
					{

						neighbours.push_back(blocks[m][n]);

						double len = lenght(xID, yID, blocks[m][n]->xID, blocks[m][n]->yID);
						if (len > 0.998 && len < 1.002)
						{
							neighbourSpringConst.push_back(1.0);

						}
						else
						{
							neighbourSpringConst.push_back(0.5);
						}
					}

				}

			}

		}


	}



	double block::springForce(double k, double d, double x, double y, int komponent)
	{
		double deltaX = x - xPos;
		double deltaY = y - yPos;
		double len = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
		if (komponent == 0)
		{
			return k*(len - d)*(deltaX) / len;
		}
		else if (komponent == 1)
		{
			return k*(len - d)*deltaY / len;
		}

	}

	double block::dampningForce(double nu, double vx, double vy, int komponent)
	{


		double deltaX = vx - xVel;
		double deltaY = vy - yVel;

		double len = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
		if (len > 0) {
			if (komponent == 0)
			{
				return -nu*(deltaX);
			}
			else if (komponent == 1)
			{
				return -nu*(deltaY);
			}
		}
		else { return 0; }
	}

	void block::InternalForces()
	{
		xForce = 0;
		yForce = 0;
		int i = 0;
		for (shared_ptr<block> neigbour : neighbours)
		{
			double k_ = neighbourSpringConst[i] * k;
			double nu_ = neighbourSpringConst[i] * nu;
			double eps = 0.05;
			double d_;

			if (abs(neighbourSpringConst[i] - 0.5) < eps)
			{
				d_ = sqrt(2)*d;
			}
			else
			{
				d_ = d;
			}

			xForce += springForce(k_, d_, neigbour->xPos, neigbour->yPos, 0)-dampningForce(nu_, neigbour->xVel, neigbour->yVel, 0);
			yForce += springForce(k_, d_, neigbour->xPos, neigbour->yPos, 1) -dampningForce(nu_, neigbour->xVel, neigbour->yVel, 1);
			i++;

		}
	};

	void block::integrate()
	{
		xVel += xForce / m*dt;
		xPos += xVel*dt;

		yVel += yForce / m*dt;
		yPos += yVel*dt;
	};

	void block::calculateForces() {};


