// Sample code for ECE 198

// Written by Bernie Roehl, August 2021

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:

#define BUTTON_BLINK
//#define LIGHT_SCHEDULER
// #define TIME_RAND
// #define KEYPAD
// #define KEYPAD_CONTROL
// #define SEVEN_SEGMENT
// #define KEYPAD_SEVEN_SEGMENT
// #define COLOR_LED
// #define ROTARY_ENCODER
// #define ANALOG
// #define PWM

#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

#include <math.h>
#include <time.h>

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);
    srand(time(NULL));
    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

#ifdef BUTTON_BLINK
    
    // Wait for the user to push the blue button, then blink the LED.   
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
    InitializePin(GPIOA, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    InitializePin(GPIOC, GPIO_PIN_10, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);

    // initialize key switches
    InitializePin(GPIOC, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);
    InitializePin(GPIOC, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);
    InitializePin(GPIOB, GPIO_PIN_0, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);
    InitializePin(GPIOA, GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0);
    //InitializePin(GPIOC, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, 0); //this is the onboard button



    //bool useDelay = true; // probably not possible to implement this
    int scrollSpeed = 0;

    // each of the elements arrays corresponds to the pin number at the ith row/column, 0 <= i <= 7 
    int rows[8] = {8, 3, 16, 5, 9, 15, 10, 1};
    int columns[8] = {4, 11, 12, 6, 14, 7, 9, 13}; 


    int refreshBoard(int onLeds[8][8][1], int numRows, int numColumns, int *numberOfNotes, int *score, int *pressed0, int *pressed1, int *pressed2, int *pressed3, bool *tooEarly0,
                    bool *tooEarly1, bool *tooEarly2, bool *tooEarly3){    
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
/*     onLeds = { {{1}{0}{0}}
               {{0}{1}{0}}
               {{0}{0}{1}} }
               scroll delay
    onLeds = { {{0}{0}{0}}
               {{1}{0}{0}}
               {{0}{1}{0}} }
                scroll delay
    onLeds = { {{0}{0}{0}}
               {{0}{0}{0}}
               {{1}{0}{0}} } */


    /* void cycleLeds(int onLeds[][2], int numLeds) {
            
        for(int i = 0; i < numLeds; ++i) {
            
            // turn on 0,0 and 0,6
            
            if(useDelay) {
                for (int j=0; j < scrollSpeed; ++j) {
                    a(columns[onLeds[i][0]]);
                    a(rows[onLeds[i][1]]+16);
                    a(columns[onLeds[i][0]]+16);
                    a(rows[onLeds[i][1]]);
                    HAL_Delay(1);
                }
            }
            
            a(columns[onLeds[i][0]]+16);
            a(rows[onLeds[i][1]]);
            if(useDelay) {
                HAL_Delay(scrollSpeed);
            } 
        }
    } */
    
    // wait for button press (active low)
    //while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
/*     while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5))
    {
    } */

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

    int score = 0;

    int pressed0 = 0;  // 0 means no note  
    int pressed1 = 0;  // 1 means yes note
    int pressed2 = 0;  // 2 means yes note and already hit
    int pressed3 = 0;

    bool tooEarly0 = false;
    bool tooEarly1 = false;
    bool tooEarly2 = false;
    bool tooEarly3 = false;

    int numberOfNotes = 0;

    while (1) // loop forever, blinking the LED
    {
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

        //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
        //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, true);
        //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, true);

        //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, false);
        
        //HAL_Delay(10);  // 250 milliseconds == 1/4 second
        //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        //HAL_Delay(10);
        //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);

// column is power 4 11 12 6 14 7
// row is ground 8 3 16 5 9 15 10
// broken column or row pins 13 2 1
        

       /* // cycle through rows
        for(int i = 0; i < 7; ++i) {
            a(rows[i]+16);
            // cycle through columns
            for(int j = 0; j < 6; ++j) {
                a(columns[j]);
                if(useDelay) {
                    HAL_Delay(scrollSpeed);
                }
                a(columns[j]+16);
            }
            a(rows[i]);
            if(useDelay) {
                HAL_Delay(scrollSpeed);
            }
        } */
        
        //int onLeds[][2] = {{1,0}, {1,1}, {1,2}, {1, 3}, {1,4}, {1,5}, {0,6}, {2,6}};
        
        
        //int arrayNum = 0;
        //int onLeds[7][2];
        /* witch(arrayNum) {
            case 0:
                onLeds = {{1,0}, {1,1}, {1,2}, {1, 3}, {1,4}, {1,5}, {1,6}};
                break;
            case 1:
                onLeds = {{0,0}, {0,1}, {0,2}, {0, 3}, {0,4}, {0,5}, {0,6}}
                break;
            case 2:
                onLeds = {{3,0}, {3,1}, {3,2}, {3, 3}, {3,4}, {3,5}, {3,6}}
                break;
            case 3:
                onLeds = {{2,0}, {2,1}, {2,2}, {2, 3}, {2,4}, {2,5}, {2,6}}
                break;
            default:
                onLeds = {{1,0}, {1,1}, {1,2}, {1, 3}, {1,4}, {1,5}, {1,6}};
        } */
        //int onLeds[][2] = {{arrayNum,0}, {arrayNum,1}, {arrayNum,2}, {arrayNum, 3}, {arrayNum,4}, {arrayNum,5}, {arrayNum,6}};
        
        
        
        /* int onLeds2[][2] = {{0,0}, {0,1}, {0,2}, {0, 3}, {0,4}, {0,5}, {0,6}};
        int onLeds3[][2] = {{3,0}, {3,1}, {3,2}, {3, 3}, {3,4}, {3,5}, {3,6}};
        int onLeds4[][2] = {{2,0}, {2,1}, {2,2}, {2, 3}, {2,4}, {2,5}, {2,6}}; */
        //scrollSpeed = 20;
        
        //arrayNum = rand()%4;
        //arrayNum = 3;
        //cycleLeds(onLeds, 7);



        /* if (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0))){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, true);
            onLeds[6][0][0] = 1;
            HAL_Delay(1);
        }
        if (!(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, true);
            onLeds[6][1][0] = 1;
            HAL_Delay(1);
        }
        if (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0))){
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, true);
            onLeds[6][2][0] = 1;
            HAL_Delay(1);
        }
        if (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4))){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, true);
            onLeds[6][3][0] = 1;
            HAL_Delay(1);
        } */
        
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

        // scroll speed stuff 
        scrollSpeed = 5500000; // make this depend on potentiometer if possible, this speed is fine maybe a bit fast
        for (int b = 0; b < scrollSpeed; b++){ // b value changes the scroll speed
            b = b + refreshBoard(onLeds, 8, 8, &numberOfNotes, &score, &pressed0, &pressed1, &pressed2, &pressed3, &tooEarly0, &tooEarly1, &tooEarly2, &tooEarly3)/6 
            + numberOfNotes*numberOfNotes*numberOfNotes/7; // increases the scroll speed depending on how many key presses and ON leds within one refreshBoard
        }
        
        // determining the score
        if (pressed0 == 1){
            score -= 1;
        } else if (pressed0 == 2){
            score += 1;
        }
        if (pressed1 == 1){
            score -= 1;
        } else if (pressed1 == 2){
            score += 1;
        }
        if (pressed2 == 1){
            score -= 1;
        } else if (pressed2 == 2){
            score += 1;
        }
        if (pressed3 == 1){
            score -= 1;
        } else if (pressed3 == 2){
            score += 1;
        }
         
 /*        char str[100];
        sprintf(str, "value of score", score);
        // lu == "long unsigned", ld = "long decimal", where "long" is 32 bit and "decimal" implies signed
        puts(str); // transmit the buffer to the host computer's serial monitor in VSCode/PlatformIO
 */

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
            if (rand()%6 == 1){ //this 4 controls the density of notes; higher means less dense, lower means more dense
                onLeds[0][f][0] = 1;
            }
        }

        // turn on/off leds relating to score
        if (score > 0){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, true);
        } else if (score <= 0){
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, false); 
            score = 0;
        }

        HAL_Delay(rand()%50);
        
        //onLeds[6][i][0]

        //HAL_Delay(400);
        //HAL_Delay(0.1);

        //a(8+16);
        //a(3);
        //a(16);
        //a(5);
        //a(9);
        //a(15);
        //a(10);

        /* BROKEN PINS */
        //Cols 7 and 8
        //a(1);
        //a(2);
        //Row 8
        //a(13);
    }
                    
    
#endif

#ifdef LIGHT_SCHEDULER
    // Turn on the LED five seconds after reset, and turn it off again five seconds later.

    while (true) {
        uint32_t now = HAL_GetTick();
        if (now > 5000 && now < 10000)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);   // turn on LED
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);  // turn off LED
    }
#endif

#ifdef TIME_RAND
    // This illustrates the use of HAL_GetTick() to get the current time,
    // plus the use of random() for random number generation.
    
    // Note that you must have "#include <stdlib.h>"" at the top of your main.c
    // in order to use the srand() and random() functions.

    // while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press
    // srand(HAL_GetTick());  // set the random seed to be the time in ms that it took to press the button
    // if the line above is commented out, your program will get the same sequence of random numbers
    // every time you run it (which may be useful in some cases)

    while (true) // loop forever
    {
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button press

        // Display the time in milliseconds along with a random number.
        // We use the sprintf() function to put the formatted output into a buffer;
        // see https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm for more
        // information about this function
        char buff[100];
        sprintf(buff, "Time: %lu ms   Random = %ld\r\n", HAL_GetTick(), random());
        // lu == "long unsigned", ld = "long decimal", where "long" is 32 bit and "decimal" implies signed
        SerialPuts(buff); // transmit the buffer to the host computer's serial monitor in VSCode/PlatformIO

        while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button to be released
    }
#endif

#ifdef KEYPAD
    // Read buttons on the keypad and display them on the console.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        SerialPutc(keypad_symbols[ReadKeypad()]);  // look up its ASCII symbol and send it to the hsot
        while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef KEYPAD_CONTROL
    // Use top-right button on 4x4 keypad (typically 'A') to toggle LED.

    InitializeKeypad();
    while (true)
    {
        while (ReadKeypad() < 0);   // wait for a valid key
        int key = ReadKeypad();
        if (key == 3)  // top-right key in a 4x4 keypad, usually 'A'
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);   // toggle LED on or off
         while (ReadKeypad() >= 0);  // wait until key is released
    }
#endif

#ifdef SEVEN_SEGMENT
    // Display the numbers 0 to 9 inclusive on the 7-segment display, pausing for a second between each one.
    // (remember that the GND connection on the display must go through a 220 ohm current-limiting resistor!)
    
    Initialize7Segment();
    while (true)
        for (int i = 0; i < 10; ++i)
        {
            Display7Segment(i);
            HAL_Delay(1000);  // 1000 milliseconds == 1 second
        }
#endif

#ifdef KEYPAD_SEVEN_SEGMENT
    // Combines the previous two examples, displaying numbers from the keypad on the 7-segment display.

    // this string contains the symbols on the external keypad
    // (they may be different for different keypads)
    char *keypad_symbols = "123A456B789C*0#D";
    // note that they're numbered from left to right and top to bottom, like reading words on a page

    InitializeKeypad();
    Initialize7Segment();
    while (true)
    {
        int key = ReadKeypad();
        if (key >= 0)
            Display7Segment(keypad_symbols[key]-'0');  // tricky code to convert ASCII digit to a number
    }
#endif

#ifdef COLOR_LED
    // Cycle through all 8 possible colors (including off and white) as the on-board button is pressed.
    // This example assumes that the color LED is connected to pins D11, D12 and D13.

    // Remember that each of those three pins must go through a 220 ohm current-limiting resistor!
    // Also remember that the longest pin on the LED should be hooked up to GND.

    InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize color LED output pins
    while (true) {
        for (int color = 0; color < 8; ++color) {
            // bottom three bits indicate which of the three LEDs should be on (eight possible combinations)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, color & 0x01);  // blue  (hex 1 == 0001 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, color & 0x02);  // green (hex 2 == 0010 binary)
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, color & 0x04);  // red   (hex 4 == 0100 binary)

            while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));   // wait for button press 
            while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // wait for button release
        }
    }
#endif

#ifdef ROTARY_ENCODER
    // Read values from the rotary encoder and update a count, which is displayed in the console.

    InitializePin(GPIOB, GPIO_PIN_5, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize CLK pin
    InitializePin(GPIOB, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, 0);   // initialize DT pin
    InitializePin(GPIOB, GPIO_PIN_10, GPIO_MODE_INPUT, GPIO_PULLUP, 0);  // initialize SW pin
    
    bool previousClk = false;  // needed by ReadEncoder() to store the previous state of the CLK pin
    int count = 0;             // this gets incremented or decremented as we rotate the encoder

    while (true)
    {
        int delta = ReadEncoder(GPIOB, GPIO_PIN_5, GPIOB, GPIO_PIN_4, &previousClk);  // update the count by -1, 0 or +1
        if (delta != 0) {
            count += delta;
            char buff[100];
            sprintf(buff, "%d  \r", count);
            SerialPuts(buff);
        }
        bool sw = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);  // read the push-switch on the encoder (active low, so we invert it using !)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, sw);  // turn on LED when encoder switch is pushed in
    }
#endif

#ifdef ANALOG
    // Use the ADC (Analog to Digital Converter) to read voltage values from two pins.

    __HAL_RCC_ADC1_CLK_ENABLE();        // enable ADC 1
    ADC_HandleTypeDef adcInstance;      // this variable stores an instance of the ADC
    InitializeADC(&adcInstance, ADC1);  // initialize the ADC instance
    // Enables the input pins
    // (on this board, pin A0 is connected to channel 0 of ADC1, and A1 is connected to channel 1 of ADC1)
    InitializePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_MODE_ANALOG, GPIO_NOPULL, 0);   
    while (true)
    {
        // read the ADC values (0 -> 0V, 2^12 -> 3.3V)
        uint16_t raw0 = ReadADC(&adcInstance, ADC_CHANNEL_0);
        uint16_t raw1 = ReadADC(&adcInstance, ADC_CHANNEL_1);

        // print the ADC values
        char buff[100];
        sprintf(buff, "Channel0: %hu, Channel1: %hu\r\n", raw0, raw1);  // hu == "unsigned short" (16 bit)
        SerialPuts(buff);
    }
#endif

#ifdef PWM
    // Use Pulse Width Modulation to fade the LED in and out.
    uint16_t period = 100, prescale = 16;

    __TIM2_CLK_ENABLE();  // enable timer 2
    TIM_HandleTypeDef pwmTimerInstance;  // this variable stores an instance of the timer
    InitializePWMTimer(&pwmTimerInstance, TIM2, period, prescale);   // initialize the timer instance
    InitializePWMChannel(&pwmTimerInstance, TIM_CHANNEL_1);          // initialize one channel (can use others for motors, etc)

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2); // connect the LED to the timer output

    while (true)
    {
        // fade the LED in by slowly increasing the duty cycle
        for (uint32_t i = 0; i < period; ++i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
        // fade the LED out by slowly decreasing the duty cycle
        for (uint32_t i = period; i > 0; --i)
        {
            SetPWMDutyCycle(&pwmTimerInstance, TIM_CHANNEL_1, i);
            HAL_Delay(5);
        }
    }
#endif
    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
