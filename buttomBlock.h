#pragma once
#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "Block.h"
#include "connector.h"

using namespace std;

class buttom_block :public block
{
public:
	buttom_block();
	int numberOfConnectors = 1;
	double connectorInterval = blockd / numberOfConnectors;
	vector<shared_ptr<connector>> connectors;

	void connectConnectors();
	void calculateForces();
	bool returnState();

};