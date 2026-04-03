import pandas as pd
import matplotlib.pyplot as plt
import os
log_path = r"02_Core_Nav\logs\navigation_log.csv"
df = pd.read_csv("02_Core_Nav/logs/navigation_log.csv")
df = df.iloc[50:]
fig, ax = plt.subplots()
ax.plot(df['posE'], df['posN'], 'b-', label='Flight Path')
ax.axis('equal')
ax.set_title('AeroNav: 2D Flight Path')
plt.grid(True)
plt.show()
