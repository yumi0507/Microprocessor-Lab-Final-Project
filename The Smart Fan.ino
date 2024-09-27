#include <dht11.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include "SCoop.h" 

// LCD Display
LiquidCrystal LCD(20, 19, 18, 14, 15, 16, 17);
//                 RS, RW, EN, D4, D5, D6, D7

// Step Motor
int Step1 = 47;
int Step2 = 49;
int Step3 = 51;
int Step4 = 53;
int spd = 0;
int mode = 0;

// Temperature Sensor
dht11 DHT11;
const int DHT = A0;
int call;
int humi = 0, temp = 0;

// 4*4 Keyboard
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] =
    {{'0', '1', '2', '3'},
     {'4', '5', '6', '7'},
     {'8', '9', 'A', 'B'},
     {'C', 'D', 'E', 'F'}};
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(115200);
  // DHT
  pinMode(DHT, INPUT);

  // LCD
  LCD.begin(16, 2);
  for (int i = 14; i <= 20; i++)
    pinMode(i, OUTPUT);
  LCD.setCursor(0, 0);

  // Step Motor
  pinMode(Step1, OUTPUT);
  pinMode(Step2, OUTPUT);
  pinMode(Step3, OUTPUT);
  pinMode(Step4, OUTPUT);
}

void loop()
{
  char customKey = customKeypad.getKey();
  call = DHT11.read(DHT);
  humi = DHT11.humidity;
  temp = DHT11.temperature;
  
  LCD.setCursor(0, 0);
  LCD.print("Tem: ");
  LCD.print(temp);
  LCD.print(" Hum: ");
  LCD.print(humi);
  LCD.setCursor(0, 1);
  if (customKey)
  {
    switch (customKey)
    {
    case '0':
      spd = 0;
      mode = 0;
      break;
    case '1':
      spd = 6;
      mode = 1;
      break;
    case '2':
      spd = 5;
      mode = 2;
      break;
    case '3':
      spd = 3;
      mode = 3;
      break;
    default:
      break;
    }
  }
  LCD.print("Mode: ");
  LCD.setCursor(6, 1);
  LCD.print(mode);

  for(int i = 0; i < 10; i++){
      digitalWrite(Step1, LOW);
      digitalWrite(Step2, LOW);
      digitalWrite(Step3, LOW);
      digitalWrite(Step4, HIGH);
      delay(spd);
      digitalWrite(Step1, LOW);
      digitalWrite(Step2, LOW);
      digitalWrite(Step3, HIGH);
      digitalWrite(Step4, LOW);
      delay(spd);
      digitalWrite(Step1, LOW);
      digitalWrite(Step2, HIGH);
      digitalWrite(Step3, LOW);
      digitalWrite(Step4, LOW);
      delay(spd);
      digitalWrite(Step1, HIGH);
      digitalWrite(Step2, LOW);
      digitalWrite(Step2, LOW);
      digitalWrite(Step4, LOW);
      delay(spd);

  }
}
