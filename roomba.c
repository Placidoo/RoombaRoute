#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define colorGreen "\e[1;32m"
#define colorBlue "\e[1;34m"
#define colorRed "\e[;31m"
#define colorReset "\e[0m"

// NOTE: Array[Yaxis][Xaxis]

// Global Variables
int mapSize = 5, objectiveCount = 1;
int currentPosition[] = {0, 0};
char directionFacing[] = "right";

// Functions Initialization
void mapLayout();
void movePlayer(char movement, int mazeMap[][mapSize], int currentPosition[], int boundaryX, int boundaryY);

int main(){
    int mazeMap[5][5] = {   {1, 2, 2, 2, 2},
                            {0, 0, 0, 0, 2},
                            {2, 2, 2, 2 ,2},
                            {2, 0, 0, 0, 0},
                            {2, 2, 2, 2, 2}          };
    mapSize = 5;

    while(objectiveCount != 0){
        objectiveCount = 0;         // Reset to Zero
        printf("\e[1;1H\e[2J");
        mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
    }
}

void mapLayout(int mazeMap[][mapSize], int currentPosition[2], int row, int column){
    int Xaxis, Yaxis;
    int columnSpacing, columnSeparator, rowSeparator, rowLines;


    // Draw Map Layout Here:

    printf("\n");
    for(Yaxis = 0; Yaxis < row; Yaxis++){
        // Vertical Lines
        printf("\n\t");
        for(rowSeparator = 0; rowSeparator < 5; rowSeparator++) printf("+-------");
        printf("+");
        printf("\t\t\t|");      // NOTE: This line is for separator of Panels
        // Horizontal Lines
        for(columnSeparator = 0; columnSeparator < 3; columnSeparator++){
            printf("\n\t");
            for(Xaxis = 0; Xaxis < (column + 1); Xaxis++){
                printf("|");
                for(columnSpacing = 0; columnSpacing < 7; columnSpacing++){
                    if(columnSpacing == 3 && columnSeparator == 1 && Xaxis != 5){
                        if(Yaxis == currentPosition[0] && Xaxis == currentPosition[1]){                                     // Player Icon
                            printf(colorGreen);
                            printf((!strcmp(directionFacing, "up")) ? "↑" : (!strcmp(directionFacing, "left")) ? "←" :
                            (!strcmp(directionFacing, "down")) ? "↓" : "→");
                            printf(colorReset);
                        }
                        else printf(mazeMap[Yaxis][Xaxis] == 1 ? " " : (mazeMap[Yaxis][Xaxis] == 0) ? "X" : "◦");           // Open and Blocked Paths

                        if (mazeMap[Yaxis][Xaxis] == 2) objectiveCount++;                                                   // Check For Objective Count
                    }   else printf(" ");
                }
            }
            printf("\t\t|");        // NOTE: This line is for separator of Panels
        }
    }
    printf("\n\t");
    for(rowSeparator = 0; rowSeparator < 5; rowSeparator++) printf("+-------");
    printf("+");

    // Read Input Here:

    char movement;
    printf("\nCurrent Y-Position: %d\t\t[w] - Move Forward\nCurrent X-Position: %d\t\t[s] - Move Backward\nDirection Facing: %s\t\t[a / d] - Rotate\nYour Move: ", currentPosition[0], currentPosition[1], directionFacing);
    scanf("%c", &movement);
    movePlayer(movement, mazeMap, currentPosition, row, column);
}

void movePlayer(char movement, int mazeMap[][mapSize], int currentPosition[], int boundaryX, int boundaryY){
    int directionIndex;
    char *directions[] = {"up", "right", "down", "left"};
    for(int i = 0; i < 4; i++) if(!strcmp(directionFacing, directions[i])) directionIndex = i;
    
    int newY = currentPosition[0];
    int newX = currentPosition[1];

    if(movement == 'a'){                                                // Rotate Counter Clockwise
        directionIndex = (directionIndex + 3) % 4;
        strcpy(directionFacing, directions[directionIndex]);
    }
    else if(movement == 'd'){                                           // Rotate Clockwise
        directionIndex = (directionIndex + 1) % 4;
        strcpy(directionFacing, directions[directionIndex]);
    }
    else if(movement == 'w' || movement == 's'){                        // Move Forward and Backward
        int direction = (movement == 'w') ? -1 : 1;

        if(!strcmp(directionFacing, "up")) newY += direction;
        else if(!strcmp(directionFacing, "right")) newX -= direction;
        else if(!strcmp(directionFacing, "down")) newY -= direction;
        else if(!strcmp(directionFacing, "left")) newX += direction;
    }

    // Updates the Current Position from the Maze
    if(mazeMap[newY][newX] != 0 && newX >= 0 && newY >= 0 && newX < boundaryX && newY < boundaryY){
        currentPosition[0] = newY;
        currentPosition[1] = newX;

        // Makes it a blank tile
        mazeMap[newY][newX] = 1;
    }
}