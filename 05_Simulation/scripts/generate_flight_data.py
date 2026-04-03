import numpy as np
import pandas as pd
import os

def generate_sydney_mission():
    dt = 0.01 
    # 1. THE TIME: Change to 3600 seconds (1 Hour)
    t = np.arange(0, 3600, dt) 
    n_samples = len(t)

    # 2. THE THRUST: 0.5 m/s^2 for a slow, steady push to cruise speed
    # We add very tiny noise (0.01) so it looks realistic
    imu_accel_x = np.full(n_samples, 0.05) + np.random.normal(0, 0.01, n_samples)
    
    # Initial takeoff burst for the first 20 seconds
    imu_accel_x[:int(20/dt)] = 3.5 

    # 3. THE CLIMB: Climb for 10 minutes (600s) to reach ~10,000m
    imu_accel_z = np.zeros(n_samples)
    # --- THE PRECISION CLIMB ---
    for i in range(n_samples):
        if t[i] < 600.0:
            # 1. THE CLIMB: -0.4 is a lot of push. Let's make it -0.2
            imu_accel_z[i] = -0.05 + np.random.normal(0, 0.01) 
        elif t[i] < 1200.0:
            # 2. THE LEVEL-OFF: This MUST be the exact opposite to stop the ascent
            # If you pushed "up" for 600s, you need to push "down" to stop the speed!
            imu_accel_z[i] = 0.05 + np.random.normal(0, 0.01)
        else:
            # 3. THE CRUISE: Absolute zero vertical acceleration
            imu_accel_z[i] = 0.0 + np.random.normal(0, 0.001)

    # 4. THE TURN: A slight heading adjustment toward Australia (South-East)
    imu_gyro_z = np.zeros(n_samples)
    # Turn at 15 minutes into the flight
    turn_start = int(900 / dt)
    turn_end = int(920 / dt)
    imu_gyro_z[turn_start:turn_end] = 0.05 # A gentle 20-second bank

    # --- NO GLITCHES HERE ---
    # We want a clean mission for the long-haul test

    data = pd.DataFrame({
        'time': t, 
        'accel_x': imu_accel_x, 
        'accel_z': imu_accel_z, 
        'gyro_z': imu_gyro_z 
    })

    # Save to the same path so the C++ reads it automatically
    save_path = "05_Simulation/data/test_flight_01.csv"
    data.to_csv(save_path, index=False)
    print(f"--- SYDNEY MISSION DATA GENERATED: {n_samples} samples ---")

if __name__ == "__main__":
    generate_sydney_mission()