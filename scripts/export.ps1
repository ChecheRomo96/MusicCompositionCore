param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$Preset,

    [string]$Output = "",
    [int]$Parallel = 0,
    [switch]$Fresh,
    [switch]$Keep,
    [Alias("examples-on")]
    [switch]$ExamplesOn,

    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$CMakeArguments
)

. "$PSScriptRoot/common.ps1"

$customOutput = [bool]$Output
if (-not $Output) {
    $Output = Join-Path $script:MCCDistRoot $Preset
}
$Output = Resolve-MCCPath -Path $Output

if (-not $Keep -and $customOutput) {
    throw "Custom export paths require -Keep; remove custom destinations explicitly"
}

$configureParameters = @{
    Preset = $Preset
}
$effectiveCMakeArguments = @($CMakeArguments)
if ($ExamplesOn) {
    $effectiveCMakeArguments += "-DMCC_EXAMPLES=ON"
}
else {
    $effectiveCMakeArguments += "-DMCC_EXAMPLES=OFF"
}
if ($effectiveCMakeArguments.Count -gt 0) {
    $configureParameters.CMakeArguments = $effectiveCMakeArguments
}
if ($Fresh) {
    $configureParameters.Fresh = $true
}
& "$PSScriptRoot/configure.ps1" @configureParameters
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

$buildDirectory = Get-MCCBuildDirectory -Preset $Preset
$buildArguments = @(
    "--build", $buildDirectory,
    "--config", "Release",
    "--target", "MCCExportArtifacts"
)
if ($Parallel -gt 0) {
    $buildArguments += @("--parallel", $Parallel.ToString())
}
Invoke-MCCCMake -Arguments $buildArguments

if (-not $Keep) {
    Assert-MCCDistChild -Path $Output
    if (Test-Path -LiteralPath $Output) {
        Remove-Item -LiteralPath $Output -Recurse -Force
    }
}

$installParameters = @{
    Preset = $Preset
    Prefix = $Output
}
& "$PSScriptRoot/install.ps1" @installParameters
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Write-Host "Exported MCC (Release) to $Output"
