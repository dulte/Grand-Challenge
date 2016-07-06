#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <time.h>
#include <assert.h>

#include "block.h"
#include "interiorBlock.h"
#include "buttomBlock.h"
#include "buttomLeftBlock.h"
#include "topBlock.h"
#include "getVar.h"

using namespace std;

// Create output streams
ofstream outFilePositions("output/positions.bin", ios::out | ios::binary);
ofstream outFileForce("output/force.bin", ios::out | ios::binary);
ofstream outFileState("output/state.bin", ios::out | ios::binary);
ofstream outFileFriction("output/friction.bin", ios::out | ios::binary);
ofstream outFileVelocity("output/velocity.bin", ios::out | ios::binary);
ofstream outFilePusher("output/pusher.bin", ios::out | ios::binary);
ofstream outFileParameters("output/parameters.txt");

//Some functions
void writeArrayToFile(ofstream & outFile, double * array, int numBlocks);
int checkProgress(double time, double tStop, int percent, double currentTime, double start);
vector<vector<int>> getLayaout(int height, int width);




int main()
{
    //Reads variables from config-file:
    getVar *pGetVarMain = new getVar();

    const int blockHeight = int(pGetVarMain->get("height"));
    const int blockWidth = int(pGetVarMain->get("width"));
    const int numBlocks = blockHeight*blockWidth;

    double L = pGetVarMain->get("L");
    double d = L / (blockWidth - 1);

    int writeFrequency = int(pGetVarMain->get("writeFrequency"));

    double dt = pGetVarMain->get("dt");
    double tStop = pGetVarMain->get("tStop"); //orginalt 0.01
    double t = 0;

    //Some variables used for fun things
    time_t timer;
    int percent = 0;
    bool isTesting = (pGetVarMain->get("test"));
    int testTime = 10;

    bool isOneDim = false;
    if (blockHeight == 1){isOneDim = true;} //Checks if the block is only 1 block high(to make sure blocks are not top and bottom)


    //vector<vector<int>> layout;
    //layout = getLayaout(blockHeight,blockWidth);


    delete pGetVarMain; //Closes the files

    //Some arrays
    double positions[blockWidth];
    double forces[blockWidth];
    double state[blockWidth];
    double friction[blockWidth];
    double velocity[blockWidth];
    //double pusherForce[100000];
    vector<double> pusherForce;





    //Makes the 2D-vector that holds the block-objects

    cout << "Beginning initialization" << endl;

	vector<vector<shared_ptr<block>>> blocks;

	blocks.resize(blockHeight);

	for (int m = 0; m < blockHeight; m++)
	{
		blocks[m].resize(blockWidth);
	}



	for (int i = 0; i < blockHeight; i++)
	{
		for (int j = 0; j < blockWidth; j++)
		{
		    if ((i == (blockHeight - 1)) && !isOneDim)
            {

                blocks[i][j] = shared_ptr<block>(new top_block);
                blocks[i][j]->setData(j*d, i*d,j,i);


            }
            else if (i == 0)
            {
                if (j == 0)
                {
                     blocks[i][j] = shared_ptr<block>(new buttomLeft_block);


                     blocks[i][j]->setData(j*d, i*d,j,i);
                     blocks[i][j]->isOneDim(isOneDim);
                     blocks[i][j]->connectConnectors();


                }
                else
                {
                     blocks[i][j] = shared_ptr<block>(new buttom_block);


                     blocks[i][j]->setData(j*d, i*d,j,i);
                     blocks[i][j]->isOneDim(isOneDim);
                     blocks[i][j]->connectConnectors();


                }
            }
            else
            {
                blocks[i][j] = shared_ptr<block>(new interior_block);

				blocks[i][j]->setData(j*d, i*d,j,i);
            }

            /*
			if ((j > 0 && j < blockWidth - 1) && (i > 0 && i < blockHeight - 1))
			{
				blocks[i][j] = shared_ptr<block>(new interior_block);

				blocks[i][j]->setData(j*d, i*d,j,i);


			}
			else if (i == (blockHeight - 2))
            {
                if (!isOneDim)
                {
                    blocks[i][j] = shared_ptr<block>(new top_block);
                    blocks[i][j]->setData(j*d, i*d,j,i);
                }
            }
			else if (i == 0 && j == 0)
			{
				blocks[i][j] = shared_ptr<block>(new buttomLeft_block);


				blocks[i][j]->setData(j*d, i*d,j,i);
				blocks[i][j]->connectConnectors();
			}
			else
			{
				blocks[i][j] = shared_ptr<block>(new buttom_block);


				blocks[i][j]->setData(j*d, i*d,j,i);
				blocks[i][j]->connectConnectors();
			}

            */
		}


	}


	//Gives all the blocks lists over their neighbors(will be optimized)

	for (int i = 0; i < blockHeight; i++)
	{
		for (int j = 0; j < blockWidth; j++)
		{
			blocks[i][j]->fillNeigbours(blocks);
		}
	}



    //Main integration loop

    cout << "Beginning calculations" << endl;

    double timeStarted = time(&timer);
    int counter = 0;

	while (t<tStop)
	{

        //For testing and showing progression, comment out for somewhat faster running time
	    if (isTesting)
        {
            if(int(time(&timer)-timeStarted)>=testTime){
                cout << "I am estimating it will take approximately " << int(double(time(&timer)-timeStarted)/(t/tStop)) << " Sec" << endl << "Test ended" << endl;;
                break;
            }
        }
        else{
            percent = checkProgress(t, tStop, percent, time(&timer), timeStarted); // Prints the progression
        }


		for (int i = 0; i < blockHeight; i++)
		{
			for (int j = 0; j < blockWidth; j++)
			{

				blocks[i][j]->calculateForces();

			}
		}

        //Integrates (For now using Euler-Cromer, will be changed)
		for (int i = 0; i < blockHeight; i++)
		{
			for (int j = 0; j < blockWidth; j++)
			{
				blocks[i][j]->integrate();



			}

		}


        //Makes an array which holds the whether or not the springs are attached and static friction is active
		for (int j = 0; j < blockWidth; j++)
		{
			positions[j] = blocks[0][j]->xPos;
			forces[j] = blocks[0][j]->normalForce();//yForce;  //Change back to x!
			velocity[j] = blocks[0][j]->xVel;
			state[j] = int(blocks[0][j]->returnState());
			if ((blocks[0][j]->returnFricForce())>-0.005){
                    friction[j] = blocks[0][j]->returnFricForce();
				}
				else{friction[j] = -0.005;}

		}

        //Writes the data to files
		if ((counter%writeFrequency) == 0)
		{

            //cout << blocks[0][0]->returnPusherForce() << endl;
            pusherForce.push_back(blocks[0][0]->returnPusherForce());


			writeArrayToFile(outFilePositions, positions, blockWidth);
			writeArrayToFile(outFileForce, forces, blockWidth);
			writeArrayToFile(outFileState, state, blockWidth);
			writeArrayToFile(outFileFriction,friction,blockWidth);
			writeArrayToFile(outFileVelocity,velocity,blockWidth);
		}

		counter++;
		t += dt;

	}

	double pusherArray[int(pusherForce.size())];
	for (int k = 0; k < pusherForce.size();k++)
    {
        pusherArray[k] = pusherForce[k];
    }

    writeArrayToFile(outFilePusher, pusherArray, int(pusherForce.size()));
	// Output parameters to file
	outFileParameters << "nx " << blockWidth << "\n";
	outFileParameters << "dt " << dt << "\n";
	// .. fill in the rest of the parameters

	// Close output files
	outFilePositions.close();
	outFileParameters.close();
	outFileForce.close();
	outFileState.close();
	outFileFriction.close();
	outFileVelocity.close();
	outFilePositions.close();
	outFilePusher.close();





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

int checkProgress(double time, double tStop, int percent,double curretenTime, double start)
{
    if (int((time/tStop)*100)%10 == 0 && int((time/tStop)*100) != percent  ){
            cout << int((time/tStop)*100) << "% done| " << curretenTime- start << " Sec used| estimated " << round((curretenTime - start)/(time/tStop) - (curretenTime - start)) << " Sec left" << endl;
            return int((time/tStop)*100);
    }

}



vector<vector<int>> getLayaout(int height,int width)
{
    int row;
    int col;
    string num;

    ifstream inFileLayout("input/layout.txt"); //, ios::in| ios::binary);

    vector<vector<int>> init;



	init.resize(height);

	for (int m = 0; m < height; m++)
	{
		init[m].resize(width);
	}


    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {

            inFileLayout >> num;
            init[i][j] = stoi(num);
        }
    }

    inFileLayout.close();

    return init;
}
