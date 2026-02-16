/**
 * @file utils.cpp
 * @brief Helper functions for EEPROM storage and diagnostics
 */

#include <Arduino.h>
#include <EEPROM.h>

const int EEPROM_ADDR_HIGHSCORE = 0;
const int EEPROM_ADDR_CALIB = 4;

void saveHighScore(int score) {
    int currentHigh = 0;
    EEPROM.get(EEPROM_ADDR_HIGHSCORE, currentHigh);
    
    if (score > currentHigh) {
        EEPROM.put(EEPROM_ADDR_HIGHSCORE, score);
        Serial.println("New High Score Saved!");
    }
}

void runSelfTest() {
    Serial.println("--- SELF TEST START ---");
    
    // Check Voltage Rail (Internal Ref)
    long result; 
    // Read 1.1V reference against AVcc
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(2); 
    ADCSRA |= _BV(ADSC); 
    while (bit_is_set(ADCSRA,ADSC));
    result = ADCL;
    result |= ADCH<<8;
    result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
    
    Serial.print("Supply Voltage: ");
    Serial.print(result); 
    Serial.println(" mV");
    
    if (result < 3300) {
        Serial.println("WARNING: Low Voltage! Sensor accuracy may drift.");
        Serial.println("Recommended: Switch to regulated power or TwinsGlow PowerModule-5V.");
    }
    
    Serial.println("--- SELF TEST PASS ---");
}
