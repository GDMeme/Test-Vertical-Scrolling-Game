#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

#include <math.h>
#include <time.h>
#include <string.h>

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);
    srand(time(NULL));
 
    int score = 0;
    int lives = 10;
    int raw0;
    int pressed0 = 0;  // 0 means no note  
    int pressed1 = 0;  // 1 means yes note
    int pressed2 = 0;  // 2 means yes note and already hit
    int pressed3 = 0;  // 3 means yes note, already hit, and let go of key switch
    // 4 means yes note, already hit, let go of key switch, and pressed it again
    // 5 means no note and hit it

    int numberOfNotes = 0;

    bool tooEarly0 = false;
    bool tooEarly1 = false;
    bool tooEarly2 = false;
    bool tooEarly3 = false;

    bool isPressed0 = false;
    bool isPressed1 = false;
    bool isPressed2 = false;
    bool isPressed3 = false;

    InitializePin(GPIOA, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOB, GPIO_PIN_8, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);

    void turnOnOff(int abc) {
        switch (abc) {
            case 1:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, true);
                break;
            case 2:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, true);
                break;
            case 3:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, true);
                break;
            case 4:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);
                break;
            case 5:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, true);
                break;
            case 6:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, true);
                break;
            case 7:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, true);
                break;
            case 8:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, true);
                break;
            case 9:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, true);
                break;
            case 10:
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, true);
                break;
            case 11:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, true);
                break;
            case 12:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
                break;
            case 13:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true);
                break;
            case 14:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);
                break;
            case 15:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, true);
                break;
            case 16:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, true);
                break;
            case 17:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, false);
                break;
            case 18:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, false);
                break;
            case 19:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);
                break;
            case 20:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
                break;
            case 21:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, false);
                break;
            case 22:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, false);
                break;
            case 23:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, false);
                break;
            case 24:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, false);
                break;
            case 25:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, false);
                break;
            case 26:
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, false);
                break;
            case 27:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, false);
                break;
            case 28:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
                break;
            case 29:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
                break;
            case 30:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
                break;
            case 31:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
                break;
            case 32:
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);
                break;
            default:
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, false);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, false);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, false);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, false);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, false);
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, false);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, false);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);
        }
    }
    

    // initialize LEDs

    // score LEDs
    InitializePin(GPIOC, GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    // hit LED
    InitializePin(GPIOC, GPIO_PIN_11, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    // lives LEDs
    InitializePin(GPIOB, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_2, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_3, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    // initialize key switches
    InitializePin(GPIOC, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);
    InitializePin(GPIOC, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);
    InitializePin(GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);
    InitializePin(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);

    // each of the elements arrays corresponds to the pin number at the ith row/column, 0 <= i <= 7 
    int rows[8] = {8, 3, 16, 5, 9, 15, 10, 1};
    int columns[8] = {4, 11, 12, 6, 14, 7, 9, 13}; 

    // display ON LEDs on the matrix
    int refreshBoard(int onLeds[8][8][1], int numRows, int numColumns, int *numberOfNotes, int *score, int *pressed0, int *pressed1, int *pressed2, int *pressed3, bool *tooEarly0,
                    bool *tooEarly1, bool *tooEarly2, bool *tooEarly3, int *raw0, bool *isPressed0, bool *isPressed1, bool *isPressed2, bool *isPressed3){    
        int keyPresses = 0; 
        for (int i = 0; i < numRows; i++){ // i represents the rows
            for (int j = 0; j < numColumns; j++){ // j represents the columns
                if (onLeds[i][j][0] == 1){ // found an LED that's going to be on
                    if (i == 6 && j == 0){ // determining where the note is
                        *pressed0 = 1;
                    }
                    if (i == 6 && j == 1){
                        *pressed1 = 1;
                    }
                    if (i == 6 && j == 2){
                        *pressed2 = 1;                        
                    }
                    if (i == 6 && j == 3){
                        *pressed3 = 1;
                    }
                    if (*tooEarly0 == false){ // you did not hit the note too early
                        if (i == 6 && j == 0 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)) && onLeds[6][0][0] == 1 && *pressed0 == 1){ //zeroth column
                            *pressed0 = 2;
                            keyPresses += 1;
                        }
                        if (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))){ // mystery code
                            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, true);
                        }
                    } else { //you hit the note too early
                        if (i == 6 && j == 0 && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)) && onLeds[6][0][0] == 1 && *pressed0 == 1){
                            *tooEarly0 = false;
                        }
                    }
                    if (*tooEarly1 == false){
                        if (i == 6 && j == 1 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)) && onLeds[6][1][0] == 1 && *pressed1 == 1){ //first column
                            *pressed1 = 2;
                            keyPresses += 1;
                        }
                        if (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))){
                            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, true);
                        }
                    } else { 
                        if (i == 6 && j == 1 && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)) && onLeds[6][1][0] == 1 && *pressed1 == 1){
                            *tooEarly1 = false;
                        }
                    }
                    if (*tooEarly2 == false){
                        if (i == 6 && j == 2 && !(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)) && onLeds[6][2][0] == 1 && *pressed2 == 1){ //second column
                            *pressed2 = 2;
                            keyPresses += 1;
                        }
                        if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))){
                            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true);
                        }
                    } else { 
                        if (i == 6 && j == 2 && (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)) && onLeds[6][2][0] == 1 && *pressed2 == 1){
                            *tooEarly2 = false;
                        }
                    }
                    if (*tooEarly3 == false){
                        if (i == 6 && j == 3 && !(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)) && onLeds[6][3][0] == 1 && *pressed3 == 1){ //third column
                            *pressed3 = 2;
                            keyPresses += 1;
                        }
                        if (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))){
                            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, true);
                        }
                    } else { 
                        if (i == 6 && j == 3 && (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)) && onLeds[6][3][0] == 1 && *pressed3 == 1){
                            *tooEarly3 = false;
                        }
                    }
                    if (*raw0 > 1000){ // only anti mash check if difficulty is hard enough
                        if (*pressed0 == 2 && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))){ // anti mash checking
                            *pressed0 = 3;
                        }
                        if (*pressed1 == 2 && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))){
                            *pressed1 = 3;
                        }
                        if (*pressed2 == 2 && (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))){
                            *pressed2 = 3;
                        }
                        if (*pressed3 == 2 && (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))){
                            *pressed3 = 3;
                        }
                        if (*pressed0 == 3 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))){
                            *pressed0 = 4;
                        }
                        if (*pressed1 == 3 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))){
                            *pressed1 = 4;
                        }
                        if (*pressed2 == 3 && !(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))){
                            *pressed2 = 4;
                        }
                        if (*pressed3 == 3 && !(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))){
                            *pressed3 = 4;
                        }
                    }
                    if (*pressed0 == 0 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))){ // check for hitting empty lane
                        if (*isPressed0 != true){
                        *pressed0 = 5;
                        }
                    }
                    if (*pressed1 == 0 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))){
                        if (*isPressed1 != true){
                        *pressed1 = 5;
                        }
                    }
                    if (*pressed2 == 0 && !(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))){
                        if (*isPressed2 != true){
                        *pressed0 = 5;
                        }
                    }
                    if (*pressed3 == 0 && !(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))){
                        if (*isPressed3 != true){
                        *pressed0 = 5;
                        }
                    }
                    turnOnOff(columns[j]); //flicker the LEDs
                    turnOnOff(rows[i]+16);
                    /* if (true){ // this sets the LEDs to max brightness, messes up scroll speed as well
                        HAL_Delay(0.001);
                    } */
                    turnOnOff(columns[j]+16);                            
                    turnOnOff(rows[i]);
                    HAL_Delay(1);
                    (*numberOfNotes)++; // numberOfNotes does not actually represent how many notes there are, since refreshBoard is called a bunch of times
                    // a bit scuffed because numberOfNotes does not reset to 0 after each refreshBoard, so it keeps building up every time refreshBoard is called
                    // scroll speed seems to be fine though so leave it as is
                }
            }
        }
        return keyPresses;
    }

    //set all rows to HIGH   
    turnOnOff(8);
    turnOnOff(3);
    turnOnOff(16);
    turnOnOff(5);
    turnOnOff(9); 
    turnOnOff(15); 
    turnOnOff(10); 
    turnOnOff(13);

    int onLeds[8][8][1] = {
        { {0},{0},{0},{0},{0},{0},{0},{0} },
        { {0},{0},{0},{0},{0},{0},{0},{0} },
        { {0},{0},{0},{0},{0},{0},{0},{0} },
        { {0},{0},{0},{0},{0},{0},{0},{0} },
        { {0},{0},{0},{0},{0},{0},{0},{0} },
        { {0},{0},{0},{0},{0},{0},{0},{0} },
        { {0},{0},{0},{0},{0},{0},{0},{0} },
        { {0},{0},{0},{1},{0},{0},{0},{0} },
    };

    int refreshBoardScore(int onLeds[8][8][1], int numRows, int numColumns){    
        for(int i = 0; i < 70; ++i) {
            for (int i = 0; i < numRows; i++){ // i represents the rows
                for (int j = 0; j < numColumns; j++){ // j represents the columns
                    if (onLeds[i][j][0] == 1){ // found an LED that's going to be on
                        turnOnOff(columns[j]); //flicker the LEDs
                        turnOnOff(rows[i]+16);
                        turnOnOff(columns[j]+16);                            
                        turnOnOff(rows[i]);
                        HAL_Delay(1);
                    }
                }
            }
        }  
    }

    void displayDigit(int digit) {
        if(digit == 0) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 1) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 2) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{1},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 3) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 4) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 5) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 6) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{0},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 7) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{1},{1},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 8) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 9) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{1},{0},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{1},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{1},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } else if(digit == 10) {
            int digitDisplay[8][8][1] = {
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{0},{0},{0},{0},{0} },
                { {0},{0},{0},{1},{0},{0},{0},{0} },
            };
            refreshBoardScore(digitDisplay, 8, 8);
        } 
    }

    void shiftNotes() {
        // move each of the rows down one row except for the top one
        for (int c = 7; c >= 1; c--){
            for (int d = 0; d <= 7; d++){
                onLeds[c][d][0] = onLeds[c-1][d][0];
            }
        }

        // set the top row to off
        for (int e = 0; e <= 7; e++){
            onLeds[0][e][0] = 0;
        }

        // randomly generate notes at the top row
        for (int f = 0; f < 4; f++){
            int scrollSpeed = raw0/683; // raw0/683 controls the density of notes; a higher value means less dense, lower value means more dense
            if (rand()%(scrollSpeed + 2) == 1){ 
                onLeds[0][f][0] = 1;
            }
        }
    }

    while(1) // loop forever, blinking the LED
    {

        //initialize potentiometer
        __HAL_RCC_ADC1_CLK_ENABLE();        // enable ADC 1
        ADC_HandleTypeDef adcInstance;      // this variable stores an instance of the ADC
        InitializeADC(&adcInstance, ADC1);  // initialize the ADC instance
        // Enables the input pins
        // (on this board, pin A0 is connected to channel 0 of ADC1, and A1 is connected to channel 1 of ADC1)
        InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_ANALOG, GPIO_NOPULL, 0);   
        // read the ADC values (0 -> 0V, 2^12 -> 3.3V)
        raw0 = ReadADC(&adcInstance, ADC_CHANNEL_0); // raw0 is between 0 and 4096

        // setting initial conditions each time the LED moves
        pressed0 = 0;
        pressed1 = 0;
        pressed2 = 0;
        pressed3 = 0;
        tooEarly0 = false;
        tooEarly1 = false;
        tooEarly2 = false;
        tooEarly3 = false;
        numberOfNotes = 0;

        // checking whether you hit the note too early
        if (onLeds[6][0][0] == 1 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))){
            tooEarly0 = true;
        }
        if (onLeds[6][1][0] == 1 && !(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))){
            tooEarly1 = true;
        }
        if (onLeds[6][2][0] == 1 && !(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))){
            tooEarly2 = true;
        }
        if (onLeds[6][3][0] == 1 && !(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))){
            tooEarly3 = true;
        }

        // scroll speed 
        for (int b = 0; b < (100000 + (1342 * raw0)); b++){ // b value changes the scroll speed
            b = b + refreshBoard(onLeds, 8, 8, &numberOfNotes, &score, &pressed0, &pressed1, &pressed2, &pressed3, &tooEarly0, &tooEarly1, &tooEarly2, &tooEarly3, &raw0, 
            &isPressed0, &isPressed1, &isPressed2, &isPressed3)/6 + numberOfNotes*numberOfNotes*numberOfNotes/7; 
            // increases the scroll speed depending on how many key presses and ON leds within one refreshBoard
        }
        // determining the score
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, false);
        if (pressed0 == 1 || pressed0 == 4 || pressed0 == 5){
            score -= 1;
            lives -= 1;
        } else if (pressed0 == 2 || pressed0 == 3){
            score += 1;
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, true);
        }
        if (pressed1 == 1 || pressed1 == 4){
            score -= 1;
            lives -= 1;
        } else if (pressed1 == 2 || pressed1 == 3 || pressed1 == 5){
            score += 1;
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, true);
        }
        if (pressed2 == 1 || pressed2 == 4){
            score -= 1;
            lives -= 1;
        } else if (pressed2 == 2 || pressed2 == 3 || pressed2 == 5){
            score += 1;
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, true);
        }
        if (pressed3 == 1 || pressed3 == 4){
            score -= 1;
            lives -= 1;
        } else if (pressed3 == 2 || pressed3 == 3 || pressed3 == 5){
            score += 1;
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, true);
        }

        isPressed0 = false;
        isPressed1 = false;
        isPressed2 = false;
        isPressed3 = false;
        if (pressed0 == 2){
            isPressed0 = true;
        }
        if (pressed1 == 2){
            isPressed1 = true;
        }
        if (pressed2 == 2){
            isPressed2 = true;
        }
        if (pressed3 == 2){
            isPressed3 = true;
        }


        // turn on/off leds relating to score
        if (score > 0){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, true);
        } else if (score <= 0){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, false);
            score = 0;
        }
        if(score > 10) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, true);
        } else if (score <= 10){
           HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, false); 
        } 
        if(score > 20) {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, true);
            lives = 0;
        } else if (score <= 20){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, false);
        }

        // turn on/off leds relating to lives
        if (lives > 7 && lives <= 10){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, true);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, true);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, true);
        } else if (lives <= 7 && lives > 3){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, false);
        } else if (lives <= 3) {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, false);
        }
        // ending screen displaying score
        if (lives <= 0){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, false);
            // Display score on the led matrix after each game ends
            int scoreOnesDigit = score%10;
            int scoreHundredsDigit = ((score%1000) - (score%100))/100;
            int scoreTensDigit = ((score%100) - scoreOnesDigit)/10;
            HAL_Delay(500);
            // Show first, second, and third digits of the total score
            if(score > 99) {
                displayDigit(scoreHundredsDigit);
            }
            if(score > 9) {
                if(scoreTensDigit == scoreHundredsDigit) {
                    // Clear matrix for same digit
                    displayDigit(10);
                }
                displayDigit(scoreTensDigit);
            }
            if(scoreOnesDigit == scoreTensDigit) {
                // Clear matrix for same digit
                displayDigit(10);
            }
            displayDigit(scoreOnesDigit);
            break;
        } else if (lives > 0) {
            shiftNotes();
        }
    }
    
return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
