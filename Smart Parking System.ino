#import <LiquidCrystal.h>

#define A 1
#define B 2
#define C 3
#define D 4
#define NUMBER_OF_STEPS_PER_REV 128
int degree = 0;

int rs = 13, en = 12, d4 = A1, d5 = A2, d6 = A3, d7 = A4;
int slots[2] = { 0 };
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// int IRSensorEntrance = 7;  // connect ir sensor to arduino pin 2
// int GATE_LED = 6;
// int IRSensorExit = 5;  // connect ir sensor to arduino pin 2

int IRSensorSlot0 = 7;  // connect ir sensor to arduino D pin 7
int GATE_LED = A0;
int IRSensorSlot1 = 5;  // connect ir sensor to arduino D pin 5

int IRSensorEntrance = 0;  // connect ir sensor to arduino pin 2
// int GATE_LED = 6;
int IRSensorExit = 6;  // connect ir sensor to arduino pin 2

void setup() {

  pinMode(IRSensorEntrance, INPUT);  // sensor pin INPUT
  pinMode(IRSensorExit, INPUT);
  pinMode(GATE_LED, OUTPUT);  // Led pin OUTPUT

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);

  lcd.begin(16, 2);
}



void write(int a, int b, int c, int d) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
  digitalWrite(D, d);
}

void open() {
  // rotates clockwise

  write(1, 0, 0, 0);
  delay(3.5);
  write(1, 1, 0, 0);
  delay(3.5);
  write(0, 1, 0, 0);
  delay(3.5);
  write(0, 1, 1, 0);
  delay(3.5);
  write(0, 0, 1, 0);
  delay(3.5);
  write(0, 0, 1, 1);
  delay(3.5);
  write(0, 0, 0, 1);
  delay(3.5);
  write(1, 0, 0, 1);
  delay(3.5);
}


void close() {
  //rotates anticlockwise
  write(0, 0, 0, 1);
  delay(3.5);
  write(0, 0, 1, 1);
  delay(3.5);
  write(0, 0, 1, 0);
  delay(3.5);
  write(0, 1, 1, 0);
  delay(3.5);
  write(0, 1, 0, 0);
  delay(3.5);
  write(1, 1, 0, 0);
  delay(3.5);
  write(1, 0, 0, 0);
  delay(3.5);
  write(1, 0, 0, 1);
  delay(3.5);
}



void loop() {

  Serial.println(degree);
  int statusSensorSlot0 = digitalRead(IRSensorSlot0);
  int statusSensorSlot1 = digitalRead(IRSensorSlot1);
  int statusSensorEntrance = digitalRead(IRSensorEntrance);
  int statusSensorExit = digitalRead(IRSensorExit);
  int isGateOpen = 0;

  if (statusSensorEntrance == 0 || statusSensorExit == 0) {
    digitalWrite(GATE_LED, HIGH);  // LED High
    while (degree < NUMBER_OF_STEPS_PER_REV) {
      open();
      Serial.println(degree);
      degree++;
    }
    isGateOpen = 1;

    //OPEN GATE LCD PRINT WELCOME
  }


  else if (statusSensorEntrance == 1 && statusSensorExit == 1) {
    digitalWrite(GATE_LED, LOW);  // LED low
    //close gate
    while (degree > 0) {
      close();
      Serial.println(degree);
      degree--;
    }
    isGateOpen = 0;
  }


  for (int i = 0; i < 2; i++) {
    if (statusSensorSlot0 == 0) {
      slots[0] = 1;
    } else {
      slots[0] = 0;
    }

    if (statusSensorSlot1 == 0) {
      slots[1] = 1;
    } else {
      slots[1] = 0;
    }
  }



  lcd.setCursor(4, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  for (int i = 0; i < 2; i++) {
    lcd.print(i);
    if (slots[i] == 0)
      lcd.print("-EMPTY ");
    else {

      lcd.print("-FULL! ");
    }
  }
}