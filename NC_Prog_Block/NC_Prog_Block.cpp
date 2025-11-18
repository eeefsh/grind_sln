// NC_Prog_Block.cpp : 定义 DLL 的导出函数。

/*
*	由于该模板预编译头必须引用windows.h，而其中定义了WIN32
*   这会影响库设置中的预处理代码
*   若要使用预编译头，则pch.h必须包含
*	因此采取定义PCH_H的方法使得在pch.h中跳过包含项
*
*   上述问题应该还可以通过单独设置cpp文件的预编译头解决。
*/

#include "pch.h"
#define NC_Prog_Block_EXPORTS
#include "NC_Prog_Block.h"

nc_block::nc_block()
{
	int i = 0;
	block = 0;
}

nc_block::nc_block(const nc_block& block_in)
{
	int i = 0;
	block = block_in.block;
	//block_in.set_null();
}

nc_block::nc_block(nb_NC_block& block_in)
{
	int i = 0;
	block = &block_in;
}

nc_block::~nc_block()
{
	if (block != nullptr)
	{
		if (block->need_release == true)
		{
			delete block;
		}
		else
		{

		}
	}
}

void nc_block::set_null()
{
	block = nullptr;
}

void nc_block::set_model()
{
	block->set_father(nb_NC_block::father_block);
}

void nc_block::release_block_tree()
{
	if (block != nullptr)
	{
		delete block;
		block = nullptr;
	}
}

void nc_block::replace(nc_block block_in)
{
	if (block != 0)
	{
		//delete block;
	}
	block = block_in.block;
}

string nc_block::write_code()
{
	if (block != 0)
	{
		block->write_nc_code();
	}
	else
	{
		return "没有生成程序块，请检查！";
	}
	return block->NC_code;
}

void nc_block::zhixing()
{
	//NC_control_message a;
	block->ZhiXing();
}

void nc_block::set_machine(virtual_machine* pmachine)
{
	block->set_machine(pmachine);
}

void nc_block::set_stop()
{
	block->set_stop();
}

void nc_block::reset()
{
	block->reset();
}

//nc_block& nc_block::operator=(const nc_block& block_in)
//{
//	// TODO: 在此处插入 return 语句
//	block = block_in.block;
//	return *this;
//}

nc_block nc_block::operator-()
{
	//在nc_block层面，不能用new
	//因为用new得到的东西无法去析构
	//这里只需要用值传递，也就是传递block*
	//因为block*内部形成了树结构
	//因此在nc_block层面只需要保留最后的结构就可以了
	//也就是内部进行真实的运算，所有接口的运算都是临时的

	if (block == 0)
	{
		block = &nb_ChangShu(1.0);
	}
	nc_block a;
	a.block = &(-(*block));
	a.block->is_BL_now = false;
	return a;
}

//nc_block& nc_block::operator-(nc_block block_in)
//{
//	nc_block a;
//	a.block = &((*block) - (*block_in.block));
//	a.block->is_BL_now = false;
//	return a;
//}

//nc_block& nc_block::operator-(double d_in)
//{
//	nc_block a;
//	a.block = &(*block - d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator+(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block + *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator+(double d_in)
//{
//	nc_block a;
//	a.block = &(*block + d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
////nc_block& nc_block::operator*(nc_block block_in)
////{
////	nc_block a;
////	a.block = &(*block * *block_in.block);
////	a.block->is_BL_now = false;
////	return a;
////}
//
//nc_block& nc_block::operator*(double d_in)
//{
//	nc_block a;
//	a.block = &((*block) * d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator/(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block / *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator/(double d_in)
//{
//	nc_block a;
//	a.block = &(*block / d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator%(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block % *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator%(double d_in)
//{
//	nc_block a;
//	a.block = &(*block % d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator<(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block < *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator<(double d_in)
//{
//	nc_block a;
//	a.block = &(*block < d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator>(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block > *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator>(double d_in)
//{
//	nc_block a;
//	a.block = &(*block > d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator<=(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block <= *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator<=(double d_in)
//{
//	nc_block a;
//	a.block = &(*block <= d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator>=(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block >= *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator>=(double d_in)
//{
//	nc_block a;
//	a.block = &(*block >= d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator==(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block == *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator==(double d_in)
//{
//	nc_block a;
//	a.block = &(*block == d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator!=(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block != *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator!=(double d_in)
//{
//	nc_block a;
//	a.block = &(*block != d_in);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator&&(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block && *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator^(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block ^ *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& nc_block::operator||(nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block || *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
nc_block nc_block::operator=(nc_block block_in)
{
	nc_block a;
	a.block = &(*block = *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block nc_block::operator=(double d_in)
{
	nc_block a;
	a.block = &(*block = d_in);
	a.block->is_BL_now = false;
	return a;
}
//
//nc_block& nc_block::operator<<(nc_block block_in)
//{
//	block = &((*block) << (*block_in.block));
//	return *this;
//}

nc_block_matrix33::~nc_block_matrix33()
{
	if (block_mat != nullptr)
	{
		if (block_mat->need_release == true)
		{
			delete block_mat;
		}
		else
		{
			
		}
	}
}

nc_block_matrix33::nc_block_matrix33()
{
	block_mat = 0;
}

nc_block_matrix33::nc_block_matrix33(nc_block_matrix33& mat_in)
{
	block_mat = mat_in.block_mat;
}

nc_block_matrix33::nc_block_matrix33(nb_NC_block_matrix33& mat_in)
{
	block_mat = &mat_in;
}

void nc_block_matrix33::replace(nc_block_matrix33 mat_in)
{
	block_mat = mat_in.block_mat;
}



nc_block nc_block_matrix33::operator()(int i, int j)
{
	nc_block a;
	a.block = &((*block_mat)(i, j));
	a.block->is_BL_now = false;
	return a;
}

nc_block_matrix33 nc_block_matrix33::operator+(nc_block_matrix33 mat_in)
{
	nc_block_matrix33 a;
	a.block_mat = &((*block_mat) + (*mat_in.block_mat));
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 nc_block_matrix33::operator+(mat33 mat_in)
{
	nc_block_matrix33 a;
	a.block_mat = &((*block_mat) + mat_in);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_matrix33::operator*(nc_block_vec3 vec_in)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_mat) * (*vec_in.block_vec));
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_matrix33::operator*(vec3 vec_in)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_mat) * vec_in);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_matrix33 nc_block_matrix33::operator*(nc_block_matrix33 mat_in)
{
	nc_block_matrix33 a;
	a.block_mat = &((*block_mat) * (*mat_in.block_mat));
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 nc_block_matrix33::operator*(mat33 mat_in)
{
	nc_block_matrix33 a;
	a.block_mat = &((*block_mat) * mat_in);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 nc_block_matrix33::operator*(double& dou)
{
	nc_block_matrix33 a;
	a.block_mat = &((*block_mat) * dou);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 nc_block_matrix33::operator*(nc_block bl)
{
	nc_block_matrix33 a;
	a.block_mat = &((*block_mat) * (*bl.block));
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_matrix33::col(int i)
{
	nc_block_vec3 a;
	a.block_vec = &(block_mat->col(i));
	a.block_vec->is_BL_now = false;
	return a;
}

void nc_block_matrix33::set_nc_Block(int i, int j, nc_block block_in)
{
	block_mat->set_NC_Block(i, j, *(block_in.block));

}

nc_block& nc_block_matrix33::operator=(nc_block_matrix33 mat_in)
{
	nc_block a;
	a.block = &((*block_mat) = (*(mat_in.block_mat)));
	a.block->is_BL_now = false;
	return a;
}

nc_block& nc_block_matrix33::operator=(mat33 mat_in)
{
	nc_block a;
	a.block = &((*block_mat) = mat_in);
	a.block->is_BL_now = false;
	return a;
}


nc_block_vec3::~nc_block_vec3()
{
	if (block_vec != nullptr)
	{
		if (block_vec->need_release == true)
		{
			delete block_vec;
		}
		else
		{
	
		}
	}
}

nc_block_vec3::nc_block_vec3()
{
	block_vec = 0;
}

nc_block_vec3::nc_block_vec3(nc_block_vec3& vec_in)
{
	block_vec = vec_in.block_vec;
}

nc_block_vec3::nc_block_vec3(nb_NC_block_vec3& vec_in)
{
	block_vec = &vec_in;
}

void nc_block_vec3::replace(nc_block_vec3 vec_in)
{
	block_vec = vec_in.block_vec;
}

void nc_block_vec3::set_nc_Block(int i, nc_block block_in)
{
	block_vec->set_NC_Block(i, *(block_in.block));
}

nc_block nc_block_vec3::operator()(int i)
{
	nc_block a;
	a.block = &((*block_vec)(i));
	a.block->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_vec3::operator+(nc_block_vec3 vec_in)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_vec) + (*vec_in.block_vec));
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_vec3::operator+(vec3 vec_in)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_vec) + vec_in);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_vec3::operator-(nc_block_vec3 vec_in)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_vec) - (*vec_in.block_vec));
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_vec3::operator-(vec3 vec_in)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_vec) - vec_in);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_vec3::operator*(double& dou)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_vec) * dou);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 nc_block_vec3::operator*(nc_block bl)
{
	nc_block_vec3 a;
	a.block_vec = &((*block_vec) * (*bl.block));
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block& nc_block_vec3::operator=(nc_block_vec3 vec_in)
{
	nc_block a;
	a.block = &((*block_vec) = (*vec_in.block_vec));
	a.block->is_BL_now = false;
	return a;
}

nc_block& nc_block_vec3::operator=(vec3 vec_in)
{
	nc_block a;
	a.block = &((*block_vec) = vec_in);
	a.block->is_BL_now = false;
	return a;
}


nc_block& new_BL_Block()
{
	nc_block* a = new nc_block(nb_new_BL_Block());
	return *a;
}

nc_block_vec3& new_BL_Vec()
{
	nc_block_vec3* a = new nc_block_vec3(nb_new_BL_Vec());
	return *a;
}

nc_block_vec3& new_uninit_BL_Vec()
{
	nc_block_vec3 a(nb_new_uninit_BL_Vec());
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_matrix33& new_uninit_BL_Mat()
{
	nc_block_matrix33 a(nb_new_uninit_BL_Mat());
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33& new_BL_Mat()
{
	nc_block_matrix33* a = new nc_block_matrix33(nb_new_BL_Mat());
	return *a;
}

nc_block BL_Block(int type, int no)
{
	nc_block a(nb_BL_Block(type, no));
	a.block->is_BL_now = false;
	return a;
}

NC_Prog_Block_API nc_block& new_BL(int no)
{
	nc_block* a = new nc_block(nb_new_BL_Block(no));
	return *a;
}

NC_Prog_Block_API nc_block& new_BL(nc_block block_in)
{
	nc_block* a = new nc_block();
	a->block = block_in.block;
	a->block->set_father(nb_NC_block::father_block);
	a->block->is_BL_now = true;
	return *a;
}

nc_block  BL(int no)
{
	nc_block a(nb_BL(no));
	a.block->is_BL_now = false;
	return a;
}

nc_block BL(nc_block no)
{
	nc_block a(nb_BL(*no.block));
	a.block->is_BL_now = false;
	return a;
}

void  ProBegin()
{
	nb_ProBegin();
}

void  ProEnd()
{
	nb_ProEnd();
}

void  reset_var_manager()
{
	machine_var_manager.reset();
}

nc_block FuHao(nc_block block_in)
{
	nc_block a(nb_FuHao(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block abs(nc_block block_in)
{
	nc_block a(nb_abs(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block acos(nc_block block_in)
{
	nc_block a(nb_acos(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block asin(nc_block block_in)
{
	nc_block a(nb_asin(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block atan(nc_block block_in)
{
	nc_block a(nb_atan(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block cos(nc_block block_in)
{
	nc_block a(nb_cos(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block sin(nc_block block_in)
{
	nc_block a(nb_sin(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block tan(nc_block block_in)
{
	nc_block a(nb_tan(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block ceil(nc_block block_in)
{
	nc_block a(nb_ceil(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block floor(nc_block block_in)
{
	nc_block a(nb_floor(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block round(nc_block block_in)
{
	nc_block a(nb_round(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block exp(nc_block block_in)
{
	nc_block a(nb_exp(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block ln(nc_block block_in)
{
	nc_block a(nb_ln(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block sqrt(nc_block block_in)
{
	nc_block a(nb_sqrt(*(block_in.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block max(nc_block block_in, nc_block block_in1)
{
	nc_block a(nb_max(*(block_in.block), *(block_in1.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block min(nc_block block_in, nc_block block_in1)
{
	nc_block a(nb_min(*(block_in.block), *(block_in1.block)));
	a.block->is_BL_now = false;
	return a;
}

nc_block pow(nc_block block_in, nc_block block_in1)
{
	nc_block a(nb_pow(*block_in.block, *block_in1.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block ChangShu(double d)
{
	nc_block a(nb_ChangShu(d));
	a.block->is_BL_now = false;
	return a;
}

nc_block operator!(nc_block block_in)
{
	nc_block a(!*block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator-(double d_in, nc_block block_in)
{
	nc_block a(d_in - *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator+(double d_in, nc_block block_in)
{
	nc_block a(d_in + *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator*(double d_in, nc_block block_in)
{
	nc_block a(d_in * *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator/(double d_in, nc_block block_in)
{
	nc_block a(d_in / *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator%(double d_in, nc_block block_in)
{
	nc_block a(d_in % *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator<(double d_in, nc_block block_in)
{
	nc_block a(d_in < *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator>(double d_in, nc_block block_in)
{
	nc_block a(d_in > *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator<=(double d_in, nc_block block_in)
{
	nc_block a(d_in <= *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator>=(double d_in, nc_block block_in)
{
	nc_block a(d_in >= *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator==(double d_in, nc_block block_in)
{
	nc_block a(d_in == *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator!=(double d_in, nc_block block_in)
{
	nc_block a(d_in != *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator*(nc_block block_in1,nc_block block_in2)
{
	nc_block a;
	a.block = &(*block_in1.block * *block_in2.block);
	a.block->is_BL_now = false;
	return a;
}
nc_block operator-(nc_block block_in1, nc_block block_in2) 
{
	nc_block a;
	a.block = &((*block_in1.block) - (*block_in2.block));
	a.block->is_BL_now = false;
	return a;
}
//nc_block a;
//	a.block = &(*block * *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
nc_block operator-(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block - d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator+(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block + *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator+(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block + d_in);
	a.block->is_BL_now = false;
	return a;
}

//nc_block& operator*(nc_block block_in1,nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block * *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}

nc_block operator*(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &((*block_in1.block) * d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator/(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block / *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator/(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block / d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator%(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block % *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator%(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block % d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator<(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block < *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator<(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block < d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator>(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block > *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator>(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block > d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator<=(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block <= *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator<=(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block <= d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator>=(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block >= *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator>=(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block >= d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator==(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block == *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator==(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block == d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator!=(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block != *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator!=(nc_block block_in1,double d_in)
{
	nc_block a;
	a.block = &(*block_in1.block != d_in);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator&&(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block && *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator^(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block ^ *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

nc_block operator||(nc_block block_in1,nc_block block_in)
{
	nc_block a;
	a.block = &(*block_in1.block || *block_in.block);
	a.block->is_BL_now = false;
	return a;
}

//nc_block& operator=(nc_block block_in1,nc_block block_in)
//{
//	nc_block a;
//	a.block = &(*block_in1.block = *block_in.block);
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block& operator=(nc_block block_in1,double d_in)
//{
//	nc_block a;
//	a.block = &(*block_in1.block = d_in);
//	a.block->is_BL_now = false;
//	return a;
//}

nc_block operator<<(nc_block& block_in1,nc_block block_in)
{
	block_in1.block = &((*block_in1.block) << (*block_in.block));
	return block_in1;
}

void operator>>(std::ofstream& oss, nc_block block_in)
{
	oss.open("serialized_data.bin", std::ios::app | std::ios::out|std::ios::binary);
	Serialize_infile(oss, *block_in.block);
	block_in.release_block_tree();
	oss.close();
}
nc_block SET_VALUE(nc_block zuobian, nc_block youbian)
{
	nc_block a(nb_SET_VALUE(*zuobian.block, *youbian.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block M00()
{
	nc_block a(nb_M00());
	a.block->is_BL_now = false;
	return a;
}

nc_block M01()
{
	nc_block a(nb_M01());
	a.block->is_BL_now = false;
	return a;
}

nc_block M02()
{
	nc_block a(nb_M02());
	a.block->is_BL_now = false;
	return a;
}

nc_block M03()
{
	nc_block a(nb_M03());
	a.block->is_BL_now = false;
	return a;
}

nc_block M04()
{
	nc_block a(nb_M04());
	a.block->is_BL_now = false;
	return a;
}

nc_block M05()
{
	nc_block a(nb_M05());
	a.block->is_BL_now = false;
	return a;
}

nc_block M06(int tool_using, int sl_pos_on_slz)
{
	nc_block a(nb_M06(tool_using, sl_pos_on_slz));
	a.block->is_BL_now = false;
	return a;

}

nc_block M08()
{
	nc_block a(nb_M08());
	a.block->is_BL_now = false;
	return a;
}

nc_block M09()
{
	nc_block a(nb_M09());
	a.block->is_BL_now = false;
	return a;
}

nc_block M30()
{
	nc_block a(nb_M30());
	a.block->is_BL_now = false;
	return a;
}

NC_Prog_Block_API nc_block M13()
{
	nc_block a(nb_M13());
	a.block->is_BL_now = false;
	return a;
}

NC_Prog_Block_API nc_block M14()
{
	nc_block a(nb_M14());
	a.block->is_BL_now = false;
	return a;
}

NC_Prog_Block_API nc_block M15()
{
	nc_block a(nb_M15());
	a.block->is_BL_now = false;
	return a;
}

nc_block G00()
{
	nc_block a(nb_G00());
	a.block->is_BL_now = false;
	return a;
}

nc_block G01()
{
	nc_block a(nb_G01());
	a.block->is_BL_now = false;
	return a;
}

nc_block G04()
{
	nc_block a(nb_G04());
	a.block->is_BL_now = false;
	return a;
}

nc_block G52()
{
	nc_block a(nb_G52());
	a.block->is_BL_now = false;
	return a;
}

nc_block G53()
{
	nc_block a(nb_G53());
	a.block->is_BL_now = false;
	return a;
}

nc_block G54()
{
	nc_block a(nb_G54());
	a.block->is_BL_now = false;
	return a;
}

nc_block G55()
{
	nc_block a(nb_G55());
	a.block->is_BL_now = false;
	return a;
}

nc_block G56()
{
	nc_block a(nb_G56());
	a.block->is_BL_now = false;
	return a;
}

nc_block G57()
{
	nc_block a(nb_G57());
	a.block->is_BL_now = false;
	return a;
}

nc_block G58()
{
	nc_block a(nb_G58());
	a.block->is_BL_now = false;
	return a;
}

nc_block G59()
{
	nc_block a(nb_G59());
	a.block->is_BL_now = false;
	return a;
}

nc_block G90()
{
	nc_block a(nb_G90());
	a.block->is_BL_now = false;
	return a;
}

//增加颜色设置块 3.28
nc_block Set_RGB(int color)
{
	//nc_block a(nb_Set_RGB(color));
	nc_block a(nb_Set_RGB(color));
	a.block->is_BL_now = false;
	return a;
}

nc_block WAIT()
{
	nc_block a(nb_WAIT());
	a.block->is_BL_now = false;
	return a;
}

nc_block M98(nc_block targer_block, int name_num)
{
	nc_block a(nb_M98(targer_block.block, name_num));
	a.block->is_BL_now = false;
	return a;
}

nc_block M99()
{
	nc_block a(nb_M99());
	a.block->is_BL_now = false;
	return a;
}

nc_block S_speed(int s)
{
	nc_block a(nb_S_speed(s));
	a.block->is_BL_now = false;
	return a;
}

NC_Prog_Block_API nc_block S2_speed(int s)
{
	nc_block a(nb_S2_speed(s));
	a.block->is_BL_now = false;
	return a;
}

nc_block G91()
{
	nc_block a(nb_G91());
	a.block->is_BL_now = false;
	return a;
}

nc_block F(double d_in)
{
	nc_block a(nb_F(d_in));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_A_C(nc_block x, nc_block y, nc_block z, nc_block as ,nc_block c)
{
	nc_block a(nb_G31_X_Y_Z_A_C(*x.block, *y.block, *z.block, *as.block, *c.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block X_Y_Z_A_C(nc_block x, nc_block y, nc_block z, nc_block as, nc_block c)
{
	nc_block a(nb_X_Y_Z_A_C(*x.block, *y.block, *z.block, *as.block, *c.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block X_Y_Z_A_C(double& x, double& y, double& z, double& as, double& c)
{
	nc_block a(X_Y_Z_A_C(ChangShu(x),ChangShu(y),ChangShu(z),ChangShu(as),ChangShu(c)));
	a.block->is_BL_now = false;
	return a;
}

nc_block X_Y_Z_A_C_F(nc_block x, nc_block y, nc_block z, nc_block as, nc_block c, nc_block f)
{
	nc_block a(nb_X_Y_Z_A_C_F(*x.block, *y.block, *z.block, *as.block, *c.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block X_Y_Z_A_C_F(double& x, double& y, double& z, double& as, double& c, double& f)
{
	nc_block a(X_Y_Z_A_C_F(
		ChangShu(x),
		ChangShu(y),
		ChangShu(z),
		ChangShu(as),
		ChangShu(c),
		ChangShu(f)
	));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_A_C_F(nc_block x, nc_block y, nc_block z, nc_block as, nc_block c, nc_block f)
{
	nc_block a(nb_G31_X_Y_Z_A_C_F(*x.block, *y.block, *z.block, *as.block, *c.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_Y_Z_A_C_F(nc_block x, nc_block y, nc_block z, nc_block as, nc_block c, nc_block f)
{
	nc_block a(nb_G01_X_Y_Z_A_C_F(*x.block, *y.block, *z.block, *as.block, *c.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_Y_Z_A_C_F(double x, double y, double z, double as, double c, double f)
{
	nc_block a(G01_X_Y_Z_A_C_F(
		ChangShu(x),
		ChangShu(y),
		ChangShu(z),
		ChangShu(as),
		ChangShu(c),
		ChangShu(f)
	));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_Y_Z_A_C(nc_block x, nc_block y, nc_block z, nc_block as, nc_block c)
{
	nc_block a(nb_G01_X_Y_Z_A_C(*x.block, *y.block, *z.block, *as.block, *c.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_Y_Z_A_C(double x, double y, double z, double as, double c)
{
	nc_block a(G01_X_Y_Z_A_C(
		ChangShu(x),
		ChangShu(y),
		ChangShu(z),
		ChangShu(as),
		ChangShu(c))
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block X(nc_block x)
{
	nc_block a(nb_X(*x.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block Y(nc_block y)
{
	nc_block a(nb_Y(*y.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block Z(nc_block z)
{
	nc_block a(nb_Z(*z.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block A(nc_block as)
{
	nc_block a(nb_A(*as.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block C(nc_block c)
{
	nc_block a(nb_C(*c.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block X_Y_Z(nc_block x, nc_block y, nc_block z)
{
	nc_block a(nb_X_Y_Z(*x.block, *y.block, *z.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block X_F(nc_block x, nc_block f)
{
	nc_block a(nb_X_F(*x.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block Y_F(nc_block y, nc_block f)
{
	nc_block a(nb_Y_F(*y.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block Z_F(nc_block z, nc_block f)
{
	nc_block a(nb_Z_F(*z.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block A_F(nc_block as, nc_block f)
{
	nc_block a(nb_A_F(*as.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block C_F(nc_block c, nc_block f)
{
	nc_block a(nb_C_F(*c.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f)
{
	nc_block a(nb_X_Y_Z_F(*x.block, *y.block, *z.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X(nc_block x)
{
	nc_block a(nb_G31_X(*x.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Y(nc_block y)
{
	nc_block a(nb_G31_Y(*y.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Z(nc_block z)
{
	nc_block a(nb_G31_Z(*z.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_A(nc_block as)
{
	nc_block a(nb_G31_A(*as.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_C(nc_block c)
{
	nc_block a(nb_G31_C(*c.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X(double x)
{
	nc_block a(G31_X(ChangShu(x)));
	a.block->is_BL_now = false;
	return a ;
}

nc_block G31_Y(double y)
{
	nc_block a(G31_Y(ChangShu(y)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Z(double z)
{
	nc_block a(G31_Z(ChangShu(z)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_A(double as)
{
	nc_block a(G31_A(ChangShu(as)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_C(double c)
{
	nc_block a(G31_C(ChangShu(c)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z(nc_block x, nc_block y, nc_block z)
{
	nc_block a(nb_G31_X_Y_Z(*x.block, *y.block, *z.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z(double x, double y, double z)
{
	nc_block a(G31_X_Y_Z(ChangShu(x), ChangShu(y), ChangShu(z)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_F(nc_block x, nc_block f)
{
	nc_block a(nb_G31_X_F(*x.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Y_F(nc_block y, nc_block f)
{
	nc_block a(nb_G31_Y_F(*y.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Z_F(nc_block z, nc_block f)
{
	nc_block a(nb_G31_Z_F(*z.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_A_F(nc_block as, nc_block f)
{
	nc_block a(nb_G31_A_F(*as.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_C_F(nc_block c, nc_block f)
{
	nc_block a(nb_G31_C_F(*c.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}
nc_block G31_X_F(double x, nc_block f)
{
	nc_block a(G31_X_F(ChangShu(x), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Y_F(double y, nc_block f)
{
	nc_block a(G31_Y_F(ChangShu(y), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Z_F(double z, nc_block f)
{
	nc_block a(G31_Z_F(ChangShu(z), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_A_F(double as, nc_block f)
{
	nc_block a(G31_A_F(ChangShu(as), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_C_F(double c, nc_block f)
{
	nc_block a(G31_C_F(ChangShu(c), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_F(nc_block x, double f)
{
	nc_block a(G31_X_F(x, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Y_F(nc_block y, double f)
{
	nc_block a(G31_Y_F(y, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Z_F(nc_block z, double f)
{
	nc_block a(G31_Z_F(z, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_A_F(nc_block as, double f)
{
	nc_block a(G31_A_F(as, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_C_F(nc_block c, double f)
{
	nc_block a(G31_C_F(c, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_F(double x, double f)
{
	nc_block a(G31_X_F(ChangShu(x), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Y_F(double y, double f)
{
	nc_block a(G31_Y_F(ChangShu(y), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_Z_F(double z, double f)
{
	nc_block a(G31_Z_F(ChangShu(z), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_A_F(double as, double f)
{
	nc_block a(G31_A_F(ChangShu(as), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_C_F(double c, double f)
{
	nc_block a(G31_C_F(ChangShu(c), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f)
{
	nc_block a(nb_G31_X_Y_Z_F(*x.block, *y.block, *z.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_F(nc_block x, nc_block y, nc_block z, double f)
{
	nc_block a(G31_X_Y_Z_F(x, y, z, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_F(double x, double y, double z, double f)
{
	nc_block a(G31_X_Y_Z_F(ChangShu(x), ChangShu(y), ChangShu(z), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_F(vec3 point, double f)
{
	nc_block a(G31_X_Y_Z_F(point(0), point(1), point(2), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_F(nc_block x, nc_block f)
{
	nc_block a(nb_G01_X_F(*x.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Y_F(nc_block y, nc_block f)
{
	nc_block a(nb_G01_Y_F(*y.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Z_F(nc_block z, nc_block f)
{
	nc_block a(nb_G01_Z_F(*z.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_A_F(nc_block as, nc_block f)
{
	nc_block a(nb_G01_A_F(*as.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_C_F(nc_block c, nc_block f)
{
	nc_block a(nb_G01_C_F(*c.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_F(nc_block x, double f)
{
	nc_block a(G01_X_F(x, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Y_F(nc_block y, double f)
{
	nc_block a(G01_Y_F(y, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Z_F(nc_block z, double f)
{
	nc_block a(G01_Z_F(z, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_A_F(nc_block as, double f)
{
	nc_block a(G01_A_F(as, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_C_F(nc_block c, double f)
{
	nc_block a(G01_C_F(c, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_F(double x, nc_block f)
{
	nc_block a(G01_X_F(ChangShu(x), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Y_F(double y, nc_block f)
{
	nc_block a(G01_Y_F(ChangShu(y), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Z_F(double z, nc_block f)
{
	nc_block a(G01_Z_F(ChangShu(z), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_A_F(double as, nc_block f)
{
	nc_block a(G01_A_F(ChangShu(as), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_C_F(double c, nc_block f)
{
	nc_block a(G01_C_F(ChangShu(c), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_F(double x, double f)
{
	nc_block a(G01_X_F(ChangShu(x), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Y_F(double y, double f)
{
	nc_block a(G01_Y_F(ChangShu(y), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_Z_F(double z, double f)
{
	nc_block a(G01_Z_F(ChangShu(z), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_A_F(double as, double f)
{
	nc_block a(G01_A_F(ChangShu(as), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

//nc_block  G01_X_F(nc_block& x, double f)
//{
//	nc_block a(G01_X_F(x, ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}

//nc_block  G01_Y_F(nc_block& y, double f)
//{
//	nc_block a(G01_Y_F(y, ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}

//nc_block  G01_Z_F(nc_block& z, double f)
//{
//	nc_block a(G01_Z_F(z, ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_A_F(nc_block& as, double f)
//{
//	nc_block a(G01_A_F(as, ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_C_F(nc_block& c, double f)
//{
//	nc_block a(G01_C_F(c, ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_X_F(double x, nc_block& f)
//{
//	nc_block a(G01_X_F(ChangShu(x), f));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_Y_F(double y, nc_block& f)
//{
//	nc_block a(G01_Y_F(ChangShu(y), f));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_Z_F(double z, nc_block& f)
//{
//	nc_block a(G01_Z_F(ChangShu(z), f));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_A_F(double as, nc_block& f)
//{
//	nc_block a(G01_A_F(ChangShu(as), f));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_C_F(double c, nc_block& f)
//{
//	nc_block a(G01_C_F(ChangShu(c), f));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_X_F(double x, double f)
//{
//	nc_block a(G01_X_F(ChangShu(x), ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_Y_F(double y, double f)
//{
//	nc_block a(G01_Y_F(ChangShu(y), ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_Z_F(double z, double f)
//{
//	nc_block a(G01_Z_F(ChangShu(z), ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}
//
//nc_block  G01_A_F(double as, double f)
//{
//	nc_block a(G01_A_F(ChangShu(as), ChangShu(f)));
//	a.block->is_BL_now = false;
//	return a;
//}
//
nc_block G01_C_F(double c, double f)
{
	nc_block a(G01_C_F(ChangShu(c), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}


nc_block G01_X_Y_Z_F(nc_block x, nc_block y, nc_block z, nc_block f)
{
	nc_block a(nb_G01_X_Y_Z_F(*x.block, *y.block, *z.block, *f.block));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z(nc_block_vec3 point)
{
	nc_block a(G31_X_Y_Z(point(0), point(1), point(2)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_F(nc_block_vec3 point, nc_block f)
{
	nc_block a(G31_X_Y_Z_F(point(0), point(1), point(2), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_Y_Z_F(nc_block_vec3 point, nc_block f)
{
	nc_block a(G01_X_Y_Z_F(point(0), point(1), point(2), f));
	a.block->is_BL_now = false;
	return a;
}

nc_block G31_X_Y_Z_F(nc_block_vec3 point, double f)
{
	nc_block a(G31_X_Y_Z_F(point, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_Y_Z_F(nc_block_vec3 point, double f)
{
	nc_block a(G01_X_Y_Z_F(point, ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block G01_X_Y_Z_F(vec3 point, double f)
{
	nc_block a(G01_X_Y_Z_F(ChangShu(point(0)), ChangShu(point(1)), ChangShu(point(2)), ChangShu(f)));
	a.block->is_BL_now = false;
	return a;
}

nc_block BREAK()
{
	nc_block a
	(
		EXIT_zi()
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block WHILE_K(nc_block tiaojian, nc_block xunhuanti)
{
	nc_block a
	(
		nb_WHILE_K(*tiaojian.block, *xunhuanti.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block IF_K(nc_block tiaojian, nc_block zhuti)
{
	nc_block a
	(
		nb_IF_K(*tiaojian.block, *zhuti.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block IF_ELSE_K(nc_block tiaojian, nc_block zhuti1, nc_block zhuti2)
{
	nc_block a
	(
		nb_IF_ELSE_K(*tiaojian.block, *zhuti1.block, *zhuti2.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block IF_ELSEIF_ELSE_K(nc_block tiaojian1, nc_block zhuti1, nc_block tiaojian2, nc_block zhuti2, nc_block zhuti3)
{
	nc_block a
	(
		nb_IF_ELSEIF_ELSE_K(*tiaojian1.block, *zhuti1.block, *tiaojian2.block, *zhuti2.block, *zhuti3.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Process_K(int i)
{
	nc_block a
	(
		nb_Process_K(i)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block_vec3 operator+(vec3 vec, nc_block_vec3 vec1)
{
	nc_block_vec3 a(
		vec + *vec1.block_vec
	);
	a.block_vec->is_BL_now = false;
	return a;

}

nc_block_vec3 operator-(vec3 vec, nc_block_vec3 vec1)
{
	nc_block_vec3 a(
		vec - *vec1.block_vec
	);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 operator*(double dou, nc_block_vec3 vec1)
{
	nc_block_vec3 a(
		(*vec1.block_vec) * dou
	);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 operator*(nc_block dou, nc_block_vec3 vec1)
{
	nc_block_vec3 a(
		(*vec1.block_vec) * (*dou.block)
	);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block dot(nc_block_vec3 vec, nc_block_vec3 vec1)
{
	nc_block a(
		nb_dot(*vec.block_vec, *vec1.block_vec)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block dot(vec3 vec, nc_block_vec3 vec1)
{
	nc_block a(
		nb_dot(vec, *vec1.block_vec)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block dot(nc_block_vec3 vec, vec3 vec1)
{
	nc_block a(
		nb_dot(*vec.block_vec, vec1)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block_vec3 cross(nc_block_vec3 vec, nc_block_vec3 vec1)
{
	nc_block_vec3 a(
		nb_cross(*vec.block_vec, *vec1.block_vec)
	);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 cross(vec3 vec, nc_block_vec3 vec1)
{
	nc_block_vec3 a(
		nb_cross(vec, *vec1.block_vec)
	);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_vec3 cross(nc_block_vec3 vec, vec3 vec1)
{
	nc_block_vec3 a(
		nb_cross(*vec.block_vec, vec1)
	);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block_matrix33 operator*(mat33 mat_in, nc_block_matrix33 mat_in1)
{
	nc_block_matrix33 a(
		mat_in * (*mat_in1.block_mat)
	);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 operator*(double dou, nc_block_matrix33 mat_in1)
{
	nc_block_matrix33 a(
		dou * (*mat_in1.block_mat)
	);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 operator*(nc_block bl, nc_block_matrix33 mat_in1)
{
	nc_block_matrix33 a(
		(*bl.block) * (*mat_in1.block_mat)
	);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_vec3 operator*(mat33 mat_in, nc_block_vec3 vec_in)
{
	nc_block_vec3 a(
		mat_in * (*vec_in.block_vec)
	);
	a.block_vec->is_BL_now = false;
	return a;
}

nc_block Angle_between_2_vec(nc_block_vec3 vec1, nc_block_vec3 vec2)
{
	nc_block a(
		nb_Angle_between_2_vec(*vec1.block_vec, *vec2.block_vec)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_between_2_vec(vec3 vec1, nc_block_vec3 vec2)
{
	nc_block a(
		nb_Angle_between_2_vec(vec1, *vec2.block_vec)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_between_2_vec(nc_block_vec3 vec1, vec3 vec2)
{
	nc_block a(
		nb_Angle_between_2_vec(*vec1.block_vec, vec2)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans)
{
	nc_block a(
		nb_Angle_from_a_to_b_around_c(*vec1.block_vec, *vec2.block_vec, *vec3.block_vec, *ans.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, nc_block_vec3 vec3, nc_block ans)
{
	nc_block a(
		nb_Angle_from_a_to_b_around_c(vec1, *vec2.block_vec, *vec3.block_vec, *ans.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, nc_block_vec3 vec3, nc_block ans)
{
	nc_block a(
		nb_Angle_from_a_to_b_around_c(*vec1.block_vec, vec2, *vec3.block_vec, *ans.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans)
{
	nc_block a(
		nb_Angle_from_a_to_b_around_c(*vec1.block_vec, *vec2.block_vec, vec3, *ans.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_from_a_to_b_around_c(nc_block_vec3 vec1, vec3 vec2, vec3 vec3, nc_block ans)
{
	nc_block a(
		nb_Angle_from_a_to_b_around_c(*vec1.block_vec, vec2, vec3, *ans.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block Angle_from_a_to_b_around_c(vec3 vec1, nc_block_vec3 vec2, vec3 vec3, nc_block ans)
{
	nc_block a(
		nb_Angle_from_a_to_b_around_c(vec1, *vec2.block_vec, vec3, *ans.block)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block_matrix33 RotX(nc_block block_in)
{
	nc_block_matrix33 a(
		nb_RotX(*(block_in.block))
	);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 RotY(nc_block block_in)
{
	nc_block_matrix33 a(
		nb_RotY(*(block_in.block))
	);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block_matrix33 RotZ(nc_block block_in)
{
	nc_block_matrix33 a(
		nb_RotZ(*(block_in.block))
	);
	a.block_mat->is_BL_now = false;
	return a;
}

nc_block norm(nc_block_vec3 vec_in)
{
	nc_block a(
		nb_norm(*vec_in.block_vec)
	);
	a.block->is_BL_now = false;
	return a;
}

nc_block_vec3 normalise(nc_block_vec3 vec_in)
{
	nc_block_vec3 a(
		nb_normalise(*vec_in.block_vec)
	);
	a.block_vec->is_BL_now = false;
	return a;
}


//nc_block Recover_block()
//{
//	nc_block* a = new nc_block(Deserialize());
//	if (a->block->Block_type_index == BH_M98)
//	{
//		unsigned char* ans_value_ptr = reinterpret_cast<unsigned char*>(&a->block->ans_value);
//		int nc_name = 0;
//		std::memcpy(&nc_name, ans_value_ptr, sizeof(nc_name)); // 拷贝4字节  
//		f_manager->file_pos_get(nc_name);
//	}
//	else if (a->block->Block_type_index == BH_M99)
//	{
//		f_manager->recovery_now_file_pos();
//	}
//	else if (a->block->Block_type_index == BH_M30)
//	{
//		std::ifstream ifile("E:\\ml_240221\\serialized_data.bin", std::ios::binary); // 打开文件  
//
//		if (!ifile.is_open()) {
//			std::cerr << "Error opening file!" << std::endl;
//		}
//		// 移动到文件末尾  
//		ifile.seekg(0, std::ios::end); // 将读取位置移动到文件末尾  
//
//		nb_NC_block::position = ifile.tellg(); //位置定位文件末尾
//	}
//	delete f_manager;
//	std::ofstream ofile1("E:\\ml_240221\\serialized_data.bin", std::ios::binary | std::ios::trunc);
//	if (!ofile1) {
//		std::cerr << "无法打开文件serialized_data进行清空: " << std::endl;
//	}
//	std::cout << "文件已被清空: " << endl;
//
//	return *a;
//}
//
//bool reset_block()
//{
//	std::ifstream ifile("E:\\ml_240221\\serialized_data.bin", std::ios::binary); // 打开文件  
//	if (!ifile.is_open()) {
//		std::cerr << "Error opening file!" << std::endl;
//		return 1;
//	}
//	ifile.seekg(0, std::ios::beg); // 将读取位置移动到文件开头  
//
//	nb_NC_block::position = ifile.tellg(); //位置定位文件末尾
//
//}
//
//bool Recover_nc_code()
//{
//	//file_manager* af_manager = f_manager;
//	std::ifstream ifile("E:\\ml_240221\\serialized_data_menu.bin", std::ios::binary);
//	if (!ifile.is_open()) {
//		throw std::runtime_error("文件打开失败");
//	}
//
//	while (true) {
//		int name = 0;
//		std::streampos startSize = 0, endSize = 0;
//		// 读取 name (int 类型)  
//		ifile.read(reinterpret_cast<char*>(&name), sizeof(name));
//		if (ifile.eof()) {
//			std::cout << "读取已完成，文件末尾已到达。" << std::endl; // 提示读取已完成  
//			break; // 到达文件末尾，退出循环  
//	    }
//			if (ifile.fail()) {
//				ifile.close();
//				throw std::runtime_error("读取 name 失败");
//			}
//
//			// 读取 fileSize Start (std::streamsize 类型)  
//			ifile.read(reinterpret_cast<char*>(&startSize), sizeof(startSize));
//			if (ifile.fail()) {
//				ifile.close();
//				throw std::runtime_error("读取 fileSize Start 失败");
//			}
//
//			// 读取 fileSize End (std::streamsize 类型)  
//			ifile.read(reinterpret_cast<char*>(&endSize), sizeof(endSize));
//			if (ifile.fail()) {
//				ifile.close();
//				throw std::runtime_error("读取 fileSize End 失败");
//			}
//
//			string f_p = "E:\\ml_240221\\";
//			string dir = f_p + "O" + std::to_string(name);
//			std::ofstream ofile(dir, ios::trunc | ios::out);
//			ofile << "% @MACRO" << endl;
//			ofile.close();
//
//			nb_NC_block::position = startSize;
//
//			while (nb_NC_block::position < endSize)
//			{
//				nc_block* a = new nc_block(Deserialize());
//				a->block->write_nc_code();
//				ofile.open(dir, ios::app | ios::out);
//				ofile << a->block->NC_code;
//
//				if (a->block->Block_type_index == BH_M30)
//				{
//					const std::string filePath = "E:\\ml_240221\\serialized_data.bin";
//					std::ifstream ifile(filePath, std::ios::binary);
//					// 定位到文件末尾并获取大小  
//					ifile.seekg(endSize); // 移动到文件末尾  
//					nb_NC_block::position = ifile.tellg(); // 获取当前指针位置
//				}
//
//				a->release_block_tree();
//				ofile.close();
//			}
//
//		}
//
//		delete f_manager;
//		std::ofstream ofile1("E:\\ml_240221\\serialized_data.bin", std::ios::binary | std::ios::trunc);
//		std::ofstream ofile2("E:\\ml_240221\\serialized_data_menu.bin", std::ios::binary | std::ios::trunc);
//		if (!ofile1) {
//			std::cerr << "无法打开文件serialized_data进行清空: "<< std::endl;
//			return 1;
//		}
//		if (!ofile2) {
//			std::cerr << "无法打开文件serialized_data_menu进行清空: " << std::endl;
//			return 1;
//		}
//		std::cout << "文件已被清空: " << endl;
//		return true;
//
//	
//}

