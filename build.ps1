# build.ps1 - Build all 4 variants of winrar-keygen-gui.exe
# Usage: powershell -ExecutionPolicy Bypass -File build.ps1

param(
    [string]$Configuration = "Release",
    [string]$OutputDir = "publish"
)

$ErrorActionPreference = "Stop"

$variants = @(
    @{ RID = "win-x64";  SelfContained = "true";  Label = "x64" }
    @{ RID = "win-x64";  SelfContained = "false"; Label = "x64-dotnet" }
    @{ RID = "win-arm64"; SelfContained = "true";  Label = "ARM64" }
    @{ RID = "win-arm64"; SelfContained = "false"; Label = "ARM64-dotnet" }
)

# Clean output directory
if (Test-Path $OutputDir) {
    Remove-Item -Recurse -Force $OutputDir
}
New-Item -ItemType Directory -Path $OutputDir | Out-Null

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host " Building winrar-keygen-gui ($Configuration)" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$success = 0
$failed = 0

foreach ($v in $variants) {
    $rid   = $v.RID
    $sc    = $v.SelfContained
    $label = $v.Label
    $dest  = Join-Path $OutputDir $label

    Write-Host "[$label] Publishing..." -ForegroundColor Yellow

    $publishArgs = @(
        "publish"
        "-c", $Configuration
        "-r", $rid
        "--self-contained", $sc
        "-p:PublishSingleFile=true"
        "-o", $dest
    )

    # ReadyToRun for self-contained builds (faster startup)
    if ($sc -eq "true") {
        $publishArgs += "-p:PublishReadyToRun=true"
    }

    dotnet @publishArgs 2>&1 | Out-Null

    if ($LASTEXITCODE -eq 0) {
        $exe = Get-ChildItem -Path $dest -Filter "winrar-keygen-gui.exe" -ErrorAction SilentlyContinue
        if ($exe) {
            $sizeMB = [math]::Round($exe.Length / 1MB, 2)
            Write-Host "[$label] OK - $sizeMB MB" -ForegroundColor Green
        } else {
            Write-Host "[$label] OK" -ForegroundColor Green
        }
        $success++
    } else {
        Write-Host "[$label] FAILED" -ForegroundColor Red
        $failed++
    }
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host " Done: $success succeeded, $failed failed" -ForegroundColor Cyan
Write-Host " Output: $OutputDir/" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# List all output
Write-Host "Output files:" -ForegroundColor White
foreach ($v in $variants) {
    $dest = Join-Path $OutputDir $v.Label
    $exe = Get-ChildItem -Path $dest -Filter "winrar-keygen-gui.exe" -ErrorAction SilentlyContinue
    if ($exe) {
        $sizeMB = [math]::Round($exe.Length / 1MB, 2)
        Write-Host "  $($v.Label)/winrar-keygen-gui.exe  ($sizeMB MB)" -ForegroundColor Gray
    }
}

# Normalize timestamps to the current whole hour
$wholeHour = Get-Date -Minute 0 -Second 0 -Millisecond 0
Write-Host ""
Write-Host "Setting file timestamps to $($wholeHour.ToString('yyyy-MM-dd HH:mm:ss'))..." -ForegroundColor DarkGray
foreach ($v in $variants) {
    $exe = Join-Path $OutputDir "$($v.Label)\winrar-keygen-gui.exe"
    if (Test-Path $exe) {
        (Get-Item $exe).LastWriteTime = $wholeHour
        (Get-Item $exe).CreationTime  = $wholeHour
    }
}

if ($failed -gt 0) { exit 1 }
