// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<array>
#include <memory>

#include "Block.h"
#include "interiorBlock.h"
#include "buttomBlock.h"
#include "buttomLeftBlock.h"

using namespace std;

const int blockHeight = 5; //Husk å bytte tilsvarende tall i block.cpp!!!!!!!!!!!!!!!
const int blockWidth = 5;
const int numBlocks = blockHeight*blockWidth;

double L = 0.14; 			// Physical length of block chain
double d = L / (blockWidth - 1); 	// Distance between blocks in block chain
double M = 0.12;

int writeFrequency = 10;

double ddt = 1e-7;
double tStop = 0.01; //orginalt 0.01
double t = 0;

//Some arrays
double positions[blockWidth];
double forces[blockWidth];
double state[blockWidth];

// Create output streams
ofstream outFilePositions("output/positions.bin", ios::out | ios::binary);
ofstream outFileForce("output/force.bin", ios::out | ios::binary);
ofstream outFileState("output/state.bin", ios::out | ios::binary);
ofstream outFileParameters("output/parameters.txt");

//Some functions
void writeArrayToFile(ofstream & outFile, double * array, int numBlocks);

/*
double dt = 1e-7;
double tStop = 0.01; //orginalt 0.01
double t = 0;

double vPusher = 4e-4;
double kPusher = 4e6;

double nu = sqrt(0.1e3);    //Dampning coefficient
double k = 2.3e6; 			// Stiffness between blocks
double L = 0.14; 			// Physical length of block chain
double d = L / (numBlocks - 1); 	// Distance between blocks in block chain
double M = 0.12;
double m = M / numBlocks;
*/

int main()
{
	vector<vector<shared_ptr<block>>> blocks;

	blocks.resize(blockWidth);

	for (int m = 0; m < blockWidth; m++)
	{
		blocks[m].resize(blockHeight);
	}

	for (int i = 0; i < blockHeight; i++)
	{
		for (int j = 0; j < blockWidth; j++)
		{

			if ((j > 0 && j < blockWidth - 1) && (i > 0 && i < blockHeight - 1))
			{
				blocks[i][j] = shared_ptr<block>(new interior_block);

				blocks[i][j]->setData(j*d, i*d, blockWidth, L, M,j,i);
				

			}
			else if (i == 0 && j == 0)
			{
				blocks[i][j] = shared_ptr<block>(new buttomLeft_block);


				blocks[i][j]->setData(j*d, i*d, blockWidth, L, M,j,i);
			}
			else
			{
				blocks[i][j] = shared_ptr<block>(new buttom_block);


				blocks[i][j]->setData(j*d, i*d, blockWidth, L, M,j,i);
			}
			
		}

		
	}

	for (int i = 0; i < blockHeight; i++)
	{ 
		for (int j = 0; j < blockWidth; j++)
		{ 
			blocks[i][j]->fillNeigbours(blocks);
		}
	}

	int counter = 0;

	cout << blocks[0][0]->xPos << "   " << blocks[0][0]->xForce << endl;
	cout << blocks[0][1]->xPos << "   " << blocks[0][1]->xForce << endl;
	cout << blocks[0][2]->xPos << "   " << blocks[0][2]->xForce << endl;
	cout << blocks[0][blockWidth - 2]->xPos << "   " << blocks[0][blockWidth - 2]->xForce << endl;
	cout << blocks[0][blockWidth - 1]->xPos << "   " << blocks[0][blockWidth - 1]->xForce << endl;
	cout << endl;

	while (t<tStop)
	{
		for (int i = 0; i < blockHeight; i++)
		{
			for (int j = 0; j < blockWidth; j++)
			{
				blocks[i][j]->calculateForces();

			}
		}

		for (int i = 0; i < blockHeight; i++)
		{
			for (int j = 0; j < blockWidth; j++)
			{
				blocks[i][j]->integrate();

			}
		}



		for (int j = 0; j < blockWidth; j++)
		{
			positions[j] = blocks[0][j]->xPos;
			forces[j] = blocks[0][j]->xForce;
			if (blocks[0][j]->type == blockType::buttom)
			{
				state[j] = int(blocks[0][j]->returnState());
			}

		}

		if ((counter%writeFrequency) == 0)
		{
			writeArrayToFile(outFilePositions, positions, blockWidth);
			writeArrayToFile(outFileForce, forces, blockWidth);
			writeArrayToFile(outFileState, state, blockWidth);
		}

		counter++;
		t += ddt;

	}

	// Output parameters to file
	outFileParameters << "nx " << blockWidth << "\n";
	outFileParameters << "dt " << ddt << "\n";
	// .. fill in the rest of the parameters

	// Close output files
	outFilePositions.close();
	outFileParameters.close();
	outFileForce.close();



	
	cout << blocks[0][0]->xPos <<"   "<< blocks[0][0]->xForce << endl;
	cout << blocks[0][1]->xPos << "   " << blocks[0][1]->xForce << endl;
	cout << blocks[0][2]->xPos << "   " << blocks[0][2]->xForce << endl;
	cout << blocks[0][blockWidth - 2]->xPos << "   " << blocks[0][blockWidth - 2]->xForce << endl;
	cout << blocks[0][blockWidth-1]->xPos << "   " << blocks[0][blockWidth - 1]->xForce << endl;


	cout << d << endl;

    return 0;
}



void writeArrayToFile(ofstream & outFile, double * array, int numBlocks)
{
	outFile.write(reinterpret_cast<char*>(array), numBlocks*sizeof(double));
}

