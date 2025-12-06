# Battle Frontier Tileset Downloader for pokefirered
# Downloads all Battle Frontier tilesets from pokeemerald repository

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

$totalFiles = 0
$successCount = 0
$failCount = 0

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " Battle Frontier Tileset Downloader" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

foreach ($tileset in $tilesets) {
    Write-Host "Downloading $tileset..." -ForegroundColor Green
    
    # Create directories
    $tilesetDir = Join-Path $outputBase $tileset
    $paletteDir = Join-Path $tilesetDir "palettes"
    New-Item -ItemType Directory -Force -Path $tilesetDir | Out-Null
    New-Item -ItemType Directory -Force -Path $paletteDir | Out-Null
    
    # Download main files
    $files = @("tiles.png", "metatiles.bin", "metatile_attributes.bin")
    foreach ($file in $files) {
        $url = "$baseUrl/$tileset/$file"
        $output = Join-Path $tilesetDir $file
        $totalFiles++
        try {
            Invoke-WebRequest -Uri $url -OutFile $output -ErrorAction Stop
            Write-Host "  OK $file" -ForegroundColor Gray
            $successCount++
        } catch {
            Write-Host "  SKIP $file (not found or error)" -ForegroundColor Yellow
            $failCount++
        }
    }
    
    # Download palette files (00.gbapal through 15.gbapal)
    for ($i = 0; $i -le 15; $i++) {
        $palNum = "{0:D2}" -f $i
        $url = "$baseUrl/$tileset/palettes/$palNum.gbapal"
        $output = Join-Path $paletteDir "$palNum.gbapal"
        $totalFiles++
        try {
            Invoke-WebRequest -Uri $url -OutFile $output -ErrorAction Stop
            $successCount++
        } catch {
            $failCount++
        }
    }
    
    Write-Host "  Palettes downloaded" -ForegroundColor DarkGray
    Write-Host ""
}

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Download Summary:" -ForegroundColor Cyan
Write-Host "  Total files attempted: $totalFiles" -ForegroundColor White
Write-Host "  Successfully downloaded: $successCount" -ForegroundColor Green
Write-Host "  Failed/skipped: $failCount" -ForegroundColor Yellow
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Tileset download complete!" -ForegroundColor Green
Write-Host "Next: Run download_bf_maps.ps1 to download map data" -ForegroundColor White
