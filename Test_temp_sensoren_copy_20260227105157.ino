#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

Adafruit_BMP280 bmp;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int lm335Pin = A0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 niet gevonden!");
    while (1);
  }

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Thermometer");
  delay(2000);
  lcd.clear();
}

void loop() {

  // ===== BINNEN (BMP280) =====
  float tempBinnen = bmp.readTemperature();

  // ===== BUITEN (LM335 analoog) =====
  int raw = analogRead(lm335Pin);

  float voltage = raw * (5.0 / 1023.0);
  float tempBuiten = (voltage * 100.0) - 273.15;

  // ===== SERIAL =====
  Serial.print("Binnen: ");
  Serial.print(tempBinnen);
  Serial.print(" C  |  Buiten: ");
  Serial.print(tempBuiten);
  Serial.println(" C");

  // ===== LCD =====
  lcd.setCursor(0, 0);
  lcd.print("Binnen:");
  lcd.print(tempBinnen, 1);
  lcd.print((char)223);
  lcd.print("C  ");

  lcd.setCursor(0, 1);
  lcd.print("Buiten:");
  lcd.print(tempBuiten, 1);
  lcd.print((char)223);
  lcd.print("C  ");

  delay(2000);
}