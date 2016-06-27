#include <openag_gc0012.h>
Gc0012 gc0012_1(1);

void setup() {
  Serial.begin(9600);
  gc0012_1.begin();
}

std_msgs::Float32 msg;

void loop() {
  if (gc0012_1.get_air_carbon_dioxide(msg)) {
    Serial.print("Air CO2: ");
    Serial.println(msg.data);
  }
  if (gc0012_1.has_error) {
    Serial.print("Error: ");
    Serial.println(gc0012_1.error_msg);
    gc0012_1.has_error = false;
  }
}
