#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOTE: Array[Yaxis][Xaxis]
// NOTE: Inom Tubig jusq

// TODO: Levels, Input & Error Handler, GUI
// 0 = Blocked, 1 = Open, 2 = Objective

// Colors:
#define colorGreen "\e[1;32m"
#define colorBlue "\e[1;34m"
#define colorRed "\e[;31m"
#define colorReset "\e[0m"

// Global Variables
int mapSize = 0, objectiveCount = 1, indexer = 0, separateTabIndex = 0, executeIndex = 0;
int currentPosition[] = {0, 0};
char directionFacing[] = "right";
char gameMode[] = "play";
char errorLine[100];

// Input Handler (Wag Alisin!!!)
char *input[500];
char **ptr = input;

// Help Section
char *help[50] = {  "Help Section:", " ", "     Code\t\t\tDescription", " ",
                    "[ start ]\t\tto Begin the Program", "[ end ]\t\t\tto Stop the Program",
                    "[ move(fwd) ]\t\tMove RoomBhie one(1) tile Forward", "[ move(bwd) ]\t\tMove RoomBhie one(1) tile Backward",
                    "[ rotate(cw) ]\t\tRotate RoomBhie Clockwise", "[ rotate(ccw) ]\t\tRotate RoomBhie Counter Clockwise",
                    "[ reset ]\t\tErase all lines of code",
                    "", "exit to Return"};
char **ptr2 = help;


// Functions Initialization
void mapLayout();
char inputHandler();
void separateTab();
void displayMenu();
void executeCode();
void movePlayer(char movement, int mazeMap[][mapSize], int currentPosition[], int boundaryX, int boundaryY);

int main(){

    // Use this every level vvvv
    mapSize = 5;
    int mazeMap[5][5] = {   {1,0,1,1,1},
                            {1,1,1,0,1},
                            {1,0,0,1,1},
                            {1,0,0,1,0},   
                            {1,1,1,1,2}  };
    currentPosition[0] = 0; // Y Axis
    currentPosition[1] = 0; // X Axis
    for(int x = 0; x < 50; x++) ptr[x] = malloc(50 * sizeof(char)); // Allocate Memory for Each Input (Wag Alisin!!!)
    // Use this every level ^^^^

    while(objectiveCount != 0){
        objectiveCount = 0;         // Reset to Zero
        printf("\e[1;1H\e[2J");
        displayMenu();
        mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
    }
}

void mapLayout(int mazeMap[][mapSize], int currentPosition[2], int row, int column){
    int Xaxis, Yaxis;
    int columnSpacing, columnSeparator, rowSeparator, rowLines;
    separateTabIndex = 0;

    // Draw Map Layout Here:

    printf("\n");
    for(Yaxis = 0; Yaxis < row; Yaxis++){
        // Vertical Lines
        printf("\n\t\t");
        for(rowSeparator = 0; rowSeparator < mapSize; rowSeparator++) printf("+-------");
        printf("+");
        printf("\t\t\t|");      // NOTE: This line is for separator of Panels
        separateTab();
        // Horizontal Lines
        for(columnSeparator = 0; columnSeparator < 3; columnSeparator++){
            printf("\n\t\t");
            for(Xaxis = 0; Xaxis < (column + 1); Xaxis++){
                printf("|");
                for(columnSpacing = 0; columnSpacing < 7; columnSpacing++){
                    if(columnSpacing == 3 && columnSeparator == 1 && Xaxis != mapSize){
                        if(Yaxis == currentPosition[0] && Xaxis == currentPosition[1]){                                     // Player Icon
                            printf(colorGreen);
                            printf((!strcmp(directionFacing, "up")) ? "↑" : (!strcmp(directionFacing, "left")) ? "←" :
                            (!strcmp(directionFacing, "down")) ? "↓" : "→");
                            printf(colorReset);
                        }
                        else printf(mazeMap[Yaxis][Xaxis] == 1 ? " " : (mazeMap[Yaxis][Xaxis] == 0) ? "X" : "◦");           // Open and Blocked Paths
                        objectiveCount += (mazeMap[Yaxis][Xaxis] == 2) ? 1 : 0;                                             // Counts Existing Objectives
                    }   else printf(" ");
                }
            }
            printf("\t\t|");        // NOTE: This line is for separator of Panels
            separateTab();
        }
    }
    printf("\n\t\t");
    for(rowSeparator = 0; rowSeparator < mapSize; rowSeparator++) printf("+-------");
    printf("+");
    printf("\t\t\t|");        // NOTE: This line is for separator of Panels
    separateTab();

    // Read Input Here:

    printf("\n\n\tCurrent Y-Position: %d\t\t[help] - View Commands\n\tCurrent X-Position: %d\t\t[exit] - Return to Main Menu\n\tDirection Facing: %s\n\tYour Input: ", currentPosition[0], currentPosition[1], directionFacing);
    if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, row, column);
}

void separateTab(){
    if(!strcmp(gameMode,"play")){
        if(separateTabIndex == 0) printf("\tRoomBhie's Code:");
        else if(separateTabIndex == 1) printf("\t%s%s%s", colorRed, errorLine, colorReset);
        else if(ptr[separateTabIndex] != NULL){
            if(separateTabIndex == executeIndex) printf("\t>\t\t%s", ptr[separateTabIndex-2]);
            else printf("\t%d\t\t%s", separateTabIndex-1, ptr[separateTabIndex-2]);
        }
    }
    else if(!strcmp(gameMode,"help")){
        if(ptr2[separateTabIndex] != NULL) printf("\t%s", ptr2[separateTabIndex]);
    }
    separateTabIndex++;
}

char inputHandler(){
    strcpy(errorLine, " ");

    char movement[50];
        scanf("%s",&movement);

        if(!strcmp(movement, "help")) strcpy(gameMode, "help");
        else if(!strcmp(gameMode, "help") && !strcmp(movement, "exit")) strcpy(gameMode, "play");

        // Play Section
        else if(!strcmp(gameMode, "play")){

            if(indexer == 0 && strcmp(movement, "start")) strcpy(errorLine, "Error: program must begin with the 'start' command.");
            else if(!strcmp(movement, "reset")){
                for(int x = 0; x < 50; x++) ptr[x] = malloc(50 * sizeof(char));
                indexer = 0;
            }
            //char *syntax = strtok(movement, "move");
            //printf("%s\n", syntax);
            else{
                strcpy(ptr[indexer], movement);

                if(!strcmp(movement, "end")) return 'e';
                indexer++;
            }
        }

    return 'x';
}

void executeCode(int mazeMap[][mapSize], int currentPosition[], int row, int column){
    for(int lines=1; lines<indexer; lines++){
        if(!strcmp(ptr[lines],"move(fwd)")) movePlayer('w', mazeMap, currentPosition, row, column);
        else if(!strcmp(ptr[lines],"move(bwd)")) movePlayer('s', mazeMap, currentPosition, row, column);
        else if(!strcmp(ptr[lines],"rotate(cw)")) movePlayer('d', mazeMap, currentPosition, row, column);
        else if(!strcmp(ptr[lines],"rotate(ccw)")) movePlayer('a', mazeMap, currentPosition, row, column);
    }
}

void movePlayer(char movement, int mazeMap[][mapSize], int currentPosition[], int boundaryX, int boundaryY){
    int directionIndex;
    char *directions[] = {"up", "right", "down", "left"};
    for(int i = 0; i < 4; i++) if(!strcmp(directionFacing, directions[i])) directionIndex = i;
    
    int newY = currentPosition[0];
    int newX = currentPosition[1];

    if(movement == 'a' || movement == 'd'){                                                // Rotate Counter Clockwise or Clockwise respectively
        directionIndex = (movement == 'a') ? ((directionIndex + 3) % 4) : ((directionIndex + 1) % 4);
        strcpy(directionFacing, directions[directionIndex]);
    }
    else if(movement == 'w' || movement == 's'){                                            // Move Forward and Backward
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

// GUI Dito

void displayMenu(){
        printf("\n\n\t\t                       ######                                                                                                                                   \n");
        printf("\t\t                     ##**##**##                     ______  ______  ______  __    __  ______  __  __  __  ______                                                    \n");
        printf("\t\t               #####################               /\\  == \\/\\  __ \\/\\  __ \\/\\ \"-./  \\/\\  == \\/\\ \\_\\ \\/\\ \\/\\  ___\\                                \n");
        printf("\t\t           #########*##########*########*          \\ \\  __<\\ \\ \\/\\ \\ \\ \\/\\ \\ \\ \\-./\\ \\ \\  __<\\ \\  __ \\ \\ \\ \\  __\\                            \n");
        printf("\t\t         ##**********#**+==+##############          \\ \\_\\ \\_\\ \\_____\\ \\_____\\ \\_\\ \\ \\_\\ \\_____\\ \\_\\ \\_\\ \\_\\ \\_____\\                         \n");
        printf("\t\t         *#*****************************#*+          \\/_/ /_/\\/_____/\\/_____/\\/_/  \\/_/\\/_____/\\/_/\\/_/\\/_/\\/_____/                                       \n");
        printf("\t\t         =#***************#***********###++         ______ __  __  ______      ______  ______  ______  __    __  ______  ______                                     \n");
        printf("\t\t         =+*####*********##********###**+=         /\\__  _/\\ \\_\\ \\/\\  ___\\    /\\  == \\/\\  __ \\/\\  __ \\/\\ \"-./  \\/\\  == \\/\\  __ \\                \n");
        printf("\t\t         ++**#***********************#**++         \\/_/\\ \\\\ \\  __ \\ \\  __\\    \\ \\  __<\\ \\ \\/\\ \\ \\ \\/\\ \\ \\ \\-./\\ \\ \\  __<\\ \\  __ \\        \n");
        printf("\t\t           #*#####################***#**#             \\ \\_\\\\ \\_\\ \\_\\ \\_____\\   \\ \\_\\ \\_\\ \\_____\\ \\_____\\ \\_\\ \\ \\_\\ \\_____\\ \\_\\ \\_\\    \n");
        printf("\t\t             **#######********####***##                \\/_/ \\/_/\\/_/\\/_____/    \\/_/ /_/\\/_____/\\/_____/\\/_/  \\/_/\\/_____/\\/_/\\/_/                      \n");
        printf("\t\t                 ****####**###****                                                                                                                                  \n");
        printf("\n\t-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    }