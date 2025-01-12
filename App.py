import os
import time

#  ----------------------------------------------- ! Global Variables ! -----------------------------------------------    #

colorGreen  =    '\033[32m'
colorBlue   =    '\033[34m'
colorRed    =    '\033[31m'
colorReset  =    '\033[0m'

gameMode    =   'play'
errorLine   =   ''
result      =   ''

codePage            =   0
indexer             =   0
tempIndexer         =   0
executeIndex        =   0
separateTabIndex    =   0
lineCount           =   0
moveCount           =   0
level               =   0

onEdit      =   False
executing   =   False

inputs              =   [''] * 250
tempInputs          =   []
currentPosition     =   [0, 0]
startingPosition    =   [0, 0]
mazeMap             =   []

levelTitle = [              "RoomBhie's First Clean",   "Twist & Turns",    "Lost in the Dust", "Charging Quest",
                            "Maze of the Machines",     "Circular Journey", "Dusty Detours",    "Swivel Shuffle",
                            "The Great Vacuum Escape",  "Sparks Fly",       "Dusty Road Ahead", "Whirling Wonders",
                            "Power Surge",              "The Final Sweep",  "RoomBhie Recharged"   ]

helpInfo = [        "Help Section:", " ", "     Code\t\t\tDescription", " ",
                    "[ start ]\t\tto Begin the Program", "[ end ]\t\t\tto Stop the Program",
                    "[ move(fwd) ]\t\tMove RoomBhie one(1) tile Forward", "[ move(bwd) ]\t\tMove RoomBhie one(1) tile Backward",
                    "[ rotate(cw) ]\t\tRotate RoomBhie Clockwise", "[ rotate(ccw) ]\t\tRotate RoomBhie Counter Clockwise",
                    "[ reset ]\t\tErase all lines of code", "[ focus(line#)]\t\tChange Focus to Specific Code Line",
                    "[ edit(line#) ]\t\tEdit a Specific Line of Code", "[ do ]\t\t\tStart a Loop", "[ loop(iterator#) ]\tend a loop depending on the number of iterator",
                    "", "[ exit ] to Return"        ]

resultWin = [               "__   __           __        ___       _",
                            "\\ \\ / /__  _   _  \\ \\      / (_)_ __ | |",
                            " \\ V / _ \\| | | |  \\ \\ /\\ / /| | '_ \\| |",
                            "  | | (_) | |_| |   \\ V  V / | | | | |_|",
                            "  |_|\\___/ \\__,_|    \\_/\\_/  |_|_| |_(_)",
                            "", "", "", "", "", "(Note: The lower the Overall Score, the Better!)", "",
                            "-------------------------------------------------------------------",
                            "", "[1]\tPlay Again", "[2]\tNext Level", "[3]\tLevel Select",
                            "[4]\tReturn to Main Menu"   ]

resultLose = [              "__   __            _                   _ ",
                            "\\ \\ / /__  _   _  | |    ___  ___  ___| |",
                            " \\ V / _ \\| | | | | |   / _ \\/ __|/ _ \\ |",
                            "  | | (_) | |_| | | |__| (_) \\__ \\  __/_|",
                            "  |_|\\___/ \\__,_| |_____\\___/|___/\\___(_)",
                            "", "", "",
                            "-------------------------------------------------------------------",
                            "", "[1]\tPlay Again", "[2]\tNext Level", "[3]\tLevel Select",
                            "[4]\tReturn to Main Menu"   ]

level1 = [                  "", "RoomBhie: Hello there and Welcome! Try to get to the Finish Line",
                                "\t  by navigating through the Maze using Commands!", "", "TIP: You can use 'move(fwd)' to move one tile Forward",
                                "     and 'move(bwd)' to move one tile Backwards!", "", "", "Sample Code:", "", "1\t\tstart", "2\t\tmove(fwd)", "3\t\tmove(fwd)",
                                "4\t\tmove(fwd)", "5\t\tend", "","", "RoomBhie: This command makes me move five tiles forward!"             ]

level2 = [                  "", "RoomBhie: Great, you passed the first challenge! We are", "\t  just getting started! There will be a lot of Twist and Turns",
                                "\t  before we reached the end.", "", "TIP: You can use the command 'rotate(cw)' to rotate RoomBhie clockwise", "     and 'rotate(ccw)' to rotate RoomBhie counter clockwise!", "","",
                                "Sample Code:", "", "1\t\tstart", "2\t\tmove(fwd)", "3\t\trotate(ccw)", "4\t\tmove(fwd)", "5\t\tend"        ]

level3 = [                  "", "RoomBhie: Wait! Why are there so many Flags? This would also take many lines of commands?!", "", "TIP: you can use the command 'do' and 'loop'", "     to simplify repetitive commands!",
                                "","", "Sample Code:", "", "1\t\tstart", "2\t\tdo", "3\t\tmove(fwd)", "4\t\tloop(9)", "5\t\tend", "", "", "RoomBhie: Wow! With 5 lines of code this will make me move 10 steps forward!"        ]

level4 = [                  "", "RoomBhie: Fantastic! Looks like you're on your feet now!", "\t  Keep it up and see you at the other side!", "", "TIP: You can use the arrow up '↑' keys in your keyboard",
                                "     to select your previously written command!", "", "", "Challenge: Try to complete this using only 8 line of commands."     ]

#  ----------------------------------------------- ! Functions ! -----------------------------------------------    #

def clearScreen():
    os.system('cls' if os.name == 'nt' else 'clear')

def mapLayout(mazeMap, currentPosition, mapSize):
    global separateTabIndex, executing, codePage

    #  ----------------- Page Identifier -----------------    #
    if (gameMode == 'play'):
        mapSizeValues = [5, 8, 10]
        multiplier =    [20, 32, 40]

        for x in range(3):
            if  (mapSize == mapSizeValues[x]):
                if executing: codePage = executeIndex // multiplier[x]
                separateTabIndex = codePage * multiplier[x]
                break
    else:   separateTabIndex = 0
        

    for Yaxis in range(mapSize):
        #Vertical Lines
        print("\n\t\t", end="")
        for rowSeparator in range(mapSize):
            print("+-------", end="")
        print("+\t\t\t|\t", end="")
        separateTab(0)
        #Horizontal Lines
        for columnSeparator in range(3):
            print("\n\t\t", end="")
            for Xaxis in range(mapSize + 1):
                print("|", end="")
                for columnSpacing in range(7):
                    if      (columnSpacing == 1 and columnSeparator == 0 and Xaxis != mapSize and mazeMap[Yaxis][Xaxis] == 0):    print("\\",end="")
                    elif    (columnSpacing == 5 and columnSeparator == 0 and Xaxis != mapSize and mazeMap[Yaxis][Xaxis] == 0):    print("/",end="")
                    elif    (columnSpacing == 1 and columnSeparator == 2 and Xaxis != mapSize and mazeMap[Yaxis][Xaxis] == 0):    print("/",end="")
                    elif    (columnSpacing == 5 and columnSeparator == 2 and Xaxis != mapSize and mazeMap[Yaxis][Xaxis] == 0):    print("\\",end="")
                    
                    elif(columnSpacing == 3 and columnSeparator == 1 and Xaxis != mapSize):
                        if(Yaxis == currentPosition[0] and Xaxis == currentPosition[1]):
                            player =    "↑" if directionFacing == "up" else \
                                        "←" if directionFacing == "left" else \
                                        "↓" if directionFacing == "down" else "→"
                            print(f"{colorGreen}{player}{colorReset}", end="")
                        else:
                            path =  " " if mazeMap[Yaxis][Xaxis] == 1 else \
                                    "X" if mazeMap[Yaxis][Xaxis] == 0 else f"{colorGreen}🏳{colorReset}"
                            print(path, end="")
                    else: print(" ", end="")
            print("\t\t|\t", end="")
            separateTab(0)
    print("\n\t\t", end="")
    for rowSeparator in range(mapSize): print("+-------", end="")
    print("+\t\t\t|\t", end="")
    separateTab(1)

    print   (f"\n\n\tCurrent Y-Position: {currentPosition[0]}\t\t[help] - View Commands\n\tCurrent X-Position: {currentPosition[1]}\t\t[exit] - Return to Main Menu" +
             f"\n\tDirection Facing: {directionFacing}\n\tYour Input: ", end="")
    
def separateTab(codeLine):
    global gameMode, separateTabIndex, errorLine, executeIndex, result

    if              (gameMode == 'play'):
        if          (separateTabIndex == 0):                                                print("RoomBhie's Code:", end="")
        elif        (separateTabIndex == 1):                                                print(f"{colorRed}{errorLine}{colorReset}", end="")
        elif        (codeLine == 1):                                                        print(f"{colorBlue}\t\t\t[ prev/next ]\tTo Switch Page{colorReset}", end="")
        elif        (separateTabIndex < 200):
            if      (separateTabIndex == executeIndex):                                     print(f"{colorGreen}>\t\t{inputs[separateTabIndex-2]}{colorReset}", end="") 
            elif    (separateTabIndex == indexer+2 and executeIndex == 0):                  print(f"{colorGreen}>\t\t{inputs[separateTabIndex-2]}{colorReset}", end="")
            else:                                                                           print(f"{separateTabIndex-1}\t\t{inputs[separateTabIndex-2]}", end="")
    elif            (gameMode == 'help'):
        if          (separateTabIndex < len(helpInfo)):                                     print(helpInfo[separateTabIndex], end="")
    elif            (gameMode == 'result'):
        if          (separateTabIndex < len(resultWin) and result == 'win'):                print(resultWin[separateTabIndex], end="")
        elif        (separateTabIndex < len(resultLose) and result == 'lose'):              print(resultLose[separateTabIndex], end="")
    elif            (gameMode == 'story'):
        if          (codeLine == 1):                                                        print(f"{colorBlue}[ play ] - To Proceed\t\t[ return ] - To Main Menu{colorReset}", end="")
        elif        (level == 1 and separateTabIndex < len(level1)):                        print(level1[separateTabIndex], end="")
        elif        (level == 2 and separateTabIndex < len(level2)):                        print(level2[separateTabIndex], end="")
        elif        (level == 3 and separateTabIndex < len(level3)):                        print(level3[separateTabIndex], end="")
        elif        (level == 4 and separateTabIndex < len(level4)):                        print(level4[separateTabIndex], end="")
    
    separateTabIndex+=1

def inputHandler():
    global gameMode, codePage, indexer, errorLine, inputs, tempIndexer, tempInputs, onEdit, lineCount, level

    errorLine = ""
    movement = input()

    if          (gameMode == 'result'):
        '       Play Again        ';                            
        if      (movement == '1'):          # Play Again                           
            inputs = tempInputs.copy()
            startLevel(1)
        elif    (movement == '2'):          # Next Level
            level+=1
            startLevel(0)
        elif    (movement == '3'):          levelSelect()
        elif    (movement == '4'):          mainMenu()

        '       Main Menu         ';                            pass
    
    elif    (movement == 'help'):                               gameMode = 'help'
    elif    (gameMode == 'help' and movement == 'exit'):        gameMode = 'play'
        
    elif    (gameMode == 'story' and movement == 'play'):       gameMode = 'play'
    elif    (gameMode == 'story' and movement == 'return'):     mainMenu()
    #  ----------------- Play Section -----------------    #      
    
    elif    (gameMode == 'play'):
        #  ----------------- For Line Specifier -----------------    #
        '       Extract First Word      ';                                                          extractedSyntax = movement.split('(')
        #  ----------------- Code Page Switcher -----------------    #
        if      (movement == 'next' and codePage != 10):                                            codePage+= 1
        elif    (movement == 'prev' and codePage != 0):                                             codePage-= 1
        elif    (movement == 'exit'):                                                               mainMenu()
        elif    (extractedSyntax[0] == 'page' and '(' in movement and ')' in movement):
            specifiedLine = movement.split('(')[1].split(')')[0]
            if  (specifiedLine.isdigit()):                                                          codePage = (int)(specifiedLine)-1

        #  ----------------- Start Command -----------------    #      
        elif    (indexer == 0 and movement != 'start'):                                             errorLine = 'ERROR: Program must begin with the \'start\' command'
        #  ----------------- Reset Command -----------------    # 
        elif    (movement == 'reset'):
            inputs = [" "] * 250
            indexer = 0
            resetPosition()
        #  ----------------- Edit Command -----------------     #      
        elif    (extractedSyntax[0] == 'edit' and '(' in movement and ')' in movement):
            specifiedLine = movement.split('(')[1].split(')')[0]
            if  (specifiedLine.isdigit()):
                tempIndexer = indexer
                indexer = (int)(specifiedLine)-1
                onEdit = True
        #  ----------------- Delete Command -----------------   # 
        elif    (extractedSyntax[0] == 'delete' and '(' in movement and ')' in movement):
            specifiedLine = movement.split('(')[1].split(')')[0]
            if  (specifiedLine.isdigit()):                                                          inputs[(int)(specifiedLine)-1] = None
        #  ----------------- Focus Command -----------------   # 
        elif    (extractedSyntax[0] == 'focus' and '(' in movement and ')' in movement):
            specifiedLine = movement.split('(')[1].split(')')[0]
            if  (specifiedLine.isdigit()):                                                          indexer = (int)(specifiedLine)-1
        #  ----------------- End Command -----------------      #
        else:
            inputs[indexer] = movement

            if  (movement == 'end'):
                tempInputs = inputs.copy()
                lineCount = indexer
                return 'e'
            
            indexer += 1

            if  onEdit:
                indexer = tempIndexer
                onEdit = False

    return 'x'

def executeCode(mazeMap, currentPosition, mapSize):
    global executing, indexer, inputs, executeIndex

    executing = True

    #  ----------------- For Looping Purposes -----------------    #
    loopStartIndex = 0 
    loopCount = -1

    lines = 0
    while lines <= indexer:

        #  ----------------- Display Changes in Map -----------------    #
        executeIndex = lines+1
        clearScreen()
        displayMenu()
        mapLayout(mazeMap, currentPosition, mapSize)

        #  ----------------- For Looping Purposes -----------------    #
        '       Extract First Word             ';                                                                           extractedSyntax = inputs[lines].split('(')
        '       Save Loop Counts               ';   
        if      (extractedSyntax[0] == 'loop' and '(' in inputs[lines] and ')' in inputs[lines] and inputs[lines] != 'loop()'):
            loopCount = inputs[lines].split('(')[1].split(')')[0]
            if(loopCount.isdigit): loopCount = int(loopCount)
            else: loopCount = 0
        '       Return Loop to Start           ';   
        if      (extractedSyntax[0] == 'loop' and '(' in inputs[lines] and ')' in inputs[lines] and loopCount > 0):
            loopCount-=1
            inputs[lines] = f'loop({loopCount})'
            lines = loopStartIndex
        '       Reset Previous Loops           ';   
        if      (inputs[lines] == 'loop(0)'):
            for elem in range(lines+1):                                                                                     inputs[elem] = tempInputs[elem]

        #  ----------------- Execute Each Line of Code -----------------    #
        if      (inputs[lines] == 'move(fwd)'):                 movePlayer('w', mazeMap, currentPosition, mapSize)
        elif    (inputs[lines] == 'move(bwd)'):                 movePlayer('s', mazeMap, currentPosition, mapSize)
        elif    (inputs[lines] == 'rotate(cw)'):                movePlayer('d', mazeMap, currentPosition, mapSize)
        elif    (inputs[lines] == 'rotate(ccw)'):               movePlayer('a', mazeMap, currentPosition, mapSize)
        elif    (inputs[lines] == 'do'):                        loopStartIndex = lines
        elif    (inputs[lines] == 'end'):                       checkResult(mazeMap, mapSize)

        time.sleep(0.5)
        lines+=1

    executeIndex = 0

def movePlayer(movement, mazeMap, currentPosition, mapSize):
    global directionFacing, moveCount

    directionIndex = (int)
    directions = ['up', 'right', 'down', 'left']
    for x in range(4):
        if(directionFacing == directions[x]): directionIndex = x
    
    newY = currentPosition[0]
    newX = currentPosition[1]

    #  ----------------- Rotate Counter Clockwise or Clockwise -----------------         #
    if          (movement == 'a' or movement == 'd'):
        directionIndex = ((directionIndex + 3) % 4) if (movement == 'a') else ((directionIndex + 1) % 4)
        directionFacing = directions[directionIndex]      

    #  ----------------- Move Forwards or Backwards -----------------                    #
    elif        (movement == 'w' or movement == 's'):
        direction = -1 if movement == 'w' else 1

        if      (directionFacing == 'up'):          newY += direction
        elif    (directionFacing == 'right'):       newX -= direction
        elif    (directionFacing == 'down'):        newY -= direction
        elif    (directionFacing == 'left'):        newX += direction      

    #  ----------------- Updates the Current Position from the Maze -----------------    #    
    if(newX >= 0 and newY >= 0 and newX < mapSize and newY < mapSize and mazeMap[newY][newX] != 0):
        currentPosition[0] = newY
        currentPosition[1] = newX

        # Make it Blank Tile
        mazeMap[newY][newX] = 1 

    moveCount+=1 

def resetPosition():
    global lineCount, moveCount, currentPosition, result

    lineCount = 0
    moveCount = 0

    currentPosition[0] = startingPosition[0]
    currentPosition[1] = startingPosition[1]


def checkResult(mazeMap, mapSize):
    global gameMode, executing, lineCount, moveCount, result

    gameMode = 'result'
    executing = False

    rows = mapSize
    columns = mapSize

    #  ----------------- Check Objective Count -----------------    #
    objectiveCount  =   sum(1 for i in range(rows) for j in range(columns) if mazeMap[i][j] == 2)

    result          =   'win' if objectiveCount == 0 else 'lose'
    resultWin[6]    =   f'Time Complexity: {moveCount} Move/s'
    resultLose[6]   =   f"{colorRed}Don't Give Up! Try Again!{colorReset}"
    resultWin[7]    =   f'Space Complexity: {lineCount+1} Line/s'
    resultWin[9]    =   f'{colorGreen}Overall Score: {((moveCount * (lineCount+1))/(mapSize*mapSize)):.2f}{colorReset}'

def displayMenu():
    print("\n\n\t\t                       ######                                                                                                                                   ")
    print("\t\t                     ##**##**##                     ______  ______  ______  __    __  ______  __  __  __  ______                                                    ")
    print("\t\t               #####################               /\\  == \\/\\  __ \\/\\  __ \\/\\ \"-./  \\/\\  == \\/\\ \\_\\ \\/\\ \\/\\  ___\\                                ")
    print("\t\t           #########*##########*########*          \\ \\  __<\\ \\ \\/\\ \\ \\ \\/\\ \\ \\ \\-./\\ \\ \\  __<\\ \\  __ \\ \\ \\ \\  __\\                            ")
    print("\t\t         ##**********#**+==+##############          \\ \\_\\ \\_\\ \\_____\\ \\_____\\ \\_\\ \\ \\_\\ \\_____\\ \\_\\ \\_\\ \\_\\ \\_____\\                         ")
    print("\t\t         *#*****************************#*+          \\/_/ /_/\\/_____/\\/_____/\\/_/  \\/_/\\/_____/\\/_/\\/_/\\/_/\\/_____/                                       ")
    print("\t\t         =#***************#***********###++         ______ __  __  ______      ______  ______  ______  __    __  ______  ______                                     ")
    print("\t\t         =+*####*********##********###**+=         /\\__  _/\\ \\_\\ \\/\\  ___\\    /\\  == \\/\\  __ \\/\\  __ \\/\\ \"-./  \\/\\  == \\/\\  __ \\                ")
    print("\t\t         ++**#***********************#**++         \\/_/\\ \\\\ \\  __ \\ \\  __\\    \\ \\  __<\\ \\ \\/\\ \\ \\ \\/\\ \\ \\ \\-./\\ \\ \\  __<\\ \\  __ \\        ")
    print("\t\t           #*#####################***#**#             \\ \\_\\\\ \\_\\ \\_\\ \\_____\\   \\ \\_\\ \\_\\ \\_____\\ \\_____\\ \\_\\ \\ \\_\\ \\_____\\ \\_\\ \\_\\    ")
    print("\t\t             **#######********####***##                \\/_/ \\/_/\\/_/\\/_____/    \\/_/ /_/\\/_____/\\/_____/\\/_/  \\/_/\\/_____/\\/_/\\/_/                      ")
    print("\t\t                 ****####**###****                                                                                                                                  ")
    if  (level != 0): print(f"\t\t\t\t\t\t\t\t\t{colorGreen}Level {level}: {levelTitle[level-1]}{colorReset}",end="")
    print("\n\t-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------")

def mainMenu():
    global level

    '       Clear Display          ';       clearScreen()             
    level = 0
    '       Display Header         ';       displayMenu()    

    '       Show Menu              ';       
    print("\n\n\t\t\t\t\t\t\t\t\t\t\tMain Menu\n\n\n")
    print(f"\t\t\t\t\t\t\t\t\t\t    {colorGreen}[ 1 ] Start Game{colorReset}", colorGreen, colorReset)
    print("\t\t\t\t\t\t\t\t\t\t    [ 2 ] Level Select")
    print("\t\t\t\t\t\t\t\t\t\t    [ 3 ] About")
    print(f"\n\t\t\t\t\t\t\t\t\t\t    {colorRed}[ 0 ] Exit Game{colorReset}\n\n", colorRed, colorReset)
    print("\n\t\t\t\t\t\t\t\t\t\t    Select Choice: ",end="")
    choice = input()

    if      (choice == '1'):
        level = 1
        startLevel(0)
    elif    (choice == '2'):          levelSelect()
    elif    (choice == '3'):          pass
    elif    (choice == '0'):          exit()
    else:                             mainMenu()                                                    


def levelSelect():
    global level

    '       Clear Display          ';       clearScreen()             
    level = 0
    '       Display Header         ';       displayMenu()

    '       Show Levels            ';       
    print("\n\n\t\t\t\t\t\t\t\t\t\t\tLevel Selection\n\n")
    print(f"\t\t\t\t{colorGreen}[ Tutorial ]{colorReset}\t\t\t\t[ Easy ]\t\t\t\t[ Medium ]\t\t\t\t{colorRed}[ Hard ]{colorReset}\n", colorGreen, colorReset, colorRed, colorReset)
    print(f"\t\t\t {colorGreen}[ 1 ] RoomBhie's First Clean{colorReset}\t\t  [ 5 ] Maze of the Machines\t\t[ 9 ] The Great Vacuum Escape\t\t {colorRed}[ 13 ] Power Surge{colorReset}\n", colorGreen, colorReset, colorRed, colorReset)
    print(f"\t\t\t {colorGreen}[ 2 ] Twist & Turns{colorReset}\t\t\t  [ 6 ] Circular Journey\t\t[ 10 ] Sparks Fly\t\t\t {colorRed}[ 14 ] The Final Sweep{colorReset}\n", colorGreen, colorReset, colorRed, colorReset)
    print(f"\t\t\t {colorGreen}[ 3 ] Lost in the Dust{colorReset}\t\t\t  [ 7 ] Dusty Detours\t\t\t[ 11 ] Dusty Roads Ahead\t\t {colorRed}[ 15 ] RoomBhie Recharged{colorReset}\n", colorGreen, colorReset, colorRed, colorReset)
    print(f"\t\t\t {colorGreen}[ 4 ] Charging Quest{colorReset}\t\t\t  [ 8 ] Swivel Shuffle\t\t\t[ 12 ] Whirling Wonders\n", colorGreen, colorReset, colorRed, colorReset)
    print("\n\n\t\t\t\t\t\t\t\t\t\t   [ 0 ] Return to Main Menu\n\t\t\t\t\t\t\t\t\t\t        Select Level: ", end="")
    level = input()
    if      (level.isdigit()):      level = int(level)

    if      (level == 0):           mainMenu()
    else:                           startLevel(0)



def startLevel(retry):
    global gameMode, inputs, indexer, codePage, startingPosition, directionFacing, mazeMap, mapSize

    gameMode = 'play'
    if level > 0 and level < 5: gameMode = 'story'

    if retry == 0:
        inputs      =   [' '] * 250
        indexer     =   0
        codePage    =   0

    if level == 1:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [1,1,0,0,0],
                            [0,0,0,0,0],
                            [1,1,1,1,2],
                            [0,0,0,0,0],   
                            [0,0,0,1,1] ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 2, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 2:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [0,0,0,0,0],
                            [1,1,1,0,0],
                            [0,0,1,0,0],
                            [0,0,1,1,2],   
                            [0,0,0,0,0]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 1, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 3:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [2,1,1,1,2],
                            [1,0,0,0,1],
                            [1,0,1,0,1],
                            [1,0,0,0,1],   
                            [2,1,1,1,2]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 2, 4 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "down"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 4:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [2,1,0,0,1],
                            [0,1,1,0,1],
                            [0,0,1,1,0],
                            [1,0,0,1,1],   
                            [1,1,0,0,1]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 4, 4 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "up"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 5:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [1,1,1,1,2],
                            [1,0,1,0,1],
                            [1,1,1,1,1],
                            [1,0,1,1,0],   
                            [1,0,0,0,0]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 4, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 6:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [1,0,1,1,1],
                            [1,1,1,0,1],
                            [1,0,0,1,1],
                            [1,0,0,1,0],   
                            [1,1,1,1,2]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 0, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 7:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [1,1,1,1,1],
                            [1,0,1,0,1],
                            [1,1,1,0,1],
                            [1,0,0,0,1],   
                            [1,1,1,0,2]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 4, 2 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "left"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 8:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 5
        mazeMap =	    [   [1,1,1,1,1],
                            [1,0,0,0,1],
                            [1,0,2,1,1],
                            [1,1,0,0,1],   
                            [0,1,1,1,1]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 3, 1 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "left"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 9:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 8
        mazeMap =	    [   [1,1,0,0,1,1,1,0],
                            [1,1,1,1,0,1,1,1],
			                [1,0,1,1,1,1,1,0],
                            [1,1,1,1,0,1,1,1],
                            [1,0,1,2,1,0,1,0],
                            [1,0,0,1,1,1,1,1],
                            [1,1,1,1,1,0,1,0],  
                            [0,1,1,0,1,1,1,2]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 0, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 10:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 8
        mazeMap =	    [   [0,1,1,1,0,1,1,0],
                            [1,1,0,1,1,1,0,0],
                            [1,0,0,1,0,1,1,1],
                            [1,1,0,0,1,1,0,1],
                            [0,1,1,2,1,0,1,1],
                            [1,1,0,0,0,0,1,0],
                            [1,0,1,0,1,1,1,1],  
                            [1,1,1,1,1,0,0,2]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 0, 1 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "down"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 11:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 8
        mazeMap =	    [   [1,0,0,0,1,1,1,1],
                            [1,1,1,1,1,0,0,1],
                            [0,1,0,1,0,0,1,1],
                            [1,1,1,0,1,1,2,1],
                            [1,1,1,3,0,1,0,1],
                            [1,0,1,0,1,1,0,1],
                            [0,0,0,0,1,1,1,1],  
                            [2,1,1,1,1,1,1,0]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 7, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 12:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 8
        mazeMap =	    [   [1,1,1,1,1,1,1,1],
                            [0,1,0,0,0,0,1,0],
                            [1,1,1,1,1,1,1,1],
                            [0,0,0,0,1,0,0,1],
                            [0,1,2,0,1,2,1,1],
                            [1,1,0,0,0,0,0,1],
                            [1,0,1,1,1,0,1,1],  
                            [1,1,1,0,1,1,1,0]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 0, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 13:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 10
        mazeMap =	    [   [0,0,0,1,1,1,1,0,0,0],
                            [1,1,1,0,0,1,1,1,2,0],
                            [1,0,1,0,1,1,0,1,1,1],
                            [1,0,1,1,1,1,0,0,1,1],
                            [1,1,0,1,1,0,0,1,0,1],
                            [0,2,0,0,0,2,1,1,1,1],
                            [1,1,0,1,1,1,1,0,1,1],
                            [1,0,0,1,0,0,1,1,0,1],
                            [1,1,0,1,1,1,1,1,1,0],
                            [0,1,1,1,1,0,0,1,1,0]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 4, 4 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "up"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 14:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 10
        mazeMap =	    [   [1,0,1,1,1,1,1,1,1,1],
                            [0,1,1,1,0,1,0,1,0,1],
                            [0,1,0,1,0,1,0,0,1,1],
                            [1,1,0,1,0,1,0,1,1,1],
                            [2,0,0,0,0,1,1,1,0,1],
                            [1,0,0,0,1,1,1,0,0,2],
                            [1,1,0,1,1,0,0,0,1,1],
                            [1,1,2,1,1,1,0,1,1,0],
                            [1,0,0,0,0,1,0,1,0,1],
                            [2,1,1,1,1,1,1,1,0,1]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 3, 5 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "down"
        '       Implement Starting Values              ';              resetPosition()

    elif level == 15:
        #  ----------------- Level Format (Start) -----------------    #      

        '       Declare Map Size & Map Layout          ';              mapSize = 10
        mazeMap =	    [   [0,1,0,0,1,1,1,2,1,1],
                            [1,2,1,0,1,0,0,0,0,1],
                            [1,0,1,1,1,1,0,1,1,1],
                            [1,1,0,1,0,1,0,1,1,0],
                            [0,1,0,1,1,1,2,1,1,0],
                            [1,1,0,0,0,0,0,0,1,0],
                            [1,0,1,1,1,1,1,0,1,1],
                            [1,1,0,1,1,0,1,0,0,1],
                            [0,1,1,1,0,0,1,1,1,1],
                            [1,1,0,1,2,0,0,0,0,0]  ]
        
        '       Declare Starting Positions             ';              startingPosition = [ 9, 0 ]
        '       Declare Starting Facing Direction      ';              directionFacing = "right"
        '       Implement Starting Values              ';              resetPosition()

    while(True):
        '       Clear Display           ';                         clearScreen()
        '       Display Title Menu      ';                         displayMenu()
        '       Display Map Layout      ';                         mapLayout(mazeMap, currentPosition, mapSize)
        '       Request Input           ';                         
        if      (inputHandler() == 'e'):                           executeCode(mazeMap, currentPosition, mapSize)

#  ----------------------------------------------- ! Boot ! -----------------------------------------------    #
if __name__ == '__main__':
    mainMenu()