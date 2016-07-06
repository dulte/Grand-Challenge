//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "block.h"
#include "buttomLeftBlock.h"


using namespace std;

buttomLeft_block::buttomLeft_block()
{
	type = blockType::buttomLeft;
}

void buttomLeft_block::calculateForces()
{
	this->InternalForces();
	pusherForce = pusherObj->pusherForce(0, this->xPos);
	this->xForce += pusherForce;
	yForce += normalForce();
    for (shared_ptr<connector> connect : connectors)
	{

        fricForce = connect->calulateConnectorForce(this->xPos, this->yPos, this->xVel, this->normalForce());
		xForce += fricForce;
	}
	pusherObj->MovePusher();
}

double buttomLeft_block::returnPusherForce()
{
    return pusherObj->pusherForce(0, this->xPos);
}
