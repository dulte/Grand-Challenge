#ifndef BUTTOMLEFTBLOCK_H
#define BUTTOMLEFTBLOCK_H


#pragma once
//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "block.h"
#include "pusher.h"

using namespace std;

class buttomLeft_block :public block
{
public:
	double pusherPosition;
	pusher *pusherObj = new pusher();

	buttomLeft_block();
	void calculateForces();
	//double pusherForce(double kPusher, int komponent);
	//void MovePusher();


};

#endif // BUTTOMLEFTBLOCK_H
