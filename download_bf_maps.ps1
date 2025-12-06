# Battle Frontier Maps Downloader for pokefirered
# Downloads all Battle Frontier map data from pokeemerald repository

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

$totalFiles = 0
$successCount = 0
$failCount = 0

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " Battle Frontier Maps Downloader" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

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
Write-Host "Map download complete!" -ForegroundColor Green
Write-Host "Next: Update code files to integrate new maps and tilesets" -ForegroundColor White
