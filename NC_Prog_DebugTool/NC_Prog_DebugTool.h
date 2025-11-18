
#pragma once

#ifdef NC_Prog_DebugTool_EXPORTS
#define NC_Prog_DebugTool_API __declspec(dllexport)
#else
#define NC_Prog_DebugTool_API __declspec(dllimport)
#endif


#include "manager_h/MA_030201_NC_Prog_Virtual_Machine.h"
#include "manager_h\MA_031301_NC_Prog_Block_Prog_Struct.h"

class file_manager;
class NC_Prog_DebugTool_API debug_tool
{
public:
	nc_program_zhu* zhu_program_now;
public:
	nb_NC_block* nc_program_now;
public:
	virtual_machine* machine;
private:
	NC_control_message message_ctrl_now;
	block_message message_block_now;
 

private:
	bool has_error;

public:
	debug_tool();

public:
	void reset_debug();

public:
	void set_nc_prog(nc_block& nc_program);
	//zy 2024-0201
	void set_nc_prog(nc_program_zhu* tance);

	//ZYW 2023-1212
	//void set_nc_prog(nc_program_zhu& nc_program_zhu);
	void set_machine(virtual_machine* machine_in);

public:
	void reset_nc_prog();

public:
	//一直运行到完，遇到错误停止
	void run_until();
	//一句一句运行，直到父项是一个顺序块，并且子项已经全部结束
	bool run_one();

	void clean_temp_block();

	bool no_next_block();

};

//
//class NC_Prog_DebugTool_API file_manager
//{
//public:
//	file_manager();
//	~file_manager();	
//	void init(int name);
//
//public:
//	std::string dir;
//	//std::streampos position;
//	//std::stack<std::string> file_stack;
//	std::stack<std::streampos> position_stack;
//	int start_prog_name = 0;//需要初始化
//public:
//	int file_num = 1;
//	bool file_check = 1;
//public:
//	//bool file_pos_get(int nc_name);
//	//bool save_now_file_pos();//M98使用
//	//bool recovery_now_file_pos();
//	std::ifstream ifile_data;
//	std::ifstream ifile_data_menu;
//public:
//    nb_NC_block& Deserialize();
//
//    nb_NC_block& DeserializeBlock(std::ifstream& ifile);
//
//public:
//	 nc_block Recover_block();
//
//	 bool Recover_nc_code(string f_p);
//
//	 bool goto_prog_head();
//
//	 bool data_clear();
//};
