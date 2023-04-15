# Junia
A small game engine

# Building
Clone the repository using
```bash
git clone --recursive https://github.com/HiWiSciFi/Junia.git
```

## Unix
Required Ubuntu packages:
- `xorg-dev`
- `libopenal-dev`
- `build-essential` (compiler etc.)
- `cmake`
- `make`

To install all these dependencies on ubuntu in one go use
```bash
sudo apt install xorg-dev libopenal-dev cmake build-essential make
```

To download and install the Vulkan-SDK on Unix Systems follow the instructions on https://vulkan.lunarg.com/sdk/home<br>

Once you have installed all dependencies you can open up a terminal in the cloned repository and execute the following commands:
```bash
cd scripts && ./linux_run.sh
```

## Windows
On Windows there are two ways to get the dependencies. On pre-Win11 systems or systems that have not been updated in a while please use the non-winget approach.<br>
After installing the dependencies you might have to add the following Environment Variables
- `OPENALDIR` = Your path to the OpenAL SDK
- `VULKAN_SDK` = Your path to the Vulkan SDK

<details>
<summary>Winget</summary>

If you have winget available you can install dependencies easily using PowerShell.
```powershell
winget install cmake
winget install Microsoft.VisualStudio.2022.BuildTools
winget install KhronosGroup.VulkanSDK
winget install OpenAL.OpenAL
```

</details>

<details>
<summary>Non-Winget</summary>

Download and install the dependencies from the following sources by following the steps on each site:
- VisualStudio 2022 BuildTools: https://cmake.org/download/
- CMake: https://cmake.org/download/
- VulkanSDK: https://vulkan.lunarg.com/sdk/home
- OpenAL: https://www.openal.org/downloads/

</details>

Once you have installed all dependencies you can open up a powershell window in the cloned repository and execute the following commands:
```powershell
cd scripts && ./windows_run.bat
```
