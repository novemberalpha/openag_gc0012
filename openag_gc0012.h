/**
 *  \file openag_gc0012.h
 *  \brief Carbon Dioxide Sensor
 */
#ifndef OPENAG_GC0012_H
#define OPENAG_GC0012_h

#include "Arduino.h"
#include <openag_peripheral.h>

/**
 * \brief Carbon dioxide sensor
 */
class Gc0012 : public Peripheral {
  public:
    // Public variables
    String id;
    float carbon_dioxide;

    // Public functions
    Gc0012(String id, String* parameters); // constructor
    ~Gc0012(); // destructor
    void begin();
    String get(String key);
    String set(String key, String value);

  private:
    // Private variables
    String _carbon_dioxide_message;
    uint32_t _time_of_last_reading;
    const static uint32_t _min_update_interval = 0;
    String _carbon_dioxide_key;
    int _serial_port;
    HardwareSerial *_port;

    // Private functions
    void getData();
    String getCarbonDioxide();
    String getMessage(String key, String value);
    String getErrorMessage(String key);
};

#endif
