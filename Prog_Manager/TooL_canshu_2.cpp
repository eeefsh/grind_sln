#pragma once
#include"pch.h"
#define Prog_Manager_EXPORTS
#include "TooL_canshu_2.h"
#include "Storage_manager.h"

xt_CanShu_Range::xt_CanShu_Range()
{
	start = 0.0;
	end = 100.0;
}

xt_CanShu_Range::xt_CanShu_Range(double in_start, double in_end)
{
	start = in_start;
	end = in_end;
}

int xt_CanShu_Range::save(int pos)
{
	//菱形继承，最下层类，不能识别基类函数，可将renew_a_row_data放到最下面
	//write_a_row_data 也可以，只要下层能访问到上层类的所有文件数据 7.7 todo：zy ???
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_range, pos, (char*)this, sizeof(xt_CanShu_Range));

	return pos;
}

void xt_CanShu_Range::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_range, pos, (char*)this, sizeof(xt_CanShu_Range));
}

//void Cal_RenXian::Sample(double changdu, double jiaodu)
//{
//	//计算角度条件的cos值
//	double cosjiaodu = cos(jiaodu / 180.0 * datum::pi);
//
//	//建立辅助变量
//	int before_index = 0; //被抽样点下标
//	vec lsSampleVector_N1;
//	vec lsSampleVector_N2;
//
//	n_P = Data_Of_Points.n_rows;
//	mat B;//用于临时存放抽样数据
//	//对点数据矩阵进行抽样
//	for (int i = 0; i < n_P; i++)
//	{
//		//{点编号, 点坐标, (法坐标系)x向量, y向量, z向量,（横坐标系）x向量, y向量, z向量，(柱坐标)柱半径，相位角，Z+长度}
//		//{0,		1-3,			4-6,	7-9,	10-12 ,		  13-15,	  16-18,  19-21,    22,			23,     24 }
//		lsSampleVector_N1 = Data_Of_Points.row(before_index).cols(19, 21).t();
//		//记录当前点的法向
//		lsSampleVector_N2 = Data_Of_Points.row(i).cols(19, 21).t();
//
//		//如果为第一个点 抽样
//		if (i == 0)
//		{
//			B.insert_rows(B.n_rows, Data_Of_Points.row(i));
//			before_index = i;
//		}
//		//如果为最后一个点 抽样
//		else if (i == n_P - 1)
//		{
//			B.insert_rows(B.n_rows, Data_Of_Points.row(i));
//			before_index = i;
//		}
//		else
//		{
//			//若长度达到抽样条件，抽样
//			if (Distance_of_Point * (i - before_index) >= changdu)
//			{
//				B.insert_rows(B.n_rows, Data_Of_Points.row(i));
//				before_index = i;
//			}
//			//若角度达到抽样条件，抽样  
//			else if (dot(lsSampleVector_N1, lsSampleVector_N2) <= cosjiaodu)
//			{
//				B.insert_rows(B.n_rows, Data_Of_Points.row(i));
//				before_index = i;
//			}
//		}
//	}
//	//复位型线矩阵
//	Data_Of_Points.reset();
//
//	//更新数据矩阵
//	Data_Of_Points = B;
//
//	//更新点的数量
//	n_P = (int)Data_Of_Points.n_rows;
//}
//
//void Cal_RenXian::Sample(xt_CanShu_Sample& canshu)
//{
//	//取出长度、角度
//	double length = canshu.Sample_lenth;
//	double angle = canshu.Sample_angle;
//	Sample(length, angle);
//}
//
//void Cal_RenXian::Range(double start, double end)
//{
//	//将型线长度的范围转化为编号的范围
//	double a, b;
//	a = start / 100.0 * (double)Max_No_P;
//	b = end / 100.0 * (double)Max_No_P;
//
//	//记录与start和end对应的编号值的位置，存于c，d
//	int c = 0, d = 0;
//
//	//寻找起点
//	for (int i = 0; i < n_P; i++)
//	{
//		//如果型线编号符合要求则存于c中，并且d变为1，不再计算
//		if (Data_Of_Points.row(i)(0) >= a)
//		{
//			c = i;
//			break;
//		}
//		if (Data_Of_Points.row(i)(0) == n_P - 1)
//		{
//			throw - 1;//没找到起点
//		}
//	}
//
//	//寻找终点
//	for (int i = 0; i < n_P - c - 1; i++)
//	{
//
//		if (Data_Of_Points.row(n_P - i - 1)(0) <= b)
//		{
//			d = n_P - i - 1;
//			break;
//		}
//		//如果到了最后一个点，最后一个点为终点
//		if (i == n_P - c - 1)
//		{
//			throw - 1;//没有找到终点
//		}
//	}
//	//更新点数据矩阵
//	Data_Of_Points = Data_Of_Points.rows(c, d);
//
//	//更新点的数量
//	n_P = (int)Data_Of_Points.n_rows;
//
//	//将起点编号转化为0，其他也跟着减去相同的值
//	double e = Data_Of_Points.row(0)(0);
//	for (int i = 0; i < Data_Of_Points.n_rows; i++)
//	{
//		Data_Of_Points.row(i)(0) = Data_Of_Points.row(i)(0) - e;
//	}
//
//	//更新最大编号值
//	Max_No_P = (int)round(Data_Of_Points.row(Data_Of_Points.n_rows - 1)(0));
//}
//
//void Cal_RenXian::Range(xt_CanShu_Range& canshu)
//{
//	//取出起始百分比
//	double start = canshu.start;
//	double end = canshu.end;
//	Range(start, end);
//}
//
////截取线已有刃线的一段，输入截取起点终点（0-1]，得到新的线
//
////{点编号, 点坐标, (法坐标系)x向量, y向量, z向量,（横坐标系）x向量, y向量, z向量，(柱坐标)柱半径，相位角，Z+长度}
////{0,		1-3,			4-6,	7-9,	10-12 ,		  13-15,	16-18,  19-21,      22,			23,     24 }
//
//void Cal_RenXian::save(ofstream& outFile)
//{
//	outFile << n_P << " " << Max_No_P << " " << Distance_of_Point << endl;
//
//	for (int i = 0; i < n_P; i++)
//	{
//		for (int j = 0; j <= 24; j++)
//		{
//			outFile << Data_Of_Points.row(i).col(j) << " ";
//		}
//		outFile << endl;
//	}
//}
//
//void Cal_RenXian::load(ifstream& infile)
//{
//	infile >> n_P >> Max_No_P >> Distance_of_Point;
//	Data_Of_Points.reset();
//	Data_Of_Points.resize(0, 25);
//	Data_Of_Points.insert_rows(Data_Of_Points.n_rows, n_P);
//
//	double ls_num = 0.0;
//	for (int i = 0; i < n_P; i++)
//	{
//		for (int j = 0; j <= 24; j++)
//		{
//			infile >> ls_num;
//			Data_Of_Points.row(i).col(j) = ls_num;
//		}
//	}
//}

CanShu_Bian::CanShu_Bian()
{
	canshu = zeros(2, 2);
	canshu(0, 0) = 0.0;
	canshu(0, 1) = 1.0;
}

CanShu_Bian::CanShu_Bian(mat in_canshu)
{
	canshu = in_canshu;
}

int CanShu_Bian::count_element()
{
	return canshu.n_cols;
}

double CanShu_Bian::get(double percent)
{
	if (percent >= 0.0 && percent <= 1.0)
	{
		for (int i = 0; i < canshu.n_cols - 1; i++)
		{
			vec ls_left = canshu.col(i);
			vec ls_rigt = canshu.col(i + 1);
			if (ls_left(0) <= percent && percent <= ls_rigt(0))
			{
				double delta_per = ls_rigt(0) - ls_left(0);
				double delta_val = ls_rigt(1) - ls_left(1);

				double cal_per = (percent - ls_left(0)) / delta_per;

				return ls_left(1) + cal_per * delta_val;
			}
		}
	}

	return 0.0;
}

void CanShu_Bian::insert_element(double percent, double value)
{
	if (percent <= 0.0)
	{
		percent = 0.00000001;
	}
	else if (percent >= 1.0)
	{
		percent = 0.99999999;
	}
	if (percent >= 0.0 && percent <= 1.0)
	{
		for (int i = 0; i < canshu.n_cols; i++)
		{
			if (abs(percent - canshu.col(i)(0)) < 0.0000001)
			{
				canshu(1, i) = value;
				break;
			}
			else if (percent < canshu.col(i)(0))
			{
				vec ls_col = { percent ,value };
				canshu.insert_cols(i, ls_col);
				break;
			}
		}
	}
}

void CanShu_Bian::delete_element(int i)
{
	if (i == 0)
	{
	}
	else if (i == count_element() - 1)
	{
	}
	else
	{
		canshu.shed_col(i);
	}
}

int CanShu_Bian::save()
{
	int ans_pos = save_lib::storage_lib.set_2n_mat(canshu);
	return ans_pos;
}

void CanShu_Bian::load(int pos)
{
	save_lib::storage_lib.get_2n_mat(pos, canshu);
}


CanShu_Bian_v3::CanShu_Bian_v3()
{
	canshu = zeros(3, 2);
	canshu(0, 0) = 0.0;
	canshu(0, 1) = 1.0;
}

CanShu_Bian_v3::CanShu_Bian_v3(mat in_canshu)
{
	canshu = in_canshu;
}

int CanShu_Bian_v3::count_element()
{
	return canshu.n_cols;
}

vec3 CanShu_Bian_v3::get(double percent)
{
	if (percent < 0.0)
	{
		percent = 0.0;
	}
	else if (percent > 1.0)
	{
		percent = 1.0;
	}

	for (int i = 0; i < canshu.n_cols - 1; i++)
	{
		vec ls_left = canshu.col(i);
		vec ls_rigt = canshu.col(i + 1);
		if (ls_left(0) <= percent && percent <= ls_rigt(0))
		{
			double delta_per = ls_rigt(0) - ls_left(0);
			vec delta_val = ls_rigt.subvec(1, 2) - ls_left.subvec(1, 2);

			double cal_per = (percent - ls_left(0)) / delta_per;
			return ls_left.subvec(1, 2) + cal_per * delta_val;
		}
	}

	return zeros(3);
}

void CanShu_Bian_v3::insert_element(double percent, vec value)
{
	if (percent <= 0.0)
	{
		percent = 0.00000001;
	}
	else if (percent >= 1.0)
	{
		percent = 0.99999999;
	}
	if (percent >= 0.0 && percent <= 1.0)
	{
		for (int i = 0; i < canshu.n_cols; i++)
		{
			if (abs(percent - canshu.col(i)(0)) < 0.0000001)
			{
				canshu.submat(1, i, 2, i) = value;
				break;
			}
			else if (percent < canshu.col(i)(0))
			{
				vec ls_col = zeros(3);
				ls_col(0) = percent;
				ls_col.subvec(1, 2) = value;
				canshu.insert_cols(i, ls_col);
				break;
			}
		}
	}
}

void CanShu_Bian_v3::delete_element(int i)
{
	if (i == 0)
	{
	}
	else if (i == count_element() - 1)
	{
	}
	else
	{
		canshu.shed_col(i);
	}
}

int CanShu_Bian_v3::save()
{
	int ans_pos = save_lib::storage_lib.set_3n_mat(canshu);
	return ans_pos;
}

void CanShu_Bian_v3::load(int pos)
{
	save_lib::storage_lib.get_3n_mat(pos, canshu);
}


xt_CanShu_HDM_MoXue_d_XunHuan::xt_CanShu_HDM_MoXue_d_XunHuan()
{
}

xt_CanShu_HDM_MoXue_d_XunHuan xt_CanShu_HDM_MoXue_d_XunHuan::operator=(const xt_CanShu_HDM_MoXue_d_XunHuan& A)
{
	return xt_CanShu_HDM_MoXue_d_XunHuan();
}

int xt_CanShu_HDM_MoXue_d_XunHuan::save(int pos)
{
	return 0;
}

void xt_CanShu_HDM_MoXue_d_XunHuan::load(int pos)
{
}

xt_CanShu_JinTuiDao::xt_CanShu_JinTuiDao()
{
	JinDaoXiangQie = 0;
	TuiDaoXiangQie = 0;
	JingXiangAnQuanJuLi = 10.0;
	ZhouXiangAnQuanJuLi = 20.0;
	JinDaoJiaoDu = 90.0;
	TuiDaoJiaoDu = 90.0;
	JinDaoJuLi = 1.0;
	TuiDaoJuLi = 1.0;
	JieJinJiaoDu = 90.0;
	YuanLiJiaoDu = 90.0;
}

int xt_CanShu_JinTuiDao::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(
		storage_lib.file_dir_gx_jintuidao, pos, (char*)this, sizeof(xt_CanShu_JinTuiDao));
	return pos;
}

void xt_CanShu_JinTuiDao::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_jintuidao, pos, (char*)this, sizeof(xt_CanShu_JinTuiDao));
}


xt_Mo_HDM_CanShu::xt_Mo_HDM_CanShu()
{
}

int xt_Mo_HDM_CanShu::save(int pos)
{
	range.save(pos);
	sample.save(pos);
	jintuidao.save(pos);
	bianhuan.save(pos);
	xunhuan.save(pos);
	zhenlie.save(pos);
	fangfa.save(pos);
	sudu.save(pos);

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_A_before, pos, (char*)&A_before, sizeof(A_before));
	return pos;
}

void xt_Mo_HDM_CanShu::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_A_before, pos, (char*)&A_before, sizeof(A_before));

	//函数继承关系紊乱，先用临时变量解决，后期查找原因 25.11.14
	xt_CanShu_Range ls_range;
	ls_range.load(pos);
	range = ls_range;
	xt_CanShu_Sample ls_sample;
	ls_sample.load(pos);
	sample = ls_sample;

	xt_CanShu_JinTuiDao ls_jintuidao;
	ls_jintuidao.load(pos);
	jintuidao = ls_jintuidao;
	xt_CanShu_MoXue_BianHuan ls_bianhuan;
	bianhuan.load(pos);
	bianhuan = ls_bianhuan;
	xt_CanShu_MoXue_XunHuan ls_xunhuan;
	ls_xunhuan.load(pos);
	xunhuan = ls_xunhuan;
	xt_CanShu_MoXue_ZhenLie ls_zhenlie;
	ls_zhenlie.load(pos);
	zhenlie = ls_zhenlie;

	CanShu_HDM_MoXue_FangFa ls_fangfa;
	ls_fangfa.load(pos);
	fangfa = ls_fangfa;
	CanShu_SuDu ls_sudu;
	ls_sudu.load(pos);
	sudu = ls_sudu;
}

inline double xt_Mo_HDM_CanShu::get_sample_ang(int cal_flag)
{
	double ans = -1.0;
	if (cal_flag == 0)
	{
		ans = sample.Sample_angle;
	}
	if (cal_flag == 1)
	{
		ans = sample.Sample_angle_2D;
	}
	if (cal_flag == 2)
	{
		ans = sample.Sample_angle_3D;
	}
	return ans;
}

inline double xt_Mo_HDM_CanShu::get_sample_len(int cal_flag)
{
	double ans = -1.0;
	if (cal_flag == 0)
	{
		ans = sample.Sample_lenth;
	}
	if (cal_flag == 1)
	{
		ans = sample.Sample_lenth_2D;
	}
	if (cal_flag == 2)
	{
		ans = sample.Sample_lenth_3D;
	}
	return ans;
}

inline double xt_Mo_HDM_CanShu::get_range_end()
{

	return range.end;

}

inline double xt_Mo_HDM_CanShu::get_range_start()
{
	return range.start;
}

xt_CanShu_MoXue_BianHuan::xt_CanShu_MoXue_BianHuan()
{
	FaXiangPianZhi = 0.0;
	ChangDuPianZhi = 0.0;
	JingXiangPianZhi = 0.0;
	XuanZhuanPianZhi = 0.0;
}

xt_CanShu_MoXue_BianHuan::xt_CanShu_MoXue_BianHuan(double inFaXiangPianZhi, double inChangDuPianZhi, double inJingXiangPianZhi, double inXuanZhuanPianZhi)
{
	FaXiangPianZhi = inFaXiangPianZhi;
	ChangDuPianZhi = inChangDuPianZhi;
	JingXiangPianZhi = inJingXiangPianZhi;
	XuanZhuanPianZhi = inXuanZhuanPianZhi;
}

void xt_CanShu_MoXue_BianHuan::save(std::ofstream& outfile)
{
}

void xt_CanShu_MoXue_BianHuan::load(std::ifstream& infile)
{
}

int xt_CanShu_MoXue_BianHuan::save(int pos)
{
	return pos;
}

void xt_CanShu_MoXue_BianHuan::load(int pos)
{
}

xt_CanShu_MoXue_XunHuan::xt_CanShu_MoXue_XunHuan()
{
}

void xt_CanShu_MoXue_XunHuan::AddCanShu(xt_CanShu_HDM_MoXue_d_XunHuan dCanShu)
{
	CanShu.push_back(dCanShu);
}

void xt_CanShu_MoXue_XunHuan::EditCanShu(int id, xt_CanShu_HDM_MoXue_d_XunHuan dCanShu)
{
	CanShu.at(id) = dCanShu;
}

void xt_CanShu_MoXue_XunHuan::DeleteCanShu(int id)
{
	CanShu.erase(CanShu.begin() + id);
}

void xt_CanShu_MoXue_XunHuan::up(int i)
{
	if (i == 0)
	{
		return;
	}
	else
	{
		xt_CanShu_HDM_MoXue_d_XunHuan a;
		a = CanShu.at(i - 1);
		CanShu.at(i - 1) = CanShu.at(i);
		CanShu.at(i) = a;
	}
}

void xt_CanShu_MoXue_XunHuan::down(int i)
{
	if (i == CanShu.size() - 1)
	{
		return;
	}
	else
	{
		xt_CanShu_HDM_MoXue_d_XunHuan a;
		a = CanShu.at(i + 1);
		CanShu.at(i + 1) = CanShu.at(i);
		CanShu.at(i) = a;
	}
}

void xt_CanShu_MoXue_XunHuan::save(std::ofstream& outfile)
{
}

void xt_CanShu_MoXue_XunHuan::load(std::ifstream& infile)
{
}

int xt_CanShu_MoXue_XunHuan::save(int pos)
{
	return pos;
}

void xt_CanShu_MoXue_XunHuan::load(int pos)
{
}

void xt_CanShu_MoXue_ZhenLie::SetDengfen(int i)
{
	if (i == 0)
	{
		RenShu = 0;
	}
	else
	{
		RenShu = 1;
	}
}

void xt_CanShu_MoXue_ZhenLie::SetRenShu(int i)
{
	if (i >= 1)
	{
		RenShu = i;
	}
	else
	{
		RenShu = 1;
	}
}

void xt_CanShu_MoXue_ZhenLie::BDF_add()
{
	BDF_RenShu++;
	WeiZhi.resize(BDF_RenShu);
	for (int i = 0; i < BDF_RenShu; i++)
	{
		WeiZhi(i) = 360.0 / double(BDF_RenShu) * double(i);
	}
}

void xt_CanShu_MoXue_ZhenLie::BDF_delete(int i)
{
	BDF_RenShu--;
	WeiZhi.shed_row(i);
}

//0:第一行不能修改 1:修改成功 2：角度值应在上一个与下一个之间
int xt_CanShu_MoXue_ZhenLie::BDF_edit(int i, double jiaodu)
{
	if (i == 0)
	{
		return 0;
	}
	if (jiaodu > WeiZhi(i - 1))
	{
		WeiZhi(i) = jiaodu;
		return 1;
	}
	else
	{
		return 2;
	}

}

void xt_CanShu_MoXue_ZhenLie::BDF_Dengfen()
{
	for (int i = 0; i < BDF_RenShu; i++)
	{
		WeiZhi(i) = 360.0 / double(BDF_RenShu) * double(i);
	}
}

xt_CanShu_MoXue_ZhenLie::xt_CanShu_MoXue_ZhenLie()
{
	DengFen = 0;
	RenShu = 1;
	BDF_RenShu = RenShu;
	WeiZhi = { 0 };
}

void xt_CanShu_MoXue_ZhenLie::save(std::ofstream& outfile)
{
}

void xt_CanShu_MoXue_ZhenLie::load(std::ifstream& infile)
{
}

int xt_CanShu_MoXue_ZhenLie::save(int pos)
{
	return pos;
}

void xt_CanShu_MoXue_ZhenLie::load(int pos)
{
}

CanShu_QianJiao::CanShu_QianJiao()
{
	save_b_qianjiao_n = 0;
	save_b_qianjiao_r = 0;

	luoxuan_order = 0;

	type = 0; //0-法向，1-径向
}

CanShu_QianJiao::~CanShu_QianJiao()
{
}

int CanShu_QianJiao::save(int pos)
{
	//矩阵save
	save_b_qianjiao_n = b_qianjiao_n.save();
	save_b_qianjiao_r = b_qianjiao_r.save();

	//
	qj_canshu_data ls_row_data;
	ls_row_data.save_b_qianjiao_n = save_b_qianjiao_n;
	ls_row_data.save_b_qianjiao_r = save_b_qianjiao_r;

	ls_row_data.luoxuan_pos = luoxuan_order;
	ls_row_data.type = type;

	save_lib::storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_qj_canshu, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	return pos;
}

void CanShu_QianJiao::load(int pos)
{
	qj_canshu_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_qj_canshu, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	save_b_qianjiao_n = ls_row_data.save_b_qianjiao_n;
	save_b_qianjiao_r = ls_row_data.save_b_qianjiao_r;
	luoxuan_order = ls_row_data.luoxuan_pos;
	type = ls_row_data.type;

	CanShu_Bian ls_mat1;
	ls_mat1.load(save_b_qianjiao_n);
	b_qianjiao_n = ls_mat1;

	CanShu_Bian ls_mat2;
	ls_mat2.load(save_b_qianjiao_r);
	b_qianjiao_r = ls_mat2;

}

CanShu_XingXian::CanShu_XingXian()
{
	input_type = 0;

	ang_zhui = 0.0;

	sel_dxf_pos = -1;
}

CanShu_XingXian::~CanShu_XingXian()
{
}

int CanShu_XingXian::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_xx_canshu, pos,
		(char*)this, sizeof(CanShu_XingXian));
	return pos;
}

void CanShu_XingXian::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_xx_canshu, pos,
		(char*)this, sizeof(CanShu_XingXian));
}


int CanShu_LuoXuan::save(int pos)
{
	//矩阵save
	save_obj_hjbc = obj_hjbc.save();
	save_B_daocheng = B_daocheng.save();
	save_B_luoxuan = B_luoxuan.save();

	//
	lx_canshu_data ls_row_data;
	ls_row_data.save_obj_hjbc = save_obj_hjbc;
	ls_row_data.save_B_daocheng = save_B_daocheng;
	ls_row_data.save_B_luoxuan = save_B_luoxuan;

	ls_row_data.xingxian_pos = guanlian_xx_id;
	ls_row_data.fendu_pos = guanlian_fd_id;
	ls_row_data.type_cao = type_cao;
	ls_row_data.type_zhi = type_zhi;
	ls_row_data.zhi_ang_qian = zhi_ang_qian;
	ls_row_data.zhi_pianxin = zhi_pianxin;
	ls_row_data.ang_xie = ang_xie;
	ls_row_data.R_zhi_or_xie = R_zhi_or_xie;

	ls_row_data.type_xie = type_xie;
	ls_row_data.xie_ang_qian = xie_ang_qian;
	ls_row_data.xie_pianxin = xie_pianxin;
	ls_row_data.type_luo = type_luo;
	ls_row_data.D_daocheng = D_daocheng;
	ls_row_data.D_ang_luo = D_ang_luo;

	ls_row_data.ang_r = ang_r;

	save_lib::storage_lib.Storage_base::edit_a_row_data(save_lib::storage_lib.file_dir_lx_canshu, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	return pos;
}

void CanShu_LuoXuan::load(int pos)
{
	lx_canshu_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_lx_canshu, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	save_obj_hjbc = ls_row_data.save_obj_hjbc;
	save_B_daocheng = ls_row_data.save_B_daocheng;
	save_B_luoxuan = ls_row_data.save_B_luoxuan;
	guanlian_xx_id = ls_row_data.xingxian_pos;
	guanlian_fd_id = ls_row_data.fendu_pos;
	type_cao = ls_row_data.type_cao;
	type_zhi = ls_row_data.type_zhi;
	zhi_ang_qian = ls_row_data.zhi_ang_qian;
	zhi_pianxin = ls_row_data.zhi_pianxin;
	ang_xie = ls_row_data.ang_xie;
	R_zhi_or_xie = ls_row_data.R_zhi_or_xie;

	type_xie = ls_row_data.type_xie;
	xie_ang_qian = ls_row_data.xie_ang_qian;
	xie_pianxin = ls_row_data.xie_pianxin;
	type_luo = ls_row_data.type_luo;
	D_daocheng = ls_row_data.D_daocheng;
	D_ang_luo = ls_row_data.D_ang_luo;
	ang_r = ls_row_data.ang_r;

	CanShu_Bian ls_mat1;
	ls_mat1.load(save_obj_hjbc);
	obj_hjbc = ls_mat1;

	CanShu_Bian ls_mat2;
	ls_mat2.load(save_B_daocheng);
	B_daocheng = ls_mat2;

	CanShu_Bian ls_mat3;
	ls_mat3.load(save_B_luoxuan);
	B_luoxuan = ls_mat3;

}

int CanShu_HouJiao::save(int pos)
{
	//矩阵save
	save_B_ang_n_1 = B_ang_n_1.save();
	save_B_ang_n_2 = B_ang_n_2.save();
	save_B_ang_n_3 = B_ang_n_3.save();
	save_B_ang_a_r_1 = B_ang_a_r_1.save();
	save_B_ang_a_r_2 = B_ang_a_r_2.save();
	save_B_ang_a_r_3 = B_ang_a_r_3.save();
	//
	hj_canshu_data ls_row_data;
	ls_row_data.save_B_ang_n_1 = save_B_ang_n_1;
	ls_row_data.save_B_ang_n_2 = save_B_ang_n_2;
	ls_row_data.save_B_ang_n_3 = save_B_ang_n_3;
	ls_row_data.save_B_ang_a_r_1 = save_B_ang_a_r_1;
	ls_row_data.save_B_ang_a_r_2 = save_B_ang_a_r_2;
	ls_row_data.save_B_ang_a_r_3 = save_B_ang_a_r_3;

	ls_row_data.xingxian_pos = guanlian_xx_id;
	ls_row_data.type = type;

	ls_row_data.D_ang_n_1 = D_ang_n_1;
	ls_row_data.D_wid_n_1 = D_wid_n_1;
	ls_row_data.is_bian_n_1 = is_bian_n_1;
	ls_row_data.D_ang_n_2 = D_ang_n_2;
	ls_row_data.D_wid_n_2 = D_wid_n_2;
	ls_row_data.is_bian_n_2 = is_bian_n_2;
	ls_row_data.D_ang_n_3 = D_ang_n_3;
	ls_row_data.D_wid_n_3 = D_wid_n_3;
	ls_row_data.is_bian_n_3 = is_bian_n_3;

	ls_row_data.D_ang_a_1 = D_ang_a_1;
	ls_row_data.D_ang_r_1 = D_ang_r_1;
	ls_row_data.D_wid_a_1 = D_wid_a_1;
	ls_row_data.is_bian_a_1 = is_bian_a_1;
	ls_row_data.D_ang_a_2 = D_ang_a_2;
	ls_row_data.D_ang_r_2 = D_ang_r_2;
	ls_row_data.D_wid_a_2 = D_wid_a_2;
	ls_row_data.is_bian_a_2 = is_bian_a_2;
	ls_row_data.D_ang_a_3 = D_ang_a_3;
	ls_row_data.D_ang_r_3 = D_ang_r_3;
	ls_row_data.D_wid_a_3 = D_wid_a_3;
	ls_row_data.is_bian_a_3 = is_bian_a_3;

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_hj_canshu, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	return pos;
}

void CanShu_HouJiao::load(int pos)
{

	hj_canshu_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_hj_canshu, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	save_B_ang_n_1 = ls_row_data.save_B_ang_n_1;
	save_B_ang_n_2 = ls_row_data.save_B_ang_n_2;
	save_B_ang_n_3 = ls_row_data.save_B_ang_n_3;
	save_B_ang_a_r_1 = ls_row_data.save_B_ang_a_r_1;
	save_B_ang_a_r_2 = ls_row_data.save_B_ang_a_r_2;
	save_B_ang_a_r_3 = ls_row_data.save_B_ang_a_r_3;

	guanlian_xx_id = ls_row_data.xingxian_pos;
	type = ls_row_data.type;

	D_ang_n_1 = ls_row_data.D_ang_n_1;
	D_wid_n_1 = ls_row_data.D_wid_n_1;
	is_bian_n_1 = ls_row_data.is_bian_n_1;
	D_ang_n_2 = ls_row_data.D_ang_n_2;
	D_wid_n_2 = ls_row_data.D_wid_n_2;
	is_bian_n_2 = ls_row_data.is_bian_n_2;
	D_ang_n_3 = ls_row_data.D_ang_n_3;
	D_wid_n_3 = ls_row_data.D_wid_n_3;
	is_bian_n_3 = ls_row_data.is_bian_n_3;

	D_ang_a_1 = ls_row_data.D_ang_a_1;
	D_ang_r_1 = ls_row_data.D_ang_r_1;
	D_wid_a_1 = ls_row_data.D_wid_a_1;
	is_bian_a_1 = ls_row_data.is_bian_a_1;
	D_ang_a_2 = ls_row_data.D_ang_a_2;
	D_ang_r_2 = ls_row_data.D_ang_r_2;
	D_wid_a_2 = ls_row_data.D_wid_a_2;
	is_bian_a_2 = ls_row_data.is_bian_a_2;
	D_ang_a_3 = ls_row_data.D_ang_a_3;
	D_ang_r_3 = ls_row_data.D_ang_r_3;
	D_wid_a_3 = ls_row_data.D_wid_a_3;
	is_bian_a_3 = ls_row_data.is_bian_a_3;


	CanShu_Bian_v4 ls_mat1;
	ls_mat1.load(save_B_ang_n_1);
	B_ang_n_1 = ls_mat1;

	CanShu_Bian_v4 ls_mat2;
	ls_mat2.load(save_B_ang_n_2);
	B_ang_n_2 = ls_mat2;

	CanShu_Bian_v4 ls_mat3;
	ls_mat3.load(save_B_ang_n_3);
	B_ang_n_3 = ls_mat3;

	CanShu_Bian_v4 ls_mat4;
	ls_mat4.load(save_B_ang_a_r_1);
	B_ang_a_r_1 = ls_mat4;

	CanShu_Bian_v4 ls_mat5;
	ls_mat5.load(save_B_ang_a_r_2);
	B_ang_a_r_2 = ls_mat5;

	CanShu_Bian_v4 ls_mat6;
	ls_mat6.load(save_B_ang_a_r_3);
	B_ang_a_r_3 = ls_mat6;
}

int xt_Mo_QDM_CanShu::save(int pos)
{
	range.save(pos);
	sample.save(pos);
	jintuidao.save(pos);
	bianhuan.save(pos);
	xunhuan.save(pos);
	zhenlie.save(pos);
	fangfa.save(pos);
	sudu.save(pos);
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_A_before, pos, (char*)&A_before, sizeof(A_before));
	return pos;
}

void xt_Mo_QDM_CanShu::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_A_before, pos, (char*)&A_before, sizeof(A_before));
	
	//函数继承关系紊乱，先用临时变量解决，后期查找原因 25.11.14
	xt_CanShu_Range ls_range;
	ls_range.load(pos);
	range = ls_range;
	xt_CanShu_Sample ls_sample;
	ls_sample.load(pos);
	sample = ls_sample;

	xt_CanShu_JinTuiDao ls_jintuidao;
	ls_jintuidao.load(pos);
	jintuidao = ls_jintuidao;
	xt_CanShu_MoXue_BianHuan ls_bianhuan;
	bianhuan.load(pos);
	bianhuan = ls_bianhuan;
	xt_CanShu_MoXue_XunHuan ls_xunhuan;
	ls_xunhuan.load(pos);
	xunhuan = ls_xunhuan;
	xt_CanShu_MoXue_ZhenLie ls_zhenlie;
	ls_zhenlie.load(pos);
	zhenlie = ls_zhenlie;

	CanShu_QDM_MoXue_FangFa ls_fangfa;
	ls_fangfa.load(pos);
	fangfa = ls_fangfa;
	CanShu_SuDu ls_sudu;
	ls_sudu.load(pos);
	sudu = ls_sudu;
}

inline double xt_Mo_QDM_CanShu::get_sample_ang(int cal_flag)
{
	double ans = -1.0;
	if (cal_flag == 0)
	{
		ans = sample.Sample_angle;
	}
	if (cal_flag == 1)
	{
		ans = sample.Sample_angle_2D;
	}
	if (cal_flag == 2)
	{
		ans = sample.Sample_angle_3D;
	}
	return ans;
}

inline double xt_Mo_QDM_CanShu::get_sample_len(int cal_flag)
{
	double ans = -1.0;
	if (cal_flag == 0)
	{
		ans = sample.Sample_lenth;
	}
	if (cal_flag == 1)
	{
		ans = sample.Sample_lenth_2D;
	}
	if (cal_flag == 2)
	{
		ans = sample.Sample_lenth_3D;
	}
	return ans;
}

inline double xt_Mo_QDM_CanShu::get_range_end()
{

	return range.end;

}

inline double xt_Mo_QDM_CanShu::get_range_start()
{
	return range.start;
}


xt_CanShu_HDM_MoXue_QX_WY::xt_CanShu_HDM_MoXue_QX_WY()
{
	pos_QX_bian = -1;
	pos_WY_bian = -1;

	QX = 1.0;
	WY = 1.0;
	QX_isbian = 0;
	WY_isbian = 0;

	CanShu_Bian scale_and_trans_mat;

	QX_bian = scale_and_trans_mat;
	WY_bian = scale_and_trans_mat;
}

int xt_CanShu_HDM_MoXue_QX_WY::save(int pos)
{
	pos_QX_bian = QX_bian.save();
	pos_WY_bian = WY_bian.save();

	//
	fangfa_xx_wy_data ls_row_data;
	ls_row_data.pos_xx_bian = pos_QX_bian;
	ls_row_data.pos_wy_bian = pos_WY_bian;
	ls_row_data.xx = QX;
	ls_row_data.wy = WY;
	ls_row_data.xx_isbian = QX_isbian;
	ls_row_data.wy_isbian = WY_isbian;

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_juti_ff, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	return pos;
}

void xt_CanShu_HDM_MoXue_QX_WY::load(int pos)
{
	fangfa_xx_wy_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_juti_ff, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	pos_QX_bian = ls_row_data.pos_xx_bian;
	pos_WY_bian = ls_row_data.pos_wy_bian;
	QX = ls_row_data.xx;
	WY = ls_row_data.wy;
	QX_isbian = ls_row_data.xx_isbian;
	WY_isbian = ls_row_data.wy_isbian;

	CanShu_Bian ls_qx;
	ls_qx.load(pos_QX_bian);
	QX_bian = ls_qx;

	CanShu_Bian ls_wy;
	ls_wy.load(pos_WY_bian);
	WY_bian = ls_wy;
}

_BD_WY_xt_CanShu_HDM_1_MoXue::_BD_WY_xt_CanShu_HDM_1_MoXue()
{
	int b = 2;
}

int _BD_WY_xt_CanShu_HDM_1_MoXue::save()
{
	pos_BD_bian = BD_bian.save();
	pos_WY_bian = WY_bian.save();

	//
	fangfa_xx_wy_data ls_row_data;
	ls_row_data.pos_xx_bian = pos_BD_bian;
	ls_row_data.pos_wy_bian = pos_WY_bian;
	ls_row_data.xx = BD;
	ls_row_data.wy = WY;
	ls_row_data.xx_isbian = BD_isbian;
	ls_row_data.wy_isbian = WY_isbian;

	storage_lib.Storage_base::edit_a_row_data(
		storage_lib.file_dir_gx_juti_ff, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	return pos;
}

void _BD_WY_xt_CanShu_HDM_1_MoXue::load()
{
	fangfa_xx_wy_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(
		storage_lib.file_dir_gx_juti_ff, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	pos_BD_bian = ls_row_data.pos_xx_bian;
	pos_WY_bian = ls_row_data.pos_wy_bian;
	BD = ls_row_data.xx;
	WY = ls_row_data.wy;
	BD_isbian = ls_row_data.xx_isbian;
	WY_isbian = ls_row_data.wy_isbian;

	CanShu_Bian ls_bd;
	ls_bd.load(pos_BD_bian);
	BD_bian = ls_bd;

	CanShu_Bian ls_wy;
	ls_wy.load(pos_WY_bian);
	WY_bian = ls_wy;
}

xt_CanShu_HDM_MoXue_XZ_WY::xt_CanShu_HDM_MoXue_XZ_WY()
{
	pos_XZ_bian = -1;
	pos_WY_bian = -1;

	XZ = -1.0;
	WY = -1.0;
	XZ_isbian = 0;
	WY_isbian = 0;
}

xt_CanShu_HDM_MoXue_XZ_WY::~xt_CanShu_HDM_MoXue_XZ_WY()
{
}

int xt_CanShu_HDM_MoXue_XZ_WY::save(int pos)
{
	pos_XZ_bian = XZ_bian.save();
	pos_WY_bian = WY_bian.save();

	//
	fangfa_xx_wy_data ls_row_data;
	ls_row_data.pos_xx_bian = pos_XZ_bian;
	ls_row_data.pos_wy_bian = pos_WY_bian;
	ls_row_data.xx = XZ;
	ls_row_data.wy = WY;
	ls_row_data.xx_isbian = XZ_isbian;
	ls_row_data.wy_isbian = WY_isbian;

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_juti_ff, pos, (char*)&ls_row_data, sizeof(ls_row_data));
	return pos;
}

void xt_CanShu_HDM_MoXue_XZ_WY::load(int pos)
{
	fangfa_xx_wy_data ls_row_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_juti_ff, pos, (char*)&ls_row_data, sizeof(ls_row_data));

	pos_XZ_bian = ls_row_data.pos_xx_bian;
	pos_WY_bian = ls_row_data.pos_wy_bian;
	XZ = ls_row_data.xx;
	WY = ls_row_data.wy;
	XZ_isbian = ls_row_data.xx_isbian;
	WY_isbian = ls_row_data.wy_isbian;

	CanShu_Bian ls_xz;
	ls_xz.load(pos_XZ_bian);
	XZ_bian = ls_xz;

	CanShu_Bian ls_wy;
	ls_wy.load(pos_WY_bian);
	WY_bian = ls_wy;
}

CanShu_Bian_v4::CanShu_Bian_v4()
{
	canshu = zeros(4, 2);
	canshu(0, 0) = 0.0;
	canshu(0, 1) = 1.0;
}

CanShu_Bian_v4::CanShu_Bian_v4(mat in_canshu)
{
	canshu = in_canshu;
}

int CanShu_Bian_v4::count_element()
{
	return canshu.n_cols;
}

vec CanShu_Bian_v4::get(double percent)
{
	if (percent < 0.0)
	{
		percent = 0.0;
	}
	else if (percent > 1.0)
	{
		percent = 1.0;
	}

	for (int i = 0; i < canshu.n_cols - 1; i++)
	{
		vec ls_left = canshu.col(i);
		vec ls_rigt = canshu.col(i + 1);
		if (ls_left(0) <= percent && percent <= ls_rigt(0))
		{
			double delta_per = ls_rigt(0) - ls_left(0);
			vec delta_val = ls_rigt.subvec(1, 3) - ls_left.subvec(1, 3);

			//double cal_per = (percent - ls_rigt(0)) / delta_per;
			double cal_per = (percent - ls_left(0)) / delta_per; //8.16
			return ls_left.subvec(1, 3) + cal_per * delta_val;
		}
	}

	return zeros(4);
}

void CanShu_Bian_v4::insert_element(double percent, vec value)
{
	if (percent <= 0.0)
	{
		percent = 0.00000001;
	}
	else if (percent >= 1.0)
	{
		percent = 0.99999999;
	}
	if (percent >= 0.0 && percent <= 1.0)
	{
		for (int i = 0; i < canshu.n_cols; i++)
		{
			if (abs(percent - canshu.col(i)(0)) < 0.0000001)
			{
				canshu.submat(1, i, 3, i) = value;
				break;
			}
			else if (percent < canshu.col(i)(0))
			{
				vec ls_col = zeros(4);
				ls_col(0) = percent;
				ls_col.subvec(1, 3) = value;
				canshu.insert_cols(i, ls_col);
				break;
			}
		}
	}
}

void CanShu_Bian_v4::delete_element(int i)
{
	if (i == 0)
	{
	}
	else if (i == count_element() - 1)
	{
	}
	else
	{
		canshu.shed_col(i);
	}
}

int CanShu_Bian_v4::save()
{
	int ans_pos = save_lib::storage_lib.set_4n_mat(canshu);
	return ans_pos;
}

void CanShu_Bian_v4::load(int pos)
{
	save_lib::storage_lib.get_4n_mat(pos, canshu);
}

CanShu_SuDu::CanShu_SuDu()
{
	SL_XianSuDu = 20.0;	//砂轮线速度
	MoXueJinGei = 60.0;	//磨削进给
	JinDao = 100.0;	//进刀
	TuiDao = 100.0;	//退刀
	JieJin = 1000.0;	//接近
	YuanLi = 1000.0;	//远离
	KuaiSu = 5000.0;	//快速
}

CanShu_SuDu::~CanShu_SuDu()
{
}

int CanShu_SuDu::save(int pos)
{
	//CanShu_SuDu ls_data = *this;

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_sudu, pos, (char*)this, sizeof(CanShu_SuDu));
	return pos;
}

void CanShu_SuDu::load(int pos)
{
	//CanShu_SuDu ls_data ;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_sudu, pos, (char*)this, sizeof(CanShu_SuDu));
	//*this = ls_data;
}

CanShu_HDM_MoXue_FangFa::CanShu_HDM_MoXue_FangFa()
{
	pos_qx_wy = -1;
	in_or_out = 1;
	type = 0;

	xt_CanShu_HDM_MoXue_QX_WY scale_and_trans_mat;
	qx_wy = scale_and_trans_mat;
}

int CanShu_HDM_MoXue_FangFa::save(int pos)
{
	pos_qx_wy = qx_wy.save(pos);

	mo_hdm_ff_canshu_data ls_data;
	ls_data.pos_qx_wy = pos_qx_wy;
	ls_data.in_or_out = in_or_out;
	ls_data.type = type;

	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_fangfa, pos, (char*)&ls_data, sizeof(ls_data));

	return pos;
}

void CanShu_HDM_MoXue_FangFa::load(int pos)
{
	mo_hdm_ff_canshu_data ls_data;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_fangfa, pos, (char*)&ls_data, sizeof(ls_data));

	pos_qx_wy = ls_data.pos_qx_wy;
	in_or_out = ls_data.in_or_out;
	type = ls_data.type;


	xt_CanShu_HDM_MoXue_QX_WY ls_qx_wy;
	ls_qx_wy.load(pos);
	qx_wy = ls_qx_wy;

}


CanShu_QDM_MoXue_FangFa::CanShu_QDM_MoXue_FangFa()
{
	in_or_out = 0;
	ang_qiexue = 5.0;
	type_cao = -1;
}

CanShu_QDM_MoXue_FangFa::~CanShu_QDM_MoXue_FangFa()
{
}

int CanShu_QDM_MoXue_FangFa::save(int pos)
{
	//CanShu_QDM_MoXue_FangFa ls_data = *this;
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_fangfa, pos, (char*)this, sizeof(CanShu_QDM_MoXue_FangFa));

	return pos;
}

void CanShu_QDM_MoXue_FangFa::load(int pos)
{
	//CanShu_QDM_MoXue_FangFa ls_data ;
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_fangfa, pos, (char*)this, sizeof(CanShu_QDM_MoXue_FangFa));
	//*this = ls_data;
}

xt_CanShu_Sample::xt_CanShu_Sample()
{
	Sample_lenth = 0.04;
	Sample_angle = 2.0;

	Sample_lenth_2D = 0.1;
	Sample_angle_2D = 2.0;

	Sample_lenth_3D = 0.1;
	Sample_angle_3D = 2.0;
}

int xt_CanShu_Sample::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_gx_sample, pos, (char*)this, sizeof(xt_CanShu_Sample));
	return pos;
}

void xt_CanShu_Sample::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_gx_sample, pos, (char*)this, sizeof(xt_CanShu_Sample));
}

int CanShu_FenDu::save(int pos)
{
	storage_lib.Storage_base::edit_a_row_data(storage_lib.file_dir_fd_canshu, pos, (char*)this, sizeof(CanShu_FenDu));
	return pos;
}

void CanShu_FenDu::load(int pos)
{
	storage_lib.Storage_base::read_a_row_data(storage_lib.file_dir_fd_canshu, pos, (char*)this, sizeof(CanShu_FenDu));

}
