#pragma once
#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "Block.h"
#include "pusher.h"

using namespace std;

class buttomLeft_block :public block
{
public:
	double pusherPosition;
	pusher *pu = new pusher();

	buttomLeft_block();
	void calculateForces();
	//double pusherForce(double kPusher, int komponent);
	//void MovePusher();

	
};