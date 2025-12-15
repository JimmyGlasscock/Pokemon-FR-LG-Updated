#!/usr/bin/env python3
"""
Fix VAR_MAP_SCENE_CHRONOS_ISLE in save file - set it to 0
"""

import struct
import shutil

def set_var(data, var_num, value):
    """Set a specific variable in the save data"""
    VARS_OFFSET = 0x1340
    
    # Each var is 2 bytes (16-bit value)
    var_offset = VARS_OFFSET + ((var_num - 0x4000) * 2)
    
    if var_offset + 1 < len(data):
        # Create mutable bytearray
        data_array = bytearray(data)
        struct.pack_into('<H', data_array, var_offset, value)
        return bytes(data_array)
    return data

def main():
    save_file = r"c:\Users\Jimmy\Documents\decomps\pokefirered\pokefirered_rev1.sav"
    backup_file = save_file + ".backup_var"
    
    print(f"Reading save file: {save_file}")
    with open(save_file, 'rb') as f:
        data = f.read()
    
    print(f"Creating backup: {backup_file}")
    shutil.copy2(save_file, backup_file)
    
    # Set VAR_MAP_SCENE_CHRONOS_ISLE to 0
    var_chronos = 0x408C
    print(f"\nSetting VAR_MAP_SCENE_CHRONOS_ISLE (0x{var_chronos:04X}) to 0...")
    data = set_var(data, var_chronos, 0)
    
    print(f"\nWriting modified save file...")
    with open(save_file, 'wb') as f:
        f.write(data)
    
    print("\n✓ Save file fixed!")
    print(f"\nVAR_MAP_SCENE_CHRONOS_ISLE is now set to 0")
    print("The Brendan event should trigger when you walk to (12-14, 25)")

if __name__ == "__main__":
    main()
