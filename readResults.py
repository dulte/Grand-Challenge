# -*- coding: utf-8 -*-
"""
Created on Fri Apr 08 11:17:04 2016

@author: Daniel
"""

# Read binary file
import numpy as np
import matplotlib.pyplot as plt






class FrictionAnalyser:
    def __init__(self, parameterFileName):
        self.parameterFileName = parameterFileName
        self.readParameters()


    def readParameters(self):
        ifile = open(self.parameterFileName, "r")
        fileContents = ifile.readlines()
        for line in fileContents:
            words = line.split()
            if words[0] == "nx":
                self.nx = float(words[1])
            if words[0] == "dt":
                self.dt = float(words[1])
            # TODO: get more parameters from parameter file


    def velPlotter(self, filename, plotname = ""):
        velData = np.fromfile(filename)
        nt = len(velData)/self.nx;
        velData.resize(nt, self.nx)

        plt.pcolormesh(velData)
        plt.title(plotname)
        plt.xlabel('Block index')
        plt.ylabel('Time step')
        plt.colorbar()
        if plotname != "":
            plt.savefig(plotname + ".png")
        plt.show()



    def pcolorplot(self, spaceTimeFile, plotname = ""):
        spaceTimeData = np.fromfile(spaceTimeFile)
        nt = len(spaceTimeData)/self.nx;
        spaceTimeData.resize(nt, self.nx)

        #plt.figure(figsize=(20,15))

        plt.pcolormesh(spaceTimeData-spaceTimeData[0])
        plt.title(plotname)
        plt.xlabel('Block index')
        plt.ylabel('Time step')
        plt.colorbar()
        if plotname != "":
            plt.savefig(plotname + ".png")
        plt.show()

def plotPusher(filename, plotname = ""):
    data = np.fromfile(filename)
    plt.title(plotname)
    plt.xlabel("Time step")
    plt.ylabel("Force")
    plt.plot(data)
    if plotname != "":
            plt.savefig(plotname + ".png")
    plt.show()
    

if __name__=="__main__":
    filenameParameters = "output/parameters.txt"
    filenamePositions = "output/positions.bin"
    analyser = FrictionAnalyser(filenameParameters)
    analyser.pcolorplot(filenamePositions, "Position")
    spring = FrictionAnalyser(filenameParameters)
    spring.velPlotter("output/state.bin", "Are the springs attached to the ground")
    force = FrictionAnalyser(filenameParameters)
    force.velPlotter("output/friction.bin", "Friction force")
    velocity = FrictionAnalyser(filenameParameters)
    velocity.velPlotter("output/velocity.bin", "Velocity")
    
    plotPusher("output/pusher.bin", "Force on Pusher")
    
