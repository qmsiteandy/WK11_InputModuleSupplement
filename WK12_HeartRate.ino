#include <Wire.h>
#include "MAX30105.h" //匯入心律感測器會用到的函式庫
#include "heartRate.h"

MAX30105 particleSensor;  //宣告物件

const byte RATE_SIZE = 4; //每四筆數據算一次beatAvg
byte rates[RATE_SIZE];  //儲存運算beatAvg用的數據
byte rateSpot = 0;  //儲存運算beatAvg用的數據
long lastBeat = 0; //紀錄前次脈搏時間

float beatsPerMinute; //儲存每分鐘脈搏數
int beatAvg;  //儲存脈搏平均

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

void loop()
{
  long irValue = particleSensor.getIR();

  //當檢測到脈搏(使用heartRate.h中的函式)
  //可以用偵測到的IR數值判斷是否脈搏跳動
  if (checkForBeat(irValue) == true)
  {
    //紀錄脈搏間隔時間
    long delta = millis() - lastBeat;
    lastBeat = millis();

    //用間隔時間運算每分鐘脈搏數
    beatsPerMinute = 60 / (delta / 1000.0);

    //運算平均脈搏數
    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);

  if (irValue < 50000)
    Serial.print(" No finger?");

  Serial.println();
}
