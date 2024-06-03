#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>

#define WATER_SENSOR A0
#define SERVO_PIN 10
#define SIM900A_RX 7
#define SIM900A_TX 8
#define RELAY_PIN 9

SoftwareSerial espSerial(3, 2);  // RX, TX
SoftwareSerial SIM900A(SIM900A_RX, SIM900A_TX);

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

bool manualControl = false; // Variabl for manual control
bool sendMessageRequested = false;

// Define constants for water levels
const int WATER_LEVEL_HIGH = 100; // Example threshold for HIGH
const int WATER_LEVEL_MID = 50;  // Example threshold for MID
const int WATER_LEVEL_LOW = 25;  // Example threshold for LOW

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  //SIM900A.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SIM900A_RX, INPUT);
  pinMode(SIM900A_TX, OUTPUT);

  lcd.init();
  lcd.backlight();
  myservo.attach(SERVO_PIN);
}

void loop() {
  int waterSensorValue = analogRead(WATER_SENSOR);
  int waterLevel;

  if (espSerial.available()) {
    String status = espSerial.readStringUntil('\n'); // Read string from serial until newline character
    status.trim(); // Remove leading and trailing whitespaces
    if (status == "ON") {
      manualControl = true;
      lcd.clear();
      lcd.print("Manual Control");
      Serial.println("Manual control activated.");
      myservo.write(180);
      
    } else if (status == "OFF") { 
      manualControl = false;
      Serial.println("Automatic control activated.");

  lcd.clear();

  }
  
  // if (manualControl == true){
  //   if (espSerial.available()) {
  //     String action = Serial.readStringUntil('\n'); // Read string from serial until newline character
  //     action.trim(); // Remove leading and trailing whitespaces
  //     if (action == "Close") {
  //       myservo.write(0);
  
  //       Serial.println("Servo closed manually.");
  //     } else if (action == "Open") {
  //       myservo.write(180); // Turn servo ON
  //       Serial.println("Servo opened manually.");

  //     }

  // }

  
     
  
    // Automatic control section based on water level
  if (waterSensorValue > WATER_LEVEL_HIGH) {
      waterLevel = WATER_LEVEL_HIGH; // HIGH
    } else if (waterSensorValue < WATER_LEVEL_LOW) {
      waterLevel = WATER_LEVEL_LOW; // LOW
    } else {
      waterLevel = WATER_LEVEL_MID; // MID
    }

    // Clear and update the LCD with the current water level
    lcd.clear();
    lcd.setCursor(0, 0);

    // Control servo, relay, and update LCD based on water level
    if (waterLevel == WATER_LEVEL_HIGH) {
      lcd.print("WATER LEVEL:HIGH");
      myservo.write(180);
      digitalWrite(RELAY_PIN, HIGH);
      sendMessageRequested = true;
      espSerial.println(waterLevel);
    } else if (waterLevel == WATER_LEVEL_LOW) {
      lcd.print("WATER LEVEL:LOW");
      myservo.write(0);
      digitalWrite(RELAY_PIN, LOW);
      espSerial.println(waterLevel);
    } else {
      lcd.print("WATER LEVEL:MID");
      digitalWrite(RELAY_PIN, LOW);
      myservo.write(90);
      espSerial.println(waterLevel);
    }
  }

  if (sendMessageRequested) {
    sendSMS("+639296161440", "Water is High, Evacuate Now!!");
    sendMessageRequested = false; // Reset the flag after sending the message
  }

  // Send the water level value to ESP8266 and Serial monitor
 
  // Serial.println(waterLevel);

  delay(500); // Adjust delay as necessary
}

void sendSMS(String number, String message) {
  SIM900A.println("AT+CMGF=1"); // Set SMS mode to text
  delay(500); // Wait for command to complete

  Serial.println("Sending SMS to " + number);
  SIM900A.print("AT+CMGS=\"");
  SIM900A.print(number);
  SIM900A.println("\"");
  delay(500); // Wait for command to complete

  delay(500); // Wait for prompt

  SIM900A.print(message);
  delay(500); // Wait for message to be sent

  SIM900A.write(26); // CTRL+Z to send the message
  delay(500); // Wait for message to be sent

  // Check if message was sent successfully
  Serial.println("Waiting for response...");
  while (SIM900A.available()) {
    String response = SIM900A.readStringUntil('\n');
    Serial.println("Response: " + response);
    if (response.indexOf("OK") != -1) {
      Serial.println("SMS sent to " + number + " with message: " + message);
      break;
    }
  }

  delay(500); // Delay before sending another message
}
