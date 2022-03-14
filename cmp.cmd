@echo off
if not exist "bin" mkdir "bin"
@echo on
g++ *.cpp err\*.cpp core\*.cpp -o bin\s-files.exe -std=c++17 -lcomctl32 -lGdi32