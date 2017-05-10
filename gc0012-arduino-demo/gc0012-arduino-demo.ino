/*
 GC0012 Demo Code
 Rewritten by: Joseph Juhnke from the original author Jason Berger ( for Co2meter.com)

 This sketch connects will connect to a Cozir gss or SprintIR sensor
 and report readings back to the host computer over usb. The value is
 stored in a global variable 'co2' and can be used for any number of applications.

 pin connections:

 ArduinoMega2560_________Cozir Sensor
 GND ------------------- 1 (gnd)
 3.3v------------------- 3 (Vcc)
 18 -------------------- 5 (Rx)
 19 -------------------- 7 (Tx)
 */

void setup()
{


  Serial.begin(9600); //Start Serial connection with host
  Serial.println("Connecting to Cozir");
  Serial1.begin(9600); //Start Serial connection with Sensor
  
  delay(1000);
  
  Serial.println("Initiating Fresh Air Calibration");
  Serial1.println("G");
  String calibrate_response = Serial1.readStringUntil(0x0A);
  Serial.print("Cozir Response: ");
  Serial.println(calibrate_response);
  
  delay(1000);

  Serial.println("Setting Polling Mode");
  Serial1.println("K 2"); // Set to polling mode
  delay(1000);

  Serial.println("Sensing Enabled");

}
void loop()
{
  delay(1000);
  Serial1.println("Z");
  String data_string = Serial1.readStringUntil(0x0A);
  float co2 = 0;

  // Check for failure
  if (data_string[1] != 'Z') {
    Serial.println("Error");
  }
  else { //  good reading
    co2 = (float)(data_string.substring(3,8).toInt());
//    co2 = round(co2 / 10) * 10; // why are we rounding down?
    Serial.println(co2);
  }
}
