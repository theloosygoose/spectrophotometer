//Packages
#include <LiquidCrystal.h>

// Constants 
LiquidCrystal lcd(12,11,5,4,3,2);
const int pResistor = A0;
float voltage;
int reading;
float livereadVolt;

//smoothing vars

const int numReadings = 10;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int liveread;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(pResistor, INPUT);  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
}

void smoothing(){
//SMOOTHING
   // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(pResistor);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  delay(1000);
}

void loop() {
  smoothing();
  // calculate the average:
  average = total / numReadings;

  voltage = average * (5000.0 / 1024.0);
  String mvStr = "mv";  
  String liveStr = "live:";
  String avgStr = "avg:";
  delay(1000);
  
  liveread = analogRead(pResistor);
  livereadVolt = liveread * (5000.0 / 1024.0);
  
  
  lcd.setCursor(0, 0);
  lcd.print(avgStr + voltage + mvStr);
  lcd.setCursor(0, 1);
  lcd.print(liveStr + livereadVolt + mvStr);
  
  Serial.println(voltage);
  Serial.println(livereadVolt + liveStr);


}
