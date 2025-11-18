@echo off
REM 获取当前BAT文件的路径
set currentPath=%~dp0

REM 替换要提取的库的文件夹名字(ShaLun_dialog_dll)
REM 替换要提取的库的头文件名字(MA_010101_ShaLun_dialog_dll.h)
REM 自行更改源文件绝对路径

REM 定义源文件和源文件夹的路径
set srcFile=D:\import\manager_h\MA_010101_ShaLun_dialog_dll.h
set srcFolder=D:\import\ShaLun_dialog_dll

REM 定义目标文件夹路径
set destFileFolder=%currentPath%import\manager_h
set destFolder=%currentPath%import

REM 创建目标文件夹（如果不存在）
if not exist %destFileFolder% mkdir %destFileFolder%
if not exist %destFolder% mkdir %destFolder%

REM 复制文件到目标文件夹
copy %srcFile% %destFileFolder%

REM 复制文件夹到目标文件夹
xcopy %srcFolder% %destFolder%\ShaLun_dialog_dll /E /I

REM 打包import文件夹为ZIP文件
powershell Compress-Archive -Path %destFolder% -DestinationPath %currentPath%import.zip

REM 完成提示
echo 文件和文件夹已成功复制
pause
