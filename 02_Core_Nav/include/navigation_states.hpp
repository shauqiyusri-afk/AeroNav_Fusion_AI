#ifndef NAVIGATION_STATES_HPP
#define NAVIGATION_STATES_HPP

struct NavState {
    // 1. GPS Coordinates (Degrees)
    double lat = 3.1390;   
    double lon = 101.6869;
    double alt = 0.0;
    double time = 0.0;

    // 2. Local Meters (Requested by data_reader.cpp)
    double posN = 0.0;     
    double posE = 0.0;

    // 3. Velocities (Requested as vN, vE, vD)
    double vN = 0.0;     
    double vE = 0.0;     
    double vD = 0.0;     

    // 4. Needed for RK4 logic
    double velN = 0.0;
    double velE = 0.0;
    double velD = 0.0;

    double heading = 0.0;
    double gForce = 0.0;
};

#endif