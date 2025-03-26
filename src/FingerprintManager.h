/**
 * FingerprintManager.h - Handles fingerprint sensor functions
 * 
 * This module allows the ESP32 to:
 * - Enroll fingerprints
 * - Verify fingerprints
 * - Delete fingerprints
 * 
 * Author: Alfredo Sanchez Jr
 * Date: 2025-03-26
 */

 #ifndef FINGERPRINTMANAGER_H
 #define FINGERPRINTMANAGER_H
 
 #include <Adafruit_Fingerprint.h>

 // ✅ Global variable to check if fingerprint sensor is available
extern bool fingerprintAvailable; 
 
 // Function Declarations
 void initFingerprintSensor();
 bool enrollFingerprint(int id);
 bool verifyFingerprint();
 void deleteFingerprint(int id);
 
 #endif
 