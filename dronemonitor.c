#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ERRORS 10

// Define structures to store drone data
typedef struct {
    float altitude;
    float speed;
    float temperature;
    bool gpsSignal;
} SensorData;

typedef struct {
    bool isFlying;
    bool isHovering;
    bool obstacleDetected;
} FlightStatus;

typedef struct {
    int batteryPercentage;
    bool chargingStatus;
    float consumptionRate;
} BatteryStatus;

typedef struct {
    int errorCode;
    char description[50];
} ErrorLog;

// Global error list
ErrorLog errorList[MAX_ERRORS];
int errorCount = 0;

// Function prototypes
void updateSensorData(SensorData *sensor);
void updateFlightStatus(FlightStatus *flight);
void updateBatteryStatus(BatteryStatus *battery);
void logError(int code, const char *desc);
void displayDroneStatus(SensorData sensor, FlightStatus flight, BatteryStatus battery);
void saveDataToFile(SensorData sensor, FlightStatus flight, BatteryStatus battery);

int main() {
    SensorData sensor = {0.0, 0.0, 25.0, true};
    FlightStatus flight = {false, false, false};
    BatteryStatus battery = {100, false, 0.5};

    // Simulate drone operation
    for (int i = 0; i < 5; i++) {
        printf("\n--- Iteration %d ---\n", i + 1);

        updateSensorData(&sensor);
        updateFlightStatus(&flight);
        updateBatteryStatus(&battery);
        displayDroneStatus(sensor, flight, battery);
        saveDataToFile(sensor, flight, battery);

        // Simulate an error
        if (i == 2) {
            logError(1, "GPS signal lost");
        }

        printf("-----------------------------\n");
    }

    return 0;
}

// Function to update sensor data
void updateSensorData(SensorData *sensor) {
    sensor->altitude = (float)(rand() % 1000);
    sensor->speed = (float)(rand() % 100);
    sensor->temperature = 20.0 + (rand() % 15);
    sensor->gpsSignal = (rand() % 5) > 0;
}

// Function to update flight status
void updateFlightStatus(FlightStatus *flight) {
    flight->isFlying = (rand() % 2) > 0;
    flight->isHovering = (rand() % 2) > 0;
    flight->obstacleDetected = (rand() % 10) < 2;
}

// Function to update battery status
void updateBatteryStatus(BatteryStatus *battery) {
    battery->batteryPercentage -= (rand() % 5);
    battery->consumptionRate = (battery->batteryPercentage < 50) ? 0.7 : 0.5;
    battery->chargingStatus = (battery->batteryPercentage < 20);
}

// Function to log errors dynamically
void logError(int code, const char *desc) {
    if (errorCount < MAX_ERRORS) {
        errorList[errorCount].errorCode = code;
        snprintf(errorList[errorCount].description, sizeof(errorList[errorCount].description), "%s", desc);
        errorCount++;
        printf("ERROR LOGGED: %s\n", desc);
    }
}

// Function to display drone status
void displayDroneStatus(SensorData sensor, FlightStatus flight, BatteryStatus battery) {
    printf("Sensor Data: Altitude: %.2f m, Speed: %.2f km/h, Temperature: %.2f°C, GPS Signal: %s\n",
           sensor.altitude, sensor.speed, sensor.temperature, sensor.gpsSignal ? "Strong" : "Weak");
    printf("Flight Status: Flying: %s, Hovering: %s, Obstacle Detected: %s\n",
           flight.isFlying ? "Yes" : "No", flight.isHovering ? "Yes" : "No",
           flight.obstacleDetected ? "Yes" : "No");
    printf("Battery Status: %d%%, Charging: %s, Consumption Rate: %.2f\n", battery.batteryPercentage,
           battery.chargingStatus ? "Yes" : "No", battery.consumptionRate);
}

// Function to log sensor data to a file
void saveDataToFile(SensorData sensor, FlightStatus flight, BatteryStatus battery) {
    FILE *file = fopen("drone_log.txt", "a");
    if (file != NULL) {
        fprintf(file, "Altitude: %.2f m, Speed: %.2f km/h, Temperature: %.2f°C, GPS Signal: %s\n",
                sensor.altitude, sensor.speed, sensor.temperature, sensor.gpsSignal ? "Strong" : "Weak");
        fprintf(file, "Flight Status: Flying: %s, Hovering: %s, Obstacle Detected: %s\n",
                flight.isFlying ? "Yes" : "No", flight.isHovering ? "Yes" : "No",
                flight.obstacleDetected ? "Yes" : "No");
        fprintf(file, "Battery Status: %d%%, Charging: %s, Consumption Rate: %.2f\n\n", battery.batteryPercentage,
                battery.chargingStatus ? "Yes" : "No", battery.consumptionRate);
        fclose(file);
    }
}
