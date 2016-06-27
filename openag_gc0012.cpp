/**
 *  \file openag_gc0012.h
 *  \brief Carbon Dioxide Sensor
 */
#include "openag_gc0012.h"

Gc0012::Gc0012(int serial_port) {
  // Select serial port
  switch(serial_port) {
    case 1:
      _serial_port = &Serial1;
      break;
    case 2:
      _serial_port = &Serial2;
      break;
    case 3:
      _serial_port = &Serial3;
      break;
  }
}

void Gc0012::begin() {
  _time_of_last_reading = 0;

  // Enable serial port
  _serial_port->begin(9600);

  // Set operation mode
  _serial_port->print("K 2\r\n"); // enable polling mode
}

bool Gc0012::get_air_carbon_dioxide(std_msgs::Float32 &msg) {
  if (millis() - _time_of_last_reading > _min_update_interval){
    _time_of_last_reading = millis();
    bool res = readData();
    msg.data = _carbon_dioxide;
    return res;
  }
  return false;
}

bool Gc0012::readData() {
  // Read sensor
  _serial_port->print("Z\r\n");
  String data_string = _serial_port->readStringUntil(0x0A);
  Serial.println(data_string);

  // Check for failure
  if (data_string[1] != 'Z') {
      has_error = true;
      error_msg = "Failed to read";
  }
  else { // good reading
    _carbon_dioxide = (float)(data_string.substring(3,8).toInt());
    _carbon_dioxide = round(_carbon_dioxide / 10) * 10;
  }

  return !has_error;
}
