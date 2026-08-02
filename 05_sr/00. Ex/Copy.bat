@echo off

cd /d %~dp0

xcopy /y .\Engine\Header\*.h .\Reference\Header
xcopy /y .\Engine\Bin\Engine.lib .\Reference\Library
xcopy /y .\Engine\Bin\Engine.dll .\Client\Bin

pause