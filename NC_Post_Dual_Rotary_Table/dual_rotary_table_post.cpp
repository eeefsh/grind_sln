#include"pch.h"
#include"dual_rotary_table_post.h"



void create_dual_rotary_table_post_process(
	Para_Point_Basic& Para_Path,
	Para_State_A& Para_State_Machine,
	Para_Machine& Para_Machine,
	Para_Tools& Para_Tools,
	Para_Coord_Values& Para_Coord_Values
)
{
	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;
	mat33 GC_SYS_D = Para_Machine.get_GC_SYS_G() * Para_Path.get_G_SYS_D();
	vec3 GC_Z_D = Para_Path.get_G_SYS_D().col(2);
	vec3 GC_O_D = Para_Machine.get_GC_O_G() + Para_Machine.get_GC_SYS_G() * Para_Path.get_G_O();
	vec3 GC_N = Para_Machine.get_GC_SYS_G() * Para_Path.get_G_N();
	double A_before = Para_State_Machine.get_A_before();
	//计算A坐标
	double An = Para_Coord_Values.get_An();
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}

	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}
	Para_Coord_Values.set_An(An);

	//计算C坐标
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);
	Para_Coord_Values.set_Cn(Cn);

	//计算XYZ坐标
	//沿Y方向的AC轴偏心距向量
	vec3 JC_O2GC = tcRotZ(3, -Cn) * JC_Y * Para_Machine.get_w_c2g();
	//工件参考到工件实际的向量
	vec3 JC_GC2G = tcRotZ(3, -Cn) * tcRotX(3, -An) * Para_Machine.get_GC_O_G();
	//工件到刀具实际的向量
	vec3 JC_G2D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_D;
	//工件法向在绝对坐标系的表示
	vec3 JC_N = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_N;
	//计算刀具到刀具参考坐标系的向量
	mat33 JC_SYS_D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_SYS_D;
	vec3 JC_X_D = JC_SYS_D.col(0);
	JC_Z_D = JC_SYS_D.col(2);
	vec3 JC_D2DC = Para_Tools.get_r_sl() * JC_N - ((Para_Tools.get_d_sl()) / 2.0 - Para_Tools.get_r_sl()) * JC_X_D + Para_Tools.get_fl_sl() * JC_Z_D;
	//相加所有变量得到绝对坐标系种刀具的位置向量
	vec3 JC_O_D = JC_O2GC + JC_GC2G + JC_G2D;
	vec3 JC_O_DC = JC_O_D + JC_D2DC;
	Para_Coord_Values.set_JC_O_DC(JC_O_DC);
	Para_Coord_Values.set_JC_O_D(JC_O_D);
	Para_Coord_Values.set_JC_N(JC_N);
	Para_Coord_Values.set_JC_SYS_D(JC_SYS_D);
}

void create_dual_rotary_table_post_process(
	Para_Point_Basic& Para_Path,
	Para_State_A& Para_State_Machine,
	Para_Tools& Para_Tools,
	Para_Coord_Values& Para_Coord_Values
)
{
	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;
	Para_Machine machine;
	machine.set_GC_SYS_G(eye(3, 3));
	machine.set_GC_O_G(zeros(3));
	machine.set_w_c2g(0.0);

	//20240412wld
	mat33 GC_SYS_D = Para_Path.get_G_SYS_D();
	vec3 GC_Z_D = Para_Path.get_G_SYS_D().col(2);
	vec3 GC_O_D = Para_Path.get_G_O();
	vec3 GC_N = Para_Path.get_G_N();


	double A_before = Para_State_Machine.get_A_before();

	//计算A坐标
	double An = Para_Coord_Values.get_An();
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}
	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}
	Para_Coord_Values.set_An(An);

	//计算C坐标
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);
	Para_Coord_Values.set_Cn(Cn);

	//计算XYZ坐标
	vec3 JC_O2GC = tcRotZ(3, -Cn) * JC_Y * machine.get_w_c2g();

	//20240412 wld
	vec3 JC_GC2G = zeros(3);

	vec3 JC_G2D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_D;
	vec3 JC_N = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_N;


	mat33 JC_SYS_D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_SYS_D;
	vec3 JC_X_D = JC_SYS_D.col(0);
	JC_Z_D = JC_SYS_D.col(2);
	vec3 JC_D2DC = Para_Tools.get_r_sl() * JC_N - ((Para_Tools.get_d_sl()) / 2.0 - Para_Tools.get_r_sl()) * JC_X_D + Para_Tools.get_fl_sl() * JC_Z_D;
	
	vec3 JC_O_D = JC_O2GC + JC_GC2G + JC_G2D;
	vec3 JC_O_DC = JC_O_D + JC_D2DC;
	Para_Coord_Values.set_JC_O_DC(JC_O_DC);
	Para_Coord_Values.set_JC_O_D(JC_O_D);
	Para_Coord_Values.set_JC_SYS_D(JC_SYS_D);
}

void create_dual_rotary_table_post_process(
	Para_Point_Basic& Para_Path,
	Para_State_A& Para_State_Machine,
	Para_Coord_Values& Para_Coord_Values)
{
	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;

	Para_Machine machine;
	machine.set_GC_SYS_G(eye(3, 3));
	machine.set_GC_O_G(zeros(3));
	machine.set_w_c2g(0.0);

	Para_Tools tools;
	tools.set_d_sl(0.0);
	tools.set_fl_sl(0.0);
	tools.set_r_sl(0.0);

	mat33 GC_SYS_D = Para_Path.get_G_SYS_D();
	vec3 GC_Z_D = Para_Path.get_G_SYS_D().col(2);
	vec3 GC_O_D = Para_Path.get_G_O();
	vec3 GC_N = Para_Path.get_G_N();
	double A_before = Para_State_Machine.get_A_before();

	//计算A坐标
	double An = Para_Coord_Values.get_An();
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}
	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}
	Para_Coord_Values.set_An(An);

	//计算C坐标
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);
	Para_Coord_Values.set_Cn(Cn);

	//计算XYZ坐标
	vec3 JC_O2GC = tcRotZ(3, -Cn) * JC_Y * machine.get_w_c2g();
	vec3 JC_GC2G = tcRotZ(3, -Cn) * tcRotX(3, -An) * machine.get_GC_O_G();
	vec3 JC_G2D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_D;
	vec3 JC_N = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_N;
	mat33 JC_SYS_D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_SYS_D;
	vec3 JC_X_D = JC_SYS_D.col(0);
	JC_Z_D = JC_SYS_D.col(2);
	vec3 JC_D2DC = tools.get_r_sl() * JC_N - ((tools.get_d_sl()) / 2.0 - tools.get_r_sl()) * JC_X_D + tools.get_fl_sl() * JC_Z_D;
	
	vec3 JC_O_D = JC_O2GC + JC_GC2G + JC_G2D;
	vec3 JC_O_DC = JC_O_D + JC_D2DC;
	Para_Coord_Values.set_JC_O_DC(JC_O_DC);
	Para_Coord_Values.set_JC_O_D(JC_O_D);
	Para_Coord_Values.set_JC_N(JC_N);
	Para_Coord_Values.set_JC_SYS_D(JC_SYS_D);
}


void create_daijie_post_process(
	Para_Point_Basic& Para_Path,
	Para_State_A& Para_State_Machine,
	Para_Machine& Para_Machine,
	Para_Tools& Para_Tools,
	Para_Coord_Values& Para_Coord_Values)
{
	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;
	mat33 GC_SYS_D = Para_Machine.get_GC_SYS_G() * Para_Path.get_G_SYS_D();
	vec3 GC_Z_D = Para_Path.get_G_SYS_D().col(2);

	//20240412 wld 改
	vec3 GC_O_D = Para_Machine.get_GC_O_G() + Para_Machine.get_GC_SYS_G() * Para_Path.get_G_O();

	vec3 GC_N = Para_Machine.get_GC_SYS_G() * Para_Path.get_G_N();

	//戴杰机床A轴方向与模型相反
	double A_before = -(Para_State_Machine.get_A_before());
	double C_before = -90 -(Para_State_Machine.get_C_before()); //11.14

	//计算A坐标
	double An = Para_Coord_Values.get_An();
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}

	//while是修正，A的计算值会影响转的角度从而影响C
	//加正负的判断，取方向与Y正的夹角0-360 -- 11.4-ZY
	//double rotat_An = An;
	//if (GC_Z_D(1) < 0 )
	//{
	//	An = 180 + An;  //An的初始值被限定在-90，90 
	//}

	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}

	//计算C坐标
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);	
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);
	//while (Cn - C_before > DEG_90) 3.26 ZY 注释：AC不能同时使用
	//{
	//	Cn = Cn - DEG_180;
	//}
	//while (Cn - C_before < -DEG_90)
	//{
	//	Cn = Cn + DEG_180;
	//}

	//计算XYZ坐标
	vec3 JC_O2GC = tcRotZ(3, -Cn) * JC_Y * Para_Machine.get_w_c2g();
	vec3 JC_GC2G = tcRotZ(3, -Cn) * tcRotX(3, -An) * Para_Machine.get_GC_O_G();
	vec3 JC_G2D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_D;
	vec3 JC_N = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_N;
	mat33 JC_SYS_D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_SYS_D;
	vec3 JC_X_D = JC_SYS_D.col(0);
	JC_Z_D = JC_SYS_D.col(2);
	vec3 JC_D2DC = Para_Tools.get_r_sl() * JC_N 
		- ((Para_Tools.get_d_sl()) / 2.0 - Para_Tools.get_r_sl()) * JC_X_D 
		+ Para_Tools.get_fl_sl() * JC_Z_D;
	
	vec3 JC_O_D = JC_O2GC + JC_GC2G + JC_G2D;
	vec3 JC_O_DC = JC_O_D + JC_D2DC;
	Para_Coord_Values.set_JC_O_DC(JC_O_DC);
	Para_Coord_Values.set_JC_O_D(JC_O_D);
	Para_Coord_Values.set_JC_N(JC_N);
	Para_Coord_Values.set_JC_SYS_D(JC_SYS_D);

	//坐标变换，由于戴杰机床AC轴位置不同，所以设置
	Para_Coord_Values.set_An(-An);
	Para_Coord_Values.set_Cn(-90.0 - Cn);
}

void create_dual_rotary_table_post_process(
	vec3& G_O_in, vec3& G_N_in, mat33& G_SYS_D_in,
	mat33& GC_SYS_G_in, vec3& GC_O_G_in, double& w_c2g_in,
	double& r_sl_in, double& d_sl_in, double& fl_sl_in,
	double& A_before_in, double& C_before_in,
	vec3& JC_O_DC_out, double& An_out, double& C_out
)
{
	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;
	mat33 GC_SYS_D = GC_SYS_G_in * G_SYS_D_in;
	vec3 GC_Z_D = GC_SYS_D.col(2);
	//20240412 wld 改
	vec3 GC_O_D = GC_SYS_G_in * G_O_in + GC_O_G_in;
	vec3 GC_N = GC_SYS_G_in * G_N_in;
	double A_before = A_before_in;

	//计算A坐标
	double An = An_out;
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}
	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}
	An_out = An;

	//计算C坐标
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);
	C_out = Cn;

	//计算XYZ坐标
	//沿Y方向的AC轴偏心距向量
	vec3 JC_O2GC = tcRotZ(3, -Cn) * JC_Y * w_c2g_in;
	//工件参考到工件实际的向量
	vec3 JC_GC2G = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_G_in;
	//工件到刀具实际的向量
	vec3 JC_G2D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_D;
	//工件法向在绝对坐标系的表示
	vec3 JC_N = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_N;
	//计算刀具到刀具参考坐标系的向量
	mat33 JC_SYS_D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_SYS_D;
	vec3 JC_X_D = JC_SYS_D.col(0);
	JC_Z_D = JC_SYS_D.col(2);
	vec3 JC_D2DC = r_sl_in * JC_N - ((d_sl_in) / 2.0 - r_sl_in) * JC_X_D + fl_sl_in * JC_Z_D;
	//相加所有变量得到绝对坐标系种刀具的位置向量
	JC_O_DC_out = JC_O2GC + JC_GC2G + JC_G2D + JC_D2DC;
}

void create_daijie_post_process(
	vec3& G_O_in, vec3& G_N_in, mat33& G_SYS_D_in,
	mat33& GC_SYS_G_in, vec3& GC_O_G_in, double& w_c2g_in,
	double& r_sl_in, double& d_sl_in, double& fl_sl_in,
	double& A_before_in, double& C_before_in,
	vec3& JC_O_DC_out, double& An_out, double& C_out)
{
	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;

	mat33 GC_SYS_D = GC_SYS_G_in * G_SYS_D_in;
	vec3 GC_Z_D = GC_SYS_D.col(2);
	//20240412 wld 改
	vec3 GC_O_D = GC_SYS_G_in * G_O_in + GC_O_G_in;
	vec3 GC_N = GC_SYS_G_in * G_N_in;
	//戴杰机床A轴方向与模型相反
	double A_before = -A_before_in;

	//计算A坐标
	double An = An_out;
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}
	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}
	An_out = An;

	//计算C坐标
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);
	C_out = Cn;

	//计算XYZ坐标
	vec3 JC_O2GC = tcRotZ(3, -Cn) * JC_Y * w_c2g_in;
	vec3 JC_GC2G = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_G_in;
	vec3 JC_G2D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_D;
	vec3 JC_N = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_N;
	mat33 JC_SYS_D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_SYS_D;
	vec3 JC_X_D = JC_SYS_D.col(0);
	JC_Z_D = JC_SYS_D.col(2);
	vec3 JC_D2DC = r_sl_in * JC_N - ((d_sl_in) / 2.0 - r_sl_in) * JC_X_D + fl_sl_in * JC_Z_D;
	JC_O_DC_out = JC_O2GC + JC_GC2G + JC_G2D + JC_D2DC;

	//坐标变换，由于戴杰机床AC轴位置不同，所以设置
	An_out = -An;
	C_out = -90.0 - Cn;
}

void create_dual_rotary_table_post_process(
	vec3& G_O_in, vec3& G_N_in, mat33& G_SYS_D_in,
	double& A_before_in, double& C_before_in,
	vec3& JC_O_DC_out, double& An_out, double& C_out)
{
	mat33 GC_SYS_G_in = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };;
	vec3 GC_O_G_in = { 0.0,0.0,0.0 };
	double w_c2g_in = 0.0;
	double r_sl_in = 0.0;
	double d_sl_in = 0.0;
	double fl_sl_in = 0.0;

	const double  DEG_90 = 90.0;
	const double  DEG_180 = 180.0;
	const double  DIF_E = 0.000001;
	mat33 GC_SYS_D = GC_SYS_G_in * G_SYS_D_in;
	vec3 GC_Z_D = GC_SYS_D.col(2);
	vec3 GC_O_D = GC_SYS_G_in * G_O_in + GC_O_G_in; //20240412 wld
	vec3 GC_N = GC_SYS_G_in * G_N_in;
	double A_before = A_before_in;

	//计算A坐标
	double An = An_out;
	if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) > DIF_E)
	{
		An = DEG_90;
	}
	else if (abs(GC_Z_D(1)) < DIF_E && abs(GC_Z_D(2)) < DIF_E)
	{
		std::cout << "主轴与A轴平行" << endl;
		An = A_before;
	}
	else if (abs(GC_Z_D(1)) >= DIF_E)
	{
		An = atan((GC_Z_D(2) / GC_Z_D(1))) / datum::pi * 180.0;
	}
	while (An - A_before > DEG_90)
	{
		An = An - DEG_180;
	}
	while (An - A_before < -DEG_90)
	{
		An = An + DEG_180;
	}
	An_out = An;

	//计算C坐标
	vec3 JC_Z_D = tcRotX(3, -An) * GC_Z_D;
	vec3 JC_Y = tcY(3);
	vec3 JC_Z = tcZ(3);
	double Cn = deltaRotAngle(JC_Y, JC_Z_D, JC_Z);
	C_out = Cn;

	//计算XYZ坐标
	vec3 JC_O2GC = tcRotZ(3, -Cn) * JC_Y * w_c2g_in;
	vec3 JC_GC2G = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_G_in;
	vec3 JC_G2D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_O_D;
	vec3 JC_N = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_N;
	mat33 JC_SYS_D = tcRotZ(3, -Cn) * tcRotX(3, -An) * GC_SYS_D;
	vec3 JC_X_D = JC_SYS_D.col(0);
	JC_Z_D = JC_SYS_D.col(2);
	vec3 JC_D2DC = r_sl_in * JC_N - ((d_sl_in) / 2.0 - r_sl_in) * JC_X_D + fl_sl_in * JC_Z_D;
	JC_O_DC_out = JC_O2GC + JC_GC2G + JC_G2D + JC_D2DC;
}
