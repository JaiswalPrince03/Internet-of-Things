#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define buzzerPin 13

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
char keys [ROW_NUM] [COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte pin_rows [ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column [COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

LiquidCrystal_I2C lcd (0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

Servo myservo; // create servo object to control a servo

const String password_1 = "12345"; // change your password here


String input_password;

void setup() {

  pinMode(buzzerPin, OUTPUT);
  
  input_password.reserve (32);
  
  myservo.attach(11); // attaches the servo on pin D11 to the servo object
  
  lcd.init();
  lcd.backlight();
  lcd.print("ENTER PASSWORD");
}

void loop() {

  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    
    if(key == '*') {
      input_password = "";
      lcd.clear();
    } else if(key == '#') {
      lcd.clear();
      
      if(input_password == password_1) {
        Serial.println("password is correct");
        lcd.setCursor(0, 0);
        lcd.print("CORRECT!");
        lcd.setCursor(0, 1);
        lcd.print("DOOR UNLOCKED!");
        myservo.write(90); // move servo motor shaft at the 180-degree position
        delay(1000);
        myservo.write(0);// move servo motor shaft at the 0-degree position
      
      } else {
        Serial.println("password is incorrect, try again");
        lcd.setCursor(0, 0);
        lcd.print("INCORRECT!");
        lcd.setCursor(0, 1);
        lcd.print("ACCESS DENIED!");
        digitalWrite(buzzerPin, HIGH);
        delay(1000);
        digitalWrite(buzzerPin, LOW);
        delay(1000);
        
      }
      
      input_password = ""; // reset the input password
      
    } else {
      if(input_password.length() == 0) {
        lcd.clear();
      }
      
      input_password += key; // append new character to input password string
      
      lcd.setCursor(input_password.length(), 0); // move cursor to new position
      lcd.print('*'); // print * key as hiden character
    }
    Serial.begin(9600);

    
    
  }
}