
#include <Wire.h>
#include <MPU6050.h>
float accel = 0.0;

MPU6050 mpu;

void setup() 
{
  Serial.begin(9600);

  // Initialize MPU6050
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
  checkSettings();
  

 Serial.println("Fall Detection Software On!");
}
  
 void checkSettings()
{

  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  


}



  /*
  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
  */


void loop()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

// Gyroscope Data
  //Serial.print(" Xraw = ");
  //Serial.print(rawGyro.XAxis);
  //Serial.print(" Yraw = ");
  //Serial.print(rawGyro.YAxis);
  //Serial.print(" Zraw = ");
  //Serial.println(rawGyro.ZAxis);

 // Serial.print(" Gyro Xnorm = ");
  //Serial.print(normGyro.XAxis);
  //Serial.print(" Gyro Ynorm = ");
  //Serial.print(normGyro.YAxis);
  //Serial.print(" Gyro Znorm = ");
  //Serial.println(normGyro.ZAxis);

// Accelerometer Data
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();

 // Serial.print(" Xraw = ");
  //Serial.print(rawAccel.XAxis);
  int xnorm = normAccel.XAxis;
  //Serial.print(" Yraw = ");
 // Serial.print(rawAccel.YAxis);
   int ynorm = normAccel.YAxis;
 //Serial.print(" Zraw = ");
// Serial.println(rawAccel.ZAxis);
    int znorm = normAccel.ZAxis;

 
  //Serial.print(" Acc Xnorm = ");
  //Serial.print(normAccel.XAxis);
  
 // Serial.print(" Acc Ynorm = ");
  //Serial.print(normAccel.YAxis);
//Serial.print(" Acc Znorm = ");
//Serial.println(normAccel.ZAxis);

 accel = sqrt(xnorm* xnorm + ynorm * ynorm + znorm*znorm);

 //Serial.println(accel);

 if (znorm <=1)
{
  Serial.print("Fall detected.      ");
  if (accel >=12)
  {
    Serial.print("Severeity: HIGH RISK      ");
  }
  else {
    Serial.print("Severity: LOW RISK     ");
  }
}
else {
  Serial.print("No problems detected     ");
}
 
 
  delay(2000);
}
