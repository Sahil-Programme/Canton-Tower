//-----------------------------
//  PROJECT TITLE : LED TOWER
//  CREATED BY    : SAHIL YADAV
//-----------------------------
//  DATE CREATED  : 1 FEBRUARY 2020
//  DATE MODIFIED : 13 MARCH 2020

//-----------NOTE------------//
/* 
 * This code is written to create few looping animation for
 * a daisy chained LED tower. The total number of LEDs is 170
 * Type of LEDs used PL9823
 * These type of LEDs requires 5V, GND and a single data pin to run
 * Microcontroller used: arduino nano (most of the controllers can be used)
 * Any analog microphone can be used with aproprite amplifier
 */

#include <FastLED.h>  // REQUIRED LIBRARY

// this can be adjusted according to the size of your leds
#define NUM_LEDS 170  // NUMBER OF LEDS PRESENT IN THE TOWER 

#define DATA_PIN 6        // PIN DEFINITION FOR DATA(led strip)
#define MICROPHONE_PIN A3 // PIN DEFINITION FOR THE MICROPHONE FOR VU METER

CRGB leds[NUM_LEDS];  // Creating led object matrix

long stored_time = 0;        // Required to keep track of time and aadd a delay
long animation_delay = 3000; // To add a delay

void setup() {
  // initialising serial terminal
  Serial.begin(57600);    
  Serial.println("resetting");
  
  LEDS.addLeds<PL9823,DATA_PIN,RGB>(leds,NUM_LEDS); // initialising leds
  LEDS.setBrightness(255);                          // setting light brightness maximum
  FastLED.clear();  // clearing up led matrix
  FastLED.show();   // updating tower
  delay(20);

}

void loop() {

  //  ONLY UNCOMMENT ONE OF THE FOLLOWING TO ENTER THE RIGHT MODE
  //  mode_vu_meter();    //  uncomment this line if you want to use tower as a VU meter.
  //  mode_animations();  //  uncomment this line if you want to use the tower for animations.
}

void mode_vu_meter()  {
  FastLED.clear();  // clearing out the led matrix
  int H = analogRead(MICROPHONE_PIN);   // reading microphone data
  H = map(H,0,1024,0,16);   // mapping the readings appropriately

  // this loop updates the led matrix/tower in accordance to the mapped microphone readings
  for(int x=0;x<H;x++)  {
    for(int i=0;i<10;i++) {
      leds[coordinates(x,i)]=CRGB(0,255,0); // color format (R , G , B)
    }
  }
  FastLED.show(); // update and show all the leds
  delay(2);
}

void mode_animations()  {
  
  //animation 1
  /*
   * animation one is a DNA like spiral
   * the rotation speed keeps on increasing with every iteration
   */
  stored_time = millis();
  int d=100;  // update rate delay

  // this while loop acts as a delay of 3 seconds
  // using this instead of a delay is a good practice
  while((millis()-stored_time) < animation_delay) {

    // both of these loops basically turn on 1st and 5th led of every level during first update
    // and then shifts to 2nd and 6th and so on which gives the illusion of spirals
    for(int j=0;j<10;j++) {
      for(int i=0;i<16;i++) {
        for(int x = 0; x<10 ; x++) {
          leds[160+x] = CRGB(255,0,0);
        }
        leds[coordinates(i,j)] = CRGB(0,255,0); //  format of coordinates( level, number of led on that level)
                                                //  there are 16 levels and 10 leds for the crown

        int temp = j+5;
        if(temp>=10) {
          temp = temp-10;
        }
        leds[coordinates(i,temp)] = CRGB(0,255,0);
      }
      FastLED.show();
      delay(d);
      d-=1;   // this increases the speed of rotation after every update
      FastLED.clear();
    }
  }

  //animation 2
  /*
   * animation two is one color going up and down 
   */
  stored_time =millis();
  // this while loop acts as a delay of 3 seconds
  while((millis()-stored_time) < animation_delay) {

    // the following code basically turns on all the leds on each level one after the other 
    for(int x=0;x<16;x++) {
      for(int i=0;i<10;i++) {
        leds[coordinates(x,i)] = CRGB(0,0,255);
        //leds[coordinates(16-x,i)] = CRGB(255,0,0);
      }
      FastLED.show();
      delay(25);
      FastLED.clear();
    }
    for(int x=16;x>=0;x--) {
      for(int i=0;i<10;i++) {
        leds[coordinates(x,i)] = CRGB(0,0,255);
        //leds[coordinates(16-x,i)] = CRGB(255,0,0);
      }
      FastLED.show();
      delay(25);
      FastLED.clear();
    }
  }
  //animation 3
  /*
   * animation three is two color going up and down 
   * this animation is very similar to 2nd one but only has an extra ring of
   * color going in the other direction
   */
  stored_time =millis();
  // this while loop acts as a delay of 3 seconds
  while((millis()-stored_time) < animation_delay) {
    for(int x=0;x<16;x++) {
      for(int i=0;i<10;i++) {
        leds[coordinates(x,i)] = CRGB(255,0,0);
        leds[coordinates(16-x,i)] = CRGB(0,255,0);
      }
      FastLED.show();
      delay(25);
      FastLED.clear();
    }
    for(int x=16;x>=0;x--) {
      for(int i=0;i<10;i++) {
        leds[coordinates(x,i)] = CRGB(255,0,0);
        leds[coordinates(16-x,i)] = CRGB(0,255,0);
      }
      FastLED.show();
      delay(25);
      FastLED.clear();
    }
  }
}

// this function takes the level and number of led in that level as an input and outputs a single
//number which is the position of that led as the long chain
int coordinates(int level, int number) {
  int num_led = (level*10)+number;
  return num_led;
}
