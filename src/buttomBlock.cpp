#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "block.h"
#include "buttomBlock.h"


using namespace std;


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
		this->connectors.push_back(shared_ptr<connector>(new connector(pos, dt)));
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

