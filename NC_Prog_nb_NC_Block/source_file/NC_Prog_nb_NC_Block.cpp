#include "..\pch.h"
#define NC_Prog_nb_NC_Block_EXPORTS
#include "NC_Prog_nb_NC_Block.h"
#include "manager_h/xt_armadillo_settings.h"
#include <iostream>
#include <bitset>


//father_block:所有希望以副本形式下挂的块的公共父项
//主要用于变量块的定义之中。

nc_manager machine_var_manager;

nb_NC_block nb_NC_block::father_block;
NC_block_funs nb_NC_block::func_vec;
std::stack<nb_NC_block*> nb_NC_block::prog_stack;
virtual_machine* nb_NC_block::machine_ptr;
std::streampos nb_NC_block::position;
std::stack<std::streampos> nb_NC_block::position_stack;

using std::to_string;

nb_NC_block__run::nb_NC_block__run()
	: nb_NC_block__data(), nb_NC_block__tree()
{
	reset();
}

nb_NC_block__run::nb_NC_block__run(const nb_NC_block__run& A)
	:nb_NC_block__data(A), nb_NC_block__tree(A)
{
	reset();
}


nb_NC_block__run::~nb_NC_block__run()
{
	int i = 0;
}

void nb_NC_block__run::reset()
{
	int ls_n = 0;
	while (ls_n < count_son)
	{
		son_block_ptr_vec[ls_n]->reset();
		++ls_n;
	}
	son_not_end = true;
	now_not_cal = true;
	son_now_at = 0;

	ctrl_mes.is_stop = false;
	ctrl_mes.next_block = 0;

	blk_mes.ans_message = 0;
	blk_mes.error_message = 1;
}

//增加子程序块

bool nb_NC_block__run::push_back(nb_NC_block& k_in)
{
	if (Block_type_index == BH_PROCESS_K)
	{
		++count_son;
		son_block_ptr_vec.push_back(&k_in);
		return true;
	}
	else
	{
		return false;
	}
}

void nb_NC_block__run::set_machine(virtual_machine* p_machine)
{
	//for (int i = 0; i < count_son; i++)
	//{
	//	get_son_at(i)->set_machine(p_machine);
	//}
	machine_ptr = p_machine;
}

//设置块的最后一个子块为断点

void nb_NC_block__run::set_stop()
{
	get_son_at(count_son - 1)->ctrl_mes.is_stop = true;
}

nb_NC_block__funs_GY_CL_back::nb_NC_block__funs_GY_CL_back()
{
	;
}

nb_NC_block__funs_GY_CL_back::nb_NC_block__funs_GY_CL_back(const nb_NC_block__funs_GY_CL_back& A)
	:nb_NC_block__run(A)
{
	;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_Cal_One()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 1;//这是一个值运算块

	//单输入运算的子块也必须为值运算
	if (ls_mes.ans_message == 1)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 值运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;

}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_Cal_Two()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 1;//这是一个值运算块

	//单输入运算的子块也必须为值运算
	if (ls_mes.ans_message == 1)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 值运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_GX_One()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 2;//这是一个关系运算块

	//单输入运算的子块也必须为关系运算
	if (ls_mes.ans_message == 2)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 关系运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_GX_Two()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 2;//这是一个关系运算块

	//值运算也可以是关系运算
	if (ls_mes.ans_message == 1 || ls_mes.ans_message == 2)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 关系运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_CZ_Zero()
{
	blk_mes.ans_message = 3;//这是一个操作运算块
	blk_mes.error_message = 1;//子块无错误
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_CZ_One()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 3;//这是一个操作运算块

	//单输入运算的子块也必须为值运算
	if (ls_mes.ans_message == 1)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 值运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_CZ_Two()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 3;//这是一个操作运算块

	//单输入运算的子块也必须为值运算
	if (ls_mes.ans_message == 1)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 值运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_CZ_Duo()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = (son_block_ptr_vec[son_now_at]->blk_mes);

	blk_mes.ans_message = 3;//这是一个操作运算块

	//单输入运算的子块也必须为值运算
	if (ls_mes.ans_message == 1)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 值运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_Z_IF()
{
	if (son_block_ptr_vec[son_now_at]->ans_value > 0.1)
	{
		blk_mes.ans_message = 4;
	}
	else
	{
		blk_mes.ans_message = 5;
	}
	blk_mes.error_message = 1;//子块无错误
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_Z_NEXT()
{
	blk_mes.ans_message = 6;//这是一个NEXT
	blk_mes.error_message = 1;//子块无错误
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_Z_BACK()
{
	blk_mes.ans_message = 7;//这是一个BACK
	blk_mes.error_message = 1;//子块无错误
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_Z_END()
{
	blk_mes.ans_message = 8;//这是一个END
	blk_mes.error_message = 1;//子块无错误
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_JGZ_EXIT()
{
	blk_mes.ans_message = 9;//这是一个EXIT
	blk_mes.error_message = 1;//子块无错误
	son_now_at++;
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_JG_WHILE()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 10;//这是一个WHILE结构

	//若收到 结构子块-IF-是
	if (ls_mes.ans_message == 4)
	{
		now_not_cal = true;
		son_now_at = 1;
	}
	//若收到 结构子块-IF-否
	else if (ls_mes.ans_message == 5)
	{
		now_not_cal = true;
		son_now_at = 3;
	}
	//若收到 结构子块-IF-BACK
	else if (ls_mes.ans_message == 7)
	{
		reset();
		now_not_cal = true;
		son_now_at = 0;
	}
	//若收到 结构子块-IF-END
	else if (ls_mes.ans_message == 8)
	{
		reset();
		now_not_cal = true;
		son_now_at = count_son;
		//while块最终会到此，无错误完成
		blk_mes.error_message = 1;
	}
	//若收到 结构子块-IF-EXIT
	else if (ls_mes.ans_message == 9)
	{
		reset();
		now_not_cal = true;
		son_now_at = 3;
	}
	//若收到 顺序快-正常结束
	else if (ls_mes.ans_message == 12)
	{
		now_not_cal = true;
		son_now_at = 2;
	}
	else
	{
		//此种情况就是循环体没有用顺序快的情况
		now_not_cal = true;
		son_now_at = 2;
		//设置返回错误信息：意外的子块
		//blk_mes.error_message = 2;
	}

	if (ls_mes.error_message != 1)
	{
		blk_mes.error_message = 3;
	}
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_JGZ_IF()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 11;//这是一个IF结构

	if (ls_mes.error_message == 1)
	{
		blk_mes.error_message = 1;
		if (ls_mes.ans_message == 4)
		{
			now_not_cal = true;
			son_now_at += 1;
		}
		else if (ls_mes.ans_message == 5)
		{
			now_not_cal = true;
			son_now_at += 2;
		}
		else if (ls_mes.ans_message == 6)
		{
			now_not_cal = true;
			son_now_at += 1;
		}
		else if (ls_mes.ans_message == 9)
		{
			//for (int i = 0; i < count_son; i++)
			//{
			//	son_block_ptr_vec[i]->reset();
			//	i++;
			//}
			reset();
			now_not_cal = true;
			son_now_at = count_son;
			blk_mes.ans_message = 9;
			blk_mes.error_message = 1;
		}
		else if (ls_mes.ans_message == 8)
		{
			//for (int i = 0; i < count_son; i++)
			//{
			//	son_block_ptr_vec[i]->reset();
			//	i++;
			//}
			reset();
			now_not_cal = true;
			son_now_at = count_son;
			blk_mes.error_message = 1;
		}
		else if (ls_mes.ans_message == 10 || ls_mes.ans_message == 11 || ls_mes.ans_message == 12)
		{
			now_not_cal = true;
			son_now_at += 1;
		}
		else if (ls_mes.ans_message == 3)
		{
			now_not_cal = true;
			son_now_at += 1;
		}
		else
		{
			blk_mes.error_message = 2;
		}
	}
	else
	{
		blk_mes.error_message = 3;
	}
}

void nb_NC_block__funs_GY_CL_back::GY_CL_back_KFL_JG_Process()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	//2024.2.4 zy
	if (son_block_ptr_vec.size() == 0)
	{
		//2024.2.23 zy
		blk_mes.ans_message = 12;//这是一个PROCESS结构
		blk_mes.error_message = 1;
		now_not_cal = true;
		son_now_at = 0;
		return;
	}
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 12;//这是一个PROCESS结构

	if (ls_mes.error_message == 1)
	{
		blk_mes.error_message = 1;
		if (ls_mes.ans_message == 3 ||
			ls_mes.ans_message == 10 ||
			ls_mes.ans_message == 11 ||
			ls_mes.ans_message == 12
			)
		{
			now_not_cal = true;
			son_now_at += 1;
		}
		else if (ls_mes.ans_message == 9)
		{
			now_not_cal = true;
			son_now_at = count_son;
			blk_mes.ans_message = 9;
			blk_mes.error_message = 1;
		}
		else if (ls_mes.ans_message == 6)
		{
			now_not_cal = true;
			son_now_at += 1;
		}
		else
		{
			now_not_cal = true;
			son_now_at += 1;
			//	blk_mes.error_message = 2;
			//可能错误
		}
	}
	else
	{
		blk_mes.error_message = 3;
	}
}

nb_NC_block__funs_CL_back::nb_NC_block__funs_CL_back()
{
	;
}

nb_NC_block__funs_CL_back::nb_NC_block__funs_CL_back(const nb_NC_block__funs_CL_back& A)
	:nb_NC_block__funs_GY_CL_back(A)
{
	;
}

void nb_NC_block__funs_CL_back::CL_back_FuHao()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_KuoHao()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_ABS()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_ACOS()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_ASIN()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_ATAN()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_COS()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_SIN()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_TAN()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_CEIL()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_FLOOR()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_ROUND()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_EXP()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_LN()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_SQRT()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_MAX()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_MIN()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_POW()
{
	GY_CL_back_KFL_Cal_Two();
}

void nb_NC_block__funs_CL_back::CL_back_JIAN()
{
	GY_CL_back_KFL_Cal_Two();
}

void nb_NC_block__funs_CL_back::CL_back_JIA()
{
	GY_CL_back_KFL_Cal_Two();
}

void nb_NC_block__funs_CL_back::CL_back_CHENG()
{
	GY_CL_back_KFL_Cal_Two();
}

void nb_NC_block__funs_CL_back::CL_back_CHU()
{
	GY_CL_back_KFL_Cal_Two();
}

void nb_NC_block__funs_CL_back::CL_back_MOD()
{
	GY_CL_back_KFL_Cal_Two();
}

void nb_NC_block__funs_CL_back::CL_back_NOT()
{
	GY_CL_back_KFL_GX_One();
}

void nb_NC_block__funs_CL_back::CL_back_XIAOYU()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_DAYU()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_XIAODENGYU()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_DAYUDENGYU()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_DENGYU()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_BUDENGYU()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_AND()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_XOR()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_OR()
{
	GY_CL_back_KFL_GX_Two();
}

void nb_NC_block__funs_CL_back::CL_back_M00()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M01()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M02()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M03()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M04()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M05()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M06()
{
	GY_CL_back_KFL_CZ_One();
}

void nb_NC_block__funs_CL_back::CL_back_M08()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M09()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M19()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M30()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G00()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G01()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G04()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G52()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G53()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G54()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G55()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G56()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G57()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G58()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G59()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G90()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_WAIT()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_G91()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_F()
{
	GY_CL_back_KFL_CZ_One();
}

void nb_NC_block__funs_CL_back::CL_back_FUZHI()
{
	GY_CL_back_KFL_CZ_Two();
}

void nb_NC_block__funs_CL_back::CL_back_G31_X_Y_Z_A_C()
{
	GY_CL_back_KFL_CZ_Duo();
}

void nb_NC_block__funs_CL_back::CL_back_X_Y_Z_A_C()
{
	GY_CL_back_KFL_CZ_Duo();
}

void nb_NC_block__funs_CL_back::CL_back_IF()
{
	GY_CL_back_KFL_Z_IF();
}

void nb_NC_block__funs_CL_back::CL_back_NEXT()
{
	GY_CL_back_KFL_Z_NEXT();
}

void nb_NC_block__funs_CL_back::CL_back_BACK()
{
	GY_CL_back_KFL_Z_BACK();
}

void nb_NC_block__funs_CL_back::CL_back_END()
{
	GY_CL_back_KFL_Z_END();
}

void nb_NC_block__funs_CL_back::CL_back_EXIT()
{
	GY_CL_back_KFL_JGZ_EXIT();
}

void nb_NC_block__funs_CL_back::CL_back_WHILE_K()
{
	GY_CL_back_KFL_JG_WHILE();
}

void nb_NC_block__funs_CL_back::CL_back_IF_K()
{
	GY_CL_back_KFL_JGZ_IF();
}

void nb_NC_block__funs_CL_back::CL_back_PROCESS_K()
{
	GY_CL_back_KFL_JG_Process();
}

void nb_NC_block__funs_CL_back::CL_back_BL_A()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息

	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 1;//变量运算块向上说自己是值运算

	//单输入运算的子块也必须为值运算
	if (ls_mes.ans_message == 1)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 值运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_CL_back::CL_back_BL_JIN()
{
	//进入这个分支，必然是处理子块返回
	//第一步：取子块返回消息
	block_message ls_mes = son_block_ptr_vec[son_now_at]->blk_mes;

	blk_mes.ans_message = 1;//变量运算块向上说自己是值运算

	//单输入运算的子块也必须为值运算
	if (ls_mes.ans_message == 1)
	{
		//如果子块错误：无错误
		if (ls_mes.error_message == 1)
		{
			blk_mes.error_message = 1;
		}
		//如果子块返回错误
		else
		{
			//设置返回错误信息：子块运算错
			blk_mes.error_message = 3;
		}
	}
	//若输入运算不是 值运算
	else
	{
		//设置返回错误信息：意外的子块
		blk_mes.error_message = 2;
	}
	son_now_at++;
}

void nb_NC_block__funs_CL_back::CL_back_CHANGSHU()
{
	blk_mes.ans_message = 1;//这是一个值运算块
	//无错误
	blk_mes.error_message = 1;
	son_now_at++;
}

void nb_NC_block__funs_CL_back::CL_back_X_Y_Z_A_C_F()
{
	GY_CL_back_KFL_CZ_Duo();
}

void nb_NC_block__funs_CL_back::CL_back_G31_X_Y_Z_A_C_F()
{
	GY_CL_back_KFL_CZ_Duo();
}

void nb_NC_block__funs_CL_back::CL_back_G01_X_Y_Z_A_C_F()
{
	GY_CL_back_KFL_CZ_Duo();
}

void nb_NC_block__funs_CL_back::CL_back_ZhengHao()
{
	GY_CL_back_KFL_Cal_One();
}

void nb_NC_block__funs_CL_back::CL_back_G01_X_Y_Z_A_C()
{
	GY_CL_back_KFL_CZ_Duo();
}

void nb_NC_block__funs_CL_back::CL_back_M98()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M99()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_S_speed()
{
	GY_CL_back_KFL_CZ_One();
}

void nb_NC_block__funs_CL_back::CL_back_Set_RGB()
{
	GY_CL_back_KFL_CZ_One();
}

void nb_NC_block__funs_CL_back::CL_back_M13()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M14()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_M15()
{
	GY_CL_back_KFL_CZ_Zero();
}

void nb_NC_block__funs_CL_back::CL_back_S2_speed()
{
	GY_CL_back_KFL_CZ_One();
}

nb_NC_block__funs_CAL::nb_NC_block__funs_CAL()
{
	;
}

nb_NC_block__funs_CAL::nb_NC_block__funs_CAL(const nb_NC_block__funs_CAL& A)
	:nb_NC_block__run(A)
{
	;
}

void nb_NC_block__funs_CAL::CAL_FuHao()
{
	ans_value = -son_block_ptr_vec[0]->ans_value;
	this->blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_KuoHao()
{
	ans_value = son_block_ptr_vec[0]->ans_value;
}

void nb_NC_block__funs_CAL::CAL_ABS()
{
	ans_value = abs(son_block_ptr_vec[0]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_ACOS()
{
	double ls_in = son_block_ptr_vec[0]->ans_value;
	if (ls_in > 1.0 || ls_in < -1.0)
	{
		//超出定义域
		blk_mes.error_message = 4;
	}
	else
	{
		ans_value = acos(ls_in) / datum::pi * 180.0;
	}
}

void nb_NC_block__funs_CAL::CAL_ASIN()
{
	double ls_in = son_block_ptr_vec[0]->ans_value;
	if (ls_in > 1.0 || ls_in < -1.0)
	{
		//超出定义域
		blk_mes.error_message = 4;
	}
	else
	{
		ans_value = asin(ls_in) / datum::pi * 180.0;
	}
}

void nb_NC_block__funs_CAL::CAL_ATAN()
{
	ans_value = atan(son_block_ptr_vec[0]->ans_value) / datum::pi * 180.0;
}

void nb_NC_block__funs_CAL::CAL_COS()
{
	ans_value = cos(son_block_ptr_vec[0]->ans_value / 180.0 * datum::pi);
}

void nb_NC_block__funs_CAL::CAL_SIN()
{
	ans_value = sin(son_block_ptr_vec[0]->ans_value / 180.0 * datum::pi);
}

void nb_NC_block__funs_CAL::CAL_TAN()
{
	ans_value = tan(son_block_ptr_vec[0]->ans_value / 180.0 * datum::pi);
}

void nb_NC_block__funs_CAL::CAL_CEIL()
{
	ans_value = ceil(son_block_ptr_vec[0]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_FLOOR()
{
	ans_value = floor(son_block_ptr_vec[0]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_ROUND()
{
	ans_value = round(son_block_ptr_vec[0]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_EXP()
{
	ans_value = exp(son_block_ptr_vec[0]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_LN()
{
	ans_value = log(son_block_ptr_vec[0]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_SQRT()
{
	if (son_block_ptr_vec[0]->ans_value < 0.0)
	{
		//超出定义域
		blk_mes.error_message = 4;
		ans_value = 0.0;
	}
	else
	{
		ans_value = floor(son_block_ptr_vec[0]->ans_value);
	}
}

void nb_NC_block__funs_CAL::CAL_MAX()
{
	if (son_block_ptr_vec[0]->ans_value
		>= son_block_ptr_vec[1]->ans_value
		)
	{
		ans_value = son_block_ptr_vec[0]->ans_value;
	}
	else
	{
		ans_value = son_block_ptr_vec[1]->ans_value;
	}
}

void nb_NC_block__funs_CAL::CAL_MIN()
{
	if (son_block_ptr_vec[0]->ans_value
		<= son_block_ptr_vec[1]->ans_value
		)
	{
		ans_value = son_block_ptr_vec[0]->ans_value;
	}
	else
	{
		ans_value = son_block_ptr_vec[1]->ans_value;
	}
}

void nb_NC_block__funs_CAL::CAL_POW()
{
	ans_value = pow(son_block_ptr_vec[0]->ans_value,
		son_block_ptr_vec[1]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_JIAN()
{
	ans_value =
		son_block_ptr_vec[0]->ans_value
		- son_block_ptr_vec[1]->ans_value;
}

void nb_NC_block__funs_CAL::CAL_JIA()
{
	ans_value =
		son_block_ptr_vec[0]->ans_value
		+ son_block_ptr_vec[1]->ans_value;
}

void nb_NC_block__funs_CAL::CAL_CHENG()
{
	ans_value =
		son_block_ptr_vec[0]->ans_value
		* son_block_ptr_vec[1]->ans_value;
}

void nb_NC_block__funs_CAL::CAL_CHU()
{
	if (son_block_ptr_vec[1]->ans_value == 0.0)
	{
		//超出定义域
		blk_mes.error_message = 4;
		ans_value = 0.0;
	}
	ans_value =
		son_block_ptr_vec[0]->ans_value
		/ son_block_ptr_vec[1]->ans_value;
}

void nb_NC_block__funs_CAL::CAL_MOD()
{
	ans_value = int(son_block_ptr_vec[0]->ans_value)
		% int(son_block_ptr_vec[1]->ans_value);
}

void nb_NC_block__funs_CAL::CAL_NOT()
{
	if (abs(son_block_ptr_vec[0]->ans_value) < 0.000001)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_XIAOYU()
{
	if (son_block_ptr_vec[0]->ans_value < son_block_ptr_vec[1]->ans_value)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_DAYU()
{
	if (son_block_ptr_vec[0]->ans_value > son_block_ptr_vec[1]->ans_value)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_XIAODENGYU()
{
	if (son_block_ptr_vec[0]->ans_value <= son_block_ptr_vec[1]->ans_value)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_DAYUDENGYU()
{
	if (son_block_ptr_vec[0]->ans_value >= son_block_ptr_vec[1]->ans_value)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_DENGYU()
{
	if (son_block_ptr_vec[0]->ans_value == son_block_ptr_vec[1]->ans_value)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_BUDENGYU()
{
	if (son_block_ptr_vec[0]->ans_value != son_block_ptr_vec[1]->ans_value)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_AND()
{
	if (son_block_ptr_vec[0]->ans_value > 0.0001
		&&
		son_block_ptr_vec[1]->ans_value > 0.0001)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_XOR()
{
	if (son_block_ptr_vec[0]->ans_value > 0.0001
		&&
		son_block_ptr_vec[1]->ans_value < 0.0001)
	{
		ans_value = 1.0;
	}
	else if (son_block_ptr_vec[0]->ans_value < 0.0001
		&&
		son_block_ptr_vec[1]->ans_value > 0.0001)
	{
		ans_value = 1.0;
	}
	else
	{
		ans_value = 0.0;
	}
}

void nb_NC_block__funs_CAL::CAL_OR()
{
	if (son_block_ptr_vec[0]->ans_value < 0.0001
		&&
		son_block_ptr_vec[1]->ans_value < 0.0001)
	{
		ans_value = 0.0;
	}
	else
	{
		ans_value = 1.0;
	}
}

void nb_NC_block__funs_CAL::CAL_M00()
{
	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M01()
{
}

void nb_NC_block__funs_CAL::CAL_M02()
{
}

void nb_NC_block__funs_CAL::CAL_M03()
{
	machine_ptr->M03();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M04()
{
	machine_ptr->M04();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M05()
{
	machine_ptr->M05();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M06()
{
	machine_ptr->M06(int (son_block_ptr_vec[0]->ans_value));
	machine_ptr->set_using_sl_num_on_slz(int (ans_value));

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M08()
{
	machine_ptr->M08();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M09()
{
	machine_ptr->M09();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M19()
{

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M30()
{
	////25.7.24 phy
	//std::ifstream ifile("serialized_data.bin", std::ios::binary); // 打开文件  

	//if (!ifile.is_open()) {
	//	std::cerr << "Error opening file!" << std::endl;
	//}
	//// 移动到文件末尾  
	//ifile.seekg(0, std::ios::end); // 将读取位置移动到文件末尾  

	//nb_NC_block::position = ifile.tellg(); //位置定位文件末尾

	//ifile.close();

	//3.18 zy
	machine_ptr->M30();

	//计算过程错误信息
	blk_mes.error_message = 1;

}

void nb_NC_block__funs_CAL::CAL_G00()
{
	machine_ptr->G00();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G01()
{
	machine_ptr->G01();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G04()
{

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G52()
{

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G53()
{

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G54()
{
	machine_ptr->G54_G59(0);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G55()
{
	machine_ptr->G54_G59(1);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G56()
{
	machine_ptr->G54_G59(2);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G57()
{
	machine_ptr->G54_G59(3);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G58()
{
	machine_ptr->G54_G59(4);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G59()
{
	machine_ptr->G54_G59(5);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G90()
{
	machine_ptr->G90();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_WAIT()
{
	//machine_ptr->G90();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G91()
{
	machine_ptr->G91();

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_F()
{
	machine_ptr->F(son_block_ptr_vec[0]->ans_value);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_FUZHI()
{
	//计算过程错误信息
	blk_mes.error_message = 1;

	//machine_ptr->
	if (son_block_ptr_vec[0]->Block_type_index == BH_BL_A)
	{
		machine_ptr->BL_A_set(
			int(son_block_ptr_vec[0]->son_block_ptr_vec[0]->ans_value),
			son_block_ptr_vec[1]->ans_value
		);
	}
	else if (son_block_ptr_vec[0]->Block_type_index == BH_BL_JIN)
	{
		machine_ptr->BL_S_set(
			int(son_block_ptr_vec[0]->son_block_ptr_vec[0]->ans_value),
			son_block_ptr_vec[1]->ans_value
		);
	}
	else
	{
		blk_mes.error_message = 4;
	}
}

void nb_NC_block__funs_CAL::CAL_G31_X_Y_Z_A_C()
{
	vec5 point_ls;
	point_ls(0) = son_block_ptr_vec[0]->ans_value;
	point_ls(1) = son_block_ptr_vec[1]->ans_value;
	point_ls(2) = son_block_ptr_vec[2]->ans_value;
	point_ls(3) = son_block_ptr_vec[3]->ans_value;
	point_ls(4) = son_block_ptr_vec[4]->ans_value;

	//如果值为99999.123455~99999.123457之间，99999.123456则代表不执行
	machine_ptr->move_cal_to_cache(point_ls(0), point_ls(1), point_ls(2),
		point_ls(3), point_ls(4));

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_X_Y_Z_A_C()
{
	vec5 point_ls;
	point_ls(0) = son_block_ptr_vec[0]->ans_value;
	point_ls(1) = son_block_ptr_vec[1]->ans_value;
	point_ls(2) = son_block_ptr_vec[2]->ans_value;
	point_ls(3) = son_block_ptr_vec[3]->ans_value;
	point_ls(4) = son_block_ptr_vec[4]->ans_value;

	//如果值为99999.123455~99999.123457之间，99999.123456则代表不执行
	machine_ptr->move_cal_to_cache(point_ls(0), point_ls(1), point_ls(2),
		point_ls(3), point_ls(4));

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_IF()
{
	/*if (son_block_ptr_vec[son_now_at]->ans_value > 0.1)
	{
	ans_value = 1.0;
	}
	else
	{
	ans_value = 0.0;
	}*/
	ans_value = 0.0;
	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_NEXT()
{
	ans_value = 0.0;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_BACK()
{
	ans_value = 0.0;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_END()
{
	ans_value = 0.0;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_EXIT()
{
	ans_value = 0.0;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_WHILE_K()
{
	ans_value = 0.0;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_IF_K()
{
	ans_value = 0.0;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_PROCESS_K()
{
	ans_value = 0.0;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_BL_A()
{
	machine_ptr->BL_A_read(
		int(son_block_ptr_vec[0]->ans_value),
		ans_value
	);

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_BL_JIN()
{
	machine_ptr->BL_S_read(
		int(son_block_ptr_vec[0]->ans_value),
		ans_value
	);

	//计算过程错误信息
	blk_mes.error_message = 1;

}

void nb_NC_block__funs_CAL::CAL_CHANGSHU()
{
	//常数运算块，不需要计算吧

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_X_Y_Z_A_C_F()
{
	machine_ptr->F(son_block_ptr_vec[5]->ans_value);

	vec5 point_ls;
	point_ls(0) = son_block_ptr_vec[0]->ans_value;
	point_ls(1) = son_block_ptr_vec[1]->ans_value;
	point_ls(2) = son_block_ptr_vec[2]->ans_value;
	point_ls(3) = son_block_ptr_vec[3]->ans_value;
	point_ls(4) = son_block_ptr_vec[4]->ans_value;

	//如果值为99999.123455~99999.123457之间，99999.123456则代表不执行
	machine_ptr->move_cal_to_cache(point_ls(0), point_ls(1), point_ls(2),
		point_ls(3), point_ls(4));

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G31_X_Y_Z_A_C_F()
{
	machine_ptr->F(son_block_ptr_vec[5]->ans_value);

	vec5 point_ls;
	point_ls(0) = son_block_ptr_vec[0]->ans_value;
	point_ls(1) = son_block_ptr_vec[1]->ans_value;
	point_ls(2) = son_block_ptr_vec[2]->ans_value;
	point_ls(3) = son_block_ptr_vec[3]->ans_value;
	point_ls(4) = son_block_ptr_vec[4]->ans_value;

	//如果值为99999.123455~99999.123457之间，99999.123456则代表不执行
	machine_ptr->move_cal_to_cache(point_ls(0), point_ls(1), point_ls(2),
		point_ls(3), point_ls(4));

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G01_X_Y_Z_A_C_F()
{
	machine_ptr->G01();
	machine_ptr->F(son_block_ptr_vec[5]->ans_value);

	//vec5 point_ls;
	vec5 point_ls;
	point_ls(0) = son_block_ptr_vec[0]->ans_value;
	point_ls(1) = son_block_ptr_vec[1]->ans_value;
	point_ls(2) = son_block_ptr_vec[2]->ans_value;
	point_ls(3) = son_block_ptr_vec[3]->ans_value;
	point_ls(4) = son_block_ptr_vec[4]->ans_value;

	//如果值为99999.123455~99999.123457之间，99999.123456则代表不执行
	//machine_ptr->Move_cal(point_ls);

	machine_ptr->move_cal_to_cache(point_ls(0), point_ls(1), point_ls(2),
		point_ls(3), point_ls(4));

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_ZhengHao()
{
	ans_value = son_block_ptr_vec[0]->ans_value;

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_G01_X_Y_Z_A_C()
{
	machine_ptr->G01();

	vec5 point_ls;
	point_ls(0) = son_block_ptr_vec[0]->ans_value;
	point_ls(1) = son_block_ptr_vec[1]->ans_value;
	point_ls(2) = son_block_ptr_vec[2]->ans_value;
	point_ls(3) = son_block_ptr_vec[3]->ans_value;
	point_ls(4) = son_block_ptr_vec[4]->ans_value;

	//如果值为99999.123455~99999.123457之间，99999.123456则代表不执行

	machine_ptr->move_cal_to_cache(point_ls(0), point_ls(1), point_ls(2),
		point_ls(3), point_ls(4));

	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M98()
{
	//改变下一步的运算为转跳的位置
	//memcpy(&(ctrl_mes.next_block), &ans_value, 4);

	////记录回跳位置
	//prog_stack.push(father_block_ptr);

	////检查指针有效性
	unsigned char* ans_value_ptr = reinterpret_cast<unsigned char*>(&this->ans_value);
	int name_num = 0;
	memcpy(&name_num, reinterpret_cast<char*>(&ans_value) + 4, 4);
	nb_NC_block::position;
	file_pos_get(name_num);
	nb_NC_block::position;
	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M99()
{
	//改变下一步的运算为转跳的位置
	//ctrl_mes.next_block = prog_stack.top();
	//prog_stack.pop();

	////子树重置 24.2.26 zy
	////reset();
	recovery_now_file_pos();
	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_S_speed()
{
	//machine_ptr->S(son_block_ptr_vec[0]->ans_value);
	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_Set_RGB()
{
	machine_ptr->set_RGB(son_block_ptr_vec[0]->ans_value);
	//计算过程错误信息
	blk_mes.error_message = 1;
}

void nb_NC_block__funs_CAL::CAL_M13()
{
}

void nb_NC_block__funs_CAL::CAL_M14()
{
}

void nb_NC_block__funs_CAL::CAL_M15()
{
}

void nb_NC_block__funs_CAL::CAL_S2_speed()
{
}

nb_NC_block__write_code::nb_NC_block__write_code()
	: nb_NC_block__data(), nb_NC_block__tree()
{
	NC_code = "";
}

nb_NC_block__write_code::nb_NC_block__write_code(const nb_NC_block__write_code& a)
	: nb_NC_block__data(a), nb_NC_block__tree(a)
{
	NC_code = a.NC_code;
	Block_type_index = a.Block_type_index;
	ans_value =a.ans_value;
	father_block_ptr = a.father_block_ptr;
	count_son = a.count_son;
	son_block_ptr_vec.shrink_to_fit();
	
	for (int i = 0; i < count_son; i++)
	{
		son_block_ptr_vec.push_back(a.son_block_ptr_vec[i]);
	}
}

string nb_NC_block__write_code::kong()
{
	string str = "";
	return str;
}

string nb_NC_block__write_code::NC_endl()
{
	string str = "";
	str = ";";
	return str;
}

string nb_NC_block__write_code::endl()
{
	string str = "";
	str = "\n";
	return str;
}

string nb_NC_block__write_code::Comment(string& comment)
{
	string str = "";
	str = str + "//" + comment;
	return str;
}

string nb_NC_block__write_code::NC_Line(string code)
{
	string str = "";
	str = str + code + NC_endl() + endl();
	return str;
}

string nb_NC_block__write_code::NC_Line(string& code, string& comment)
{
	string str = "";
	str = str + code + NC_endl() + "  " + Comment(comment) + endl();
	return str;
}

string nb_NC_block__write_code::NC_Comment(string& comment)
{
	string str = "";
	str = str + Comment(comment) + endl();
	return str;
}

string nb_NC_block__write_code::KuoHao(string& code)
{
	string str = "";
	str += "(" + code + ")";
	return str;
}

//d 是输入的double ，i 是要转化的位数

string nb_NC_block__write_code::d2str(double d, int i)
{
	std::stringstream ss;
	std::string ans = "";
	ss.setf(std::ios::fixed);
	ss.precision(i);
	ss << d;
	ans = ss.str();
	ss.str("");
	return ans;
}

string nb_NC_block__write_code::YuanKuoHao(string str_in)
{
	string str = "";
	if (str_in[0] == '(' && str_in[str_in.size()-1] == ')')
	{
		str_in = str_in.substr(1, str_in.size() - 2);
	}
	else if (str_in[0] == '[' && str_in[str_in.size() - 1] == ']')
	{
		str_in = str_in.substr(1, str_in.size() - 2);
	}
	else
	{
		
	}
	//str += "(" + str_in + ")";
	//string str = "";
	str += "(" + str_in + ")";
	return str;
}

string nb_NC_block__write_code::ZhongKuoHao(string str_in)
{
	string str = "";
	if (str_in[0] == '(' && str_in[str_in.size() - 1] == ')')
	{
		str_in = str_in.substr(1, str_in.size() - 2);
	}
	else if (str_in[0] == '[' && str_in[str_in.size() - 1] == ']')
	{
		str_in = str_in.substr(1, str_in.size() - 2);
	}
	else
	{
		
	}

	str += "[" + str_in + "]";

	//string str = "";
	//str += "[" + str_in + "]";
	return str;
}

void nb_NC_block__write_code::NC_CODE_FuHao()
{
	NC_code = KuoHao(kong() + "-" + get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_KuoHao()
{
	NC_code = KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_ABS()
{
	NC_code = "ABS" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_ACOS()
{
	NC_code = "ACOS" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_ASIN()
{
	NC_code = "ASIN" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_ATAN()
{
	NC_code = "ATAN" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_COS()
{
	NC_code = "COS" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_SIN()
{
	NC_code = "SIN" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_TAN()
{
	NC_code = "TAN" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_CEIL()
{
	NC_code = "CEIL" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_FLOOR()
{
	NC_code = "FLOOR" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_ROUND()
{
	NC_code = "ROUND" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_EXP()
{
	NC_code = "EXP" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_LN()
{
	NC_code = "LN" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_SQRT()
{
	NC_code = "SQRT" + KuoHao(get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_MAX()
{
	NC_code = "MAX" + KuoHao(get_son_at(0)->NC_code + "," + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_MIN()
{
	NC_code = "MIN" + KuoHao(get_son_at(0)->NC_code + "," + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_POW()
{
	NC_code = "POW" + KuoHao(get_son_at(0)->NC_code + "," + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_JIAN()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "-" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_JIA()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "+" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_CHENG()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "*" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_CHU()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "/" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_MOD()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "MOD" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_NOT()
{
	NC_code = "";
	NC_code = NC_code + KuoHao(kong() + "NOT" + get_son_at(0)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_XIAOYU()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "<" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_DAYU()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + ">" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_XIAODENGYU()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "<=" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_DAYUDENGYU()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + ">=" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_DENGYU()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "=" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_BUDENGYU()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "<>" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_AND()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "AND" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_XOR()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "XOR" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_OR()
{
	NC_code = KuoHao(get_son_at(0)->NC_code + "OR" + get_son_at(1)->NC_code);
}

void nb_NC_block__write_code::NC_CODE_M00()
{
	NC_code = NC_Line("M00");
}

void nb_NC_block__write_code::NC_CODE_M01()
{

}

void nb_NC_block__write_code::NC_CODE_M02()
{
}

void nb_NC_block__write_code::NC_CODE_M03()
{
	NC_code = NC_Line("M03");
}

void nb_NC_block__write_code::NC_CODE_M04()
{
	NC_code = NC_Line("M04");
}

void nb_NC_block__write_code::NC_CODE_M05()
{
	NC_code = NC_Line("M05");
}

void nb_NC_block__write_code::NC_CODE_M06()
{
	string str = "";
	int num = get_son_at(0)->ans_value + 1;
	//str = str + "T" + get_son_at(0)->NC_code[0] + "M06"; //get_son_at(0)->NC_code转成int
	str = str + "M06" + "T" + d2str(num,0); //12.3zy
	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_M08()
{
	NC_code = NC_Line("M08");
}

void nb_NC_block__write_code::NC_CODE_M09()
{
	NC_code = NC_Line("M09");
}

void nb_NC_block__write_code::NC_CODE_M19()
{
}

void nb_NC_block__write_code::NC_CODE_M30()
{
	NC_code = NC_Line("M30");
}

void nb_NC_block__write_code::NC_CODE_G00()
{
	NC_code = NC_Line("G00");
}

void nb_NC_block__write_code::NC_CODE_G01()
{
	NC_code = NC_Line("G01");
}

void nb_NC_block__write_code::NC_CODE_G04()
{
}

void nb_NC_block__write_code::NC_CODE_G52()
{

}

void nb_NC_block__write_code::NC_CODE_G53()
{
}

void nb_NC_block__write_code::NC_CODE_G54()
{
	NC_code = NC_Line("G54");
}

void nb_NC_block__write_code::NC_CODE_G55()
{
	NC_code = NC_Line("G55");
}

void nb_NC_block__write_code::NC_CODE_G56()
{
	NC_code = NC_Line("G56");
}

void nb_NC_block__write_code::NC_CODE_G57()
{
	NC_code = NC_Line("G57");
}

void nb_NC_block__write_code::NC_CODE_G58()
{
	NC_code = NC_Line("G58");
}

void nb_NC_block__write_code::NC_CODE_G59()
{
	NC_code = NC_Line("G59");
}

void nb_NC_block__write_code::NC_CODE_G90()
{
	NC_code = NC_Line("G90");
}

void nb_NC_block__write_code::NC_CODE_WAIT()
{
	NC_code = NC_Line("WAIT()");
}

void nb_NC_block__write_code::NC_CODE_G91()
{
	NC_code = NC_Line("G91");
}

void nb_NC_block__write_code::NC_CODE_F()
{
	string str = "";
	str = str + "F" + get_son_at(0)->NC_code;
	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_FUZHI()
{
	string str = "";
	str = str + get_son_at(0)->NC_code + ":=" + get_son_at(1)->NC_code;
	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_G31_X_Y_Z_A_C()
{
	string str = "G31 ";
	string str_in[] = { "","","","","" };
	string str_zhou[] = { "X","Y","Z","A","C" };

	for (int i = 0; i < 5; i++)
	{
		if (abs(get_son_at(i)->ans_value - BUZHIXING) < 0.000001)
		{
			str_in[i] = "";
		}
		else
		{
			str_in[i] += str_zhou[i] + KuoHao(get_son_at(i)->NC_code);
		}
		str += str_in[i];
	}
	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_X_Y_Z_A_C()
{
	string str = "";
	string str_in[] = { "","","","","" };
	string str_zhou[] = { "X","Y","Z","A","C" };

	for (int i = 0; i < 5; i++)
	{
		if (abs(get_son_at(i)->ans_value - BUZHIXING) < 0.000001)
		{
			str_in[i] = "";
		}
		else
		{
			str_in[i] += str_zhou[i] + KuoHao(get_son_at(i)->NC_code);
		}
		str += str_in[i];
	}
	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_IF()
{
	//不用写
}

void nb_NC_block__write_code::NC_CODE_NEXT()
{
	//不用写
}

void nb_NC_block__write_code::NC_CODE_BACK()
{
	//不用写
}

void nb_NC_block__write_code::NC_CODE_END()
{
	//不用写
}

void nb_NC_block__write_code::NC_CODE_EXIT()
{
	string str = "";
	NC_code = NC_Line("EXIT");;
}

void nb_NC_block__write_code::NC_CODE_WHILE_K()
{
	string str = "";
	string str1 = "";
	//NCLINE不打分号
	str = str1 + "WHILE" + KuoHao(get_son_at(0)->get_son_at(0)->NC_code) + "DO" + endl();
	str += get_son_at(1)->NC_code;
	str += NC_Line(str1 + "END_WHILE");
	NC_code = str;

}

void nb_NC_block__write_code::NC_CODE_IF_K()
{
	//IF_THEN
	string str = "";
	string str1 = "";
	if (count_son == 3)
	{
		//NCLINE不打分号
		str = str1 + "IF" + KuoHao(get_son_at(0)->get_son_at(0)->NC_code) + "THEN" + endl();
		str += get_son_at(1)->NC_code;
		str += NC_Line(str1 + "END_IF");
		NC_code = str;
	}

	//IF_ELSE
	if (count_son == 5)
	{
		//NCLINE不打分号
		str = str1 + "IF" + KuoHao(get_son_at(0)->get_son_at(0)->NC_code) + "THEN" + endl();
		str += get_son_at(1)->NC_code;
		str += str1 + "ELSE" + endl();
		str += get_son_at(3)->NC_code;
		str += NC_Line(str1 + "END_IF");
		NC_code = str;
	}

	//IF_ELSEIF_ELSE
	if (count_son == 7)
	{
		//NCLINE不打分号
		str = str1 + "IF" + KuoHao(get_son_at(0)->get_son_at(0)->NC_code) + "THEN" + endl();
		str += get_son_at(1)->NC_code;
		str += str1 + "ELSEIF" + get_son_at(2)->get_son_at(0)->NC_code + "THEN" + endl();
		str += get_son_at(3)->NC_code;
		str += str1 + "ELSE" + endl();
		str += get_son_at(5)->NC_code;
		str += NC_Line(str1 + "END_IF");
		NC_code = str;
	}

}

void nb_NC_block__write_code::NC_CODE_PROCESS_K()
{
	string str = "";
	for (int i = 0; i < count_son; i++)
	{
		str += son_block_ptr_vec[i]->NC_code;
	}
	NC_code = str;
}

void nb_NC_block__write_code::NC_CODE_BL_A()
{
	string str = "";
	NC_code = str + "@" + ZhongKuoHao( son_block_ptr_vec[0]->NC_code);
}

void nb_NC_block__write_code::NC_CODE_BL_JIN()
{
	string str = "";
	NC_code = str + "#" + ZhongKuoHao(son_block_ptr_vec[0]->NC_code);
}

void nb_NC_block__write_code::NC_CODE_CHANGSHU()
{
	if (get_father() == 0)
	{
		NC_code = d2str(ans_value, 8);
	}
	else
	{
		if (get_father()->get_block_type() == BH_BL_A)
		{
			NC_code = to_string(int(ans_value));
		}
		else if (get_father()->get_block_type() == BH_BL_JIN)
		{
			NC_code = to_string(int(ans_value));
		}
		else if (get_father()->get_block_type() == BH_MOD)
		{
			NC_code = to_string(int(ans_value));
		}
		else if (ans_value < 0.0)
		{
			NC_code = YuanKuoHao(d2str(ans_value, 8));
		}
		else
		{
			NC_code = d2str(ans_value, 8);
		}
	}
}

void nb_NC_block__write_code::NC_CODE_X_Y_Z_A_C_F()
{
	string str = "";
	string str_in[] = { "","","","","" };
	string str_zhou[] = { "X","Y","Z","A","C" };

	for (int i = 0; i < 5; i++)
	{
		if (abs(get_son_at(i)->ans_value - BUZHIXING) < 0.000001)
		{
			str_in[i] = "";
		}
		else
		{
			str_in[i] += str_zhou[i] + YuanKuoHao(get_son_at(i)->NC_code);
		}
		str += str_in[i];
	}

	str += "F" + YuanKuoHao(get_son_at(5)->NC_code);

	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_G31_X_Y_Z_A_C_F()
{
	string str = "G31 ";
	string str_in[] = { "","","","","" };
	string str_zhou[] = { "X","Y","Z","A","C" };

	for (int i = 0; i < 5; i++)
	{
		if (abs(get_son_at(i)->ans_value - BUZHIXING) < 0.000001)
		{
			str_in[i] = "";
		}
		else
		{
			str_in[i] += str_zhou[i] + YuanKuoHao(get_son_at(i)->NC_code);
		}
		str += str_in[i];
	}

	str += "F" + YuanKuoHao(get_son_at(5)->NC_code);

	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_G01_X_Y_Z_A_C_F()
{
	string str = "G01 ";
	string str_in[] = { "","","","","" };
	string str_zhou[] = { "X","Y","Z","A","C" };

	for (int i = 0; i < 5; i++)
	{
		if (abs(get_son_at(i)->ans_value - BUZHIXING) < 0.000001)
		{
			str_in[i] = "";
		}
		else
		{
			str_in[i] += str_zhou[i] + YuanKuoHao(get_son_at(i)->NC_code);
		}
		str += str_in[i];
	}

	str += "F" + YuanKuoHao(get_son_at(5)->NC_code);

	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_ZhengHao()
{
	NC_code = get_son_at(0)->NC_code;
}

void nb_NC_block__write_code::NC_CODE_G01_X_Y_Z_A_C()
{
	string str = "G01 ";
	string str_in[] = { "","","","","" };
	string str_zhou[] = { "X","Y","Z","A","C" };

	for (int i = 0; i < 5; i++)
	{
		if (abs(get_son_at(i)->ans_value - BUZHIXING) < 0.000001)
		{
			str_in[i] = "";
		}
		else
		{
			str_in[i] += str_zhou[i] + YuanKuoHao(get_son_at(i)->NC_code);
		}
		str += str_in[i];
	}

	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_M98()
{
	//NC_M98的ans_value和其他不同
	string a = "";
	int name_num = 0;
	memcpy(&name_num, reinterpret_cast<char*>(&ans_value) + 4, 4);

	a = a + "M98 P" + to_string(name_num);//通过指向程序类的指针 调用程序的名字
	//在ans_value  里面存放 程序类的指针
	NC_code = NC_Line(a);
}

void nb_NC_block__write_code::NC_CODE_M99()
{
	NC_code = NC_Line("M99");
}

void nb_NC_block__write_code::NC_CODE_S_speed()
{
	string str = "";
	str = str + "S" + get_son_at(0)->NC_code;
	NC_code = NC_Line(str);
}

void nb_NC_block__write_code::NC_CODE_Set_RGB()
{
	//不写
}

void nb_NC_block__write_code::NC_CODE_M13()
{
	NC_code = NC_Line("M13");
}

void nb_NC_block__write_code::NC_CODE_M14()
{
	NC_code = NC_Line("M14");
}

void nb_NC_block__write_code::NC_CODE_M15()
{
	NC_code = NC_Line("M15");
}

void nb_NC_block__write_code::NC_CODE_S2_speed()
{
	string str = "";
	str = str = "S2=" + get_son_at(0)->NC_code;
	NC_code = NC_Line(str);
}

//执行函数：唯一的入口

NC_control_message nb_NC_block::ZhiXing()
{
	//如果目前还没有出现错误
	if (blk_mes.error_message == 1)
	{
		//如果还有子块未处理完成
		son_not_end = (son_now_at < count_son);

		//第二次进来，子块已经全部被标记，son_now_at == count_son，  2024.2.23 zy
		if (son_now_at == count_son && father_block_ptr == nullptr)
		{
			ctrl_mes.next_block = father_block_ptr;
			//son_now_at = 0; //再将所有子程序执行一遍
			//son_not_end = true; //不进入 改为父指针
			//son_block_ptr_vec[son_now_at]->now_not_cal = true;
		}
		if (son_not_end)
		{
			//如果子程序还没有运行,则需要去运行子块
			if (son_block_ptr_vec[son_now_at]->now_not_cal)
			{
				//设置下一步执行这个子块
				ctrl_mes.next_block = son_block_ptr_vec[son_now_at];
				//标记子块已运行
				now_not_cal = !now_not_cal;//貌似不起作用
				//没进check   //当前子程序块号+1 全部在check函数中增加 2024.2.23 zy
				//++son_now_at;
				
			}
			//若子块已执行，则需要去check子块信息
			else  
			{
				//check子块 返回信息
				block_check();
				//指定下一步执行的块为自己
				ctrl_mes.next_block = this;
				//标记子块没运行
				now_not_cal = !now_not_cal;//貌似也没用
				////当前子程序块号+1 全部在check函数中增加
				//++son_now_at;
			}
		}
		//如果所有子块已经处理完成,进行自身计算
		else
		{
			if (count_son == 0)
			{
				//对于没有子块的情况应先check
				block_check();
			}

			//第二次进来，子块已经全部被标记，son_now_at == count_son，  2024.2.23 zy
			//if (son_now_at == count_son ) //father_block_ptr = null
			//{
			//	reset();
			//}
			//else
			{
				//指定下一步执行的块为父程序块 (针对大多数程序块，除了M98 M99)
				//M98 M99  将在self cal 中改变next关系
				ctrl_mes.next_block = father_block_ptr;
				//调用自己的计算函数
				self_cal();

				//24.2.26 zy
				//if (this->Block_type_index == 44)  //主程序M30 执行完结束
				//{
				//	ctrl_mes.next_block = nullptr;
				//}

				//还原本程序块结构信息，其他信息不影响
				son_now_at = 0;
				now_not_cal = false;
			}
		}
	}
	else
	{
		//如果之前的子程序块已经出现了错误，则不需要在进行后续执行
		//直接设置下一步执行的块为父程序块
		ctrl_mes.next_block = father_block_ptr;
		//在此不需要还原结构，因为已经出错，不会再回来这里；
		//但是需要保证在下次运行前进行reset()
	}
	return ctrl_mes;
}

//返回信息检查函数

void nb_NC_block::block_check()
{
	(this->*(func_vec.pblock_check[Block_type_index]))();
}

//程序块自身计算函数

void nb_NC_block::self_cal()
{
	if (Block_type_index == 75)
	{
		int a = 1;
	}
	(this->*(func_vec.pself_cal[Block_type_index]))();

}

//整个程序一起写，与上面两个在执行函数中调用不同
// 此函数需要进行递归调用
//nc程序生成函数 在NC_code中产生代码
//此程序应该在所有程序块完成时调用，将逐级调用下级程序块，最后在顶层程序块生成所有的程序

void nb_NC_block::write_nc_code()
{
	//递归调用下级程序块的程序生成函数
	for (int i = 0; i < count_son; i++)
	{
		son_block_ptr_vec[i]->write_nc_code();
	}

	//生成自己的函数生成函数
	(this->*(func_vec.pnc_code[Block_type_index]))();
}

//整个程序一起写，与上面两个在执行函数中调用不同
// 此函数需要进行递归调用
//nc程序生成函数 在NC_code中产生代码
//此程序应该在所有程序块完成时调用，将逐级调用下级程序块，最后在顶层程序块生成所有的程序

//copy全部，包括子块，所有都是全新的

nb_NC_block* nb_NC_block::new_copy()
{
	nb_NC_block* ls_block_ptr = new nb_NC_block(*this);
	ls_block_ptr->father_block_ptr = nullptr;
	ls_block_ptr->is_BL_now = false;

	for (int i = 0; i < count_son; i++)
	{
		ls_block_ptr->set_son(*(get_son_at(i)->new_copy()), i);
	}
	ls_block_ptr->ans_value = ans_value;
	ls_block_ptr->NC_code = NC_code;
	return ls_block_ptr;
}

//copy全部，包括子块，所有都是全新的

//获得程序块类型号

//设置块的最后一个子块为断点

//构造函数

nb_NC_block::nb_NC_block()
	:nb_NC_block__write_code()
{
	count_son = 0;
	father_block_ptr = 0;
	son_block_ptr_vec.clear();
	machine_ptr = 0;

	Block_type_index = 0;

	son_not_end = true;
	now_not_cal = true;
	son_now_at = 0;
	ans_value = 0;

	ctrl_mes.is_stop = false;
	ctrl_mes.next_block = 0;

	blk_mes.ans_message = 0;
	blk_mes.error_message = 1;

	//ls_get_in = "";
}

//指定type构造函数

nb_NC_block::nb_NC_block(int type)
{
	if (type == BH_BL_A)
	{
		//分配变量号
		count_son = 0;
		father_block_ptr = 0;
		son_block_ptr_vec.clear();
		machine_ptr = 0;

		Block_type_index = type;

		son_not_end = true;
		now_not_cal = true;
		son_now_at = 0;

		ctrl_mes.is_stop = false;
		ctrl_mes.next_block = 0;

		blk_mes.ans_message = 0;
		blk_mes.error_message = 1;
		ans_value = 0;

		NC_code = "";

		//申请变量号
		this->set_son_count(1);
		nb_NC_block* ls_changliangk = new nb_NC_block(BH_CHANGSHU);
		//获得变量号
		//ls_changliangk->ans_value=
		this->set_son(*ls_changliangk, 0);
	}
	else if (type == BH_BL_JIN)
	{
		//分配变量号
		count_son = 0;
		father_block_ptr = 0;
		son_block_ptr_vec.clear();
		machine_ptr = 0;

		Block_type_index = type;

		son_not_end = true;
		now_not_cal = true;
		son_now_at = 0;

		ctrl_mes.is_stop = false;
		ctrl_mes.next_block = 0;

		blk_mes.ans_message = 0;
		blk_mes.error_message = 1;
		ans_value = 0;
		NC_code = "";

		//申请变量号
		this->set_son_count(1);
		nb_NC_block* ls_changliangk = new nb_NC_block(BH_CHANGSHU);
		//获得变量号
		//ls_changliangk->ans_value=
		this->set_son(*ls_changliangk, 0);
	}
	else
	{
		count_son = 0;
		father_block_ptr = 0;
		son_block_ptr_vec.clear();
		machine_ptr = 0;

		Block_type_index = type;

		son_not_end = true;
		now_not_cal = true;
		son_now_at = 0;


		ctrl_mes.is_stop = false;
		ctrl_mes.next_block = 0;

		blk_mes.ans_message = 0;
		blk_mes.error_message = 1;
		ans_value = 0;
		NC_code = "";
	}
}

nb_NC_block::nb_NC_block(int type, int number)
	:nb_NC_block__write_code()
{
	//分配变量号
	//set_father(father_block);
		//分配变量号
	count_son = 0;
	set_father(father_block);
	son_block_ptr_vec.clear();
	machine_ptr = 0;

	if (type == 1)
	{
		Block_type_index = BH_BL_JIN;
	}
	else if (type == 0)
	{
		Block_type_index = BH_BL_A;
	}
	else
	{
		//报错
		Block_type_index = BH_BL_A;
	}

	son_not_end = true;
	now_not_cal = true;
	son_now_at = 0;

	ctrl_mes.is_stop = false;
	ctrl_mes.next_block = 0;

	blk_mes.ans_message = 0;
	blk_mes.error_message = 1;
	ans_value = 0;

	NC_code = "";
	//构造常数块
	this->set_son_count(1);
	nb_NC_block* ls_changliangk = new nb_NC_block(BH_CHANGSHU);
	ls_changliangk->ans_value = number;
	//获得变量号
	this->set_son(*ls_changliangk, 0);
}

nb_NC_block::nb_NC_block(int type, nb_NC_block& num_block)
	:nb_NC_block__write_code()
{
	//分配变量号
	//set_father(father_block);
	count_son = 0;
	set_father(father_block);
	son_block_ptr_vec.clear();
	machine_ptr = 0;

	if (type == 1)
	{
		Block_type_index = BH_BL_JIN;
	}
	else if (type == 0)
	{
		Block_type_index = BH_BL_A;
	}
	else
	{
		//报错
		Block_type_index = BH_BL_A;
	}
	son_not_end = true;
	now_not_cal = true;
	son_now_at = 0;

	ctrl_mes.is_stop = false;
	ctrl_mes.next_block = 0;

	blk_mes.ans_message = 0;
	blk_mes.error_message = 1;
	ans_value = 0;

	NC_code = "";

	this->set_son_count(1);
	//获得变量号
	this->set_son(num_block, 0);
}

//复制构造函数，不复制子项
nb_NC_block::nb_NC_block(const nb_NC_block& A)
{
	//复制部分
	count_son = A.count_son;
	father_block_ptr = A.father_block_ptr;
	son_block_ptr_vec.resize(A.son_block_ptr_vec.size());
	for (int i = 0; i < count_son; i++)
	{
		son_block_ptr_vec[i] = A.son_block_ptr_vec[i];
	}
	machine_ptr = A.machine_ptr;
	Block_type_index = A.Block_type_index;

	//初始化部分
	son_not_end = true;
	now_not_cal = true;
	son_now_at = 0;

	ctrl_mes.is_stop = false;
	ctrl_mes.next_block = 0;

	blk_mes.ans_message = 0;
	blk_mes.error_message = 1;
	ans_value = 0;
}

nb_NC_block::~nb_NC_block()
{
	//首先调用所有子项的析构函数，
	// 而析构函数中会删除所有子项对象，在将子项指针设置为0
	// 自己所有成员自己析构。
	//析构子块
	//for (int i = 0; i < count_son; i++)
	//{
	//	delete son_block_ptr_vec[i];
	//	son_block_ptr_vec[i] = 0;
	//}
	////析构自身
	//for (int i = 0; i < count_son; i++)
	//{
	//	son_block_ptr_vec[i] = 0;
	//}
	////delete this;

	//析构加判定条件防止报错 25.11.6 zy
	for (int i = 0; i < son_block_ptr_vec.size(); i++)
	{
		delete son_block_ptr_vec[i];
		son_block_ptr_vec[i] = 0;
	}
	
}

//=
nb_NC_block& nb_NC_block::operator=(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_FUZHI);
	ls_block->set_son_count(2);
	ls_block->set_son(*this, 0);
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

//=
nb_NC_block& nb_NC_block::operator=(double d_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_FUZHI);
	ls_block->set_son_count(2);
	ls_block->set_son(*this, 0);

	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}
//20231206-ZYW
void nb_NC_block::edit_BL_AT_from_to(int before, int now)
{
	queue<nb_NC_block*> temp_queue;
	temp_queue.push(this);
	nb_NC_block* block_now = 0;
	while (!temp_queue.empty())
	{//层级遍历
		block_now = temp_queue.front();
		for (size_t i = 0; i < block_now->count_son; i++)
		{
			temp_queue.push(block_now->get_son_at(i));
		}

		{
			//遍历的操作
			// 变量下的常量块=before,则替换成now
			if (block_now->Block_type_index == BH_BL_A)
			{
				if (block_now->get_son_at(0)->Block_type_index == BH_CHANGSHU)
				{
					if (abs(block_now->get_son_at(0)->ans_value - before) < 0.01)
					{
						block_now->get_son_at(0)->ans_value = double(now);
					}
				}
			}
			//遍历的操作
		}
		temp_queue.pop();
	}
}

bool nb_NC_block::set_son(nb_NC_block& son, int i)
{
	//以下程序解决了已经有父项的程序块，避免多重下挂的问题
	//常见的如变量重用，或者大段程序的重用
	//遇到这种情况，则应该将下挂部分复制以后，将副本下挂
	//利用了默认产生的程序块父项为0的特点。
	if (i >= 0 && i < count_son)
	{
		//如果输入的block没有父项，则直接下挂
		if (son.get_father() == 0)
		{
			son_block_ptr_vec[i] = &son;
			son_block_ptr_vec[i]->set_father(*this);
			return true;
		}
		//否则应该new一个副本下挂
		else
		{
			son_block_ptr_vec[i] = son.new_copy();
			son_block_ptr_vec[i]->set_father(*this);
			return true;
		}
	}
	else
	{
		return false;
	}
}

//是0常数程序块

//是1常数程序块

// 是常数块

//获得父程序块指针，没有则为0；

nb_NC_block__tree::nb_NC_block__tree()
{
	count_son = 0;
	father_block_ptr = 0;
	son_block_ptr_vec.shrink_to_fit();
}

nb_NC_block__tree::nb_NC_block__tree(const nb_NC_block__tree& A)
:nb_NC_block__base(A)
{
	father_block_ptr=A.father_block_ptr;
	count_son = A.count_son;
	for (int i = 0; i < count_son; i++)
	{
		son_block_ptr_vec[i] = A.son_block_ptr_vec[i];
	}
}

nb_NC_block* nb_NC_block__tree::get_father()
{
	return father_block_ptr;
}

//获得指定为值，子项指针

nb_NC_block* nb_NC_block__tree::get_son_at(int i)
{
	if (i >= 0 && i < count_son)
	{
		return son_block_ptr_vec[i];
	}
	else
	{
		return 0;
	}
}

//链接父项

void nb_NC_block__tree::set_father(nb_NC_block& father)
{
	father_block_ptr = &father;
}

//设置子项数量

bool nb_NC_block__tree::set_son_count(int i)
{
	if (i >= 0)
	{
		count_son = i;
		son_block_ptr_vec.resize(i);
		return true;
	}
	else
	{
		return false;
	}
}

//获得程序块类型号

nb_NC_block__data::nb_NC_block__data()
{
	Block_type_index = 0;
	ans_value = 0.0;
}

nb_NC_block__data::nb_NC_block__data(const nb_NC_block__data& A)
	:nb_NC_block__base(A)
{
	Block_type_index = A.Block_type_index;
	ans_value = A.ans_value;
}

int nb_NC_block__data::get_block_type()
{
	return Block_type_index;
}

//是0常数程序块

bool nb_NC_block__data::is_zero_block()
{
	if (
		(Block_type_index == BH_CHANGSHU)
		&&
		(abs(ans_value) < 0.0000000000000001)
		)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//是1常数程序块

bool nb_NC_block__data::is_one_block()
{
	if (
		(Block_type_index == BH_CHANGSHU)
		&&
		(
			abs(ans_value - 1.0) < 0.0000000000000001)
		)
	{
		return true;
	}
	else
	{
		return false;
	}

}

// 是常数块

bool nb_NC_block__data::is_changshu()
{
	if (this->get_block_type() == BH_CHANGSHU)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Serialize_infile(std::ofstream& oss, nb_NC_block& block_in)
{
	const std::string startMarker = "abc";
	oss.write(startMarker.c_str(), startMarker.size());
	// 调用辅助函数进行序列化  
	SerializeBlock(oss, block_in);
	oss.close();
	return true;

}
// 辅助递归函数  
void SerializeBlock(std::ofstream& oss, nb_NC_block& block)
{
	const int START_MARKER = 0xABCD; // 开始标记  
	const int END_MARKER = 0xDCBA;   // 结束标记  

	// 写入开始标记  
	oss.write(reinterpret_cast<const char*>(&START_MARKER), sizeof(int));

	// 写入 Block_type_index  
	oss.write(reinterpret_cast<const char*>(&block.Block_type_index), sizeof(int));

	// 写入 ans_value  
	oss.write(reinterpret_cast<const char*>(&block.ans_value), sizeof(double));

	// 写入 count_son  
	oss.write(reinterpret_cast<const char*>(&block.count_son), sizeof(int));

	// 写入结束标记  
	oss.write(reinterpret_cast<const char*>(&END_MARKER), sizeof(int));

	// 递归写入子块  
	if (block.count_son > 0) {
		for (size_t i = 0; i < block.son_block_ptr_vec.size(); ++i) {
			SerializeBlock(oss, *block.son_block_ptr_vec[i]);
		}
	}
}

//nb_NC_block& Deserialize()
//{
//	std::ifstream ifile("E:\\ml_240221\\serialized_data.bin", std::ios::binary);
//	if (!ifile.is_open()) {
//		throw std::runtime_error("文件打开失败");
//	}
//	// 移动文件指针到指定位置  
//	ifile.seekg(nb_NC_block::position);
//
//	// 读取标志位  
//	std::string startMarker = "abc";
//	std::string fileMarker(startMarker.size(), '\0');
//	ifile.read(&fileMarker[0], startMarker.size());
//
//	if (fileMarker != startMarker) {
//		throw std::runtime_error("未找到标识符");
//	}
//
//	// 反序列化块  
//	//nb_NC_block rootBlock;
//	//rootBlock = DeserializeBlock(ifile);
//
//	nb_NC_block* rootBlock = &DeserializeBlock(ifile);
//
//
//	// 寻找下一个标识符  
//	std::string nextMarker(startMarker.size(), '\0');
//	while (ifile.read(&nextMarker[0], startMarker.size()))
//	{
//		if (nextMarker == startMarker) {
//			// 找到下一个标识符，将位置设置为标识符开头  
//			nb_NC_block::position = ifile.tellg() - static_cast<std::streamoff>(startMarker.size());
//			break;
//		}
//		// 如果到达文件末尾并且没有找到下一个标识符  
//		// 进行相应处理 
//		else if (ifile.eof()) {
//			throw std::runtime_error("未找到更多的标识符");
//			break;
//		}
//	}
//	//if (nb_NC_block::nb_NC_block::position <= nb_NC_block::f_manager->fileSizeList[nb_NC_block::f_manager->file_num])
//	//{
//	//	if (rootBlock.Block_type_index == BH_M30)
//	//	{
//	//		nb_NC_block::f_manager->file_check = true;
//	//		nb_NC_block::f_manager->file_num++;
//	//	}
//	//	else
//	//	{
//	//		nb_NC_block::f_manager->file_check = false;
//	//	}
//	//}
//	//else
//	//{
//	//	if (nb_NC_block::f_manager->file_check == false)
//	//	{
//	//		throw std::runtime_error("程序未包含M30");
//	//	}
//	//}
//	
//	return *rootBlock; // 返回当前块  
//}
//
//
//nb_NC_block& DeserializeBlock(std::ifstream& ifile)
//{
//	const int START_MARKER = 0xABCD; // 开始标记  
//	const int END_MARKER = 0xDCBA;   // 结束标记  
//
//	// 读取开始标记  
//	int marker;
//	ifile.read(reinterpret_cast<char*>(&marker), sizeof(int));
//	if (marker != START_MARKER) {
//		std::cerr << "Error: Start marker not found!" << std::endl;
//		//return nullptr; // 处理错误  
//	}
//
//	nb_NC_block* block = new nb_NC_block(0);
//
//	// 读取 Block_type_index  
//	ifile.read(reinterpret_cast<char*>(&block->Block_type_index), sizeof(int));
//
//	// 读取 ans_value  
//	ifile.read(reinterpret_cast<char*>(&block->ans_value), sizeof(double));
//
//	// 读取 count_son  
//	ifile.read(reinterpret_cast<char*>(&block->count_son), sizeof(int));
//
//	// 读取结束标记  
//	ifile.read(reinterpret_cast<char*>(&marker), sizeof(int));
//	if (marker != END_MARKER) {
//		std::cerr << "Error: End marker not found!" << std::endl;
//		//return nullptr; // 处理错误  
//	}
//
//	// 读取子块  
//	if (block->count_son > 0) {
//		block->son_block_ptr_vec.resize(block->count_son);
//		for (int i = 0; i < block->count_son; ++i) {
//			block->son_block_ptr_vec[i] = &DeserializeBlock(ifile);
//			block->son_block_ptr_vec[i]->set_father(*block);
//		}
//	}
//
//	return *block;
//}
bool file_pos_get(int nc_name)
{
	std::ifstream ifile("serialized_data_menu.bin", std::ios::binary);
	if (!ifile.is_open()) {
		throw std::runtime_error("文件打开失败");
	}
	while (true) {
		//// 读取name的长度  
		////size_t nameLength;
		////ifile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
		////if (ifile.eof()) break; // 到达文件末尾，退出循环  
		////if (ifile.fail()) {
		////	ifile.close();
		////	throw std::runtime_error("读取name长度失败");
		////}

		//// 读取name  
		//std::string name(nameLength, '\0'); // 创建指定长度的字符串  
		//ifile.read(&name[0], nameLength);
		//if (ifile.fail()) {
		//	ifile.close();
		//	throw std::runtime_error("读取name失败");
		//}

		//// 读取文件大小（起始）  
		//std::streampos startSize;
		//ifile.read(reinterpret_cast<char*>(&startSize), sizeof(startSize));
		//if (ifile.fail()) {
		//	ifile.close();
		//	throw std::runtime_error("读取起始fileSize失败");
		//}

		//// 读取文件大小（结束）  
		//std::streampos endSize;
		//ifile.read(reinterpret_cast<char*>(&endSize), sizeof(endSize));
		//if (ifile.fail()) {
		//	ifile.close();
		//	throw std::runtime_error("读取结束fileSize失败");
		//}
		int name = 0;
		std::streampos startSize = 0, endSize = 0;
		// 读取 name (int 类型)  
		ifile.read(reinterpret_cast<char*>(&name), sizeof(name));
		if (ifile.eof()) {
			std::cout << "读取已完成，文件末尾已到达。" << std::endl; // 提示读取已完成  
			break; // 到达文件末尾，退出循环  
		}
		if (ifile.fail()) {
			ifile.close();
			throw std::runtime_error("读取 name 失败");
		}

		// 读取 fileSize Start (std::streamsize 类型)  
		ifile.read(reinterpret_cast<char*>(&startSize), sizeof(startSize));
		if (ifile.fail()) {
			ifile.close();
			throw std::runtime_error("读取 fileSize Start 失败");
		}

		// 读取 fileSize End (std::streamsize 类型)  
		ifile.read(reinterpret_cast<char*>(&endSize), sizeof(endSize));
		if (ifile.fail()) {
			ifile.close();
			throw std::runtime_error("读取 fileSize End 失败");
		}
		// 检查当前name是否与nc_name匹配  
		if (name == (nc_name)) {
			// 保存当前的文件位置  
			save_now_file_pos();
			nb_NC_block::position = startSize; // 假设我们需要存储起始文件大小  
			ifile.close();
			return true; // 找到匹配，返回true  
		}
	}

	ifile.close();
	return false; // 没有找到匹配的nc_file  
}
//void file_manager::file_name_get()
//{
//	long long previous_file_size = -1; // 临时保存上一个fileSize  
//	long long current_file_size = 0;
//	std::ifstream ifile("E:\\ml_240221\\serialized_data_menu.bin", std::ios::binary);
//	if (!ifile.is_open()) {
//		throw std::runtime_error("文件打开失败");
//	}
//	std::string line;
//	std::string current_name;
//	while (std::getline(ifile, current_name)) {
//		// 读取下一行以获取fileSize  
//		if (std::getline(ifile, line)) {
//			current_file_size = std::stoll(line); // 将读取的fileSize转换为长整型  
//
//			// 检查当前fileSize是否与目标fileSize匹配  
//			if (previous_file_size != -1 && position > previous_file_size && position <= current_file_size)
//			{
//
//				b_name = current_name;
//				ifile.close();
//			}
//			previous_file_size = current_file_size;
//		}
//	}
//}

bool save_now_file_pos()
{
	nb_NC_block::position_stack.push(nb_NC_block::position);
	return true;
}

bool recovery_now_file_pos()
{
	if (!nb_NC_block::position_stack.empty()) { // 检查栈是否为空  
		nb_NC_block::position = nb_NC_block::position_stack.top();
		nb_NC_block::position_stack.pop();
	}
	return true;
}