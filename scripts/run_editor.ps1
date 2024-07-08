Set-Location -Path $PSScriptRoot
cd ..

$project_path = Join-Path -Path (Get-Location) -ChildPath "GameEngineProject\.project"

cd build

& .\editor\Editor.exe $project_path

cd ..
