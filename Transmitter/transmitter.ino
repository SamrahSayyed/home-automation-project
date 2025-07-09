#define BLYNK_TEMPLATE_ID           "xxx"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "xxx" 
#define BLYNK_PRINT Serial

#include <RH_ASK.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char *cmd_on = "FAN_ON";
const char *cmd_off = "FAN_OFF";

RH_ASK driver(2000, D1, D3); 

// ----- Blynk credentials -----
char auth[] = "xxx";
char ssid[] = "wifi_name";
char pass[] = "password";

// ----- Sensor Pins -----
#define PIR_PIN D5
#define DHTPIN D7
#define DHTTYPE DHT11
#define MQ2_PIN A0

// ----- OLED -----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ----- Objects -----
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  pinMode(PIR_PIN, INPUT);
  dht.begin();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while(1);
  }

  if (!driver.init()) {
    Serial.println("Transmitter init failed");
  }
  pinMode(D8,INPUT);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V0)
{
  if (param.asInt() == 1)
  {
    driver.send((uint8_t *)cmd_on, strlen(cmd_on));
    driver.waitPacketSent();
    Serial.println("Signal Sent: FAN_ON");
  }
  else
  {
    driver.send((uint8_t *)cmd_off, strlen(cmd_off));
    driver.waitPacketSent();
    Serial.println("Signal Sent: FAN_OFF");
  }
}

void loop() {
  Blynk.run();

  // Read sensors
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  int gasValue = analogRead(MQ2_PIN);
  bool motion = digitalRead(PIR_PIN);
  int light_low = digitalRead(D8);

  if (light_low == 0)
  {
    Serial.println("Light is too low");
  }

  // --- Display on OLED ---
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: "); display.print(temp); display.println(" C");
  display.print("Humidity: "); display.print(humid); display.println(" %");
  display.print("Gas: "); display.println(gasValue);
  display.print("Motion: "); display.println(motion ? "Yes" : "No");
  display.display();

  // --- Send to Blynk ---
  Blynk.virtualWrite(V4, temp);
  Blynk.virtualWrite(V5, humid);
  Blynk.virtualWrite(V6, gasValue);
  Blynk.virtualWrite(V7, motion);

  delay(1000);  // Update every second
}
