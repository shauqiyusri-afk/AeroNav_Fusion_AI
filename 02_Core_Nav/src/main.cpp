#include <iostream>
#include <string>
#include "../include/navigation_states.hpp"

// Forward declaration
void read_sensor_data(std::string filename);

int main() {
    std::cout << "--- AeroNav Fusion AI: Core Brain Starting ---" << std::endl;
    
    // SYNC THIS PATH:
    // In 02_Core_Nav/src/main.cpp
    std::string flight_log = "05_Simulation/data/test_flight_01.csv";
    read_sensor_data(flight_log);

    std::cout << "--- Processing Complete ---" << std::endl;
    return 0;
}