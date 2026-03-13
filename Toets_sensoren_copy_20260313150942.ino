#define BLYNK_TEMPLATE_ID "TMPL5c_X2yiSz"
#define BLYNK_TEMPLATE_NAME "Toets sensoren"
#define BLYNK_AUTH_TOKEN "OhaVXALlKtoDIWjoaJ08ot0wyQofaE-Q"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "embed";
char pass[] = "weareincontrol";

// Sensor & actuators
#define DHTPIN 5        // DHT11 sensor pin
#define DHTTYPE DHT11
#define LEDPIN 2        // Ketel LED
#define POTPIN 1       // Potentiometer pin (veilig op ESP32-C6)

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// Temperatuur variabelen
float temperature;
int setTemp = 20;

// Voor hysteresis regeling
float hysteresis = 0.5;

// Laatste waarden voor synchronisatie
int lastPotTemp = -1;

BLYNK_WRITE(V3)
{
  // Slider in Blynk app verandert
  setTemp = param.asInt();
}

void sendData()
{
  // Lees temperatuur van DHT11
  temperature = dht.readTemperature();

  // Lees potentiometer
  int potValue = analogRead(POTPIN);
  int potTemp = map(potValue, 0, 4095, 0, 30);

  // Controleer of potentiometer verschilt van setTemp
  if (abs(potTemp - setTemp) > 1 && potTemp != lastPotTemp)
  {
    setTemp = potTemp;
    lastPotTemp = potTemp;
    // Update app slider
    Blynk.virtualWrite(V3, setTemp);
  }

  // Serial debug
  Serial.print("Gemeten temp: "); Serial.print(temperature);
  Serial.print(" °C, Set temp: "); Serial.print(setTemp);
  Serial.print(" °C, Pot temp: "); Serial.println(potTemp);

  // Ketel aan/uit met hysteresis
  if (temperature < setTemp - hysteresis)
    digitalWrite(LEDPIN, HIGH);
  else if (temperature > setTemp + hysteresis)
    digitalWrite(LEDPIN, LOW);

  // Stuur data naar Blynk
  Blynk.virtualWrite(V0, temperature);       // Actuele temp
  Blynk.virtualWrite(V1, setTemp);           // Gewenste temp
  Blynk.virtualWrite(V2, digitalRead(LEDPIN)); // Ketelstatus
}

void setup()
{
  Serial.begin(115200);

  pinMode(LEDPIN, OUTPUT);
  dht.begin();

  // Verbinden met Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer voor regelmatige updates
  timer.setInterval(2000L, sendData);
}

void loop()
{
  Blynk.run();
  timer.run();
}