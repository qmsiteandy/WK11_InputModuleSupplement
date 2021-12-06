//4pins超音波測距模組
int triggerPin = 12; //用來trigger
int echoPin = 14; //用來接收echo
long duration, cm, inches;
 
void setup() {
  Serial.begin (115200);  // Serial Port begin
  pinMode(triggerPin, OUTPUT); //發送超音波
  pinMode(echoPin, INPUT);  //讀取超音波
}
 
void loop()
{
  //發送超音波
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);  // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  //接收超音波
  duration = pulseIn(echoPin, HIGH);   // 收到高電位時的時間

  //將回傳時間換算成距離 cm 或 inch 
  cm = (duration/2) / 29.1;          
  inches = (duration/2) / 74; 
  Serial.print("Distance : ");  
  Serial.print(inches);
  Serial.print("in,   ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
