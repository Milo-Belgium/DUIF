int pinA = 6;
int pinB = 5;
int pinC = 2;
int pinD = 3;
int pinE = 4;
int pinF = 7;
int pinG = 8;

int knopStop = 1;
int knop1 = 9;
int knop2 = 10;
int knop3 = 12;

int fan = 11;  
int snelheid = 0;

void setup() {

  pinMode(knopStop, INPUT_PULLUP);
  pinMode(knop1, INPUT_PULLUP);
  pinMode(knop2, INPUT_PULLUP);
  pinMode(knop3, INPUT_PULLUP);

  pinMode(fan, OUTPUT);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);

  displayOff();
}

void loop() {

  if (digitalRead(knopStop) == LOW) {
    analogWrite(fan, 0);
    displayOff();
  }

  else if (digitalRead(knop1) == LOW) {
    analogWrite(fan, 64);   
    getal_1();
  }

  else if (digitalRead(knop2) == LOW) {
    analogWrite(fan, 128);  
    getal_2();
  }

  else if (digitalRead(knop3) == LOW) {
    analogWrite(fan, 255);    
    getal_3();
  }
  else {
    analogWrite(fan, 0);  
  }
}

void setFan(int snelheid) {
  analogWrite(fan, snelheid);
}


void displayOff() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}

void getal_1() {
  displayOff();
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
}

void getal_2() {
  displayOff();
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinG, HIGH);
}

void getal_3() {
  displayOff();
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinG, HIGH);
}