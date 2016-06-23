#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "Block.h"
#include "buttomLeftBlock.h"


using namespace std;

const int LblockHeight = 4;
const int LblockWidth = 4;
const int LnumBlocks = LblockHeight*LblockWidth;

double Ldt = 1e-7;

double Lk = 2.3e6; 			// Stiffness between blocks
double LL = 0.14; 			// Physical length of block chain
double Ld = LL / (LnumBlocks - 1); 	// Distance between blocks in block chain
double LM = 0.12;
double lm = LM / LnumBlocks;

buttomLeft_block::buttomLeft_block()
{
	type = blockType::buttomLeft;
}

void buttomLeft_block::calculateForces()
{
	this->InternalForces();
	this->xForce += pu->pusherForce(0, this->xPos);

	pu->MovePusher();
}