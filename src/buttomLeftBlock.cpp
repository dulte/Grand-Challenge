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
	this->xForce += pusherObj->pusherForce(0, this->xPos);
    for (shared_ptr<connector> connect : connectors)
	{
        fricForce = connect->calulateConnectorForce(this->xPos, this->yPos, this->xVel);
		xForce += fricForce;
	}
	pusherObj->MovePusher();
}

