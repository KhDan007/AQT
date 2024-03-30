#include <Stepper.h>

// Stepper motor setup
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
const int stepsPerRevolution = 200; 
Stepper myStepper(stepsPerRevolution, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4); 

// Water sensor setup
#define POWER_PIN 7
#define SIGNAL_PIN A5
#define SENSOR_MIN 0
#define SENSOR_MAX 521
int value = 0;
int level = 0; 

// Timing variables
unsigned long currentMillis = 0;
unsigned long stepperInterval = 2; 
unsigned long sensorInterval = 1000; 
unsigned long previousStepperTime = 0;
unsigned long previousSensorTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT); 
  digitalWrite(POWER_PIN, LOW); 

  myStepper.setSpeed(60); 
}

void loop() {
  currentMillis = millis();

  // Water Sensor Reading 
  if (currentMillis - previousSensorTime >= sensorInterval) {
    previousSensorTime = currentMillis;

    // Water sensor reading
    digitalWrite(POWER_PIN, HIGH); 
    delay(10);
    value = analogRead(SIGNAL_PIN); 
    digitalWrite(POWER_PIN, LOW);  

    level = map(value, SENSOR_MIN, SENSOR_MAX, 0, 4); 
    Serial.print("Water level: ");
    Serial.println(level);
  }

  // Stepper Motor Control (only if water level is 0)
  if (currentMillis - previousStepperTime >= stepperInterval && level == 0) {
    previousStepperTime = currentMillis;
    myStepper.step(1); 
  }
}

