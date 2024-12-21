
/*          

    BSCS 3 - IS         

    Meraña, Joed                    ____                       ____  _     _        _____ _            ____                       _                            
    Baisa, Marco                   |  _ \ ___   ___  _ __ ___ | __ )| |__ (_) ___  |_   _| |__   ___  |  _ \ ___   ___  _ __ ___ | |__   __ _      
    Belen, Princess                | |_) / _ \ / _ \| '_ ` _ \|  _ \| '_ \| |/ _ \   | | | '_ \ / _ \ | |_) / _ \ / _ \| '_ ` _ \| '_ \ / _` |     
    Cayubit, Jhade                 |  _ < (_) | (_) | | | | | | |_) | | | | |  __/   | | | | | |  __/ |  _ < (_) | (_) | | | | | | |_) | (_| |     
    Esmade, Zed                    |_| \_\___/ \___/|_| |_| |_|____/|_| |_|_|\___|   |_| |_| |_|\___| |_| \_\___/ \___/|_| |_| |_|_.__/ \__,_| 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

/*  -------------------------------- ! IMPORTANT ! -------------------------------- */

//#include <unistd.h>           /*      For Linux User      */
#include <time.h>               /*      For Windows User    */
#define sleepInterval 200      /*  Change to 1000 if OS is Windows
                                    Change to 1 if OS is Linux          */
#define clearSyntax "cls"       /*  Change to "cls" if OS is Windows
                                    Change to "clear" if OS is Linux    */

/*  ------------------------ ! May babaguhin pa sa Line 364 & 365 ! ------------------------ */


/*  -------------------------------- !      NOTE      ! -------------------------------- */

// NOTE: Array[Yaxis][Xaxis]
// 0 = Blocked, 1 = Open, 2 = Objective

#pragma region Global Variables
/*  ----------------- Colors: ----------------- */
#define colorGreen "\e[1;32m"
#define colorBlue "\e[1;34m"
#define colorRed "\e[;31m"
#define colorReset "\e[0m"

/*  ----------------- Global Variables -----------------    */
int mapSize = 0, indexer = 0, separateTabIndex = 0, 
    executeIndex = 0, tempIndexer = 0, codePage = 0,
    moveCount = 0, lineCount = 0, level = 0;

int currentPosition[] = {0, 0};
int startingPosition[] = {0, 0};

char directionFacing[] = "right",
     startingDirection[] = "right",
     gameMode[10] = "play",
     result[] = "lose",
     onEdit[5] = "No",
     executing[5] = "No",
     errorLine[100];

char *levelTitle[] = {      "RoomBhie's First Clean",   "Twist & Turns",    "Lost in the Dust", "Charging Quest",
                            "Maze of the Machines",     "Circular Journey", "Dusty Detours",    "Swivel Shuffle",
                            "The Great Vacuum Escape",  "Sparks Fly",       "Dusty Road Ahead", "Whirling Wonders",
                            "Power Surge",              "The Final Sweep",  "RoomBhie Recharged"   };

/*  ----------------- Input Handler -----------------   */
char *input[500];
char *tempInput[500];
char **ptr = input;

/*  ----------------- Help Section -----------------    */
char *help[50] = {  "Help Section:", " ", "     Code\t\t\tDescription", " ",
                    "[ start ]\t\tto Begin the Program", "[ end ]\t\t\tto Stop the Program",
                    "[ move(fwd) ]\t\tMove RoomBhie one(1) tile Forward", "[ move(bwd) ]\t\tMove RoomBhie one(1) tile Backward",
                    "[ rotate(cw) ]\t\tRotate RoomBhie Clockwise", "[ rotate(ccw) ]\t\tRotate RoomBhie Counter Clockwise",
                    "[ reset ]\t\tErase all lines of code", "[ focus(line#)]\t\tChange Focus to Specific Code Line",
                    "[ edit(line#) ]\t\tEdit a Specific Line of Code", "[ do ]\t\t\tStart a Loop", "[ loop(iterator#) ]\tend a loop depending on the number of iterator",
                    "", "[ exit ] to Return"};
char **ptr2 = help;

/*  ----------------- Result Section -----------------    */
char *resultWin[50] = {     "__   __           __        ___       _",
                            "\\ \\ / /__  _   _  \\ \\      / (_)_ __ | |",
                            " \\ V / _ \\| | | |  \\ \\ /\\ / /| | '_ \\| |",
                            "  | | (_) | |_| |   \\ V  V / | | | | |_|",
                            "  |_|\\___/ \\__,_|    \\_/\\_/  |_|_| |_(_)",
                            "", "", "", "", "", "(Note: The lower the Overall Score, the Better!)", "",
                            "-------------------------------------------------------------------",
                            "", "[1]\tPlay Again", "[2]\tNext Level", "[3]\tLevel Select",
                            "[4]\tReturn to Main Menu"   };
char **ptr3 = resultWin;

char *resultLose[50] = {    "__   __            _                   _ ",
                            "\\ \\ / /__  _   _  | |    ___  ___  ___| |",
                            " \\ V / _ \\| | | | | |   / _ \\/ __|/ _ \\ |",
                            "  | | (_) | |_| | | |__| (_) \\__ \\  __/_|",
                            "  |_|\\___/ \\__,_| |_____\\___/|___/\\___(_)",
                            "", "", "",
                            "-------------------------------------------------------------------",
                            "", "[1]\tPlay Again", "[2]\tNext Level", "[3]\tLevel Select",
                            "[4]\tReturn to Main Menu"   };

char **ptr4 = resultLose;

/*  ----------------- Story Section -----------------    */
char *level1[50] = {            "", "RoomBhie: Hello there and Welcome! Try to get to the Finish Line",
                                "\t  by navigating through the Maze using Commands!", "", "TIP: You can use 'move(fwd)' to move one tile Forward",
                                "     and 'move(bwd)' to move one tile Backwards!", "", "", "Sample Code:", "", "1\t\tstart", "2\t\tmove(fwd)", "3\t\tmove(fwd)",
                                "4\t\tmove(fwd)", "5\t\tend", "","", "RoomBhie: This command makes me move five tiles forward!"};
char **ptr5 = level1;

char *level2[50] = {            "", "RoomBhie: Great, you passed the first challenge! We are", "\t  just getting started! There will be a lot of Twist and Turns",
                                "\t  before we reached the end.", "", "TIP: You can use the command 'rotate(cw)' to rotate RoomBhie clockwise", "     and 'rotate(ccw)' to rotate RoomBhie counter clockwise!", "","",
                                "Sample Code:", "", "1\t\tstart", "2\t\tmove(fwd)", "3\t\trotate(ccw)", "4\t\tmove(fwd)", "5\t\tend"};
char **ptr6 = level2;

char *level3[50] = {            "", "RoomBhie: Wait! Why are there so many Flags? This would also take many lines of commands?!", "", "TIP: you can use the command 'do' and 'loop'", "     to simplify repetitive commands!",
                                "","", "Sample Code:", "", "1\t\tstart", "2\t\tdo", "3\t\tmove(fwd)", "4\t\tloop(9)", "5\t\tend", "", "", "RoomBhie: Wow! With 5 lines of code this will make me move 10 steps forward!"};
char **ptr7 = level3;

char *level4[50] = {            "", "RoomBhie: Fantastic! Looks like you're on your feet now!", "\t  Keep it up and see you at the other side!", "", "TIP: You can use the arrow up '↑' keys in your keyboard",
                                "     to select your previously written command!", "", "", "Challenge: Try to complete this using only 8 line of commands."};
char **ptr8 = level4;

/*  ----------------- Functions Initialization -----------------    */
void mapLayout();
char inputHandler();
void separateTab();
void displayMenu();
void mainMenu();
void levelSelect();
void checkResult();
void resetPosition();
void executeCode();
void startLevel();
void movePlayer(char movement, int mazeMap[][mapSize], int currentPosition[], int boundaryX, int boundaryY);
#pragma endregion

int main(){
    /*  ----------------------------------------------- ! Boot ! -----------------------------------------------    */
    /*      Clear Display                           */                    system(clearSyntax);
    /*      If Unicode/Symbols is not printing      */                    system("chcp 65001"); 
    mainMenu();
}

void mapLayout(int mazeMap[][mapSize], int currentPosition[2], int row, int column){
    int Xaxis, Yaxis;
    int columnSpacing, columnSeparator, rowSeparator, rowLines;
    char finishLine[10]; 
    sprintf(finishLine,"%s🏳%s",colorGreen,colorReset);
    
/*  -------------------------------- Page Identifier -------------------------------- */
    if(!strcmp(gameMode, "play")){
        /*      Easy Mode       */      if(mapSize == 5){
                                            if(!strcmp(executing,"Yes"))    codePage = executeIndex / 20;
                                        separateTabIndex =                  codePage * 20;
                                        }
        /*      Medium Mode     */      if(mapSize == 8){
                                            if(!strcmp(executing,"Yes"))    codePage = executeIndex / 32;
                                        separateTabIndex =                  codePage * 32;
                                        }
        /*      Hard Mode       */      if(mapSize == 10){
                                            if(!strcmp(executing,"Yes"))    codePage = executeIndex / 40;
                                        separateTabIndex =                  codePage * 40;
                                        }
    } else separateTabIndex = 0;

    /*  -------------------------------- Map Layout & Grids -------------------------------- */
    printf("\n");
    for(Yaxis = 0; Yaxis < row; Yaxis++){
        // Vertical Lines
        printf("\n\t\t");
        for(rowSeparator = 0; rowSeparator < mapSize; rowSeparator++) printf("+-------");
        printf("+\t\t\t|");
        separateTab(0);
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
                        else printf(mazeMap[Yaxis][Xaxis] == 1 ? " " : (mazeMap[Yaxis][Xaxis] == 0) ? "X" : finishLine);           // Open and Blocked Paths
                    }   else printf(" ");
                }
            }
            printf("\t\t|");        // NOTE: This line is for separator of Panels
            separateTab(0);
        }
    }
    printf("\n\t\t");
    for(rowSeparator = 0; rowSeparator < mapSize; rowSeparator++) printf("+-------");
    printf("+\t\t\t|");
    separateTab(1);

    /*  -------------------------------- Debuggin & Input -------------------------------- */
    printf("\n\n\tCurrent Y-Position: %d\t\t[help] - View Commands\n\tCurrent X-Position: %d\t\t[exit] - Return to Main Menu\n\tDirection Facing: %s\n\tYour Input: ", currentPosition[0], currentPosition[1], directionFacing);
}

void separateTab(int codeLine){
    if(!strcmp(gameMode,"play")){
        if          (separateTabIndex == 0)                                             printf("\tRoomBhie's Code:");
        else if     (separateTabIndex == 1)                                             printf("\t%s%s%s", colorRed, errorLine, colorReset);
        else if     (codeLine == 1)                                                     printf("%s\t\t\t\t[ prev/next ]\tTo Switch Page%s", colorBlue, colorReset);
        else if     (ptr[separateTabIndex] != NULL){
            if      (separateTabIndex == executeIndex)                                  printf("\t%s>\t\t%s%s", colorGreen, ptr[separateTabIndex-2], colorReset);
            else if (separateTabIndex == indexer+2 && executeIndex == 0)                printf("\t%s>\t\t%s%s", colorGreen, ptr[separateTabIndex-2], colorReset);
            else                                                                        printf("\t%d\t\t%s", separateTabIndex-1, ptr[separateTabIndex-2]);
        }
    }
    else if         (!strcmp(gameMode,"help")){  if(ptr2[separateTabIndex] != NULL)     printf("\t%s", ptr2[separateTabIndex]);  }
    else if         (!strcmp(gameMode,"result")){
        if          (ptr3[separateTabIndex] != NULL && !strcmp(result, "win"))          printf("\t%s", ptr3[separateTabIndex]);
        else if     (ptr4[separateTabIndex] != NULL && !strcmp(result, "lose"))         printf("\t%s", ptr4[separateTabIndex]);
    }
    else if         (!strcmp(gameMode,"story")){
        if          (codeLine == 1)                                                     printf("\t%s[ play ] - To Proceed\t\t[ return ] - To Main Menu%s", colorBlue, colorReset);
        else if     (level == 1 && ptr5[separateTabIndex] != NULL)                      printf("\t%s", ptr5[separateTabIndex]);
        else if     (level == 2 && ptr6[separateTabIndex] != NULL)                      printf("\t%s", ptr6[separateTabIndex]);
        else if     (level == 3 && ptr7[separateTabIndex] != NULL)                      printf("\t%s", ptr7[separateTabIndex]);
        else if     (level == 4 && ptr8[separateTabIndex] != NULL)                      printf("\t%s", ptr8[separateTabIndex]);
    } 

    separateTabIndex++;
}

char inputHandler(){
    strcpy(errorLine, " ");

    char movement[50];
        scanf("%s",&movement);

        if(!strcmp(gameMode, "result")){
            /*      Play Again      */      if          (!strcmp(movement, "1")){
                                                        /*  Copy Inputs from Temporary Array  */
                                                        for (int i = 0; i < 202; i++) {
                                                            input[i] =              (char *)malloc(strlen(tempInput[i]) + 1);
                                                            if (input[i] != NULL)   {strcpy(input[i], tempInput[i]);}         }
                                                            startLevel(1);
                                                        }                 
            /*      Next Level      */      else if     (!strcmp(movement, "2")){    level++; startLevel(0);     }
            /*      Level Select    */      else if     (!strcmp(movement, "3"))     levelSelect();
            /*      Main Menu       */      else if     (!strcmp(movement, "4"))     mainMenu();
        }

        else if     (!strcmp(movement, "help"))                                       strcpy(gameMode, "help");
        else if     (!strcmp(gameMode, "help") && !strcmp(movement, "exit"))          strcpy(gameMode, "play");

        else if     (!strcmp(gameMode, "story") && !strcmp(movement, "play"))         strcpy(gameMode, "play");
        else if     (!strcmp(gameMode, "story") && !strcmp(movement, "return"))       mainMenu();

        /*  ----------------- Play Section -----------------    */
        else if         (!strcmp(gameMode, "play")){

            /*  ----------------- For Line Specifier -----------------  */
            char move[50]; char *extractedSyntax; int specifiedLine;
            /*      Save Temp String        */      strcpy(move, movement);
            /*      Extract First Word      */      extractedSyntax = strtok(move, " (");
            
            /*  ----------------- Code Page Switcher -----------------    */
            if          (!strcmp(gameMode, "play") && !strcmp(movement, "next") && codePage != 11)        codePage++;
            else if     (!strcmp(gameMode, "play") && !strcmp(movement, "prev") && codePage != 0)         codePage--;
            else if     (!strcmp(movement, "exit"))                                                       mainMenu();
            else if     (!strcmp(extractedSyntax, "page")){
                sscanf  (movement, "page(%d)", &specifiedLine);
                codePage = specifiedLine-1;
            }
            /*  ----------------- Start Command -----------------    */
            else if     (indexer == 0 && strcmp(movement, "start"))             strcpy(errorLine, "Error: program must begin with the 'start' command.");
            /*  ----------------- Reset Command -----------------    */
            else if     (!strcmp(movement, "reset")){
                for(int x = 0; x < 50; x++) ptr[x] = malloc(50 * sizeof(char));
                indexer = 0;

                resetPosition();
            }
            /*  ----------------- Edit Command -----------------    */
            else if     (!strcmp(extractedSyntax, "edit")){
                sscanf(movement, "edit(%d)", &specifiedLine);
                tempIndexer = indexer;
                indexer=specifiedLine-1;
                strcpy(onEdit, "Yes");
            }
            /*  ----------------- Delete Command -----------------    */
            else if     (!strcmp(extractedSyntax, "delete")){
                sscanf(movement, "delete(%d)", &specifiedLine);
                ptr[specifiedLine-1] = malloc(50 * sizeof(char));
            }
            /*  ----------------- Focus Command -----------------    */
            else if     (!strcmp(extractedSyntax, "focus")){
                sscanf(movement, "focus(%d)", &specifiedLine);
                indexer = specifiedLine-1;
            }
            /*  ----------------- End Command -----------------    */
            else{
                strcpy(ptr[indexer], movement);

                if      (!strcmp(movement, "end")) {

                            /*  Copy Inputs to Temporary Array  */
                            for (int i = 0; i < 202; i++) {
                                tempInput[i] = (char *)malloc(strlen(input[i]) + 1); // +1 for the null terminator
                                
                                if (tempInput[i] != NULL) {
                                    strcpy(tempInput[i], input[i]);
                                }
                            }

                            lineCount = indexer; 
                            return 'e';
                    }
                    indexer++;
                if      (!strcmp(onEdit, "Yes")) {indexer = tempIndexer; strcpy(onEdit, "No"); } // Return to Normal Index after Editing
            }
        }

    return 'x';
}

void executeCode(int mazeMap[][mapSize], int currentPosition[], int row, int column){

    strcpy  (executing, "Yes");

    /*      For Looping Purposes        */
    int loopStartIndex = 0, loopCount = -1, canLoop = 1;

    for(int lines=0; lines<=indexer; lines++){

        /*      Display Changes in Map      */
        executeIndex = lines+1;
        system(clearSyntax);
        displayMenu();
        mapLayout(mazeMap, currentPosition, row, column);

        /*  ----------------- For Looping Purposes -----------------    */
        char move[50]; char *extractedSyntax;
        /*      Save Temp String        */      strcpy(move, ptr[lines]);
        /*      Extract First Word      */      extractedSyntax = strtok(move, " (");                                                                                                
        /*      Save Loop Counts        */      if(!strcmp(extractedSyntax,"loop")) {                           sscanf(ptr[lines], "loop(%d)", &loopCount); canLoop = 0; }                          
        /*      Return to Loop Start    */      if(!strcmp(extractedSyntax,"loop") && loopCount != 0) {         sprintf(ptr[lines], "loop(%d)", loopCount-1); 
                                                    lines = loopStartIndex; 
                                                    loopCount--;
                                                }
                                                if(!strcmp(ptr[lines],"loop(0)")){      // For Reseting Previous Loops (Nested Loops)
                                                        for (int i = 0; i <= lines; i++) {
                                                            input[i] =              (char *)malloc(strlen(tempInput[i]) + 1);
                                                            if (input[i] != NULL)   {strcpy(input[i], tempInput[i]);}         }
                                                }


        /*      Execute Each Line of Codes      */
        if          (!strcmp(ptr[lines],"move(fwd)"))        movePlayer('w', mazeMap, currentPosition, row, column);
        else if     (!strcmp(ptr[lines],"move(bwd)"))        movePlayer('s', mazeMap, currentPosition, row, column);
        else if     (!strcmp(ptr[lines],"rotate(cw)"))       movePlayer('d', mazeMap, currentPosition, row, column);
        else if     (!strcmp(ptr[lines],"rotate(ccw)"))      movePlayer('a', mazeMap, currentPosition, row, column);
        else if     (!strcmp(ptr[lines],"do"))               loopStartIndex = lines;
        else if     (!strcmp(ptr[lines],"end"))              checkResult(mazeMap);


        /*      For Windows OS      */      _sleep(sleepInterval);
        /*      For Linux OS        */      //sleep(sleepInterval);
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
    if      (movement == 'a' || movement == 'd'){                                                
        directionIndex = (movement == 'a') ? ((directionIndex + 3) % 4) : ((directionIndex + 1) % 4);
        strcpy(directionFacing, directions[directionIndex]);
    }
    /*       ----------------- Move Fowards and Backwards -----------------         */
    else if (movement == 'w' || movement == 's'){                                            
        int direction = (movement == 'w') ? -1 : 1;

        if          (!strcmp(directionFacing, "up"))         newY += direction;
        else if     (!strcmp(directionFacing, "right"))      newX -= direction;
        else if     (!strcmp(directionFacing, "down"))       newY -= direction;
        else if     (!strcmp(directionFacing, "left"))       newX += direction;
    }

    /*  ----------------- Updates the Current Position from the Maze -----------------  */
    if(mazeMap[newY][newX] != 0 && newX >= 0 && newY >= 0 && newX < boundaryX && newY < boundaryY){
        currentPosition[0] = newY;
        currentPosition[1] = newX;

        // Makes it a blank tile
        mazeMap[newY][newX] = 1;
    }

    moveCount++;
}

void resetPosition(){
    lineCount = 0; 
    moveCount = 0;

    currentPosition[0] = startingPosition[0];
    currentPosition[1] = startingPosition[1];
    strcpy(directionFacing, startingDirection);
}

void checkResult(int mazeMap[][mapSize]){
    strcpy  (gameMode,"result");
    strcpy  (executing,"No");

    int objectiveCount = 0;
    int rows = mapSize, column = mapSize;

    /*      Check Objective Count   */
    for(int i=0; i<rows; i++) for(int j=0; j<column; j++) if(mazeMap[i][j] == 2) objectiveCount++;

    ptr3[6] = malloc(50 * sizeof(char));
    ptr4[6] = malloc(50 * sizeof(char));
    ptr3[7] = malloc(50 * sizeof(char));
    ptr3[9] = malloc(50 * sizeof(char));

    strcpy      (result, (objectiveCount == 0) ? "win" : "lose");
    sprintf     (ptr3[6], "Time Complexity: %d Move/s", moveCount);
    sprintf     (ptr4[6], "%sDon't Give Up! Try Again!%s", colorRed, colorReset);
    sprintf     (ptr3[7], "Space Complexity: %d Line/s", lineCount+1);
    sprintf     (ptr3[9], "%sOverall Score: %.2f%s", colorGreen, (double)(moveCount*(lineCount+1))/(mapSize*mapSize), colorReset);
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
    if(level != 0) printf("\t\t\t\t\t\t\t\t\t%sLevel %d: %s%s", colorGreen, level, levelTitle[level-1], colorReset);
    printf("\n\t-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
}

void mainMenu(){
    /*      Clear Display       */      system(clearSyntax);    level = 0;
    /*      Display Header      */      displayMenu();

    /*      Show Menu           */      
    char choice[50];
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\tMain Menu\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t\t    %s[ 1 ] Start Game%s\n", colorGreen, colorReset);
    printf("\t\t\t\t\t\t\t\t\t\t    [ 2 ] Level Select\n");
    printf("\t\t\t\t\t\t\t\t\t\t    [ 3 ] About\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t    %s[ 0 ] Exit Game%s\n\n\n", colorRed, colorReset);
    printf("\n\t\t\t\t\t\t\t\t\t\t    Select Choice: ");
    scanf("%s", &choice);

    if          (!strcmp(choice, "1")){          level = 1; startLevel(0);   }
    else if     (!strcmp(choice, "2"))           levelSelect();
    else if     (!strcmp(choice, "3"));
    else if     (!strcmp(choice, "0"))           exit(0);
    else                                         mainMenu();
}

void levelSelect(){
    /*      Clear Display       */      system(clearSyntax); level  = 0;
    /*      Display Header      */      displayMenu();

    /*      Show Levels         */      
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\tLevel Selection\n\n\n");
    printf("\t\t\t\t%s[ Tutorial ]%s\t\t\t\t[ Easy ]\t\t\t\t[ Medium ]\t\t\t\t%s[ Hard ]%s\n\n", colorGreen, colorReset, colorRed, colorReset);
    printf("\t\t\t %s[ 1 ] RoomBhie's First Clean%s\t\t  [ 5 ] Maze of the Machines\t\t[ 9 ] The Great Vacuum Escape\t\t %s[ 13 ] Power Surge%s\n\n", colorGreen, colorReset, colorRed, colorReset);
    printf("\t\t\t %s[ 2 ] Twist & Turns%s\t\t\t  [ 6 ] Circular Journey\t\t[ 10 ] Sparks Fly\t\t\t %s[ 14 ] The Final Sweep%s\n\n", colorGreen, colorReset, colorRed, colorReset);
    printf("\t\t\t %s[ 3 ] Lost in the Dust%s\t\t\t  [ 7 ] Dusty Detours\t\t\t[ 11 ] Dusty Roads Ahead\t\t %s[ 15 ] RoomBhie Recharged%s\n\n", colorGreen, colorReset, colorRed, colorReset);
    printf("\t\t\t %s[ 4 ] Charging Quest%s\t\t\t  [ 8 ] Swivel Shuffle\t\t\t[ 12 ] Whirling Wonders\n\n", colorGreen, colorReset, colorRed, colorReset);
    printf("\n\n\t\t\t\t\t\t\t\t\t\t   [ 0 ] Return to Main Menu\n\t\t\t\t\t\t\t\t\t\t        Select Level: ");
    scanf("%d", &level);

    if(level == 0) mainMenu();
    else startLevel(0);
}

/*  ----------------------------- ! Levels Dito ! -----------------------------    */


void startLevel(int retry){
    
    strcpy(gameMode, "play");
    if(level > 0 && level < 5) strcpy(gameMode, "story");

    if(retry == 0){
        /*      Allocate Memory for Each Input (Wag Alisin!!!)      */
        for(int x = 0; x < 202; x++) ptr[x] = malloc(50 * sizeof(char));
        indexer = 0;
        codePage = 0;
    }

    /*      Level One       */
    if(level == 1){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {1,1,0,0,0},
                                        {0,0,0,0,0},
                                        {1,1,1,1,2},
                                        {0,0,0,0,0},   
                                        {0,0,0,1,1}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 2;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }
    
    /*      Level Two       */
    if(level == 2){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {0,0,0,0,0},
                                        {1,1,1,0,0},
                                        {0,0,1,0,0},
                                        {0,0,1,1,2},   
                                        {0,0,0,0,0}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 1;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Three       */
    if(level == 3){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {2,1,1,1,2},
                                        {1,0,0,0,1},
                                        {1,0,1,0,1},
                                        {1,0,0,0,1},   
                                        {2,1,1,1,2}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 2;
            /*          Declare Starting X Position                     */      startingPosition[1] = 4;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "down");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Four       */
    if(level == 4){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {2,1,0,0,1},
                                        {0,1,1,0,1},
                                        {0,0,1,1,0},
                                        {1,0,0,1,1},   
                                        {1,1,0,0,1}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 4;
            /*          Declare Starting X Position                     */      startingPosition[1] = 4;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "up");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Five       */
    if(level == 5){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {1,1,1,1,2},
                                        {1,0,1,0,1},
                                        {1,1,1,1,1},
                                        {1,0,1,1,0},   
                                        {1,0,0,0,0}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 4;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Siz       */
    if(level == 6){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {1,0,1,1,1},
                                        {1,1,1,0,1},
                                        {1,0,0,1,1},
                                        {1,0,0,1,0},   
                                        {1,1,1,1,2}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 0;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Seven       */
    if(level == 7){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {1,1,1,1,1},
                                        {1,0,1,0,1},
                                        {1,1,1,0,1},
                                        {1,0,0,0,1},   
                                        {1,1,1,0,2}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 4;
            /*          Declare Starting X Position                     */      startingPosition[1] = 2;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "left");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Eight       */
    if(level == 8){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 5;
            int mazeMap[5][5] = 	  { {1,1,1,1,1},
                                        {1,0,0,0,1},
                                        {1,0,2,1,1},
                                        {1,1,0,0,1},   
                                        {0,1,1,1,1}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 3;
            /*          Declare Starting X Position                     */      startingPosition[1] = 1;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "left");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Nine       */
    if(level == 9){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 8;
            int mazeMap[8][8] = 	  { {1,1,0,0,1,1,1,0},
                                        {1,1,1,1,0,1,1,1},
			                            {1,0,1,1,1,1,1,0},
                                        {1,1,1,1,0,1,1,1},
                                        {1,0,1,2,1,0,1,0},
                                        {1,0,0,1,1,1,1,1},
                                        {1,1,1,1,1,0,1,0},  
                                        {0,1,1,0,1,1,1,2}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 0;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Ten       */
    if(level == 10){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 8;
            int mazeMap[8][8] = 	  { {0,1,1,1,0,1,1,0},
                                        {1,1,0,1,1,1,0,0},
                                        {1,0,0,1,0,1,1,1},
                                        {1,1,0,0,1,1,0,1},
                                        {0,1,1,2,1,0,1,1},
                                        {1,1,0,0,0,0,1,0},
                                        {1,0,1,0,1,1,1,1},  
                                        {1,1,1,1,1,0,0,2}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 0;
            /*          Declare Starting X Position                     */      startingPosition[1] = 1;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "down");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Eleven       */
    if(level == 11){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 8;
            int mazeMap[8][8] = 	  { {1,0,0,0,1,1,1,1},
                                        {1,1,1,1,1,0,0,1},
                                        {0,1,0,1,0,0,1,1},
                                        {1,1,1,0,1,1,2,1},
                                        {1,1,1,3,0,1,0,1},
                                        {1,0,1,0,1,1,0,1},
                                        {0,0,0,0,1,1,1,1},  
                                        {2,1,1,1,1,1,1,0}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 7;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Twelve       */
    if(level == 12){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 8;
            int mazeMap[8][8] = 	  { {1,1,1,1,1,1,1,1},
                                        {0,1,0,0,0,0,1,0},
                                        {1,1,1,1,1,1,1,1},
                                        {0,0,0,0,1,0,0,1},
                                        {0,1,2,0,1,2,1,1},
                                        {1,1,0,0,0,0,0,1},
                                        {1,0,1,1,1,0,1,1},  
                                        {1,1,1,0,1,1,1,0}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 0;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Thirteen       */
    if(level == 13){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 10;
            int mazeMap[10][10] = 	  { {0,0,0,1,1,1,1,0,0,0},
                                        {1,1,1,0,0,1,1,1,2,0},
                                        {1,0,1,0,1,1,0,1,1,1},
                                        {1,0,1,1,1,1,0,0,1,1},
                                        {1,1,0,1,1,0,0,1,0,1},
                                        {0,2,0,0,0,2,1,1,1,1},
                                        {1,1,0,1,1,1,1,0,1,1},
                                        {1,0,0,1,0,0,1,1,0,1},
                                        {1,1,0,1,1,1,1,1,1,0},
                                        {0,1,1,1,1,0,0,1,1,0}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 4;
            /*          Declare Starting X Position                     */      startingPosition[1] = 4;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "up");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Fourteen       */
    if(level == 14){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 10;
            int mazeMap[10][10] = 	  { {1,0,1,1,1,1,1,1,1,1},
                                        {0,1,1,1,0,1,0,1,0,1},
                                        {0,1,0,1,0,1,0,0,1,1},
                                        {1,1,0,1,0,1,0,1,1,1},
                                        {2,0,0,0,0,1,1,1,0,1},
                                        {1,0,0,0,1,1,1,0,0,2},
                                        {1,1,0,1,1,0,0,0,1,1},
                                        {1,1,2,1,1,1,0,1,1,0},
                                        {1,0,0,0,0,1,0,1,0,1},
                                        {2,1,1,1,1,1,1,1,0,1}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 3;
            /*          Declare Starting X Position                     */      startingPosition[1] = 5;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "down");

            /*              Implement Starting Positions                */      resetPosition();

            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }

    /*      Level Fifteen       */
    if(level == 15){
        /*  ----------------- Level Format (Start) -----------------    */      

            /*          Declare Map Size & Map Layout                   */      mapSize = 10;
            int mazeMap[10][10] = 	  { {0,1,0,0,1,1,1,2,1,1},
                                        {1,2,1,0,1,0,0,0,0,1},
                                        {1,0,1,1,1,1,0,1,1,1},
                                        {1,1,0,1,0,1,0,1,1,0},
                                        {0,1,0,1,1,1,2,1,1,0},
                                        {1,1,0,0,0,0,0,0,1,0},
                                        {1,0,1,1,1,1,1,0,1,1},
                                        {1,1,0,1,1,0,1,0,0,1},
                                        {0,1,1,1,0,0,1,1,1,1},
                                        {1,1,0,1,2,0,0,0,0,0}  };

            /*          Declare Starting Y Position                     */      startingPosition[0] = 9;
            /*          Declare Starting X Position                     */      startingPosition[1] = 0;
            /*          Declare Starting Facing Direction               */      strcpy(startingDirection, "right");

            /*              Implement Starting Positions                */      resetPosition();
            
            while(1){
                /*          Clear Display                   */      system(clearSyntax);
                /*          Display Title Menu              */      displayMenu();
                /*          Display Map Layout              */      mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
                /*          Request Input                   */      if(inputHandler() == 'e') executeCode(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
            }

            /*  ----------------- Level Format (Finish) -----------------    */
    }
}

/*          

    BSCS 3 - IS         

    Meraña, Joed                    ____                       ____  _     _        _____ _            ____                       _                            
    Baisa, Marco                   |  _ \ ___   ___  _ __ ___ | __ )| |__ (_) ___  |_   _| |__   ___  |  _ \ ___   ___  _ __ ___ | |__   __ _      
    Belen, Princess                | |_) / _ \ / _ \| '_ ` _ \|  _ \| '_ \| |/ _ \   | | | '_ \ / _ \ | |_) / _ \ / _ \| '_ ` _ \| '_ \ / _` |     
    Cayubit, Jhade                 |  _ < (_) | (_) | | | | | | |_) | | | | |  __/   | | | | | |  __/ |  _ < (_) | (_) | | | | | | |_) | (_| |     
    Esmade, Zed                    |_| \_\___/ \___/|_| |_| |_|____/|_| |_|_|\___|   |_| |_| |_|\___| |_| \_\___/ \___/|_| |_| |_|_.__/ \__,_| 

*/

