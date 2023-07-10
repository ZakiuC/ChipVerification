SET PATH=H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin;C:\Program Files\PlasticSCM5\server;C:\Program Files\PlasticSCM5\client;C:\Python311\Scripts\;C:\Python311\;C:\Program Files\Common Files\Oracle\Java\javapath;H:\java\bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.6\bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.6\libnvvp;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;H:\git\Git\cmd;C:\Android;C:\Windows\System32;H:\Wechat tools\game\微信web开发者工具\dll;H:\apktool;H:\PYTHON310\User_base&site\OTHER\swigwin-3.0.12;H:\CUDA\CUDA Development\bin;H:\CUDA\CUDA Development\libnvvp;H:\CUDA\CUDA Development\lib;H:\CUDA\CUDA Development\include;H:\Wechat tools\微信web开发者工具\dll;C:\Program Files\dotnet\;H:\VsCode\Microsoft VS Code\bin;G:\x32\tools\WinScp\WinSCP\;C:\Program Files\usbipd-win\;C:\Program Files\NVIDIA Corporation\Nsight Compute 2022.1.0\;H:\PYTHON310\;H:\PYTHON310\Scripts\;A:\Anaconda\Anaconda\Scripts;A:\Anaconda\Anaconda\condabin;A:\Anaconda\Anaconda\Library\bin;A:\Anaconda\Anaconda;H:\nodejs\;C:\ProgramData\chocolatey\bin;C:\Program Files (x86)\GtkSharp\2.12\bin;C:\Program Files\mingw64\bin;C:\Program Files\CMake\bin;G:\x64\Tools\MSYS2\mingw64\bin;H:\PYTHON310\Scripts\;H:\PYTHON310\;C:\Users\23370\AppData\Local\Microsoft\WindowsApps;C:\Users\23370\.dotnet\tools;A:\Anaconda\Pycharm\PyCharm Community Edition 2022.3\bin;;C:\Users\23370\AppData\Local\GitHubDesktop\bin;C:\Users\23370\AppData\Roaming\npm
SET ARMCC6_ASMOPT=--diag_suppress=9931
SET ARMCC6_CCOPT=--diag_suppress=9931
SET ARMCC6_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=FT32F030CBATx
SET CPU_VENDOR=FMD
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\main.__i"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\aes.__i"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\ft32f0xx_flash.__i"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\ft32f0xx_gpio.__i"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\ft32f0xx_rcc.__i"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\startup_ft32f072xb._ac"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmClang.exe" @".\objects\system_ft32f0xx.__i"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\ArmLink" --Via ".\Objects\ChipVerification.lnp"
"H:\keil_v5\Arm\Cores\ARM\ARMCLANG\Bin\fromelf.exe" ".\Objects\ChipVerification.axf" --i32combined --output ".\Objects\ChipVerification.hex"
