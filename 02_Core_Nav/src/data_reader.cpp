#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib> // For atof
#include <iomanip>  // Needed for setprecision
#include "../include/navigation_states.hpp"



void read_sensor_data(std::string filename) {
    std::ifstream file(filename.c_str());
    std::string line, word;

    // CHANGE TO THIS:
    std::ofstream logFile("02_Core_Nav/logs/navigation_log.csv");   
    if (logFile.is_open()) {
        // We match exactly what we write in the loop:
        logFile << "time,lat,lon,alt,heading,gForce\n";
    }

    // 1. Initialize our aircraft's state
    NavState currentState; // All zeros to start (At rest)
    double dt = 0.01;            // 0.01 second steps

    // --- FIX: NO MORE SILENT FAILURES ---
    if (!file.is_open()) {
        std::cout << "\n[!] CRITICAL ERROR: CANNOT OPEN FILE" << std::endl;
        std::cout << "[!] LOOKING AT: " << filename << std::endl;
        std::cout << "[!] Check if your Python script saved the file there!\n" << std::endl;
        return; 
    } else {
        std::cout << ">>> SUCCESS: File Found. Starting Navigation Brain..." << std::endl;
    }

    std::getline(file, line); // Skip header

    std::cout << "Time | Accel | Calculated Velocity" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> row;

        while (std::getline(ss, word, ',')) {
            row.push_back(atof(word.c_str()));
        }

        // Now we need at least 4 columns: Time, AccelX, AccelZ, and GyroZ
        if (row.size() < 4) continue;

        double time   = row[0];
        double accelX = row[1]; // Forward thrust
        double accelZ = row[2]; // Vertical movement
        double gyroZ   = row[3]; // NEW: Turn rate (rad/s)

        currentState.time = time; // This links the CSV time to your NavState
        currentState.gForce = std::sqrt(std::pow(accelX, 2) + std::pow(accelZ, 2)) / 9.81;

        if (time > 20.0 && time < 21.0) {
            std::cout << "DEBUG: Time " << time << " | Raw GyroZ: " << row[3] << std::endl;
        }

        // --- THE SHIELD (PHASE 2) ---
        if (std::abs(accelX) > 50.0 || std::abs(accelZ) > 50.0) { 
            std::cout << "!!! [SENTINEL] ANOMALY BLOCKED AT " << time << "s !!!" << std::endl;
            continue; 
        }

        // --- 1. HEADING UPDATE (The Turning Logic) ---
        // Convert radians to degrees and add to current heading
        currentState.heading += (gyroZ * 180.0 / M_PI) * dt;

        // Keep heading between 0 and 360 degrees
        if (currentState.heading >= 360.0) currentState.heading -= 360.0;
        if (currentState.heading < 0.0)    currentState.heading += 360.0;

        // --- 2. VECTOR MATH (Splitting Speed into N and E) ---
        double rad = currentState.heading * (M_PI / 180.0);
        double accelN = accelX * cos(rad);
        double accelE = accelX * sin(rad);

        // Update Velocities (Meters per second)
        currentState.velN += accelN * dt;
        currentState.velE += accelE * dt;
        currentState.velD += accelZ * dt;
        // Add these two lines back in!
        currentState.posN += currentState.velN * dt;
        currentState.posE += currentState.velE * dt;

        // --- 3. THE GPS ENGINE (Converting Meters to Degrees) ---
        // ... (rest of your GPS code)

        // --- 3. THE GPS ENGINE (Converting Meters to Degrees) ---
        const double R = 6371000.0; // Earth Radius
        
        // Update Latitude
        currentState.lat += (currentState.velN * dt / R) * (180.0 / M_PI);
        
        // Update Longitude (Adjusted for Latitude)
        double cosLat = cos(currentState.lat * M_PI / 180.0);
        currentState.lon += (currentState.velE * dt / (R * cosLat)) * (180.0 / M_PI);
        
        currentState.alt -= currentState.velD * dt;

        // --- 3. PRINT THE GLOBAL STATUS ---
        std::cout << std::fixed << std::setprecision(6) // 6 decimals for GPS accuracy
                  << time << "s | " 
                  << "Lat: " << currentState.lat << " | " 
                  << "Lon: " << currentState.lon << " | "
                  << "Hdg: " << (int)currentState.heading << "° | "
                  << "Alt: " << (int)currentState.alt << "m";       

        // Phase Detection
        if (std::abs(currentState.velD) < 0.1) {
            std::cout << " >>> [CRUISE]";
        } else if (-currentState.velD > 0.1) {
            std::cout << " ^^^ [CLIMBING]";
        } else {
            std::cout << " vvv [DESCENDING]";
        }
        std::cout << std::endl;

        // --- 4. RECORD TO BLACK BOX ---
        if (logFile.is_open()) {
            // Now currentState.time and currentState.gForce are valid!
            logFile << currentState.time << "," << currentState.lat << "," 
                    << currentState.lon << "," << currentState.alt << "," 
                    << currentState.heading << "," << currentState.gForce << "\n";
        }
    }

    logFile.close(); // <--- Now this happens AFTER the loop finishes
    std::cout << ">>> Flight data saved to 02_Core_Nav/logs/navigation_log.csv" << std::endl;
} // <--- This bracket closes the FUNCTION