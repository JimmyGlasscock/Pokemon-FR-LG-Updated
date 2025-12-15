#!/usr/bin/env python3
"""
Check Pokemon FireRed save file for specific flags and variables
"""

import struct

def read_save_file(filename):
    with open(filename, 'rb') as f:
        return f.read()

def check_flag(data, flag_num):
    """Check if a specific flag is set in the save data"""
    # Flags start at offset 0x1270 in FireRed save data
    FLAGS_OFFSET = 0x1270
    
    byte_offset = FLAGS_OFFSET + (flag_num // 8)
    bit_offset = flag_num % 8
    
    if byte_offset < len(data):
        byte_value = data[byte_offset]
        is_set = (byte_value >> bit_offset) & 1
        return is_set
    return None

def check_var(data, var_num):
    """Check the value of a specific variable in the save data"""
    # Variables start at offset 0x1340 in FireRed save data
    VARS_OFFSET = 0x1340
    
    # Each var is 2 bytes (16-bit value)
    var_offset = VARS_OFFSET + ((var_num - 0x4000) * 2)
    
    if var_offset + 1 < len(data):
        value = struct.unpack('<H', data[var_offset:var_offset+2])[0]
        return value
    return None

def main():
    save_file = r"c:\Users\Jimmy\Documents\decomps\pokefirered\pokefirered_rev1.sav"
    
    print(f"Reading save file: {save_file}")
    data = read_save_file(save_file)
    print(f"Save file size: {len(data)} bytes\n")
    
    # Check FLAG_HIDE_CHRONOS_ISLE_BRENDAN (0x21E = 542 decimal)
    flag_brendan = 0x21E
    flag_state = check_flag(data, flag_brendan)
    print(f"FLAG_HIDE_CHRONOS_ISLE_BRENDAN (0x{flag_brendan:03X}):")
    print(f"  State: {'SET (hidden)' if flag_state else 'CLEAR (visible)'}")
    print()
    
    # Check VAR_MAP_SCENE_CHRONOS_ISLE (0x408C)
    var_scene = 0x408C
    var_value = check_var(data, var_scene)
    print(f"VAR_MAP_SCENE_CHRONOS_ISLE (0x{var_scene:04X}):")
    print(f"  Value: {var_value}")
    print(f"  Event trigger: {'YES (value is 0)' if var_value == 0 else 'NO (value must be 0)'}")
    print()
    
    # Check some other related flags
    print("Other Chronos flags:")
    for name, flag_hex in [
        ("FLAG_HIDE_CHRONOS_BRENDAN", 0x21C),
        ("FLAG_DEFEATED_CHRONOS_BRENDAN", 0x21D),
        ("FLAG_RECEIVED_CHRONOS_TICKET", 0x1BC),
        ("FLAG_SHOWN_CHRONOS_TICKET", 0x2E7),
        ("FLAG_SYS_SEVII_MAP_CHRONOS", None),
        ("FLAG_WORLD_MAP_CHRONOS_ISLE", None),
        ("FLAG_ENABLE_SHIP_CHRONOS_ISLE", None),
    ]:
        if flag_hex is not None:
            state = check_flag(data, flag_hex)
            if state is not None:
                print(f"  {name} (0x{flag_hex:03X}): {'SET' if state else 'CLEAR'}")
    
    print("\n" + "="*60)
    print("DIAGNOSIS:")
    print("="*60)
    
    if flag_state == 1:
        print("❌ PROBLEM: FLAG_HIDE_CHRONOS_ISLE_BRENDAN is SET")
        print("   This hides the Brendan NPC object.")
        print("   The flag should be CLEAR for Brendan to appear.")
    elif var_value != 0:
        print("❌ PROBLEM: VAR_MAP_SCENE_CHRONOS_ISLE is not 0")
        print(f"   Current value: {var_value}")
        print("   The event only triggers when this variable equals 0.")
    else:
        print("✓ Both flag and variable are in correct states!")
        print("  Brendan should appear when you enter Chronos Isle.")
        print("\nPossible issues:")
        print("  1. You're already on Chronos Isle when loading the save")
        print("     → The OnTransition script won't run until you leave and return")
        print("  2. The ROM wasn't rebuilt with the latest changes")
        print("     → Make sure you're using the newly built ROM")
        print("  3. You need to walk to coordinates (12-14, 25) to trigger the event")
        print("     → The trigger zone is at y=25, walking north from the harbor")
    
    print("\n" + "="*60)
    print("RECOMMENDED FIX:")
    print("="*60)
    print("If the event still doesn't work, try:")
    print("1. Leave Chronos Isle (go to harbor, take ship away)")
    print("2. Return to Chronos Isle")
    print("3. Walk north to y-coordinate 25 (near the middle of the island)")
    print("\nThe OnTransition script will clear FLAG_HIDE_CHRONOS_ISLE_BRENDAN")
    print("when you enter the map, making Brendan visible for the cutscene.")

if __name__ == "__main__":
    main()
