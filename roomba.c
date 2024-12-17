#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// NOTE: Array[Yaxis][Xaxis]
// NOTE: Inom Tubig jusq

// TODO: Levels, Input & Error Handler, GUI
// 0 = Blocked, 1 = Open, 2 = Objective

/*  ----------------- Colors: ----------------- */
#define colorGreen "\e[1;32m"
#define colorBlue "\e[1;34m"
#define colorRed "\e[;31m"
#define colorReset "\e[0m"

/*  ----------------- Global Variables -----------------    */
int mapSize = 0, indexer = 0, separateTabIndex = 0,
    executeIndex = 0, tempIndexer = 0;
int currentPosition[] = {0, 0};
char directionFacing[] = "right";
char gameMode[10] = "play";
char onEdit[5] = "No";
char errorLine[100];

/*  ----------------- Input Handler -----------------   */
char *input[500];
char **ptr = input;

/*  ----------------- Help Section -----------------    */
char *help[50] = {  "Help Section:", " ", "     Code\t\t\tDescription", " ",
                    "[ start ]\t\tto Begin the Program", "[ end ]\t\t\tto Stop the Program",
                    "[ move(fwd) ]\t\tMove RoomBhie one(1) tile Forward", "[ move(bwd) ]\t\tMove RoomBhie one(1) tile Backward",
                    "[ rotate(cw) ]\t\tRotate RoomBhie Clockwise", "[ rotate(ccw) ]\t\tRotate RoomBhie Counter Clockwise",
                    "[ reset ]\t\tErase all lines of code", "[ focus(line#)]\t\tChange Focus to Specific Code Line",
                    "[ edit(line#) ]\t\tEdit a Specific Line of Code",
                    "", "exit to Return"};
char **ptr2 = help;

/*  ----------------- Result Section -----------------    */
char *result[50] = {    "Result:"   };
char **ptr3 = result;


/*  ----------------- Functions Initialization -----------------    */
void mapLayout();
char inputHandler();
void separateTab();
void displayMenu();
void checkResult();
void executeCode();
void movePlayer(char movement, int mazeMap[][mapSize], int currentPosition[], int boundaryX, int boundaryY);

int main(){

    /*  ----------------- Level Format (Start) -----------------    */      

    /*          Declare Map Size & Map Layout                   */      mapSize = 5;
    int mazeMap[5][5] = {   {1,0,1,1,1},
                            {1,1,1,0,1},
                            {1,0,0,1,1},
                            {1,0,0,1,0},   
                            {1,1,1,1,2}  };

    /*          Declare Starting Y Position                     */      currentPosition[0] = 0;
    /*          Declare Starting X Position                     */      currentPosition[1] = 0;

    /*      Allocate Memory for Each Input (Wag Alisin!!!)      */
    for(int x = 0; x < 50; x++) ptr[x] = malloc(50 * sizeof(char));

    while(1){
        /*          Clear Display                   */      printf("\e[1;1H\e[2J");
        /*          Display Title Menu              */      displayMenu();
        /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
        /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
    }

    /*  ----------------- Level Format (Finish) -----------------    */      

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
}

void separateTab(){
    if(!strcmp(gameMode,"play")){
        if(separateTabIndex == 0) printf("\tRoomBhie's Code:");
        else if(separateTabIndex == 1) printf("\t%s%s%s", colorRed, errorLine, colorReset);
        else if(ptr[separateTabIndex] != NULL){
            if(separateTabIndex == executeIndex) printf("\t%s>\t\t%s%s", colorGreen, ptr[separateTabIndex-2], colorReset);
            else if(separateTabIndex == indexer+2 && executeIndex == 0) printf("\t%s>\t\t%s%s", colorGreen, ptr[separateTabIndex-2], colorReset);
            else printf("\t%d\t\t%s", separateTabIndex-1, ptr[separateTabIndex-2]);
        }
    }
    else if(!strcmp(gameMode,"help")){
        if(ptr2[separateTabIndex] != NULL) printf("\t%s", ptr2[separateTabIndex]);
    }
    else if(!strcmp(gameMode,"result")) if(ptr2[separateTabIndex] != NULL) printf("\t%s", ptr3[separateTabIndex]);

    separateTabIndex++;
}

char inputHandler(){
    strcpy(errorLine, " ");

    char movement[50];
        scanf("%s",&movement);

        if(!strcmp(movement, "help")) strcpy(gameMode, "help");
        else if(!strcmp(gameMode, "help") && !strcmp(movement, "exit")) strcpy(gameMode, "play");

        /*  ----------------- Play Section -----------------    */
        else if(!strcmp(gameMode, "play")){

            /*  ----------------- For Line Specifier -----------------  */
            char move[50]; char *extractedSyntax; int specifiedLine;
            /*      Save Temp String        */      strcpy(move, movement);
            /*      Extract First Word      */      extractedSyntax = strtok(move, " (");
            

            /*  ----------------- Start Command -----------------    */
            if(indexer == 0 && strcmp(movement, "start")) strcpy(errorLine, "Error: program must begin with the 'start' command.");
            /*  ----------------- Reset Command -----------------    */
            else if(!strcmp(movement, "reset")){
                for(int x = 0; x < 50; x++) ptr[x] = malloc(50 * sizeof(char));
                indexer = 0;
            }
            /*  ----------------- Edit Command -----------------    */
            else if(!strcmp(extractedSyntax, "edit")){
                sscanf(movement, "edit(%d)", &specifiedLine);
                tempIndexer = indexer;
                indexer=specifiedLine-1;
                strcpy(onEdit, "Yes");
            }
            /*  ----------------- Delete Command -----------------    */
            else if(!strcmp(extractedSyntax, "delete")){
                sscanf(movement, "delete(%d)", &specifiedLine);
                ptr[specifiedLine-1] = malloc(50 * sizeof(char));
            }
            /*  ----------------- Focus Command -----------------    */
            else if(!strcmp(extractedSyntax, "focus")){
                sscanf(movement, "focus(%d)", &specifiedLine);
                indexer = specifiedLine-1;
            }
            /*  ----------------- End Command -----------------    */
            else{
                strcpy(ptr[indexer], movement);

                if(!strcmp(movement, "end")) return 'e';
                indexer++;
                if(!strcmp(onEdit, "Yes")) {indexer = tempIndexer; strcpy(onEdit, "No"); } // Return to Normal Index after Editing
            }
        }

    return 'x';
}

void executeCode(int mazeMap[][mapSize], int currentPosition[], int row, int column){

    /*      For Looping Purposes        */
    int loopStartIndex = 0, loopCount = -1, canLoop = 1;

    for(int lines=0; lines<=indexer; lines++){

        /*      Display Changes in Map      */
        executeIndex = lines+1;
        printf("\e[1;1H\e[2J");
        displayMenu();
        mapLayout(mazeMap, currentPosition, row, column);

        /*  ----------------- For Looping Purposes -----------------    */
        char move[50]; char *extractedSyntax;
        /*      Save Temp String        */      strcpy(move, ptr[lines]);
        /*      Extract First Word      */      extractedSyntax = strtok(move, " (");
        /*      Save Loop Counts        */      if(!strcmp(extractedSyntax,"loop") && canLoop == 1) { sscanf(ptr[lines], "loop(%d)", &loopCount); canLoop = 0; }
        /*      Return to Loop Start    */      if(!strcmp(extractedSyntax,"loop") && loopCount != 0) {
                                                    sprintf(ptr[lines], "loop(%d)", loopCount-1); 
                                                    lines = loopStartIndex; 
                                                    loopCount--;
                                                }
        /*      Enable Looping          */      if(!strcmp(extractedSyntax,"loop") && loopCount == 0 && canLoop == 0) canLoop = 1;


        /*      Execute Each Line of Codes      */
        if(!strcmp(ptr[lines],"move(fwd)")) movePlayer('w', mazeMap, currentPosition, row, column);
        else if(!strcmp(ptr[lines],"move(bwd)")) movePlayer('s', mazeMap, currentPosition, row, column);
        else if(!strcmp(ptr[lines],"rotate(cw)")) movePlayer('d', mazeMap, currentPosition, row, column);
        else if(!strcmp(ptr[lines],"rotate(ccw)")) movePlayer('a', mazeMap, currentPosition, row, column);
        else if(!strcmp(ptr[lines],"do")) loopStartIndex = lines;
        else if(!strcmp(ptr[lines],"end")) checkResult(mazeMap);
        sleep(1);
    }
    executeIndex = 0;
}

void movePlayer(char movement, int mazeMap[][mapSize], int currentPosition[], int boundaryX, int boundaryY){
    int directionIndex;
    char *directions[] = {"up", "right", "down", "left"};
    for(int i = 0; i < 4; i++) if(!strcmp(directionFacing, directions[i])) directionIndex = i;
    
    int newY = currentPosition[0];
    int newX = currentPosition[1];

    /*  ----------------- Rotate Counter Clockwise or Clockwise -----------------   */
    if(movement == 'a' || movement == 'd'){                                                
        directionIndex = (movement == 'a') ? ((directionIndex + 3) % 4) : ((directionIndex + 1) % 4);
        strcpy(directionFacing, directions[directionIndex]);
    }
    /*       ----------------- Move Fowards and Backwards -----------------         */
    else if(movement == 'w' || movement == 's'){                                            
        int direction = (movement == 'w') ? -1 : 1;

        if(!strcmp(directionFacing, "up")) newY += direction;
        else if(!strcmp(directionFacing, "right")) newX -= direction;
        else if(!strcmp(directionFacing, "down")) newY -= direction;
        else if(!strcmp(directionFacing, "left")) newX += direction;
    }

    /*  ----------------- Updates the Current Position from the Maze -----------------  */
    if(mazeMap[newY][newX] != 0 && newX >= 0 && newY >= 0 && newX < boundaryX && newY < boundaryY){
        currentPosition[0] = newY;
        currentPosition[1] = newX;

        // Makes it a blank tile
        mazeMap[newY][newX] = 1;
    }
}

void checkResult(int mazeMap[][mapSize]){
    strcpy(gameMode,"result");

    int objectiveCount = 0;
    int rows = mapSize, column = mapSize;

    for(int i=0; i<rows; i++){
        for(int j=0; j<column; j++){
            if(mazeMap[i][j] == 2){
                objectiveCount++;
            }
        }
    }

    ptr3[0] = (objectiveCount == 0) ? "You Win" : "You Lose";
    
}

/*  ----------------- GUI Dito -----------------    */
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