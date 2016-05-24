/**
 *  \file openag_gc0012.h
 *  \brief Carbon Dioxide Sensor
 */
#include "openag_gc0012.h"

Gc0012::Gc0012(String id, String* parameters) : Peripheral(id, parameters) {
  this->id = id;
  _serial_port = parameters[0].toInt();
  _carbon_dioxide_key = "carbon_dioxide";
}

Gc0012::~Gc0012() {}

void Gc0012::begin() {
  _time_of_last_reading = 0;

  // Select serial port
  switch(_serial_port) {
    case 1:
      _port = &Serial1;
      break;
    case 2:
      _port = &Serial2;
      break;
    case 3:
      _port = &Serial3;
      break;
  }

  // Enable serial port
  _port->begin(9600);

  // Set operation mode
  _port->print("K 2\r\n"); // enable polling mode

}

String Gc0012::get(String key) {
  if (key == _carbon_dioxide_key) {
    return getCarbonDioxide();
  }
  return getErrorMessage(key);
}

String Gc0012::set(String key, String value) {
  return getErrorMessage(_carbon_dioxide_key);
}

String Gc0012::getCarbonDioxide(){
  if (millis() - _time_of_last_reading > _min_update_interval){ // can only read sensor so often
    getData();
    _time_of_last_reading = millis();
  }
  return _carbon_dioxide_message;
}

void Gc0012::getData() {
  boolean is_good_reading = true;

  // Read sensor
  _port->print("Z\r\n");
  String data_string = _port->readStringUntil(0x0A);

  // Check for failure
  if (data_string[1] != 'Z') {
    is_good_reading = false;
  }
  else { // good reading
    carbon_dioxide = (float)(data_string.substring(3,8).toInt());
    carbon_dioxide = round(carbon_dioxide / 10) * 10;
  }

  // Update messages
  if (is_good_reading) {
    _carbon_dioxide_message = getMessage(_carbon_dioxide_key, String(carbon_dioxide, 0));
  }
  else { // read failure
    _carbon_dioxide_message = getErrorMessage(_carbon_dioxide_key);
  }
}

String Gc0012::getMessage(String key, String value) {
  return String(id + "," + key + "," + value);
}

String Gc0012::getErrorMessage(String key) {
  return String(id + "," + key + ",error");
}
