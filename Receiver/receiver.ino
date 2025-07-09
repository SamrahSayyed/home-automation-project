#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

void setup() {
  Serial.begin(9600);
  if (!driver.init()) {
    Serial.println("Receiver init failed");
  }
  pinMode(8,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {
  uint8_t buf[12];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen)) {
    buf[buflen] = '\0';
    Serial.print("Received: ");
    Serial.println((char*)buf);

    if (strcmp((char*)buf, "FAN_ON") == 0) {
      digitalWrite(8,HIGH);
      delayMicroseconds(550);
      digitalWrite(8,LOW);
      delay(20-(550/1000));
      digitalWrite(LED_BUILTIN,HIGH);
    }
    if (strcmp((char*)buf, "FAN_OFF") == 0) {
      digitalWrite(8,HIGH);
      delayMicroseconds(1400);
      digitalWrite(8,LOW);
      delay(20-(1400/1000));
      digitalWrite(LED_BUILTIN,LOW);
    }
  }
}
