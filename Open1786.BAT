SET PATH=D:\Keil_v5\ARM\ARMCC\Bin;C:\ProgramData\Oracle\Java\javapath;C:\Program Files (x86)\Common Files\Intel\Shared Libraries\redist\intel64\compiler;D:\Program\Python\Python36\Scripts\;D:\Program\Python\Python36\;C:\Perl64\site\bin;C:\Perl64\bin;C:\Program Files (x86)\Intel\iCLS Client\;C:\Program Files\Intel\iCLS Client\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\ProgramData\chocolatey\bin;C:\Program Files\Git\cmd;C:\Program Files (x86)\GitExtensions\;D:\Program\MiKTeX2.9\miktex\bin\x64\;C:\Program Files\MiKTeX 2.9\miktex\bin\x64\;D:\Program\Qt\5.9.1\msvc2017_64\bin;D:\Program\Qt\Tools\QtCreator\bin;D:\Program\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.11.25503\bin\HostX64\x64;D:\Program\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build;D:\Program\doxygen\bin;D:\Program\OpenCppCoverage;D:\Program\Qt\5.9.1\mingw53_32\bin;D:\Program\nodejs\;D:\Program\GnuWin32\bin;D:\Program\Python\Python36-32\Scripts\;D:\Program\Python\Python36-32\;C:\Users\Kevin\AppData\Local\Microsoft\WindowsApps;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\tools\cmder;D:\Program\OpenCppCoverage;C:\Users\Kevin\AppData\Roaming\npm;C:\Users\Kevin\AppData\Local\atom\bin
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=Open1786
SET CPU_CLOCK=0x00B71B00
"D:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_lpc17xx._ia"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_lpc17xx.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_clkpwr.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_gpio.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_pinsel.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_timer.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_exti.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_nvic.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_ssp.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lpc17xx_i2c.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\ili_lcd_general.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\lcd_api.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\english_16x8.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\affichagelcd.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\touch_panel.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\timer0.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\tactile.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\timer1.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\output\memoire.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Output\Project.lnp"
"D:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Output\Project.axf" --i32combined --output ".\Output\Project.hex"
