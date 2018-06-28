@echo off
rmdir /S /Q build
rmdir /S /Q bin
cmake -B.\build -H. -DCMAKE_SYSTEM_VERSION=10.0 -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build .\build --config Release -- /p:OutDir="../bin/"
