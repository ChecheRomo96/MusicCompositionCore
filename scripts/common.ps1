. "$PSScriptRoot/romodular-adapter.ps1"
. (Join-Path $script:MCCRoModularScripts "common.ps1")

function Invoke-MCCCMake {
    param([Parameter(Mandatory = $true)][string[]]$Arguments)

    Invoke-RoModularCMake -Arguments $Arguments
}

function Get-MCCBuildDirectory {
    param([Parameter(Mandatory = $true)][string]$Preset)
    return Get-RoModularBuildDirectory -Preset $Preset
}

function Assert-MCCPreset {
    param([Parameter(Mandatory = $true)][string]$Preset)

    Assert-RoModularPreset -Preset $Preset
}

function Get-MCCConfiguration {
    param(
        [Parameter(Mandatory = $true)][string]$Preset,
        [string]$Configuration = "",
        [string]$DefaultConfiguration = "Debug"
    )

    return Get-RoModularConfiguration `
        -Preset $Preset `
        -Configuration $Configuration `
        -DefaultConfiguration $DefaultConfiguration
}

function Assert-MCCConfiguration {
    param([Parameter(Mandatory = $true)][string]$Configuration)

    Assert-RoModularConfiguration -Configuration $Configuration
}

function Assert-MCCConfigured {
    param([Parameter(Mandatory = $true)][string]$Preset)

    Assert-RoModularConfigured -Preset $Preset
}

function Resolve-MCCPath {
    param([Parameter(Mandatory = $true)][string]$Path)

    return Resolve-RoModularPath -Path $Path
}

function Assert-MCCDistChild {
    param([Parameter(Mandatory = $true)][string]$Path)

    Assert-RoModularDistChild -Path $Path
}
