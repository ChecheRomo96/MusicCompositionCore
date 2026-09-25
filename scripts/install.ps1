param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$Preset,

    [string]$Prefix = ""
)

. "$PSScriptRoot/common.ps1"

Assert-MCCConfigured -Preset $Preset

$buildDirectory = Get-MCCBuildDirectory -Preset $Preset
if (-not $Prefix) {
    $Prefix = Join-Path $script:MCCDistRoot $Preset
}
$Prefix = Resolve-MCCPath -Path $Prefix

$arguments = @("--install", $buildDirectory, "--prefix", $Prefix)
$arguments += @("--config", "Release")

Invoke-MCCCMake -Arguments $arguments
