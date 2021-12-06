//3pins超音波測距模組
int signalPin = 12; //用來trigger及接收echo
long duration, cm, inches;
 
void setup() {
  Serial.begin (115200);  // Serial Port begin
}
 
void loop()
{
  //發送超音波
  pinMode(signalPin, OUTPUT); //發送超音波時切還為輸出
  digitalWrite(signalPin, LOW);
  delayMicroseconds(5);
  digitalWrite(signalPin, HIGH);  // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(signalPin, LOW);

  //接收超音波
  pinMode(signalPin, INPUT);             // //讀取超音波時切還為輸入
  duration = pulseIn(signalPin, HIGH);   // 收到高電位時的時間

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
