#include "../include/navigation_states.hpp"
#include <vector>
#include <cmath>

// This is our 'f(t, y)' - The Derivative Function
// It calculates how the state changes (velocity, position) based on current sensors
NavState compute_derivatives(const NavState& state, double ax, double ay, double az) {
    NavState delta;
    
    // --- EARTH CONSTANTS ---
    const double R = 6371000.0; // Radius of Earth in meters
    const double rad2deg = 57.2957795; // (180 / PI) to convert to degrees

    // 1. Position Derivatives (Converting Velocity to Degrees/Second)
    
    // Change in Latitude: Velocity North / Radius
    delta.lat = (state.velN / R) * rad2deg; 

    // Change in Longitude: Velocity East / (Radius * cos(Latitude))
    // We use cos(lat) because the Earth gets "skinnier" at the top!
    double cosLat = std::cos(state.lat * (3.14159 / 180.0));
    delta.lon = (state.velE / (R * cosLat)) * rad2deg;

    delta.alt = -state.velD; // Standard: Negative Down = Positive Altitude

    // 2. Velocity Derivatives (Change in Velocity = Acceleration)
    delta.velN = ax; 
    delta.velE = ay;
    delta.velD = az;

    return delta;
}

// The RK4 Integration Step
// The RK4 Integration Step
NavState propagate_state_rk4(NavState current_state, double ax, double ay, double az, double dt) {
    NavState k1, k2, k3, k4, next_state;

    // --- FIX: Use next_state to store the result ---
    double totalAccel = std::sqrt(ax*ax + ay*ay + az*az);
    next_state.gForce = totalAccel / 9.81; 
    
    // Also pass the time forward
    next_state.time = current_state.time + dt;

    // ... rest of your RK4 math ...

    // k1: Slope at the beginning of the interval
    k1 = compute_derivatives(current_state, ax, ay, az);

    // k2: Slope at the midpoint (using k1 to guess)
    NavState state_k2 = current_state;
    state_k2.lat += k1.lat * (dt/2.0); // ...and so on for all states
    k2 = compute_derivatives(state_k2, ax, ay, az);

    // k3: Slope at the midpoint again (using k2 to guess)
    NavState state_k3 = current_state;
    state_k3.lat += k2.lat * (dt/2.0);
    k3 = compute_derivatives(state_k3, ax, ay, az);

    // k4: Slope at the end of the interval
    NavState state_k4 = current_state;
    state_k4.lat += k3.lat * dt;
    k4 = compute_derivatives(state_k4, ax, ay, az);

    // Final "Golden Average" Step: state = old + (dt/6) * (k1 + 2k2 + 2k3 + k4)
    next_state.lat = current_state.lat + (dt/6.0) * (k1.lat + 2*k2.lat + 2*k3.lat + k4.lat);
    next_state.velN = current_state.velN + (dt/6.0) * (k1.velN + 2*k2.velN + 2*k3.velN + k4.velN);
    // ... we repeat this for all 15 states

    return next_state;
}