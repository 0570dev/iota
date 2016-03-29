int light_lastUpdate = 0;
int light_update_interval = 10000; // 10 seconds

float lastLux = 0;

void setupLight() {
  updateLight();
}

void updateLight() {
  float volts = analogRead(A0) * 3.3 / 1024.0;
  float amps = volts / 10000.0;  // 10k resistor
  float microamps = amps * 1000000;
  float lux = microamps * 2.0;
  
  lastLux = lux;
  Serial.print(lux);
  Serial.println(" lux");
}

void loopLight() {
  if (millis() > light_update_interval && 
       ((millis() - light_update_interval) > light_lastUpdate)) {
    updateLight();
    light_lastUpdate = millis();
  }
}

