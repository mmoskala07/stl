RMDIR build /S /Q
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
MinGW32-make

grayscaleImages.exe
@REM grayscaleImages-ut.exe

cd ..

