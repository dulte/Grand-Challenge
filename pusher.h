#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#ifndef pusher
#define puher



struct pusher
{
public:
	double vPusher = 4e-3;
	double kPusher = 4e6;

	double Pdt = 1e-7;

	double pusherPosition;

	pusher();

	double pusherForce(int komponent, double x);

	void MovePusher();


};

#endif