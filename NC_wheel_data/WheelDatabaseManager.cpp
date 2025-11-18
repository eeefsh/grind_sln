#include "pch.h"
#define NC_wheel_data_EXPORTS

#include "WheelDatabaseManager.h"
#include <ctime>
using namespace std;


namespace WheelDatabaseManager_namespace
{
	string wheel_dir;
	string group_dir;
	string wheel_flag = "skwheel";
	string group_flag = "skgroup";
}

WheelDatabaseManager::WheelDatabaseManager(std::string dir_val)
{
	WheelDatabaseManager_namespace::wheel_dir = dir_val;
	size_num = 0;
	fstream outFile(WheelDatabaseManager_namespace::wheel_dir, ios::in | ios::binary);
	if (!outFile.is_open())
	{
		creat_bin(outFile);
		return;
	}
	//校验
	string ans_char;
	ans_char.resize(WheelDatabaseManager_namespace::wheel_flag.size());
	outFile.seekg(ios::beg);
	outFile.read(ans_char.data(), WheelDatabaseManager_namespace::wheel_flag.size());
	
	if (ans_char != WheelDatabaseManager_namespace::wheel_flag)
	{
		outFile.close();
		creat_bin(outFile);
		return;
	}
	else
	{
		outFile.read(reinterpret_cast<char*>(&size_num), sizeof(size_num));
		ptr_pos = outFile.tellg();
	}
	outFile.close();
	if (outFile.fail())
	{
		cerr << "Error opening file!" << endl;
	}
}

void WheelDatabaseManager::creat_bin(std::fstream& outFile)
{
	outFile.open(WheelDatabaseManager_namespace::wheel_dir, ios::out | ios::binary);
	if (!outFile.is_open())
	{
		cerr << "Error opening file!" << endl;
	}

	//写入标记
	outFile.write(WheelDatabaseManager_namespace::wheel_flag.c_str(), WheelDatabaseManager_namespace::wheel_flag.size());
	//写入0个数
	size_t temp = 0;
	outFile.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	ptr_pos = outFile.tellg();

	outFile.close();
	if (outFile.fail())
	{
		cerr << "Error opening file!" << endl;
	}
}

bool WheelDatabaseManager::insertWheeldata(wheel_pack_data& data)
{
	streampos pos_temp;
	find_empty_wheel(pos_temp);

	fstream outFile(WheelDatabaseManager_namespace::wheel_dir, ios::in | ios::out | ios::binary);
	outFile.seekp(pos_temp);
	outFile.write(reinterpret_cast<char*>(&data), sizeof(data));
	size_num++;
	outFile.seekp(WheelDatabaseManager_namespace::wheel_flag.size());
	outFile.write(reinterpret_cast<char*>(&size_num), sizeof(size_num));

	outFile.close();
	if (outFile.fail()) {
		std::cerr << "Error modifying file!" << std::endl;
		return 0;
	}

	return 1;
}

bool WheelDatabaseManager::renewWheeldata(std::vector<wheel_pack_data>& data)
{

	fstream outFile(WheelDatabaseManager_namespace::wheel_dir, ios::out | ios::binary);
	if (!outFile.is_open())
	{
		cerr << "Error opening file!" << endl;
		return 0;
	}

	outFile.write(WheelDatabaseManager_namespace::wheel_flag.c_str(), WheelDatabaseManager_namespace::wheel_flag.size());

	size_num = data.size();
	outFile.write(reinterpret_cast<char*>(&size_num), sizeof(size_num));

	size_t temp = data.size() * sizeof(data[0]);
	outFile.write(reinterpret_cast<char*>(data.data()), temp);
	
	

	outFile.close();
	if (outFile.fail()) {
		std::cerr << "Error modifying file!" << std::endl;
		return 0;
	}

	return 1;
}

bool WheelDatabaseManager::readWheeldata(vector<wheel_pack_data>& data)
{
	fstream outFile(WheelDatabaseManager_namespace::wheel_dir, ios::in | ios::binary);
	if (!outFile.is_open())
	{
		return 0;
	}
	
	outFile.seekg(ptr_pos);
	data.resize(size_num);

	void* temp = data.data();
	size_t num = sizeof(data[0]) * size_num;

	outFile.read(reinterpret_cast<char*>(temp), num);
	outFile.close();
	if (outFile.fail()) {
		std::cerr << "Error modifying file!" << std::endl;
		return 0;
	}

	return 1;
}

size_t WheelDatabaseManager::size()
{
	return size_num;
}

void WheelDatabaseManager::find_empty_wheel(std::streampos& out)
{
	wheel_pack_data buff;
	fstream File(WheelDatabaseManager_namespace::wheel_dir, ios::in | ios::binary);
	streampos n = ptr_pos;

	while (true)
	{
		File.seekg(n);
		if (File.peek() == EOF)
		{
			out = n;
			break;
		}
		File.read(reinterpret_cast<char*>(&buff), sizeof(buff));
		if (buff.type == 0)
		{
			out = n;
			break;
		}
		n += sizeof(buff);
	}
	File.close();
}

WheelDatabaseManager_namespace::update_time::update_time()
{
	currentTime = time(nullptr);
}

void WheelDatabaseManager_namespace::update_time::get_tm(std::tm& val)
{
	localtime_s(&val, &currentTime);
}

GroupDatabaseManager::GroupDatabaseManager(std::string dir_val)
{
	WheelDatabaseManager_namespace::group_dir = dir_val;
	size_num = 0;
	fstream outFile(WheelDatabaseManager_namespace::group_dir, ios::in | ios::binary);
	if (!outFile.is_open())
	{
		creat_bin(outFile);
		return;
	}
	//校验
	string ans_char;
	ans_char.resize(WheelDatabaseManager_namespace::group_flag.size());
	outFile.seekg(ios::beg);
	outFile.read(ans_char.data(), WheelDatabaseManager_namespace::group_flag.size());

	if (ans_char != WheelDatabaseManager_namespace::group_flag)
	{
		outFile.close();
		creat_bin(outFile);
		return;
	}
	else
	{
		outFile.read(reinterpret_cast<char*>(&size_num), sizeof(size_num));
		ptr_pos = outFile.tellg();
	}
	outFile.close();
	if (outFile.fail())
	{
		cerr << "Error opening file!" << endl;
	}
}

bool GroupDatabaseManager::renewGroupdata(std::vector<group_pack_data>& data)
{

	fstream outFile(WheelDatabaseManager_namespace::group_dir, ios::out | ios::binary);
	if (!outFile.is_open())
	{
		cerr << "Error opening file!" << endl;
		return 0;
	}

	outFile.write(WheelDatabaseManager_namespace::group_flag.c_str(), WheelDatabaseManager_namespace::group_flag.size());

	size_num = data.size();
	outFile.write(reinterpret_cast<char*>(&size_num), sizeof(size_num));

	size_t temp = data.size() * sizeof(data[0]);
	outFile.write(reinterpret_cast<char*>(data.data()), temp);



	outFile.close();
	if (outFile.fail()) {
		std::cerr << "Error modifying file!" << std::endl;
		return 0;
	}

	return 1;
}

bool GroupDatabaseManager::readGroupdata(std::vector<group_pack_data>& data)
{
	fstream outFile(WheelDatabaseManager_namespace::group_dir, ios::in | ios::binary);
	if (!outFile.is_open())
	{
		return 0;
	}

	outFile.seekg(ptr_pos);
	data.resize(size_num);

	void* temp = data.data();
	size_t num = sizeof(data[0]) * size_num;

	outFile.read(reinterpret_cast<char*>(temp), num);
	outFile.close();
	if (outFile.fail()) {
		std::cerr << "Error modifying file!" << std::endl;
		return 0;
	}

	return 1;
}

size_t GroupDatabaseManager::size()
{
	return size_num;
}

void GroupDatabaseManager::creat_bin(std::fstream& outFile)
{
	outFile.open(WheelDatabaseManager_namespace::group_dir, ios::out | ios::binary);
	if (!outFile.is_open())
	{
		cerr << "Error opening file!" << endl;
	}

	//写入标记
	outFile.write(WheelDatabaseManager_namespace::group_flag.c_str(), WheelDatabaseManager_namespace::group_flag.size());
	//写入0个数
	size_t temp = 0;
	outFile.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	ptr_pos = outFile.tellg();

	outFile.close();
	if (outFile.fail())
	{
		cerr << "Error opening file!" << endl;
	}
}

std::string wheel_pack_data::get_name_wheel()
{
	return string(name_wheel);
}

std::string wheel_reference_information::get_name_wheel()
{
	return string(name_wheel);
}
