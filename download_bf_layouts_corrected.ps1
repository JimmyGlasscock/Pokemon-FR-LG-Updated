# Download Battle Frontier layout files from pokeemerald GitHub
# Using corrected naming without underscores

$baseUrl = "https://raw.githubusercontent.com/pret/pokeemerald/master/data/layouts"

# Layout folders (actual names from Emerald repo)
$layouts = @(
    "BattleFrontier_OutsideWest",
    "BattleFrontier_OutsideEast",
    "BattleFrontier_BattleArenaBattleRoom",
    "BattleFrontier_BattleArenaCorridor",
    "BattleFrontier_BattleArenaLobby",
    "BattleFrontier_BattleDomeBattleRoom",
    "BattleFrontier_BattleDomeCorridor",
    "BattleFrontier_BattleDomeLobby",
    "BattleFrontier_BattleDomePreBattleRoom",
    "BattleFrontier_BattleFactoryBattleRoom",
    "BattleFrontier_BattleFactoryLobby",
    "BattleFrontier_BattleFactoryPreBattleRoom",
    "BattleFrontier_BattlePalaceBattleRoom",
    "BattleFrontier_BattlePalaceCorridor",
    "BattleFrontier_BattlePalaceLobby",
    "BattleFrontier_BattlePikeCorridor",
    "BattleFrontier_BattlePikeLobby",
    "BattleFrontier_BattlePikeRoomNormal",
    "BattleFrontier_BattlePikeRoomFinal",
    "BattleFrontier_BattlePikeRoomWildMons",
    "BattleFrontier_BattlePikeThreePathRoom",
    "BattleFrontier_BattlePyramidFloor",
    "BattleFrontier_BattlePyramidLobby",
    "BattleFrontier_BattleTowerBattleRoom",
    "BattleFrontier_BattleTowerCorridor",
    "BattleFrontier_BattleTowerLobby",
    "BattleFrontier_BattleTowerMultiCorridor",
    "BattleFrontier_BattleTowerMultiPartnerRoom",
    "BattleFrontier_Lounge1",
    "BattleFrontier_Lounge2",
    "BattleFrontier_ExchangeServiceCorner",
    "BattleFrontier_RankingHall",
    "BattleFrontier_ScottsHouse",
    "BattleFrontier_ReceptionGate"
)

$files = @("border.bin", "map.bin")

$downloadCount = 0
$skipCount = 0

foreach ($layout in $layouts) {
    $localDir = "data\layouts\$layout"
    
    # Create directory if it doesn't exist
    if (!(Test-Path $localDir)) {
        New-Item -ItemType Directory -Path $localDir -Force | Out-Null
    }
    
    foreach ($file in $files) {
        $url = "$baseUrl/$layout/$file"
        $output = "$localDir\$file"
        
        try {
            Write-Host "Downloading $layout/$file..." -ForegroundColor Cyan
            Invoke-WebRequest -Uri $url -OutFile $output -ErrorAction Stop
            $downloadCount++
        }
        catch {
            Write-Host "  Skipped (not found): $layout/$file" -ForegroundColor Yellow
            $skipCount++
        }
    }
}

Write-Host "`nDownload complete!" -ForegroundColor Green
Write-Host "Downloaded: $downloadCount files" -ForegroundColor Green
Write-Host "Skipped: $skipCount files" -ForegroundColor Yellow
