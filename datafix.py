import numpy as np
import pandas as pd

def fix_dates(data):
    for i in range(1, len(data) - 1):
        prev_val = data.iloc[i - 1, 0]
        next_val = data.iloc[i + 1, 0]
        
        if prev_val == next_val:
            data.iloc[i, 0] = prev_val

def fix_services(data):
    for i in range(0,len(data)):
        val = str(data.iloc[i, 1])
        if len(val) in range(6,10):
            data.iloc[i, 1] = "National"
        elif len(val) > 10:
            data.iloc[i, 1] = "International"
        elif len(val) != 0:
            data.iloc[i, 1] = ""

data = pd.read_csv(filepath_or_buffer="revised.csv", sep=";")
fix_dates(data)
fix_services(data)
data.to_csv(path_or_buf="revised.csv", sep=";", index=False)



