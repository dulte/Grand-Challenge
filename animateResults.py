# -*- coding: utf-8 -*-
"""
Created on Tue Jun 28 23:30:03 2016

@author: Daniel
"""
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
                
    def makeArray(self,filename):
        
        rawData = open(filename, "r")
        data = []
        holder = []
        
        for line in rawData:
            w = line.split()
            if float(w[0]) == 666:
                data.append(np.array(holder))
                holder = []
            else:
                holder.append(w)
        
        self.dataArray = np.array(data)
        
    def arraycolorplot(self, i):
        tempArray = np.copy(self.dataArray[i])
        nt = len(tempArray)/self.nx;
        tempArray.resize(nt, self.nx)
        plt.pcolormesh(tempArray)
        plt.show()
       
        

if __name__=="__main__":
    filenameParameters = "output/parameters.txt"
    filenamePositions = "output/xpos.txt"
    anima = FrictionAnalyser(filenameParameters)
    anima.makeArray(filenamePositions)
    anima.arraycolorplot(0)
        