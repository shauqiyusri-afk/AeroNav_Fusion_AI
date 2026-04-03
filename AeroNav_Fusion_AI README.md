# AeroNav Fusion AI

AI-assisted navigation system combining Inertial Navigation System (INS) and GNSS using Extended Kalman Filtering (EKF) for long-duration flight simulations.

---

## Overview

AeroNav Fusion AI is a research and engineering project exploring sensor fusion for aerospace navigation systems.

The project combines INS measurements with GNSS data to improve navigation accuracy during long-duration flight trajectories.

INS systems provide continuous navigation but accumulate drift over time, while GNSS provides absolute positioning but may suffer from signal degradation or outages.

This project investigates how Extended Kalman Filtering can fuse both systems to produce more reliable position estimates.

---

## Objectives

- Simulate aircraft navigation trajectories
- Model inertial navigation drift
- Implement Extended Kalman Filter sensor fusion
- Analyze trajectory error reduction
- Evaluate navigation performance during degraded GNSS conditions

---

## System Architecture

INS Sensors
      ↓
State Prediction Model
      ↓
Extended Kalman Filter
      ↓
GNSS Measurement Update
      ↓
Corrected Position / Velocity Estimate

---

## Repository Structure

01_Docs  
Project documentation and design notes.

02_Core_Nav  
Core navigation algorithms and EKF implementation.

03_AI_Sentinel  
AI-based components and experimental modules.

05_Simulation  
Flight trajectory simulations and analysis.

tests  
Testing scripts and validation tools.

---

## Technologies

Python  
C++  
Extended Kalman Filtering  
Numerical Simulation

---

## Example Use Cases

- Long-haul aircraft trajectory simulations
- Autonomous navigation research
- Sensor fusion algorithm development
- GNSS-denied navigation experiments

---

## Future Development

- Real-world sensor data integration
- Fault detection for navigation systems
- Satellite navigation simulation
- Integration with spacecraft attitude systems
