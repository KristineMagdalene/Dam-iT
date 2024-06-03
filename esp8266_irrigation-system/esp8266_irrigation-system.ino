#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

#define LED_PIN D2

char FIREBASE_AUTH[] = "AIzaSyD7yxqTuclEbuUrzg3W74db6AXRdUnR_vg"; // Your Firebase Web API Key
char FIREBASE_HOST[] = "dam-dam-12920-default-rtdb.firebaseio.com"; // Your Firebase Host URL
char WIFI_SSID[] = "PLDT_Home_82480"; // Your WIFI SSID
char WIFI_PASSWORD[] = "Pldthome*369"; // Your WIFI Password

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600); // For debugging and communication
  pinMode(LED_PIN, OUTPUT);
  WiFi.mode(WIFI_OFF);

  // Small delay to allow the ESP8266 to power up properly
  delay(1000);

  // Initialize WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.println("Connecting to WiFi...");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to WiFi.");

  // Initialize Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Firebase initialized.");
}

void loop() {
  // Check if data is available on Serial
  if (Serial.available()) {
    String waterLevel = Serial.readString();
    Firebase.setInt(firebaseData, "/dam/waterLevel", waterLevel.toInt());
    Serial.print(waterLevel);
  }

  // Get manual control status from Firebase and control LED
  if (Firebase.getString(firebaseData, "/dam/manual control")) {
    String status = firebaseData.stringData();
    Serial.println(status);
    if (status == "ON"){
      if (Firebase.getString(firebaseData, "/dam/gateStatus")) {
    String manual = firebaseData.stringData();
    Serial.println(manual); // Print manual control status to serial
   
    }
     
  }
  }
  

  // Small delay to avoid overwhelming the loop
  delay(100);
}
