/*
A0		  VOL
A1		  CNY3
A2		  CNY2
A3		  CNY1
A4		  OLED_SDA
A5		  OLED_SCL

0_RX		
1_TX		
2       I_FUNCTION
3_PWM   O_MOTOR_STEP
4	      I_TRIGGER
5_PWM   
6_PWM   O_LED1
7       O_GATE1
8       O_RELAY
9_PWM   O_GATE2
10_PWM  O_LED2
11_PWM  
12      O_GATE3
13      O_LASER
*/



#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define CNY_LIMIT 600
#define MOTOR_PULSE 700
#define MOTOR_REVOLUTION 400
#define BREECHBLOCK_PULSE 2
#define MAINFPS 20
#define LEASTVOLTAGE 50
#define FUNCTIONLONG 0.5



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const unsigned char cylinder0[] PROGMEM = {
  0x00,0x07,0xE0,0x00,
  0x00,0x1F,0xF8,0x00,
  0x00,0x3C,0x3C,0x00,
  0x00,0x70,0x0E,0x00,
  0x00,0x63,0xC6,0x00,
  0x00,0x64,0x26,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x64,0x26,0x00,
  0x00,0x63,0xC6,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x60,0x06,0x00,
  0x00,0x63,0xC6,0x00,
  0x00,0x64,0x26,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x68,0x16,0x00,
  0x00,0x64,0x26,0x00,
  0x00,0x63,0xC6,0x00,
  0x00,0x70,0x0E,0x00,
  0x00,0x3C,0x3C,0x00,
  0x00,0x1F,0xF8,0x00,
  0x00,0x07,0xE0,0x00
};

const unsigned char cylinder1[] PROGMEM = {
    0x00, 0x3e, 0x00, 0x00, 
    0x00, 0xff, 0x80, 0x00, 
    0x01, 0xe3, 0xc0, 0x00, 
    0x03, 0x80, 0x60, 0x00, 
    0x03, 0x1e, 0x30, 0x00, 
    0x07, 0x21, 0x30, 0x00, 
    0x06, 0x40, 0x98, 0x00, 
    0x06, 0x40, 0x98, 0x00, 
    0x07, 0x40, 0x9c, 0x00, 
    0x03, 0x40, 0x8c, 0x00, 
    0x03, 0x21, 0x0c, 0x00, 
    0x03, 0x9e, 0x0e, 0x00, 
    0x01, 0x80, 0x06, 0x00, 
    0x01, 0x80, 0x06, 0x00, 
    0x01, 0xc0, 0x07, 0x00, 
    0x00, 0xc0, 0x03, 0x00, 
    0x00, 0xc0, 0x03, 0x00, 
    0x00, 0xe0, 0x03, 0x80, 
    0x00, 0x60, 0x01, 0x80, 
    0x00, 0x60, 0x01, 0x80, 
    0x00, 0x70, 0x79, 0xc0, 
    0x00, 0x30, 0x84, 0xc0, 
    0x00, 0x31, 0x02, 0xc0, 
    0x00, 0x39, 0x02, 0xe0, 
    0x00, 0x19, 0x02, 0x60, 
    0x00, 0x19, 0x02, 0x60, 
    0x00, 0x0c, 0x84, 0xe0, 
    0x00, 0x0c, 0x78, 0xc0, 
    0x00, 0x06, 0x01, 0xc0, 
    0x00, 0x03, 0xc7, 0x80, 
    0x00, 0x01, 0xff, 0x00, 
    0x00, 0x00, 0x7c, 0x00
};

const unsigned char cylinder2[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x07, 0x80, 0x00, 0x00, 
    0x1f, 0xf0, 0x00, 0x00, 
    0x3c, 0xfe, 0x00, 0x00, 
    0x70, 0x1f, 0xc0, 0x00, 
    0x63, 0xc3, 0xf8, 0x00, 
    0xe4, 0x20, 0x7f, 0x00, 
    0xc8, 0x10, 0x0f, 0xc0, 
    0xc8, 0x10, 0x01, 0xf0, 
    0xc8, 0x10, 0x00, 0x38, 
    0xe8, 0x10, 0x00, 0x0c, 
    0x64, 0x20, 0x03, 0xc6, 
    0x63, 0xc0, 0x04, 0x26, 
    0x30, 0x00, 0x08, 0x17, 
    0x1c, 0x00, 0x08, 0x13, 
    0x0f, 0x80, 0x08, 0x13, 
    0x03, 0xf0, 0x08, 0x13, 
    0x00, 0xfe, 0x04, 0x27, 
    0x00, 0x1f, 0xc3, 0xc6, 
    0x00, 0x03, 0xf8, 0x0e, 
    0x00, 0x00, 0x7f, 0x3c, 
    0x00, 0x00, 0x0f, 0xf8, 
    0x00, 0x00, 0x01, 0xe0, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

const unsigned char cylinder3[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x3f, 0xff, 0xff, 0xfc, 
    0x70, 0x00, 0x00, 0x0e, 
    0x63, 0xc0, 0x03, 0xc6, 
    0xe4, 0x20, 0x04, 0x27, 
    0xc8, 0x10, 0x08, 0x13, 
    0xc8, 0x10, 0x08, 0x13, 
    0xc8, 0x10, 0x08, 0x13, 
    0xc8, 0x10, 0x08, 0x13, 
    0xe4, 0x20, 0x04, 0x27, 
    0x63, 0xc0, 0x03, 0xc6, 
    0x70, 0x00, 0x00, 0x0e, 
    0x3f, 0xff, 0xff, 0xfc, 
    0x1f, 0xff, 0xff, 0xf8, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

const unsigned char cylinder4[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0xe0, 
    0x00, 0x00, 0x0f, 0xf8, 
    0x00, 0x00, 0x7f, 0x3c, 
    0x00, 0x03, 0xf8, 0x0e, 
    0x00, 0x1f, 0xc3, 0xc6, 
    0x00, 0xfe, 0x04, 0x27, 
    0x03, 0xf0, 0x08, 0x13, 
    0x0f, 0x80, 0x08, 0x13, 
    0x1c, 0x00, 0x08, 0x13, 
    0x30, 0x00, 0x08, 0x17, 
    0x63, 0xc0, 0x04, 0x26, 
    0x64, 0x20, 0x03, 0xc6, 
    0xe8, 0x10, 0x00, 0x0c, 
    0xc8, 0x10, 0x00, 0x38, 
    0xc8, 0x10, 0x01, 0xf0, 
    0xc8, 0x10, 0x0f, 0xc0, 
    0xe4, 0x20, 0x7f, 0x00, 
    0x63, 0xc3, 0xf8, 0x00, 
    0x70, 0x1f, 0xc0, 0x00, 
    0x3c, 0xfe, 0x00, 0x00, 
    0x1f, 0xf0, 0x00, 0x00, 
    0x07, 0x80, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00
};

const unsigned char cylinder5[] PROGMEM = {
    0x00, 0x00, 0x7c, 0x00, 
    0x00, 0x01, 0xff, 0x00, 
    0x00, 0x03, 0xc7, 0x80, 
    0x00, 0x06, 0x01, 0xc0, 
    0x00, 0x0c, 0x78, 0xc0, 
    0x00, 0x0c, 0x84, 0xe0, 
    0x00, 0x19, 0x02, 0x60, 
    0x00, 0x19, 0x02, 0x60, 
    0x00, 0x39, 0x02, 0xe0, 
    0x00, 0x31, 0x02, 0xc0, 
    0x00, 0x30, 0x84, 0xc0, 
    0x00, 0x70, 0x79, 0xc0, 
    0x00, 0x60, 0x01, 0x80, 
    0x00, 0x60, 0x01, 0x80, 
    0x00, 0xe0, 0x03, 0x80, 
    0x00, 0xc0, 0x03, 0x00, 
    0x00, 0xc0, 0x03, 0x00, 
    0x01, 0xc0, 0x07, 0x00, 
    0x01, 0x80, 0x06, 0x00, 
    0x01, 0x80, 0x06, 0x00, 
    0x03, 0x9e, 0x0e, 0x00, 
    0x03, 0x21, 0x0c, 0x00, 
    0x03, 0x40, 0x8c, 0x00, 
    0x07, 0x40, 0x9c, 0x00, 
    0x06, 0x40, 0x98, 0x00, 
    0x06, 0x40, 0x98, 0x00, 
    0x07, 0x21, 0x30, 0x00, 
    0x03, 0x1e, 0x30, 0x00, 
    0x03, 0x80, 0x60, 0x00, 
    0x01, 0xe3, 0xc0, 0x00, 
    0x00, 0xff, 0x80, 0x00, 
    0x00, 0x3e, 0x00, 0x00
};

// output
const int MOTOR_STEP = 3;
const int MOTOR_ENABLE = 5;
const int LED_1 = 6;
const int GATE1 = 7;
const int RELAY = 8;
const int GATE2 = 9;
const int LED_2 = 10;
const int GATE3 = 12;
const int LASER = 13;

// input
const int FUNCTION = 2;
const int TRIGGER = 4;

// analog
const int VOL = A0;
const int CNY3 = A1;
const int CNY2 = A2;
const int CNY1 = A3;
// const int SDA = A4;
// const int SCL = A5;



int functionState = 3; // light/laser setting by function key
// 0 : led off, laser off
// 1 : led off, laser on
// 2 : led on, laser off
// 3 : led on, laser on
int voltage = 0; // capacitor voltage display
int velocityCheck = 0; // for measure velocity
int triggerPushed = 0; // check trigger pushed
int functionPushed = 0; // check function pushed
int breechblockQueue = 0; // brechblock animation queue
int motorQueue = 0; // motor initiate queue
int launchQueue = 0; // launch initiate queue

unsigned long motorTime = 0;
unsigned long mainTime = 0;
unsigned long launchTime = 0;
int velocityTime = 0;



void setup() {
  pinMode(MOTOR_STEP, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(GATE1, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(GATE2, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(GATE3, OUTPUT);
  pinMode(LASER, OUTPUT);
  
  pinMode(FUNCTION, INPUT_PULLUP);
  pinMode(TRIGGER, INPUT_PULLUP);

  pinMode(VOL, INPUT);
  pinMode(CNY3, INPUT);
  pinMode(CNY2, INPUT);
  pinMode(CNY1, INPUT);

  digitalWrite(MOTOR_STEP, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(GATE1, LOW);
  digitalWrite(RELAY, HIGH);
  digitalWrite(GATE2, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(GATE3, LOW);
  digitalWrite(LASER, LOW);



  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(1000);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(13, 29);
  display.println("PrestoTheEngineer");
  display.display();

  for (int i = 0; i < 30; i++) {
    analogWrite(LED_1, i * 6 + 15);
    analogWrite(LED_2, i * 6 + 15);
    delay(50);
  }

  lightControl(launchQueue);
}

void oledDisplay(int voltage, int velocity, int functionState, int launchQueue, int* breechblockQueue) {
  char inttostring[4];

  display.clearDisplay();



  if (launchQueue >= 0) {
    sprintf(inttostring, "%3d", voltage);

    display.setTextSize(3);
    display.setCursor(6, 10);
    display.println(inttostring);

    display.setTextSize(2);
    display.setCursor(56, 24);
    display.println("/");

    display.setTextSize(1);
    display.setCursor(64, 34);
    display.println("390v");
  }

  else {
    sprintf(inttostring, "%3d", velocityTime);

    display.setTextSize(3);
    display.setCursor(6, 10);
    display.println(inttostring);

    display.setTextSize(2);
    display.setCursor(60, 24);
    display.println("m/s");
  }



  display.drawRect(4, 44, 84, 12, WHITE);
  display.fillRect(7, 47, voltage * 0.215, 6, WHITE);



  // LED default
  display.drawLine(69, 13, 90, 13, WHITE);
  display.drawLine(69, 14, 90, 14, WHITE);
  display.drawLine(81, 10, 81, 17, WHITE);
  display.drawLine(82, 10, 82, 17, WHITE);
  display.drawLine(77, 10, 77, 17, WHITE);
  display.drawLine(78, 11, 78, 16, WHITE);
  display.drawLine(79, 12, 79, 15, WHITE);

  // LED on
  if (functionState % 4 > 1) {
    display.drawLine(79, 9, 82, 6, WHITE);
    display.drawLine(80, 6, 82, 6, WHITE);
    display.drawLine(82, 8, 82, 6, WHITE);
    display.drawLine(84, 9, 87, 6, WHITE);
    display.drawLine(85, 6, 87, 6, WHITE);
    display.drawLine(87, 8, 87, 6, WHITE);
  }
  


  // laser default
  display.drawLine(97, 13, 106, 13, WHITE);
  display.drawLine(97, 14, 106, 14, WHITE);
  display.drawLine(109, 13, 112, 13, WHITE);
  display.drawLine(109, 14, 112, 14, WHITE);
  display.drawLine(110, 12, 111, 12, WHITE);
  display.drawLine(110, 15, 111, 15, WHITE);

  // laser on
  if (functionState % 2 == 1) {
    display.drawLine(110, 6, 110, 9, WHITE);
    display.drawLine(111, 6, 111, 9, WHITE);
    display.drawLine(110, 18, 110, 21, WHITE);
    display.drawLine(111, 18, 111, 21, WHITE);
    display.drawLine(115, 13, 118, 13, WHITE);
    display.drawLine(115, 14, 118, 14, WHITE);
    display.drawLine(104, 8, 106, 10, WHITE);
    display.drawLine(104, 7, 107, 10, WHITE);
    display.drawLine(105, 7, 107, 9, WHITE);
    display.drawLine(104, 19, 106, 17, WHITE);
    display.drawLine(104, 20, 107, 17, WHITE);
    display.drawLine(105, 20, 107, 18, WHITE);
    display.drawLine(114, 9, 116, 7, WHITE);
    display.drawLine(114, 10, 117, 7, WHITE);
    display.drawLine(115, 10, 117, 8, WHITE);
    display.drawLine(114, 18, 116, 20, WHITE);
    display.drawLine(114, 17, 117, 20, WHITE);
    display.drawLine(115, 17, 117, 19, WHITE);
  }
  


  if (*breechblockQueue > BREECHBLOCK_PULSE * 4) {
    display.drawBitmap(92, 28, cylinder1, 32, 32, WHITE);
  }

  else if (*breechblockQueue > BREECHBLOCK_PULSE * 3) {
    display.drawBitmap(92, 28, cylinder2, 32, 32, WHITE);
  }

  else if (*breechblockQueue > BREECHBLOCK_PULSE * 2) {
    display.drawBitmap(92, 28, cylinder3, 32, 32, WHITE);
  }

  else if (*breechblockQueue > BREECHBLOCK_PULSE * 1) {
    display.drawBitmap(92, 28, cylinder4, 32, 32, WHITE);
  }

  else if (*breechblockQueue > BREECHBLOCK_PULSE * 0) {
    display.drawBitmap(92, 28, cylinder5, 32, 32, WHITE);
  }

  else {
    display.drawBitmap(92, 28, cylinder0, 32, 32, WHITE);
  }

  if (*breechblockQueue > 0) { (*breechblockQueue)--; }
  
  

  display.display();
}

void motorMove(int motorQueue) {
  if (motorQueue % 2 == 0) { digitalWrite(MOTOR_STEP, HIGH); }
  else { digitalWrite(MOTOR_STEP, LOW); }
}

void lightControl(int launchQueue) {
  digitalWrite(LASER, functionState % 2);

  if (functionState % 4 > 1) {
    if (launchQueue == 0) {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
    }

    else if (launchQueue < 0) {
      analogWrite(LED_1, launchQueue * 8 + 255);
      analogWrite(LED_2, launchQueue * 8 + 255);
    }

    else if (launchQueue % 10 < 5) {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
    }

    else {
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, HIGH);
    }
    
  }

  else {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
  }
}

int launch(int* velocityTime) {
  // Stage_1
  digitalWrite(GATE1, HIGH); // gate 1 on
  launchTime = millis();
  while (digitalRead(CNY1) == LOW) { // (analogRead(CNY1) < CNY_LIMIT) {
    if (millis() - launchTime > 500) { // projectile stuck or empty
        digitalWrite(GATE1, LOW);
        return 9;
    }
  }
  launchTime = millis();
  while (digitalRead(CNY1) == HIGH) {
    if (millis() - launchTime > 500) { // projectile stuck or empty
      return 39;
    }
  }
  digitalWrite(GATE1, LOW); // gate 1 off
  digitalWrite(LED_1, LOW);



  // Stage_2
  digitalWrite(GATE2, HIGH); // gate 2 on
  launchTime = millis();
  while (digitalRead(CNY2) == LOW) { // (analogRead(CNY2) < CNY_LIMIT) {
    if (millis() - launchTime > 500) { // projectile stuck or empty
      digitalWrite(GATE2, LOW);
      return 19;
    }
  }
  launchTime = millis();
  while (digitalRead(CNY2) == HIGH) {
    if (millis() - launchTime > 500) { // projectile stuck or empty
      return 49;
    }
  }
  digitalWrite(GATE2, LOW); // gate 2 off
  digitalWrite(LED_2, LOW);
  unsigned long tempTime = micros();



  // Stage_3
  digitalWrite(GATE3, HIGH); // gate 3 on
  launchTime = millis();
  while (digitalRead(CNY3) == LOW) { // (analogRead(CNY3) < CNY_LIMIT) {
    if (millis() - launchTime > 500) { // projectile stuck or empty
      digitalWrite(GATE3, LOW);
      return 29;
    }
  }
  launchTime = millis();
  while (digitalRead(CNY1) == HIGH) {
    if (millis() - launchTime > 500) { // projectile stuck or empty
      return 59;
    }
  }
  digitalWrite(GATE3, LOW); // gate 3 off
  (*velocityTime) = micros() - tempTime;

  breechblockQueue += (BREECHBLOCK_PULSE * 4);
  motorQueue += (MOTOR_REVOLUTION / 2);

  return -30;
}



void loop() {
  if ((micros() - motorTime) >= MOTOR_PULSE) { // for motor pulse
    // Motor control
    if (motorQueue > 0) {
      motorMove(motorQueue);
      motorQueue--;
    }



    if ((micros() - mainTime) >= (1000000 / MAINFPS)) { // for main FPS
      // Trigger Control
      if ((digitalRead(TRIGGER) == LOW) && (triggerPushed == 0) && (analogRead(VOL) > (LEASTVOLTAGE * 2.5))) { // push
        digitalWrite(RELAY, LOW);
        launchQueue = launch(&velocityTime);
        triggerPushed++;
        digitalWrite(RELAY, HIGH);
      }

      else if ((digitalRead(TRIGGER) == HIGH) && (triggerPushed > 0)) { // pull
        triggerPushed = 0;
      }


      // Function Control
      if (digitalRead(FUNCTION) == LOW) { // push
        functionPushed++;
      }

      else if (functionPushed > 0) { // pull (short)
        if ((functionPushed < (MAINFPS * FUNCTIONLONG))) {
          motorQueue += MOTOR_REVOLUTION;
        }
        
        functionPushed = 0;
      }

      if (functionPushed == (MAINFPS * FUNCTIONLONG)) { // pushed (long)
        functionState++;
      }



      lightControl(launchQueue);
      oledDisplay(analogRead(VOL) * 0.4, 186000 / velocityTime, functionState, launchQueue, &breechblockQueue);

      if (launchQueue > 0) { launchQueue--; }
      else if (launchQueue < 0) { launchQueue++; }

      mainTime = micros();
    }

    motorTime = micros();
  }
}

