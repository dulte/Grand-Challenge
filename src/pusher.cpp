//#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "pusher.h"
#include "getVar.h"

using namespace std;


pusher::pusher()
{
    getVar *pGetVarPusher = new getVar();

    vPusher = pGetVarPusher->get("vPusher");
    kPusher = pGetVarPusher->get("kPusher");
    dt = pGetVarPusher->get("dt");

	pusherPosition = -0.01;
	pusherEqD = -pusherPosition;

	delete pGetVarPusher;
}

double pusher::pusherForce(int komponent, double x)
{

	double pForce = -kPusher*((x-pusherPosition) - pusherEqD);

	return pForce;
}

void pusher::MovePusher()
{
	pusherPosition += vPusher*dt;
}
