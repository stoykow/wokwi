$ErrorActionPreference = "Stop"

$repoRoot = Split-Path -Parent $PSScriptRoot
$cli = Join-Path $repoRoot ".tools\arduino-cli\arduino-cli.exe"
$esp32IndexUrl = "https://espressif.github.io/arduino-esp32/package_esp32_index.json"

if (-not (Test-Path -LiteralPath $cli)) {
  & (Join-Path $PSScriptRoot "install-arduino-cli.ps1")
}

if (-not (Test-Path -LiteralPath $cli)) {
  throw "arduino-cli wurde nicht gefunden: $cli"
}

try {
  & $cli config init
} catch {
  Write-Host "Arduino-CLI-Konfiguration existiert bereits."
}

$config = & $cli config dump
if ($config -notmatch [regex]::Escape($esp32IndexUrl)) {
  & $cli config add board_manager.additional_urls $esp32IndexUrl
}

& $cli core update-index
& $cli core install arduino:avr
& $cli core install esp32:esp32
& $cli lib install PubSubClient

Write-Host "Arduino-Setup ist fertig."
