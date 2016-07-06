# -*- coding: utf-8 -*-
"""
Created on Mon Jun 27 18:44:08 2016

@author: Daniel
"""

import pygame
import numpy as np
import sys

pygame.init()
clock = pygame.time.Clock()

#Var for basic game flow:
done = False
WINDOWWIDTH = 800
WINDOWHEIGHT = 400

gridSize = 600


blocksHorizontal = 51
blocksVertical = 37

sqSize = gridSize/blocksHorizontal

screen_size = (WINDOWWIDTH,WINDOWHEIGHT)
screen = pygame.display.set_mode(screen_size)
myfont = pygame.font.SysFont("monospace", 15)
pygame.display.set_caption("Layout")



#Div Var:

WHITE     = (255, 255, 255)
BLACK     = (  0,   0,   0)
RED       = (255,   0,   0)
GREEN     = (  0, 255,   0)
YELLOW    = (255, 255,   0)
ORANGE    = (255, 165,   0)
DARKGREEN = (  0, 155,   0)
DARKGRAY  = ( 40,  40,  40)




def main():
    #init
    done = False
    grid = makeGrid(blocksHorizontal,blocksVertical)
    
   
    coordGrid = makeCoordGrid(grid, blocksHorizontal,blocksVertical)
       
    
    sqType = 0
    drawType = 0
    
    
    gameLoop(done, grid, coordGrid,sqType,drawType)#done, board, plays, mouse_over_square, whosTurn)
        
def gameLoop(done, grid, coordGrid,sqType,drawType):#done, board, plays, mouse_over_square, whosTurn):
    
  
    while not done:
        
        screen.fill(BLACK)
        #mouse_over_square = returnSquare()
        mousex,mousey = pygame.mouse.get_pos()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    writeToFile(grid)
                if event.key == pygame.K_RIGHT:
                    drawType = (drawType+1)%3
                if event.key == pygame.K_LEFT:
                    sqType = (sqType+1)%5
            if event.type == pygame.MOUSEBUTTONDOWN:
                updateGrid(grid,coordGrid,mousex,mousey,sqType,drawType)
        
        if pygame.mouse.get_pressed()[0]:
            updateGrid(grid,coordGrid,mousex,mousey,sqType,drawType)
               
        

        fillGrid(grid,coordGrid)
        
        color = returnColor(sqType)
        sqX,sqY = returnSquare(coordGrid,mousex,mousey)
        drawSqOnPointer(coordGrid,sqX,sqY, color,drawType)        
        
        
        drawGrid(grid,coordGrid)
        drawButtons(sqType)
      
        pygame.display.flip()
        
        clock.tick(60)      
    else:
        pygame.quit()
        sys.exit()
   
   
   
   
   
   
   
   
    
def makeGrid(bHor,bVer):
    grid = [[1 for i in range(bVer)] for j in range(bHor)]
    return grid
  

  
def drawGrid(grid,coordGrid):
    for i in range(len(coordGrid)):
        pygame.draw.line(screen,WHITE,[coordGrid[i][0][0],coordGrid[0][0][1]],[coordGrid[i][-1][0],coordGrid[-1][-1][1]+ sqSize] ,1)
    for j in range(len(coordGrid[0])):
        pygame.draw.line(screen,WHITE,[coordGrid[0][0][0],coordGrid[0][j][1]],[coordGrid[-1][0][0] + sqSize,coordGrid[-1][j][1]] ,1)
    
    pygame.draw.line(screen,WHITE,[coordGrid[0][0][0] ,coordGrid[0][-1][1]+sqSize],[coordGrid[-1][0][0] + sqSize,coordGrid[-1][-1][1]+ sqSize] ,1)
    pygame.draw.line(screen,WHITE,[coordGrid[-1][0][0]+sqSize,coordGrid[-1][0][1]],[coordGrid[-1][0][0] + sqSize,coordGrid[-1][-1][1]+sqSize],1)



def fillGrid(grid,coordGrid):
    for i in range(len(coordGrid)):
        for j in range(len(coordGrid[0])):
            color = ()
        
            try:color = returnColor(grid[i][j])
            except: print "o"; terminate()
            if grid[i][j] != 0:
                try:drawSmallSq(coordGrid,i,j,color)
                except:print "k"; terminate()

def returnSquare(coordGrid,x,y): #Takes screen coordinates and returns grid coordinates
    
    for i in range(len(coordGrid)):
        for j in range(len(coordGrid[0])):
            try:
                if (x > coordGrid[i][j][0] and x <= (coordGrid[i][j][0] + sqSize)) and (y > coordGrid[i][j][1] and y <= coordGrid[i][j][1] + sqSize):
                                      
                    return i,j 
                else:
                    continue
            except: print "der"; terminate()
    else:
        return -1,-1

def makeCoordGrid(grid,bH,bV): #Makes a grid or the same size as grid, but with x,y coordinates
    coordGrid = np.zeros([bH,bV,2])
    
    midpoint = WINDOWHEIGHT/2
    gridStartY = midpoint - sqSize*blocksVertical/2
    gridStartX = sqSize
    
    xPoints = [gridStartX + i*sqSize for i in range(bH)]
    yPoints = [gridStartY + i*sqSize for i in range(bV)]
    
    try:
        for i in range(len(coordGrid)):
            for j in range(len(coordGrid[0])):
                
                coordGrid[i][j][0] = xPoints[i]
                coordGrid[i][j][1] = yPoints[j]
    except: print "her"
    return coordGrid


    
def drawSmallSq(coordGrid,i,j,color):
    if i == -1: 
        return
    x,y = coordGrid[i][j]
    pygame.draw.rect(screen,color,[x,y,sqSize,sqSize])
    
def drawButtons(sqType):
    color =()
    color = returnColor(sqType)
    
    pygame.draw.rect(screen,color,[WINDOWWIDTH - 100*(WINDOWWIDTH/gridSize), WINDOWHEIGHT/10,100,50])
    pygame.draw.rect(screen,DARKGREEN,[WINDOWWIDTH - 100*(WINDOWWIDTH/gridSize), WINDOWHEIGHT/1.5,100,50])
    
def updateGrid(grid,coordGrid,x,y,sqType,drawType):
    i,j = returnSquare(coordGrid,x,y)
    if drawType == 1:
        for k in range(len(coordGrid[0])):
            try:
                grid[i][k] = sqType
            except:
                return
            
    elif  drawType == 2:
        for k in range(len(coordGrid)):
            try:
                grid[k][j] = sqType
            except:
                return          
    else:
        try:
            grid[i][j] = sqType
        except:
            return
    
def returnColor(sqType):
    color =()
    if sqType == 1:
        color = ORANGE
    elif sqType == 2:
        color = RED
    elif sqType == 3:
        color = GREEN
    elif sqType == 4:
        color = YELLOW
    else:
        color = WHITE
    
    return color
    
def drawSqOnPointer(coordGrid,sqX,sqY, color,drawType): 
    if drawType == 1:
        for i in range(len(coordGrid[0])):
            drawSmallSq(coordGrid,sqX,i, color)
    elif  drawType == 2:
        for i in range(len(coordGrid)):
            drawSmallSq(coordGrid,i,sqY, color)
    else:
        drawSmallSq(coordGrid,sqX,sqY, color)
        

def writeToFile(grid):
    grid = np.array(grid)
    grid = np.transpose(grid)
    outFile = open("layout.txt","w")
    for row in grid:
        for num in row:
            try:outFile.write(str(num) + " ")
            except: print "j"; terminate()
        outFile.write("\n")
    outFile.close()
        
def terminate():
    pygame.quit()
    sys.exit()

try:
    main()
except:
    print "noe skjedde"
    terminate()