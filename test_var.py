#!/usr/bin/env python3
"""
Test if VAR_MAP_SCENE_CHRONOS_ISLE is actually being checked
"""

import struct

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
    
    print(f"Setting VAR_MAP_SCENE_CHRONOS_ISLE to 1 (should disable trigger)...")
    
    with open(save_file, 'rb') as f:
        data = f.read()
    
    # Set VAR_MAP_SCENE_CHRONOS_ISLE to 1
    data = set_var(data, 0x408C, 1)
    
    # Write test save
    test_save = save_file.replace('.sav', '_test_var1.sav')
    with open(test_save, 'wb') as f:
        f.write(data)
    
    print(f"Created test save: {test_save}")
    print("Load this save - the event should NOT trigger")
    print("")
    print("Then set it back to 0:")
    
    # Set back to 0
    data = set_var(data, 0x408C, 0)
    test_save2 = save_file.replace('.sav', '_test_var0.sav')
    with open(test_save2, 'wb') as f:
        f.write(data)
    
    print(f"Created test save: {test_save2}")
    print("Load this save - the event SHOULD trigger")

if __name__ == "__main__":
    main()
