#include "pch.h"
#include <filesystem>
#include "DataConversion.h"

namespace DataConversion_namespace
{
	namespace fs = std::filesystem;


	//文件拷贝函数
	bool copyFileToFolder(const std::string& sourcePath, const std::string& targetFolder) {
		try {
			fs::path sourceFile(sourcePath);
			fs::path targetParent(targetFolder);
			auto target = targetParent / sourceFile.filename();

			fs::create_directories(targetParent); // 如果目标文件夹不存在，递归创建
			fs::copy_file(sourceFile, target, fs::copy_options::overwrite_existing); // 复制文件

			std::cout << "文件复制成功！" << std::endl;
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "文件复制失败：" << e.what() << std::endl;
			return false;
		}
	}

	//判断文件夹内是否存在同名
	//重名返回1
	bool hasDuplicateFileName(const std::string& folderPath, const std::string& fileName)
	{
		for (const auto& entry : std::filesystem::directory_iterator(folderPath))
		{
			if (entry.is_regular_file() && entry.path().filename() == fileName)
			{
				return true;
			}
		}
		return false;
	}

	//读取记录最新编号的文件，如果文件不存在就创建一个并返回"00000000"
	//读取成功返回1；
	bool readFirstLineFromFile(const std::string& filePath, std::string& content) {
		try {
			// 检查文件夹是否存在，如果不存在则创建
			fs::path folderPath = fs::path(filePath).parent_path();
			if (!fs::exists(folderPath)) {
				fs::create_directories(folderPath);
			}

			// 打开文件以读取内容
			std::ifstream file(filePath);
			if (!file.is_open()) {
				// 文件不存在，创建并写入默认内容
				std::ofstream newFile(filePath);
				if (!newFile.is_open()) {
					std::cerr << "无法创建文件：" << filePath << std::endl;
					return false;
				}
				std::string temp = "00000000";
				newFile << "temp"; // 写入默认内容
				newFile.close();
				content = temp; // 设置引用字符串
			}
			else {
				// 读取第一行内容
				std::getline(file, content);
				file.close();
			}

			std::cout << "文件已成功读取：" << filePath << std::endl;
			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "发生异常：" << e.what() << std::endl;
			return false;
		}
	}

	//给字符串数字加1
	void incrementNumberString(std::string& numberString) {
		// 从字符串末尾开始遍历，逐位加1
		int carry = 1; // 初始进位为1
		for (int i = numberString.size() - 1; i >= 0; --i) {
			int digit = numberString[i] - '0'; // 将字符转换为数字
			int sum = digit + carry;
			numberString[i] = '0' + (sum % 10); // 更新当前位的值
			carry = sum / 10; // 计算进位
		}

		// 如果最高位有进位，添加新的位
		if (carry > 0) {
			numberString.insert(numberString.begin(), '1');
		}
	}

	//提取文件名
	void extractFileName(const std::string& filePath, std::string& fileName) {
		try {
			// 使用 std::filesystem::path 获取文件名
			fs::path path(filePath);
			fileName = path.filename().string();

		}
		catch (const std::exception& e) {
			std::cerr << "发生异常：" << e.what() << std::endl;
		}
	}
	
	//对存在的文件重新内容
	bool clearAndWriteToFile(const std::string& filePath, const std::string& content) {
		try {
			// 打开文件以清除内容
			std::ofstream file(filePath, std::ofstream::out | std::ofstream::trunc);
			if (!file.is_open()) {
				std::cerr << "无法打开文件：" << filePath << std::endl;
				return false;
			}

			// 写入新的内容
			file << content;
			file.close();

			return true;
		}
		catch (const std::exception& e) {
			std::cerr << "发生异常：" << e.what() << std::endl;
			return false;
		}
	}

}

wheel_pack_data DataConversion::wheel_to_pack(my_function::port_getData* val)
{
	vec temp;
	val->gat_data(temp);
	wheel_pack_data ans;
	ans.type = temp[0];
	if (ans.type == my_function::_DXF)
	{
		
		std::string temp_dir;
		//获得dxf文件路径
		val->gat_dir(temp_dir);
		//复制dxf文件到缓存文件夹
		DataConversion_namespace::copyFileToFolder(temp_dir, "Temp_dxf");


		std::string temp_num;
		//获取最新编号名称
		DataConversion_namespace::readFirstLineFromFile(R"(Save_dxf/Latest_number.txt)", temp_num);
		
		bool is_repeat = 1;
		do
		{
			//判断是否重名
			is_repeat = DataConversion_namespace::hasDuplicateFileName("Save_dxf", temp_num);
			if (is_repeat)
			{
				//编号加1
				DataConversion_namespace::incrementNumberString(temp_num);
			}
		} while (is_repeat);

		//获取系统需要存储dxf文件的路径
		std::string file_name;
		DataConversion_namespace::extractFileName(temp_dir, file_name);
		std::string file_dir_temp = "Temp_dxf/";
		file_dir_temp = file_dir_temp + file_name;
		
		//将文件移动到Save_dxf文件夹并用编号名字
		std::string ls_dir = "Save_dxf/";
		ls_dir = ls_dir + temp_num;
		bool aaaa = rename(file_dir_temp.c_str(), ls_dir.c_str());

		for (size_t i = 0; i < ls_dir.size(); i++)
		{
			ans.dxf_dir[i] = ls_dir.c_str()[i];
		}
		
		//重写入最新编号给记录
		DataConversion_namespace::incrementNumberString(temp_num);
		DataConversion_namespace::clearAndWriteToFile(R"(Save_dxf/Latest_number.txt)", temp_num);

		
		ans.data1 = temp[1];
		ans.data2 = temp[2];
	}
	else
	{
		ans.data1 = temp[1];
		ans.data2 = temp[2];
		ans.data3 = temp[3];
		ans.data4 = temp[4];
		ans.data5 = temp[5];
		ans.data6 = temp[6];
		ans.data7 = temp[7];
		ans.data8 = temp[8];
		ans.data9 = temp[9];
	}
	return ans;
}
