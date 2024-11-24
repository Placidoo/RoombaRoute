#include <stdio.h>
#include <stdlib.h>

// NOTE: Array[Yaxis][Xaxis]

void mapLayout();
void movePlayer(char movement, int mazeMap[][5], int currentPosition[2]);
int currentPosition[] = {0, 0};

int main(){
    int mazeMap[5][5] = {   {1, 1, 1, 1, 1},
                            {0, 0, 0, 0, 1},
                            {1, 1, 1, 1 ,1},
                            {1, 0, 0, 0, 0},
                            {1, 1, 1, 1, 1}          };
    int finishLine[] = {4, 4};

    while(1){
        printf("\e[1;1H\e[2J");
        mapLayout(mazeMap, currentPosition, sizeof(mazeMap) / sizeof(mazeMap[0]), sizeof(mazeMap[0])/ sizeof(mazeMap[0][0]));
        printf("\nCurrent Y-Position: %d\nCurrent X-Position: %d\nYour Move: ", currentPosition[0], currentPosition[1]);
        char movement;
        scanf("%c", &movement);
        movePlayer(movement, mazeMap, currentPosition);
        if(currentPosition[0] == finishLine[0] && currentPosition[1] == finishLine[1]) break;
    }
}

void movePlayer(char movement, int mazeMap[][5], int currentPosition[2]){
    int Position[] = {currentPosition[0], currentPosition[1]};
    if(movement == 'w') Position[0] -= 1;
    if(movement == 'a') Position[1] -= 1;
    if(movement == 's') Position[0] += 1;
    if(movement == 'd') Position[1] += 1;

    if(mazeMap[Position[0]][Position[1]] != 0){
        currentPosition[0] = Position[0];
        currentPosition[1] = Position[1];
    }
}

void printHorizontalLines(int columns){
    for(int i = 0; i < columns; i++) printf("+-------");
    printf("+\n");
}

void printCell(int mazeMap[][5], int currentPosition[2], int Yaxis, int Xaxis){
    if(Yaxis == currentPosition[0] && Xaxis == currentPosition[1]) printf(" O ");       // Player
    else printf(mazeMap[Yaxis][Xaxis] == 1 ? "   " : " X ");                            // Path and Blocked Paths
}

void mapLayout(int mazeMap[][5], int currentPosition[2], int row, int column){
    printf("\n");

    // Print Top Border
    printHorizontalLines(column);

    // Print Maze Rows
    for(int Yaxis = 0; Yaxis < row; Yaxis++){
        // Print Maze Cells and Vertical Borders
        for(int rowSeparator = 0; rowSeparator < 3; rowSeparator++){
            printf("\t|");
            for(int Xaxis = 0; Xaxis < column; Xaxis++){
                printCell(mazeMap, currentPosition, Yaxis, Xaxis);
                printf("|");
            }
            printf("\n");

            // After Printing Cells, Print Horizontal Separator
            if(rowSeparator == 2) printHorizontalLines(column);
        }
    }
}
