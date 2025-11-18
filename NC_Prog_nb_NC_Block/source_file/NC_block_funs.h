 #pragma once
#include <vector>

class nb_NC_block;
using std::vector;

//程序块函数表：存放不同程序块的共用函数指针
typedef void(nb_NC_block::* void_fun_ptr)();

class NC_block_funs
{
public:
	vector<void_fun_ptr> pblock_check;
	vector<void_fun_ptr> pself_cal;
	vector<void_fun_ptr> pnc_code;

public:
	NC_block_funs();
};

#include "NC_Prog_nb_NC_Block.h"

