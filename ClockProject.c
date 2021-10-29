/*
    Project - Digital clock
    Author: Anushanga Pavith
    Date: 10/29/2021
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// for position of digits
#define STARTROW 2
#define COLUMN1 2
#define COLUMN2 15
#define COLUMN3 21
#define COLUMN4 34
#define COLUMN5 40
#define DATEROW 8
#define DATECOL 22

// digit arrays
int zero[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1}
};
int one[5][6] = {
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1}
};
int two[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1}
};
int three[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1}
};
int four[5][6] = {
    {1, 1, 0, 0, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1}
};
int five[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
};
int six[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
};
int seven[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1}
};
int eight[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
};
int nine[5][6] = {
    {1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1},
};
int colon[5][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0},
};

// Global variable for colour. Default value is white.
int ansiClr = 47;

// Functions prototyping
int countArray(char[]);
int absolute(int);
int compare(char []);
void selection(int digit, int row, int col);
void printdigit(int one[5][6], int row, int col);
void clocktime();
int digitColPosition(int index);

/*
    background colours (refers to compare function and ansi background colour values)
    0 - black 40
    1 - red 41
    2 - green 42
    3 - yellow 43
    4 - blue 44
    5 - magenta 45
    6 - cyan 46
    7 - white 47
*/

int main(int argc, char *argv[])
{
    char specialArr[100];

    /*Error handelling and calling the clock*/

    if(argc == 1)
    {
        // There are only one argument. './program'
        // Start the clock
        clocktime();
    }
    else if(argv[1][0] == '-')
    {
        if(argv[1][1] == 'h')
        {
            // input -h
            printf("usage : clock -h\t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
            return 0;
        }
        else if(argv[1][1] == '\0')
        {
            //input - 
            // Start the clock
            clocktime();
        }
        else if (argv[1][1] != 'c')
        {
            // input is like -i, -s, -dsd, -wd5 ...
            printf("Invalid use of arguments.\nusage : clock -h\t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n");
            return 0;
        }
        else if (argv[1][1] == 'c')
        {
            if(argc == 2 && argv[1][2] == '\0')
            {
                // input -c (only -c )
                printf("Invalid use of arguments.\nusage : clock -h\t\tquick help on cmd\nusage : clock -c <color>\tprint clock with a color\n");
                return 0;
            }
            else if(argc == 3 && argv[1][2] == '\0')
            {
                // input -c anything

                // The colour will assign to the global variable ansiClr
                ansiClr = compare(argv[2]) + 40;
                if(ansiClr == 48)
                {
                    // if the input wasn't defined colours compare(arg[2]) will return 8. means the colour not defined
                    printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", argv[2]);
                    return 0;
                }
                // when the color is acceptable clock will begin
                else clocktime();
            }
            else
            {
                // input -cred, -cblue, -cbla_bla_bla
                for(int k = 2; argv[1][k] != '\0'; k++)
                {
                    // put the things after "-c" to an array
                    specialArr[k-2] = argv[1][k];
                }
                ansiClr = compare(specialArr) + 40;
                if(ansiClr == 48)
                {
                    printf("%s :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n", specialArr);
                    return 0;
                }
                else clocktime();
            }
        }
    }
    clocktime();

    return 0;
}

// Function for count elements in an array
int countArray(char toCount[100])
{
    int i = 0;
    while(toCount[i] != '\0')
    {
        i++;
    }
    return i;
}

// Function for calculate absolute value
int absolute(int val)
{
    if(val >= 0) return val;
    else
    {
        val = 0 - val;
        return val;
    }
}

// Function for assign colour according to the input
int compare(char arr[])
{
    char colorArr[8][8] = {
        {'b', 'l', 'a', 'c', 'k'},
        {'r', 'e', 'd'},
        {'g', 'r', 'e', 'e', 'n'},
        {'y', 'e', 'l', 'l', 'o', 'w'},
        {'b', 'l', 'u', 'e'},
        {'m', 'a', 'g', 'e', 'n', 't', 'a'},
        {'c', 'y', 'a', 'n'},
        {'w', 'h', 'i', 't', 'e'}
    };

    int i = 0;
    int retColour = 8;
    _Bool isEqual;
    for(; i < 8; i++)
    {
        if(arr[0] == colorArr[i][0] || absolute(arr[0] - colorArr[i][0]) == 32)
        {
            // If first charactors are same, then compare rest.
            isEqual = 1;
            for(int j = 0; j < countArray(arr); j++)
            {
                if(arr[j] != colorArr[i][j] && absolute(arr[j] - colorArr[i][j]) != 32)
                {
                    isEqual = 0;
                    break;
                }
            }
            // Find are there additional charactors after the name of the colour. if so, it will neglected.
            if(isEqual == 1 && arr[countArray(colorArr[i])] == '\0')
            {
                retColour = i;
            }
        }
    }
    return retColour;    
}

// Function for select the big digit array and call the print function.
void selection(int digit, int row, int col)
{
    if(digit == 0)  printdigit(zero, row, col);
    else if(digit == 1)  printdigit(one, row, col);
    else if(digit == 2)  printdigit(two, row, col);
    else if(digit == 3)  printdigit(three, row, col);
    else if(digit == 4)  printdigit(four, row, col);
    else if(digit == 5)  printdigit(five, row, col);
    else if(digit == 6)  printdigit(six, row, col);
    else if(digit == 7)  printdigit(seven, row, col);
    else if(digit == 8)  printdigit(eight, row, col);
    else if(digit == 9)  printdigit(nine, row, col);
    else if(digit == 10)  printdigit(colon, row, col);
}

// Function for print big digit. Inputs are related array, the position to be print.
void printdigit(int bignum[5][6], int row, int col)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            if(bignum[i][j] == 1)
            {
                printf("\e[%d;%df\033[1;%im \033[0m", row+i, col+j, ansiClr);
            }
            else if (bignum[i][j] == 0)
            {
                printf("\e[%d;%df ", row+i, col+j);
            }
        }
        printf("\n");
    }
}

// Function for get system time and date
void clocktime()
{
    system("stty -echo"); // Won't show user inputs while running the clock

    while(1)
    {
        time_t currentTime;
        time(&currentTime);
        char dateArr[20];
        char timeArr[20];

        struct tm *myTime = localtime(&currentTime);
        struct tm *date = localtime(&currentTime);

        strftime(dateArr, 20, "%Y-%m-%d", date);
        strftime(timeArr, 20, "%H-%M-%S", myTime);


        printf("\033[?25l"); //cursor off
        printf("\033[H\033[J"); // Clear the screen
        //printf("\033[2J"); // Clear the screen

        for(int i = 0; i < countArray(timeArr); i++)
        {
            // pass values that in time array.
            if(timeArr[i] == '-') selection(10, STARTROW, digitColPosition(i));
            else selection(timeArr[i]-48, STARTROW, digitColPosition(i));
        }

        // Print date as string.
        printf("\e[%i;%if\033[0;%im%s\033[0m\n",  DATEROW, DATECOL, ansiClr-10, dateArr);
        usleep(0.5*1000000);
        //sleep(1);
        printf("\n");
    }
}

// Function for assign the position where the digit should print
int digitColPosition(int index)
{
    if(index == 0) return (COLUMN1);
    else if(index == 1) return (COLUMN1+7);    
    else if(index == 2) return (COLUMN2);
    else if(index == 3) return (COLUMN3);
    else if(index == 4) return (COLUMN3+7); 
    else if(index == 5) return (COLUMN4);
    else if(index == 6) return (COLUMN5);
    else if(index == 7) return (COLUMN5+7);
    else return 0;    
}