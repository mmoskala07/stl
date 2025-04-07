@REM RMDIR build /S /Q
@REM mkdir build
cd build
@REM cmake -G "MinGW Makefiles" ..
MinGW32-make

removeVowels-ut.exe

cd ..