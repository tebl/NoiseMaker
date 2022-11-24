#pragma once
#include "settings.h"

#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.print(x); 
#else
 #define DEBUG_PRINT(x)
#endif
#ifdef DEBUG
 #define DEBUG_PRINTLN(x)  Serial.println(x);
#else
 #define DEBUG_PRINTLN(x)
#endif