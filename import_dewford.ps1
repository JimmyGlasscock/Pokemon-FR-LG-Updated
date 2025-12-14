# Import Dewford Town from pokeemerald to pokefirered
# This script copies all necessary files for Dewford Town

$emeraldPath = "C:\Users\Jimmy\Documents\decomps\pokeemerald"
$firedPath = "C:\Users\Jimmy\Documents\decomps\pokefirered"

Write-Host "Importing Dewford Town from pokeemerald..." -ForegroundColor Green

# Create directories if they don't exist
$dirs = @(
    "$firedPath\data\tilesets\secondary\dewford",
    "$firedPath\data\tilesets\secondary\dewford\palettes",
    "$firedPath\data\tilesets\secondary\dewford\anim",
    "$firedPath\data\tilesets\secondary\dewford\anim\flag",
    "$firedPath\graphics\tilesets\secondary\dewford",
    "$firedPath\graphics\tilesets\secondary\dewford\palettes",
    "$firedPath\graphics\tilesets\secondary\dewford\anim",
    "$firedPath\graphics\tilesets\secondary\dewford\anim\flag",
    "$firedPath\data\maps\DewfordTown"
)

foreach ($dir in $dirs) {
    if (!(Test-Path $dir)) {
        New-Item -ItemType Directory -Path $dir -Force | Out-Null
        Write-Host "Created directory: $dir" -ForegroundColor Yellow
    }
}

# Copy Dewford tileset data files
Write-Host "`nCopying Dewford tileset data files..." -ForegroundColor Cyan

$dataFiles = @(
    "data/tilesets/secondary/dewford/metatiles.bin",
    "data/tilesets/secondary/dewford/metatile_attributes.bin"
)

foreach ($file in $dataFiles) {
    $source = Join-Path $emeraldPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        Copy-Item $source $dest -Force
        Write-Host "  Copied: $file" -ForegroundColor Green
    } else {
        Write-Host "  WARNING: Source file not found: $file" -ForegroundColor Red
    }
}

# Copy Dewford tileset graphics files
Write-Host "`nCopying Dewford tileset graphics..." -ForegroundColor Cyan

$gfxFiles = @(
    "data/tilesets/secondary/dewford/tiles.4bpp.lz"
)

foreach ($file in $gfxFiles) {
    $source = Join-Path $emeraldPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        Copy-Item $source $dest -Force
        Write-Host "  Copied: $file" -ForegroundColor Green
    } else {
        Write-Host "  WARNING: Source file not found: $file" -ForegroundColor Red
    }
}

# Copy Dewford tileset palettes
Write-Host "`nCopying Dewford tileset palettes..." -ForegroundColor Cyan

for ($i = 0; $i -le 15; $i++) {
    $palNum = $i.ToString("D2")
    $file = "data/tilesets/secondary/dewford/palettes/$palNum.gbapal"
    $source = Join-Path $emeraldPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        Copy-Item $source $dest -Force
        Write-Host "  Copied: palette $palNum.gbapal" -ForegroundColor Green
    }
}

# Copy Dewford tileset animations
Write-Host "`nCopying Dewford tileset animations..." -ForegroundColor Cyan

for ($i = 0; $i -le 7; $i++) {
    $file = "data/tilesets/secondary/dewford/anim/flag/$i.4bpp"
    $source = Join-Path $emeraldPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        Copy-Item $source $dest -Force
        Write-Host "  Copied: flag animation $i.4bpp" -ForegroundColor Green
    }
}

# Copy DewfordTown map data
Write-Host "`nCopying DewfordTown map data..." -ForegroundColor Cyan

$mapFiles = @(
    "data/maps/DewfordTown/map.json",
    "data/maps/DewfordTown/scripts.inc",
    "data/maps/DewfordTown/text.inc"
)

foreach ($file in $mapFiles) {
    $source = Join-Path $emeraldPath $file
    $dest = Join-Path $firedPath $file
    if (Test-Path $source) {
        Copy-Item $source $dest -Force
        Write-Host "  Copied: $file" -ForegroundColor Green
    } else {
        Write-Host "  WARNING: Source file not found: $file" -ForegroundColor Red
    }
}

# Copy Dewford Town music
Write-Host "`nSearching for Dewford Town music..." -ForegroundColor Cyan

# Check for Dewford music file in pokeemerald
$musicFile = "$emeraldPath\sound\songs\midi\mus_dewford.mid"
if (Test-Path $musicFile) {
    $destMusic = "$firedPath\sound\songs\midi\mus_dewford.mid"
    Copy-Item $musicFile $destMusic -Force
    Write-Host "  Copied: Dewford Town music (MIDI)" -ForegroundColor Green
} else {
    # Try .s file
    $musicFile = "$emeraldPath\sound\songs\mus_dewford.s"
    if (Test-Path $musicFile) {
        $destMusic = "$firedPath\sound\songs\mus_dewford.s"
        Copy-Item $musicFile $destMusic -Force
        Write-Host "  Copied: Dewford Town music (.s file)" -ForegroundColor Green
    } else {
        Write-Host "  NOTE: Dewford music file not found. Will need to search for correct name." -ForegroundColor Yellow
    }
}

Write-Host "`n========================================" -ForegroundColor Green
Write-Host "Import complete!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host "`nNext steps:" -ForegroundColor Cyan
Write-Host "1. Update src/data/tilesets/headers.h to add Dewford tileset" -ForegroundColor White
Write-Host "2. Update src/data/tilesets/metatiles.h to reference Dewford data" -ForegroundColor White
Write-Host "3. Update src/data/tilesets/graphics.h to reference Dewford graphics" -ForegroundColor White
Write-Host "4. Update src/tileset_anims.c to add Dewford animations" -ForegroundColor White
Write-Host "5. Add DewfordTown to data/maps/map_groups.json" -ForegroundColor White
Write-Host "6. Update include/constants/songs.h to add Dewford music" -ForegroundColor White
Write-Host "7. Update songs.mk to compile Dewford music" -ForegroundColor White
Write-Host "8. Rebuild the project" -ForegroundColor White
