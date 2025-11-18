#pragma once

/*
*	******************使用模板的说明*****************
*
*	1、模板设置了环境变量 xt_import_vc_dir 指向总的库目录（需要按照制定的结构存放库）
*	2、参照 引用额外的库的说明 引用库
*	3、需要导出的类需要添加宏定义：AFX_EXT_CLASS
* 
*/

/*
* //本文件最终放置于项目外，D:\import\manager_h
* 
* 
* **************************************** 说明 ************************************************
* 
*	本文件为了简化和固化项目属性设置流程，通过在包含该头文件，可以避免繁琐的项目设置，便于重用
* 
*	由于无法在#include指令中实现使用环境变量，因此采用了绝对路径
*	由于无法在#Pragma指令中实现使用环境变量，因此采用了绝对路径
*	D:import路径是本电脑指定的库文件存放位置，在不同电脑中使用时应根据情况进行替换
*	库存放位置下应有对应库的文件夹，内设：bin、lib、include文件夹分别存放dll、lib、h文件
* 
*	$(xt_vc_import_dir)环境变量应指向库存放目录，D:import
* 
* **************************************** @说明 ***********************************************
* 
* 
* *************************** 如果是dll项目引用该头文件 把以下代码复制到 【生成前事件】 中********************************

copy "$(xt_vc_import_dir)\ShaLun_dialog_dll\lib\$(Platform)\$(Configuration)\*.lib" "$(OutDir)*.lib"
copy "$(xt_vc_import_dir)\ShaLun_dialog_dll\bin\$(Platform)\$(Configuration)\*.dll" "$(OutDir)*.dll"

* *************************** 如果是dll项目 把以下代码复制到 【生成前事件】 中*******************************
* 
* 
* * ************************* 如果普通应用项目引用该头文件 把以下代码复制到 【生成前事件】 中********************************

copy "$(xt_vc_import_dir)\ShaLun_dialog_dll\bin\$(Platform)\$(Configuration)\*.dll" "$(OutDir)*.dll"

* *************************** 如果普通应用项目 把以下代码复制到 【生成前事件】 中*******************************
*/

//设置包含的头文件
#include "ShaLun_dialog_dll\include\dialog_Beixing_shalun.h"
#include "ShaLun_dialog_dll\include\dialog_Diexing_shalun.h"
#include "ShaLun_dialog_dll\include\dialog_DXF_shalun.h"
#include "ShaLun_dialog_dll\include\dialog_group_create.h"
#include "ShaLun_dialog_dll\include\dialog_group_list.h"
#include "ShaLun_dialog_dll\include\dialog_Jianjiao_shalun.h"
#include "ShaLun_dialog_dll\include\dialog_Ping_shalun.h"
#include "ShaLun_dialog_dll\include\dialog_wheel_create.h"
#include "ShaLun_dialog_dll\include\dialog_wheel_list.h"
#include "ShaLun_dialog_dll\include\dialog_Yuanjiao_shalun.h"

//复制到生成后事件
//copy "$(ProjectName).h" "$(xt_vc_import_dir)\$(ProjectName)\include\$(ProjectName).h"


//定义预编译器
#define AMAR_USE_LAPACK
#define AMAR_USE_BLAS

//注意：某些模板可能包含WIN32引起程序出错
#ifdef xt_WIN32
	#ifdef _DEBUG
		#pragma comment(lib, "ShaLun_dialog_dll\\lib\\win32\\debug\\ShaLun_dialog_dll.lib")
	#else
		#pragma comment(lib, "ShaLun_dialog_dll\\lib\\win32\\release\\ShaLun_dialog_dll.lib")
	#endif
#else
	#ifdef _DEBUG
		#pragma comment(lib, "ShaLun_dialog_dll\\lib\\x64\\debug\\ShaLun_dialog_dll.lib")
	#else
		#pragma comment(lib, "ShaLun_dialog_dll\\lib\\x64\\release\\ShaLun_dialog_dll.lib")
	#endif
#endif
