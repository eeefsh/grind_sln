#pragma once
#ifdef Prog_Manager_EXPORTS
#define Prog_Manager_API __declspec(dllexport)
#else
#define Prog_Manager_API __declspec(dllimport)
#endif
#include"manager_h/MA_031301_NC_Prog_Block_Prog_Struct.h"
#include "Obj_Prog.h"

class Prog_Manager_API void_zi :
	public nc_program_zi
{
public:
	//01 构造与析构
	void_zi(nc_program_zi_fangzhichongfu* father, int nc_var_type);
	~void_zi();

	//02 函数主体
	void prog_main();
	//03 输入输出变量

	//04 函数调用
	nc_block diaoyong();

	//05 成员子函数

private:

};
