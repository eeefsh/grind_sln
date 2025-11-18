#pragma once
#pragma pack(push,1)
#ifdef NC_Prog_nb_NC_Block_EXPORTS
#define NC_Prog_nb_NC_Block_API __declspec(dllexport)
#else
#define NC_Prog_nb_NC_Block_API __declspec(dllimport)
#endif
//为了实现可以调试，则需要由调试器来运行程序
//程序运行后向调试器发送下一个要执行的程序块的指针；
//同时也发送需要是否需要中断。
//所以设计这个类来传递必要的消息
class nb_NC_block;
class NC_Prog_nb_NC_Block_API NC_control_message
{
public:
	//下一个执行的程序块
	nb_NC_block* next_block;
	//是否断点
	bool is_stop;
};

// 程序块运行状态消息：用于实现程序块按顺序执行
class NC_Prog_nb_NC_Block_API block_message
{
public:
	/*
		0	没有初始化（默认值）
		1	值运算
		2	关系运算
		3	操作
		4	结构子块 - IF - 是
		5	结构子块 - IF - 否
		6	结构子块 - NEXT
		7	结构子块 - BACK
		8	结构子块 - END
		9	结构子块 - EXIT
		10	结构主块 - while
		11	结构主块 - IF
		12	结构主块 - Process
	*/
	unsigned char ans_message;
	/*
		0	未填写错误信息
		1	无错误
		2	意外的子块
		3	子块错误
		4	计算时出错
		5	操作失败
	*/
	unsigned char error_message;

public:
	block_message();

	block_message(block_message& a);
};

#pragma pack(pop)