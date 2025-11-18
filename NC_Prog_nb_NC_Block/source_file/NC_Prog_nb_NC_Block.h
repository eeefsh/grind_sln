#pragma once
#ifdef NC_Prog_nb_NC_Block_EXPORTS
#define NC_Prog_nb_NC_Block_API __declspec(dllexport)
#else
#define NC_Prog_nb_NC_Block_API __declspec(dllimport)
#endif

#include <stack>
#include <vector>
#include <string>
#include "常量定义.h"
#include "message.h"
#include "manager_h/MA_030201_NC_Prog_Virtual_Machine.h"
#include "NC_block_funs.h"
#include "nc_manager.h"

#include "fstream"
using std::stack;
using std::string;
using std::vector;

class nc_program;
class nb_NC_block;

extern NC_Prog_nb_NC_Block_API nc_manager machine_var_manager;
extern NC_Prog_nb_NC_Block_API std::streampos position;
extern NC_Prog_nb_NC_Block_API std::stack<std::streampos>position_stack;


//基类 用于实现多态
class NC_Prog_nb_NC_Block_API nb_NC_block__base
{

};

//base-1
class NC_Prog_nb_NC_Block_API nb_NC_block__data
	:virtual public nb_NC_block__base
{
public:
	nb_NC_block__data();
	nb_NC_block__data(const nb_NC_block__data& A);
public:
	//程序块类型: 操作，计算查询，句子，if，while。。。
	int Block_type_index;
public:
	//当前程序块的结果值
	//涉及:公式化简、结果计算、常量值等
	//M98中 0到-3  存目标程序块指针
	//M98中 -4到-7 存程序名字的编号（int类型）
	double ans_value;

public:
	//获得程序块类型号
	int get_block_type();
	//是0常数程序块
	bool is_zero_block();
	//是1常数程序块
	bool is_one_block();
	// 是常数块
	bool is_changshu();
};

//base-2
class NC_Prog_nb_NC_Block_API nb_NC_block__tree
	:virtual public nb_NC_block__base
{
public:
	nb_NC_block__tree();
	//只复制指针
	nb_NC_block__tree(const nb_NC_block__tree& A);
public:
	//指向父程序块的指针
	nb_NC_block* father_block_ptr;
public:
	//子程序块数量
	int count_son;
	//指向子程序块的指针
	vector<nb_NC_block*> son_block_ptr_vec;

public:
	//获得父程序块指针，没有则为0；
	nb_NC_block* get_father();

	//获得指定为值，子项指针
	nb_NC_block* get_son_at(int i);

public:
	//链接父项
	void set_father(nb_NC_block& father);

	//设置子项数量
	bool set_son_count(int i);
};

//合并
//run 实现程序可运行的变量


class NC_Prog_nb_NC_Block_API nb_NC_block__run :
	virtual public nb_NC_block__data,
	virtual public nb_NC_block__tree
{
public:
	nb_NC_block__run();
	nb_NC_block__run(const nb_NC_block__run& A);

	~nb_NC_block__run();

public:
	//用于记录子程序的调用顺序
	static std::stack<nb_NC_block*> prog_stack;

public:
	//虚拟机指针
	static virtual_machine* machine_ptr;

public:
	//若真：子程序块还没执行完
	bool son_not_end;
	//若真：当前子程序块还没有执行，执行子程序块的执行程序
	//若假：当前子程序块已经执行，当前执行返回信息处理
	bool now_not_cal;
	//当前处理的子程序块编号
	int son_now_at;
public:
	//运行结构用信息
	NC_control_message ctrl_mes;
public:
	//返回信息
	block_message blk_mes;

public:
	//当出现错误需要重新执行时使用
	//只需要调用树根的reset();
	void reset();

	//增加子程序块
	bool push_back(nb_NC_block& k_in);

	void set_machine(virtual_machine* p_machine);

	//设置块的最后一个子块为断点
	void set_stop();
};

//run-1 共用处理函数
class NC_Prog_nb_NC_Block_API nb_NC_block__funs_GY_CL_back :
	virtual public nb_NC_block__run
{
public:
	nb_NC_block__funs_GY_CL_back();
	nb_NC_block__funs_GY_CL_back(const nb_NC_block__funs_GY_CL_back& A);
public:
	void GY_CL_back_KFL_Cal_One();
	void GY_CL_back_KFL_Cal_Two();
	void GY_CL_back_KFL_GX_One();
	void GY_CL_back_KFL_GX_Two();
	void GY_CL_back_KFL_CZ_Zero();
	void GY_CL_back_KFL_CZ_One();
	void GY_CL_back_KFL_CZ_Two();
	void GY_CL_back_KFL_CZ_Duo();
	void GY_CL_back_KFL_Z_IF();
	void GY_CL_back_KFL_Z_NEXT();
	void GY_CL_back_KFL_Z_BACK();
	void GY_CL_back_KFL_Z_END();
	void GY_CL_back_KFL_JGZ_EXIT();
	void GY_CL_back_KFL_JG_WHILE();
	void GY_CL_back_KFL_JGZ_IF();
	void GY_CL_back_KFL_JG_Process();

};

//run-1.1 处理函数
class NC_Prog_nb_NC_Block_API nb_NC_block__funs_CL_back:
	public nb_NC_block__funs_GY_CL_back
{
public:
	nb_NC_block__funs_CL_back();
	nb_NC_block__funs_CL_back(const nb_NC_block__funs_CL_back& A);

public:
	void CL_back_FuHao();
	void CL_back_KuoHao();
	void CL_back_ABS();
	void CL_back_ACOS();
	void CL_back_ASIN();
	void CL_back_ATAN();
	void CL_back_COS();
	void CL_back_SIN();
	void CL_back_TAN();
	void CL_back_CEIL();
	void CL_back_FLOOR();
	void CL_back_ROUND();
	void CL_back_EXP();
	void CL_back_LN();
	void CL_back_SQRT();
	void CL_back_MAX();
	void CL_back_MIN();
	void CL_back_POW();
	void CL_back_JIAN();
	void CL_back_JIA();
	void CL_back_CHENG();
	void CL_back_CHU();
	void CL_back_MOD();
	void CL_back_NOT();
	void CL_back_XIAOYU();
	void CL_back_DAYU();
	void CL_back_XIAODENGYU();
	void CL_back_DAYUDENGYU();
	void CL_back_DENGYU();
	void CL_back_BUDENGYU();
	void CL_back_AND();
	void CL_back_XOR();
	void CL_back_OR();
	void CL_back_M00();
	void CL_back_M01();
	void CL_back_M02();
	void CL_back_M03();
	void CL_back_M04();
	void CL_back_M05();
	void CL_back_M06();
	void CL_back_M08();
	void CL_back_M09();
	void CL_back_M19();
	void CL_back_M30();
	void CL_back_G00();
	void CL_back_G01();
	void CL_back_G04();
	void CL_back_G52();
	void CL_back_G53();
	void CL_back_G54();
	void CL_back_G55();
	void CL_back_G56();
	void CL_back_G57();
	void CL_back_G58();
	void CL_back_G59();
	void CL_back_G90();
	void CL_back_WAIT();
	void CL_back_G91();
	void CL_back_F();
	void CL_back_FUZHI();
	void CL_back_G31_X_Y_Z_A_C();
	void CL_back_X_Y_Z_A_C();
	void CL_back_IF();
	void CL_back_NEXT();
	void CL_back_BACK();
	void CL_back_END();
	void CL_back_EXIT();
	void CL_back_WHILE_K();
	void CL_back_IF_K();
	void CL_back_PROCESS_K();
	void CL_back_BL_A();
	void CL_back_BL_JIN();
	void CL_back_CHANGSHU();
	void CL_back_X_Y_Z_A_C_F();
	void CL_back_G31_X_Y_Z_A_C_F();
	void CL_back_G01_X_Y_Z_A_C_F();
	void CL_back_ZhengHao();
	void CL_back_G01_X_Y_Z_A_C();
	void CL_back_M98();
	void CL_back_M99();
	void CL_back_S_speed();
	void CL_back_Set_RGB();
	void CL_back_M13();
	void CL_back_M14();
	void CL_back_M15();
	void CL_back_S2_speed();

};

//run-2 自身计算函数
class NC_Prog_nb_NC_Block_API nb_NC_block__funs_CAL:
	virtual public nb_NC_block__run
{
public:
	nb_NC_block__funs_CAL();
	nb_NC_block__funs_CAL(const nb_NC_block__funs_CAL& A);
public:
	void CAL_FuHao();
	void CAL_KuoHao();
	void CAL_ABS();
	void CAL_ACOS();
	void CAL_ASIN();
	void CAL_ATAN();
	void CAL_COS();
	void CAL_SIN();
	void CAL_TAN();
	void CAL_CEIL();
	void CAL_FLOOR();
	void CAL_ROUND();
	void CAL_EXP();
	void CAL_LN();
	void CAL_SQRT();
	void CAL_MAX();
	void CAL_MIN();
	void CAL_POW();
	void CAL_JIAN();
	void CAL_JIA();
	void CAL_CHENG();
	void CAL_CHU();
	void CAL_MOD();
	void CAL_NOT();
	void CAL_XIAOYU();
	void CAL_DAYU();
	void CAL_XIAODENGYU();
	void CAL_DAYUDENGYU();
	void CAL_DENGYU();
	void CAL_BUDENGYU();
	void CAL_AND();
	void CAL_XOR();
	void CAL_OR();
	void CAL_M00();
	void CAL_M01();
	void CAL_M02();
	void CAL_M03();
	void CAL_M04();
	void CAL_M05();
	void CAL_M06();
	void CAL_M08();
	void CAL_M09();
	void CAL_M19();
	void CAL_M30();
	void CAL_G00();
	void CAL_G01();
	void CAL_G04();
	void CAL_G52();
	void CAL_G53();
	void CAL_G54();
	void CAL_G55();
	void CAL_G56();
	void CAL_G57();
	void CAL_G58();
	void CAL_G59();
	void CAL_G90();
	void CAL_WAIT();
	void CAL_G91();
	void CAL_F();
	void CAL_FUZHI();
	void CAL_G31_X_Y_Z_A_C();
	void CAL_X_Y_Z_A_C();
	void CAL_IF();
	void CAL_NEXT();
	void CAL_BACK();
	void CAL_END();
	void CAL_EXIT();
	void CAL_WHILE_K();
	void CAL_IF_K();
	void CAL_PROCESS_K();
	void CAL_BL_A();
	void CAL_BL_JIN();
	void CAL_CHANGSHU();
	void CAL_X_Y_Z_A_C_F();
	void CAL_G31_X_Y_Z_A_C_F();
	void CAL_G01_X_Y_Z_A_C_F();
	void CAL_ZhengHao();
	void CAL_G01_X_Y_Z_A_C();
	void CAL_M98();
	void CAL_M99();
	void CAL_S_speed();
	void CAL_Set_RGB();
	void CAL_M13();
	void CAL_M14();
	void CAL_M15();
	void CAL_S2_speed();
};

//write 生成NC程序的相关代码
class NC_Prog_nb_NC_Block_API nb_NC_block__write_code:
	virtual public nb_NC_block__data,
	virtual public nb_NC_block__tree
{
public:
	nb_NC_block__write_code();
	nb_NC_block__write_code(const nb_NC_block__write_code& a);
public:
	////仅用于M98
	//string ls_get_in;
	//当前程序块的代码
	std::string NC_code;
public:
	string kong();
	string NC_endl();
	string endl();
	string Comment(string& comment);
	string NC_Line(string code);
	string NC_Line(string& code, string& comment);
	string NC_Comment(string& comment);
	string KuoHao(string& code);
	//d 是输入的double ，i 是要转化的位数
	string d2str(double d, int i);
	string YuanKuoHao(string str_in);
	//ZYW-240109
	string ZhongKuoHao(string str_in);
public:
	void NC_CODE_FuHao();
	void NC_CODE_KuoHao();
	void NC_CODE_ABS();
	void NC_CODE_ACOS();
	void NC_CODE_ASIN();
	void NC_CODE_ATAN();
	void NC_CODE_COS();
	void NC_CODE_SIN();
	void NC_CODE_TAN();
	void NC_CODE_CEIL();
	void NC_CODE_FLOOR();
	void NC_CODE_ROUND();
	void NC_CODE_EXP();
	void NC_CODE_LN();
	void NC_CODE_SQRT();
	void NC_CODE_MAX();
	void NC_CODE_MIN();
	void NC_CODE_POW();
	void NC_CODE_JIAN();
	void NC_CODE_JIA();
	void NC_CODE_CHENG();
	void NC_CODE_CHU();
	void NC_CODE_MOD();
	void NC_CODE_NOT();
	void NC_CODE_XIAOYU();
	void NC_CODE_DAYU();
	void NC_CODE_XIAODENGYU();
	void NC_CODE_DAYUDENGYU();
	void NC_CODE_DENGYU();
	void NC_CODE_BUDENGYU();
	void NC_CODE_AND();
	void NC_CODE_XOR();
	void NC_CODE_OR();
	void NC_CODE_M00();
	void NC_CODE_M01();
	void NC_CODE_M02();
	void NC_CODE_M03();
	void NC_CODE_M04();
	void NC_CODE_M05();
	void NC_CODE_M06();
	void NC_CODE_M08();
	void NC_CODE_M09();
	void NC_CODE_M19();
	void NC_CODE_M30();
	void NC_CODE_G00();
	void NC_CODE_G01();
	void NC_CODE_G04();
	void NC_CODE_G52();
	void NC_CODE_G53();
	void NC_CODE_G54();
	void NC_CODE_G55();
	void NC_CODE_G56();
	void NC_CODE_G57();
	void NC_CODE_G58();
	void NC_CODE_G59();
	void NC_CODE_G90();
	void NC_CODE_WAIT();
	void NC_CODE_G91();
	void NC_CODE_F();
	void NC_CODE_FUZHI();
	void NC_CODE_G31_X_Y_Z_A_C();
	void NC_CODE_X_Y_Z_A_C();
	void NC_CODE_IF();
	void NC_CODE_NEXT();
	void NC_CODE_BACK();
	void NC_CODE_END();
	void NC_CODE_EXIT();
	void NC_CODE_WHILE_K();
	void NC_CODE_IF_K();
	void NC_CODE_PROCESS_K();
	void NC_CODE_BL_A();
	void NC_CODE_BL_JIN();
	void NC_CODE_CHANGSHU();
	void NC_CODE_X_Y_Z_A_C_F();
	void NC_CODE_G31_X_Y_Z_A_C_F();
	void NC_CODE_G01_X_Y_Z_A_C_F();
	void NC_CODE_ZhengHao();
	void NC_CODE_G01_X_Y_Z_A_C();
	void NC_CODE_M98();
	void NC_CODE_M99();
	void NC_CODE_S_speed();
	void NC_CODE_Set_RGB();
	void NC_CODE_M13();
	void NC_CODE_M14();
	void NC_CODE_M15();
	void NC_CODE_S2_speed();
};

//合并
//程序块：用于表达所有的程序单元，无论大小均为程序块
class NC_Prog_nb_NC_Block_API nb_NC_block:
	public nb_NC_block__write_code,
	public nb_NC_block__funs_CL_back,
	public nb_NC_block__funs_CAL
{
	friend class nb_NC_block;
	static NC_block_funs func_vec;
public:
	static nb_NC_block father_block;
	bool is_BL = false;//不用
	bool is_BL_now = false;
	bool need_release = false;
public:
	static std::streampos position;
	static std::stack<std::streampos> position_stack;


//基本功能：
public:
	//1 执行函数：唯一的入口
	NC_control_message ZhiXing();

	//1.1 返回信息检查函数
	void block_check();

	//1.2 程序块自身计算函数
	void self_cal();

	//2 nc程序生成函数 在NC_code中产生代码
	//此程序应该在所有程序块完成时调用，将逐级调用下级程序块，最后在顶层程序块生成所有的程序
	void write_nc_code();

//构造：
public:
	//构造函数
	nb_NC_block();

	//指定type构造函数
	nb_NC_block(int type);

	//变量构造函数，两个int参数（仅用于变量）
	nb_NC_block(int type, int number);

	//变量构造函数，int参数 0:@ 1:#   num_block代表可以计算出程序号的块
	nb_NC_block(int type, nb_NC_block& num_block);

	//复制构造函数，不复制子项  2025暂时不知道哪里需要用这种情况
	nb_NC_block(const nb_NC_block& A);

	~nb_NC_block();

	//copy全部，包括子块，所有都是全新的
	nb_NC_block* new_copy();
	
//赋值：
public:
	//=
	nb_NC_block& operator=(nb_NC_block& block_in);

	//=
	nb_NC_block& operator=(double d_in);

//20231206-ZYW
public:
	void edit_BL_AT_from_to(int before, int now);

public:
	//链接子项
	bool set_son(nb_NC_block& son, int i);
public:
	// 声明友元函数  
	friend NC_Prog_nb_NC_Block_API bool Serialize_infile(std::ofstream& oss, nb_NC_block& block_in);

	friend NC_Prog_nb_NC_Block_API void SerializeBlock(std::ofstream& oss, nb_NC_block& block);

//	friend NC_Prog_nb_NC_Block_API nb_NC_block& Deserialize();
//public:
//	friend NC_Prog_nb_NC_Block_API nb_NC_block& DeserializeBlock(std::ifstream& ifile);
	friend NC_Prog_nb_NC_Block_API	bool file_pos_get(int nc_name);
	friend NC_Prog_nb_NC_Block_API	bool save_now_file_pos();//M98使用
	friend NC_Prog_nb_NC_Block_API	bool recovery_now_file_pos();
};

NC_Prog_nb_NC_Block_API bool Serialize_infile(std::ofstream& oss, nb_NC_block& block_in);

NC_Prog_nb_NC_Block_API void SerializeBlock(std::ofstream& oss, nb_NC_block& block);

//NC_Prog_nb_NC_Block_API nb_NC_block& Deserialize();
//
//NC_Prog_nb_NC_Block_API nb_NC_block& DeserializeBlock(std::ifstream& ifile);
NC_Prog_nb_NC_Block_API	bool file_pos_get(int nc_name);
NC_Prog_nb_NC_Block_API	bool save_now_file_pos();//M98使用
NC_Prog_nb_NC_Block_API	bool recovery_now_file_pos();