clang-format -i *.hpp *.cpp

RMDIR build /S /Q
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
MinGW32-make

advancedCalculator.exe

cd ..
