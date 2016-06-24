#ifndef CONNECTOR_H
#define CONNECTOR_H


#pragma once
//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct connector
{
public:

    //These variables will be read from config
	double timeMelted = 0; //Tiden connectoren har vaert smelted
	double timeToStick = 0.0002; //Tiden det tar foer connectoren fester seg igjen
	bool state = true; //Om connectoren er festet eller ikke
	double randomEpsilon = (rand() % 100) / (1e-5); //En lite, tilfeldig varianse til tiden det tar connectoren aa feste seg igjen
	double d = 0.0001; //Likevektslengde til connectoren

	double connectorPos;
	double connectorVel = 0;
	double connectorForce = 0;
	double connectorHeight = d/2;

	double connectorMass = 0.1;

	double f_ni = 500;//1920. / 70.;
	double connectorSpringConst = sqrt((39.2e9)*(f_ni));

	double connStaticFricCoeff = 0.4;
	double connDynamicFricCoef = 0.17;

	double connectorDt;



	int sign(double v);


	connector(double x, double dt);

	double calulateConnectorForce(double x, double y, double vx);
	double returnedForce(double x, double y, double vx);
	void inegrateConnector(double force);
};

#endif // CONNECTOR_H
