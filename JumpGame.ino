// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define NEOPIXEL_PIN            7
#define RESET_BTN_PIN            3
#define PRESSURE_MAT_SWITCH_PIN            2

#define INITIAL_DELAY_VALUE       30
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      90

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);


int delayval = INITIAL_DELAY_VALUE; // delay for half a second
int q = 40;
int previousPixel = 42;
int blueVal = 5;
int redVal = 150;
int greenVal = 0;
int redChange = 0;
int greenChange = 0;
int blueChange = 0;
int redDir = -1;
int greenDir = 1;
int blueDir = 1;

int curScore = 0;
boolean gameRunning = false;
boolean jumpedAtLeastOnce = false;
boolean onMatCurrently = false;
boolean currentlyJumping = false;

int btnVal = 0;     // variable for reading the pin status
int matVal = 0;     // variable for reading the pin status

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(RESET_BTN_PIN, INPUT_PULLUP);    // declare pushbutton as input
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
  
}

void loop() {

  if (gameRunning == false) {
    btnVal = digitalRead(RESET_BTN_PIN);  // read input value
    if (btnVal == LOW) {         // check if the input is HIGH (button released)
      digitalWrite(LED_BUILTIN, LOW);  // turn LED OFF 
      gameRunning = true;   
      delayval =  INITIAL_DELAY_VALUE; 
      curScore = 1;
    } else {
      digitalWrite(LED_BUILTIN, HIGH);  // turn LED ON
    }    
    return;
  }

  if (curScore > 99) {

    while (1) {
      matrix.println(666);
      matrix.writeDisplay();
      delay(300);
      matrix.println(99999);
      matrix.writeDisplay();

      delay(300);
            
    }

  } else {
    curScore = curScore + 1;  
  }

  
   
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  if ( delayval > 2 ) {
    delayval = delayval - 1;  
  }

  blueChange = random(10,40);
  redChange = random(10,40);
  greenChange = random(10,40);

  blueVal = blueVal + (blueChange * blueDir);
  redVal = redVal + (redChange * redDir);
  greenVal = greenVal + (greenChange * greenDir);
  if (blueVal > 255) {
    blueVal = 254;
    blueDir = -1;
  }
  if (redVal > 255) {
    redVal = 254;
    redDir = -1;
  }

  if (greenVal > 255) {
    greenVal = 254;
    greenDir = -1;
  }

//
  if (blueVal < 1) {
    blueVal = 1;
    blueDir = 1;
  }
  if (redVal < 1) {
    redVal = 1;
    redDir = 1;
  }

  if (greenVal < 1) {
    greenVal = 1;
    greenDir = 1;
  }


  matrix.print(curScore * 100, DEC);
  matrix.writeDisplay();
  
  for(int i=0;i<NUMPIXELS;i=i+1){

  
    matVal = digitalRead(PRESSURE_MAT_SWITCH_PIN);  // read input value
    Serial.println('Here ');
    Serial.println(matVal);
    if (matVal == HIGH) {         // check if the input is HIGH (button pressed)
      digitalWrite(LED_BUILTIN, HIGH);  // turn LED ON
      onMatCurrently = true;
      Serial.println("Matt Pressed!");
    } else {
      digitalWrite(LED_BUILTIN, LOW);  // turn LED OFF 
      if (onMatCurrently == true) {
        jumpedAtLeastOnce = true;
        Serial.println("On Mat jumped once!");
      }
      onMatCurrently = false;
      
      
    } 
      
    if (i == 0) {
      previousPixel = NUMPIXELS - 1;
    } else {
      previousPixel = i-1;
    }

    if (i == 45) {

      if ((onMatCurrently == true) || (jumpedAtLeastOnce == false)) {
          gameRunning = false;
      } else {
        jumpedAtLeastOnce = false;
      }
      
    }
    
    pixels.setPixelColor(previousPixel, pixels.Color(0, 0 , 0 )); // Blank the one behind
    
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(redVal, greenVal ,blueVal)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}
