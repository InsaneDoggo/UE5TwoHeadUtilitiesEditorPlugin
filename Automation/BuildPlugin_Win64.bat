@echo off

SET RunUAT_PATH=f:\ue_bin\UE_5.3\Engine\Build\BatchFiles\RunUAT.bat


%RunUAT_PATH% BuildPlugin ^
 -Plugin="%~dp0\..\TwoHeadUtilities.uplugin" ^
 -Package="%~dp0\..\Build\TwoHeadUtilities_Package" ^
 -TargetPlatforms=Win64

echo Done!

pause