#include "isd-dev-pinout.hpp"
#include <Wire.h>
#include <SimpleFOC.h>

MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);

TaskHandle_t task_sensor_get_status_HANDLE = NULL;
void task_sensor_get_status( void * pvParameters )
{
  for( ;; )
  {
    sensor.update();
    vTaskDelay(100);
  }
}

TaskHandle_t task_sensor_print_status_HANDLE = NULL;
void task_sensor_print_status( void * pvParameters )
{
  for( ;; )
  {
    Serial.print("STATUS\t||\tangle: ");
    Serial.println(sensor.getAngle());
    Serial.print("STATUS\t||\tvelocity: ");
    Serial.println(sensor.getVelocity());
    vTaskDelay(1000 /portTICK_PERIOD_MS);
  }
}

void setup() 
{
  
  Serial.begin(115200);

  Wire.setClock(400000);

  // Start I2C
  while (!(Wire.begin(SDA_PIN,SCL_PIN)))
  {
    Serial.println("PREP\t||\tBegin I2C");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println("ERROR\t||\tI2C Cant Init");
  }
  Serial.println("DONE\t||\tI2C Ready");

  // Start sensor
  sensor.init(&Wire);

  Serial.println("DONE\t||\tSensor Ready");

  //pin tasks
  xTaskCreate( task_sensor_get_status, "get_status", 2048, NULL, 1, &task_sensor_get_status_HANDLE );
  //configASSERT( task_sensor_get_status_HANDLE );

  xTaskCreate( task_sensor_print_status, "print_status", 2048, NULL, 2, &task_sensor_print_status_HANDLE );
  //configASSERT( task_sensor_print_status_HANDLE );

  vTaskDelay(1000 /portTICK_PERIOD_MS);
}

void loop() 
{
}
