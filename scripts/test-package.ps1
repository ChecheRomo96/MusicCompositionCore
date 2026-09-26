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

# Without an explicit prefix, MCC resolves Foundation itself: sibling export,
# GitHub Release package or sources (see cmake/MCCFoundation.cmake).
if (-not $FoundationPrefix -and $env:MCC_FOUNDATION_PREFIX) {
    $FoundationPrefix = $env:MCC_FOUNDATION_PREFIX
}
$exportParameters = @{
    Preset = $Preset
}
if ($FoundationPrefix) {
    $FoundationPrefix = Resolve-MCCPath -Path $FoundationPrefix
    $foundationConfig = Join-Path $FoundationPrefix "lib/cmake/Foundation/FoundationConfig.cmake"
    if (-not (Test-Path -LiteralPath $foundationConfig -PathType Leaf)) {
        throw "Foundation package not found at $FoundationPrefix"
    }
    $exportParameters.CMakeArguments = @("-DMCC_FOUNDATION_PREFIX=$FoundationPrefix")
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

# The Foundation package MCC used; empty when Foundation was built from
# sources and installed next to MCC.
$cachePath = Join-Path (Get-MCCBuildDirectory -Preset $Preset) "CMakeCache.txt"
$resolvedFoundationPrefix = ""
$resolvedLine = Select-String -LiteralPath $cachePath `
    -Pattern "^MCC_FOUNDATION_RESOLVED_PREFIX:INTERNAL=(.*)$" | Select-Object -First 1
if ($resolvedLine) {
    $resolvedFoundationPrefix = $resolvedLine.Matches[0].Groups[1].Value
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
    "-DCMAKE_PREFIX_PATH=$mccPrefix;$resolvedFoundationPrefix"
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
