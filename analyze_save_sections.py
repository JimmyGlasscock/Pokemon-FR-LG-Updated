#!/usr/bin/env python3
"""
Analyze FireRed save file sections
"""

import struct

def read_save_section(data, section_offset):
    """Read a save section and return its info"""
    if section_offset + 0xFF8 > len(data):
        return None
    
    # Save section structure:
    # 0x000-0xFF3: Data
    # 0xFF4-0xFF7: Section ID, checksum
    # 0xFF8-0xFFB: Signature (0x08012025 for valid section)
    # 0xFFC-0xFFF: Save index (counter)
    
    section_id = struct.unpack('<H', data[section_offset + 0xFF4:section_offset + 0xFF6])[0]
    checksum = struct.unpack('<H', data[section_offset + 0xFF6:section_offset + 0xFF8])[0]
    signature = struct.unpack('<I', data[section_offset + 0xFF8:section_offset + 0xFFC])[0]
    save_index = struct.unpack('<I', data[section_offset + 0xFFC:section_offset + 0x1000])[0]
    
    return {
        'section_id': section_id,
        'checksum': checksum,
        'signature': signature,
        'save_index': save_index,
        'valid': signature == 0x08012025
    }

def check_var_in_section(data, section_offset, var_num):
    """Check VAR value in a specific section"""
    # Section 1 contains variables at offset 0x00F0 in the section
    VARS_OFFSET_IN_SECTION1 = 0x00F0
    
    var_offset = section_offset + VARS_OFFSET_IN_SECTION1 + ((var_num - 0x4000) * 2)
    
    if var_offset + 1 < len(data):
        value = struct.unpack('<H', data[var_offset:var_offset+2])[0]
        return value
    return None

def main():
    save_file = r"c:\Users\Jimmy\Documents\decomps\pokefirered\pokefirered_rev1.sav"
    
    print(f"Analyzing save file: {save_file}\n")
    
    with open(save_file, 'rb') as f:
        data = f.read()
    
    print(f"Save file size: {len(data)} bytes\n")
    
    # FireRed has 2 save slots (A and B), each is 14 sections * 0x1000 bytes = 0xE000
    save_slots = [
        ('Save Slot A', 0x0000),
        ('Save Slot B', 0xE000)
    ]
    
    for slot_name, base_offset in save_slots:
        print(f"{'='*60}")
        print(f"{slot_name} at 0x{base_offset:05X}")
        print(f"{'='*60}")
        
        if base_offset + 0xE000 > len(data):
            print("  SLOT DOESN'T EXIST (file too small)\n")
            continue
        
        # Check section 0 (contains save index)
        section0_info = read_save_section(data, base_offset)
        if section0_info:
            print(f"  Section 0:")
            print(f"    Valid: {section0_info['valid']}")
            print(f"    Save Index: {section0_info['save_index']}")
            
            # Check section 1 (contains variables)
            section1_offset = base_offset + 0x1000
            section1_info = read_save_section(data, section1_offset)
            if section1_info and section1_info['valid']:
                print(f"  Section 1:")
                print(f"    Valid: {section1_info['valid']}")
                
                # Check VAR_MAP_SCENE_CHRONOS_ISLE in this section
                var_value = check_var_in_section(data, section1_offset, 0x408C)
                print(f"    VAR_MAP_SCENE_CHRONOS_ISLE (0x408C): {var_value}")
        print()
    
    print("\nThe game uses whichever save slot has the HIGHER save index.")

if __name__ == "__main__":
    main()
