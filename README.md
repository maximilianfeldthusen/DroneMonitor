## Documentation 

### DroneMonitor

This code provides a basic **drone operation monitoring system**. Let’s break it down in a way that feels intuitive and easy to understand.

### **Understanding the Code**
At its core, this program **simulates drone operations** by tracking sensor data, flight status, battery levels, and errors. It runs through multiple iterations, updating drone data and logging it for analysis.

#### **1. Header Files and Constants**
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ERRORS 10
```
- `stdio.h`: Enables input and output operations, such as printing messages.
- `stdlib.h`: Provides utility functions like `rand()` for generating random values.
- `stdbool.h`: Allows the use of `true` and `false` as boolean values.
- `string.h`: Helps with handling text data, such as error descriptions.
- `MAX_ERRORS`: Limits the number of error messages stored.

#### **2. Structs: Organizing Data**
Each struct represents a different aspect of the drone's functionality.
```c
typedef struct {
    float altitude;
    float speed;
    float temperature;
    bool gpsSignal;
} SensorData;
```
This struct **stores sensor readings**, such as altitude, speed, temperature, and GPS signal status.

```c
typedef struct {
    bool isFlying;
    bool isHovering;
    bool obstacleDetected;
} FlightStatus;
```
This struct keeps track of **the flight mode**, whether the drone is flying, hovering, or encountering obstacles.

```c
typedef struct {
    int batteryPercentage;
    bool chargingStatus;
    float consumptionRate;
} BatteryStatus;
```
The battery struct **monitors charge levels** and calculates power consumption rates.

```c
typedef struct {
    int errorCode;
    char description[50];
} ErrorLog;
```
This struct **logs errors**, storing an error code and description.

#### **3. Global Error List**
```c
ErrorLog errorList[MAX_ERRORS];
int errorCount = 0;
```
- `errorList` is an array that holds errors.
- `errorCount` keeps track of how many errors have been logged.

#### **4. Function Prototypes**
These lines declare functions that will be defined later. They **ensure that the compiler knows about all functions before they are used**.
```c
void updateSensorData(SensorData *sensor);
void updateFlightStatus(FlightStatus *flight);
void updateBatteryStatus(BatteryStatus *battery);
void logError(int code, const char *desc);
void displayDroneStatus(SensorData sensor, FlightStatus flight, BatteryStatus battery);
void saveDataToFile(SensorData sensor, FlightStatus flight, BatteryStatus battery);
```

#### **5. Main Function: The Heart of the Program**
```c
int main() {
    SensorData sensor = {0.0, 0.0, 25.0, true};
    FlightStatus flight = {false, false, false};
    BatteryStatus battery = {100, false, 0.5};
```
- Initializes the drone’s **starting conditions**.
- Battery is set to **100% charge**, the drone is **not flying**, and **sensor readings start at zero**.

```c
for (int i = 0; i < 5; i++) {
    printf("\n--- Iteration %d ---\n", i + 1);
```
- Runs a **loop for five iterations**, simulating the drone’s operation step by step.

#### **6. Updating Sensor, Flight, and Battery Data**
Each function **updates relevant data** using random values to mimic real-world changes.

```c
void updateSensorData(SensorData *sensor) {
    sensor->altitude = (float)(rand() % 1000);
    sensor->speed = (float)(rand() % 100);
    sensor->temperature = 20.0 + (rand() % 15);
    sensor->gpsSignal = (rand() % 5) > 0;
}
```
- Assigns **random values** to sensor data fields.
- Temperature ranges from **20°C to 35°C**, and GPS **sometimes fails**.

Similar logic is applied to flight status:
```c
void updateFlightStatus(FlightStatus *flight) {
    flight->isFlying = (rand() % 2) > 0;
    flight->isHovering = (rand() % 2) > 0;
    flight->obstacleDetected = (rand() % 10) < 2;
}
```
- Drone randomly **starts flying or hovering**.
- Sometimes detects **an obstacle**.

Battery behavior follows a similar pattern:
```c
void updateBatteryStatus(BatteryStatus *battery) {
    battery->batteryPercentage -= (rand() % 5);
    battery->consumptionRate = (battery->batteryPercentage < 50) ? 0.7 : 0.5;
    battery->chargingStatus = (battery->batteryPercentage < 20);
}
```
- **Battery depletes randomly**.
- **Consumption rate increases** when charge falls below 50%.
- If charge drops **below 20%, it needs charging**.

#### **7. Error Logging**
Errors occur in real drones, so the code tracks them.
```c
void logError(int code, const char *desc) {
    if (errorCount < MAX_ERRORS) {
        errorList[errorCount].errorCode = code;
        snprintf(errorList[errorCount].description, sizeof(errorList[errorCount].description), "%s", desc);
        errorCount++;
        printf("ERROR LOGGED: %s\n", desc);
    }
}
```
- Stores **up to 10 errors**.
- Uses `snprintf()` to **safely format error messages**.

#### **8. Displaying Drone Status**
This function **prints updated drone data** after each iteration.
```c
void displayDroneStatus(SensorData sensor, FlightStatus flight, BatteryStatus battery) {
    printf("Sensor Data: Altitude: %.2f m, Speed: %.2f km/h, Temperature: %.2f°C, GPS Signal: %s\n",
           sensor.altitude, sensor.speed, sensor.temperature, sensor.gpsSignal ? "Strong" : "Weak");
}
```
Each data point is displayed with **precision formatting**.

#### **9. Logging Data to a File**
```c
void saveDataToFile(SensorData sensor, FlightStatus flight, BatteryStatus battery) {
    FILE *file = fopen("drone_log.txt", "a");
    if (file != NULL) {
        fprintf(file, "Altitude: %.2f m, Speed: %.2f km/h, Temperature: %.2f°C\n",
                sensor.altitude, sensor.speed, sensor.temperature);
        fclose(file);
    }
}
```
- Opens `"drone_log.txt"` in **append mode** to store multiple entries.
- Writes **sensor data to the file**, making it available for analysis.

### **Summary**
This program **mimics real-world drone behavior**, allowing monitoring of flight and battery status while logging errors. It demonstrates **modular programming, structured data handling, and error management**.
