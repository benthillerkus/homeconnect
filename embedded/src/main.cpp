#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  printf("Hello World!\n");
  digitalWrite(4, digitalRead(4) == LOW ? HIGH : LOW);
  sleep(5);
}
