#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "Block.h"
#include "interiorBlock.h"
using namespace std;

interior_block::interior_block()
{
	type = blockType::middle;
}

void interior_block::calculateForces()
{
	this->InternalForces();
}