#pragma once
/*
* //本文件最终放置于项目外，D:\DR_Programs\import\manager.h
* 
* 
* **************************************** 说明 ************************************************
* 
*	本文件为了简化和固化项目属性设置流程，通过在包含该头文件，可以避免繁琐的项目设置，便于重用
* 
*	由于无法在#include指令中实现使用环境变量，因此采用了绝对路径
*	由于无法在#Pragma指令中实现使用环境变量，因此采用了绝对路径
*	D:\DR_Programs\import\路径是本电脑指定的库文件存放位置，在不同电脑中使用时应根据情况进行替换
*	库存放位置下应有对应库的文件夹，内设：bin、lib、include文件夹分别存放dll、lib、h文件
* 
*	$(xt_vc_import_dir)环境变量应指向库存放目录，D:\DR_Programs\import\
* 
* **************************************** @说明 ***********************************************
* 
* 
* *************************** 如果是dll项目引用该头文件 把以下代码复制到 【生成前事件】 中********************************

copy "$(xt_vc_import_dir)\NC_Prog_Show_WorkPart_and_ShaLun\lib\$(Platform)\$(Configuration)\*.lib" "$(OutDir)*.lib"
copy "$(xt_vc_import_dir)\NC_Prog_Show_WorkPart_and_ShaLun\bin\$(Platform)\$(Configuration)\*.dll" "$(OutDir)*.dll"

* *************************** 如果是dll项目 把以下代码复制到 【生成前事件】 中*******************************
* 
* 
* * ************************* 如果普通应用项目引用该头文件 把以下代码复制到 【生成前事件】 中********************************

copy "$(xt_vc_import_dir)\NC_Prog_Show_WorkPart_and_ShaLun\bin\$(Platform)\$(Configuration)\*.dll" "$(OutDir)*.dll"

* *************************** 如果普通应用项目 把以下代码复制到 【生成前事件】 中*******************************
*/

//设置包含的头文件
//#include "NC_Prog_Show_WorkPart_and_ShaLun\include\NC_Prog_Show_WorkPart_and_ShaLun.h"
#include"NC_Prog_Show_WorkPart_and_ShaLun\include\show_gj_sl/gj_show.h"


//定义预编译器
#define AMAR_USE_LAPACK
#define AMAR_USE_BLAS

//注意：某些模板可能包含WIN32引起程序出错
#ifdef xt_WIN32
	#ifdef _DEBUG
		#pragma comment(lib, "NC_Prog_Show_WorkPart_and_ShaLun\\lib\\win32\\debug\\NC_Prog_Show_WorkPart_and_ShaLun.lib")
	#else
		#pragma comment(lib, "NC_Prog_Show_WorkPart_and_ShaLun\\lib\\win32\\release\\NC_Prog_Show_WorkPart_and_ShaLun.lib")
	#endif
#else
	#ifdef _DEBUG
		#pragma comment(lib, "NC_Prog_Show_WorkPart_and_ShaLun\\lib\\x64\\debug\\NC_Prog_Show_WorkPart_and_ShaLun.lib")
	#else
		#pragma comment(lib, "NC_Prog_Show_WorkPart_and_ShaLun\\lib\\x64\\release\\NC_Prog_Show_WorkPart_and_ShaLun.lib")
	#endif
#endif

using namespace arma;