@echo off&&cls
set /p pathName=H:\virus\virus\ConsoleApplication\Debug%=%
cd %pathName%
REM set /p exec=kur.exe:%=%
set /p file=kur.exe%=%
g++ -o %file.exe% %file%.cpp
%file%.exe
