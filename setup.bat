@echo off
set "buildPath=.\VS_CMakeBuildFiles"
if exist "%buildPath%\" (
    echo Opening VS solution...
    cd build
    RealEngine.sln
    cd ../
) else (
    echo Creating build folder...
    cmake -S . -B VS_CMakeBuildFiles
)

