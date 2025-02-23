#include "Arduino.h"

void setup(void) {

  Serial.begin(9600);

  Serial.print("\nhello World");
  
}

int cntr=0;

void loop(void) {

  if (cntr==0) {
    Serial.print(".");
  }

  cntr++;

  if (cntr>=50000) cntr=0;
}
