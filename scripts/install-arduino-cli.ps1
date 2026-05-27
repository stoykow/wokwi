$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$installDir = Join-Path $repoRoot ".tools\arduino-cli"
$zipPath = Join-Path $env:TEMP "arduino-cli-windows-64bit.zip"

$release = Invoke-RestMethod -Uri "https://api.github.com/repos/arduino/arduino-cli/releases/latest"
$asset = $release.assets |
  Where-Object { $_.name -like "*Windows_64bit.zip" } |
  Select-Object -First 1

if (-not $asset) {
  throw "Kein Windows-64-bit-Release für arduino-cli gefunden."
}

New-Item -ItemType Directory -Force -Path $installDir | Out-Null

Write-Host "Lade $($asset.name) herunter..."
Invoke-WebRequest -Uri $asset.browser_download_url -OutFile $zipPath

Write-Host "Installiere nach $installDir..."
Expand-Archive -LiteralPath $zipPath -DestinationPath $installDir -Force
Remove-Item -LiteralPath $zipPath -Force

$exePath = Join-Path $installDir "arduino-cli.exe"
if (-not (Test-Path -LiteralPath $exePath)) {
  throw "arduino-cli.exe wurde nicht gefunden: $exePath"
}

Write-Host "arduino-cli ist installiert: $exePath"
& $exePath version
