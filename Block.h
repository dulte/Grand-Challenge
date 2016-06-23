#pragma once
#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

using namespace std;
/*
const int blockHeight = 4;
const int blockWidth = 4;
const int numBlocks = blockHeight*blockWidth;

double dt = 1e-7;

double nu = sqrt(0.1e3);    //Dampning coefficient
double k = 2.3e6; 			// Stiffness between blocks
double L = 0.14; 			// Physical length of block chain
double d = L / (numBlocks - 1); 	// Distance between blocks in block chain
double M = 0.12;
double m = M / numBlocks;
*/
enum blockType
{
	buttom = 0,
	top = 1,
	leftWall = 2,
	rightWall = 3,
	middle = 4,
	buttomLeft = 5,
	buttomRight = 6,
	topLeft = 7,
	topRight = 8
};


class block
{
public:
	double xPos;
	double yPos;

	double xVel = 0;
	double yVel = 0;

	double xForce = 0;
	double yForce = 0;

	double springAttachmentPoint;

	blockType type;

	bool state = true;
	double timeMelted = 0;
	vector<shared_ptr<block>> neighbours;
	vector<double> neighbourSpringConst;

	int numberOfBlocks;
	double blockL;
	double blockM;

	double blockd; 	// Distance between blocks in block chain
	double blockm;

	int xID;
	int yID;

	block();

	void setData(double x, double y, const int numberOfBlocks_, double L_, double M_, int xID_, int yID_);
	void fillNeigbours(vector<vector<shared_ptr<block>>> &blocks);
	double springForce(double k, double d, double x, double y, int komponent);
	double dampningForce(double nu, double vx, double vy, int komponent);
	void InternalForces();
	void integrate();
	virtual void calculateForces();

	virtual bool returnState();

};