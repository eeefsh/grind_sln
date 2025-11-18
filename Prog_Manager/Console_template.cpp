// Console_template.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include"Miller_XiDao.h"

using namespace editor_line;


int main()
{
	//所有参数类都要有setcanshu函数，且形参为全部变量、后刀面可以继承一些
#pragma region 铣刀完整流程测试

	//0、存储文件的工具对象
	Storage_manager storage_tool;
	
	//1、构造制定类型铣刀
	Miller_D_ZQ* tool_1 = new Miller_D_ZQ();
	Miller_D_ZQ* tool_2 = new Miller_D_ZQ();
	tool_1->set_storage_ptr(&storage_tool);
	tool_2->set_storage_ptr(&storage_tool);
	
	//2、设置公共参数
	CanShu_ZQ_GongGong ls_GG;
	//ls_GG.set_CanShu(); //对话框获取所需所有参数
	tool_1->set_canshu_gg(ls_GG); 
	//tool_2->set_canshu_gg(ls_GG);

	//3、增加一个工序--工序参数、砂轮、速度
	//3.1 需要一个工序形参对象--工序类型设置
	//3.2 根据工序类型构造工序对象
	XingCan_Miller_GX ls_gx;
	//前刀面
	CanShu_ZQ_QDM ls_cs_qdm;
	//ls_cs_qdm.set_CanShu();//对话框获取所需所有参数
	ls_gx.set_CanShu_ZQ_QDM(ls_cs_qdm);
	tool_1->add_gx_by_end(ls_gx, 10);
	//tool_2->add_gx_by_end(ls_gx, 11);

	/*Canshu_ZQ_HDM_1 ls_hdm;
	ls_gx.set_Canshu_ZQ_HDM_1(ls_hdm);
	tool_1->add_gx_by_end(ls_gx, 123456);*/

	//{
	//	//螺旋槽
	//	Canshu_ZQ_LXC ls_cs_lxc;
	//	//ls_cs_lxc.set_CanShu();//对话框获取所需所有参数
	//	ls_gx.set_Canshu_ZQ_LXC(ls_cs_lxc);
	//	tool_1->add_gx_by_end(ls_gx,"luoxuancao");
	//	//后刀面
	//	Canshu_ZQ_HDM_1 ls_cs_hdm;
	//	ls_cs_hdm.set_CanShu();//对话框获取所需所有参数
	//	ls_gx.set_Canshu_ZQ_HDM_1(ls_cs_hdm);
	//	tool_1->add_gx_by_end(ls_gx,"houdaomian");
	//}
	{

		//4、增删查改，工序完成
		//4.1、计算所有结果
		//ls_cs_qdm.set_CanShu();//对话框获取所需所有参数
		//ls_gx.set_CanShu_ZQ_QDM(ls_cs_qdm);
		//tool->set_gx(2,ls_gx);	//更改工序

		//tool->set_gx_order(2, 0);//设置工序顺序
		//tool->del_gx(tool->get_gx_num() - 1);

		/*Miller_GX_Base* ls_get_gx = nullptr;
		tool->get_gx(0, ls_get_gx);
		int type = ls_get_gx->get_gx_type();*/

		//tool_1->Save(&save_manager,0);
	}

	int cur_pos1 = tool_1->Save();

	tool_2->Load(cur_pos1);
	
	//5、选择后续动作--仿真、NC输出

#pragma endregion



	Miller_RenXian ren_xian;
	generator_line gen_tool;
	gen_tool.set_delta_dis(0.05);
	KongJianXian k_luoxuanxian;
	KongJianXian k_duanxian;

	vec3 O = { 0,0,0 };
	double die_ang = 15;
	mat33 sys = (3, 3, fill::eye);

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
