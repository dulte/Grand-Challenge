//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>
#include<math.h>
#include <cmath>

#include "connector.h"

using namespace std;

connector::connector(double x, double dt)
{
	connectorPos = x; //Vestigial, and will be changed
	connectorDt = dt;
	//timeToStick += randomEpsilon;
}

int connector::sign(double v)
{
	if (v < 0)
	{
		return -1;
	}
	else if (v>0)
	{
		return 1;
	}
	else { return 0; }
}

double connector::calulateConnectorForce(double x, double y, double vx)
{

	double lenght = sqrt(pow(x - connectorPos, 2) + pow(y - connectorHeight, 2));

	double deltaX = connectorPos - x;

    //spring force is now calculated with deltaX, this is a naive model and will be the first thing to be changed
	double springForce = connectorSpringConst*(deltaX);//connectorSpringConst*deltaX*(lenght - d) / lenght;

	double dynamicForce = -connDynamicFricCoef*f_ni*sign(vx);

    //return dynamicForce;

	if (state)
	{
		if (abs(springForce) < connStaticFricCoeff*f_ni)
		{
			return springForce;
		}
		else
		{
			//state = true;
			state = false;
			//cout << "hei" << " " << dynamicForce << endl;
			return dynamicForce;
		}
	}
	else if (!state)
	{
		if (timeMelted < timeToStick)
		{
			timeMelted += connectorDt;
			//connectorPos = x;
			return dynamicForce;
		}
		else
		{
			connectorPos = x;
			timeMelted = 0;

			state = true;
			return springForce;
		}
	}
}

double connector::returnedForce(double x, double y, double vx)
{
	double deltaX = connectorPos - x;



	double force = this->calulateConnectorForce(x, y, vx);


	if (deltaX < d)
	{
		//return 0;
		inegrateConnector(force);
		return force;
	}
	else
	{
		inegrateConnector(force);
		return force;
	}

}

void connector::inegrateConnector(double force)
{
	connectorVel += force / connectorMass*connectorDt;
	connectorPos += connectorVel*connectorDt;
}
