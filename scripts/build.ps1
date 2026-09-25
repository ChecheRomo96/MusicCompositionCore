param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$Preset,

    [string]$Configuration = "",
    [string]$Target = "",
    [int]$Parallel = 0,
    [switch]$CleanFirst,
    [switch]$Fresh,
    [Alias("examples-on")]
    [switch]$ExamplesOn
)

. "$PSScriptRoot/common.ps1"

$configureArguments = @("--preset", $Preset)
if ($Fresh) {
    $configureArguments += "--fresh"
}
if ($ExamplesOn) {
    $configureArguments += "-DMCC_EXAMPLES=ON"
}
Invoke-MCCCMake -Arguments $configureArguments

$buildDirectory = Get-MCCBuildDirectory -Preset $Preset
$configurationName = Get-MCCConfiguration `
    -Preset $Preset `
    -Configuration $Configuration `
    -DefaultConfiguration "Debug"
Assert-MCCConfiguration -Configuration $configurationName
$arguments = @("--build", $buildDirectory)

$arguments += @("--config", $configurationName)
if ($Target) {
    $arguments += @("--target", $Target)
}
if ($Parallel -gt 0) {
    $arguments += @("--parallel", $Parallel.ToString())
}
if ($CleanFirst) {
    $arguments += "--clean-first"
}

Invoke-MCCCMake -Arguments $arguments
