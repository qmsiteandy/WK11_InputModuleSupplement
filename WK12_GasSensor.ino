const int sensor_pin = 12;
const int alert_pin = 14;

void setup() {
  Serial.begin(115200);
  pinMode(sensor_pin, INPUT);
  pinMode(alert_pin, INPUT);
}

void loop() {
  Serial.print(analogRead(sensor_pin));
  Serial.print(" | ");
  Serial.print("alert = ");
  Serial.println(digitalRead(alert_pin));
  delay(200);
}
