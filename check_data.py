import pandas as pd
import os

# Direct absolute path
log_path = r"C:\Users\shauqi\Desktop\AeroNav_Fusion_AI\02_Core_Nav\logs\navigation_log.csv"

if not os.path.exists(log_path):
    print("STILL NOT FOUND!")
else:
    df = pd.read_csv(log_path)
    print("--- SUCCESS! ---")
    print("Your CSV actually contains these columns:")
    print(df.columns.tolist())
    
    if 'posE' in df.columns and 'posN' in df.columns:
        print("\nPhysics Check:")
        print(f"Max East: {df['posE'].max()}m")
        print(f"Max North: {df['posN'].max()}m")
    else:
        print("\nWARNING: Your C++ code is still writing the OLD column names!")