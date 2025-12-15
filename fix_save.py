#!/usr/bin/env python3
"""
Fix Pokemon FireRed save file - SET FLAG_HIDE_CHRONOS_ISLE_BRENDAN
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

def update_checksum(data):
    """Update the checksum for FireRed save data"""
    # Save sections are 0x1000 bytes each
    # Each section has a checksum at offset 0xFF6-0xFF7
    data_array = bytearray(data)
    
    for section in range(14):
        section_offset = section * 0x1000
        if section_offset + 0x1000 > len(data):
            break
        
        # Calculate checksum for section data (0x000-0xFF3)
        checksum = 0
        for i in range(0xFF4 // 4):
            offset = section_offset + (i * 4)
            if offset + 3 < len(data_array):
                value = struct.unpack('<I', data_array[offset:offset+4])[0]
                checksum = (checksum + value) & 0xFFFFFFFF
        
        # Take upper 16 bits
        checksum = (checksum >> 16) + (checksum & 0xFFFF)
        checksum = (checksum >> 16) + (checksum & 0xFFFF)
        
        # Write checksum
        checksum_offset = section_offset + 0xFF6
        if checksum_offset + 1 < len(data_array):
            struct.pack_into('<H', data_array, checksum_offset, checksum & 0xFFFF)
    
    return bytes(data_array)

def main():
    save_file = r"c:\Users\Jimmy\Documents\decomps\pokefirered\pokefirered_rev1.sav"
    backup_file = save_file + ".backup"
    
    print(f"Reading save file: {save_file}")
    with open(save_file, 'rb') as f:
        data = f.read()
    
    print(f"Creating backup: {backup_file}")
    shutil.copy2(save_file, backup_file)
    
    # Set FLAG_HIDE_CHRONOS_ISLE_BRENDAN (0x21E = 542 decimal)
    flag_brendan = 0x21E
    print(f"\nSetting FLAG_HIDE_CHRONOS_ISLE_BRENDAN (0x{flag_brendan:03X})...")
    data = set_flag(data, flag_brendan)
    
    print("Updating checksums...")
    data = update_checksum(data)
    
    print(f"\nWriting modified save file...")
    with open(save_file, 'wb') as f:
        f.write(data)
    
    print("\n✓ Save file fixed!")
    print("\nWhat was changed:")
    print("  - FLAG_HIDE_CHRONOS_ISLE_BRENDAN is now SET (Brendan hidden)")
    print("  - When you walk to y-coordinate 25, the coord event will trigger")
    print("  - The event will clear the flag and add Brendan dynamically")
    print("\nNow rebuild the ROM with 'make' and test in-game!")

if __name__ == "__main__":
    main()
