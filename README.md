# IoT Smart Irrigation System

An intelligent irrigation system using ESP8266 and Firebase Realtime Database. The system automates the opening and closing of an irrigation dam based on water levels and allows manual control through a mobile application. It also sends water level notifications and SMS alerts to designated phone numbers.

## Features

- **Automatic Control**: Opens and closes the irrigation dam automatically depending on the water level.
- **Manual Control**: Allows manual operation of the irrigation gate through a mobile application.
- **Water Level Notifications**: Sends notifications to the admin's mobile application.
- **SMS Alerts**: Automatically sends SMS alerts to designated phone numbers.

## Components Used

- **ESP8266**: WiFi module for connecting to the internet and communicating with Firebase.
- **Arduino Uno R3**: Microcontroller for controlling the sensors and actuators.
- **Servo Motor**: Used to control the gate opening of the irrigation system.
- **Water Level Sensor**: Detects the water level in the dam to automate gate control.
- **Relay Module**: Controls the pump and other high-power components.
- **Pump**: Connected to the relay module for irrigation purposes.
- **SIM900A**: GSM module for sending SMS alerts.

## How It Works

1. **Water Level Monitoring**: The water level sensor continuously monitors the water level.
2. **Data Transmission**: The ESP8266 sends the water level data to Firebase Realtime Database.
3. **Automated Control**: Based on the water level data, the servo motor automatically opens or closes the irrigation gate.
4. **Manual Override**: The mobile application allows for manual control of the irrigation gate.
5. **Notifications and Alerts**: Water level notifications are sent to the mobile application, and SMS alerts are sent via the SIM900A module.

## Schematic Diagram

(schematic diagram image here)

## Installation

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/KristineMagdalene/Irrigation-System-IOT-based-using-NodeMCU-esp8266-and-firebase.git
    cd IOT-Smart-Irrigation-System
    ```

2. **Install Required Libraries**:
    - FirebaseESP8266
    - Servo
    - SoftwareSerial
    

3. **Upload the Code**:
    - Open the Arduino IDE.
    - Connect your Arduino Uno and ESP8266.
    - Upload the code from the `src` folder to your Arduino Uno.

4. **Configure Firebase**:
    - Set up a Firebase Realtime Database.
    - Update the Firebase credentials in the code.

5. **Mobile Application**:
    - (Provide instructions or link to the mobile app repository or APK)

## Usage

- **Automatic Mode**: The system will operate automatically based on water levels.
- **Manual Mode**: Use the mobile application to manually control the irrigation gate.
- **SMS Alerts**: Ensure the SIM900A is properly configured with your SIM card to receive SMS alerts.

## Troubleshooting

- **Connection Issues**: Ensure the ESP8266 is connected to a stable WiFi network.
- **Sensor Calibration**: Make sure the water level sensor is correctly calibrated and positioned.
- **Firebase Configuration**: Double-check your Firebase database URL and authentication details.

## Contributions

Contributions are welcome! Please fork the repository and create a pull request with your changes.


Feel free to reach out for any queries or suggestions. Happy irrigating!

