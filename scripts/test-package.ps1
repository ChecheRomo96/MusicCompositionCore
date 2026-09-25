param(
    [Parameter(Mandatory = $true, Position = 0)]
    [string]$Preset,

    [string]$FoundationPrefix = "",
    [int]$Parallel = 0,
    [switch]$Fresh
)

. "$PSScriptRoot/common.ps1"

Assert-MCCPreset -Preset $Preset
if ($Preset -notmatch "^(macos|linux|windows)_") {
    throw "Package consumer tests require a runnable desktop preset"
}

if (-not $FoundationPrefix) {
    if ($env:MCC_FOUNDATION_PREFIX) {
        $FoundationPrefix = $env:MCC_FOUNDATION_PREFIX
    }
    else {
        $FoundationPrefix = Join-Path $script:MCCRoot "../Foundation/dist/$Preset"
    }
}
$FoundationPrefix = Resolve-MCCPath -Path $FoundationPrefix
$foundationConfig = Join-Path $FoundationPrefix "lib/cmake/Foundation/FoundationConfig.cmake"
if (-not (Test-Path -LiteralPath $foundationConfig -PathType Leaf)) {
    throw "Foundation package not found at $FoundationPrefix"
}

$exportParameters = @{
    Preset = $Preset
    CMakeArguments = @("-DMCC_FOUNDATION_PREFIX=$FoundationPrefix")
}
if ($Parallel -gt 0) {
    $exportParameters.Parallel = $Parallel
}
if ($Fresh) {
    $exportParameters.Fresh = $true
}
& "$PSScriptRoot/export.ps1" @exportParameters
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

$mccPrefix = Join-Path $script:MCCDistRoot $Preset
$consumerSource = Join-Path $script:MCCRoot "tests/PackageConsumer"
$consumerBuild = Join-Path $script:MCCBuildRoot "package-consumer/$Preset"

if ($Fresh -and (Test-Path -LiteralPath $consumerBuild)) {
    Remove-Item -LiteralPath $consumerBuild -Recurse -Force
}

Invoke-MCCCMake -Arguments @(
    "-S", $consumerSource,
    "-B", $consumerBuild,
    "-DCMAKE_BUILD_TYPE=Release",
    "-DMCC_DIR=$(Join-Path $mccPrefix 'lib/cmake/MCC')",
    "-DFoundation_DIR=$(Join-Path $FoundationPrefix 'lib/cmake/Foundation')"
)

$buildArguments = @("--build", $consumerBuild, "--config", "Release")
if ($Parallel -gt 0) {
    $buildArguments += @("--parallel", $Parallel.ToString())
}
Invoke-MCCCMake -Arguments $buildArguments

$testArguments = @(
    "--test-dir", $consumerBuild,
    "--output-on-failure",
    "--no-tests=error",
    "--build-config", "Release"
)
if ($Parallel -gt 0) {
    $testArguments += @("--parallel", $Parallel.ToString())
}
& ctest @testArguments
if ($LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}

Write-Host "Verified installed MCC package and transitive Foundation dependency"
