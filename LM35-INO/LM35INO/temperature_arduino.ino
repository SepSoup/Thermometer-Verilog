#include <stdio.h>
#include <math.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

#define ACK_PIN 12
#define DATA_1_PIN 2
#define DATA_2_PIN 3
#define DATA_3_PIN 4
#define DATA_4_PIN 5
#define DATA_5_PIN 6
#define DATA_6_PIN 7
#define DATA_7_PIN 8
#define DATA_8_PIN 9
#define DATA_9_PIN 10
#define DATA_10_PIN 11
#define TIME_STEP 500

Adafruit_ADS1115 ads;

void toBinary10Bit(int num, int binaryArr[10]) {
  if (num < 0 || num > 999) {
      Serial.print("Input should be between 0 and 999.\n");
      return;
  }
  for (int i = 9; i >= 0; i--) {
      binaryArr[9 - i] = (num >> i) & 1;
  }
}

void setup() {
  // put your setup code here, to run once:
  delay(1000);

  pinMode(ACK_PIN, OUTPUT);
  pinMode(DATA_1_PIN, OUTPUT);
  pinMode(DATA_2_PIN, OUTPUT);
  pinMode(DATA_3_PIN, OUTPUT);
  pinMode(DATA_4_PIN, OUTPUT);
  pinMode(DATA_5_PIN, OUTPUT);
  pinMode(DATA_6_PIN, OUTPUT);
  pinMode(DATA_7_PIN, OUTPUT);
  pinMode(DATA_8_PIN, OUTPUT);
  pinMode(DATA_9_PIN, OUTPUT);
  pinMode(DATA_10_PIN, OUTPUT);

  digitalWrite(ACK_PIN, LOW);
  digitalWrite(DATA_1_PIN, LOW);
  digitalWrite(DATA_2_PIN, LOW);
  digitalWrite(DATA_3_PIN, LOW);
  digitalWrite(DATA_4_PIN, LOW);
  digitalWrite(DATA_5_PIN, LOW);
  digitalWrite(DATA_6_PIN, LOW);
  digitalWrite(DATA_7_PIN, LOW);
  digitalWrite(DATA_8_PIN, LOW);
  digitalWrite(DATA_9_PIN, LOW);
  digitalWrite(DATA_10_PIN, LOW);

  Serial.begin(9600);
  Wire.begin();
  if (!ads.begin())
  {
    while(1) {
      Serial.println("Failed to initialize ADS.");
      delay(1000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  int16_t adc3;
  float volts3, temp;
  int sendTemp;
  int binaryArr[10];
 
  adc3 = ads.readADC_SingleEnded(3);
  volts3 = ads.computeVolts(adc3);
  temp = volts3 * 100;
  sendTemp = (int)(trunc(temp * 10));
  toBinary10Bit(sendTemp, binaryArr);

  Serial.println("-----------------------------------------------------------");
  Serial.print("TEMPERATURE: "); Serial.println(temp);
  Serial.print("send temp: "); Serial.println(sendTemp);

  Serial.print("Binary representation: ");
  for (int i = 0; i < 10; i++) {
    Serial.print(binaryArr[i]);
  }
  Serial.print("\n");
 
  delay(800);

  digitalWrite(ACK_PIN, HIGH);

  digitalWrite(DATA_1_PIN, binaryArr[0]);
  digitalWrite(DATA_2_PIN ,binaryArr[1]);
  digitalWrite(DATA_3_PIN ,binaryArr[2]);
  digitalWrite(DATA_4_PIN ,binaryArr[3]);
  digitalWrite(DATA_5_PIN ,binaryArr[4]);
  digitalWrite(DATA_6_PIN ,binaryArr[5]);
  digitalWrite(DATA_7_PIN ,binaryArr[6]);
  digitalWrite(DATA_8_PIN ,binaryArr[7]);
  digitalWrite(DATA_9_PIN ,binaryArr[8]);
  digitalWrite(DATA_10_PIN ,binaryArr[9]);

  delayMicroseconds(TIME_STEP);

  digitalWrite(ACK_PIN, LOW);

  delayMicroseconds(TIME_STEP);

  digitalWrite(DATA_1_PIN, LOW);
  digitalWrite(DATA_2_PIN, LOW);
  digitalWrite(DATA_3_PIN, LOW);
  digitalWrite(DATA_4_PIN, LOW);
  digitalWrite(DATA_5_PIN, LOW);
  digitalWrite(DATA_6_PIN, LOW);
  digitalWrite(DATA_7_PIN, LOW);
  digitalWrite(DATA_8_PIN, LOW);
  digitalWrite(DATA_9_PIN, LOW);
  digitalWrite(DATA_10_PIN, LOW);
}
