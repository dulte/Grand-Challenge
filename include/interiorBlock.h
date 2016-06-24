#ifndef INTERIORBLOCK_H
#define INTERIORBLOCK_H


#pragma once
//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "block.h"

using namespace std;

class interior_block:public block
{
public:
	interior_block();
	void calculateForces();
};



#endif // INTERIORBLOCK_H
