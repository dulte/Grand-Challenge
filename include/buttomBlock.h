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
	int numberOfConnectors = 1;
	double connectorInterval = d / numberOfConnectors;
	vector<shared_ptr<connector>> connectors;

	void connectConnectors();
	void calculateForces();
	bool returnState();

};
