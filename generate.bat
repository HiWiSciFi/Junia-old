@ECHO OFF
setlocal enabledelayedexpansion

ECHO Checking for VulkanSDK install...
IF "%VULKAN_SDK%"=="" (
	ECHO VulkanSDK not found! Please make sure it is installed and the $VULKAN_SDK environment variable is set. The installer will set it automatically
	ECHO You can download the latest LunarG VulkanSDK at https://vulkan.lunarg.com/sdk/home
	SET /P c="Do you want to install it automatically (Y/[N])?"
	IF /I "!c!" == "Y" GOTO INSTALL
	GOTO END
)
ECHO VulkanSDK found at "%VULKAN_SDK%"
ECHO Generating project files for vs2022...
ECHO -------------------------------------------
CALL .\external\premake\premake5.exe vs2022 --opengl --vulkan --vulkanpath="%VULKAN_SDK%" --windowapi=win32
GOTO END

:INSTALL
MKDIR TempVulkanInstallDir
CD .\TempVulkanInstallDir
powershell -Command "Invoke-WebRequest https://sdk.lunarg.com/sdk/download/latest/windows/vulkan-sdk.exe -OutFile vulkan-sdk.exe"
START /WAIT .\vulkan-sdk.exe
CD ..\
RD /S /Q .\TempVulkanInstallDir
ECHO You have to restart your PC in order for the installation to finish...
ECHO Restart this script once you have
GOTO END

:END
PAUSE
