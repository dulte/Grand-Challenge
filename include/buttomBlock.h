//#ifndef BUTTOMBLOCK_H
//#define BUTTOMBLOCK_H

#pragma once
//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "block.h"
#include "connector.h"

using namespace std;

class buttom_block :public block
{
public:
	buttom_block();
	int numberOfConnectors = 10;
	double fricForce = 0;
	double normalForceSpringCoeff = 5e10;
	double connectorInterval = d / numberOfConnectors;
	bool oneDim =true;

	vector<shared_ptr<connector>> connectors;

	void connectConnectors();
	void calculateForces();
	bool returnState();
	double returnFricForce();
	double normalForce();

	void isOneDim(bool _oneDim);

};
