@echo off
set SOURCE="C:\Users\Alex\OneDrive\Документы\Work\Natural Automatics\MetaTemp-git\MetaTempUnit\Hardware\library\KelvinVR"
set DEST="C:\Users\Alex\OneDrive\Документы\Arduino\libraries\KelvinVR"

echo Copying KelvinVR library...

if exist %DEST% (
    rmdir /s /q %DEST%
)

xcopy %SOURCE% %DEST% /E /I /Y

if errorlevel 1 (
    echo Error copying files!
) else (
    echo Successfully copied KelvinVR library!
)

pause
