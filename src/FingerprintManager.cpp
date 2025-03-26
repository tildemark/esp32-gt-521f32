/**
 * FingerprintManager.cpp - Implements fingerprint sensor functions
 */

 #include "FingerprintManager.h"

 // ✅ Use UART2 (GPIO16 as RX, GPIO17 as TX)
 HardwareSerial mySerial(2);
 Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
 bool fingerprintAvailable = false;  // ✅ flag to track sensor status
 
 /**
  * Initializes the fingerprint sensor.
  */

void initFingerprintSensor() {
    Serial.println("🔍 Initializing Fingerprint Sensor...");
    mySerial.begin(9600, SERIAL_8N1, 16, 17); // UART2: RX=16, TX=17
    delay(1000);

    finger.begin(57600);
    delay(1000);

    if (finger.verifyPassword()) {
        Serial.println("✅ Fingerprint sensor detected!");
        fingerprintAvailable = true;  // ✅ Mark sensor as available
    } else {
        Serial.println("❌ Fingerprint sensor not found. Skipping fingerprint functions.");
        fingerprintAvailable = false; // ✅ Mark sensor as missing
    }
}
  
 
 /**
  * Enrolls a fingerprint with a given ID.
  * @param id Fingerprint ID (1-127)
  * @return true if enrolled successfully, false otherwise
  */
 bool enrollFingerprint(int id) {
   Serial.print("📌 Place finger on the sensor to enroll ID ");
   Serial.println(id);
 
   if (finger.getImage() != FINGERPRINT_OK) return false;
   if (finger.image2Tz(1) != FINGERPRINT_OK) return false;
   if (finger.storeModel(id) != FINGERPRINT_OK) return false;
 
   Serial.println("✅ Fingerprint enrolled successfully!");
   return true;
 }
 
 /**
  * Verifies a fingerprint match.
  * @return true if the fingerprint is recognized, false otherwise
  */
 bool verifyFingerprint() {
   Serial.println("🔍 Place your finger on the sensor...");
 
   if (finger.getImage() != FINGERPRINT_OK) return false;
   if (finger.image2Tz(1) != FINGERPRINT_OK) return false;
   if (finger.fingerSearch() != FINGERPRINT_OK) return false;
 
   Serial.print("✅ Fingerprint matched! ID: ");
   Serial.println(finger.fingerID);
   return true;
 }
 
 /**
  * Deletes a stored fingerprint.
  * @param id Fingerprint ID to delete
  */
 void deleteFingerprint(int id) {
   if (finger.deleteModel(id) == FINGERPRINT_OK) {
     Serial.println("✅ Fingerprint deleted successfully.");
   } else {
     Serial.println("❌ Failed to delete fingerprint.");
   }
 }
 