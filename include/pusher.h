#ifndef PUSHER_H
#define PUSHER_H


//#include "stdafx.h"
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
	double vPusher;// = 4e-4;
	double kPusher;// = 4e6;

    double pusherEqD;

	double dt;// = 1e-7;

	double pusherPosition;

	pusher();

	double pusherForce(int komponent, double x);

	void MovePusher();


};

#endif

#endif // PUSHER_H
