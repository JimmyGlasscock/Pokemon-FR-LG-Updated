# Import Violet City from CrystalDust to pokefirered
# This script copies all necessary files for Violet City from Johto

$crystaldustPath = "C:\Users\Jimmy\Documents\decomps\CrystalDust"
$firedPath = "C:\Users\Jimmy\Documents\decomps\pokefirered"

Write-Host "Importing Violet City from CrystalDust..." -ForegroundColor Green

# Check if CrystalDust exists
if (!(Test-Path $crystaldustPath)) {
    Write-Host "ERROR: CrystalDust not found at $crystaldustPath" -ForegroundColor Red
    Write-Host "Please clone it first: git clone https://github.com/Sierraffinity/CrystalDust.git" -ForegroundColor Yellow
    exit 1
}

# Create directories if they don't exist
$dirs = @(
    "$firedPath\data\tilesets\secondary\violet",
    "$firedPath\data\tilesets\secondary\violet\palettes",
    "$firedPath\graphics\tilesets\secondary\violet",
    "$firedPath\graphics\tilesets\secondary\violet\palettes",
    "$firedPath\data\maps\VioletCity",
    "$firedPath\data\layouts\VioletCity"
)

foreach ($dir in $dirs) {
    if (!(Test-Path $dir)) {
        New-Item -ItemType Directory -Path $dir -Force | Out-Null
        Write-Host "Created directory: $dir" -ForegroundColor Yellow
    }
}

# Copy VioletCity map data
Write-Host "`nCopying VioletCity map data..." -ForegroundColor Cyan

$mapFiles = @(
    "data/maps/VioletCity/map.json",
    "data/maps/VioletCity/scripts.inc",
    "data/maps/VioletCity/text.inc"
)

foreach ($file in $mapFiles) {
    $source = Join-Path $crystaldustPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        Copy-Item $source $dest -Force
        Write-Host "  Copied: $file" -ForegroundColor Green
    } else {
        Write-Host "  WARNING: Source file not found: $file" -ForegroundColor Red
    }
}

# Check for layout files
Write-Host "`nSearching for VioletCity layout files..." -ForegroundColor Cyan

$layoutPatterns = @(
    "data/layouts/VioletCity/border.bin",
    "data/layouts/VioletCity/map.bin"
)

foreach ($file in $layoutPatterns) {
    $source = Join-Path $crystaldustPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        Copy-Item $source $dest -Force
        Write-Host "  Copied: $file" -ForegroundColor Green
    } else {
        Write-Host "  NOTE: Layout file not found: $file" -ForegroundColor Yellow
    }
}

# Try to find and copy the tileset used by Violet City
Write-Host "`nSearching for Violet City tileset..." -ForegroundColor Cyan

# First, check what tileset Violet City uses
$mapJsonPath = "$firedPath\data\maps\VioletCity\map.json"
if (Test-Path $mapJsonPath) {
    $mapJson = Get-Content $mapJsonPath -Raw | ConvertFrom-Json
    $layoutName = $mapJson.layout
    $tilesetPrimary = $mapJson.tileset_primary
    $tilesetSecondary = $mapJson.tileset_secondary
    
    Write-Host "  Layout: $layoutName" -ForegroundColor White
    Write-Host "  Primary Tileset: $tilesetPrimary" -ForegroundColor White
    Write-Host "  Secondary Tileset: $tilesetSecondary" -ForegroundColor White
    
    # Copy secondary tileset if it's a Johto-specific one
    if ($tilesetSecondary -and $tilesetSecondary -ne "gTileset_General") {
        $tilesetName = $tilesetSecondary -replace "gTileset_", ""
        Write-Host "`n  Attempting to copy tileset: $tilesetName" -ForegroundColor Cyan
        
        # Copy tileset data files
        $tilesetFiles = @(
            "data/tilesets/secondary/$tilesetName/metatiles.bin",
            "data/tilesets/secondary/$tilesetName/metatile_attributes.bin",
            "data/tilesets/secondary/$tilesetName/tiles.4bpp.lz"
        )
        
        foreach ($file in $tilesetFiles) {
            $source = Join-Path $crystaldustPath $file
            $dest = Join-Path $firedPath $file
            $destDir = Split-Path $dest -Parent
            if (!(Test-Path $destDir)) {
                New-Item -ItemType Directory -Path $destDir -Force | Out-Null
            }
            if (Test-Path $source) {
                Copy-Item $source $dest -Force
                Write-Host "    Copied: $file" -ForegroundColor Green
            }
        }
        
        # Copy palettes
        for ($i = 0; $i -le 15; $i++) {
            $palNum = $i.ToString("D2")
            $file = "data/tilesets/secondary/$tilesetName/palettes/$palNum.gbapal"
            $source = Join-Path $crystaldustPath $file
            $dest = Join-Path $firedPath $file
            $destDir = Split-Path $dest -Parent
            if (!(Test-Path $destDir)) {
                New-Item -ItemType Directory -Path $destDir -Force | Out-Null
            }
            if (Test-Path $source) {
                Copy-Item $source $dest -Force
                Write-Host "    Copied palette: $palNum.gbapal" -ForegroundColor Green
            }
        }
    }
}

# Copy any Violet City-specific music
Write-Host "`nSearching for Violet City music..." -ForegroundColor Cyan

$musicFiles = @(
    "sound/songs/midi/mus_violetcity.mid",
    "sound/songs/mus_violetcity.s"
)

foreach ($file in $musicFiles) {
    $source = Join-Path $crystaldustPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        $destDir = Split-Path $dest -Parent
        if (!(Test-Path $destDir)) {
            New-Item -ItemType Directory -Path $destDir -Force | Out-Null
        }
        Copy-Item $source $dest -Force
        Write-Host "  Copied: $file" -ForegroundColor Green
    }
}

Write-Host "`n========================================" -ForegroundColor Green
Write-Host "Violet City import complete!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host "`nNext steps:" -ForegroundColor Cyan
Write-Host "1. Update include/constants/maps.h to add VioletCity map constants" -ForegroundColor White
Write-Host "2. Update include/constants/layouts.h to add VioletCity layout" -ForegroundColor White
Write-Host "3. Update src/data/tilesets/headers.h to add any new tilesets" -ForegroundColor White
Write-Host "4. Update src/data/tilesets/metatiles.h to reference tileset data" -ForegroundColor White
Write-Host "5. Update src/data/tilesets/graphics.h to reference tileset graphics" -ForegroundColor White
Write-Host "6. Add VioletCity to data/maps/map_groups.json in a Johto group" -ForegroundColor White
Write-Host "7. Update include/constants/songs.h if music was added" -ForegroundColor White
Write-Host "8. Update songs.mk to compile any new music" -ForegroundColor White
Write-Host "9. Rebuild the project with 'make'" -ForegroundColor White
Write-Host "`nNote: You may need to manually adjust scripts and events" -ForegroundColor Yellow
Write-Host "to be compatible with FireRed's engine differences." -ForegroundColor Yellow
