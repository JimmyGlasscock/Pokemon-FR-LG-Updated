# Violet City Import Guide

## Prerequisites

1. Clone CrystalDust if not already done:
```powershell
cd C:\Users\Jimmy\Documents\decomps
git clone https://github.com/Sierraffinity/CrystalDust.git
```

2. Run the import script:
```powershell
cd C:\Users\Jimmy\Documents\decomps\pokefirered
.\import_violetcity.ps1
```

## What the Script Does

The `import_violetcity.ps1` script will:
- Copy Violet City map files from CrystalDust
- Copy associated tilesets and graphics
- Copy layout files (border.bin, map.bin)
- Copy music files if they exist
- Create all necessary directories

## Manual Integration Steps

After running the script, you need to integrate Violet City into the FireRed engine:

### 1. Add to Map Groups

Edit `data/maps/map_groups.json` and add a new Johto group:

```json
"group_order": [
  ...existing groups...,
  "gMapGroup_JohtoTowns"
],

"gMapGroup_JohtoTowns": [
  "VioletCity"
]
```

### 2. Register the Tileset

Check what tileset Violet City uses in `data/maps/VioletCity/map.json` and add it to:

**`src/data/tilesets/headers.h`:**
```c
const struct Tileset gTileset_VioletCity = 
{
    .isCompressed = TRUE,
    .isSecondary = TRUE,
    .tiles = gTilesetTiles_VioletCity,
    .palettes = gTilesetPalettes_VioletCity,
    .metatiles = gMetatiles_VioletCity,
    .metatileAttributes = gMetatileAttributes_VioletCity,
    .callback = NULL,
};
```

**`src/data/tilesets/metatiles.h`:**
```c
extern const u16 gMetatiles_VioletCity[];
extern const u16 gMetatileAttributes_VioletCity[];
```

**`src/data/tilesets/graphics.h`:**
```c
extern const u32 gTilesetTiles_VioletCity[];
extern const u16 gTilesetPalettes_VioletCity[][16];
```

### 3. Add Map Constants

**`include/constants/map_groups.h`** (this is auto-generated, but check it):
```c
// Johto Towns
#define MAP_VIOLET_CITY (MAP_GROUP(JOHTO_TOWNS, 0))
```

### 4. Build the Project

```powershell
make clean
make -j4
```

## Troubleshooting

### Missing Files
If certain files are missing from CrystalDust, you may need to:
1. Check alternative map names (VioletCity vs Violet_City vs VioletTown)
2. Look in CrystalDust's data/layouts directory for layout data
3. Check if tilesets are shared with other Johto towns

### Build Errors
- **Tileset errors**: Make sure all tileset files are copied and registered
- **Layout errors**: Verify border.bin and map.bin exist in data/layouts/VioletCity
- **Script errors**: CrystalDust scripts may use Emerald-specific scripting that needs conversion

### Testing
To test Violet City in-game, you'll need to:
1. Add a warp to it from an existing map, OR
2. Use a script command to warp there, OR  
3. Modify your player's starting location in `src/new_game.c`

Example warp addition to test:
```c
// In an existing map's scripts
warp MAP_VIOLET_CITY, 255, 10, 10  // Warp to x=10, y=10 in Violet City
```

## Next Steps

Once Violet City works, you can import other Johto cities using the same process:
- NewBarkTown
- CherrygroveCity  
- AzaleaTown
- GoldenrodCity
- Ecruteak City
- Olivine City
- Cianwood City
- Mahogany Town
- Blackthorn City

Create similar import scripts for each town by copying `import_violetcity.ps1` and changing the town name.
