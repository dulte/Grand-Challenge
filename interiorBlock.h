#pragma once
#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "Block.h"

using namespace std;

class interior_block:public block
{
public:
	interior_block();
	void calculateForces();
};

