@echo off
REM 获取当前BAT文件的路径
set currentPath=%~dp0

REM 定义要删除的文件和文件夹路径
set destFolder=%currentPath%import
set zipFile=%currentPath%import.zip

REM 删除ZIP文件
if exist %zipFile% del %zipFile%

REM 删除文件夹及其所有内容
if exist %destFolder% (
    rmdir /s /q %destFolder%
)

REM 完成提示
echo import文件夹和import.zip已删除
