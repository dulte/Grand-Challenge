#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "pusher.h"

using namespace std;


pusher::pusher()
{
	pusherPosition = 0;
}

double pusher::pusherForce(int komponent, double x)
{

	double pForce = kPusher*(pusherPosition - x);
	return pForce;
}

void pusher::MovePusher()
{
	pusherPosition += vPusher*Pdt;
}