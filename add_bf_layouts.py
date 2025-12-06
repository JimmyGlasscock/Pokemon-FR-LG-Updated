#!/usr/bin/env python3
import json

# Read FireRed's layouts.json
with open('data/layouts/layouts.json', 'r') as f:
    firered = json.load(f)

# Read Emerald's layouts reference
with open('bf_layouts_reference.json', 'r') as f:
    emerald = json.load(f)

# Extract Battle Frontier layouts from Emerald
bf_layouts = [layout for layout in emerald['layouts'] if layout['id'].startswith('LAYOUT_BATTLE_FRONTIER_')]
bf_layouts.sort(key=lambda x: x['id'])

# Add border_width and border_height to each layout
for layout in bf_layouts:
    layout['border_width'] = 2
    layout['border_height'] = 2

# Append to FireRed's layouts
firered['layouts'].extend(bf_layouts)

# Write back with proper formatting (2-space indent)
with open('data/layouts/layouts.json', 'w') as f:
    json.dump(firered, f, indent=2)
    f.write('\n')  # Add newline at end of file

print(f"Added {len(bf_layouts)} Battle Frontier layouts")
print(f"Total layouts: {len(firered['layouts'])}")
