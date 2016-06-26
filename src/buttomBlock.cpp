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

	//this->connectConnectors();
}

void buttom_block::connectConnectors()
{
    //Makes a given number of connectors per block
	for (int i = 1; i <= numberOfConnectors; i++)
	{
		double pos = this->xPos;// + i*connectorInterval;
		this->connectors.push_back(shared_ptr<connector>(new connector(pos, dt,oneDim)));

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
		yForce += normalForce();

		fricForce = connect->calulateConnectorForce(this->xPos, this->yPos, this->xVel, this->normalForce());
		xForce += fricForce;
		//cout << connect->calulateConnectorForce(this->xPos, this->yPos, this->xVel) << endl;
	}
}

bool buttom_block::returnState()
{
	return connectors[0]->state;
}

double buttom_block::returnFricForce()
{
    return this->fricForce;
}

double buttom_block::normalForce()
{
    if (this->yPos<0)
    {
        return -normalForceSpringCoeff*this->yPos;
    }
    else{return 0;}
}

void buttom_block::isOneDim(bool _oneDim)
{
    oneDim = _oneDim;
}

