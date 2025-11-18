
#include "pch.h"
#define NC_Prog_DebugTool_EXPORTS
#include "NC_Prog_DebugTool.h"
#include <filesystem> // 需要C++17支持
#include <string>

debug_tool::debug_tool()
{
	nc_program_now = 0;
	machine = 0;
	reset_debug();
}

void debug_tool::reset_debug()
{
	zhu_program_now = 0;
	nc_program_now = 0;
	machine = 0;
	message_ctrl_now.is_stop = false;
	message_ctrl_now.next_block = 0;
	message_block_now.ans_message = 0;
	message_block_now.error_message = 0;
	nb_NC_block::position = 0;
}

//2025.3.6
//void debug_tool::set_nc_prog()
//{
//	block_now = Recover_block();
//	nc_program_now = block_now.block;
//	message_ctrl_now.next_block = block_now.block;
//	if (machine != 0)
//	{
//		nc_program_now->set_machine(machine);
//	}
//}

void debug_tool::set_nc_prog(nc_block& nc_program)
{
	nc_program_now = nc_program.block;
	message_ctrl_now.next_block = nc_program.block;
	if (machine != 0)
	{
		nc_program_now->set_machine(machine);
	}
}

void debug_tool::clean_temp_block()
{
	delete nc_program_now;
	nc_program_now = 0;

}

bool debug_tool::no_next_block()
{
	if (message_ctrl_now.next_block == nullptr)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}



//ZYW-20231212
//void debug_tool::set_nc_prog(nc_program_zhu& nc_program_zhu)
//{
//	//设置当前的树
//	nc_program_now = nc_program_zhu.entrance.block;
//	//在message里设置即将执行的树
//	message_ctrl_now.next_block = nc_program_zhu.entrance.block;
//	//如果有虚拟机床则设置虚拟机床
//	if (machine != 0)
//	{
//		nc_program_now->set_machine(machine);
//	}
//	//如何处理子程序间的转跳？
//}

void debug_tool::set_machine(virtual_machine* machine_in)
{
	machine = machine_in;
	if (nc_program_now != 0)
	{
		nc_program_now->set_machine(machine);
		machine->reset();
	}
	else
	{
		int i = 0;
	}
}

void debug_tool::set_nc_prog(nc_program_zhu* tance)
{

	zhu_program_now = tance;
	//设置当前的树
	nc_program_now =tance->entrance.block;
	//在message里设置即将执行的树
	message_ctrl_now.next_block = tance->entrance.block;
	//如果有虚拟机床则设置虚拟机床
	if (machine != 0)
	{
		nc_program_now->set_machine(machine);
	}
}

void debug_tool::reset_nc_prog()
{
	zhu_program_now->prog_file.goto_prog_head();
	message_ctrl_now.is_stop = false;
	message_block_now.ans_message = 0;
	message_block_now.error_message = 1;
}

void debug_tool::run_until()
{
	while (1)
	{
		if (message_ctrl_now.next_block == nullptr)
		{
			break;
		}
		//没有发现错误
		if (
			message_ctrl_now.next_block->blk_mes.error_message < 2
			)
		{
			message_ctrl_now = message_ctrl_now.next_block->ZhiXing();
		}
		//发现了错误，指向了错误所在的父项块
		else
		{
			//记录错误信息
			message_block_now = message_ctrl_now.next_block->blk_mes;
			break;
		}
	}
	//message_ctrl_now.
	//message_block_now
}

bool debug_tool::run_one()
{
	bool is_stop = false;
	while (1)
	{
		
		if (message_ctrl_now.next_block == nullptr)
		{
			return false;
		}
		//没有发现错误
		if (
			message_ctrl_now.next_block->blk_mes.error_message < 2
			)
		{
			if (message_ctrl_now.next_block->father_block_ptr != 0)
			{
				//对父项是顺序块且子项都已经执行完毕的块，可以认为是独立的一行
				if (
					message_ctrl_now.next_block->father_block_ptr->get_block_type() == BH_PROCESS_K
					&&
					message_ctrl_now.next_block->son_now_at >= message_ctrl_now.next_block->count_son
					)
				{
					is_stop = true;
					//int cur_son_at = message_ctrl_now.next_block->son_now_at;
				}
				//test
				//message_ctrl_now.next_block->write_nc_file();
				//string ls_s = message_ctrl_now.next_block->nc_file;
				//test
				message_ctrl_now = message_ctrl_now.next_block->ZhiXing();


				if (is_stop == true)
				{
					//is_stop = false;
					return true;
				}
			}
			else
			{
				//message_ctrl_now.next_block = nullptr;
				message_ctrl_now = message_ctrl_now.next_block->ZhiXing();

			}
		}
		//发现了错误，指向了错误所在的父项块
		else
		{
			//记录错误信息
			message_block_now = message_ctrl_now.next_block->blk_mes;
			return false;
		}
	}
	//message_ctrl_now.
	//message_block_now
}

//
//file_manager::file_manager()
//{
//
//}
//
//file_manager::~file_manager()
//{
//	ifile_data.close();
//	ifile_data_menu.close();
//
//}
//
//void file_manager::init(int name)
//{
//	dir = "serialized_data.bin";
//	start_prog_name = name;
//
//	if (ifile_data.is_open())
//	{
//		ifile_data.close();
//	}
//	ifile_data.open("serialized_data.bin", std::ios::binary);
//
//	if (ifile_data_menu.is_open())
//	{
//		ifile_data_menu.close();
//	}
//	ifile_data_menu.open("serialized_data_menu.bin", std::ios::binary);
//
//	goto_prog_head();
//}
//
//nb_NC_block& file_manager::Deserialize()
//{
//	if (ifile_data.is_open())
//	{
//		ifile_data.close();
//	}
//	ifile_data.open("serialized_data.bin", std::ios::binary);
//
//	if (!ifile_data.is_open()) {
//		throw std::runtime_error("文件打开失败");
//	}
//	// 定位到文件末尾并获取大小  
//	ifile_data.seekg(0, std::ios::end); // 移动到文件末尾  
//	std::streampos fileSize = ifile_data.tellg(); // 获取当前指针位置
//	std::streampos aaa = nb_NC_block::position;
//
//	if (nb_NC_block::position == fileSize)
//	{
//		return nb_M30();
//	}
//	// 移动文件指针到指定位置  
//	ifile_data.seekg(nb_NC_block::position);
//	// 读取标志位  
//	std::string startMarker = "abc";
//	std::string fileMarker(startMarker.size(), '\0');
//	ifile_data.read(&fileMarker[0], startMarker.size());
//
//	if (fileMarker != startMarker) {
//		throw std::runtime_error("未找到标识符");
//	}
//
//	// 反序列化块  
//	//nb_NC_block rootBlock;
//	//rootBlock = DeserializeBlock(ifile);
//
//	nb_NC_block* rootBlock = &DeserializeBlock(ifile_data);
//	nb_NC_block::position = ifile_data.tellg();
//
//	// 寻找下一个标识符  
//	//std::string nextMarker(startMarker.size(), '\0');
//	//while (ifile_data.read(&nextMarker[0], startMarker.size()))
//	//{
//	//	if (nextMarker == startMarker) {
//	//		// 找到下一个标识符，将位置设置为标识符开头  
//	//		nb_NC_block::position = ifile_data.tellg() - static_cast<std::streamoff>(startMarker.size());
//	//		break;
//	//	}
//	//	// 如果到达文件末尾并且没有找到下一个标识符  
//	//	// 进行相应处理 
//	//	else if (ifile_data.eof()) {
//	//		throw std::runtime_error("未找到更多的标识符");
//	//		break;
//	//	}
//	//}
//
//
//	ifile_data.close();
//	return *rootBlock; // 返回当前块  
//}
//
//
//nb_NC_block& file_manager::DeserializeBlock(std::ifstream& ifile)
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
//
//nc_block file_manager::Recover_block()
//{
//	nc_block* a = new nc_block(Deserialize());
//
//	nc_block shunxu(Process_K(0));
//	if (a->block->Block_type_index != BH_PROCESS_K)
//	{
//		shunxu << *a;
//		return shunxu;
//	}
//	else
//	{
//		return *a;
//
//	}
//}
//
//bool file_manager::goto_prog_head()
//{
//	if (ifile_data_menu.is_open())
//	{
//		ifile_data_menu.close();
//		ifile_data_menu.open("serialized_data_menu.bin", std::ios::binary);
//	}
//	if (ifile_data.is_open())
//	{
//		ifile_data.close();
//		ifile_data.open("serialized_data.bin", std::ios::binary);
//	}
//	int Name = start_prog_name;
//	//std::ifstream ifile("serialized_data_menu.bin", std::ios::binary);
//if (!ifile_data_menu.is_open()) {
//	throw std::runtime_error("文件打开失败");
//}
//
//	while (true) {
//		int name = 0;
//		std::streampos startSize = 0, endSize = 0;
//		// 读取 name (int 类型)  
//		ifile_data_menu.read(reinterpret_cast<char*>(&name), sizeof(name));
//		if (ifile_data_menu.eof()) {
//			std::cout << "读取已完成，文件末尾已到达。" << std::endl; // 提示读取已完成  
//			break; // 到达文件末尾，退出循环  
//		}
//		if (ifile_data_menu.fail()) {
//			ifile_data_menu.close();
//			throw std::runtime_error("读取 name 失败");
//		}
//
//		// 读取 fileSize Start (std::streamsize 类型)  
//		ifile_data_menu.read(reinterpret_cast<char*>(&startSize), sizeof(startSize));
//		if (ifile_data_menu.fail()) {
//			ifile_data_menu.close();
//			throw std::runtime_error("读取 fileSize Start 失败");
//		}
//
//		// 读取 fileSize End (std::streamsize 类型)  
//		ifile_data_menu.read(reinterpret_cast<char*>(&endSize), sizeof(endSize));
//		if (ifile_data_menu.fail()) {
//			ifile_data_menu.close();
//			throw std::runtime_error("读取 fileSize End 失败");
//		}
//		if (name == Name)
//		{
//			nb_NC_block::position = startSize;
//			break;
//
//		}
//	}
//	return true;
//}
//
////bool file_manager::data_clear()
////{
////	std::ifstream ifile("serialized_data_menu.bin", std::ios::binary);
////	if (!ifile.is_open()) {
////		throw std::runtime_error("文件打开失败");
////	}
////	while (true) {
////		int name = 0;
////		std::streampos startSize = 0, endSize = 0;
////		// 读取 name (int 类型)  
////		ifile.read(reinterpret_cast<char*>(&name), sizeof(name));
////		if (ifile.eof()) {
////			std::cout << "读取已完成，文件末尾已到达。" << std::endl; // 提示读取已完成  
////			break; // 到达文件末尾，退出循环  
////		}
////		if (ifile.fail()) {
////			ifile.close();
////			throw std::runtime_error("读取 name 失败");
////		}
////
////		// 读取 fileSize Start (std::streamsize 类型)  
////		ifile.read(reinterpret_cast<char*>(&startSize), sizeof(startSize));
////		if (ifile.fail()) {
////			ifile.close();
////			throw std::runtime_error("读取 fileSize Start 失败");
////		}
////
////		// 读取 fileSize End (std::streamsize 类型)  
////		ifile.read(reinterpret_cast<char*>(&endSize), sizeof(endSize));
////		if (ifile.fail()) {
////			ifile.close();
////			throw std::runtime_error("读取 fileSize End 失败");
////		}
////		if (name == 101)
////		{
////			std::streampos pos = ifile.tellg();
////			std::ofstream ofile1("serialized_data.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
////			if (!ofile1.is_open()) {
////				throw std::runtime_error("文件打开失败");
////			}
////			// 将文件指针移动到 startSize 的位置  
////			ofile1.seekp(startSize);
////			// 清除 startSize 之后的所有内容：通过调整文件大小实现  
////			ofile1.write("", 0); // 写入0字节以清空数据  
////			ofile1.close(); // 关闭输出流，以便后续可以用 truncate 方式处理  
////
////
////			//// 重新打开文件以进行清空操作，并将文件大小调整到 startSize  
////			std::ofstream ofile2("serialized_data_menu.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
////			if (!ofile2.is_open()) {
////				throw std::runtime_error("文件打开失败");
////			}
////			ofile2.seekp(pos); // 移动到当前指针位置，实际上此操作并没有改变位置  
////			ofile2.write("", 0); // 写入0字节以清空数据  
////			ofile2.close(); // 关闭文件  
////
////			ifile.close();
////			return true; // 操作成功  
////
////		}
////	}
////	return false; // 如果没有找到符合条件的情况，返回 false  
////
////}
//
//
//bool file_manager::data_clear()
//{
//			// 1. 截断数据文件到startSize
//			try {
//				std::filesystem::resize_file(
//					"serialized_data.bin",
//					static_cast<uintmax_t>(0)
//				);
//			}
//			catch (const std::filesystem::filesystem_error& e) {
//				throw std::runtime_error("数据文件截断失败: " + std::string(e.what()));
//			}
//
//			// 2. 截断menu文件到当前记录的起始位置
//			try {
//				std::filesystem::resize_file(
//					"serialized_data_menu.bin",
//					static_cast<uintmax_t>(0)
//				);
//			}
//			catch (const std::filesystem::filesystem_error& e) {
//				throw std::runtime_error("菜单文件截断失败: " + std::string(e.what()));
//			}
//
//			return true;
//
//}
//
//
//
//bool file_manager::Recover_nc_code(string f_p)
//{
//	//file_manager* af_manager = f_manager;
//	//std::ifstream ifile("serialized_data_menu.bin", std::ios::binary);
//
//	if (ifile_data_menu.is_open()) 
//	{
//		ifile_data_menu.close();
//	}
//
//	ifile_data_menu.open("serialized_data_menu.bin", std::ios::binary);
//
//	if (!ifile_data_menu.is_open()) {
//		throw std::runtime_error("文件打开失败");
//	}
//
//	while (true) {
//		int name = 0;
//		std::streampos startSize = 0, endSize = 0;
//		// 读取 name (int 类型)  
//		ifile_data_menu.read(reinterpret_cast<char*>(&name), sizeof(name));
//		if (ifile_data_menu.eof()) {
//			std::cout << "读取已完成，文件末尾已到达。" << std::endl; // 提示读取已完成  
//			break; // 到达文件末尾，退出循环  
//		}
//		if (ifile_data_menu.fail()) {
//			ifile_data_menu.close();
//			throw std::runtime_error("读取 name 失败");
//		}
//
//		// 读取 fileSize Start (std::streamsize 类型)  
//		ifile_data_menu.read(reinterpret_cast<char*>(&startSize), sizeof(startSize));
//		if (ifile_data_menu.fail()) {
//			ifile_data_menu.close();
//			throw std::runtime_error("读取 fileSize Start 失败");
//		}
//
//		// 读取 fileSize End (std::streamsize 类型)  
//		ifile_data_menu.read(reinterpret_cast<char*>(&endSize), sizeof(endSize));
//		if (ifile_data_menu.fail()) {
//			ifile_data_menu.close();
//			throw std::runtime_error("读取 fileSize End 失败");
//		}
//
//		string dir = f_p +"\\"+"O" + std::to_string(name);
//		std::ofstream ofile(dir, ios::trunc | ios::out);
//		ofile << "% @MACRO" << endl;
//		ofile.close();
//
//		nb_NC_block::position = startSize;
//
//		while (nb_NC_block::position < endSize)
//		{
//			nc_block* a = new nc_block(Deserialize());
//			a->block->write_nc_code();
//			ofile.open(dir, ios::app | ios::out);
//			ofile << a->block->NC_code;
//
//			if (a->block->Block_type_index == BH_M30)
//			{
//				//const std::string filePath = "serialized_data.bin";
//				//std::ifstream ifile(filePath, std::ios::binary);
//				// 定位到文件末尾并获取大小  
//				//ifile_data.seekg(endSize); // 移动到文件末尾  
//				//nb_NC_block::position = ifile_data.tellg(); // 获取当前指针位置
//				nb_NC_block::position = endSize;
//			}
//
//			a->release_block_tree();
//			ofile.close();
//		}
//
//	}
//
//	ifile_data_menu.close();
//	return true;
//
//
//}
//
//
