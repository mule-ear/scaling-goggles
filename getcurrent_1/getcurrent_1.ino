#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219a(0x40);
Adafruit_INA219 ina219b(0x44);
Adafruit_INA219 ina219c(0x48);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void setup(void) 
{
  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif
  uint32_t currentFrequency;
    
  Serial.begin(9600);
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219a.begin();
  ina219b.begin();
  ina219c.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop(void) 
{
  float shuntvoltageA = 0;
  float busvoltageA = 0;
  float current_mAA = 0;
  float loadvoltageA = 0;
  
  float shuntvoltageB = 0;
  float busvoltageB = 0;
  float current_mAB = 0;
  float loadvoltageB = 0;
  
  float shuntvoltageC = 0;
  float busvoltageC = 0;
  float current_mAC = 0;
  float loadvoltageC = 0;

  shuntvoltageA = ina219a.getShuntVoltage_mV();
  busvoltageA = ina219a.getBusVoltage_V();
  current_mAA = ina219a.getCurrent_mA();
  loadvoltageA = busvoltageA + (shuntvoltageA / 1000);
  
  shuntvoltageB = ina219b.getShuntVoltage_mV();
  busvoltageB = ina219b.getBusVoltage_V();
  current_mAB = ina219b.getCurrent_mA();
  loadvoltageB = busvoltageB + (shuntvoltageB / 1000);
  
  shuntvoltageC = ina219c.getShuntVoltage_mV();
  busvoltageC = ina219c.getBusVoltage_V();
  current_mAC = ina219c.getCurrent_mA();
  loadvoltageC = busvoltageC + (shuntvoltageC / 1000);

  Serial.println("Battery: ");  
  Serial.print("B1:"); Serial.println(busvoltageA);
  Serial.print("S1:"); Serial.println(shuntvoltageA);
  Serial.print("L1:"); Serial.println(loadvoltageA);
  Serial.print("C1:"); Serial.println(current_mAA);
  Serial.println();
  Serial.println("Load"); 
  Serial.print("B2:"); Serial.println(busvoltageB);
  Serial.print("S2:"); Serial.println(shuntvoltageB);
  Serial.print("L2:"); Serial.println(loadvoltageB);
  Serial.print("C2:"); Serial.println(current_mAB);
  Serial.println();
  Serial.println("PV Array");
  Serial.print("B3:"); Serial.println(busvoltageC);
  Serial.print("S3:"); Serial.println(shuntvoltageC);
  Serial.print("L3:"); Serial.println(loadvoltageC);
  Serial.print("C3:"); Serial.println(current_mAC);
  Serial.println();
  //Serial.println("");

  delay(30000);
}
