/*
 * Author: Daniel Chen
 * Student Number: 43419712
 * Lab Section: L2B
 * Date: March 30 2019
 *
 * Purpose: Simon Game
 */

/* Header Files */

#include <stdio.h>
#include <stdlib.h>
#include <DAQlib.h>
#include <unistd.h>
#include <time.h>

/* Input/Output Channels */
#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define NUM_BUTTON 4

/* Other Symbolic Constants */
#define ON 1
#define OFF 0

#define LENGTH 5

#define GREEN 0
#define RED 1

#define TRUE 1
#define FALSE 0

#define ONE_SECOND 1000000

/* Function Prototypes */
void runSimon (void);
int randInt(int lower, int upper);
void generateSequence(int length, int data[]);
void guess(int guess[NUM_BUTTON], int currentState);
int readButton(void);
int check(int guess[NUM_BUTTON], int answer[LENGTH], int currentState);
void display(int answer[LENGTH], int currentState);
void flashColor(int color);


int main(void)
{
    int setupNum;
    
    printf("Enter configuration type (0 for the device or 6 for the simulator): ");
    scanf("%d", &setupNum);
    
    if (setupDAQ(setupNum) == TRUE) {
        runSimon();
    }
    else {
        printf("ERROR: Cannot initialize system\n");
    }
    
    system("PAUSE");
    return 0;
}

/*
 * Name: runSimon
 * Purpose: Run the Simon Game
 * Parameter: void
 * Return Value: void
 */
void runSimon (void)
{
    int guessNum[] = {0, 0, 0, 0, 0};
    int answer[LENGTH];
    int currentState = 1;
    
    generateSequence(LENGTH, answer);
    
    while(continueSuperLoop()){
        do {
            usleep(ONE_SECOND);
            display(answer, currentState);
            guess(guessNum, currentState);
            
            if(check(guessNum, answer, currentState) == FALSE)
            {
                flashColor(RED);
                printf("You lose!\n");
                printf("Prepare for a new game in \n");
                printf("3\n");
                usleep(ONE_SECOND);
                printf("2\n");
                usleep(ONE_SECOND);
                printf("1\n");
                usleep(ONE_SECOND);
                runSimon();
            }
            else
            {
                flashColor(GREEN);
            }
            
            currentState ++;
        } while (check(guessNum, answer, currentState) && currentState <= 5);
        
        if(currentState == 6){
            flashColor(GREEN);
            printf("You win!!\n");
            printf("Prepare for a new game in \n");
            printf("3\n");
            usleep(ONE_SECOND);
            printf("2\n");
            usleep(ONE_SECOND);
            printf("1\n");
            usleep(ONE_SECOND);
            runSimon();
        }
        
            
        
        
    }
}

/*
 * Name: generateSequence
 * Purpose: Generate the random number sequence using the randInt function and store it in an array
 * Parameter: The length of the sequence and the array that the sequence is being stored
 * Return Value: void
 */

void generateSequence(int length, int data[])
{
    int index;
    
    srand( (unsigned) time( NULL ) );
    
    for(index = 0; index < length; index++){
        
        data[index] = randInt(0, 3);
        
    }
}

/*
 * Name: randInt
 * Purpose: Generate a random number within a range
 * Parameter: The upper and lower bound for the range of random numbers
 * Return Value: the random number
 */

int randInt(int lower, int upper)
{
    int divider = upper - lower + 1;
    
    return rand() % divider;
}

/*
 * Name: guess
 * Purpose: Store the player's guess values in an array
 * Parameter: The array in which the guess values are being stored and the current state of the game
 * Return Value: void
 */

void guess(int guessNum[NUM_BUTTON], int currentState){
    
    int index;
    
    for(index = 0; index < currentState; index++){
        guessNum[index] = readButton();
    }
}

/*
 * Name: readButton
 * Purpose: Record and output the player's pressed button
            Wait until the player has pressed and released the button, then output the value
 * Parameter: void
 * Return Value: The pressed button value
 */

int readButton(void){
    
    int buttonState0 = OFF;
    int buttonState1 = OFF;
    int buttonState2 = OFF;
    int buttonState3 = OFF;
    
    do{
        
        buttonState0 = digitalRead(0);
        buttonState1 = digitalRead(1);
        buttonState2 = digitalRead(2);
        buttonState3 = digitalRead(3);
        
        while(buttonState0 == ON && buttonState1 == OFF && buttonState2 == OFF && buttonState3 == OFF){
            while(digitalRead(0) == OFF){
                return 0;
            }
        }
        
        while(buttonState0 == OFF && buttonState1 == ON && buttonState2 == OFF && buttonState3 == OFF){
            while(digitalRead(1) == OFF){
                return 1;
            }
        }
        
        while(buttonState0 == OFF && buttonState1 == OFF && buttonState2 == ON && buttonState3 == OFF){
            while(digitalRead(2) == OFF){
                return 2;
            }
        }
        
        while(buttonState0 == OFF && buttonState1 == OFF && buttonState2 == OFF && buttonState3 == ON){
            while(digitalRead(3) == OFF){
                return 3;
            }
        }
        
    }while((buttonState0 + buttonState1 + buttonState2 + buttonState3) == 0 ||
            (buttonState0 + buttonState1 + buttonState2 + buttonState3) == 1);
    
    return -1;
}

/*
 * Name: check
 * Purpose: Check if the guessed values are the same as the answers
 * Parameter: The guessed number array, the answer array, and the state the player is at currently
 * Return Value: The true / false if the guessed numbers are consistent with the answers up to the current
                 state
 */

int check(int guessNum[NUM_BUTTON], int answer[LENGTH], int currentState){
    
    int index;
    
    for(index = 0; index < currentState; index++){
        if (guessNum[index] != answer[index])
            return FALSE;
    }
    return TRUE;
}

/*
 * Name: display
 * Purpose: Display the answer values up to the current state
 * Parameter: The answer array and the state the player is at currently
 * Return Value: the pressed button value
 */

void display(int answer[LENGTH], int currentState){
    
    int index;
    
    for(index = 0; index < currentState; index ++){
        usleep(ONE_SECOND / 5);
        digitalWrite(answer[index], ON);
        usleep(ONE_SECOND / 5);
        digitalWrite(answer[index], OFF);
    }
}

/*
 * Name: flashColor
 * Purpose: Flash the specified color three times
 * Parameter: The color
 * Return Value: void
 */

void flashColor(int color){
    
    int index;
    
    for (index = 0; index < 3; index++){
        digitalWrite(color, ON);
        usleep(ONE_SECOND / 6);
        digitalWrite(color, OFF);
        usleep(ONE_SECOND / 6);
    }
}
