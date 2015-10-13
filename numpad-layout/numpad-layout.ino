//By William Tavares

#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 6   // can be a digital pin
#define XP 7   // can be a digital pin

short TS_MINX = 150;
short TS_MINY = 120;
short TS_MAXX = 850;
short TS_MAXY = 891; 

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
// optional
#define LCD_RESET A4 

//Color Definitons
#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0

#define MINPRESSURE 1
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
// Pins A2-A6
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364); 

//2.4 = 240 x 320
//Height 319 to fit on screen

//Size of key containers 70px
#define BOXSIZE 70

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

  //Container variables for touch coordinates
  int X, Y, Z;
  
  //Screen height without hidden pixel
  double tHeight = tft.height()-1;
  //Centering the mid square
  double center = (tft.width()/2)-(BOXSIZE/2);
  //Space between squares
  double padding = 10;
  //Position of squares to the left and right of center
  double fromCenter = BOXSIZE + padding;
  //Second row Y-Axis position
  double secondRow = BOXSIZE + padding;
  //Third row Y-Axis position
  double thirdRow = secondRow + BOXSIZE + padding;
  //Fourth row Y-Axis position
  double fourthRow = thirdRow + BOXSIZE + padding;
  //Y-Axis align for all squares
  double verticalAlign = (tHeight-((BOXSIZE * 4)+(padding * 3)))/2;
  //Left column starting x posision
  double leftColPositionX = center - fromCenter;
  //Mid column starting x posision
  double midColPositionX = center;
  //Right column starting x posision
  double rightColPositionX = center + fromCenter;

void setup() {  
  Serial.begin(9600);

  tft.reset();  
  uint16_t identifier = tft.readID();
  Serial.println(identifier, HEX);
  tft.begin(identifier);

  tft.fillScreen(BLACK);

  //(initial x,initial y,width,height,color)
  //First Row
  tft.drawRect(leftColPositionX, verticalAlign, BOXSIZE, BOXSIZE, WHITE);
  tft.drawRect(midColPositionX, verticalAlign, BOXSIZE, BOXSIZE, WHITE);
  tft.drawRect(rightColPositionX, verticalAlign, BOXSIZE, BOXSIZE, WHITE);

  //Second Row
  tft.drawRect(leftColPositionX, secondRow + verticalAlign, BOXSIZE, BOXSIZE, CYAN);
  tft.drawRect(midColPositionX, secondRow + verticalAlign, BOXSIZE, BOXSIZE, CYAN);
  tft.drawRect(rightColPositionX, secondRow + verticalAlign, BOXSIZE, BOXSIZE, CYAN);

  //Third Row
  tft.drawRect(leftColPositionX, thirdRow + verticalAlign, BOXSIZE, BOXSIZE, GREEN);
  tft.drawRect(midColPositionX, thirdRow + verticalAlign, BOXSIZE, BOXSIZE, GREEN);
  tft.drawRect(rightColPositionX, thirdRow + verticalAlign, BOXSIZE, BOXSIZE, GREEN);

  //Fourth Row
  tft.drawRect(leftColPositionX, fourthRow + verticalAlign, (BOXSIZE*2)+padding, BOXSIZE, RED);
  tft.drawRect(rightColPositionX, fourthRow + verticalAlign, BOXSIZE, BOXSIZE, RED);
}

void loop() {
  retrieveTouch();

  if(Z > MINPRESSURE && Z < MAXPRESSURE){
    //Check if element clicked is in left column
    if(X > leftColPositionX && X < (leftColPositionX+BOXSIZE)){
      //Check if element clicked is in row 1
      if(Y > verticalAlign && Y < (verticalAlign + BOXSIZE)){
           Serial.println("1");
           delay(150); 
      }
      //Check if element clicked is in row 2
      else if(Y > verticalAlign && Y < (secondRow + BOXSIZE)){
           Serial.println("4");
           delay(150); 
      }
      //Check if element clicked is in row 3
      else if(Y > verticalAlign && Y < (thirdRow + BOXSIZE)){
           Serial.println("7");
           delay(150); 
      }
      //Check if element clicked is in row 4
      else if(Y > verticalAlign && Y < (fourthRow + BOXSIZE)){
           Serial.println("0");
           delay(150); 
      }
       //Check if element clicked is in mid column
    } else if (X > midColPositionX && X < (midColPositionX+BOXSIZE)){
      //Check if element clicked is in row 1
      if(Y > verticalAlign && Y < (verticalAlign + BOXSIZE)){
           Serial.println("2");
           delay(150); 
      }
      //Check if element clicked is in row 2
      else if(Y > verticalAlign && Y < (secondRow + BOXSIZE)){
           Serial.println("5");
           delay(150); 
      }
      //Check if element clicked is in row 3
      else if(Y > verticalAlign && Y < (thirdRow + BOXSIZE)){
           Serial.println("8");
           delay(150); 
      }
      //Check if element clicked is in row 4
      else if(Y > verticalAlign && Y < (fourthRow + BOXSIZE)){
           Serial.println("0");
           delay(150); 
      }
      //Check if element clicked is in third column
    } else if (X > rightColPositionX && X < (rightColPositionX+BOXSIZE)){
      //Check if element clicked is in row 1
      if(Y > verticalAlign && Y < (verticalAlign + BOXSIZE)){
           Serial.println("3");
           delay(150); 
      }
      //Check if element clicked is in row 2
      else if(Y > verticalAlign && Y < (secondRow + BOXSIZE)){
           Serial.println("6");
           delay(150); 
      }
      //Check if element clicked is in row 3
      else if(Y > verticalAlign && Y < (thirdRow + BOXSIZE)){
           Serial.println("9");
           delay(150); 
      }
      //Check if element clicked is in row 3
      else if(Y > verticalAlign && Y < (fourthRow + BOXSIZE)){
           Serial.println(".");
           delay(150); 
      }
    }
  }
}

void retrieveTouch()
{
    digitalWrite(13, HIGH); 
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    //If sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT); 
    pinMode(YP, OUTPUT); 
  
    //Scale from 0->1023 to tft.width
    X = map(p.x, TS_MAXX, TS_MINX, 0, tft.width());
    Y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());
    Z = p.z;
}
