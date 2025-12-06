# Battle Frontier Port - Phase 1: Maps and Tilesets

## Overview
This guide covers porting all Battle Frontier maps and tilesets from pokeemerald to pokefirered.

**Total Scope:**
- 11 Tilesets
- 46 Map folders
- ~500+ individual files

## Step 1: Download All Tileset Data from pokeemerald

### Tilesets to Copy (from data/tilesets/secondary/)

1. **battle_frontier**
2. **battle_frontier_outside_west**
3. **battle_frontier_outside_east**
4. **battle_palace**
5. **battle_dome**
6. **battle_factory**
7. **battle_pike**
8. **battle_arena**
9. **battle_pyramid**
10. **battle_frontier_ranking_hall**
11. **battle_tent**

### For Each Tileset, Copy These Files:

```
data/tilesets/secondary/{tileset_name}/
├── tiles.png
├── tiles.4bpp (if exists)
├── tiles.4bpp.lz (if exists)
├── metatiles.bin
├── metatile_attributes.bin
└── palettes/
    ├── 00.gbapal
    ├── 01.gbapal
    ├── 02.gbapal
    ... (through 15.gbapal)
```

### PowerShell Download Script

Save this as `download_bf_tilesets.ps1`:

```powershell
# Battle Frontier Tileset Downloader
$baseUrl = "https://raw.githubusercontent.com/pret/pokeemerald/master/data/tilesets/secondary"
$outputBase = "C:\Users\Jimmy\Documents\decomps\pokefirered\data\tilesets\secondary"

$tilesets = @(
    "battle_frontier",
    "battle_frontier_outside_west",
    "battle_frontier_outside_east",
    "battle_palace",
    "battle_dome",
    "battle_factory",
    "battle_pike",
    "battle_arena",
    "battle_pyramid",
    "battle_frontier_ranking_hall",
    "battle_tent"
)

foreach ($tileset in $tilesets) {
    Write-Host "Downloading $tileset..." -ForegroundColor Green
    
    # Create directory
    $tilesetDir = Join-Path $outputBase $tileset
    $paletteDir = Join-Path $tilesetDir "palettes"
    New-Item -ItemType Directory -Force -Path $tilesetDir | Out-Null
    New-Item -ItemType Directory -Force -Path $paletteDir | Out-Null
    
    # Download main files
    $files = @("tiles.png", "metatiles.bin", "metatile_attributes.bin")
    foreach ($file in $files) {
        $url = "$baseUrl/$tileset/$file"
        $output = Join-Path $tilesetDir $file
        try {
            Invoke-WebRequest -Uri $url -OutFile $output -ErrorAction Stop
            Write-Host "  ✓ $file" -ForegroundColor Gray
        } catch {
            Write-Host "  ✗ $file (not found or error)" -ForegroundColor Yellow
        }
    }
    
    # Download palette files (00.gbapal through 15.gbapal)
    for ($i = 0; $i -le 15; $i++) {
        $palNum = "{0:D2}" -f $i
        $url = "$baseUrl/$tileset/palettes/$palNum.gbapal"
        $output = Join-Path $paletteDir "$palNum.gbapal"
        try {
            Invoke-WebRequest -Uri $url -OutFile $output -ErrorAction Stop
        } catch {
            # Silently skip missing palettes
        }
    }
}

Write-Host "`nTileset download complete!" -ForegroundColor Green
```

## Step 2: Download All Map Data from pokeemerald

### Maps to Copy (from data/maps/)

All 46 Battle Frontier maps - see full list in previous output.

### For Each Map, Copy These Files:

```
data/maps/{MapName}/
├── map.json
├── scripts.inc (if exists)
└── text.inc (if exists)
```

### PowerShell Download Script for Maps

Save this as `download_bf_maps.ps1`:

```powershell
# Battle Frontier Maps Downloader
$baseUrl = "https://raw.githubusercontent.com/pret/pokeemerald/master/data/maps"
$outputBase = "C:\Users\Jimmy\Documents\decomps\pokefirered\data\maps"

$maps = @(
    "BattleFrontier_OutsideWest",
    "BattleFrontier_OutsideEast",
    "BattleFrontier_BattleTowerLobby",
    "BattleFrontier_BattleTowerElevator",
    "BattleFrontier_BattleTowerCorridor",
    "BattleFrontier_BattleTowerBattleRoom",
    "BattleFrontier_BattleTowerMultiPartnerRoom",
    "BattleFrontier_BattleTowerMultiCorridor",
    "BattleFrontier_BattleTowerMultiBattleRoom",
    "BattleFrontier_BattleDomeLobby",
    "BattleFrontier_BattleDomeCorridor",
    "BattleFrontier_BattleDomePreBattleRoom",
    "BattleFrontier_BattleDomeBattleRoom",
    "BattleFrontier_BattlePalaceLobby",
    "BattleFrontier_BattlePalaceCorridor",
    "BattleFrontier_BattlePalaceBattleRoom",
    "BattleFrontier_BattlePyramidLobby",
    "BattleFrontier_BattlePyramidFloor",
    "BattleFrontier_BattlePyramidTop",
    "BattleFrontier_BattleArenaLobby",
    "BattleFrontier_BattleArenaCorridor",
    "BattleFrontier_BattleArenaBattleRoom",
    "BattleFrontier_BattleFactoryLobby",
    "BattleFrontier_BattleFactoryPreBattleRoom",
    "BattleFrontier_BattleFactoryBattleRoom",
    "BattleFrontier_BattlePikeLobby",
    "BattleFrontier_BattlePikeCorridor",
    "BattleFrontier_BattlePikeThreePathRoom",
    "BattleFrontier_BattlePikeRoomNormal",
    "BattleFrontier_BattlePikeRoomFinal",
    "BattleFrontier_BattlePikeRoomWildMons",
    "BattleFrontier_RankingHall",
    "BattleFrontier_Lounge1",
    "BattleFrontier_ExchangeServiceCorner",
    "BattleFrontier_Lounge2",
    "BattleFrontier_Lounge3",
    "BattleFrontier_Lounge4",
    "BattleFrontier_ScottsHouse",
    "BattleFrontier_Lounge5",
    "BattleFrontier_Lounge6",
    "BattleFrontier_Lounge7",
    "BattleFrontier_ReceptionGate",
    "BattleFrontier_Lounge8",
    "BattleFrontier_Lounge9",
    "BattleFrontier_PokemonCenter_1F",
    "BattleFrontier_PokemonCenter_2F",
    "BattleFrontier_Mart"
)

foreach ($map in $maps) {
    Write-Host "Downloading $map..." -ForegroundColor Cyan
    
    # Create directory
    $mapDir = Join-Path $outputBase $map
    New-Item -ItemType Directory -Force -Path $mapDir | Out-Null
    
    # Download files
    $files = @("map.json", "scripts.inc", "text.inc")
    foreach ($file in $files) {
        $url = "$baseUrl/$map/$file"
        $output = Join-Path $mapDir $file
        try {
            Invoke-WebRequest -Uri $url -OutFile $output -ErrorAction Stop
            Write-Host "  ✓ $file" -ForegroundColor Gray
        } catch {
            Write-Host "  ✗ $file (skipped)" -ForegroundColor DarkGray
        }
    }
}

Write-Host "`nMap download complete!" -ForegroundColor Green
```

## Step 3: Update FireRed Code Files

After downloading all files, you need to integrate them into the FireRed codebase.

### Files to Modify:

1. **src/data/tilesets/headers.h** - Add tileset definitions
2. **src/data/tilesets/graphics.h** - Add tileset graphics declarations
3. **src/data/tilesets/metatiles.h** - Add metatile declarations
4. **data/maps/map_groups.json** - Add new map group
5. **include/constants/maps.h** - Add map constants (if exists)
6. **include/constants/layouts.h** - Add layout constants (if exists)
7. **graphics_file_rules.mk** - Add tileset build rules
8. **tileset_rules.mk** - Add tileset compilation rules

### Next Steps After Download:

1. Run both PowerShell scripts to download all files
2. Verify all files downloaded correctly
3. Update code files with tileset/map definitions
4. Test compilation
5. Fix any build errors

## Notes

- Some maps may not have scripts.inc or text.inc files
- Not all palettes 00-15 exist for every tileset
- The build system will need significant updates to compile everything
- Initial build will likely have errors that need fixing

## Estimated Time

- Download: 10-15 minutes
- Code integration: 2-4 hours
- Build fixes: 2-6 hours
- **Total for Phase 1: 5-10 hours**
