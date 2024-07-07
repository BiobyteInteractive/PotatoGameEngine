Set-Location -Path $PSScriptRoot;
cd ..;

$directoryPath = ".\build"
if(-not (Test-Path $directoryPath)) {
    .\scripts\setup.ps1
} else {
    cd .\build;
    cmake .. -G Ninja;
}

.\..\vendor\bin\ninja.exe;
cd ..;