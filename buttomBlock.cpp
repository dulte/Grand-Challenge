#include "buttomBlock.h"

//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "block.h"
#include "buttomBlock.h"
using namespace std;

const int BblockHeight = 4;
const int BblockWidth = 4;
const int BnumBlocks = BblockHeight*BblockWidth;

double Bdt = 1e-7;

double Bk = 2.3e6; 			// Stiffness between blocks
double BL = 0.14; 			// Physical length of block chain
double Bd = BL / (BnumBlocks - 1); 	// Distance between blocks in block chain
double BM = 0.12;
double Bm = BM / BnumBlocks;

buttom_block::buttom_block()
{
	type = blockType::buttom;
	this->connectConnectors();
}

void buttom_block::connectConnectors()
{
	for (int i = 1; i <= numberOfConnectors; i++)
	{
		double pos = this->xPos + i*connectorInterval;
		this->connectors.push_back(shared_ptr<connector>(new connector(pos, Bdt)));
	}
}

void buttom_block::calculateForces()
{
	this->InternalForces();
	for (shared_ptr<connector> connect : connectors)
	{
		//this->xForce += connect->returnedForce(this->xPos,this->yPos,this->xVel);
		//cout << connect->returnedForce(this->xPos, this->yPos, this->xVel) << endl;

		//cout << this->xPos << endl;
		//xForce += connect->calulateConnectorForce(this->xPos, this->yPos, this->xVel);
		//cout << connect->calulateConnectorForce(this->xPos, this->yPos, this->xVel) << endl;
	}
}

bool buttom_block::returnState()
{
	return connectors[0]->state;
}

