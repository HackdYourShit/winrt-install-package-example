if not defined VCPKG_TOOLCHAIN_FILE (
    :: Change this to point to the Vcpkg toolchain file on your system
    set VCPKG_TOOLCHAIN_FILE=C:\Users\Vlad\Git\vcpkg\scripts\buildsystems\vcpkg.cmake
)

rmdir /S /Q build
rmdir /S /Q bin
cmake -B.\build -H. -DCMAKE_CXX_FLAGS_RELEASE="/MT" -DCMAKE_GENERATOR_PLATFORM=x64 -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_TOOLCHAIN_FILE=%VCPKG_TOOLCHAIN_FILE%
cmake --build .\build --config Release -- /p:OutDir="../bin/"
