#include"pch.h"
#define Prog_Manager_EXPORTS
#include "Tool_Geo_Obj.h"
#include"manager_h/MA_010101_Read_dxf_manager.h"
#include"Tool_Base.h"


void Cal_XingXian::set_base_data(CanShu_XingXian& in_data)
{
	data_base = in_data;
	is_lastest = 0;
}


void Cal_XingXian::init_data()
{
	if (data_base.input_type == 0)//参数构造
	{
		if (data_base.type_shape == 0)
		{
			gen_xx_of_zhuimian();
		}
		else if (data_base.type_shape == 1)
		{
			gen_xx_of_qiutou();
		}
		else if (data_base.type_shape == 2)
		{
			gen_xx_of_pingdi();
		}
		else if (data_base.type_shape == 3)
		{
			gen_xx_of_yuanjiao();
		}
	}
	else
	{
		//读DXf
		string ls_xx_name;
		mat ls_line;  //点+切向 6*n
		//double acc = ptr_tool->canshu_gg.sample_tool.Sample_lenth;
		double acc = 0.001;
		storage_lib.get_dxf_xx_data(data_base.sel_dxf_pos, acc, ls_line);

		int count_p = ls_line.n_cols;
		Data_Of_Points.reset();
		Data_Of_Points = zeros(13, count_p);
		//Data_Of_Points.col(i) = ans_p;
		for (int i = 0; i < count_p; i++)
		{
			vec ls_p = ls_line.submat(0, i, 2, i);
			vec ls_t = ls_line.submat(3, i, 5, i);
			vec3 norm = tcRotZ(3, 90.0) * ls_t;
			vec3 Z_zhou = normalise(cross(ls_t, norm));
			vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
						  ls_t(0), ls_t(1), ls_t(2),
						  norm(0), norm(1), norm(2),
						  Z_zhou(0), Z_zhou(1), Z_zhou(2),
						  (double)i };

			Data_Of_Points.col(i) = ans_p;
		}
	}
	
	//
	is_lastest = 1;
	for (size_t i = 0; i < v_GL_LX.size(); i++)
	{
		v_GL_LX[i]->is_lastest = 0;
	}
	for (size_t i = 0; i < v_GL_HJ.size(); i++)
	{
		v_GL_HJ[i]->is_lastest = 0;
	}
}

void Cal_XingXian::init_data(mat line)
{
	Data_Of_Points = zeros(13, line.n_cols);
	int count = line.n_cols;
	for (int i = 0; i < count; i++)
	{
		vec ls_p = line.col(i);
		vec ls_t = zeros(3);

		if (i == count - 1)
		{
			ls_t = normalise(line.col(i ) - line.col(i -1));
		}
		else
		{
			ls_t = normalise(line.col(i+1) - line.col(i));
		}
		vec3 norm = tcRotZ(3, 90.0) * ls_t;
		vec3 Z_zhou = normalise(cross(ls_t, norm));
		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
					  ls_t(0), ls_t(1), ls_t(2),
					  norm(0), norm(1), norm(2),
					  Z_zhou(0), Z_zhou(1), Z_zhou(2),
					  (double)i }; 
		Data_Of_Points.col(i) = ans_p;
	}

	//计算长度坐标
	Data_Of_Points(12, 0) = 0.0;
	for (int i = 1; i < count; i++)
	{
		double dis = tcDistance(line.col(i), line.col(i - 1));
		Data_Of_Points(12, i) = Data_Of_Points(12, i - 1) + dis;
	}
}

void Cal_XingXian::cal_son_last_state()
{
	if (is_lastest == 0)
	{
		for (size_t i = 0; i < v_GL_LX.size(); i++)
		{
			v_GL_LX[i]->is_lastest = 0;
		}
		for (size_t i = 0; i < v_GL_HJ.size(); i++)
		{
			v_GL_HJ[i]->is_lastest = 0;
		}
	}
}

//数据访问
//返回点的数量

int Cal_XingXian::n_P()
{
	return Data_Of_Points.n_cols;
}

//返回刃线的型线长度

double Cal_XingXian::Lenth()
{
	return Data_Of_Points(12, n_P() -1);
}

vec Cal_XingXian::BG_P(int i)
{
	return Data_Of_Points.col(i).rows(0, 2);
}

mat Cal_XingXian::BG_P()
{
	return Data_Of_Points.rows(0, 2);
}

vec Cal_XingXian::BG_T(int i)
{
	return Data_Of_Points.col(i).rows(3, 5);
}

mat Cal_XingXian::BG_T()
{
	return Data_Of_Points.rows(3, 5);
}

vec Cal_XingXian::BG_N(int i)
{
	return Data_Of_Points.col(i).rows(6, 8);
}

vec Cal_XingXian::BG_Z(int i)
{
	return Data_Of_Points.col(i).rows(9, 11);
}

//返回第i个点处的柱坐标系，3阶

inline mat33 Cal_XingXian::BG_zSYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = BG_T(i);
	ans.col(1) = BG_N(i);
	ans.col(2) = BG_Z(i);

	return ans;
}

//返回第i个点处的长度坐标

double Cal_XingXian::Lenth_At_Point(int i)
{
	return Data_Of_Points(12, i) * 0.001;
}

vec Cal_XingXian::get_P_by_x(double in_x)
{
	double ls_min_x = 0.0;
	for (int i = 0; i < n_P(); i++)
	{
		vec ls_p = Data_Of_Points.col(i);
		if (ls_p(0) >= in_x)
		{
			vec ls_ans = {(double) i, ls_p(0) };
			return ls_ans;
		}
	}

	int index = n_P() - 1;
	vec ls_p = Data_Of_Points.col(index);
	vec ls_ans = { (double)index,  ls_p(0) };
	return ls_ans;
}

void Cal_XingXian::gen_xx_of_zhuimian()
{
	double delta_dis = ptr_tool->get_delta_dis();

	vec3 start_p = { 0.0, data_base.start_R_0, 0.0 };
	vec3 ls_t = tcRotZ(3, data_base.ang_zhui) * tcX(3);
	vec3 norm = tcRotZ(3, 90.0) * ls_t;
	vec3 Z_zhou = normalise(cross(ls_t, norm));
	int count_p = data_base.len_0 / delta_dis;
	Data_Of_Points.reset();
	Data_Of_Points = zeros(13, count_p);
	//Data_Of_Points.col(i) = ans_p;
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = start_p + i * ls_t * delta_dis;
		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.col(i) = ans_p;
	}
}

void Cal_XingXian::gen_xx_of_qiutou()
{
	double delta_dis = ptr_tool->get_delta_dis();
	//球头部分
	vec3 start_o = { -data_base.start_R_1, 0.0, 0.0 };
	double delta_ang = tcDegree(delta_dis / data_base.start_R_1);
	int count_p0 = 90.0 / delta_ang;

	for (int i = 0; i < count_p0; i++)
	{
		vec ls_p = tcRotZ(3, -(i * delta_ang)) * start_o;

		vec3 ls_t = tcRotZ(3, -(i * delta_ang)) * tcY(3);
		vec3 norm = tcRotZ(3, 90.0) * ls_t;
		vec3 Z_zhou = normalise(cross(ls_t, norm));


		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);

	}

	//锥面部分
	vec3 start_p = { 0.0, data_base.start_R_1, 0.0 };
	vec3 ls_t = tcRotZ(3, data_base.ang_zhui) * tcX(3);
	vec3 norm = tcRotZ(3, 90.0) * ls_t;
	vec3 Z_zhou = normalise(cross(ls_t, norm));
	int count_p = data_base.len_1 / delta_dis;
	for (int i = 0; i <= count_p; i++)
	{
		vec ls_p = start_p + i * ls_t * delta_dis;
		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
	}
}

void Cal_XingXian::gen_xx_of_pingdi()
{
	double delta_dis = ptr_tool->get_delta_dis();
	//端刃部分
	double delta_h = data_base.start_R_2 * tan(tcRadians(data_base.ang_die_2));
	vec3 start_p = { delta_h, 0.0, 0.0 };
	vec3 end_p = { 0.0,data_base.start_R_2 ,0.0 };
	vec3 start_t = tcRotZ(3, data_base.ang_die_2) * tcY(3);
	double dis = tcDistance(start_p, end_p);
	int count_p0 = dis / delta_dis;
	for (int i = 0; i < count_p0; i++)
	{
		vec ls_p = start_p + start_t * i * delta_dis;

		vec3 ls_t = start_t;
		vec3 norm = tcRotZ(3, 90.0) * ls_t;
		vec3 Z_zhou = normalise(cross(ls_t, norm));

		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);

	}

	//锥面部分
	start_p = { 0.0, data_base.start_R_2, 0.0 };
	vec3 ls_t = tcRotZ(3, data_base.ang_zhui) * tcX(3);
	vec3 norm = tcRotZ(3, 90.0) * ls_t;
	vec3 Z_zhou = normalise(cross(ls_t, norm));
	int count_p = data_base.len_2 / delta_dis;
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = start_p + i * ls_t * delta_dis;
		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
	}
}

void Cal_XingXian::gen_xx_of_yuanjiao()
{
	double delta_dis = ptr_tool->get_delta_dis();
	//端刃部分
	double delta_h = data_base.start_R_3 * tan(tcRadians(data_base.ang_die_3));

	vec3 start_p = { delta_h, 0.0, 0.0 };
	//端刃终点
	vec3 ls_op = { -data_base.yuanjiao_R_3,0.0,0.0 };
	ls_op = tcRotZ(3, data_base.ang_die_3) * ls_op;
	vec3 ls_move = { delta_h ,data_base.start_R_3 ,0.0 };
	vec3 end_p = ls_op + ls_move; //平移

	vec3 start_t = normalise(end_p - start_p);
	double dis = tcDistance(start_p, end_p);

	int count_p0 = dis / delta_dis;
	for (int i = 0; i < count_p0; i++)
	{
		vec ls_p = start_p + start_t * i * delta_dis;

		vec3 ls_t = start_t;
		vec3 norm = tcRotZ(3, 90.0) * ls_t;
		vec3 Z_zhou = normalise(cross(ls_t, norm));

		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);

	}

	//圆角部分
	double delta_ang = tcDegree(delta_dis / data_base.yuanjiao_R_3);
	int count_r = (data_base.ang_die_3 + 90.0 - data_base.ang_zhui) / delta_dis;
	vec3 end_p_r = ls_op;
	for (int i = 0; i < count_r; i++)
	{
		vec3 ls_p = tcRotZ(3, -(i * delta_ang)) * ls_op + ls_move;
		end_p_r = ls_p;

		vec3 ls_t = normalise(cross(ls_p, tcZ(3)));
		vec3 norm = tcRotZ(3, 90.0) * ls_t;
		vec3 Z_zhou = normalise(cross(ls_t, norm));

		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);

	}

	//锥面部分
	start_p = end_p_r;
	vec3 ls_t = tcRotZ(3, data_base.ang_zhui) * tcX(3);
	vec3 norm = tcRotZ(3, 90.0) * ls_t;
	vec3 Z_zhou = normalise(cross(ls_t, norm));
	int count_p = data_base.len_2 / delta_dis;
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = start_p + i * ls_t * delta_dis;
		vec ans_p = { ls_p(0), ls_p(1), ls_p(2),
			ls_t(0), ls_t(1), ls_t(2),
			norm(0), norm(1), norm(2),
			Z_zhou(0), Z_zhou(1), Z_zhou(2),
			(double)i };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
	}
}

void Cal_XingXian::Range(double in_start, double in_end)
{
	int count_p = n_P();

#pragma region 确定起点和终点
	double len_all = Lenth_At_Point(count_p - 1); //25.11.11

	//将型线长度的范围转化为编号的范围
	double a, b;
	//a = in_start / 100.0 * (double)count_p;
	//b = in_end / 100.0 * (double)count_p;
	a = in_start / 100.0 * len_all;
	b = in_end / 100.0 * len_all;
	//记录与start和end对应的编号值的位置，存于c，d
	int c = 0, d = 0;
	//寻找起点
	for (int i = 0; i < count_p; i++)
	{
		//如果型线编号符合要求则存于c中，并且d变为1，不再计算
		if (Lenth_At_Point(i) >= a) //取长度坐标判断
		{
			c = i;
			break;
		}
		if (Lenth_At_Point(i) == count_p - 1)
		{
			throw - 1;//没找到起点
		}
	}
	//寻找终点
	for (int i = 0; i < count_p - c - 1; i++)
	{

		if (Lenth_At_Point(count_p - i - 1) <= b)
		{
			d = count_p - i - 1;
			break;
		}
		//如果到了最后一个点，最后一个点为终点
		if (i == count_p - c - 1)
		{
			throw - 1;//没有找到终点
		}
	}
#pragma endregion 

#pragma region 修改点数据矩阵
	//跟新点数据矩阵
	Data_Of_Points = Data_Of_Points.cols(c, d);
#pragma endregion
}

void Cal_XingXian::Sample(double in_len, double in_ang)
{
#pragma region 抽样数据
	//计算角度条件的cos值
	double cosjiaodu;
	cosjiaodu = cos(in_ang / 180.0 * datum::pi);

	//建立辅助变量
	int ChouYangStart = 0, ChouYangEnd = 0;
	vec lsSampleVector_N1;
	vec lsSampleVector_N2;
	double changdu1 = 0.0;
	double changdu2 = 0.0;

	//用于临时存放抽样数据
	mat B = Data_Of_Points;
	//抽样结果坐标
	int j = 0;

	int count_p = n_P();
	//对点数据矩阵进行抽样
	for (int i = 0; i < count_p; i++)
	{
		//记录上一个抽样点的长度坐标
		changdu1 = Lenth_At_Point(ChouYangStart);
		//记录当前点的长度坐标
		changdu2 = Lenth_At_Point(i);

		//记录上一个抽样点的切向
		lsSampleVector_N1 = BG_T(ChouYangStart);
		//记录当前点的切向
		lsSampleVector_N2 = BG_T(i);

		//如果为第一个点或最后一个点 抽样
		if (i == 0 || i == count_p - 1)
		{
			B.col(j) = Data_Of_Points.col(i);
			ChouYangStart = i;
			++j;
		}
		else
		{
			//若长度达到抽样条件，抽样
			if (abs(changdu2 - changdu1) >= in_len)
			{
				B.col(j) = Data_Of_Points.col(i);
				ChouYangStart = i;
				++j;
			}
			//若角度达到抽样条件，抽样
			else if (dot(lsSampleVector_N1, lsSampleVector_N2) <= cosjiaodu)
			{
				B.col(j) = Data_Of_Points.col(i);
				ChouYangStart = i;
				++j;
			}
		}
	}
	//复位型线矩阵
	Data_Of_Points.reset();
	//更新数据矩阵
	Data_Of_Points = B.cols(0, j - 1);
	//更新点的数量
	//d_n_P = (int)Data_Of_Points.n_rows;
	//长度和长度坐标不变
#pragma endregion
}

int Cal_XingXian::save(int pos)
{
	//storage_lib.Storage_base::renew_a_row_data(26, pos, (char*)&data_base, sizeof(data_base));
	return pos;
}

void Cal_XingXian::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_xx_canshu, pos, (char*)&data_base, sizeof(data_base));
}

void Cal_XingXian::init_guanxi()
{
	//没有上级关系
}



////初始化按照精度读取dxf文件为点集数据
//void Cal_XingXian::init_data_by_dxf_file(string in_file, double in_dis, double in_ang)
//{
//	lenth = in_dis;
//	line_manager ls_read_tool(in_file);
//	vector<vec> ans_ponts;
//
//	ls_read_tool.get_integral_point(in_dis, in_ang, ans_ponts);
//
//	ans_vv_to_mat(ans_ponts);
//}
//
//void Cal_XingXian::init_data_by_dxf_file(string in_file, double in_dis)
//{
//	lenth = in_dis;
//	//string in_file2 =  ".dxf";
//	in_file = "dxf_copy\\" + in_file;
//	line_manager ls_read_tool(in_file);
//	vector<vec> ans_ponts;
//
//	ls_read_tool.get_discrete_point(in_dis, ans_ponts);
//
//	ans_vv_to_mat(ans_ponts);
//}
//
//void Cal_XingXian::rotate(mat33 SYS)
//{
//	int length = Data_Of_Points.n_cols;
//	for (int i = 0; i < length; i++)
//	{
//		vec3 ls_p = Data_Of_Points.submat(0, i, 2, i);
//		vec ls_t = Data_Of_Points.submat(3, i, 5, i); //取出为9*1
//		double ls_len = Data_Of_Points(6, i);
//
//		ls_p = SYS * ls_p;
//		ls_t = SYS * ls_t;
//
//		vec ls_ans = { ls_p(0),ls_p(1),ls_p(2),
//			ls_t(0),ls_t(1),ls_t(2),
//			ls_len };
//		Data_Of_Points.col(i) = ls_ans;
//	}
//}
//
////抽样(只能操作一次) 长度条件，角度条件
//
//void Cal_XingXian::Sample(double changdu, double jiaodu)
//{
//#pragma region 抽样数据
//	//计算角度条件的cos值
//	double cosjiaodu;
//	cosjiaodu = cos(jiaodu / 180.0 * datum::pi);
//
//	//建立辅助变量
//	int ChouYangStart = 0, ChouYangEnd = 0;
//	vec lsSampleVector_N1;
//	vec lsSampleVector_N2;
//	double changdu1 = 0.0;
//	double changdu2 = 0.0;
//
//	//用于临时存放抽样数据
//	mat B = Data_Of_Points;
//	//抽样结果坐标
//	int j = 0;
//
//	//对点数据矩阵进行抽样
//	for (int i = 0; i < Data_Of_Points.n_cols; i++)
//	{
//		//记录上一个抽样点的长度坐标
//		changdu1 = Lenth_At_Point(ChouYangStart);
//		//记录当前点的长度坐标
//		changdu2 = Lenth_At_Point(i);
//
//		//记录上一个抽样点的切向
//		lsSampleVector_N1 = BG_T(3, ChouYangStart);
//		//记录当前点的切向
//		lsSampleVector_N2 = BG_T(3, i);
//
//		//如果为第一个点或最后一个点 抽样
//		if (i == 0 || i == Data_Of_Points.n_cols - 1)
//		{
//			B.col(j) = Data_Of_Points.col(i);
//			ChouYangStart = i;
//			++j;
//		}
//		else
//		{
//			//若长度达到抽样条件，抽样
//			if (abs(changdu2 - changdu1) >= changdu)
//			{
//				B.col(j) = Data_Of_Points.col(i);
//				ChouYangStart = i;
//				++j;
//			}
//			//若角度达到抽样条件，抽样
//			else if (dot(lsSampleVector_N1, lsSampleVector_N2) <= cosjiaodu)
//			{
//				B.col(j) = Data_Of_Points.col(i);
//				ChouYangStart = i;
//				++j;
//			}
//		}
//	}
//	//复位型线矩阵
//	Data_Of_Points.reset();
//	//更新数据矩阵
//	Data_Of_Points = B.cols(0, j - 1);
//	//更新点的数量
//	//d_n_P = (int)Data_Of_Points.n_rows;
//	//长度和长度坐标不变
//#pragma endregion
//}
//
////起始百分比选择范围 抽样后不能选范围 [0,1]
//
//void Cal_XingXian::Range(double in_strat, double in_end)
//{
//	int count_p = Data_Of_Points.n_cols;
//	int start_index = count_p * in_strat;
//	int end_index = count_p * in_end;
//
//	//切掉两头
//	Data_Of_Points.shed_cols(end_index - 1, count_p - 1);
//	Data_Of_Points.shed_rows(0, start_index);
//}
//
////径向偏置-增大回转半径
//
//void Cal_XingXian::PianZhi_R(double in_R)
//{
//	for (int i = 0; i < Data_Of_Points.n_cols; i++)
//	{
//		Data_Of_Points.col(i).row(0) = Data_Of_Points.col(i).row(0) + in_R;
//	}
//}
//
////在某个长度位置插入一个点,返回这个点的位置
//
//int Cal_XingXian::insert_point_at_lenth(double pos)
//{
//	if (pos > Lenth() || pos < 0.0)
//	{
//		//输入值超出限制
//		return -1;
//	}
//	for (int i = 0; i < Data_Of_Points.n_cols; ++i)
//	{
//		//找到刚好在这个位置的点 3.3 不能直接比较
//		if (abs(Lenth_At_Point(i) - pos) < 0.00001)
//		{
//			//维持原来的不变，不进行任何操作
//			return i;
//		}
//		//第一次超过pos
//		else if (Lenth_At_Point(i) > pos)
//		{
//			//需要插入一个点，并更新相关数据
//			//在第i个点前面插入一个全部为0的行
//			Data_Of_Points.insert_rows(i, 1, true);
//			//将新插入的位置的长度坐标设置为输入值
//			set_Lenth_At_Point(i, pos);
//			//新插入点的切向等于原来那个点的切向
//			Data_Of_Points.submat(i, 3, i, 5) = Data_Of_Points.submat(i + 1, 3, i + 1, 5);
//			//新插入点的坐标为:原来点的坐标-长度距离*原来的切向
//			Data_Of_Points.submat(i, 0, i, 2) = Data_Of_Points.submat(i + 1, 0, i + 1, 2) - (Lenth_At_Point(i + 1) - Lenth_At_Point(i)) * Data_Of_Points.submat(i + 1, 3, i + 1, 5);
//			//更新点的数量
//			//d_n_P++;
//			return i;
//		}
//		else
//		{
//			return -1;
//		}
//	}
//}
//
////起点延长
//
//void Cal_XingXian::extend_at_start(double lenth)
//{
//	Data_Of_Points.submat(0, 0, 2, 0) = Data_Of_Points.submat(0, 0, 2, 0) - lenth * Data_Of_Points.submat(3, 0, 5, 0);
//	set_Lenth_At_Point(0, -lenth);
//	for (int i = 0; i < Data_Of_Points.n_cols; i++)
//	{
//		set_Lenth_At_Point(i, Lenth_At_Point(i) + lenth);
//	}
//}
//
////终点延长
//
//void Cal_XingXian::extend_at_end(double lenth)
//{
//	int count_p = Data_Of_Points.n_cols;
//	Data_Of_Points.submat(0, count_p - 1, 2, count_p - 1) = Data_Of_Points.submat(0, count_p - 1, 2, count_p - 1) - lenth * Data_Of_Points.submat(3, count_p - 1, 5, count_p - 1);
//	set_Lenth_At_Point(0, -lenth);
//}
//
////设置第i个点的坐标
//
//void Cal_XingXian::set_P(int i, vec P_in)
//{
//	Data_Of_Points.submat(0, i, 2, i) = P_in;
//}
//
////设置第i个点的切向
//
//void Cal_XingXian::set_T(int i, vec T_in)
//{
//	Data_Of_Points.submat(3, i, 5, i) = T_in;
//}
//
////设置第i个点的长度坐标
//
//void Cal_XingXian::set_Lenth_At_Point(int i, double lenth_pos)
//{
//	Data_Of_Points(6, i) = lenth_pos;
//}

Cal_XingXian::Cal_XingXian()
{
	ptr_tool = nullptr;

	Data_Of_Points.reset();
	Data_Of_Points.reshape(13, 0);

	v_GL_LX.clear();
	v_GL_HJ.clear();
}

Cal_XingXian::~Cal_XingXian()
{
}

Cal_XingXian::Cal_XingXian(Tool_Base* in_ptr, CanShu_XingXian& in_data)
{
	ptr_tool = in_ptr;
	set_base_data(in_data);

	Data_Of_Points.reset();
	Data_Of_Points(13, 0);

	v_GL_LX.clear();
	v_GL_HJ.clear();
}

//将读取的dxf点转为mat

//void Cal_XingXian::ans_vv_to_mat(vector<vec>& points)
//{
//	Data_Of_Points.clear();
//	int count_p = points.size();
//	for (int i = 0; i < count_p; i++)
//	{
//		vec ls_data = points[i];
//		vec ls_t = { ls_data(0), ls_data(1), ls_data(2) };
//		vec ls_p = { ls_data(3),ls_data(4),ls_data(5) };
//		//dxf的x 转为Z为长度方向
//		ls_t = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_t;
//		ls_p = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_p;
//
//		vec ans_p = { ls_p(0), ls_p(1), ls_p(2), ls_t(0), ls_t(1), ls_t(2), i * lenth };
//
//		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
//	}
//}

inline void Cal_LouXuan::set_base_data(CanShu_LuoXuan& in_data)
{
	data_base = in_data;
	is_lastest = 0;
}

double Cal_LouXuan::get_zhi_or_xie_ang_qian()
{
	//直槽
	if (data_base.type_cao == 0 )
	{
		double ang_qian = 0.0;
		double ang_xie = 0.0;
		//1-计算前角
		double start_R = data_base.R_zhi_or_xie;
		vec start_p = { 0.0,start_R,0.0 };

		//前角
		if (data_base.type_zhi == 0)
		{
			ang_qian = data_base.zhi_ang_qian;
		}
		//偏心距
		else
		{
			ang_qian = tcDegree(atan(data_base.zhi_pianxin / start_R));
		}

		return ang_qian;
	}
	else if (data_base.type_cao == 1) //斜槽
	{
		double ang_qian = 0.0;
		double ang_xie = 0.0;
		//1-计算前角
		double start_R = data_base.R_zhi_or_xie;
		vec start_p = { 0.0,start_R,0.0 };

		//前角
		if (data_base.type_xie == 0)
		{
			ang_qian = data_base.xie_ang_qian;
		}
		//偏心距
		else
		{
			ang_qian = tcDegree(atan(data_base.xie_pianxin / start_R));
		}

		return ang_qian;
	}
	else 
	{
		return -999.0;
	}
}

void Cal_LouXuan::init_data()
{

	if (is_lastest == 0)
	{
		
	}
	else
	{
		return;
	}

	if (data_base.guanlian_xx_id == -1)
	{
		error_message_global = -1;
		return;
	}

	

	//1 设置向前关联-需要相应的表
	ptr_xx = ptr_tool->ptr_list_xx->get_obj(data_base.guanlian_xx_id);
	//ptr_fd = ptr_tool->ptr_list_fd->get_a_cal_data(data_base.fendu_id);

	//ptr_xx->add_son(this);
	//ptr_fd->add_son(this); 8.7 注释

	//2 计算主数据
	if (data_base.type_cao == 0 ) //直槽
	{
		double ang_qian = 0.0;
		double ang_xie = 0.0;
		//1-计算前角
		double start_R = data_base.R_zhi_or_xie;
		vec start_p = { 0.0,start_R,0.0 };

		//前角
		if (data_base.type_zhi == 0) 
		{
			ang_qian = data_base.zhi_ang_qian;
		}
		//偏心距
		else
		{
			ang_qian = tcDegree(atan(data_base.zhi_pianxin / start_R));
		}

		//2-斜角
		ang_xie = 0.0;

		//3-型线点与槽面交点
		mat vp ; //3*n
		cal_zhicao_vp(start_p, ang_qian, ang_xie, vp);

		//4
		cal_main_data_by_points(vp, ang_qian);
	}
	else if (data_base.type_cao == 1) //斜槽
	{
		double ang_qian = 0.0;
		double ang_xie = 0.0;
		//1-计算前角
		double start_R = data_base.R_zhi_or_xie;
		vec start_p = { 0.0,start_R,0.0 };

		//前角
		if (data_base.type_xie == 0) 
		{
			ang_qian = data_base.xie_ang_qian;
		}
		//偏心距
		else
		{
			ang_qian = tcDegree(atan(data_base.xie_pianxin / start_R));
		}
		//2-斜角
		ang_xie = data_base.ang_xie;

		//3-型线点与槽面交点
		mat vp; //3*n
		cal_zhicao_vp(start_p, ang_qian, ang_xie, vp);

		//4-
		cal_main_data_by_points(vp, ang_qian);
	}
	else
	{
		vec daocheng_v(ptr_xx->n_P(), fill::zeros);
		mat ans_point(3, ptr_xx->n_P(), fill::zeros);
		//等导程
		if (data_base.type_luo == 0)
		{
			//1-计算所有点处的导程
			daocheng_v = cal_daocheng_v_by_dengdaocheng();
		}
		//等螺旋角
		else if (data_base.type_luo == 1)
		{
			//1-计算所有点处的导程
			daocheng_v = cal_daocheng_v_by_dengluoxuanjiao();
		}
		//变导程
		else if (data_base.type_luo == 2)
		{
			//1-计算所有点处的导程
			daocheng_v = cal_daocheng_v_by_biandaocheng();
		}
		//变螺旋角
		else if (data_base.type_luo == 3)
		{
			//1.1-计算所有点处的螺旋角
			vec luoxuanjiao_v(ptr_xx->n_P(), fill::zeros);
			luoxuanjiao_v = cal_luoxuanjiao_v_by_bianluoxuan();

			//1-计算所有点处的导程
			daocheng_v = cal_daocheng_v_by_luoxuanjiao_v(luoxuanjiao_v);
		}

		//2-计算全部点
		ans_point = cal_points_by_daocheng_v(daocheng_v);

		//3-计算所有数据
		cal_main_data_by_points(ans_point, data_base.ang_r);
	}
	
	//
	is_lastest = 1;
	for (size_t i = 0; i < v_GL_GX.size(); i++)
	{
		v_GL_GX[i]->is_lastest = 0;
	}
}

void Cal_LouXuan::init_guanxi()
{
	int xx_show_index = ptr_tool->ptr_list_xx->base_data.get_show_index_by_id(data_base.guanlian_xx_id);
	int fd_show_index = ptr_tool->ptr_list_fd->base_data.get_show_index_by_id(data_base.guanlian_fd_id);

	ptr_xx = ptr_tool->ptr_list_xx->get_obj(xx_show_index);
	ptr_fd = ptr_tool->ptr_list_fd->get_obj(fd_show_index);

	ptr_xx->add_guanxi_GL_LX(this);
	ptr_fd->add_guanxi_GL_LX(this);
}


bool Cal_LouXuan::is_del_ok()
{
	if (v_GL_GX.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cal_LouXuan::cal_son_last_state()
{
	if (is_lastest == 0)
	{
		for (size_t i = 0; i < v_GL_GX.size(); i++)
		{
			v_GL_GX[i]->is_lastest = 0;
		}
	}
}


//转角+倾角 - 构造定长度-平槽面

void Cal_LouXuan::init_data_by_zhuan_qing(double in_zhuan, double in_qing)
{
	//平面方向都相同，每个点坐标不同
	//vec3 ans_fx = tcRotZ(3, -in_zhuan) * (-tcX(3));
	//vec3 start_p = { start_point_R, 0.0, 0.0 };
	//vec3 end_p = { start_point_R, 0.0, end_point_len };
	//end_p = end_p * tcRotX(3, -in_qing);

	//double dis_s_e = tcDistance(start_p, end_p);
	//vec3 ls_t = normalise(end_p - start_p);

	//int count_p = dis_s_e / 0.001;
	//Data_Of_Points.clear();
	//for (int i = 0; i <= count_p; i++)
	//{
	//	vec ls_p = start_p + i * ls_t * 0.001;
	//	vec ans_p = { ls_p(0), ls_p(1), ls_p(2), ans_fx(0), ans_fx(1), ans_fx(2) };

	//	Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
	//}

}

//偏心距+倾角 - 构造定长度-平槽面

void Cal_LouXuan::init_data_by_pianxin_qing(double in_pian, double in_qing)
{
	vec ls_start_p = ptr_xx->BG_P(0);
	double start_point_R = norm(ls_start_p);
	double end_point_len = ptr_xx->Lenth();

	//根据偏心距及圆半径，计算出转角，后续计算复用
	double cal_zhuan = asin(in_pian / start_point_R);

	vec3 ans_fx = tcRotZ(3, -cal_zhuan) * (-tcX(3));
	vec3 start_p = { start_point_R, 0.0, 0.0 };
	vec3 end_p = { start_point_R, 0.0, end_point_len };
	end_p = end_p * tcRotX(3, -in_qing);

	double dis_s_e = tcDistance(start_p, end_p);
	vec3 ls_t = normalise(end_p - start_p);

	int count_p = dis_s_e / 0.001;
	Data_Of_Points.clear();
	for (int i = 0; i <= count_p; i++)
	{
		vec ls_p = start_p + i * ls_t * 0.001;
		vec ans_p = { ls_p(0), ls_p(1), ls_p(2), ans_fx(0), ans_fx(1), ans_fx(2) };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
	}
}

//螺旋角 - 构造定长度-直纹槽面

void Cal_LouXuan::init_data_by_luoxuan(double in_luo)
{
	vec start_p = ptr_xx->BG_P(0);
	double start_point_R = norm(start_p);
	//方向：指向回转轴
	mat ans_p;
	//gen_luoxuanxian(in_luo, start_point_R, ans_p);

	int count_p = ans_p.n_cols;
	for (int i = 0; i < count_p; i++)
	{
		vec3 ls_p = ans_p.col(i);
		vec3 ans_fx = normalise(-ls_p);
		vec ans_data = { ls_p(0), ls_p(1), ls_p(2), ans_fx(0), ans_fx(1), ans_fx(2) };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
	}

}

//导程 - 构造定长度-直纹槽面

void Cal_LouXuan::init_data_by_daocheng(double in_daocheng)
{
	vec start_p = ptr_xx->BG_P(0);
	double start_point_R = norm(start_p);
	//导程转化为螺旋角计算
	double cal_luo = atan((2.0 * start_point_R * datum::pi) / in_daocheng);

	mat ans_p;
	//gen_luoxuanxian(cal_luo, start_point_R, ans_p);

	int count_p = ans_p.n_cols;
	for (int i = 0; i < count_p; i++)
	{
		vec3 ls_p = ans_p.col(i);
		vec3 ans_fx = normalise(-ls_p);
		vec ans_data = { ls_p(0), ls_p(1), ls_p(2), ans_fx(0), ans_fx(1), ans_fx(2) };

		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
	}
}

void Cal_LouXuan::Range(double in_start, double in_end)
{
	int count_p = n_P();

#pragma region 确定起点和终点
	double len_all = Lenth_At_Point(count_p - 1); //25.11.11

	//将型线长度的范围转化为编号的范围
	double a, b;
	//a = in_start / 100.0 * (double)count_p;
	//b = in_end / 100.0 * (double)count_p;
	a = in_start / 100.0 * len_all;
	b = in_end / 100.0 * len_all;
	//记录与start和end对应的编号值的位置，存于c，d
	int c = 0, d = 0;
	//寻找起点
	for (int i = 0; i < count_p; i++)
	{
		//如果型线编号符合要求则存于c中，并且d变为1，不再计算
		if (Lenth_At_Point(i) >= a) //取长度坐标判断
		{
			c = i;
			break;
		}
		if (Lenth_At_Point(i) == count_p - 1)
		{
			throw - 1;//没找到起点
		}
	}
	//寻找终点
	for (int i = 0; i < count_p - c - 1; i++)
	{

		if (Lenth_At_Point(count_p - i - 1) <= b)
		{
			d = count_p - i - 1;
			break;
		}
		//如果到了最后一个点，最后一个点为终点
		if (i == count_p - c - 1)
		{
			throw - 1;//没有找到终点
		}
	}
#pragma endregion 

#pragma region 修改点数据矩阵
	//跟新点数据矩阵
	Data_Of_Points = Data_Of_Points.cols(c, d);
#pragma endregion
}

void Cal_LouXuan::Sample(double in_len, double in_ang)
{
#pragma region 抽样数据
	//计算角度条件的cos值
	double cosjiaodu;
	cosjiaodu = cos(in_ang / 180.0 * datum::pi);

	//建立辅助变量
	int ChouYangStart = 0, ChouYangEnd = 0;
	vec lsSampleVector_N1;
	vec lsSampleVector_N2;
	double changdu1 = 0.0;
	double changdu2 = 0.0;

	//用于临时存放抽样数据
	mat B = Data_Of_Points;
	//抽样结果坐标
	int j = 0;

	int count_p = n_P();
	//对点数据矩阵进行抽样
	for (int i = 0; i < count_p; i++)
	{
		//记录上一个抽样点的长度坐标
		changdu1 = Lenth_At_Point(ChouYangStart);
		//记录当前点的长度坐标
		changdu2 = Lenth_At_Point(i);

		//记录上一个抽样点的切向
		lsSampleVector_N1 = -BG_nX(ChouYangStart);
		//记录当前点的切向
		lsSampleVector_N2 = -BG_nX(i);

		//如果为第一个点或最后一个点 抽样
		if (i == 0 || i == count_p - 1)
		{
			B.col(j) = Data_Of_Points.col(i);
			ChouYangStart = i;
			++j;
		}
		else
		{
			//若长度达到抽样条件，抽样
			if (abs(changdu2 - changdu1) >= in_len)
			{
				B.col(j) = Data_Of_Points.col(i);
				ChouYangStart = i;
				++j;
			}
			//若角度达到抽样条件，抽样
			else if (dot(lsSampleVector_N1, lsSampleVector_N2) <= cosjiaodu)
			{
				B.col(j) = Data_Of_Points.col(i);
				ChouYangStart = i;
				++j;
			}
		}
	}
	//复位型线矩阵
	Data_Of_Points.reset();
	//更新数据矩阵
	Data_Of_Points = B.cols(0, j - 1);
	//更新点的数量
	//d_n_P = (int)Data_Of_Points.n_rows;
	//长度和长度坐标不变
#pragma endregion
}

inline void Cal_LouXuan::speak_father_del_guanxi()
{
	ptr_xx->del_guanxi_GL_LX(this);
	ptr_fd->del_guanxi_GL_LX(this);
}

void Cal_LouXuan::sel_a_xx_id(int in_id)
{
	data_base.guanlian_xx_id = in_id;
	ptr_xx = ptr_tool->ptr_list_xx->get_obj(data_base.guanlian_xx_id);
}

void Cal_LouXuan::sel_a_fd_id(int in_id)
{
	data_base.guanlian_fd_id = in_id;
	ptr_fd = ptr_tool->ptr_list_fd->get_obj(data_base.guanlian_fd_id);
}

int Cal_LouXuan::save(int pos)
{
	data_base.save(pos);
	return pos;
}

void Cal_LouXuan::load(int pos)
{
	data_base.load(pos);
}

inline int Cal_LouXuan::del_self()
{
	if (v_GL_GX.size() == 0)
	{
	}
	else
	{
		return 1;
	}

	speak_father_del_guanxi();
	delete this;
	return 0;
}

//返回点的数量

//返回第i个点的坐标，3或4阶，点号

//返回全部的点坐标

//返回第i个点处的方向量，3或4阶，点号

//vec Cal_LouXuan::BG_hT(int a, int i)
//{
//	vec m;
//	m = this->Data_Of_Points.col(i).rows(6, 8).t();
//	if (a == 3)
//	{
//		return m;
//	}
//	else if (a == 4)
//	{
//		m.insert_rows(m.n_rows, 1);
//		m(3) = 1.0;
//		return m;
//	}
//	else
//	{
//		//只能是3阶或4阶
//		throw 1;
//	}
//}
//
////返回全部的方向量
//
//mat Cal_LouXuan::BG_hT()
//{
//	return Data_Of_Points.rows(6, 8);
//}

//返回第i个点处的长度坐标

Cal_LouXuan::Cal_LouXuan()
{
	ptr_tool = nullptr;

	ptr_xx = nullptr;
	ptr_fd = nullptr;

	Data_Of_Points.reset();
	Data_Of_Points.reshape(31, 0);

	v_GL_GX.clear();
}

Cal_LouXuan::Cal_LouXuan(Tool_Base* in_ptr, CanShu_LuoXuan& in_data)
{
	ptr_tool = in_ptr;
	set_base_data(in_data);

	ptr_xx = nullptr;
	ptr_fd = nullptr;

	Data_Of_Points.reset();
	Data_Of_Points(28, 0);

	v_GL_GX.clear();
}

Cal_LouXuan::~Cal_LouXuan()
{
}

//void Cal_LouXuan::cal_main_data_by_zhi_qian(double ang_qian)
//{
//	int count_p = ptr_xx->n_P();
//	for (int i = 0; i < count_p; i++)
//	{
//		vec ls_p = ptr_xx->BG_P(3, i); //直角坐标点
//		vec p_zhu = { ls_p(0), ls_p(1), 0.0 };//柱坐标点
//
//		vec t_R = tcRotX(3, -ang_qian) * ls_p;
//		t_R = normalise(-t_R);	//半径方向-向内
//
//		vec zhu_X = ptr_xx->BG_T(3, i); //X轴：相位0截形的切向
//		vec zhu_Z = tcZ(3); //Z轴：	同刀具Z轴
//		vec zhu_Y = cross(zhu_Z, zhu_X); //Y轴：
//
//		vec fa_X = ptr_xx->BG_T(3, i);//X轴：	刃线切向
//		vec fa_Z = cross(fa_X, cross(tcZ(3), t_R));//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//		vec fa_Y = cross(fa_Z, fa_X);//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//
//		double ls_len = ptr_xx->Lenth_At_Point(i);
//
//		vec ans_p = { p_zhu(0), p_zhu(1), p_zhu(2),
//			ls_p(0), ls_p(1), ls_p(2),
//			t_R(0), t_R(1), t_R(2),
//			zhu_X(0), zhu_X(1), zhu_X(2),
//			zhu_Y(0), zhu_Y(1), zhu_Y(2),
//			zhu_Z(0), zhu_Z(1), zhu_Z(2),
//			fa_X(0), fa_X(1), fa_X(2),
//			fa_Y(0), fa_Y(1), fa_Y(2),
//			fa_Z(0), fa_Z(1), fa_Z(2),
//			ls_len };
//
//		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
//	}
//}
//
//void Cal_LouXuan::cal_main_data_by_xie_qian(double ang_qian)
//{
//	double add_xishu = tan(tcRadians(data_base.ang_xie));
//	int count_p = ptr_xx->n_P();
//	for (int i = 0; i < count_p; i++)
//	{
//		vec ls_p = ptr_xx->BG_P(3, i); //直角坐标点
//		vec ls_tr_p = ls_p;
//		double add_z = add_xishu * ls_p(0);
//		ls_p(2) = ls_p(2) + add_z;
//
//		double ang_XW = deltaRotAngle(ls_tr_p, ls_p, tcX(3));
//
//		vec p_zhu = { ls_tr_p(0), ls_tr_p(1), ang_XW };//柱坐标点
//
//		vec t_R = tcRotX(3, -ang_qian) * ls_tr_p;
//		t_R = normalise(-t_R);	//半径方向-向内
//
//		vec zhu_X = ptr_xx->BG_T(3, i); //X轴：相位0截形的切向
//		vec zhu_Z = tcZ(3); //Z轴：	同刀具Z轴
//		vec zhu_Y = cross(zhu_Z, zhu_X); //Y轴：
//
//		vec fa_X = ptr_xx->BG_T(3, i);//X轴：	刃线切向
//		vec fa_Z = cross(fa_X, cross(tcZ(3), t_R));//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//		vec fa_Y = cross(fa_Z, fa_X);//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//
//		double ls_len = ptr_xx->Lenth_At_Point(i);
//
//		vec ans_p = { p_zhu(0), p_zhu(1), p_zhu(2),
//			ls_p(0), ls_p(1), ls_p(2),
//			t_R(0), t_R(1), t_R(2),
//			zhu_X(0), zhu_X(1), zhu_X(2),
//			zhu_Y(0), zhu_Y(1), zhu_Y(2),
//			zhu_Z(0), zhu_Z(1), zhu_Z(2),
//			fa_X(0), fa_X(1), fa_X(2),
//			fa_Y(0), fa_Y(1), fa_Y(2),
//			fa_Z(0), fa_Z(1), fa_Z(2),
//			ls_len };
//
//		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
//	}
//}
//
//void Cal_LouXuan::cal_main_data_by_luo(double ang_luo)
//{
//	vec start_p = ptr_xx->BG_P(3, 0);
//	double zhuan_xishu = tan(tcRadians(ang_luo));
//
//	int count_p = ptr_xx->n_P();
//	for (int i = 0; i < count_p; i++)
//	{
//		vec ls_p = ptr_xx->BG_P(3, i); //直角坐标点
//		double delta_len = ls_p(0) - start_p(0);
//		double delta_rad = delta_len * zhuan_xishu;
//		double ang_XW = tcDegree(delta_rad / ls_p(1));  //弧长/半径
//
//		vec ls_tr_p = ls_p;
//		ls_p = tcRotX(3, ang_XW) * ls_p;
//
//		vec p_zhu = { ls_p(0), ls_p(1), ang_XW };//柱坐标点
//
//		vec t_R = normalise(-ls_p);	//半径方向-向内
//
//		vec zhu_X = ptr_xx->BG_T(3, i); //X轴：相位0截形的切向
//		vec zhu_Z = tcZ(3); //Z轴：	同刀具Z轴
//		vec zhu_Y = cross(zhu_Z, zhu_X); //Y轴：
//
//		vec fa_X = ptr_xx->BG_T(3, i);//X轴：	刃线切向
//		vec fa_Z = cross(fa_X, cross(tcZ(3), t_R));//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//		vec fa_Y = cross(fa_Z, fa_X);//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//
//		double ls_len = ptr_xx->Lenth_At_Point(i);
//
//		vec ans_p = { p_zhu(0), p_zhu(1), p_zhu(2),
//			ls_p(0), ls_p(1), ls_p(2),
//			t_R(0), t_R(1), t_R(2),
//			zhu_X(0), zhu_X(1), zhu_X(2),
//			zhu_Y(0), zhu_Y(1), zhu_Y(2),
//			zhu_Z(0), zhu_Z(1), zhu_Z(2),
//			fa_X(0), fa_X(1), fa_X(2),
//			fa_Y(0), fa_Y(1), fa_Y(2),
//			fa_Z(0), fa_Z(1), fa_Z(2),
//			ls_len };
//
//		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
//	}
//
//}
//
//void Cal_LouXuan::cal_main_data_by_B_luo(mat& B_ang_luo)
//{
//	//将变螺旋角矩阵插值好，遍历直接取
//	vector<double> v_cal_ang_luo;
//
//	vec last_luo = B_ang_luo.col(0);
//	for (int i = 1; i < B_ang_luo.n_cols; i++)
//	{
//		vec cur_luo = B_ang_luo.col(i);
//		double delta_len = cur_luo(0) - last_luo(0);
//		int cal_num = delta_len / 0.001;
//
//		double delta_luo = (cur_luo(1) - last_luo(1)) / cal_num;
//		for (int j = 0; j < cal_num; j++)
//		{
//			double ls_ans_luo = cur_luo(1) + delta_luo * j;
//			v_cal_ang_luo.push_back(ls_ans_luo);
//		}
//		last_luo = cur_luo;
//	}
//
//	int count_p = ptr_xx->n_P();
//	vec start_p = ptr_xx->BG_P(3, 0);
//
//	for (int i = 0; i < count_p; i++)
//	{
//		double ls_len = ptr_xx->Lenth_At_Point(i);
//		double ls_ang_luo = v_cal_ang_luo[ls_len / 0.001];
//		double zhuan_xishu = tan(tcRadians(ls_ang_luo));
//
//		vec ls_p = ptr_xx->BG_P(3, i); //直角坐标点
//		double delta_len = ls_p(0) - start_p(0);
//		double delta_rad = delta_len * zhuan_xishu;
//		double ang_XW = tcDegree(delta_rad / ls_p(1));  //弧长/半径
//
//		vec ls_tr_p = ls_p;
//		ls_p = tcRotX(3, ang_XW) * ls_p;
//
//		vec p_zhu = { ls_p(0), ls_p(1), ang_XW };//柱坐标点
//
//		vec t_R = normalise(-ls_p);	//半径方向-向内
//
//		vec zhu_X = ptr_xx->BG_T(3, i); //X轴：相位0截形的切向
//		vec zhu_Z = tcZ(3); //Z轴：	同刀具Z轴
//		vec zhu_Y = cross(zhu_Z, zhu_X); //Y轴：
//
//		vec fa_X = ptr_xx->BG_T(3, i);//X轴：	刃线切向
//		vec fa_Z = cross(fa_X, cross(tcZ(3), t_R));//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//		vec fa_Y = cross(fa_Z, fa_X);//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
//
//		//double ls_len = ptr_xx->Lenth_At_Point(i);
//
//		vec ans_p = { p_zhu(0), p_zhu(1), p_zhu(2),
//			ls_p(0), ls_p(1), ls_p(2),
//			t_R(0), t_R(1), t_R(2),
//			zhu_X(0), zhu_X(1), zhu_X(2),
//			zhu_Y(0), zhu_Y(1), zhu_Y(2),
//			zhu_Z(0), zhu_Z(1), zhu_Z(2),
//			fa_X(0), fa_X(1), fa_X(2),
//			fa_Y(0), fa_Y(1), fa_Y(2),
//			fa_Z(0), fa_Z(1), fa_Z(2),
//			ls_len };
//
//		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
//	}
//
//}
//
//void Cal_LouXuan::set_R_len(double in_R, double in_z_len)
//{
//
//}
//
//void Cal_LouXuan::rotate(mat33 SYS)
//{
//	int length = Data_Of_Points.n_cols;
//	for (int i = 0; i < length; i++)
//	{
//		vec3 ls_p = Data_Of_Points.submat(0, i, 2, i);
//		vec ls_t = Data_Of_Points.submat(3, i, 5, i); //取出为9*1
//
//		ls_p = SYS * ls_p;
//		ls_t = SYS * ls_t;
//
//		vec ls_ans = { ls_p(0),ls_p(1),ls_p(2),
//			ls_t(0),ls_t(1),ls_t(2) };
//		Data_Of_Points.col(i) = ls_ans;
//	}
//}
//
//void Cal_LouXuan::gen_luoxuanxian(double in_luo, double in_R, mat& points)
//{
//	double end_point_len; //???
//
//	double zhui = 0.0;
//	double luo_ang = in_luo;
//	double A = tan(tcRadians(zhui));
//	double B = tan(tcRadians(luo_ang));
//	double C = cos(tcRadians(zhui));
//	double delta_dis = 0.001;
//	double delta_z = delta_dis;
//	double delta_r = A * delta_z;
//	double delta_l = delta_z / C;  //母线长度增量
//	double delta_w = B * delta_l;
//	//double delta_w = B * delta_z;	//螺旋角与轴线夹角 8.8 mark
//
//	double cur_R = in_R;
//	double cur_ang = 0.0;
//	double cur_len = 0.0;
//
//	vec3 p_pre = { cur_R, 0.0, 0.0 };
//	p_pre = tcRotZ(3, cur_ang) * p_pre;
//
//	//计算结果存放
//	mat ans_p; //3*n
//
//	while (1)
//	{
//		double ls_R = cur_R + delta_r;
//		double delta_ang = tcDegree(atan(delta_w / ls_R)); //旋转需要角度值
//		//double delta_ang = tcDegree(delta_w / ls_R);
//		//double delta_ang = tcDegree(delta_w / ls_R);
//		double ls_ang = cur_ang + delta_ang;
//		double ls_len = cur_len + delta_z;
//
//		vec3 p_ls = { ls_R ,0.0, ls_len };
//		vec3 ls_ans = tcRotZ(3, ls_ang) * p_ls;
//
//		//修整到空间弧长相等 6.12zeng
//		double dis_temp = tcDistance(p_pre, ls_ans);
//		double ans_xishu = delta_dis * 1.0 / dis_temp;
//		//double ans_xishu = 1.0 ; //不修整
//		double ans_delta_z = ans_xishu * delta_z;
//		double ans_delta_r = ans_xishu * delta_r;
//		double ans_delta_ang = ans_xishu * delta_ang;
//
//		cur_R = cur_R + ans_delta_r;
//		cur_ang = cur_ang + ans_delta_ang;
//		cur_len = cur_len + ans_delta_z;
//
//		vec3 p_ans = { cur_R ,0.0, cur_len };
//		p_ans = tcRotZ(3, cur_ang) * p_ans;
//		p_pre = p_ans;	//记录上一点
//
//		ans_p.insert_cols(ans_p.n_cols, p_ans);
//		if (ls_ans(2) > end_point_len)
//		{
//			break;
//		}
//	}
//}

//重载=

//void Cal_RenXian::operator=(const Cal_RenXian& A)
//{
//	n_P = A.n_P;
//	Max_No_P = A.Max_No_P;
//	Distance_of_Point = A.Distance_of_Point;
//	Data_Of_Points = A.Data_Of_Points;
//}
//
////输入已经构造完成的空间线（ mat（n*3：x，y，z）） 坐标系原点在螺旋线起点截面回转中心
////输出：以第一个点相位角为0
//
//void Cal_RenXian::ImportData_by_luoxuancao(KongJianXian& line_in)
//{
//#pragma region 转换圆柱坐标
//	//要求的矩阵为3坐标，其中长度坐标必须是Z，由刀尖到刀柄
//	//需要注意螺旋角造成的弧长影响，本程序可能在排序时出错
//	//将三坐标换算为，圆柱坐标（分别为X，半径，相位角）
//	//相位角在第一个点为0
//
//	//空间线坐标系转到工件坐标系相同--默认输入已经满足该条件
//	mat A = line_in.get_all_p(); //空间线坐标系下，刃线的数据表达（n*3：x，R，z）
//
//	vec  R, XWJ, Z;  //柱半径，相位角，Z+长度
//	XWJ.resize(A.n_rows);
//	//记录过中轴线点，相位角计算完改为旁边点的相位角
//	vector<int> v_index;
//
//	//计算圆柱坐标系
//	//长度坐标 
//	Z = A.col(2);
//	//半径坐标
//	R = sqrt(square(A.col(0)) + square(A.col(1)));
//
//	//计算相位角，单位是弧度
//	for (int i = 0; i < A.n_rows; i++)
//	{
//		if (A.row(i)(1) > 0)
//		{
//			XWJ(i) = acos(A.row(i)(0) / R(i));
//		}
//		else if (A.row(i)(1) < 0)
//		{
//			XWJ(i) = 2 * datum::pi - acos(A.row(i)(0) / R(i));
//		}
//		else if (A.row(i)(1) == 0 && A.row(i)(0) > 0)
//		{
//			XWJ(i) = 0.0;
//		}
//		else if (A.row(i)(1) == 0 && A.row(i)(0) < 0)
//		{
//			XWJ(i) = datum::pi;
//		}
//		else
//		{
//			XWJ(i) = 0.0;	//说明点在中轴线上
//			v_index.push_back(i);
//		}
//		//变换方向和零点，使X坐标上为0，绕Z轴旋转为正
//		XWJ(i) = -XWJ(i) + datum::pi / 2.0;
//	}
//	//以第一个点位相位0；
//	XWJ = XWJ - XWJ(0);
//	//修改中轴线点的相位角
//	for (int i = 0; i < v_index.size(); i++)
//	{
//		int cur = v_index[i];
//		if (cur < XWJ.size() - 1)
//		{
//			XWJ(cur) = XWJ(cur + 1);
//		}
//		else
//		{
//			XWJ(cur) = XWJ(cur - 1); //最后一个点在中轴线等于前一点相位角
//		}
//	}
//#pragma endregion 
//
//	//计算均分点距
//	Distance_of_Point = line_in.get_delta_dis();
//	//点的总数=读入点数据矩阵的行数
//	n_P = (int)Z.n_rows;
//
//#pragma region 计算点数据
//	//计算两个坐标系的xRz向量等并储存
//	//定义临时变量
//	rowvec dData_Of_Points;
//	vec SYS_X_N, SYS_Y_N, SYS_Z_N;
//	vec	SYS_X_H, SYS_Y_H, SYS_Z_H;
//	vec	T, N, Z0;
//	Z0 = tcZ(3);
//
//	//复位数据储存矩阵
//	Data_Of_Points.reset();
//	//填充点数据矩阵，不计算第最后一个点
//	for (int i = 0; i < n_P - 1; i++)
//	{
//		//临时变量复位
//		dData_Of_Points.reset();
//		//记录点编号 = i
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 1);
//		dData_Of_Points(0) = (double)i;
//		//记录点坐标
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, A.submat(i, 0, i, 2));
//
//		//计算(法坐标系)x向量, Y向量, z向量
//		SYS_X_N = normalise(A.submat(i + 1, 0, i + 1, 2).t() - A.submat(i, 0, i, 2).t());
//		vec3 ls_p = -A.submat(i, 0, i, 2).t(); //参考点指向回转轴
//		ls_p(2) = 0.0;
//		SYS_Y_N = normalise(cross(normalise(ls_p), SYS_X_N)); //垂直于刃线，指向0后刀面内
//		SYS_Z_N = normalise(cross(SYS_X_N, SYS_Y_N));
//
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_N.t());
//
//		//计算(横坐标系)x向量, Y向量, z向量---8.28 计算，修改---在刃线坐标系的计算方式
//		//Y --//指向回转运动的反方向。同零径向后角线方向
//		SYS_Y_H = normalise(tcRotZ(3, -90.0) * ls_p);
//		//X-- //相切于刃线在纵截面内的投影线，由刀尖指向刀柄
//		vec3 cur_p = A.submat(i, 0, i, 2).t();
//		vec3 next_p = A.submat(i + 1, 0, i + 1, 2).t();
//		double delta_z = next_p(2) - cur_p(2);
//		double delta_r = R(i + 1) - R(i);
//		cur_p(2) = 0.0;	//水平
//		vec3 cal_p = normalise(cur_p) * R(i + 1); //半径长度
//		cal_p(2) = delta_z;	//长度增量
//
//		SYS_X_H = normalise(cal_p - cur_p);
//		//在纵截面内，垂直于刃线在纵截面内的投影线，指向材料内部
//		SYS_Z_H = normalise(cross(SYS_X_H, SYS_Y_H));
//
//
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_H.t());
//
//		//记录(柱坐标系)柱半径，相位角，Z+长度
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, R.row(i));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, XWJ.row(i));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, Z.row(i));
//
//		//将一条目数据插入Data矩阵中
//		Data_Of_Points.insert_rows(Data_Of_Points.n_rows, dData_Of_Points);
//	}
//
//	//加上最后一个点 2024.11.20
//	{
//		//临时变量复位
//		dData_Of_Points.reset();
//		//记录点编号 = n_P - 1
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 1);
//		dData_Of_Points(0) = (double)(n_P - 1);
//		//记录点坐标
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, A.submat(n_P - 1, 0, n_P - 1, 2));
//
//		//计算(法坐标系)x向量, Y向量, z向量
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_N.t());
//
//		//计算(横坐标系)x向量, Y向量, z向量
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_H.t());
//
//		//记录(柱坐标系)柱半径，相位角，Z+长度
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, R.row(n_P - 1));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, XWJ.row(n_P - 1));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, Z.row(n_P - 1));
//
//		//将一条目数据插入Data矩阵中
//		Data_Of_Points.insert_rows(Data_Of_Points.n_rows, dData_Of_Points);
//	}
//
//	//最大点编号 = 最后一个点的总编号
//	Max_No_P = (int)Data_Of_Points.row(Data_Of_Points.n_rows - 1)(0);
//	n_P = Data_Of_Points.n_rows;
//#pragma endregion
//
//	//test
//	//mat ls_line = get_kongjianxian();
//	//ls_line = ls_line.t();
//	//ls_line.save(R"(import_5.31.txt)", raw_ascii);
//}
//
//void Cal_RenXian::ImportData_by_qiutou(KongJianXian& line_in)
//{
//#pragma region 转换圆柱坐标
//	//要求的矩阵为3坐标，其中长度坐标必须是Z，由刀尖到刀柄
//	//需要注意螺旋角造成的弧长影响，本程序可能在排序时出错
//	//将三坐标换算为，圆柱坐标（分别为X，半径，相位角）
//	//相位角在第一个点为0
//
//	//空间线坐标系转到工件坐标系相同--默认输入已经满足该条件
//	mat A = line_in.get_all_p(); //空间线坐标系下，刃线的数据表达（n*3：x，R，z）
//
//	vec  R, XWJ, Z;  //柱半径，相位角，Z+长度
//	XWJ.resize(A.n_rows);
//	//记录过中轴线点，相位角计算完改为旁边点的相位角
//	vector<int> v_index;
//
//	//计算圆柱坐标系
//	//长度坐标 
//	Z = A.col(2);
//	//半径坐标
//	R = sqrt(square(A.col(0)) + square(A.col(1)));
//
//	//计算相位角，单位是弧度
//	for (int i = 0; i < A.n_rows; i++)
//	{
//		if (A.row(i)(1) > 0)
//		{
//			XWJ(i) = acos(A.row(i)(0) / R(i));
//		}
//		else if (A.row(i)(1) < 0)
//		{
//			XWJ(i) = 2 * datum::pi - acos(A.row(i)(0) / R(i));
//		}
//		else if (A.row(i)(1) == 0 && A.row(i)(0) > 0)
//		{
//			XWJ(i) = 0.0;
//		}
//		else if (A.row(i)(1) == 0 && A.row(i)(0) < 0)
//		{
//			XWJ(i) = datum::pi;
//		}
//		else
//		{
//			XWJ(i) = 0.0;	//说明点在中轴线上
//			v_index.push_back(i);
//		}
//		//变换方向和零点，使X坐标上为0，绕Z轴旋转为正
//		XWJ(i) = -XWJ(i) + datum::pi / 2.0;
//	}
//	//以第一个点位相位0；
//	XWJ = XWJ - XWJ(0);
//	//修改中轴线点的相位角
//	for (int i = 0; i < v_index.size(); i++)
//	{
//		int cur = v_index[i];
//		if (cur < XWJ.size() - 1)
//		{
//			XWJ(cur) = XWJ(cur + 1);
//		}
//		else
//		{
//			XWJ(cur) = XWJ(cur - 1); //最后一个点在中轴线等于前一点相位角
//		}
//	}
//#pragma endregion 
//
//	//计算均分点距
//	Distance_of_Point = line_in.get_delta_dis();
//	//点的总数=读入点数据矩阵的行数 - 1 最后一个点不要 --要11.20
//	n_P = (int)Z.n_rows;
//
//#pragma region 计算点数据
//	//计算两个坐标系的xRz向量等并储存
//	//定义临时变量
//	rowvec dData_Of_Points;
//	vec SYS_X_N, SYS_Y_N, SYS_Z_N;
//	vec	SYS_X_H, SYS_Y_H, SYS_Z_H;
//	vec	T, N, Z0;
//	Z0 = tcZ(3);
//
//	//复位数据储存矩阵
//	Data_Of_Points.reset();
//	//填充点数据矩阵，不计算第最后一个点
//	for (int i = 0; i < n_P - 1; i++)
//	{
//		//临时变量复位
//		dData_Of_Points.reset();
//		//记录点编号 = i
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 1);
//		dData_Of_Points(0) = (double)i;
//		//记录点坐标
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, A.submat(i, 0, i, 2));
//
//		//计算(法坐标系)x向量, Y向量, z向量
//		SYS_X_N = normalise(A.submat(i + 1, 0, i + 1, 2).t() - A.submat(i, 0, i, 2).t());
//		vec3 ls_p = -A.submat(i, 0, i, 2).t(); //球头部分参考点指向球心  --9.14 
//		//运动方向
//		vec3 v_yundong = cross(normalise(ls_p), tcZ(3));
//		vec3 test_ls_y = normalise(cross(normalise(ls_p), SYS_X_N));
//
//		SYS_Y_N = normalise(v_yundong - dot(v_yundong, SYS_X_N) * SYS_X_N);
//		SYS_Z_N = normalise(cross(SYS_X_N, SYS_Y_N));
//		double ang = tcDegree(acos(dot(test_ls_y, SYS_Y_N)));
//
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_N.t());
//
//		//计算(横坐标系)x向量, Y向量, z向量---8.28 计算，修改---在刃线坐标系的计算方式
//		//Y --//指向回转运动的反方向。同零径向后角线方向
//		ls_p(2) = 0.0;//球头部分参考点指向球心  --9.21
//		SYS_Y_H = normalise(tcRotZ(3, -90.0) * ls_p);
//		//X-- //相切于刃线在纵截面内的投影线，由刀尖指向刀柄
//		vec3 cur_p = A.submat(i, 0, i, 2).t();
//		vec3 next_p = A.submat(i + 1, 0, i + 1, 2).t();
//		double delta_z = next_p(2) - cur_p(2);
//		double delta_r = R(i + 1) - R(i);
//		cur_p(2) = 0.0;	//水平
//		vec3 cal_p = normalise(cur_p) * delta_r; //半径增量
//		cal_p(2) = delta_z;	//长度增量
//
//		SYS_X_H = normalise(cal_p);
//		//在纵截面内，垂直于刃线在纵截面内的投影线，指向材料内部
//		SYS_Z_H = normalise(cross(SYS_X_H, SYS_Y_H));
//
//
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_H.t());
//
//		//记录(柱坐标系)柱半径，相位角，Z+长度
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, R.row(i));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, XWJ.row(i));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, Z.row(i));
//
//		//将一条目数据插入Data矩阵中
//		Data_Of_Points.insert_rows(Data_Of_Points.n_rows, dData_Of_Points);
//	}
//
//	//加上最后一个点 2024.11.20
//	{
//		//临时变量复位
//		dData_Of_Points.reset();
//		//记录点编号 = n_P - 1
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 1);
//		dData_Of_Points(0) = (double)(n_P - 1);
//		//记录点坐标
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, A.submat(n_P - 1, 0, n_P - 1, 2));
//
//		//计算(法坐标系)x向量, Y向量, z向量
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_N.t());
//
//		//计算(横坐标系)x向量, Y向量, z向量
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_H.t());
//
//		//记录(柱坐标系)柱半径，相位角，Z+长度
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, R.row(n_P - 1));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, XWJ.row(n_P - 1));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, Z.row(n_P - 1));
//
//		//将一条目数据插入Data矩阵中
//		Data_Of_Points.insert_rows(Data_Of_Points.n_rows, dData_Of_Points);
//	}
//
//	//最大点编号 = 最后一个点的总编号
//	Max_No_P = (int)Data_Of_Points.row(Data_Of_Points.n_rows - 1)(0);
//	n_P = Data_Of_Points.n_rows;
//#pragma endregion
//
//	//test  - 2024.11.20 验证正确，没少点
//	//mat ls_line = get_kongjianxian();
//	//ls_line = ls_line.t();
//	//ls_line.save(R"(import_5.31.txt)", raw_ascii);
//}
//
////对于平底刀横刃法坐标系与横坐标系相等
//
//void Cal_RenXian::ImportData_by_hengren(KongJianXian& line_in)
//{
//#pragma region 转换圆柱坐标
//	//要求的矩阵为3坐标，其中长度坐标必须是Z，由刀尖到刀柄
//	//需要注意螺旋角造成的弧长影响，本程序可能在排序时出错
//	//将三坐标换算为，圆柱坐标（分别为X，半径，相位角）
//	//相位角在第一个点为0
//
//	//空间线坐标系转到工件坐标系相同--默认输入已经满足该条件
//	mat A = line_in.get_all_p(); //空间线坐标系下，刃线的数据表达（n*3：x，R，z）
//
//	vec  R, XWJ, Z;  //柱半径，相位角，Z+长度
//	XWJ.resize(A.n_rows);
//	//记录过中轴线点，相位角计算完改为旁边点的相位角
//	vector<int> v_index;
//
//	//计算圆柱坐标系
//	//长度坐标 
//	Z = A.col(2);
//	//半径坐标
//	R = sqrt(square(A.col(0)) + square(A.col(1)));
//
//	//计算相位角，单位是弧度
//	for (int i = 0; i < A.n_rows; i++)
//	{
//		if (A.row(i)(1) > 0)
//		{
//			XWJ(i) = acos(A.row(i)(0) / R(i));
//		}
//		else if (A.row(i)(1) < 0)
//		{
//			XWJ(i) = 2 * datum::pi - acos(A.row(i)(0) / R(i));
//		}
//		else if (A.row(i)(1) == 0 && A.row(i)(0) > 0)
//		{
//			XWJ(i) = 0.0;
//		}
//		else if (A.row(i)(1) == 0 && A.row(i)(0) < 0)
//		{
//			XWJ(i) = datum::pi;
//		}
//		else
//		{
//			XWJ(i) = 0.0;	//说明点在中轴线上
//			v_index.push_back(i);
//		}
//		//变换方向和零点，使X坐标上为0，绕Z轴旋转为正
//		XWJ(i) = -XWJ(i) + datum::pi / 2.0;
//	}
//	//以第一个点位相位0；
//	XWJ = XWJ - XWJ(0);
//	//修改中轴线点的相位角
//	for (int i = 0; i < v_index.size(); i++)
//	{
//		int cur = v_index[i];
//		if (cur < XWJ.size() - 1)
//		{
//			XWJ(cur) = XWJ(cur + 1);
//		}
//		else
//		{
//			XWJ(cur) = XWJ(cur - 1); //最后一个点在中轴线等于前一点相位角
//		}
//	}
//#pragma endregion 
//
//	//计算均分点距
//	Distance_of_Point = line_in.get_delta_dis();
//	//点的总数=读入点数据矩阵的行数
//	n_P = (int)Z.n_rows;
//
//#pragma region 计算点数据
//	//计算两个坐标系的xRz向量等并储存
//	//定义临时变量
//	rowvec dData_Of_Points;
//	vec SYS_X_N, SYS_Y_N, SYS_Z_N;
//	vec	SYS_X_H, SYS_Y_H, SYS_Z_H;
//	vec	T, N, Z0;
//	Z0 = tcZ(3);
//
//	//复位数据储存矩阵
//	Data_Of_Points.reset();
//	//填充点数据矩阵，不计算第最后一个点
//	for (int i = 0; i < n_P - 1; i++)
//	{
//		//临时变量复位
//		dData_Of_Points.reset();
//		//记录点编号 = i
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 1);
//		dData_Of_Points(0) = (double)i;
//		//记录点坐标
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, A.submat(i, 0, i, 2));
//
//		//计算(法坐标系)x向量, Y向量, z向量
//		SYS_X_N = normalise(A.submat(i + 1, 0, i + 1, 2).t() - A.submat(i, 0, i, 2).t());
//		//参考点指向原点 -2.11 
//		//横刃运动反方向一定水平 - 2.14
//		vec3 ls_p = A.submat(n_P - 1, 0, n_P - 1, 2).t(); //所有坐标系都相同
//		vec3 ls_p1 = tcRotZ(3, 2.0) * ls_p;
//
//		vec3 ls_v = normalise(ls_p1 - ls_p);
//		ls_v = normalise(cross(ls_v, SYS_X_N));
//		SYS_Y_N = normalise(cross(SYS_X_N, ls_v));
//
//		//SYS_Y_N = normalise(cross(SYS_X_N, normalise(ls_p))); //垂直于刃线，运动方向相反
//		SYS_Z_N = normalise(cross(SYS_X_N, SYS_Y_N));
//
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_N.t());
//
//		//计算(横坐标系)x向量, Y向量, z向量---与法坐标系相同
//		//Y --//指向回转运动的反方向。同零径向后角线方向
//		SYS_Y_H = SYS_Y_N;
//
//		SYS_X_H = SYS_X_N;
//
//		SYS_Z_H = SYS_Z_N;
//
//
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_H.t());
//
//		//记录(柱坐标系)柱半径，相位角，Z+长度
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, R.row(i));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, XWJ.row(i));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, Z.row(i));
//
//		//将一条目数据插入Data矩阵中
//		Data_Of_Points.insert_rows(Data_Of_Points.n_rows, dData_Of_Points);
//	}
//
//	//加上最后一个点 2024.11.20
//	{
//		//临时变量复位
//		dData_Of_Points.reset();
//		//记录点编号 = n_P - 1
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 1);
//		dData_Of_Points(0) = (double)(n_P - 1);
//		//记录点坐标
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, A.submat(n_P - 1, 0, n_P - 1, 2));
//
//		//计算(法坐标系)x向量, Y向量, z向量
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_N.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_N.t());
//
//		//计算(横坐标系)x向量, Y向量, z向量
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_X_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Y_H.t());
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, SYS_Z_H.t());
//
//		//记录(柱坐标系)柱半径，相位角，Z+长度
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, R.row(n_P - 1));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, XWJ.row(n_P - 1));
//		dData_Of_Points.insert_cols(dData_Of_Points.n_cols, Z.row(n_P - 1));
//
//		//将一条目数据插入Data矩阵中
//		Data_Of_Points.insert_rows(Data_Of_Points.n_rows, dData_Of_Points);
//	}
//
//	//最大点编号 = 最后一个点的总编号
//	Max_No_P = (int)Data_Of_Points.row(Data_Of_Points.n_rows - 1)(0);
//	n_P = Data_Of_Points.n_rows;
//#pragma endregion
//
//	//test
//	//mat ls_line = get_kongjianxian();
//	//ls_line = ls_line.t();
//	//ls_line.save(R"(import_5.31.txt)", raw_ascii);
//}
//
//////将起点终点反向得到新的线-
////球头、螺旋不同--目前只有球头10.14
//
//void Cal_RenXian::fanxiang()
//{
//	mat ls_data = this->get_kongjianxian(); //n*3
//	ls_data = ls_data.t(); //3*n
//
//	ls_data = fliplr(ls_data);
//
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	this->ImportData_by_qiutou(ls_line);
//}
//
////将已有刃线，进行旋转
//
//void Cal_RenXian::rotate(mat33 SYS)
//{
//	mat ls_data = this->get_kongjianxian(); //n*3
//	ls_data = ls_data.t(); //3*n
//	ls_data = SYS * ls_data;
//
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	this->ImportData_by_luoxuancao(ls_line);
//}
//
////将已有刃线，进行平移
//
//void Cal_RenXian::trans(vec3 O)
//{
//	mat ls_data = this->get_kongjianxian(); //n*3
//	ls_data = ls_data.t(); //3*n
//	ls_data.each_col() += O;
//
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	this->ImportData_by_luoxuancao(ls_line);
//}
//
////截取线已有刃线的一段，输入截取起点终点（0-1]，得到新的线
//
//void Cal_RenXian::cutting(double start, double end)
//{
//	mat ls_data = this->get_kongjianxian(); //n*3
//	int p_num = ls_data.n_rows;
//	int start_index = p_num * start;
//	int end_index = p_num * end;
//	//切掉两头
//	ls_data.shed_rows(end_index - 1, ls_data.n_rows - 1);
//	ls_data.shed_rows(0, start_index);
//
//	ls_data = ls_data.t();
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	this->ImportData_by_luoxuancao(ls_line);
//}
//
//void Cal_RenXian::cutting_qiutou(double start, double end)
//{
//	double len_ren = this->Lenth_of_RenXian();
//	mat ls_data = this->get_kongjianxian(); //n*3
//	int p_num = ls_data.n_rows;
//	int start_index = p_num * start;
//	int end_index = p_num * end;
//	//切掉两头  
//	/*ls_data.shed_rows(end_index, ls_data.n_rows);
//	ls_data.shed_rows(0, start_index);*/  //shed_rows(0,0) 也会切掉第一个 11.20 
//
//	ls_data = ls_data.submat(start_index, 0, end_index - 1, 2);
//
//	ls_data = ls_data.t();
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	this->ImportData_by_qiutou(ls_line);
//}
//
////沿终点切向延伸指定距离
//
//void Cal_RenXian::extend(double add_dis)
//{
//	mat ls_data = this->get_kongjianxian(); //n*3
//	int p_num = ls_data.n_rows;
//	ls_data = ls_data.t();
//	vec3 pend1 = ls_data.col(p_num - 1);
//	vec3 pend2 = ls_data.col(p_num - 2);
//	vec3 delta_qie = normalise(pend1 - pend2);
//
//	double delta_dis = tcDistance(pend1, pend2);
//
//	if (delta_dis < 0.0000001)
//	{
//		throw - 1;
//	}
//
//	int add_num = add_dis / delta_dis;
//	ls_data.insert_cols(p_num - 1, add_num);
//	for (int i = 0; i < add_num; i++)
//	{
//		vec3 ls_p = delta_qie * delta_dis * (i + 1) + pend1;
//		ls_data.col(p_num + i) = ls_p;
//	}
//
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	this->ImportData_by_luoxuancao(ls_line);
//}
//
////针对球头线设置偏心距, 在没拼接螺旋前偏置()
//
//void Cal_RenXian::set_pinxin_dis(double in_dis)
//{
//	//1、根据偏心距计算出，偏置长度的范围
//	mat ls_data = get_kongjianxian(); //n*3
//
//	//ls_data.save(R"(importdata_5.31.txt)", raw_ascii);
//
//	ls_data = ls_data.t(); //3*n
//
//	//2、计算一个点的偏置量
//	int p_num = ls_data.n_cols;
//	double delta_pian = in_dis / p_num;
//
//	for (int i = 0; i < p_num; i++)
//	{
//		ls_data.col(i) = P(i) - hY(i) * (i * delta_pian);
//	}
//
//	KongJianXian ls_line;
//	ls_line.init_data(ls_data);
//	this->ImportData_by_qiutou(ls_line);
//
//	//ls_data = ls_data.t();
//	//ls_data.save(R"(pianxin_5.31.txt)", raw_ascii);
//}
//
////将已经计算完成的刃线，旋转工序对应的补偿角度 25.2.19
//
//void Cal_RenXian::rotate_by_buchang(double in_bu_ang)
//{
//	//数据拆分旋转后合并
//	int count_p = Data_Of_Points.n_rows;//点编号
//	for (int i = 0; i < count_p; i++)
//	{
//		//拆分
//		vec3 p_coor = Data_Of_Points.submat(i, 1, i, 3).t(); //点坐标
//
//		vec3 n_SYS_x = Data_Of_Points.submat(i, 4, i, 6).t();
//		vec3 n_SYS_y = Data_Of_Points.submat(i, 7, i, 9).t();
//		vec3 n_SYS_z = Data_Of_Points.submat(i, 10, i, 12).t();
//		mat33 n_SYS = eye(3, 3);
//		n_SYS.col(0) = n_SYS_x;
//		n_SYS.col(1) = n_SYS_y;
//		n_SYS.col(2) = n_SYS_z;
//
//		vec3 h_SYS_x = Data_Of_Points.submat(i, 13, i, 15).t();
//		vec3 h_SYS_y = Data_Of_Points.submat(i, 16, i, 18).t();
//		vec3 h_SYS_z = Data_Of_Points.submat(i, 19, i, 21).t();
//		mat33 h_SYS = eye(3, 3);
//		h_SYS.col(0) = h_SYS_x;
//		h_SYS.col(1) = h_SYS_y;
//		h_SYS.col(2) = h_SYS_z;
//
//		double R_zhu = Data_Of_Points(i, 22);
//		double ang_XW = Data_Of_Points(i, 23);
//		double z_value = Data_Of_Points(i, 24);
//
//		//旋转
//		{
//			p_coor = tcRotZ(3, in_bu_ang) * p_coor;
//			n_SYS = tcRotZ(3, in_bu_ang) * n_SYS;
//			h_SYS = tcRotZ(3, in_bu_ang) * h_SYS;
//
//			R_zhu = R_zhu;
//			ang_XW = ang_XW + in_bu_ang;
//			z_value = z_value;
//		}
//
//
//		//合并
//		{
//			rowvec dData_Of_Points;
//			dData_Of_Points.reset();
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 1);
//			dData_Of_Points(0) = (double)i;//记录点坐标
//
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, p_coor.t());//记录点坐标
//
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, n_SYS.col(0).t());//(法坐标系)x向量, Y向量, z向量
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, n_SYS.col(1).t());
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, n_SYS.col(2).t());
//
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, h_SYS.col(0).t());//(法坐标系)x向量, Y向量, z向量
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, h_SYS.col(1).t());
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, h_SYS.col(2).t());
//
//			dData_Of_Points.insert_cols(dData_Of_Points.n_cols, 3);
//			dData_Of_Points(22) = R_zhu;
//			dData_Of_Points(23) = ang_XW;
//			dData_Of_Points(24) = z_value;
//
//			Data_Of_Points.row(i) = dData_Of_Points;
//		}
//
//	}
//
//
//}
//
////返回刃线的长度,在抽样的情况下可能无法得出
//
//double Cal_RenXian::Lenth_of_RenXian()
//{
//	return (double)Max_No_P * Distance_of_Point;
//}
//
////返回刃线点的数量
//
//int Cal_RenXian::get_p_num()
//{
//	return n_P;
//}
//
////返回第i个点的坐标，点号
//
//vec Cal_RenXian::P(int i)
//{
//	vec m;
//	m = this->Data_Of_Points.row(i).cols(1, 3).t();
//	return m;
//}
//
////返回第i个点处的，法坐标系: X向量
//
//vec Cal_RenXian::nX(int i)
//{
//	vec m;
//	m = this->Data_Of_Points.row(i).cols(4, 6).t();
//	return m;
//}
//
////返回第i个点处的, 法坐标系：Y向量
//
//vec Cal_RenXian::nY(int i)
//{
//	vec m;
//	m = this->Data_Of_Points.row(i).cols(7, 9).t();
//	return m;
//}
//
////返回第i个点处的，法坐标系：Z向量
//
//vec Cal_RenXian::nZ(int i)
//{
//	vec m;
//	m = this->Data_Of_Points.row(i).cols(10, 12).t();
//	return m;
//}
//
////返回第i个点处的，横坐标系: X向量
//
//vec Cal_RenXian::hX(int i)
//{
//	vec m;
//	m = this->Data_Of_Points.row(i).cols(13, 15).t();
//	return m;
//}
//
////返回第i个点处的，横坐标系：Y向量
//
//vec Cal_RenXian::hY(int i)
//{
//	vec m;
//	m = this->Data_Of_Points.row(i).cols(16, 18).t();
//	return m;
//}
//
////返回第i个点处的，横坐标系：Z向量
//
//vec Cal_RenXian::hZ(int i)
//{
//	vec m;
//	m = this->Data_Of_Points.row(i).cols(19, 21).t();
//	return m;
//}
//
////返回第i个点的柱半径
//
//double Cal_RenXian::rotR(int i)
//{
//	return Data_Of_Points.row(i)(22);
//}
//
////返回第i个点的相位角
//
//double Cal_RenXian::XWJ(int i)
//{
//	return Data_Of_Points.row(i)(23);
//}
//
////返回第i个点处的，法坐标系
//
//mat Cal_RenXian::nSYS(int i)
//{
//	mat m;
//	m.insert_cols(m.n_cols, this->Data_Of_Points.row(i).cols(4, 6).t());//X向量
//	m.insert_cols(m.n_cols, this->Data_Of_Points.row(i).cols(7, 9).t());//Y向量
//	m.insert_cols(m.n_cols, this->Data_Of_Points.row(i).cols(10, 12).t());//Z向量
//	return m;
//}
//
////返回第i个点处的，横坐标系
//
//mat Cal_RenXian::hSYS(int i)
//{
//	mat m;
//	m.insert_cols(m.n_cols, this->Data_Of_Points.row(i).cols(13, 15).t());//X向量
//	m.insert_cols(m.n_cols, this->Data_Of_Points.row(i).cols(16, 18).t());//Y向量
//	m.insert_cols(m.n_cols, this->Data_Of_Points.row(i).cols(19, 21).t());//Z向量
//	return m;
//}
//
////第i个点所在的弧长百分比，空间线长度
//
//double Cal_RenXian::lenth_percent(int i)
//{
//	return double(Data_Of_Points(i, 0)) / double(Max_No_P);
//}
//
////构造函数
//
//Cal_RenXian::Cal_RenXian()
//{
//	n_P = 0;
//	Max_No_P = 0;
//	Distance_of_Point = 0.0;
//	Data_Of_Points.clear();
//}
//
////析构函数
//
//Cal_RenXian::~Cal_RenXian()
//{
//}
//
////提取出空间线的点集，用来进行刃线的相关编辑 返回n*3
//
//mat Cal_RenXian::get_kongjianxian()
//{
//	return Data_Of_Points.submat(0, 1, n_P - 1, 3);
//}
//
//double Cal_RenXian::cal_cut_dis_percent_in_end(double in_dis, mat& in_ren)
//{
//	//in_ren n*3
//	int count_p = in_ren.n_rows;
//	double count_dis = 0.0;
//	int ans_index = 0;
//	while (count_dis < in_dis)
//	{
//		vec p0 = in_ren.row(count_p - 1).t();
//		vec p1 = in_ren.row(count_p - 2).t();
//		double ls_dis = tcDistance(p0, p1);
//		//double ls_dis = tcDistance(in_ren.row(count_p - 1), in_ren.row(count_p - 2));
//		count_dis = count_dis + ls_dis;
//
//		ans_index++;
//		count_p--;
//	}
//	double ans = ans_index / ((in_ren.n_rows - 1) * 1.0);
//	return ans;
//}

void Cal_FenDu::set_base_data(CanShu_FenDu& in_data)
{
	data_base = in_data;
	is_lastest = 0;
}

void Cal_FenDu::init_data()
{
	is_lastest = 1;
	v_fendu.clear();
	count = data_base.count;
	for (int i = 0; i < data_base.count; i++)
	{
		v_fendu.push_back(data_base.v_ang_pos[i]);
	}
	//
	is_lastest = 1;
	for (size_t i = 0; i < v_GL_LX.size(); i++)
	{
		v_GL_LX[i]->is_lastest = 0;
	}
}

void Cal_FenDu::init_guanxi()
{
	//没有上级关系
}

void Cal_FenDu::add_son(Cal_LouXuan* in_ptr)
{
	v_GL_LX.push_back(in_ptr);
}

void Cal_FenDu::cal_son_last_state()
{
	if (is_lastest == 0)
	{
		for (size_t i = 0; i < v_GL_LX.size(); i++)
		{
			v_GL_LX[i]->is_lastest = 0;
		}
	}
}

void Cal_FenDu::del_guanxi_GL_LX(Cal_LouXuan* p)
{
	for (auto iter = v_GL_LX.begin(); iter != v_GL_LX.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_LX.erase(iter);
			break;
		}
	}
}

int Cal_FenDu::guanxi_exist(Cal_LouXuan* p)
{
	for (size_t i = 0; i < v_GL_LX.size(); i++)
	{
		if (p == v_GL_LX[i])
		{
			return i;
		}
	}
	return -1;
}

void Cal_XingXian::del_guanxi_GL_LX(Cal_LouXuan* p)
{
	for (auto iter = v_GL_LX.begin(); iter != v_GL_LX.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_LX.erase(iter);
			break;
		}
	}
}
void Cal_XingXian::add_guanxi_GL_LX(Cal_LouXuan* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_LX.push_back(p);
	}
}

void Cal_XingXian::del_guanxi_GL_HJ(Cal_HouJiao* p)
{
	for (auto iter = v_GL_HJ.begin(); iter != v_GL_HJ.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_HJ.erase(iter);
			break;
		}
	}
}

int Cal_XingXian::guanxi_exist(Cal_HouJiao* p)
{
	for (size_t i = 0; i < v_GL_HJ.size(); i++)
	{
		if (p == v_GL_HJ[i])
		{
			return i;
		}
	}
	return -1;
}

int Cal_XingXian::guanxi_exist(Cal_LouXuan* p)
{
	for (size_t i = 0; i < v_GL_LX.size(); i++)
	{
		if (p == v_GL_LX[i])
		{
			return i;
		}
	}
	return -1;
}

bool Cal_XingXian::is_del_ok()
{
	if (v_GL_LX.size() == 0 && v_GL_HJ.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}	
}

void Cal_XingXian::speak_father_del_guanxi()
{
	//没有向上关系
}

void Cal_XingXian::add_guanxi_GL_HJ(Cal_HouJiao* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_HJ.push_back(p);
	}
}

void Cal_FenDu::add_guanxi_GL_LX(Cal_LouXuan* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_LX.push_back(p);
	}
}

int Cal_FenDu::Count()
{
	return count;
}

double Cal_FenDu::Angle(int i)
{
	return v_fendu[i];
}

void Cal_FenDu::speak_father_del_guanxi()
{
	//没有向上关系
}

Cal_FenDu::Cal_FenDu()
{
	count = 0;
	v_fendu.clear();
	ptr_tool = nullptr;
	v_GL_LX.clear();
}

Cal_FenDu::~Cal_FenDu()
{
}

Cal_FenDu::Cal_FenDu(Tool_Base* in_ptr, CanShu_FenDu& in_data)
{
	ptr_tool = in_ptr;
	set_base_data(in_data);
	init_data();

	v_GL_LX.clear();
}



int Cal_FenDu::del_self()
{
	int count = 1;
	if (v_GL_LX.size() == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return 1;
	}
}

bool Cal_FenDu::is_del_ok()
{
	if (v_GL_LX.size()==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Cal_FenDu::save(int pos)
{
	data_base.save(pos);
	return pos;
}


void Cal_FenDu::load(int pos)
{
	data_base.load(pos);
}


void Cal_QDM::set_base_data(CanShu_QianJiao& in_data)
{
	data_base = in_data;
	is_lastest = 0;
}

void Cal_QDM::set_Range(double in_start, int in_end)
{
	range_start = in_start;
	range_end = in_end;
}

void Cal_QDM::set_Sample(double in_len, int in_ang)
{
	sample_len = in_len;
	sample_ang = in_ang;
}

void Cal_QDM::init_data()
{
	//1 设置向前关联-需要相应的表
	//从list获取cal_xx时，进行计算，计算前检查是否计算(增加标志位 7.21
	ptr_lx = ptr_tool->ptr_list_lx->get_obj(data_base.luoxuan_order);

	if (error_message_global != 0)
	{
		return;
	}

	Cal_LouXuan ls_lx = *ptr_lx;
	ls_lx.Range(range_start, range_end);
	ls_lx.Sample(sample_len, sample_ang);

	//判断螺旋-槽的类型
	int ls_lx_type = ptr_tool->ptr_list_lx->get_n_lx_type(data_base.luoxuan_order);
	//直槽或斜槽
	if (ls_lx_type == 0 || ls_lx_type == 1)
	{
		cal_main_data_by_zhi_or_xie(&ls_lx);

		is_lastest = 1;
		return;
	}

	//螺旋槽
	//2 计算主数据
	if (data_base.type == 0) //法向前角
	{
		int count_p = ls_lx.n_P();

		//将前角矩阵插值好，遍历直接取
		vec qianjiao_v(count_p, fill::zeros);
		qianjiao_v = cal_qianjiao_v_by_B_n(&ls_lx);

		cal_main_data_by_n_v_qianjiao(&ls_lx, qianjiao_v);

	}
	else//径向前角
	{
		int count_p = ls_lx.n_P();

		//将前角矩阵插值好，遍历直接取
		vec qianjiao_v(count_p, fill::zeros);
		qianjiao_v = cal_qianjiao_v_by_B_r(&ls_lx);

		cal_main_data_by_r_v_qianjiao(&ls_lx, qianjiao_v);
	}

	is_lastest = 1;
}

void Cal_QDM::add_son(Miller_GX_Base* in_ptr)
{
	v_GL_GX.push_back(in_ptr);
}

void Cal_QDM::cal_son_last_state()
{
	if (is_lastest == 0)
	{
		for (size_t i = 0; i < v_GL_GX.size(); i++)
		{
		//	v_GL_GX[i]->is_lastest = 0;
		}
	}
}


void Cal_QDM::del_guanxi_GL_GX(Miller_GX_Base* p)
{
	for (auto iter = v_GL_GX.begin(); iter != v_GL_GX.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_GX.erase(iter);
			break;
		}
	}
}

void Cal_QDM::add_guanxi_GL_GX(Miller_GX_Base* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_GX.push_back(p);
	}
}

int Cal_QDM::guanxi_exist(Miller_GX_Base* p)
{
	for (size_t i = 0; i < v_GL_GX.size(); i++)
	{
		if (p == v_GL_GX[i])
		{
			return i;
		}
	}
	return -1;
}

//返回点的数量

inline int Cal_QDM::n_P()
{
	return Data_Of_Points.n_cols;
}

vec Cal_QDM::BG_P(int i)
{
	return Data_Of_Points.col(i).rows(0, 2);
}

//返回全部的点坐标

inline mat Cal_QDM::BG_P()
{
	return Data_Of_Points.rows(0, 2);
}

//返回第i个点处的X

inline vec Cal_QDM::BG_X(int i)
{
	return Data_Of_Points.col(i).rows(3, 5);
}

inline vec Cal_QDM::BG_Y(int i)
{
	return Data_Of_Points.col(i).rows(6, 8);
}

inline vec Cal_QDM::BG_Z(int i)
{
	return Data_Of_Points.col(i).rows(9, 11);
}

//返回第i个点处的前刀面坐标系 3*3

inline mat33 Cal_QDM::BG_SYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = BG_X(i);
	ans.col(1) = BG_Y(i);
	ans.col(2) = BG_Z(i);

	return ans;
}

//返回第i个点处的长度坐标

inline double Cal_QDM::Lenth_At_Point(int i)
{
	return Data_Of_Points(12, i) * 0.001;
}



inline Cal_QDM::Cal_QDM(Tool_Base* in_ptr, CanShu_QianJiao& in_data)
{
	ptr_tool = in_ptr;
	set_base_data(in_data);
	init_data();
	v_GL_GX.clear();
}


Cal_QDM::Cal_QDM()
{
	ptr_tool = nullptr;
	ptr_lx = nullptr;
	Data_Of_Points.reset();
	Data_Of_Points.reshape(13, 0);
	v_GL_GX.clear();
}

Cal_QDM::~Cal_QDM()
{
}

vec Cal_QDM::cal_qianjiao_v_by_B_n(Cal_LouXuan* ls_lx)
{
	vec qianjiao_v(ls_lx->n_P(), fill::zeros);
	double lenth = ls_lx->Lenth();
	for (size_t i = 0; i < ls_lx->n_P(); i++)
	{
		qianjiao_v(i) = data_base.b_qianjiao_n.get(ls_lx->Lenth_At_Point(i) / lenth);
	}
	return qianjiao_v;
}

vec Cal_QDM::cal_qianjiao_v_by_B_r(Cal_LouXuan* ls_lx)
{
	vec qianjiao_v(ls_lx->n_P(), fill::zeros);
	double lenth = ls_lx->Lenth();
	for (size_t i = 0; i < ls_lx->n_P(); i++)
	{
		qianjiao_v(i) = data_base.b_qianjiao_r.get(ls_lx->Lenth_At_Point(i) / lenth);
	}
	return qianjiao_v;
}

inline void Cal_QDM::cal_main_data_by_n_v_qianjiao(Cal_LouXuan* ls_lx, vec& in_v_qina)
{
	int count_p = in_v_qina.n_rows;
	Data_Of_Points = zeros(13, count_p);
	//增加标志位，使计算面数据反向 8.16
	if (luo_or_duan == 0)
	{
		for (int i = 0; i < count_p; i++)
		{
			vec ls_p = ls_lx->BG_P(i);
			double ls_len = ls_lx->Lenth_At_Point(i);

			mat33 ls_sys;
			//如果是直槽或者斜槽
			if (ls_lx->data_base.type_cao == 0 || ls_lx->data_base.type_cao == 1)
			{
				//螺旋的法0后坐标系，转对应前角
				ls_sys = ls_lx->BG_nSYS(0);
			}
			else
			{
				//螺旋的法0后坐标系，转对应前角
				ls_sys = ls_lx->BG_nSYS(i);
			}
			ls_sys = ls_sys * tcRotZ(3, 180.0) * tcRotX(3, -90.0 - in_v_qina(i));

			Data_Of_Points.submat(0, i, 2, i) = ls_p;
			Data_Of_Points.submat(3, i, 5, i) = ls_sys.col(0);
			Data_Of_Points.submat(6, i, 8, i) = ls_sys.col(1);
			Data_Of_Points.submat(9, i, 11, i) = ls_sys.col(2);
			Data_Of_Points(12, i) = (double)i;

		}
	}
	//球头槽或端齿槽、刀柄到刀尖
	else
	{
		for (int i = count_p - 1; i >= 0; i--)
		{
			vec ls_p = ls_lx->BG_P(i);
			double ls_len = ls_lx->Lenth_At_Point(i);

			//螺旋的法0后坐标系，转对应ls_lx前角
			mat33 ls_sys = ls_lx->BG_nSYS(i);

			ls_sys = ls_sys * tcRotZ(3, 180.0) * tcRotX(3, -90.0 + in_v_qina(i));

			Data_Of_Points.submat(0, i, 2, i) = ls_p;
			Data_Of_Points.submat(3, i, 5, i) = ls_sys.col(0);
			Data_Of_Points.submat(6, i, 8, i) = ls_sys.col(1);
			Data_Of_Points.submat(9, i, 11, i) = ls_sys.col(2);
			Data_Of_Points(12, i) = (double)i;

		}
	}
}

inline void Cal_QDM::cal_main_data_by_r_v_qianjiao(Cal_LouXuan* ls_lx, vec& in_v_qina)
{
	int count_p = in_v_qina.n_rows;
	Data_Of_Points = zeros(13, count_p);
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = ls_lx->BG_P(i);
		double ls_len = ls_lx->Lenth_At_Point(i);

		//螺旋的法0后坐标系，转对应前角
		vec3 ls_y ;//0前角线方向
		

		//如果是直槽或者斜槽
		if (ls_lx->data_base.type_cao == 0 || ls_lx->data_base.type_cao == 1)
		{
			ls_y = -ls_lx->BG_r_arrow(0);//0前角线方向
		}
		else
		{
			ls_y = -ls_lx->BG_r_arrow(i);//0前角线方向
		}
		ls_y = tcRotX(3, -in_v_qina(i)) * ls_y;

		vec3 ls_t = -ls_lx->BG_nX(i);//刃线切向

		vec3 ls_z = normalise(cross(ls_t, ls_y));//法向

		vec3 ls_x = normalise(cross(ls_y, ls_z));

		Data_Of_Points.submat(0, i, 2, i) = ls_p;
		Data_Of_Points.submat(3, i, 5, i) = ls_x;
		Data_Of_Points.submat(6, i, 8, i) = ls_y;
		Data_Of_Points.submat(9, i, 11, i) = ls_z;
		Data_Of_Points(12, i) = (double)i;
	}
}

void Cal_QDM::cal_main_data_by_zhi_or_xie(Cal_LouXuan* ls_lx)
{
	int count_p = ls_lx->n_P();
	Data_Of_Points = zeros(13, count_p);

	//开槽直槽斜槽用第一个点的法向 25.11.10
	vec3 ls_y = -ls_lx->BG_r_arrow(0);//0前角线方向
	double ang_qian = ls_lx->get_zhi_or_xie_ang_qian();
	ls_y = tcRotX(3, -ang_qian) * ls_y; 

	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = ls_lx->BG_P(i);


		vec3 ls_t = -ls_lx->BG_nX(i);//刃线切向

		vec3 ls_z = normalise(cross(ls_t, ls_y));//法向

		vec3 ls_x = normalise(cross(ls_y, ls_z));

		Data_Of_Points.submat(0, i, 2, i) = ls_p;
		Data_Of_Points.submat(3, i, 5, i) = ls_x;
		Data_Of_Points.submat(6, i, 8, i) = ls_y;
		Data_Of_Points.submat(9, i, 11, i) = ls_z;
		Data_Of_Points(12, i) = (double)i;
	}
}

inline void Cal_QDM::speak_father_del_guanxi()
{

}


inline int Cal_QDM::del_self()
{
	if (v_GL_GX.size() == 0)
	{
	}
	else
	{
		return 1;
	}
	speak_father_del_guanxi();
	delete this;
	return 0;
}

void Cal_QDM::sel_a_lx_id(int in_id)
{
	data_base.luoxuan_order = in_id;
	ptr_lx = ptr_tool->ptr_list_lx->get_obj(data_base.luoxuan_order);
	ptr_lx->init_data();
}

void Cal_QDM::Range(double in_start, double in_end)
{
	int count_p = n_P();

#pragma region 确定起点和终点
	double len_all = Lenth_At_Point(count_p - 1); //25.11.11

	//将型线长度的范围转化为编号的范围
	double a, b;
	//a = in_start / 100.0 * (double)count_p;
	//b = in_end / 100.0 * (double)count_p;
	a = in_start / 100.0 * len_all;
	b = in_end / 100.0 * len_all;
	//记录与start和end对应的编号值的位置，存于c，d
	int c = 0, d = 0;
	//寻找起点
	for (int i = 0; i < count_p; i++)
	{
		//如果型线编号符合要求则存于c中，并且d变为1，不再计算
		if (Lenth_At_Point(i) >= a) //取长度坐标判断
		{
			c = i;
			break;
		}
		if (Lenth_At_Point(i) == count_p - 1)
		{
			throw - 1;//没找到起点
		}
	}
	//寻找终点
	for (int i = 0; i < count_p - c - 1; i++)
	{

		if (Lenth_At_Point(count_p - i - 1) <= b)
		{
			d = count_p - i - 1;
			break;
		}
		//如果到了最后一个点，最后一个点为终点
		if (i == count_p - c - 1)
		{
			throw - 1;//没有找到终点
		}
	}
#pragma endregion 

#pragma region 修改点数据矩阵
	//跟新点数据矩阵
	Data_Of_Points = Data_Of_Points.cols(c, d);
#pragma endregion
}

void Cal_QDM::Sample(double in_len, double in_ang)
{
#pragma region 抽样数据
	//计算角度条件的cos值
	double cosjiaodu;
	cosjiaodu = cos(in_ang / 180.0 * datum::pi);

	//建立辅助变量
	int ChouYangStart = 0, ChouYangEnd = 0;
	vec lsSampleVector_N1;
	vec lsSampleVector_N2;
	double changdu1 = 0.0;
	double changdu2 = 0.0;

	//用于临时存放抽样数据
	mat B = Data_Of_Points;
	//抽样结果坐标
	int j = 0;

	int count_p = n_P();
	//对点数据矩阵进行抽样
	for (int i = 0; i < count_p; i++)
	{
		//记录上一个抽样点的长度坐标
		changdu1 = Lenth_At_Point(ChouYangStart);
		//记录当前点的长度坐标
		changdu2 = Lenth_At_Point(i);

		//记录上一个抽样点的切向
		lsSampleVector_N1 = BG_X(ChouYangStart);
		//记录当前点的切向
		lsSampleVector_N2 = BG_X(i);

		//如果为第一个点或最后一个点 抽样
		if (i == 0 || i == count_p - 1)
		{
			B.col(j) = Data_Of_Points.col(i);
			ChouYangStart = i;
			++j;
		}
		else
		{
			//若长度达到抽样条件，抽样
			if (abs(changdu2 - changdu1) >= in_len)
			{
				B.col(j) = Data_Of_Points.col(i);
				ChouYangStart = i;
				++j;
			}
			//若角度达到抽样条件，抽样
			else if (dot(lsSampleVector_N1, lsSampleVector_N2) <= cosjiaodu)
			{
				B.col(j) = Data_Of_Points.col(i); 
				ChouYangStart = i;
				++j;
			}
		}
	}
	//复位型线矩阵
	Data_Of_Points.reset();
	//更新数据矩阵
	Data_Of_Points = B.cols(0, j - 1);
	//更新点的数量
	//d_n_P = (int)Data_Of_Points.n_rows;
	//长度和长度坐标不变
#pragma endregion
}

inline Cal_QDM Cal_QDM::copy_main_data()
{
	Cal_QDM ans;
	ans.Data_Of_Points = Data_Of_Points;
	return ans;
}


inline void Cal_XinHouMian::set_base_data(CanShu_XinHouMian& in_data)
{
	data_base = in_data;
	is_lastest = 0;
}

void Cal_XinHouMian::init_data()
{
	mat ls_vp;
	mat ls_vt;

	//计算初始曲线
	//	选择0 - 通过dxf获得：
	if (data_base.type_line == 0)
	{
		Cal_XingXian* ls_xx = ptr_tool->ptr_list_xx->get_obj(data_base.xingxian_pos);
		ls_vp = ls_xx->BG_P();
		ls_vt = ls_xx->BG_T();
	}
	//	选择1 - 参数得到
	else
	{
		//芯厚面需要前后左右都延长一定范围，确保砂轮有正确相交条件 7.22

		//根据槽类型构造不同芯厚面引导线 8.7
		//螺旋槽
		if (data_base.type_cao == 0)
		{
			vec3 start_p = { 0.0, data_base.start_R, 0.0 };
			vec3 ls_t = tcRotZ(3, data_base.ang_zhui) * tcX(3);//向刀柄
			vec3 end_p = start_p + ls_t * data_base.len;
			start_p = start_p + (-ls_t) * 50.0;

			//直线两个点就行
			ls_vp.insert_cols(ls_vp.n_cols, start_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);

			ls_vp.insert_cols(ls_vp.n_cols, end_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);
		}
		//1-平底端齿槽
		else if (data_base.type_cao == 1)
		{
			vec3 start_p = { data_base.high_up, 0.0, 10.0 };
			vec3 ls_t = tcRotZ(3,  90.0 - data_base.ang_cao) * tcX(3);
			vec3 end_p = start_p + ls_t * 50.0; ////逆路径，
			//start_p = start_p + (-ls_t) * 50.0; 

			//直线两个点就行
			ls_vp.insert_cols(ls_vp.n_cols, start_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);

			ls_vp.insert_cols(ls_vp.n_cols, end_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);
		}
		//2 - 球头槽
		else if (data_base.type_cao == 2)
		{
			vec3 start_p = {  0.0, data_base.r_xin, 0.0 };
			vec3 o_t = { data_base.r_qiu - data_base.high_o, 0.0, 0.0 }; //圆心偏置

			double delta_ang = 1.0;
			int count_p = (data_base.ang_up - data_base.ang_down) / delta_ang;

			//下端直线
			vec3 ls_t = tcRotZ(3, data_base.ang_down) * (tcX(3));
			vec3 ls_p = start_p + (ls_t) * 100.0 + o_t;
			ls_vp.insert_cols(ls_vp.n_cols, ls_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);

			//圆弧
			for (int i = 0; i < count_p; i++)
			{
				vec3 ls_p = tcRotZ(3, data_base.ang_down + i * delta_ang) * start_p + o_t;
				vec3 ls_t = tcRotZ(3, data_base.ang_down + i * delta_ang) * (tcX(3)); //向刀柄

				ls_vp.insert_cols(ls_vp.n_cols, ls_p);
				ls_vt.insert_cols(ls_vt.n_cols, ls_t);
			}

			//上端直线
			while (true)
			{
				vec3 ls_end_p = ls_vp.col(ls_vp.n_cols - 1);
				vec3 ls_t = tcRotZ(3, data_base.ang_up) * (tcX(3));
				vec3 ls_p = ls_end_p + (-ls_t) * 1.0 ;

				if (ls_p(1) < 0.0)
				{
					break;
				}
				ls_vp.insert_cols(ls_vp.n_cols, ls_p);
				ls_vt.insert_cols(ls_vt.n_cols, ls_t);
			}

			//起点终点反向 》》控制芯厚面法向 8.16
			ls_vp = fliplr(ls_vp);
			ls_vt = fliplr(ls_vt);

		}
		//3 - 圆角前刀面
		else if (data_base.type_cao == 2)
		{
			vec3 start_p = {  0.0, data_base.r_xin_p, 0.0 };
			vec3 ls_t = tcRotZ(3, data_base.ang_p) * tcX(3);
			vec3 end_p = start_p + ls_t * 10.0; //（估计值）
			start_p = start_p + (-ls_t) * 50.0;

			//直线两个点就行
			ls_vp.insert_cols(ls_vp.n_cols, start_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);

			ls_vp.insert_cols(ls_vp.n_cols, end_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);
		}
		//4-成型端齿槽 10.10
		else 
		{
			vec3 start_p = { data_base.start_len_cx, data_base.start_R_cx, 0.0 };
			vec3 end_p = { data_base.end_len_cx, data_base.end_R_cx, 0.0 };
			vec3 ls_t = normalise(end_p - start_p); //向刀柄
			end_p = end_p + ls_t * 50.0; //（估计值）

			//直线两个点就行
			ls_vp.insert_cols(ls_vp.n_cols, start_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);

			ls_vp.insert_cols(ls_vp.n_cols, end_p);
			ls_vt.insert_cols(ls_vt.n_cols, ls_t);
		}

	}


	//曲线到面
	//平面
	if (data_base.type_mian == 0)
	{
		vec ls_p0 = { 0.0,0.0, data_base.len_lashen }; 
		vec ls_p1 = { 0.0,0.0,-data_base.len_lashen };
		vec ls_t = -tcZ(3);

		mat ydx_p(3, 2, fill::zeros);
		mat ydx_t(3, 2, fill::zeros);
		ydx_p.col(0) = ls_p0;
		ydx_p.col(1) = ls_p1;
		ydx_t.col(0) = ls_t;
		ydx_t.col(1) = ls_t;

		obj_qm = Get_Bezier_Curve3_QM_SL(ls_vp, ls_vt, ydx_p, ydx_t);
	}
	//回转面
	else
	{
		vec zhou_p = { 0.0,data_base.len_huizhuan_pianyi,0.0 };
		vec zhou_t = { 1.0,0.0,0.0 };

		//tset 8.11
		//ls_data.each_col() += O;
		//ls_vp.each_col() *= tcRotX(3, 180.0);
		for (int i = 0; i < ls_vp.n_cols; i++)
		{
			ls_vp.col(i) = tcRotX(3, data_base.ang_huizhuan) * ls_vp.col(i);
			ls_vt.col(i) = tcRotX(3, data_base.ang_huizhuan) * ls_vt.col(i);
		}
		double delta_ang = 2.0 * data_base.ang_huizhuan / 20.0;

		obj_qm = Get_Bezier_Curve3_QM_HZ(ls_vp, ls_vt, zhou_p, -zhou_t, 20, delta_ang);
	}

	is_lastest = 1;
}

void Cal_XinHouMian::cal_son_last_state()
{
	if (is_lastest == 0)
	{
		//for (size_t i = 0; i < v_GL_LX.size(); i++)
		//{
		//	v_GL_LX[i]->is_lastest = 0;
		//}
		//for (size_t i = 0; i < v_GL_HJ.size(); i++)
		//{
		//	v_GL_HJ[i]->is_lastest = 0;
		//}
	}
}

inline void Cal_XinHouMian::get_data(Bezier_Curve3_QM& ans_data)
{
	ans_data = obj_qm;
}

Cal_XinHouMian::Cal_XinHouMian()
{
}

Cal_XinHouMian::~Cal_XinHouMian()
{
}

inline Cal_XinHouMian::Cal_XinHouMian(Tool_Base* in_ptr, CanShu_XinHouMian& in_data)
{
	ptr_tool = in_ptr;
	set_base_data(in_data);
	init_data();
}

//void Cal_Houjiao::set_base_data(int id_xx, Cal_HouJiao& in_data)
//{
//	xingxian_id = id_xx;
//	data_base = in_data;
//}
//
//void Cal_Houjiao::add_son(Cal_HDM* in_ptr)
//{
//	v_GL_HDM.push_back(in_ptr);
//}
//
//double Cal_Houjiao::BG_width_1()
//{
//	return Data_Of_Points(1,0);
//}
//
//double Cal_Houjiao::BG_width_2()
//{
//	return Data_Of_Points(2, 0);
//}
//
//double Cal_Houjiao::BG_width_3()
//{
//	return Data_Of_Points(3, 0);
//}
//
//double Cal_Houjiao::BG_n_ang_hdm1(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(1,i);
//}
//
//double Cal_Houjiao::BG_a_ang_hdm1(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(2, i);
//}
//
//double Cal_Houjiao::BG_d_ang_hdm1(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(3, i);
//}
//
//double Cal_Houjiao::BG_n_ang_hdm2(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(4, i);
//}
//
//double Cal_Houjiao::BG_a_ang_hdm2(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(5, i);
//}
//
//double Cal_Houjiao::BG_d_ang_hdm2(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(6, i);
//}
//
//double Cal_Houjiao::BG_n_ang_hdm3(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(7, i);
//}
//
//double Cal_Houjiao::BG_a_ang_hdm3(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(8, i);
//}
//
//double Cal_Houjiao::BG_d_ang_hdm3(int i)
//{
//	i = i + 1; //第一列没存角度
//	return Data_Of_Points(9, i);
//}
//
//Cal_Houjiao::Cal_Houjiao()
//{
//}
//
//Cal_Houjiao::~Cal_Houjiao()
//{
//}


Cal_HDM::Cal_HDM(int id_lx, int id_hj, Tool_Base* in_ptr)
	:rx(id_lx, id_hj, in_ptr)
{
	luoxuan_order = id_lx;
	houjiao_order = id_hj;

	ptr_tool = in_ptr;

	init_data();

	v_GL_GX.clear();
}

inline void Cal_HDM::speak_father_del_guanxi()
{

}

inline int Cal_HDM::del_self()
{
	if (v_GL_GX.size() == 0)
	{
	}
	else
	{
		return 1;
	}
	speak_father_del_guanxi();
	delete this;
	return 0;
}

void Cal_HDM::sel_a_lx_id(int in_id)
{
	luoxuan_order = in_id;
	ptr_lx = ptr_tool->ptr_list_lx->get_obj(luoxuan_order);
}

void Cal_HDM::sel_a_hj_id(int in_id)
{
	houjiao_order = in_id;
	ptr_hj = ptr_tool->ptr_list_hj->get_obj(houjiao_order);
}

//wld20250603
//按照型线百分比取值

inline void Cal_HDM::Range(double in_start, double in_end)
{
	int count_p = n_P();
	double lenth = Lenth_At_Point(n_P() - 1);
#pragma region 确定起点和终点
	//将型线长度的范围转化为编号的范围
	double a, b;
	a = in_start / 100.0 * lenth;
	b = in_end / 100.0 * lenth + 0.0001;
	//记录与start和end对应的编号值的位置，存于c，d
	int c = 0, d = 0;
	//寻找起点
	for (int i = 0; i < count_p; i++)
	{
		//如果型线编号符合要求则存于c中，并且d变为1，不再计算
		if (Lenth_At_Point(i) >= a)
		{
			c = i;
			break;
		}
		if (i == count_p - 1)
		{
			throw - 1;//没找到起点
		}
	}
	//寻找终点
	for (int i = 0; i < count_p - c - 1; i++)
	{

		if (Lenth_At_Point(count_p - i - 1) <= b)
		{
			d = count_p - i - 1;
			break;
		}
		//如果到了最后一个点，最后一个点为终点
		if (i == count_p - c - 1)
		{
			throw - 1;//没有找到终点
		}
	}
#pragma endregion 

#pragma region 修改点数据矩阵
	//跟新点数据矩阵
	Data_Of_Points = Data_Of_Points.cols(c, d);
#pragma endregion
}

//wld20250603
//没有结果

inline void Cal_HDM::Sample(double in_len, double in_ang)
{
#pragma region 抽样数据
	//计算角度条件的cos值
	double cosjiaodu;
	cosjiaodu = cos(in_ang / 180.0 * datum::pi);

	//建立辅助变量
	int ChouYangStart = 0, ChouYangEnd = 0;
	vec lsSampleVector_N1;
	vec lsSampleVector_N2;
	double changdu1 = 0.0;
	double changdu2 = 0.0;

	//用于临时存放抽样数据
	mat B = Data_Of_Points;
	//抽样结果坐标
	int j = 0;

	int count_p = n_P();
	//对点数据矩阵进行抽样
	for (int i = 0; i < count_p; i++)
	{
		//记录上一个抽样点的长度坐标
		changdu1 = Lenth_At_Point(ChouYangStart);
		//记录当前点的长度坐标
		changdu2 = Lenth_At_Point(i);

		//记录上一个抽样点的切向
		lsSampleVector_N1 = HJ1_X(ChouYangStart);
		//记录当前点的切向
		lsSampleVector_N2 = HJ1_X(i);

		//如果为第一个点或最后一个点 抽样
		if (i == 0 || i == count_p - 1)
		{
			B.col(j) = Data_Of_Points.col(i);
			ChouYangStart = i;
			++j;
		}
		else
		{
			//若长度达到抽样条件，抽样
			if (abs(changdu2 - changdu1) >= in_len)
			{
				B.col(j) = Data_Of_Points.col(i);
				ChouYangStart = i;
				++j;
			}
			//若角度达到抽样条件，抽样
			else if (dot(lsSampleVector_N1, lsSampleVector_N2) <= cosjiaodu)
			{
				B.col(j) = Data_Of_Points.col(i);
				ChouYangStart = i;
				++j;
			}
		}
	}

	//复位型线矩阵
	Data_Of_Points.reset();
	//更新数据矩阵
	Data_Of_Points = B.cols(0, j - 1);
	//更新点的数量
	//d_n_P = (int)Data_Of_Points.n_rows;
	//长度和长度坐标不变
#pragma endregion
#pragma endregion
}

//20250603

inline void Cal_HDM::set_luoxuan_id(int id)
{
	luoxuan_order = id;
}

//20250603

inline void Cal_HDM::set_houjiao_id(int id)
{
	houjiao_order = id;
}

inline Cal_HDM Cal_HDM::copy_main_data()
{
	Cal_HDM ans;
	ans.Data_Of_Points = Data_Of_Points;
	return ans;
}

inline void Cal_HDM::set_base_data(int id_lx, int id_hj) //,Cal_hdm_RX& in_data后刀面刃线是计算出来的
{
	//xingxian_id = id_xx;
	luoxuan_order = id_lx;
	houjiao_order = id_hj;
	is_lastest = 0;
}

void Cal_HDM::set_Range(double in_start, int in_end)
{
	range_start = in_start;
	range_end = in_end;
}

void Cal_HDM::set_Sample(double in_len, int in_ang)
{
	sample_len = in_len;
	sample_ang = in_ang;
}

void Cal_HDM::init_data()
{
	//wenlidong1	没有对rx对象赋值

	//0 初始化
	ptr_lx = ptr_tool->ptr_list_lx->get_obj(luoxuan_order);
	ptr_hj = ptr_tool->ptr_list_hj->get_obj(houjiao_order);

	if (error_message_global != 0)
	{
		return;
	}

	//0 初始化
	rx.ptr_tool = ptr_tool; //刀指针赋值 8.4
	rx.data_base.luoxuan_pos = luoxuan_order;
	rx.data_base.xingxian_pos = ptr_hj->data_base.guanlian_xx_id;
	rx.luo_or_duan = luo_or_duan;
	//成型刀需要螺旋与后角里的型线求交得到后刀面刃线 8.22
	rx.need_jiao_hdm = need_jiao_hdm;
	rx.set_range_and_sample(range_start, range_end, sample_len, sample_ang);
	rx.init_data();

	if (error_message_global != 0)
	{
		return;
	}

	//0 准备
	//Cal_XingXian* ls_xx = ptr_hj->ptr_xx;
	//int count = ls_xx->n_P();
	int count = rx.n_P();
	Data_Of_Points = zeros(37, count);

	//计算初始参考点
	for (size_t i = 0; i < count; i++)
	{
		//
		set_HJ1_P(i, rx.BG_P(i));
	}

	//第一后角：计算HDM坐标系和下一个点
	{
		//法后角
		if (ptr_hj->type(0) == 0)
		{
			for (size_t i = 0; i < count; i++)
			{
				//
				mat ls_sys1 = rx.BG_nSYS(i);
				ls_sys1 = ls_sys1 * tcRotX(3, -ptr_hj->HJ1_r_or_n(i));
				set_HJ1_SYS(i, ls_sys1);

				//
				double width = ptr_hj->HJ1_w(i);
				vec3 ls_p = rx.BG_P(i) + ls_sys1.col(1) * width;
				set_HJ2_P(i, ls_p);
			}
		}
		//径向+轴向
		else
		{
			for (size_t i = 0; i < count; i++)
			{

				vec test_x = rx.Data_Of_Points.col(i).subvec(9, 11);
				vec test_y = rx.Data_Of_Points.col(i).subvec(12, 14);
				vec test_z = rx.Data_Of_Points.col(i).subvec(15, 17);

				//
				mat ls_sys1 = rx.BG_zSYS(i);
				double jinghoujiao = ptr_hj->HJ1_r_or_n(i);
				double zhouhoujiao = ptr_hj->HJ1_a(i);  


				//
				double z_xishu = -dot(ls_sys1.col(1), tcX(3));
				vec3 ls_y= 
					tcRotY(3, z_xishu * zhouhoujiao)
					* tcRotX(3, jinghoujiao) 
					* ls_sys1.col(2);
			
				vec ls_t = rx.BG_zX(i); //切向
				vec ls_z = normalise(cross(ls_y, ls_t)); //后刀面法向
				vec ls_x = normalise(cross(ls_y, ls_z));

				//增加相位角变换
				double xiangwei = rx.BG_zP(i)(2);

				mat33 ans_sys = eye(3, 3);
				ans_sys.col(0) = ls_x;
				ans_sys.col(1) = ls_y;
				ans_sys.col(2) = ls_z;
				ans_sys = tcRotX(3, xiangwei) * ans_sys;

				set_HJ1_SYS(i, ans_sys);

				//
				double width = ptr_hj->HJ1_w(i);
				vec3 ls_p = rx.BG_P(i) + ans_sys.col(1) * width;
				set_HJ2_P(i, ls_p);
			}
		}
	}

	//后刀面坐标系输出点、Z轴长，y轴短 8.26
	{
		//std::ofstream outFile1("points_hdm_sys.txt");
		//if (!outFile1.is_open()) 
		//{
		//	std::cerr << "无法打开文件！" << std::endl;
		//}

		//// 设置输出格式（6位小数，科学计数法）
		//outFile1 << std::scientific << std::setprecision(6);


		//for (int i = 0; i < count; i++)
		//{
		//	vec point = HJ1_P(i);
		//	// 写入文件：x y z（每行一个点）
		//	outFile1 << point(0) << " " << point(1) << " " << point(2) << "\n";

		//	vec ls_z = HJ1_Z(i);
		//	for (int j = 1; j < 6; j++)
		//	{
		//		vec ls_p = ls_z * j * 0.3 + point; 
		//		outFile1 << ls_p(0) << " " << ls_p(1) << " " << ls_p(2) << "\n";
		//	}

		//	vec ls_y = HJ1_Y(i);
		//	for (int j = 1; j < 4; j++)
		//	{
		//		vec ls_p = ls_y * j * 0.1 + point;
		//		outFile1 << ls_p(0) << " " << ls_p(1) << " " << ls_p(2) << "\n";
		//	}
		//}
		//outFile1.close();
		
	}

	//第二后角：计算HDM坐标系和下一个点
	{
		//法后角
		if (ptr_hj->type(0) == 0)
		{
			for (size_t i = 0; i < count; i++)
			{
				//
				//set_HJ1_P(i, rx.BG_P(i));
				//wenlidong1 增加相位角计算
				double xiangwei2 = get_xiangwei(HJ2_P(i));
				double xiangwei1 = get_xiangwei(HJ1_P(i));
				double xiangwei = xiangwei2 - xiangwei1;


				//
				mat ls_sys1 = rx.BG_nSYS(i);
				ls_sys1 = tcRotX(3,xiangwei)* ls_sys1 * tcRotX(3, -ptr_hj->HJ2_r_or_n(i)); //2后角 法后角值
				set_HJ2_SYS(i, ls_sys1);

				//
				double width = ptr_hj->HJ2_w(i);
				vec3 ls_p = HJ2_P(i) + ls_sys1.col(1) * width;
				set_HJ3_P(i, ls_p);
			}
		}
		//径向+轴向
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				//
				//set_HJ1_P(i, rx.BG_P(i));

				//
				mat ls_sys1 = rx.BG_zSYS(i);
				double jinghoujiao = ptr_hj->HJ2_r_or_n(i);
				double zhouhoujiao = ptr_hj->HJ2_a(i);

				double z_xishu = -dot(ls_sys1.col(1), tcX(3));
				vec3 ls_y =
					tcRotY(3, z_xishu * zhouhoujiao)
					* tcRotX(3, jinghoujiao)
					* ls_sys1.col(2);

				vec ls_t = rx.BG_nX(i); //切向
				vec ls_z = normalise(cross(ls_y, ls_t)); //后刀面法向
				vec ls_x = normalise(cross(ls_y, ls_z));

				mat33 ans_sys = eye(3, 3);
				ans_sys.col(0) = ls_x;
				ans_sys.col(1) = ls_y;
				ans_sys.col(2) = ls_z;

				//wenlidong1 增加相位计算
				double xiangwei = get_xiangwei(HJ2_P(i));
				ans_sys = tcRotX(3,xiangwei) * ans_sys;

				set_HJ2_SYS(i, ans_sys);

				//
				double width = ptr_hj->HJ2_w(i);
				//vec3 ls_p = rx.BG_P(i) + ls_sys1.col(1) * width;
				vec3 ls_p = HJ2_P(i) + ans_sys.col(1) * width;//wenlidong1 
				set_HJ3_P(i, ls_p);

			}
		}
	}

	//第三后角：计算HDM坐标系和下一个点
	{
		//法后角
		if (ptr_hj->type(0) == 0)
		{
			for (size_t i = 0; i < count; i++)
			{
				//
				double xiangwei2 = get_xiangwei(HJ3_P(i));
				double xiangwei1 = get_xiangwei(HJ1_P(i));
				double xiangwei = xiangwei2 - xiangwei1;

				//
				mat ls_sys1 = rx.BG_nSYS(i);
				ls_sys1 = tcRotX(3, xiangwei) * ls_sys1 * tcRotX(3, -ptr_hj->HJ3_r_or_n(i)); //3后角 法后角值
				set_HJ3_SYS(i, ls_sys1);

				//
			}
		}
		//径向+轴向
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				//
				//set_HJ1_P(i, rx.BG_P(i));

				//
				mat ls_sys1 = rx.BG_zSYS(i);
				double jinghoujiao = ptr_hj->HJ3_r_or_n(i);
				double zhouhoujiao = ptr_hj->HJ3_a(i);

				double z_xishu = -dot(ls_sys1.col(1), tcX(3));
				vec3 ls_y =
					tcRotY(3, z_xishu * zhouhoujiao)
					* tcRotX(3, jinghoujiao)
					* ls_sys1.col(2);

				vec ls_t = rx.BG_nX(i); //切向
				vec ls_z = normalise(cross(ls_y, ls_t)); //后刀面法向
				vec ls_x = normalise(cross(ls_y, ls_z));

				mat33 ans_sys = eye(3, 3);
				ans_sys.col(0) = ls_x;
				ans_sys.col(1) = ls_y;
				ans_sys.col(2) = ls_z;

				//wenlidong1 增加相位计算
				double xiangwei = get_xiangwei(HJ3_P(i));
				ans_sys = tcRotX(3, xiangwei) * ans_sys;

				set_HJ3_SYS(i, ans_sys);

				//
				//double width = ptr_hj->Data_Of_Points(5, i);
				////vec3 ls_p = rx.BG_P(i) + ls_sys1.col(1) * width;
				//vec3 ls_p = HJ2_P(i) + ls_sys1.col(1) * width;
				//set_HJ2_P(i, ls_p);
			}
		}
	}

	//计算长度坐标
	for (size_t i = 0; i < count; i++)
	{
		set_length(i, (double)i);
	}

	is_lastest = 1;
}



void Cal_HDM::add_son(Miller_GX_Base* in_ptr)
{
	v_GL_GX.push_back(in_ptr);
}

//返回点的数量

void Cal_HDM::del_guanxi_GL_GX(Miller_GX_Base* p)
{
	for (auto iter= v_GL_GX.begin(); iter != v_GL_GX.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_GX.erase(iter);
			break;
		}
	}
}

void Cal_HDM::add_guanxi_GL_GX(Miller_GX_Base* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_GX.push_back(p);
	}
}

int Cal_HDM::guanxi_exist(Miller_GX_Base* p)
{
	for (size_t i = 0; i < v_GL_GX.size(); i++)
	{
		if (p == v_GL_GX[i])
		{
			return i;
		}
	}
	return -1;
}

int Cal_HDM::n_P()
{
	return Data_Of_Points.n_cols;
}

vec Cal_HDM::HJ1_P(int i)
{
	return Data_Of_Points.col(i).rows(0, 2);
}

vec Cal_HDM::HJ2_P(int i)
{
	return Data_Of_Points.col(i).rows(3, 5);
}

vec Cal_HDM::HJ3_P(int i)
{
	return Data_Of_Points.col(i).rows(6, 8);
}

vec Cal_HDM::HJ1_X(int i)
{
	return Data_Of_Points.col(i).rows(9, 11);
}

vec Cal_HDM::HJ1_Y(int i)
{
	return Data_Of_Points.col(i).rows(12, 14);
}

vec Cal_HDM::HJ1_Z(int i)
{
	return Data_Of_Points.col(i).rows(15, 17);
}

mat33 Cal_HDM::HJ1_SYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = HJ1_X(i);
	ans.col(1) = HJ1_Y(i);
	ans.col(2) = HJ1_Z(i);

	return ans;
}

vec Cal_HDM::HJ2_X(int i)
{
	return Data_Of_Points.col(i).rows(18, 20);
}

vec Cal_HDM::HJ2_Y(int i)
{
	return Data_Of_Points.col(i).rows(21, 23);
}

vec Cal_HDM::HJ2_Z(int i)
{
	return Data_Of_Points.col(i).rows(24, 26);
}

mat33 Cal_HDM::HJ2_SYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = HJ2_X(i);
	ans.col(1) = HJ2_Y(i);
	ans.col(2) = HJ2_Z(i);

	return ans;
}

vec Cal_HDM::HJ3_X(int i)
{
	return Data_Of_Points.col(i).rows(27, 29);
}

vec Cal_HDM::HJ3_Y(int i)
{
	return Data_Of_Points.col(i).rows(30, 32);
}

vec Cal_HDM::HJ3_Z(int i)
{
	return Data_Of_Points.col(i).rows(33, 35);
}

mat33 Cal_HDM::HJ3_SYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = HJ3_X(i);
	ans.col(1) = HJ3_Y(i);
	ans.col(2) = HJ3_Z(i);

	return ans;
}


//返回第i个点处的长度坐标

double Cal_HDM::Lenth_At_Point(int i)
{
	return Data_Of_Points(36, i) * 0.001;
}

//设置第2后刀面第i个点处的后面坐标系  3阶
inline void Cal_HDM::set_HJ2_SYS(int i, mat in_sys)
{
	Data_Of_Points.col(i).subvec(18, 20) = in_sys.col(0);
	Data_Of_Points.col(i).subvec(21, 23) = in_sys.col(1);
	Data_Of_Points.col(i).subvec(24, 26) = in_sys.col(2);
}

//设置第1后刀面第i个点处的后面坐标系  3阶
inline void Cal_HDM::set_HJ1_SYS(int i, mat in_sys)
{
	Data_Of_Points.col(i).subvec(9, 11) = in_sys.col(0);
	Data_Of_Points.col(i).subvec(12, 14) = in_sys.col(1);
	Data_Of_Points.col(i).subvec(15, 17) = in_sys.col(2);
}

//设置第3后刀面第i个点的坐标，3阶
inline void Cal_HDM::set_HJ3_P(int i, vec in_p)
{
	Data_Of_Points.col(i).subvec(6, 8) = in_p;
}

//设置第2后刀面第i个点的坐标，3阶
inline void Cal_HDM::set_HJ2_P(int i, vec in_p)
{
	Data_Of_Points.col(i).subvec(3, 5) = in_p;
}

//设置第1后刀面第i个点的坐标，3阶
inline void Cal_HDM::set_HJ1_P(int i, vec in_p)
{
	Data_Of_Points.col(i).subvec(0, 2) = in_p;
}


//设置第3后刀面第i个点处的后面坐标系  3阶
inline void Cal_HDM::set_HJ3_SYS(int i, mat in_sys)
{
	Data_Of_Points.col(i).subvec(27, 29) = in_sys.col(0);
	Data_Of_Points.col(i).subvec(30, 32) = in_sys.col(1);
	Data_Of_Points.col(i).subvec(33, 35) = in_sys.col(2);
}


//设置第i个点的长度坐标
inline void Cal_HDM::set_length(int i, double in_len)
{
	Data_Of_Points(36, i) = in_len;
}

double Cal_HDM::get_xiangwei(vec p)
{
	vec ls_p = p;
	ls_p(0) = 0.0;
	ls_p = normalise(ls_p);
	double ans = deltaRotAngle(tcY(3), ls_p, tcX(3));
	return ans;
}

void Cal_HDM::set_main_data_by_djjx_rx(mat& ls_rx)
{
	int count_p = ls_rx.n_cols;
	Data_Of_Points = zeros(37, count_p);
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = ls_rx.submat(0, i, 2, i);
		mat ls_sys = ls_rx.submat(0, i, 2, i);

		set_HJ1_P(i, ls_p);
		set_HJ1_SYS(i, ls_sys);
	}
}

Cal_HDM::Cal_HDM()
{
	luoxuan_order = 0;
	houjiao_order = 0;

	ptr_tool = nullptr;
	ptr_lx = nullptr;
	ptr_hj = nullptr;

	Data_Of_Points = zeros(37, 0);
	v_GL_GX.clear();
}

Cal_HDM::~Cal_HDM()
{
}

vec Cal_hdm_RX::cal_cir_plane_jiaodian(vec p, vec n, double m, double R)
{
	double a = n(0);
	double b = n(1);
	double c = n(2);
	double x0 = p(0);
	double y0 = p(1);
	double z0 = p(2);

	double d = -a * x0 - b * y0 - c * z0;

	double x = m;
	double y = -1.0;

	double up_left = -b * (a * m + d);
	double up_rigt = c * sqrt((b * b + c * c) * R * R - (a * m + d) * (a * m + d));
	double down = b * b + c * c;
	if (c < 0)
	{
		y = (up_left - up_rigt) / down;
	}
	else
	{
		y = (up_left + up_rigt) / down;
	}

	double z = -((b * y + (a * m + d)) / c);

	vec ans_p = { x,y,z };
	return ans_p;
}

Cal_hdm_RX::Cal_hdm_RX()
{
	Data_Of_Points = zeros(28, 0);
}

Cal_hdm_RX::~Cal_hdm_RX()
{
}

Cal_hdm_RX::Cal_hdm_RX(int id_lx, int id_hj, Tool_Base* in_ptr)
{
	ptr_tool = in_ptr;

	Cal_HouJiao* ls_hj_ptr = ptr_tool->ptr_list_hj->get_obj(id_hj);
	int ls_xx_id = ls_hj_ptr->data_base.guanlian_xx_id;

	CanShu_hdm_rx ls_canshu;
	ls_canshu.luoxuan_pos = id_lx;
	ls_canshu.xingxian_pos = ls_xx_id;

	set_base_data(ls_canshu);

	init_data();
}

int Cal_LouXuan::n_P()
{
	return Data_Of_Points.n_cols;
}

vec Cal_LouXuan::BG_zP(int i)
{
	return Data_Of_Points.col(i).rows(0, 2);
}

vec Cal_LouXuan::BG_P(int i)
{
	return Data_Of_Points.col(i).rows(3, 5);
}

mat Cal_LouXuan::BG_zP()
{
	return Data_Of_Points.submat(0,0, 2, n_P() - 1);
}

mat Cal_LouXuan::BG_P()
{
	return Data_Of_Points.submat(3, 0, 5, n_P() - 1);
}

double Cal_LouXuan::get_xiangwei(int i)
{
	return Data_Of_Points(2, i);
}

vec Cal_LouXuan::BG_r_arrow(int i)
{
	return Data_Of_Points.col(i).rows(6, 8);
}

//返回第i个点处的柱坐标X方向 3阶

inline vec Cal_LouXuan::BG_zX(int i)
{
	return Data_Of_Points.col(i).rows(9, 11);
}

//返回第i个点处的柱坐标Y方向 3阶

inline vec Cal_LouXuan::BG_zY(int i)
{
	return Data_Of_Points.col(i).rows(12, 14);
}

//返回第i个点处的柱坐标Z方向 3阶

inline vec Cal_LouXuan::BG_zZ(int i)
{
	return Data_Of_Points.col(i).rows(15, 17);
}

//返回第i个点处的柱坐标系 3阶

inline mat33 Cal_LouXuan::BG_zSYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = BG_zX(i);
	ans.col(1) = BG_zY(i);
	ans.col(2) = BG_zZ(i);

	return ans;
}

//返回第i个点处的法坐标X方向 3阶

inline vec Cal_LouXuan::BG_nX(int i)
{
	return Data_Of_Points.col(i).rows(18, 20);
}

//返回第i个点处的法坐标X方向 3阶

inline vec Cal_LouXuan::BG_nY(int i)
{
	return Data_Of_Points.col(i).rows(21, 23);
}

//返回第i个点处的法坐标X方向 3阶

inline vec Cal_LouXuan::BG_nZ(int i)
{
	return Data_Of_Points.col(i).rows(24, 26);
}


//返回第i个点处的法坐标系 3阶

inline mat33 Cal_LouXuan::BG_nSYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = BG_nX(i);
	ans.col(1) = BG_nY(i);
	ans.col(2) = BG_nZ(i);

	return ans;
}

double Cal_LouXuan::Lenth_At_Point(int i)
{
	return Data_Of_Points(27, i) * 0.001;
}

double Cal_LouXuan::Lenth()
{
	return Data_Of_Points(27, n_P()-1);
}

double Cal_LouXuan::get_xiangwei_by_x(double x_in)
{
	double ans_xw = -999.0;
	int count_p = n_P();
	for (int i = 0; i < count_p; i++)
	{
		vec  ls_p = BG_zP(i);
		if (ls_p(0) < x_in || abs(ls_p(0) -x_in) < 0.01)
		{
			ans_xw = get_xiangwei(i);
			continue;
		}
		if (ls_p(0) > x_in )
		{
			break;
		}
	}
	return ans_xw;
}

int Cal_LouXuan::get_index_by_x(double x_in)
{
	int ans_index = -1;
	int count_p = n_P();
	for (int i = 0; i < count_p; i++)
	{
		vec  ls_p = BG_zP(i);
		if (ls_p(0) < x_in || abs(ls_p(0) - x_in) < 0.01)
		{
			ans_index =i;
			continue;
		}
		if (ls_p(0) > x_in)
		{
			break;
		}
	}
	return ans_index;
}

mat33 Cal_LouXuan::BG_nSYS_by_x(double x_in)
{
	int index = -1;
	int count_p = n_P();
	for (int i = 0; i < count_p; i++)
	{
		vec  ls_p = BG_zP(i);
		if (ls_p(0) < x_in || abs(ls_p(0) - x_in) < 0.01)
		{
			index = i;
			continue;
		}
		if (ls_p(0) > x_in)
		{
			break;
		}
	}

	mat33 ans = eye(3, 3);
	ans.col(0) = BG_nX(index);
	ans.col(1) = BG_nY(index);
	ans.col(2) = BG_nZ(index);
	return ans;
}

vec Cal_LouXuan::BG_zhiwen(int i)
{
	return Data_Of_Points.col(i).rows(28, 30);
}

void Cal_LouXuan::cal_jiaoxian_by_xx(Cal_XingXian* ptr_xx, Cal_hdm_RX& ans_rx)
{
	int count = ptr_xx->n_P();
	ans_rx.Data_Of_Points = zeros(28, count);


	//成型刀
	if (ans_rx.need_jiao_hdm == 1)
	{
		for (int i = 0; i < count; i++) 
		{
			//槽面点
			vec ls_p = ptr_xx->BG_P(i);
			double m = ls_p(0);
			double R = ls_p(1);

			//槽面法向
			//螺旋面点数量小于型线点数量，通过x值就近获取 
			int cur_index = get_index_by_x(m);

			double ls_xw = get_xiangwei(cur_index);

			vec plane_n = tcRotX(3,90.0) * BG_zhiwen(cur_index);
			vec plane_p = BG_P(cur_index);

			//需要测试法向反向，结果
			vec ans_p = cal_cir_plane_jiaodian(plane_p, plane_n, m, R);

			if (isnan(ans_p(0)) || isnan(ans_p(1)) || isnan(ans_p(2)))
			{
				error_message_global = -3;
				return;
			}


			//
			ans_rx.Data_Of_Points(0, i) = plane_p(0);
			ans_rx.Data_Of_Points(1, i) = plane_p(1);

			vec cal_p = ans_p;
			cal_p(0) = 0.0;
			cal_p = normalise(cal_p);
			double cal_xw = deltaRotAngle(tcY(3), cal_p, tcX(3));

			//
			ans_rx.Data_Of_Points(2, i) = cal_xw;
			ans_rx.Data_Of_Points.col(i).subvec(3, 5) = ans_p;
			ans_rx.Data_Of_Points.col(i).subvec(6, 8) = cal_p;

			//
			ans_rx.Data_Of_Points.col(i).subvec(9, 11) = ptr_xx->BG_T(i);
			ans_rx.Data_Of_Points.col(i).subvec(15, 17) = tcZ(3);
			ans_rx.Data_Of_Points.col(i).subvec(12, 14) =
				normalise(cross(
					ans_rx.Data_Of_Points.col(i).subvec(15, 17),
					ans_rx.Data_Of_Points.col(i).subvec(9, 11)
				));

			//发0后面坐标系暂时不算

			//
			ans_rx.Data_Of_Points(27, i) = ptr_xx->Lenth_At_Point(i);
		}
	}
	//立铣刀
	else
	{
		//增加后刀面逆路径计算 8.21 
		if (ans_rx.luo_or_duan == 0)
		{
			for (size_t i = 0; i < count; i++)
			{
				//
				vec ls_point = BG_P(i);

				ans_rx.Data_Of_Points(0, i) = ls_point(0);
				ans_rx.Data_Of_Points(1, i) = ls_point(1);
				ans_rx.Data_Of_Points(2, i) = get_xiangwei(i);

				//
				vec ls_point1 = tcRotX(3, ans_rx.Data_Of_Points(2, i)) * ls_point;
				ans_rx.Data_Of_Points.col(i).subvec(3, 5) = ls_point1;

				//
				ls_point1(0) = 0.0;
				ans_rx.Data_Of_Points.col(i).subvec(6, 8) = normalise(ls_point1);

				//
				ans_rx.Data_Of_Points.col(i).subvec(9, 11) = ptr_xx->BG_T(i);
				ans_rx.Data_Of_Points.col(i).subvec(15, 17) = tcZ(3);
				ans_rx.Data_Of_Points.col(i).subvec(12, 14) =
					normalise(cross(
						ans_rx.Data_Of_Points.col(i).subvec(15, 17),
						ans_rx.Data_Of_Points.col(i).subvec(9, 11)
					));

				//发0后面坐标系暂时不算

				//
				ans_rx.Data_Of_Points(27, i) = Lenth_At_Point(i);
			}
		}
		//端
		else
		{
			for (int j = count - 1, i = 0; j >= 0; j--, i++)
			{
				//
				vec ls_point = BG_P(j);

				ans_rx.Data_Of_Points(0, i) = ls_point(0);
				ans_rx.Data_Of_Points(1, i) = ls_point(1);
				ans_rx.Data_Of_Points(2, i) = get_xiangwei(i);

				//
				vec ls_point1 = tcRotX(3, ans_rx.Data_Of_Points(2, i)) * ls_point;
				ans_rx.Data_Of_Points.col(i).subvec(3, 5) = ls_point1;

				//
				ls_point1(0) = 0.0;
				ans_rx.Data_Of_Points.col(i).subvec(6, 8) = normalise(ls_point1);

				//
				ans_rx.Data_Of_Points.col(i).subvec(9, 11) = ptr_xx->BG_T(j);
				ans_rx.Data_Of_Points.col(i).subvec(15, 17) = tcZ(3);
				ans_rx.Data_Of_Points.col(i).subvec(12, 14) =
					normalise(cross(
						ans_rx.Data_Of_Points.col(i).subvec(15, 17),
						ans_rx.Data_Of_Points.col(i).subvec(9, 11)
					));

				vec test_x = ans_rx.Data_Of_Points.col(i).subvec(9, 11);
				vec test_y = ans_rx.Data_Of_Points.col(i).subvec(12, 14);
				vec test_z = ans_rx.Data_Of_Points.col(i).subvec(15, 17);

				//发0后面坐标系暂时不算

				//
				ans_rx.Data_Of_Points(27, i) = (double)i;
			}
		}
	}


	//法0后刀面坐标系计算
	if (ans_rx.luo_or_duan == 0)
	{
		for (size_t i = 0; i < count - 1; i++)
		{
			vec3 ls_p1 = ans_rx.Data_Of_Points.col(i).subvec(3, 5);
			vec3 ls_p2 = ans_rx.Data_Of_Points.col(i + 1).subvec(3, 5);
			vec3 ls_Rvec = ans_rx.Data_Of_Points.col(i).subvec(6, 8);
			vec3 ls_vec1_x = normalise(ls_p2 - ls_p1);
			vec3 ls_vec3_z = normalise(
				cross(
					ls_vec1_x,
					normalise(cross(tcX(3), ls_Rvec)
					)
				)
			);
			vec3 ls_vec2_y = normalise(cross(ls_vec3_z, ls_vec1_x));
			ans_rx.Data_Of_Points.col(i).subvec(18, 20) = ls_vec1_x;
			ans_rx.Data_Of_Points.col(i).subvec(21, 23) = ls_vec2_y;
			ans_rx.Data_Of_Points.col(i).subvec(24, 26) = ls_vec3_z;
		}

		ans_rx.Data_Of_Points.col(count - 1).subvec(18, 20) = ans_rx.Data_Of_Points.col(count - 2).subvec(18, 20);
		ans_rx.Data_Of_Points.col(count - 1).subvec(21, 23) = ans_rx.Data_Of_Points.col(count - 2).subvec(21, 23);
		ans_rx.Data_Of_Points.col(count - 1).subvec(24, 26) = ans_rx.Data_Of_Points.col(count - 2).subvec(24, 26);

	}
	else
	{
		for (int i = count - 1; i > 0; i--)
		{
			vec3 ls_p1 = ans_rx.Data_Of_Points.col(i).subvec(3, 5);
			vec3 ls_p2 = ans_rx.Data_Of_Points.col(i - 1).subvec(3, 5);
			vec3 ls_Rvec = ans_rx.Data_Of_Points.col(i).subvec(6, 8);
			vec3 ls_vec1_x = normalise(ls_p2 - ls_p1);
			vec3 ls_vec3_z = normalise(
				cross(
					ls_vec1_x,
					normalise(cross(tcX(3), ls_Rvec)
					)
				)
			);
			vec3 ls_vec2_y = normalise(cross(ls_vec3_z, ls_vec1_x));
			ans_rx.Data_Of_Points.col(i).subvec(18, 20) = ls_vec1_x;
			ans_rx.Data_Of_Points.col(i).subvec(21, 23) = ls_vec2_y;
			ans_rx.Data_Of_Points.col(i).subvec(24, 26) = ls_vec3_z;
		}

		ans_rx.Data_Of_Points.col(0).subvec(18, 20) = ans_rx.Data_Of_Points.col(1).subvec(18, 20);
		ans_rx.Data_Of_Points.col(0).subvec(21, 23) = ans_rx.Data_Of_Points.col(1).subvec(21, 23);
		ans_rx.Data_Of_Points.col(0).subvec(24, 26) = ans_rx.Data_Of_Points.col(1).subvec(24, 26);

	}
}


//p：平面点，n平面法向，m圆的长度坐标，R圆半径

inline vec Cal_LouXuan::cal_cir_plane_jiaodian(vec p, vec n, double m, double R)
{
	double a = n(0);
	double b = n(1);
	double c = n(2);
	double x0 = p(0);
	double y0 = p(1);
	double z0 = p(2);

	double d = -a * x0 - b * y0 - c * z0;

	double x = m;
	double y = -1.0;

	double up_left = -b * (a * m + d);
	double up_rigt = c * sqrt((b * b + c * c) * R * R - (a * m + d) * (a * m + d));
	double down = b * b + c * c;
	if (c < 0)
	{
		y = (up_left - up_rigt) / down;
	}
	else
	{
		y = (up_left + up_rigt) / down;
	}

	double z = -((b * y + (a * m + d)) / c);

	vec ans_p = { x,y,z };
	return ans_p;
}

inline void Cal_LouXuan::cal_zhicao_vp(vec start_p, double in_qian, double in_xie, mat& ans_vp)
{
	//计算槽面的表达数据

	mat33 start_sys = eye(3, 3) * tcRotX(3, -in_qian) * tcRotY(3, -in_xie);

	vec plane_p = start_p; //槽面点
	vec plane_n = start_sys * tcZ(3); //槽面法向

	int count_p = ptr_xx->n_P();
	ans_vp.reset();
	ans_vp = zeros(3, count_p);
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = ptr_xx->BG_P(i);
		//ls_p(1) = data_base.R_zhi_or_xie; //用螺旋参数中的半径 11.3

		double m = ls_p(0);
		double R = ls_p(1);

		vec ans_p = cal_cir_plane_jiaodian(plane_p, plane_n, m, R);

		ans_vp.col(i) = ans_p;
	}
}

void Cal_LouXuan::cal_main_data_by_points(mat& in_vp, double ang_qian)
{
	int count_p = in_vp.n_cols;
	Data_Of_Points.reset();
	Data_Of_Points = zeros(31, count_p);
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = in_vp.col(i); //直角坐标点

		if (isnan(ls_p(0)) || isnan(ls_p(1)) || isnan(ls_p(2)))
		{
			error_message_global = -1; 
			return;
		}

		//计算相位
		vec cal_p = ls_p;
		cal_p(0) = 0.0;
		cal_p = normalise(cal_p);
		double XW = deltaRotAngle(tcY(3), cal_p, tcX(3));
		vec p_zhu = { ls_p(0), ls_p(1), XW };//柱坐标点

		//半径方向-向外
		vec t_R = normalise(cal_p);	

		//柱坐标系
		vec zhu_X = -ptr_xx->BG_T(i); //X轴：相位0截形的切向
		vec zhu_Y = tcZ(3); //Z轴：	同刀具Z轴
		vec zhu_Z = cross(zhu_X, zhu_Y); //Y轴：

		//法0后面坐标系
		vec ls_T;
		if (i == count_p - 1)
		{
			//vec ls_next = in_vp.col(i + 1);
			ls_T = -Data_Of_Points.col(i - 1).rows(18, 20);
		}
		else
		{
			vec ls_next = in_vp.col(i + 1);
			ls_T = normalise(ls_next - ls_p);
		}
		vec fa_X = -ls_T;//X轴：	刃线切向
		vec fa_Z = normalise( cross(fa_X, normalise(cross(tcX(3), t_R))));//Z轴：	单位化（X轴×(刀具X轴×半径方向)）
		vec fa_Y = cross(fa_Z, fa_X);//Z轴：	后角线方向（Z轴×X轴）


		double ls_len = ptr_xx->Lenth_At_Point(i);

		vec ls_zhiwen = tcRotX(3, -ang_qian) * (-tcY(3));

		vec ans_p = { p_zhu(0), p_zhu(1), p_zhu(2),
			ls_p(0), ls_p(1), ls_p(2),
			t_R(0), t_R(1), t_R(2),
			zhu_X(0), zhu_X(1), zhu_X(2),
			zhu_Y(0), zhu_Y(1), zhu_Y(2),
			zhu_Z(0), zhu_Z(1), zhu_Z(2),
			fa_X(0), fa_X(1), fa_X(2),
			fa_Y(0), fa_Y(1), fa_Y(2),
			fa_Z(0), fa_Z(1), fa_Z(2),
			(double) i,
			ls_zhiwen(0),ls_zhiwen(1),ls_zhiwen(2)
		};
		Data_Of_Points.col(i) = ans_p;
	}
}

mat Cal_LouXuan::cal_luoxuancao_vp()
{
	int count_p = ptr_xx->n_P();

	mat ans_vp = zeros(3, count_p);

	vec last_p = ptr_xx->BG_P(0);
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = ptr_xx->BG_P(i); //直角坐标点
		double delta_len = ls_p(0) - last_p(0);

		double add_ang =  360.0 * (delta_len / data_base.D_daocheng); //角度增量

		ls_p = tcRotX(3, add_ang) * ls_p;  //实际位置


		ans_vp.col(i) = ls_p;

		last_p = ls_p;
	}
	return ans_vp;
}

void Cal_LouXuan::cal_B_daocheng_canshu(vector<double>& ans_v_cal_ang)
{
	vec last_dao = data_base.B_daocheng.canshu.col(0);
	for (int i = 1; i < data_base.B_daocheng.count_element(); i++)
	{
		vec cur_dao = data_base.B_daocheng.canshu.col(i);
		double delta_len = cur_dao(0) - last_dao(0);
		int cal_num = delta_len / ptr_xx->Lenth();

		double delta_qian = (cur_dao(1) - last_dao(1)) / cal_num;
		for (int j = 0; j < cal_num; j++)
		{
			double ls_ans_dao = cur_dao(1) + delta_qian * j;
			ans_v_cal_ang.push_back(ls_ans_dao);
		}
		last_dao = cur_dao;
	}
}

void Cal_LouXuan::B_luo_to_B_daocheng()
{
	//1-计算所有点处的螺旋角
	vec luoxuanjiao_v(ptr_xx->n_P(), fill::zeros);
	double lenth = ptr_xx->Lenth();
	for (size_t i = 0; i < ptr_xx->n_P(); i++)
	{
		luoxuanjiao_v(i) = data_base.B_luoxuan.get(ptr_xx->Lenth_At_Point(i) / lenth);
	}

	//2-计算所有点处的导程
	vec daocheng_v(ptr_xx->n_P(), fill::zeros);
	for (int i = 0; i < ptr_xx->n_P(); i++)
	{
		vec ls_p = ptr_xx->BG_P(i);
		ls_p(0) = 0.0;
		double R = norm(ls_p);

		daocheng_v(i) = 2.0 * datum::pi * R / tan(tcRadians(luoxuanjiao_v(i)));
	}

	//3-计算全部点
	mat ans_point(3, ptr_xx->n_P(), fill::zeros);
	double xiangwei_last = 0.0;
	double delta_x = 0.0;
	for (int i = 0; i < ptr_xx->n_P(); i++)
	{
		if (i == 0)
		{
			delta_x = 0.0;
			xiangwei_last = 0.0;
			ans_point.col(i) = ptr_xx->BG_P(i);
		}
		else
		{
			delta_x = ptr_xx->BG_P(i)(0) - ptr_xx->BG_P(i - 1)(0);
			xiangwei_last = xiangwei_last + delta_x / daocheng_v(i) * 360.0;
			ans_point.col(i) = tcRotX(3, xiangwei_last);
		}
	}
}


mat Cal_LouXuan::cal_luoxuancao_vp_by_B_daocheng(vector<double>& in_v_cal_ang)
{
	int count_p = ptr_xx->n_P();
	mat ans_vp = zeros(3, count_p);

	vec last_p = ptr_xx->BG_P(0);
	for (int i = 0; i < count_p; i++)
	{
		vec ls_p = ptr_xx->BG_P(i); //直角坐标点
		double delta_len = ls_p(0) - last_p(0);

		double add_ang = 360.0 * (delta_len / in_v_cal_ang[i]); //角度增量

		ls_p = tcRotX(3, add_ang) * ls_p;  //实际位置

		ans_vp.col(i) = ls_p;

		last_p = ls_p;
	}
	return ans_vp;
}

vec Cal_LouXuan::cal_daocheng_v_by_dengdaocheng()
{
	vec daocheng_v(ptr_xx->n_P(), fill::zeros);
	for (size_t i = 0; i < ptr_xx->n_P(); i++)
	{
		daocheng_v(i) = data_base.D_daocheng;
	}
	return daocheng_v;
}

vec Cal_LouXuan::cal_daocheng_v_by_dengluoxuanjiao()
{
	vec daocheng_v(ptr_xx->n_P(), fill::zeros);
	for (int i = 0; i < ptr_xx->n_P(); i++)
	{
		vec ls_p = ptr_xx->BG_P(i);
		ls_p(0) = 0.0;
		double R = norm(ls_p);

		daocheng_v(i) = 2.0 * datum::pi * R / tan(tcRadians(data_base.D_daocheng));
	}
	return daocheng_v;
}

vec Cal_LouXuan::cal_daocheng_v_by_biandaocheng()
{
	vec daocheng_v(ptr_xx->n_P(), fill::zeros);
	double lenth = ptr_xx->Lenth();
	for (size_t i = 0; i < ptr_xx->n_P(); i++)
	{
		daocheng_v(i) = data_base.B_daocheng.get(ptr_xx->Lenth_At_Point(i) / lenth);
	}
	return daocheng_v;
}

vec Cal_LouXuan::cal_luoxuanjiao_v_by_bianluoxuan()
{
	vec luoxuanjiao_v(ptr_xx->n_P(), fill::zeros);
	double lenth = ptr_xx->Lenth();
	for (size_t i = 0; i < ptr_xx->n_P(); i++)
	{
		luoxuanjiao_v(i) = data_base.B_luoxuan.get(ptr_xx->Lenth_At_Point(i) / lenth);
	}
	return luoxuanjiao_v;
}

vec Cal_LouXuan::cal_daocheng_v_by_luoxuanjiao_v(vec& luoxuanjiao_v)
{
	vec daocheng_v(ptr_xx->n_P(), fill::zeros);
	for (int i = 0; i < ptr_xx->n_P(); i++)
	{
		vec ls_p = ptr_xx->BG_P(i);
		ls_p(0) = 0.0;
		double R = norm(ls_p);

		daocheng_v(i) = 2.0 * datum::pi * R / tan(tcRadians(luoxuanjiao_v(i)));
	}
	return daocheng_v;
}

mat Cal_LouXuan::cal_points_by_daocheng_v(vec& daocheng_v)
{
	mat ans_point(3, ptr_xx->n_P(), fill::zeros);
	double xiangwei_last = 0.0;
	double delta_x = 0.0;
	for (int i = 0; i < ptr_xx->n_P(); i++)
	{
		if (i == 0)
		{
			delta_x = 0.0;
			xiangwei_last = 0.0;
			ans_point.col(i) = ptr_xx->BG_P(i);
		}
		else
		{
			delta_x = ptr_xx->BG_P(i)(0) - ptr_xx->BG_P(i - 1)(0);
			xiangwei_last = xiangwei_last + delta_x / daocheng_v(i) * 360.0;
			ans_point.col(i) = tcRotX(3, xiangwei_last) * ans_point.col(i); // yzl 6.3
		}
	}
	return ans_point;
}

//返回点的数量

inline void Cal_hdm_RX::set_base_data(CanShu_hdm_rx& in_data)
{
	data_base = in_data;
	is_lastest = 0;
}

void Cal_hdm_RX::set_range_and_sample(double in_start, double in_end, double in_len, double in_ang)
{
	range_start = in_start;
	range_end = in_end;
	sample_len = in_len;
	sample_ang = in_ang;
}

void Cal_hdm_RX::init_data()
{
	//
	ptr_xx = ptr_tool->ptr_list_xx->get_obj(data_base.xingxian_pos);
	ptr_lx = ptr_tool->ptr_list_lx->get_obj(data_base.luoxuan_pos);

	Cal_XingXian ls_xx = *ptr_xx;
	ls_xx.Range(range_start, range_end);
	ls_xx.Sample(sample_len, sample_ang);

	ptr_lx->cal_jiaoxian_by_xx(&ls_xx, *this);

	if (error_message_global != 0)
	{
		return;
	}

	is_lastest = 1;
}

void Cal_hdm_RX::cal_son_last_state()
{
	//if (is_lastest == 0)
	//{
	//	for (size_t i = 0; i < v_GL_LX.size(); i++)
	//	{
	//		v_GL_LX[i]->is_lastest = 0;
	//	}
	//	for (size_t i = 0; i < v_GL_HJ.size(); i++)
	//	{
	//		v_GL_HJ[i]->is_lastest = 0;
	//	}
	//}
}

inline int Cal_hdm_RX::n_P()
{
	return Data_Of_Points.n_cols;
}

vec Cal_hdm_RX::BG_zP(int i)
{
	return Data_Of_Points.col(i).rows(0, 2);
}

vec Cal_hdm_RX::BG_P(int i)
{
	return Data_Of_Points.col(i).rows(3, 5);
}

mat Cal_hdm_RX::BG_nzP()
{
	return Data_Of_Points.rows(0, 2);
}

mat Cal_hdm_RX::BG_nP()
{
	return Data_Of_Points.rows(3, 5);
}

vec Cal_hdm_RX::BG_r_arrow(int i)
{
	return Data_Of_Points.col(i).rows(6, 8);
}

vec Cal_hdm_RX::BG_zX(int i)
{
	vec test_x = Data_Of_Points.col(i).subvec(9, 11);
	vec test_x2 = Data_Of_Points.col(i).rows(9, 11);
	return Data_Of_Points.col(i).rows(9, 11);
}

vec Cal_hdm_RX::BG_zY(int i)
{
	return Data_Of_Points.col(i).rows(12, 14);
}

vec Cal_hdm_RX::BG_zZ(int i)
{
	return Data_Of_Points.col(i).rows(15, 17);
}

mat33 Cal_hdm_RX::BG_zSYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = BG_zX(i);
	ans.col(1) = BG_zY(i);
	ans.col(2) = BG_zZ(i);

	return ans;
}

vec Cal_hdm_RX::BG_nX(int i)
{
	return Data_Of_Points.col(i).rows(18, 20);
}

vec Cal_hdm_RX::BG_nY(int i)
{
	return Data_Of_Points.col(i).rows(21, 23);
}

vec Cal_hdm_RX::BG_nZ(int i)
{
	return Data_Of_Points.col(i).rows(24, 26);
}

mat33 Cal_hdm_RX::BG_nSYS(int i)
{
	mat33 ans = eye(3, 3);
	ans.col(0) = BG_nX(i);
	ans.col(1) = BG_nY(i);
	ans.col(2) = BG_nZ(i);

	return ans;
}

//返回第i个点处的长度坐标

inline double Cal_hdm_RX::Lenth_At_Point(int i)
{
	return Data_Of_Points(27, i) * 0.001;
}

void Cal_HouJiao::set_base_data(CanShu_HouJiao& in_data)
{
	data_base = in_data;
	is_lastest = 0;
}

void Cal_HouJiao::init_data()
{
	if (data_base.guanlian_xx_id == -1)
	{
		error_message_global = -1;
		return;
	}

	is_lastest = 1;

	//1
	ptr_xx = ptr_tool->ptr_list_xx->get_obj(data_base.guanlian_xx_id);
	type = data_base.type;

	//2
	int count = ptr_xx->n_P();
	Data_Of_Points = zeros(10, count);
	double lenth_in = ptr_xx->Lenth();
	//法后角
	for (size_t j = 0; j < 3; j++)
	{
		if (data_base.type == 0)
		{
			for (size_t i = 0; i < count; i++)
			{
				if (j == 0)
				{
					vec ans;
					if (data_base.is_bian_n_1 == 0)
					{
						ans = {data_base.D_ang_n_1,0.0 ,data_base.D_wid_n_1 };
					}
					else
					{
						ans = data_base.B_ang_n_1.get(ptr_xx->Lenth_At_Point(i) / lenth_in);
					}
					Data_Of_Points.col(i).subvec(0, 2) = ans;
				}
				else if(j == 1)
				{
					vec ans;
					if (data_base.is_bian_n_2 == 0)
					{
						ans = { data_base.D_ang_n_2,0.0 ,data_base.D_wid_n_2 };
					}
					else
					{
						ans = data_base.B_ang_n_2.get(ptr_xx->Lenth_At_Point(i) / lenth_in);
					}
					Data_Of_Points.col(i).subvec(3, 5) = ans;
				}
				else
				{
					vec ans;
					if (data_base.is_bian_n_3 == 0)
					{
						ans = { data_base.D_ang_n_3,0.0 ,data_base.D_wid_n_3 };
					}
					else
					{
						ans = data_base.B_ang_n_3.get(ptr_xx->Lenth_At_Point(i) / lenth_in);
					}
					Data_Of_Points.col(i).subvec(6, 8) = ans;
				}
				Data_Of_Points.col(i)(9) = (double)i;
			}
		}
		//径向后角+轴向后角
		else
		{
			for (size_t i = 0; i < count; i++)
			{
				if (j == 0)
				{
					vec ans;
					if (data_base.is_bian_a_1 == 0)
					{
						ans = { data_base.D_ang_r_1,data_base.D_ang_a_1 ,data_base.D_wid_a_1 };
					}
					else
					{
						ans = data_base.B_ang_a_r_1.get(ptr_xx->Lenth_At_Point(i) / lenth_in);
					}
					Data_Of_Points.col(i).subvec(0, 2) = ans;
				}
				else if (j == 1)
				{
					vec ans;
					if (data_base.is_bian_a_2 == 0)
					{
						ans = { data_base.D_ang_r_2,data_base.D_ang_a_2 ,data_base.D_wid_a_2 };
					}
					else
					{
						ans = data_base.B_ang_a_r_2.get(ptr_xx->Lenth_At_Point(i) / lenth_in);
					}
					Data_Of_Points.col(i).subvec(3, 5) = ans;
				}
				else
				{
					vec ans;
					if (data_base.is_bian_a_3 == 0)
					{
						ans = { data_base.D_ang_r_3,data_base.D_ang_a_3 ,data_base.D_wid_a_3 };
					}
					else
					{
						ans = data_base.B_ang_a_r_3.get(ptr_xx->Lenth_At_Point(i) / lenth_in);
					}
					Data_Of_Points.col(i).subvec(6, 8) = ans;
				}
				Data_Of_Points.col(i)(9) = (double)i;
			}
		}
	}
	//
	is_lastest = 1;
	for (size_t i = 0; i < v_GL_GX.size(); i++)
	{
		v_GL_GX[i]->is_lastest = 0;
	}

}

void Cal_HouJiao::init_guanxi()
{
	int show_index = ptr_tool->ptr_list_xx->base_data.get_show_index_by_id(data_base.guanlian_xx_id);
	ptr_xx = ptr_tool->ptr_list_xx->get_obj(show_index);
	ptr_xx->add_guanxi_GL_HJ(this);
}

void Cal_HouJiao::cal_son_last_state()
{
	if (is_lastest == 0)
	{
		for (size_t i = 0; i < v_GL_GX.size(); i++)
		{
			v_GL_GX[i]->is_lastest = 0;
		}

	}
}


void Cal_LouXuan::del_guanxi_GL_GX(Miller_GX_Base* p)
{
	for (auto iter = v_GL_GX.begin(); iter != v_GL_GX.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_GX.erase(iter);
			break;
		}
	}
}

int Cal_LouXuan::guanxi_exist(Miller_GX_Base* p)
{
	for (size_t i = 0; i < v_GL_GX.size(); i++)
	{
		if (p == v_GL_GX[i])
		{
			return i;
		}
	}
	return -1;
}

void Cal_LouXuan::add_guanxi_GL_GX(Miller_GX_Base* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_GX.push_back(p);
	}
}

void Cal_HouJiao::del_guanxi_GL_GX(Miller_GX_Base* p)
{
	for (auto iter = v_GL_GX.begin(); iter != v_GL_GX.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_GX.erase(iter);
			break;
		}
	}
}

int Cal_HouJiao::guanxi_exist(Miller_GX_Base* p)
{
	for (size_t i = 0; i < v_GL_GX.size(); i++)
	{
		if (p == v_GL_GX[i])
		{
			return i;
		}
	}
	return -1;
}

bool Cal_HouJiao::is_del_ok()
{
	if (v_GL_GX.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cal_HouJiao::add_guanxi_GL_GX(Miller_GX_Base* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_GX.push_back(p);
	}
}

double Cal_HouJiao::HJ1_r_or_n(int i)
{
	return Data_Of_Points(0, i);
}

double Cal_HouJiao::HJ1_a(int i)
{
	return Data_Of_Points(1, i);
}

double Cal_HouJiao::HJ1_w(int i)
{
	return Data_Of_Points(2, i);
}

double Cal_HouJiao::HJ2_r_or_n(int i)
{
	return Data_Of_Points(3, i);
}

double Cal_HouJiao::HJ2_a(int i)
{
	return Data_Of_Points(4, i);
}

double Cal_HouJiao::HJ2_w(int i)
{
	return Data_Of_Points(5, i);
}

double Cal_HouJiao::HJ3_r_or_n(int i)
{
	return Data_Of_Points(6, i);
}

double Cal_HouJiao::HJ3_a(int i)
{
	return Data_Of_Points(7, i);
}

double Cal_HouJiao::HJ3_w(int i)
{
	return Data_Of_Points(8, i);
}

double Cal_HouJiao::Lenth_At_Point(int i)
{
	return Data_Of_Points(9, i) * 0.001;
}

Cal_HouJiao::Cal_HouJiao()
{
	ptr_tool = nullptr;
	ptr_xx = nullptr;
	type = zeros(3);

	Data_Of_Points.reset();
	Data_Of_Points = zeros(10, 0); 
	v_GL_GX.clear();
}

Cal_HouJiao::~Cal_HouJiao()
{
}

Cal_HouJiao::Cal_HouJiao(Tool_Base* in_ptr, CanShu_HouJiao& in_data)
{
	ptr_tool = in_ptr;
	set_base_data(in_data);
	init_data();

	v_GL_GX.clear();
}

inline void Cal_HouJiao::speak_father_del_guanxi()
{
	ptr_xx->del_guanxi_GL_HJ(this);
}

inline int Cal_HouJiao::del_self()
{
	if (v_GL_GX.size() == 0)
	{
	}
	else
	{
		return 1;
	}
	speak_father_del_guanxi();
	delete this;
	return 0;
}

void Cal_HouJiao::sel_a_xx_id(int in_id)
{
	data_base.guanlian_xx_id = in_id;
	ptr_xx = ptr_tool->ptr_list_xx->get_obj(data_base.guanlian_xx_id);
}

int Cal_HouJiao::save(int pos)
{
	data_base.save(pos);
	return pos;
}

void Cal_HouJiao::load(int pos)
{
	data_base.load(pos);
}

int Cal_XinHouMian::save()
{
	//storage_lib.Storage_base::renew_a_row_data(32, pos, (char*)&data_base, sizeof(data_base));
	return pos;
}

void Cal_XinHouMian::load()
{
	//storage_lib.Storage_base::read_a_row_data(storage_lib.xx, pos, (char*)&data_base, sizeof(data_base));
}

//bool Storage_manager_xingxian::add_xingxian_count(bool add)
//{
//fstream file2;
//file2.open(file_dir_xingxian_count, std::ios::in | std::ios::out | std::ios::binary);
//if (!file2.is_open())
//{
//	return 0;
//}
////读出当前数量，根据输入修改值后写入
//file2.seekg(0, ios::beg);
//int len_data2 = -1;
//file2.read((char*)(&len_data2), sizeof(len_data2));
//file2.seekg(len_data2, ios::beg);
//int ls_count = 0;
//file2.read((char*)(&ls_count), sizeof(ls_count));
//if (add)
//{
//	ls_count++;
//}
//else
//{
//	ls_count--;
//}
//file2.close();
//
////在增加刀具时读数清空重写 7.12 mark
//file2.open(file_dir_xingxian_count, std::ios::out | std::ios::binary);
//if (!file2.is_open())
//{
//	return 0;
//}
//file2.seekp(0, ios::beg);
//file2.write((char*)(&len_data2), sizeof(len_data2));
//file2.write((char*)(&ls_count), sizeof(ls_count));
//
//file2.close();
//return true;
//}
//int Storage_manager_xingxian::get_xingxian_count()
//{
//fstream file2;
//file2.open(file_dir_xingxian_count, std::ios::in | std::ios::out | std::ios::binary);
//if (!file2.is_open())
//{
//	return 0;
//}
//
////读出当前数量，根据输入修改值后写入
//file2.seekg(0, ios::beg);
//int len_data2 = -1;
//file2.read((char*)(&len_data2), sizeof(len_data2));
//file2.seekg(len_data2, ios::beg);
//int ls_count = 0;
//file2.read((char*)(&ls_count), sizeof(ls_count));
//
//file2.close();
//
//return ls_count;
//}
////重命名dxf文件并拷贝到指定文件夹
//void Storage_manager_xingxian::renameAndCopyFile(const string& sourcePath, const string& newName, const string& targetDirectory)
//{
//namespace fs = std::filesystem;
//try
//{
//	// 检查源文件是否存在
//	if (!fs::exists(sourcePath)) {
//		std::cerr << "源文件不存在: " << sourcePath << std::endl;
//		return;
//	}
//
//	// 检查目标目录是否存在，不存在则创建
//	if (!fs::exists(targetDirectory)) {
//		fs::create_directories(targetDirectory);
//	}
//
//	// 获取源文件扩展名
//	std::string extension = fs::path(sourcePath).extension().string();
//
//	// 构建目标路径
//	fs::path targetPath = fs::path(targetDirectory) / (newName + extension);
//
//	// 拷贝文件到目标目录并重命名
//	fs::copy_file(sourcePath, targetPath, fs::copy_options::overwrite_existing);
//
//	std::cout << "文件已成功重命名并拷贝到: " << targetPath << std::endl;
//}
//catch (const fs::filesystem_error& e)
//{
//	std::cerr << "文件操作错误: " << e.what() << std::endl;
//}
//catch (const std::exception& e)
//{
//	std::cerr << "发生错误: " << e.what() << std::endl;
//}
//}
//
////将型线名称文件读成显示列表3.5-不显示-1的数据条3.6
//void Storage_manager_xingxian::read_xx_catalog_for_display_list(vector<int>& ans_type, vector<string>& ans_name)
//{
//	fstream file2;
//	{
//		file2.open(file_dir_xingxian_catalog, std::ios::in | std::ios::binary);
//		if (!file2.is_open())
//		{
//			return;
//		}
//		//数据长度
//		file2.seekg(0, ios::beg);
//		int len_data2 = -1;
//		file2.read((char*)(&len_data2), sizeof(len_data2));
//		//读到文件末尾
//		while (1)
//		{
//			if (file2.eof())
//			{
//				break;
//			}
//
//			xingxian_catalog ls_data;
//
//			file2.read((char*)(&ls_data), sizeof(xingxian_catalog));
//
//			if (ls_data.type > -1)
//			{
//				ans_type.push_back(ls_data.type);
//				string file_name;
//				file_name.resize(NAME_BUFFER_SIZE);
//				for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//				{
//					file_name[i] = ls_data.name_buffer[i];
//				}
//
//				ans_name.push_back(file_name);
//			}
//		}
//
//		file2.close();
//		return;
//	}
//}
////p_manager加载一条型线,将数据写入两个文件
////void load_a_dxf(string in_file_name,double in_dis, string in_new_name);
//
//void Storage_manager_xingxian::load_xx_data_by_name(string in_name, Cal_XingXian& ans_xx)
//{
//
//}
//
////根据目录索引对应位置的型线数据
//void Storage_manager_xingxian::load_a_tool_xx_name_and_data(vector<int>& in_v_pos, vector<string>& ans_v_name, vector<Cal_XingXian>& ans_v_data)
//{
//	ans_v_name.clear();
//	ans_v_data.clear();
//	for (int i = 0; i < in_v_pos.size(); i++)
//	{
//		string ls_name;
//		mat ls_data;
//		get_tag_pos_dxf_name_and_data(in_v_pos[i], ls_name, ls_data);
//		ans_v_name.push_back(ls_name);
//		//ans_v_data.push_back(ls_data);
//	}
//}
//
////成型刀添加一条型线，将新name写入目录文件
//int Storage_manager_xingxian::tool_add_a_xx_from_win(string in_dxf_name, string in_new_name, Cal_XingXian& xx_data)
//{
//
//
//	//读出点数据
//	//line_manager read_dxf_tool(in_dxf_name);
//	//vector<vec> p_of_dxf;
//	//read_dxf_tool.get_integral_point(in_dis, in_ang, p_of_dxf);
//	double in_dis = 0.001; //默认两点间距离 4.3
//	//read_dxf_tool.get_discrete_point(in_dis, p_of_dxf);
//
//	//xx_data.init_data_by_dxf_file(in_new_name, in_dis);4.14
//	//int count_p = p_of_dxf.size();
//
//	//写型线文件，先写点数据，后写目录
//	//fstream file1;
//	//file1.open(file_dir_xingxian_data, std::ios::out | std::ios::binary);
//
//	//file1.seekp(0, ios::end); //write定位
//	//int cur_data_start_index = file1.tellp();
//	//for (size_t i = 0; i < count_p; i++)
//	//{
//	//	vec ls_data = p_of_dxf[i];
//	//	double p_buffer[6] = { ls_data(0), ls_data(1), ls_data(2),
//	//		ls_data(3), ls_data(4), ls_data(5) };
//	//	//file1.write((char*)&p_buffer, sizeof(p_buffer));
//	//	//型线点数据
//	//	p_data.insert_cols(p_data.n_cols, ls_data);
//	//}
//	//file1.close();
//
//
//	xingxian_catalog ls_catalog;
//	ls_catalog.type = 0;
//	for (int i = 0; i < in_new_name.size(); i++)
//	{
//		ls_catalog.name_buffer[i] = in_new_name[i];
//	}
//
//	int count_xx_num = get_xingxian_count();
//
//	int len = sizeof(ls_catalog);
//	fstream file2;
//	file2.open(file_dir_xingxian_catalog, std::ios::in | std::ios::out | std::ios::binary);
//	file2.seekp(count_xx_num * sizeof(ls_catalog), ios::beg); //write定位
//
//	file2.write((char*)&ls_catalog, sizeof(ls_catalog));
//
//	file2.close();
//	return 0;
//}
//
////根据文件名修改对应行的标志位为删除（-1）3.6
//bool Storage_manager_xingxian::renew_a_xx_name_of_type_by_delete(string in_file_name)
//{
//	fstream file2;
//	{
//		file2.open(file_dir_xingxian_catalog, std::ios::in | std::ios::binary);
//		if (!file2.is_open())
//		{
//			throw - 1;
//		}
//		//数据长度
//		file2.seekg(0, ios::beg);
//		int len_data2 = -1;
//		file2.read((char*)(&len_data2), sizeof(len_data2));
//		int row_index = 1; //改变标志位写入的索引
//
//		//读到文件末尾
//		while (1)
//		{
//			if (file2.eof())
//			{
//				break;
//			}
//
//			xingxian_name_data ls_data;
//			file2.read((char*)(&ls_data), sizeof(xingxian_name_data));
//
//			string file_name;
//			file_name.resize(NAME_BUFFER_SIZE);
//			for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//			{
//				file_name[i] = ls_data.name_buffer[i];
//			}
//
//			if (file_name == in_file_name)
//			{
//				if (ls_data.type == 0)
//				{
//					file2.seekp(row_index * len_data2);
//					ls_data.type = -1;
//					file2.write((char*)&ls_data, sizeof(ls_data));
//					break;
//				}
//				else
//				{
//					return false;
//				}
//			}
//			row_index++;
//		}
//
//		file2.close();
//	}
//	return true;
//}
//
////获取指定位置的dxf文件名
//string Storage_manager_xingxian::get_tag_pos_dxf_file_name(int in_pos)
//{
//	//xingxian_name_data ans_data;
//	//fstream file2;
//	//{
//	//	file2.open(file_dir_xingxian_catalog, std::ios::in | std::ios::binary);
//	//	if (!file2.is_open())
//	//	{
//	//		return "null";
//	//	}
//	//	//数据长度
//	//	file2.seekg(0, ios::beg);
//	//	int len_data2 = -1;
//	//	file2.read((char*)(&len_data2), sizeof(len_data2));
//
//	//	file2.seekg(in_pos * len_data2, ios::beg);
//	//	file2.read((char*)&ans_data, sizeof(xingxian_name_data));
//
//	//	file2.close();
//	//}
//	//string file_name;
//	//file_name.resize(NAME_BUFFER_SIZE);
//	//for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//	//{
//	//	file_name[i] = ans_data.name_buffer[i];
//	//}
//	//return file_name;
//	return "";
//}
////获取指定位置的dxf文件名及点数据
//void Storage_manager_xingxian::get_tag_pos_dxf_name_and_data(int in_pos, string& ans_name, mat& ans_data)
//{
//	double in_dis = 0.001; //默认两点间距离 4.3
//	//read_dxf_tool.get_discrete_point(in_dis, p_of_dxf);
//
//	xingxian_catalog ls_catalog;
//	ls_catalog.type = 0;
//	int len = sizeof(ls_catalog);
//
//	fstream file2;
//	file2.open(file_dir_xingxian_catalog, std::ios::in | std::ios::out | std::ios::binary);
//	file2.seekg(in_pos * sizeof(ls_catalog), ios::beg);
//
//	file2.read((char*)&ls_catalog, sizeof(ls_catalog));
//
//	file2.close();
//
//	string file_name;
//	//file_name.resize(NAME_BUFFER_SIZE);
//	for (int i = 0; i < NAME_BUFFER_SIZE; i++)
//	{
//		//C 风格字符串，找到第一个 \0 终止符的位置，仅拼接有效内容 -4.14
//		if (ls_catalog.name_buffer[i] != '\0')
//		{
//			file_name = file_name + ls_catalog.name_buffer[i];
//		}
//		//else
//		//{
//		//	break;
//		//}
//	}
//
//
//	line_manager ls_read_tool(file_name);
//	vector<vec> ans_ponts;
//
//	ls_read_tool.get_discrete_point(in_dis, ans_ponts);
//
//	ans_vv_to_mat(ans_ponts, ans_data);
//
//	ans_name = file_name;
//}
//
////构造：指定所有文件的名字、将文件的数据大小在此设置
//Storage_manager_xingxian::Storage_manager_xingxian()
//{
//	//设置文件名
//	{
//		file_dir_xingxian_catalog = "xingxian_catalog.txt";
//		//file_dir_xingxian_data = "xingxian_save_data.txt";
//		file_dir_xingxian_count = "xingxian_count.txt";
//	}
//
//#pragma region 创建文件
//	//创建文件-并写入数据，存在就不打开直接过
//	//工序文件初始化
//	if (!std::filesystem::exists(file_dir_xingxian_catalog))
//	{
//		fstream file1;			//in|out 模式不会创建文件
//		file1.open(file_dir_xingxian_catalog, std::ios::out | std::ios::binary);
//		int len_data = sizeof(xingxian_catalog);	//刀具对象一条数据长度
//		//第一行写数据长度，直接存目录信息 4.11-15:28
//		//file1.write((char*)&len_data, len_data); //直接写一条数据长度 
//		file1.close();
//	}
//
//	//if (!std::filesystem::exists(file_dir_xingxian_data))
//	//{
//	//	fstream file1;
//	//	file1.open(file_dir_xingxian_data, std::ios::out | std::ios::binary);
//	//	//int len_data = 100 * sizeof(double);	//刀具数据一条数据长度
//	//	//file1.write((char*)&len_data, len_data);
//	//	file1.close();
//	//}
//
//	if (!std::filesystem::exists(file_dir_xingxian_count))
//	{
//		fstream file1;
//		file1.open(file_dir_xingxian_count, std::ios::out | std::ios::binary);
//		int len_data = sizeof(int);	//刀具count一条数据长度
//		file1.write((char*)&len_data, len_data);
//		int tool_count = 0;
//		file1.write((char*)&tool_count, len_data);
//		file1.close();
//	}
//	//fstream file1;
//	//if (!std::filesystem::exists(file_dir_xingxian_name))
//	//{
//	//	fstream file1;
//	//	file1.open(file_dir_xingxian_name, std::ios::out | std::ios::binary);
//	//	int len_data = sizeof(xingxian_name_data);
//	//	file1.write((char*)&len_data, len_data);
//	//	file1.close();
//	//}
//	//if (!std::filesystem::exists(file_dir_xingxian_write))
//	//{
//	//	fstream file1;
//	//	file1.open(file_dir_xingxian_write, std::ios::out | std::ios::binary);
//	//	int len_data = sizeof(int);
//	//	file1.write((char*)&len_data, len_data);
//	//	int index_max = 0;
//	//	file1.write((char*)&index_max, sizeof(index_max));
//	//	int empty_num = 0;
//	//	file1.write((char*)&empty_num, sizeof(empty_num));
//	//	file1.close();
//	//}
//
//#pragma endregion
//} //追加app方式打开文件，默认定位到末尾seekg不起作用，在增加刀具时读数清空重写 7.12 mark
//Storage_manager_xingxian::~Storage_manager_xingxian()
//{
//}
//
//void Storage_manager_xingxian::ans_vv_to_mat(vector<vec>& points, mat& Data_Of_Points)
//{
//	Data_Of_Points.clear();
//	int count_p = points.size();
//	for (int i = 0; i < count_p; i++)
//	{
//		vec ls_data = points[i];
//		vec ls_t = { ls_data(0), ls_data(1), ls_data(2) };
//		vec ls_p = { ls_data(3),ls_data(4),ls_data(5) };
//		//dxf的x 转为Z为长度方向
//		ls_t = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_t;
//		ls_p = tcRotZ(3, -90.0) * tcRotY(3, -90.0) * ls_p;
//
//		double lenth = 0.0001; //???? 6.14
//		vec ans_p = { ls_p(0), ls_p(1), ls_p(2), ls_t(0), ls_t(1), ls_t(2), i * lenth };
//
//		Data_Of_Points.insert_cols(Data_Of_Points.n_cols, ans_p);
//	}
//}

void Cal_SL_LRr::set_base_data(int in_sl_id)
{
	sl_id = in_sl_id;
}

void Cal_SL_LRr::init_data()
{
	//SL_L = in_L;
	//SL_R = in_R;
	//SL_r = in_r;
}

void Cal_SL_LRr::del_guanxi_GL_GX(Miller_GX_Base* p)
{
	for (auto iter = v_GL_GX.begin(); iter != v_GL_GX.end(); iter++)
	{
		if (*iter == p)
		{
			v_GL_GX.erase(iter);
			break;
		}
	}
}

void Cal_SL_LRr::add_guanxi_GL_GX(Miller_GX_Base* p)
{
	if (guanxi_exist(p) < 0)
	{
		v_GL_GX.push_back(p);
	}
}

int Cal_SL_LRr::guanxi_exist(Miller_GX_Base* p)
{
	for (size_t i = 0; i < v_GL_GX.size(); i++)
	{
		if (p == v_GL_GX[i])
		{
			return i;
		}
	}
	return -1;
}

void Cal_SL_LRr::speak_father_del_guanxi()
{
}

int Cal_SL_LRr::del_self()
{
	if (v_GL_GX.size() == 0)
	{
	}
	else
	{
		return 1;
	}

	speak_father_del_guanxi();
	delete this;
	return 0;
}

Cal_SL_LRr::Cal_SL_LRr()
{
	SL_L = 0.0;
	SL_R = 0.0;
	SL_r = 0.0;
}

Cal_SL_LRr::~Cal_SL_LRr()
{
}
