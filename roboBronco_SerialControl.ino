#define RX 0
#define TX 1
#define stopPin 2
#define rightPin 3
#define leftPin 4
#define forwardPin 5
#define reversePin 6
#define bumpLeftPin 8
#define bumpRightPin 7
#define startUpPin 9

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    88

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    //delay(wait);                           //  Pause for a moment
  }
}

void stopMoving();
void right(int duration);
void left(int duration);
void forward(int duration);
void reverse(int duration);
void bumpLeft(int duration);
void bumpRight(int duration);
void startUp(int duration);

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  //Serial.begin(9600);
  Serial1.begin(115200);
  pinMode(stopPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(forwardPin, INPUT_PULLUP);
  pinMode(reversePin, INPUT_PULLUP);
  pinMode(bumpLeftPin, INPUT_PULLUP);
  pinMode(bumpRightPin, INPUT_PULLUP);
  pinMode(startUpPin, INPUT_PULLUP);
  
  Serial1.print("^rwd 0_");
  Serial.print("^rwd 0_");
  Serial.print("^rwd 0_");
  delay(10);
}

/*
 * The duration variable in each of the functions is used to specify how long you want to "bumpLeft/right"
 */

void loop() {
  if(digitalRead(stopPin) == LOW){
    stopMoving();
  }

  if(digitalRead(rightPin) == LOW){
    right(0);
  }

  if(digitalRead(leftPin) == LOW){
    left(0);
  }
  
  if(digitalRead(forwardPin) == LOW){
    forward(0);
  }

  if(digitalRead(reversePin) == LOW){
    reverse(0);
  }

  if(digitalRead(bumpLeftPin) == LOW){
    bumpLeft(0);
  }

  if(digitalRead(bumpRightPin) == LOW){
    bumpRight(0);
  }

  if(digitalRead(startUpPin) == LOW){
    startUp(0);
  }
}

void stopMoving(){
  Serial1.print("!G 1 0_!G 2 0_");
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  //Serial.print("STOP\n");
  delay(10);//needed as minimum for a delay
}

void right(int duration){
  Serial1.print("!G 1 400_!G 2 -500_");
  //Serial.print("RIGHT\n");
  delay(10);//needed as minimum for a delay
}

void left(int duration){
  Serial1.print("!G 1 -400_!G 2 500_");
  //Serial.print("LEFT\n");
  delay(10);//needed as minimum for a delay
}

void forward(int duration){
  Serial1.print("!G 1 470_!G 2 550_");
  colorWipe(strip.Color(0,   0,   0), 50); // Off
  //Serial.print("FORWARD\n");
  delay(10);//needed as minimum for a delay
}

void reverse(int duration){
  //Serial.print("REVERSE\n");
  stopMoving();
  Serial1.print("!G 1 0_!G 2 -600_");
  delay(2);
  Serial1.print("!G 1 -545_!G 2 -600_");
  delay(10);//needed as minimum for a delay
}

void bumpLeft(int duration){
  //Serial.print("bumpLeft\n");
  colorWipe(strip.Color(255,   255,   255), 50); // White
  Serial1.print("!G 1 400_!G 2 700_");
  delay(70);//needed as minimum for a delay
  forward(0);
}

void bumpRight(int duration){
  //Serial.print("bumpRight\n");
  colorWipe(strip.Color(0,   255,   0), 50); // Green
  Serial1.print("!G 1 540_!G 2 390_");
  delay(70);//needed as minimum for a dela
  forward(0);
}

void startUp(int duration){
  //Serial.print("startup\n");
  Serial1.print("!G 1 0_!G 2 600_");
  delay(10);
  Serial1.print("!G 1 500_!G 2 620_");
  delay(10);
  forward(0);
}
