$script:MCCRoot = Split-Path -Parent $PSScriptRoot
$script:MCCBuildRoot = Join-Path $script:MCCRoot "build"
$script:MCCDistRoot = Join-Path $script:MCCRoot "dist"
$script:MCCRoModularScripts = Join-Path `
    $script:MCCRoot `
    "tools/RoModularBuild/scripts"

$roModularCommon = Join-Path $script:MCCRoModularScripts "common.ps1"
if (-not (Test-Path -LiteralPath $roModularCommon -PathType Leaf)) {
    throw "RoModularBuild is unavailable; initialize tools/RoModularBuild with git submodule update --init --recursive"
}

$env:ROMODULAR_PROJECT_ROOT = $script:MCCRoot
$env:ROMODULAR_BUILD_ROOT = $script:MCCBuildRoot
$env:ROMODULAR_DIST_ROOT = $script:MCCDistRoot
$env:ROMODULAR_PROJECT_LABEL = "MCC"
$env:ROMODULAR_CONFIGURE_COMMAND = "scripts/configure.ps1"
$env:ROMODULAR_DEFAULT_CONFIGURATION = "Debug"
$env:ROMODULAR_DOCUMENTATION_PRESET = "documentation"
$env:ROMODULAR_DOCUMENTATION_CONFIGURATION = "Release"
$env:ROMODULAR_INSTALL_CONFIGURATION = "Release"
$env:ROMODULAR_TESTING_CACHE_ARGUMENT = "-DMCC_TESTING=ON"
$env:ROMODULAR_EXAMPLES_CACHE_ARGUMENT = "-DMCC_EXAMPLES=ON"
