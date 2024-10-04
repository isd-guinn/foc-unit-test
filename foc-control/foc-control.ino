#include "isd-dev-pinout.hpp"
#include <Wire.h>
#include <SimpleFOC.h>

MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);

void setup() {
  
  Serial.begin(115200);

  Wire.setClock(400000);

  // Start I2C
  while (Wire.begin(SDA_PIN,SCL_PIN)){
    Serial.prinln("PREP: Begin I2C");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.prinln("ERROR  || I2C Cant Init")
  }
  Serial.prinln("DONE   || I2C Ready")

  // Start sensor
  sensor.init(&Wire);

  Serial.prinln("DONE   || Sensor Ready");
}

void loop() {
  sensor.update();

  Serial.print("STATUS  || angle: ");
  Serial.println("");


}
