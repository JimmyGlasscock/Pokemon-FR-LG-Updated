#!/usr/bin/env python3
"""
Set FLAG_HIDE_CHRONOS_ISLE_BRENDAN in save file
"""

import struct
import shutil

def set_flag(data, flag_num):
    """Set a specific flag in the save data"""
    FLAGS_OFFSET = 0x1270
    
    byte_offset = FLAGS_OFFSET + (flag_num // 8)
    bit_offset = flag_num % 8
    
    if byte_offset < len(data):
        byte_value = data[byte_offset]
        # Set the bit
        new_value = byte_value | (1 << bit_offset)
        # Create mutable bytearray
        data_array = bytearray(data)
        data_array[byte_offset] = new_value
        return bytes(data_array)
    return data

def main():
    save_file = r"c:\Users\Jimmy\Documents\decomps\pokefirered\pokefirered_rev1.sav"
    backup_file = save_file + ".backup_flag"
    
    print(f"Reading save file: {save_file}")
    with open(save_file, 'rb') as f:
        data = f.read()
    
    print(f"Creating backup: {backup_file}")
    shutil.copy2(save_file, backup_file)
    
    # Set FLAG_HIDE_CHRONOS_ISLE_BRENDAN (0x21E = 542 decimal)
    flag_brendan = 0x21E
    print(f"\nSetting FLAG_HIDE_CHRONOS_ISLE_BRENDAN (0x{flag_brendan:03X}) to SET...")
    data = set_flag(data, flag_brendan)
    
    print(f"\nWriting modified save file...")
    with open(save_file, 'wb') as f:
        f.write(data)
    
    print("\n✓ Save file fixed!")
    print("\nFLAG_HIDE_CHRONOS_ISLE_BRENDAN is now SET")
    print("Brendan will be hidden until the coord event triggers.")
    print("When you walk to (12-14, 25), the event will:")
    print("  1. Clear the flag")
    print("  2. Add Brendan object dynamically")
    print("  3. Play the cutscene")

if __name__ == "__main__":
    main()
