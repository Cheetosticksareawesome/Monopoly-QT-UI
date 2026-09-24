param([switch]$BuildOnly)

$ErrorActionPreference = 'Stop'
$repo = Split-Path $PSScriptRoot -Parent
$oldPath = $env:PATH
$oldPlatform = $env:QT_QPA_PLATFORM
Push-Location $repo
try {
    $qt = 'C:/Qt/6.11.2/mingw_64'
    $compiler = 'C:/Qt/Tools/mingw1310_64/bin/g++.exe'
    $env:PATH = "C:/Qt/Tools/mingw1310_64/bin;$qt/bin;" + $oldPath
    & 'C:/Qt/Tools/CMake_64/bin/cmake.exe' --build --preset qt-debug
    if ($LASTEXITCODE -ne 0) { throw 'Project build failed.' }

    $testArgs = @('-std=c++20', '-fPIC', '-DQT_WIDGETS_LIB', '-DQT_GUI_LIB', '-DQT_CORE_LIB', '-Ibuild/qt-debug/UIApp_autogen/include')
    $testArgs += Get-ChildItem GAME -Directory -Recurse | ForEach-Object { '-I' + $_.FullName }
    $testArgs += @("-I$qt/include", "-I$qt/include/QtWidgets", "-I$qt/include/QtGui", "-I$qt/include/QtCore", 'scripts/money-stats.cpp')
    $commands = Get-Content 'build/qt-debug/compile_commands.json' -Raw | ConvertFrom-Json
    foreach ($entry in $commands) {
        if ($entry.file -notmatch '[/\\]main\.cpp$') { $testArgs += $entry.output }
    }
    $testArgs += @("-L$qt/lib", '-lQt6Widgets', '-lQt6Gui', '-lQt6Core', '-o', 'build/money-stats.exe')
    & $compiler @testArgs
    if ($LASTEXITCODE -ne 0) { throw 'Test runner compilation failed.' }

    if (!$BuildOnly) {
        $env:QT_QPA_PLATFORM = 'offscreen'
        Write-Host 'Running up to 100,000 rolls. Output: build/money-stats.txt'
        & './build/money-stats.exe'
        if ($LASTEXITCODE -ne 0) { throw 'Test runner failed.' }
    }
}
finally {
    $env:PATH = $oldPath
    $env:QT_QPA_PLATFORM = $oldPlatform
    Pop-Location
}
