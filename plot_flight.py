import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import os

log_path = os.path.join("02_Core_Nav", "logs", "navigation_log.csv")

if not os.path.exists(log_path):
    print("Error: navigation_log.csv not found!")
else:
    df = pd.read_csv("02_Core_Nav/logs/navigation_log.csv")
    df = df.iloc[50:]
    df.columns = df.columns.str.strip()

    # --- CALCULATIONS ---
    # Calculate Ground Speed (m/s) using diff of lat/lon is complex, 
    # so we'll use the speed magnitude if available or a simplified version
    # For now, let's plot Altitude and Heading changes as telemetry
    
    fig = plt.figure(figsize=(14, 10))
    plt.subplots_adjust(hspace=0.4)

    # 1. TOP PANEL: 3D PATH
    ax1 = fig.add_subplot(2, 1, 1, projection='3d')
    ax1.plot(df['lon'], df['lat'], df['alt'], color='red', lw=2, label='Flight Path')
    ax1.scatter(df['lon'].iloc[0], df['lat'].iloc[0], df['alt'].iloc[0], color='green', s=100)
    ax1.set_title("AI-Based INS/GNSS Fusion: Cessna Global Profile", fontsize=14)
    ax1.set_zlabel("Altitude (m)")
    ax1.view_init(elev=25, azim=-45)

    # 2. BOTTOM LEFT: ALTITUDE OVER TIME
    ax2 = fig.add_subplot(2, 2, 3)
    ax2.plot(df['time'], df['alt'], color='blue', lw=1.5)
    ax2.set_title("Flight Telemetry: Altitude Profile")
    ax2.set_xlabel("Time (s)")
    ax2.set_ylabel("Altitude (m)")
    ax2.grid(True, alpha=0.3)

    # 3. BOTTOM RIGHT: HEADING (Direction)
    # This shows us exactly when the turn happens!
    ax3 = fig.add_subplot(2, 2, 4)
    ax3.plot(df['time'], df['heading'], color='orange', lw=1.5)
    ax3.set_title("Flight Telemetry: Heading (Course)")
    ax3.set_xlabel("Time (s)")
    ax3.set_ylabel("Degrees (°)")
    ax3.grid(True, alpha=0.3)

    print(">>> Dashboard Active: Monitoring Cessna Systems...")
    plt.show()