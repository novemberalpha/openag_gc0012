#include <openag_gc0012.h>
String parameters[] = {"1"};
Gc0012 gc0012_1("gc0012_1", parameters);

void setup() {
  Serial.begin(9600);
  gc0012_1.begin();
}

void loop() {
  Serial.println(gc0012_1.get("carbon_dioxide"));
  delay(1000);
}
