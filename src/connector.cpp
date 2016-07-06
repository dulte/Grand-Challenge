//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include <cmath>

#include "getVar.h"
#include "connector.h"

using namespace std;

connector::connector(double x, double dt, bool isOneDim)
{
	connectorPos = x; //Vestigial, and will be changed
    timeToStick += randomEpsilon;

    useNormalForce = isOneDim;

	getVar *connVarGet = new getVar();

	timeToStick = connVarGet->get("stickTime");

	connectorMass = connVarGet->get("connMass");
	connStaticFricCoeff = connVarGet->get("staticCoeff");
	connDynamicFricCoef = connVarGet->get("dynamicCoeff");
    connectorDt = connVarGet->get("dt");

    f_ni = connVarGet->get("N");
    connectorSpringConst = sqrt((39.2e9)*(f_ni));

    delete connVarGet;

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

double connector::calulateConnectorForce(double x, double y, double vx, double fy)
{
    double normalForce = 0;

    if (useNormalForce)
    {
        normalForce = f_ni;
    }
    else
    {

        normalForce = fy;
    }
    //double lenght = sqrt(pow(x-connectorPos,2) + pow(connectorHeight-y,2));

    double deltaX = x-connectorPos;
    double k = sqrt(39.2e9*normalForce); //Dele paa antall connectorer inne i sqrt
    double springForce = -k*deltaX; //connectorSpringConst*deltaX*(d-lenght)/lenght;
    double dynamicForce = -connDynamicFricCoef*normalForce*sign(vx);


    if(state)
    {
        if (abs(springForce) < connStaticFricCoeff*normalForce) //om du faar feil her igen, saa har du nok byttet ut connStaticFricCoeff med connectorSpringConst, som du pleier...
        {
            return springForce;
        }
        else
        {

            state = false;
            return dynamicForce;
        }
    }
    else
    {
        if(timeMelted<timeToStick)
        {
            timeMelted += connectorDt;
            this->inegrateConnector(dynamicForce);
            return dynamicForce;
        }
        else
        {
            timeMelted = 0;
            connectorPos = x;
            state = true;
            return springForce;
        }
    }


}

double connector::returnedForce(double x, double y, double vx, double fy)
{
	double lenght = sqrt(pow(x-connectorPos,2) + pow(connectorHeight-y,2));

	if (lenght < d)
	{
		return 0;

	}
	else
	{
		return this->calulateConnectorForce(x, y, vx, fy);;
	}

}

void connector::inegrateConnector(double force)
{
	connectorVel += force / connectorMass*connectorDt;
	connectorPos += connectorVel*connectorDt;
}
