$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$script:MCCRoot = Split-Path -Parent $PSScriptRoot
$script:MCCBuildRoot = Join-Path $script:MCCRoot "build"
$script:MCCDistRoot = Join-Path $script:MCCRoot "dist"

function Invoke-MCCCMake {
    param([Parameter(Mandatory = $true)][string[]]$Arguments)

    & cmake @Arguments
    if ($LASTEXITCODE -ne 0) {
        throw "cmake failed with exit code $LASTEXITCODE"
    }
}

function Get-MCCBuildDirectory {
    param([Parameter(Mandatory = $true)][string]$Preset)
    Assert-MCCPreset -Preset $Preset
    return Join-Path $script:MCCBuildRoot $Preset
}

function Assert-MCCPreset {
    param([Parameter(Mandatory = $true)][string]$Preset)

    if ($Preset -notmatch "^[A-Za-z0-9][A-Za-z0-9_.-]*$" -or $Preset.Contains("..")) {
        throw "Invalid preset name: $Preset"
    }
}

function Get-MCCConfiguration {
    param(
        [Parameter(Mandatory = $true)][string]$Preset,
        [string]$Configuration = "",
        [string]$DefaultConfiguration = "Debug"
    )

    if ($Configuration) {
        return $Configuration
    }

    if ($Preset -eq "documentation") {
        return "Release"
    }

    return $DefaultConfiguration
}

function Assert-MCCConfiguration {
    param([Parameter(Mandatory = $true)][string]$Configuration)

    if ($Configuration -notin @("Debug", "Release")) {
        throw "Unsupported configuration '$Configuration'; expected Debug or Release"
    }
}

function Assert-MCCConfigured {
    param([Parameter(Mandatory = $true)][string]$Preset)

    $buildDirectory = Get-MCCBuildDirectory -Preset $Preset
    $cache = Join-Path $buildDirectory "CMakeCache.txt"
    if (-not (Test-Path -LiteralPath $cache -PathType Leaf)) {
        throw "Preset '$Preset' is not configured; run scripts/configure.ps1 $Preset first"
    }
}

function Resolve-MCCPath {
    param([Parameter(Mandatory = $true)][string]$Path)

    if ([System.IO.Path]::IsPathRooted($Path)) {
        return [System.IO.Path]::GetFullPath($Path)
    }

    return [System.IO.Path]::GetFullPath((Join-Path $script:MCCRoot $Path))
}

function Assert-MCCDistChild {
    param([Parameter(Mandatory = $true)][string]$Path)

    $distRoot = [System.IO.Path]::GetFullPath($script:MCCDistRoot).TrimEnd(
        [System.IO.Path]::DirectorySeparatorChar,
        [System.IO.Path]::AltDirectorySeparatorChar
    )
    $candidate = [System.IO.Path]::GetFullPath($Path)
    $prefix = $distRoot + [System.IO.Path]::DirectorySeparatorChar

    $comparison = if ([System.IO.Path]::DirectorySeparatorChar -eq "\") {
        [System.StringComparison]::OrdinalIgnoreCase
    }
    else {
        [System.StringComparison]::Ordinal
    }

    if (-not $candidate.StartsWith($prefix, $comparison)) {
        throw "Refusing to remove export path outside ${distRoot}: $candidate"
    }
}

if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    throw "Required command not found: cmake"
}

Set-Location $script:MCCRoot
