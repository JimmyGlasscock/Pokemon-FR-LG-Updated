# Battle Frontier Layouts Downloader for pokefirered
# Downloads all Battle Frontier layout data from pokeemerald repository

$baseUrl = "https://raw.githubusercontent.com/pret/pokeemerald/master/data/layouts"
$outputBase = "C:\Users\Jimmy\Documents\decomps\pokefirered\data\layouts"

$layouts = @(
    "BattleFrontier_OutsideWest",
    "BattleFrontier_OutsideEast",
    "BattleFrontier_BattleTower_Lobby",
    "BattleFrontier_BattleTower_Elevator",
    "BattleFrontier_BattleTower_Corridor",
    "BattleFrontier_BattleTower_BattleRoom",
    "BattleFrontier_BattleTower_MultiPartnerRoom",
    "BattleFrontier_BattleTower_MultiCorridor",
    "BattleFrontier_BattleTower_MultiBattleRoom",
    "BattleFrontier_BattleDome_Lobby",
    "BattleFrontier_BattleDome_Corridor",
    "BattleFrontier_BattleDome_PreBattleRoom",
    "BattleFrontier_BattleDome_BattleRoom",
    "BattleFrontier_BattlePalace_Lobby",
    "BattleFrontier_BattlePalace_Corridor",
    "BattleFrontier_BattlePalace_BattleRoom",
    "BattleFrontier_BattlePyramid_Lobby",
    "BattleFrontier_BattlePyramid_Floor",
    "BattleFrontier_BattlePyramid_Top",
    "BattleFrontier_BattleArena_Lobby",
    "BattleFrontier_BattleArena_Corridor",
    "BattleFrontier_BattleArena_BattleRoom",
    "BattleFrontier_BattleFactory_Lobby",
    "BattleFrontier_BattleFactory_PreBattleRoom",
    "BattleFrontier_BattleFactory_BattleRoom",
    "BattleFrontier_BattlePike_Lobby",
    "BattleFrontier_BattlePike_Corridor",
    "BattleFrontier_BattlePike_ThreePathRoom",
    "BattleFrontier_BattlePike_RoomNormal",
    "BattleFrontier_BattlePike_RoomFinal",
    "BattleFrontier_BattlePike_RoomWildMons",
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
    "BattleFrontier_Pokemoncenter_1F",
    "BattleFrontier_Pokemoncenter_2F",
    "BattleFrontier_Mart"
)

$totalFiles = 0
$successCount = 0
$failCount = 0

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " Battle Frontier Layouts Downloader" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

foreach ($layout in $layouts) {
    Write-Host "Downloading $layout..." -ForegroundColor Cyan
    
    # Create directory
    $layoutDir = Join-Path $outputBase $layout
    New-Item -ItemType Directory -Force -Path $layoutDir | Out-Null
    
    # Download files
    $files = @("border.bin", "map.bin")
    foreach ($file in $files) {
        $url = "$baseUrl/$layout/$file"
        $output = Join-Path $layoutDir $file
        $totalFiles++
        try {
            Invoke-WebRequest -Uri $url -OutFile $output -ErrorAction Stop
            Write-Host "  OK $file" -ForegroundColor Gray
            $successCount++
        } catch {
            Write-Host "  SKIP $file (not found)" -ForegroundColor DarkGray
            $failCount++
        }
    }
    Write-Host ""
}

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Download Summary:" -ForegroundColor Cyan
Write-Host "  Total files attempted: $totalFiles" -ForegroundColor White
Write-Host "  Successfully downloaded: $successCount" -ForegroundColor Green
Write-Host "  Failed/skipped: $failCount" -ForegroundColor Yellow
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Layout download complete!" -ForegroundColor Green
Write-Host "Next: Update layouts.json to register the layouts" -ForegroundColor White
