#include <iostream>
#include <cmath>

// This is the "Sentinel" function
bool is_data_safe(double accel) {
    // 50 m/s^2 is roughly 5G. A Cessna can't do this.
    const double MAX_SAFE_ACCEL = 50.0; 

    if (std::abs(accel) > MAX_SAFE_ACCEL) {
        return false; // Anomaly detected!
    }
    return true; // Data is clean
}