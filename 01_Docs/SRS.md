# System Requirements Specification (SRS)
**Project:** AI-Based INS/GNSS Fusion for Resilient Aircraft Navigation

## 1. Project Objective
To develop a navigation monitoring system that ensures RNP 0.3 (Required Navigation Performance) integrity by detecting GNSS anomalies (jamming/spoofing) using AI-driven EKF residual analysis.

## 2. Navigation Requirements (Layer 1 & 2)
* **Accuracy:** The system must maintain horizontal accuracy within 0.3 Nautical Miles.
* **Integrity:** The system must provide an alert within 6 seconds if the Protection Level exceeds the Alarm Limit.
* **Continuity:** During a total GNSS outage, the AI-corrected INS must maintain RNP 0.3 for at least 60 seconds.

## 3. AI Sentinel Requirements (Layer 3)
* **Detection Latency:** Detect "Ramp Spoofing" (slow drift) before it exceeds 10 meters/second squared.
* **Robustness:** AI must distinguish between high-dynamic maneuvers (turns) and signal interference.
* **Recovery:** AI shall provide a "repaired" pseudo-GNSS signal to re-initialize the EKF after interference clears.

## 4. Technical Stack
* **Core:** C++ (Strapdown INS & EKF)
* **AI:** Python (PyTorch/TensorFlow - LSTM Autoencoder)
* **Integration:** pybind11 Bridge