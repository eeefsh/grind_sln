#include "..\pch.h"
#define NC_Prog_nb_NC_Block_EXPORTS
#include "nb_block_functions_1.h"

nb_NC_block& nb_FuHao(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_FuHao);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = -block_in.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_abs(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_ABS);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = abs(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_acos(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_ACOS);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = acos(block_in.ans_value) / datum::pi * 180.0;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_asin(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_ASIN);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = asin(block_in.ans_value) / datum::pi * 180.0;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_atan(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_ATAN);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = atan(block_in.ans_value) / datum::pi * 180.0;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_cos(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_COS);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = cos(block_in.ans_value / 180.0 * datum::pi);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_sin(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_SIN);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = sin(block_in.ans_value / 180.0 * datum::pi);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_tan(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_TAN);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = tan(block_in.ans_value / 180.0 * datum::pi);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_ceil(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_CEIL);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = ceil(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_floor(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_FLOOR);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = floor(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_round(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_ROUND);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = round(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_exp(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_EXP);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = exp(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_ln(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_LN);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = std::log(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_sqrt(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_SQRT);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);
	//如果为常数块，则计算出结果返回
	if (block_in.is_changshu())
	{
		//新建一个常数返回块
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		//此步体现了这个计算，根据函数的计算来确定
		ls_block_new->ans_value = sqrt(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& nb_max(nb_NC_block& block_in, nb_NC_block& block_in1)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_MAX);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);
	ls_block->set_son(block_in1, 1);
	return *ls_block;
}

nb_NC_block& nb_min(nb_NC_block& block_in, nb_NC_block& block_in1)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_MIN);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);
	ls_block->set_son(block_in1, 1);
	return *ls_block;
}

nb_NC_block& nb_pow(nb_NC_block& block_di, nb_NC_block& block_zhishu)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_POW);
	ls_block->set_son_count(2);
	ls_block->set_son(block_di, 0);
	ls_block->set_son(block_zhishu, 1);
	return *ls_block;
}


nb_NC_block& operator+(nb_NC_block& block_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_ZHENGHAO);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = (block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator-(nb_NC_block& block_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_FuHao);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = -(block_in.ans_value);
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator-(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_JIAN);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);

	if (block_in1.is_changshu() && block_in1.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in1.ans_value - block_in2.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}

	return *ls_block;
}

nb_NC_block& operator-(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_JIAN);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in.ans_value - d_in;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 0.0)
	{
		nb_NC_block* ls_block_new = block_in.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator+(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_JIA);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);

	if (block_in1.is_changshu() && block_in2.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in1.ans_value + block_in2.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else if (block_in1.is_zero_block())
	{
		nb_NC_block* ls_block_new = block_in2.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else if (block_in2.is_zero_block())
	{
		nb_NC_block* ls_block_new = block_in1.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator+(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_JIA);
	ls_block->set_son_count(2);

	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block& ls_block1 = nb_ChangShu(d_in);
	ls_block->set_son(ls_block1, 1);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in.ans_value + d_in;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 0.0)
	{
		nb_NC_block* ls_block_new = block_in.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator*(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_CHENG);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);

	if (block_in1.is_changshu() && block_in2.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in1.ans_value * block_in2.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	if (block_in2.is_zero_block() || block_in1.is_zero_block())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = 0.0;
		delete ls_block;
		return *ls_block_new;
	}
	else if (block_in1.is_one_block())
	{
		nb_NC_block* ls_block_new = block_in2.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else if (block_in2.is_one_block())
	{
		nb_NC_block* ls_block_new = block_in1.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator*(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_CHENG);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);
	ls_block->set_son(nb_ChangShu(d_in), 1);
	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in.ans_value * d_in;
		delete ls_block;
		return *ls_block_new;
	}
	else if (block_in.is_zero_block())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = 0.0;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 0.0)
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = 0.0;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 1.0)
	{
		nb_NC_block* ls_block_new = block_in.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator/(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_CHU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);

	if (block_in1.is_changshu() && block_in2.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in1.ans_value / block_in2.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else if (block_in1.is_zero_block())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = 0.0;
		delete ls_block;
		return *ls_block_new;
	}
	else if (block_in2.is_one_block())
	{
		nb_NC_block* ls_block_new = block_in1.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator/(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_CHU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);
	ls_block->set_son(nb_ChangShu(d_in), 1);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = block_in.ans_value / d_in;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 1.0)
	{
		nb_NC_block* ls_block_new = block_in.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator%(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_MOD);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator%(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_MOD);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}

nb_NC_block& operator<(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_XIAOYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator<(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_XIAOYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}

nb_NC_block& operator>(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_DAYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator>(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_DAYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}

nb_NC_block& operator<=(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_XIAODENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator<=(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_XIAODENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}

nb_NC_block& operator>=(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_DAYUDENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator>=(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_DAYUDENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}

nb_NC_block& operator==(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句-
	nb_NC_block* ls_block = new nb_NC_block(BH_DENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator==(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_DENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}

nb_NC_block& operator!=(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_BUDENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator!=(nb_NC_block& block_in, double d_in)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_BUDENGYU);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in, 0);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 1);
	return *ls_block;
}

nb_NC_block& operator&&(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_AND);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator^(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_XOR);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}

nb_NC_block& operator||(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	nb_NC_block* ls_block = new nb_NC_block(BH_OR);
	ls_block->set_son_count(2);
	ls_block->set_son(block_in1, 0);
	ls_block->set_son(block_in2, 1);
	return *ls_block;
}


nb_NC_block& operator<<(nb_NC_block& block_in1, nb_NC_block& block_in2)
{
	// TODO: 在此处插入 return 语句
	if ((block_in1.get_block_type()) == BH_PROCESS_K)
	{
		block_in1.count_son++;
		block_in1.son_block_ptr_vec.push_back(&block_in2);
		block_in2.father_block_ptr = &block_in1;
	}
	else
	{
		//报错
	}
	return block_in1;
}

nb_NC_block& operator!(nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_NOT);
	ls_block->set_son_count(1);
	ls_block->set_son(block_in, 0);

	return *ls_block;
}

nb_NC_block& operator-(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_JIAN);
	ls_block->set_son_count(2);
	//创建一个常数程序块
	ls_block->set_son(nb_ChangShu(d_in), 0);
	//设置第二个
	ls_block->set_son(block_in, 1);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = d_in - block_in.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator+(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_JIA);
	ls_block->set_son_count(2);
	//创建一个常数程序块
	ls_block->set_son(nb_ChangShu(d_in), 0);
	//设置第二个
	ls_block->set_son(block_in, 1);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = d_in + block_in.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator*(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_CHENG);
	ls_block->set_son_count(2);
	//创建一个常数程序块
	ls_block->set_son(nb_ChangShu(d_in), 0);
	//设置第二个
	ls_block->set_son(block_in, 1);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = d_in * block_in.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 0.0)
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = 0.0;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 1.0)
	{
		nb_NC_block* ls_block_new = block_in.new_copy();
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator/(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_CHU);
	ls_block->set_son_count(2);

	ls_block->set_son(nb_ChangShu(d_in), 0);
	ls_block->set_son(block_in, 1);

	if (block_in.is_changshu())
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = d_in / block_in.ans_value;
		delete ls_block;
		return *ls_block_new;
	}
	else if (d_in == 0.0)
	{
		nb_NC_block* ls_block_new = new nb_NC_block(BH_CHANGSHU);
		ls_block_new->ans_value = 0.0;
		delete ls_block;
		return *ls_block_new;
	}
	else
	{
		return *ls_block;
	}
}

nb_NC_block& operator%(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_MOD);
	ls_block->set_son_count(2);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 0);

	//设置第二个
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

nb_NC_block& operator<(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_XIAOYU);
	ls_block->set_son_count(2);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 0);

	//设置第二个
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

nb_NC_block& operator>(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_DAYU);
	ls_block->set_son_count(2);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 0);

	//设置第二个
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

nb_NC_block& operator<=(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_XIAODENGYU);
	ls_block->set_son_count(2);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 0);

	//设置第二个
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

nb_NC_block& operator>=(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_DAYUDENGYU);
	ls_block->set_son_count(2);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 0);

	//设置第二个
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

nb_NC_block& operator==(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_DENGYU);
	ls_block->set_son_count(2);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 0);

	//设置第二个
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

nb_NC_block& operator!=(double d_in, nb_NC_block& block_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_BUDENGYU);
	ls_block->set_son_count(2);

	//创建一个常数程序块
	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->set_son_count(0);
	ls_block1->ans_value = d_in;
	ls_block->set_son(*ls_block1, 0);

	//设置第二个
	ls_block->set_son(block_in, 1);
	return *ls_block;
}

nb_NC_block& nb_M00()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M00);
	return *ls_block;
}

nb_NC_block& nb_M01()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M01);
	return *ls_block;
}

nb_NC_block& nb_M02()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M02);
	return *ls_block;
}

nb_NC_block& nb_M03()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M03);
	return *ls_block;
}

nb_NC_block& nb_M04()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M04);
	return *ls_block;
}

nb_NC_block& nb_M05()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M05);
	return *ls_block;
}

nb_NC_block& nb_M06(int tool_using, int sl_pos_on_slz)
{
	if (tool_using < 0 || tool_using > 6)
	{
		tool_using = 0;
	}

	nb_NC_block* ls_block = new nb_NC_block(BH_M06);
	ls_block->ans_value = sl_pos_on_slz;
	ls_block->set_son_count(1);

	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->ans_value = tool_using;
	ls_block->set_son(*ls_block1, 0);
	return *ls_block;
}

nb_NC_block& nb_M08()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M08);
	return *ls_block;
}

nb_NC_block& nb_M09()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M09);
	return *ls_block;
}

nb_NC_block& nb_M30()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M30);
	return *ls_block;
}

nb_NC_block& nb_M13()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M13);
	return *ls_block;
}

nb_NC_block& nb_M14()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M14);
	return *ls_block;
}

nb_NC_block& nb_M15()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M15);
	return *ls_block;
}

nb_NC_block& nb_G00()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G00);
	return *ls_block;
}

nb_NC_block& nb_G01()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G01);
	return *ls_block;
}

nb_NC_block& nb_G04()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G04);
	return *ls_block;
}

nb_NC_block& nb_G52()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G52);
	return *ls_block;
}

nb_NC_block& nb_G53()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G53);
	return *ls_block;
}

nb_NC_block& nb_G54()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G54);
	return *ls_block;
}

nb_NC_block& nb_G55()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G55);
	return *ls_block;
}

nb_NC_block& nb_G56()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G56);
	return *ls_block;
}

nb_NC_block& nb_G57()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G57);
	return *ls_block;
}

nb_NC_block& nb_G58()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G58);
	return *ls_block;
}

nb_NC_block& nb_G59()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G59);
	return *ls_block;
}

nb_NC_block& nb_G90()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G90);
	return *ls_block;
}


nb_NC_block& nb_Set_RGB(int color)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_Set_RGB);

	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block->set_son_count(1);
	ls_block1->ans_value = color;
	ls_block->set_son(*ls_block1, 0);
	return *ls_block;
}

nb_NC_block& nb_WAIT()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_WAIT);
	return *ls_block;
}

nb_NC_block& nb_M98(nb_NC_block* targer_prog_root,int name_number)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M98);
	ls_block->ans_value = (double)(int(targer_prog_root));

	nb_NC_block* ls_ptr = targer_prog_root;
	memcpy(&(ls_block->ans_value), &ls_ptr, 4);//存指针
	int ls_int = name_number;
	memcpy(reinterpret_cast<char*>(&(ls_block->ans_value)) + 4, &ls_int, 4);//存指针

	//丢失名字
	return *ls_block;
}

nb_NC_block& nb_M99()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_M99);
	return *ls_block;
}

nb_NC_block& nb_S_speed(int s)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_S_speed);
	ls_block->set_son_count(1);

	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->ans_value = double(s);

	ls_block->set_son(*ls_block1, 0);
	return *ls_block;
}

nb_NC_block& nb_S2_speed(int s)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_S2_speed);
	ls_block->set_son_count(1);

	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->ans_value = double(s);

	ls_block->set_son(*ls_block1, 0);
	return *ls_block;
}

nb_NC_block& nb_G91()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G91);
	return *ls_block;
}

nb_NC_block& nb_F(double d_in)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_F);
	ls_block->set_son_count(1);

	nb_NC_block* ls_block1 = new nb_NC_block(BH_CHANGSHU);
	ls_block1->ans_value = d_in;

	ls_block->set_son(*ls_block1, 0);
	return *ls_block;
}

nb_NC_block& nb_SET_VALUE(nb_NC_block& zuobian, nb_NC_block& youbian)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_FUZHI);
	ls_block->set_son_count(2);
	ls_block->set_son(zuobian, 0);
	ls_block->set_son(youbian, 1);
	return *ls_block;
}

nb_NC_block& nb_G31_X_Y_Z_A_C(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& a, nb_NC_block& c)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G31_X_Y_Z_A_C);
	ls_block->set_son_count(5);
	ls_block->set_son(x, 0);
	ls_block->set_son(y, 1);
	ls_block->set_son(z, 2);
	ls_block->set_son(a, 3);
	ls_block->set_son(c, 4);
	return *ls_block;
}

nb_NC_block& nb_X_Y_Z_A_C(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& a, nb_NC_block& c)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_X_Y_Z_A_C);
	ls_block->set_son_count(5);
	ls_block->set_son(x, 0);
	ls_block->set_son(y, 1);
	ls_block->set_son(z, 2);
	ls_block->set_son(a, 3);
	ls_block->set_son(c, 4);
	return *ls_block;
}

nb_NC_block& nb_X_Y_Z_A_C_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& a, nb_NC_block& c, nb_NC_block& f)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_X_Y_Z_A_C_F);
	ls_block->set_son_count(6);
	ls_block->set_son(x, 0);
	ls_block->set_son(y, 1);
	ls_block->set_son(z, 2);
	ls_block->set_son(a, 3);
	ls_block->set_son(c, 4);
	ls_block->set_son(f, 5);
	return *ls_block;
}

nb_NC_block& nb_G31_X_Y_Z_A_C_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& a, nb_NC_block& c, nb_NC_block& f)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G31_X_Y_Z_A_C_F);
	ls_block->set_son_count(6);
	ls_block->set_son(x, 0);
	ls_block->set_son(y, 1);
	ls_block->set_son(z, 2);
	ls_block->set_son(a, 3);
	ls_block->set_son(c, 4);
	ls_block->set_son(f, 5);
	return *ls_block;
}

nb_NC_block& nb_G01_X_Y_Z_A_C_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& a, nb_NC_block& c, nb_NC_block& f)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G01_X_Y_Z_A_C_F);
	ls_block->set_son_count(6);
	ls_block->set_son(x, 0);
	ls_block->set_son(y, 1);
	ls_block->set_son(z, 2);
	ls_block->set_son(a, 3);
	ls_block->set_son(c, 4);
	ls_block->set_son(f, 5);
	return *ls_block;
}

nb_NC_block& nb_G01_X_Y_Z_A_C(
	nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& a, nb_NC_block& c)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_G01_X_Y_Z_A_C);
	ls_block->set_son_count(5);
	ls_block->set_son(x, 0);
	ls_block->set_son(y, 1);
	ls_block->set_son(z, 2);
	ls_block->set_son(a, 3);
	ls_block->set_son(c, 4);
	return *ls_block;
}

nb_NC_block& nb_X(nb_NC_block& x)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C(x, ls_block, ls_block, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_Y(nb_NC_block& y)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C(ls_block, y, ls_block, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_Z(nb_NC_block& z)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C(ls_block, ls_block, z, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_A(nb_NC_block& a)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C(ls_block, ls_block, ls_block, a, ls_block);
	return ans;
}

nb_NC_block& nb_C(nb_NC_block& c)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C(ls_block, ls_block, ls_block, ls_block, c);
	return ans;
}

nb_NC_block& nb_X_Y_Z(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C(x, y, z, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_X_F(nb_NC_block& x, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C_F(x, ls_block, ls_block, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_Y_F(nb_NC_block& y, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C_F(ls_block, y, ls_block, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_Z_F(nb_NC_block& z, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C_F(ls_block, ls_block, z, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_A_F(nb_NC_block& a, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C_F(ls_block, ls_block, ls_block, a, ls_block, f);
	return ans;
}

nb_NC_block& nb_C_F(nb_NC_block& c, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C_F(ls_block, ls_block, ls_block, ls_block, c, f);
	return ans;
}

nb_NC_block& nb_X_Y_Z_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_X_Y_Z_A_C_F(x, y, z, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G31_X(nb_NC_block& x)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C(x, ls_block, ls_block, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_G31_Y(nb_NC_block& y)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C(ls_block, y, ls_block, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_G31_Z(nb_NC_block& z)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C(ls_block, ls_block, z, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_G31_A(nb_NC_block& a)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C(ls_block, ls_block, ls_block, a, ls_block);
	return ans;
}

nb_NC_block& nb_G31_C(nb_NC_block& c)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C(ls_block, ls_block, ls_block, ls_block, c);
	return ans;
}

nb_NC_block& nb_G31_X_Y_Z(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C(x, y, z, ls_block, ls_block);
	return ans;
}

nb_NC_block& nb_G31_X_F(nb_NC_block& x, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C_F(x, ls_block, ls_block, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G31_Y_F(nb_NC_block& y, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C_F(ls_block, y, ls_block, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G31_Z_F(nb_NC_block& z, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C_F(ls_block, ls_block, z, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G31_A_F(nb_NC_block& a, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C_F(ls_block, ls_block, ls_block, a, ls_block, f);
	return ans;
}

nb_NC_block& nb_G31_C_F(nb_NC_block& c, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C_F(ls_block, ls_block, ls_block, ls_block, c, f);
	return ans;
}

nb_NC_block& nb_G31_X_Y_Z_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G31_X_Y_Z_A_C_F(x, y, z, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G01_X_F(nb_NC_block& x, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G01_X_Y_Z_A_C_F(x, ls_block, ls_block, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G01_Y_F(nb_NC_block& y, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G01_X_Y_Z_A_C_F(ls_block, y, ls_block, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G01_Z_F(nb_NC_block& z, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G01_X_Y_Z_A_C_F(ls_block, ls_block, z, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& nb_G01_A_F(nb_NC_block& a, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G01_X_Y_Z_A_C_F(ls_block, ls_block, ls_block, a, ls_block, f);
	return ans;
}

nb_NC_block& nb_G01_C_F(nb_NC_block& c, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G01_X_Y_Z_A_C_F(ls_block, ls_block, ls_block, ls_block, c, f);
	return ans;
}

nb_NC_block& nb_G01_X_Y_Z_F(nb_NC_block& x, nb_NC_block& y, nb_NC_block& z, nb_NC_block& f)
{
	nb_NC_block& ls_block = *(new nb_NC_block(BH_CHANGSHU));
	ls_block.ans_value = BUZHIXING;
	nb_NC_block& ans = nb_G01_X_Y_Z_A_C_F(x, y, z, ls_block, ls_block, f);
	return ans;
}

nb_NC_block& IF_zi(nb_NC_block& tiaojian)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_IF);
	ls_block->set_son_count(1);
	ls_block->set_son(tiaojian, 0);
	return *ls_block;
}

nb_NC_block& NEXT_zi()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_NEXT);
	ls_block->set_son_count(0);
	return *ls_block;
}

nb_NC_block& BACK_zi()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_BACK);
	ls_block->set_son_count(0);
	return *ls_block;
}

nb_NC_block& END_zi()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_END);
	ls_block->set_son_count(0);
	return *ls_block;
}

nb_NC_block& EXIT_zi()
{
	nb_NC_block* ls_block = new nb_NC_block(BH_EXIT);
	ls_block->set_son_count(0);
	return *ls_block;
}

nb_NC_block& nb_WHILE_K(nb_NC_block& tiaojian, nb_NC_block& xunhuanti)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_WHILE_K);
	ls_block->set_son_count(4);

	nb_NC_block* ls_block3 = &IF_zi(tiaojian);
	ls_block->set_son(*ls_block3, 0);

	ls_block->set_son(xunhuanti, 1);

	nb_NC_block* ls_block1 = &BACK_zi();
	ls_block->set_son(*ls_block1, 2);

	nb_NC_block* ls_block2 = &END_zi();
	ls_block->set_son(*ls_block2, 3);
	return *ls_block;
}

nb_NC_block& nb_IF_K(nb_NC_block& tiaojian, nb_NC_block& zhuti)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_IF_K);
	ls_block->set_son_count(3);

	nb_NC_block* ls_block1 = &IF_zi(tiaojian);
	ls_block->set_son(*ls_block1, 0);

	ls_block->set_son(zhuti, 1);

	nb_NC_block* ls_block2 = &END_zi();
	ls_block->set_son(*ls_block2, 2);

	return *ls_block;
}

nb_NC_block& nb_IF_ELSE_K(nb_NC_block& tiaojian, nb_NC_block& zhuti1, nb_NC_block& zhuti2)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_IF_K);
	ls_block->set_son_count(5);

	nb_NC_block* ls_block1 = &IF_zi(tiaojian);
	ls_block->set_son(*ls_block1, 0);

	ls_block->set_son(zhuti1, 1);

	nb_NC_block* ls_block2 = &NEXT_zi();
	ls_block->set_son(*ls_block2, 2);

	ls_block->set_son(zhuti2, 3);

	nb_NC_block* ls_block3 = &END_zi();
	ls_block->set_son(*ls_block3, 4);
	return *ls_block;
}

nb_NC_block& nb_IF_ELSEIF_ELSE_K(
	nb_NC_block& tiaojian1, nb_NC_block& zhuti1,
	nb_NC_block& tiaojian2, nb_NC_block& zhuti2,
	nb_NC_block& zhuti3
)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_IF_K);
	ls_block->set_son_count(7);

	nb_NC_block* ls_block1 = &IF_zi(tiaojian1);
	ls_block->set_son(*ls_block1, 0);

	ls_block->set_son(zhuti1, 1);

	nb_NC_block* ls_block2 = &IF_zi(tiaojian2);
	ls_block->set_son(*ls_block2, 2);

	ls_block->set_son(zhuti2, 3);

	nb_NC_block* ls_block3 = &NEXT_zi();
	ls_block->set_son(*ls_block3, 4);

	ls_block->set_son(zhuti3, 5);

	nb_NC_block* ls_block4 = &END_zi();
	ls_block->set_son(*ls_block4, 6);

	return *ls_block;
}

nb_NC_block& nb_ChangShu(double d)
{
	nb_NC_block* ls_block = new nb_NC_block(BH_CHANGSHU);
	ls_block->set_son_count(0);
	ls_block->ans_value = d;
	return *ls_block;
}

//这个函数好像是内部使用的，不应该提供接口
nb_NC_block& nb_Process_K(int i)
{
	if (i < 0)
	{
		//错误
	}
	nb_NC_block* ls_block = new nb_NC_block(BH_PROCESS_K);
	ls_block->set_son_count(i);
	return *ls_block;
}

nb_NC_block& nb_new_BL_Block()
{
	int type = 0;
	int number = 0;
	//申请变量：调用变量申请函数
	//变量申请函数根据目前的情况产生type和number
	machine_var_manager.apply_var_num(type, number);
	//生成变量
	nb_NC_block* temp = new nb_NC_block(type, number);
	temp->set_father(nb_NC_block::father_block);
	temp->is_BL_now = true;
	return *temp;
	//return *(new nb_NC_block(type, number));

}

NC_Prog_nb_NC_Block_API nb_NC_block& nb_new_BL_Block(int no)
{
	nb_NC_block* temp = new nb_NC_block(0, no);
	temp->set_father(nb_NC_block::father_block);
	temp->is_BL_now = true;
	return *temp;
}

nb_NC_block& nb_BL_Block(int type, int no)
{
	return *(new nb_NC_block(type, no));
}

nb_NC_block& nb_BL(int no)
{
	return *(new nb_NC_block(0, no));
}

nb_NC_block& nb_BL(nb_NC_block& block_in)
{
	return *(new nb_NC_block(0, block_in));
}

void nb_ProBegin()
{
	machine_var_manager.prog_start();
}

void nb_ProEnd()
{
	machine_var_manager.prog_end();
}