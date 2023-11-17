#include <Servo.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


 
Servo myservo1;
Servo myservo2;

char inByte;
int speed_step;
int servo_id;

void setup()
{
  Serial.begin(9600);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3C for 128x32
    // Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  delay(300);
  display.clearDisplay();
  display_string('/');
  //delay(1000);
  display.clearDisplay();

 
  
  myservo1.attach(10);
  myservo2.attach(9);

  
  speed_step = 0;
  servo_id=3;
   

}

void loop()
{
 //display.clearDisplay();

  ReadSerial();
}


// [Function] Checks to see if serial data has been recieved from the python file
void ReadSerial()
{
  if (Serial.available() > 0)
  {   char receviced_string[4]={'0','3','3','w'};
   char command = Serial.read();
   //display_string(command);
   //delay(1500);
    if (command ='a')
    {
      for (int i =0 ; command != 'z'; i++)
      { 
        display.clearDisplay();

        command = Serial.read();
      //  display_string(command);
        //delay(1500);
        receviced_string[i]= command;
        
      }
    }
    //receviced_string[0] = {'0'};
    //receviced_string[1] = {'7'};

     delay(100);
     
    servo_id = receviced_string[0] - '0';   // change datatype from char to integer
    int speed_step_first = receviced_string[1] - '0';   // change datatype from char to integer      
    int speed_step_second = receviced_string[2] - '0';   // change datatype from char to integer 

 
     
    speed_step = (speed_step_first*10)+speed_step_second;
   // display_string_lower_int(speed_step);
      if(servo_id==0)
      {
        myservo1.write(map(speed_step, 0, 40, 90, 180));     // move servo
      }
      delay(20);
      if(servo_id==1)
      {
        myservo2.write(map(speed_step, 0, 40, 0, 175));     // move servo
      }
  
  }
}






void display_string(char test)
{

  delay(100); // Pause for 2 seconds
  //display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  
  display.println(test);
  display.display();      // Show initial text
 // delay(100);

}


void display_string_lower_int(int test)
{

  delay(100); // Pause for 2 seconds
 // display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 0);
  
  display.println(test);
  display.display();      // Show initial text
 // delay(100);

}


void display_string_WAYlower_int(int test)
{

  delay(100); // Pause for 2 seconds
 // display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60, 20);
  
  display.println(test);
  display.display();      // Show initial text
 // delay(100);

}

void display_string_WAYWAYWAYlower_int(int test)
{

  delay(100); // Pause for 2 seconds
 // display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  
  display.println(test);
  display.display();      // Show initial text
 // delay(100);

}
