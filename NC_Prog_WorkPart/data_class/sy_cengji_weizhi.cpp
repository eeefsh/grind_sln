#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include"sy_cengji_weizhi.h"
#include"obj_cell.h"



void index_cells::del_cell(obj_cell* cp, octree*& ptr_zu, int aim_depth)
{
	map_pos.erase(cp->get_int3v());
	oc_tree.delete_obj(cp, ptr_zu, aim_depth);
}

void index_cells::init_all_cells_face_num(double d)
{
	int test_num = 0;
	vector<int3v> will_del;
	//遍历map，逐个初始化点
	auto it = map_pos.begin();
	for (; it != map_pos.end(); it++)
	{
		obj_cell* cur_cell = it->second;
		//找到点的面状态为外：1 的位置：0-5
		if (test_num == 9)
		{
			int i = 0;	//num==9
		}
		test_num++;
		//11.16 test 一个cell为内部点 但有一个外面(有问题) 造成后续初始化错误  --9.5补上了
		vector<int> save_out;
		//vector<int> true_out;
		cur_cell->get_all_face_dir_out(save_out);

		for (int i = 0; i < save_out.size(); i++ )
		{
			int side_now = save_out[i];
			vector<int> vec_side_pang;
			cur_cell->get_wai_side(side_now, vec_side_pang);
			int side_dui = cur_cell->cal_duimian_num(side_now);

			//逐个判断四个旁边面的内外情况
			vector<int> much_out;
			for (int i = 0; i < vec_side_pang.size(); i++)
			{
				//计算指定方向相邻的坐标
				int3v coor_the_pang_side = cur_cell->cal_side_p_int(vec_side_pang[i], d);
				int3v coor_the_pang_xie = cur_cell->cal_xie_side(side_now, vec_side_pang[i], d);

				//如果旁边位置不存在cell  &&  如果本位和旁边都相邻的位置不存在cell
				if (!is_the_point_exist(coor_the_pang_side))
				{ 
					if (!is_the_point_exist(coor_the_pang_xie))
					{
						//设置指定方向为外
						cur_cell->set_face_out(vec_side_pang[i]);
						much_out.push_back(vec_side_pang[i]);
					}
				}
			}

			//判断对面的内外情况
			//四个邻面中有一个外 就可判断对面内外
			bool has_xie = 0;
			bool has_out = 0;
			for (int i = 0; i < much_out.size(); i++)
			{
				has_out = 1; //没进表示 四个面都没外   有外且无斜被删
				if (cur_cell->is_the_side_out(much_out[i]))//当前邻面为外 -- 被前一轮面赋值》记录赋值
				{
					int3v op = cur_cell->cal_xie_side(much_out[i], side_dui, d);
					//斜角cell不存在
					if (!is_the_point_exist(op))
					{
						int3v op_dui = cur_cell->cal_side_p_int(side_dui, d);
						if (!is_the_point_exist(op_dui))
						{
							cur_cell->set_face_out(side_dui);
						}
					}
					//break;
					else
					{
						int3v op_dui = cur_cell->cal_side_p_int(side_dui, d);
						if (!is_the_point_exist(op_dui))
						{
							has_xie = 1;
						}
					}
				}
			}
			/*if (has_xie)
			{
				cur_cell->set_face_in(side_dui);
			}
			else
			{
				cur_cell->set_face_out(side_dui);
			}*/
			
	
			//判断外面的所对的cell是否存在
			bool has_op = 0;
			{
				int3v op = cur_cell->cal_side_p_int(side_now, d);
				if (is_the_point_exist(op))
				{
					cur_cell->set_face_in(side_now);
					if (!has_xie && !has_out)	//且四个相邻都是内，则为内部点
					{
						will_del.emplace_back(cur_cell->get_int3v());
						break;
					}
				}
			}

			//六个面全为内 删除cell
			if (cur_cell->get_num() == 0)
			{
				will_del.emplace_back(cur_cell->get_int3v());
				//it = map_pos.erase(it);
				//it--;
				break;
			}

			//判断现在的外是否与保留相对  11.17 加
			vector<int> now_out;
			cur_cell->get_all_face_dir_out(now_out);
			
				if (is_opp_save_and_now(save_out, now_out) && !has_xie && has_out)	//0.9 右边单独一列被删除 
				{
					//先不删记录坐标值，最后统一删 ,中途删除影响后续判断
					will_del.emplace_back(cur_cell->get_int3v());
					//it = map_pos.erase(it);
					//it--;
					break;
				}
			
		}
		//if (true_out.size() == 0)
		//{
		//	it = map_pos.erase(it);	//只有两个分量删除 不对
		//	it--;
		//	continue;
		//}
	}
	for (int i = 0; i < will_del.size(); i++)
	{
		map_pos.erase(will_del[i]);
	}
}

void index_cells::set_acc(double d)
{
	accuracy = abs(d);
}

obj_cell* index_cells::new_a_cutted_cell(int3v& op,int cutting_dir)
{
	obj_cell* obj = new obj_cell(op);
	if (cutting_dir % 2 == 1)
	{
		obj->set_face_out(cutting_dir - 1);
	}
	else
	{
		obj->set_face_out(cutting_dir + 1);
	}
	return obj;
}

bool index_cells::is_the_point_exist(int3v& op)
{
	auto it = map_pos.end();
	if (it == map_pos.find(op))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool index_cells::is_the_point_exist_at_xie(int3v& op)
{
	auto it = map_pos.end();
	if (it == map_pos.find(op))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool index_cells::is_opp_save_and_now(vector<int>& save_out, vector<int>& now_out)
{
	int size_save = save_out.size();
	int opp_count = 0;
	for (int i = 0; i <size_save; i++)
	{
		int cur_out = save_out[i];
		int cur_opp;
		if (cur_out % 2 == 0)
		{
			cur_opp = cur_out + 1;
		}
		else
		{
			cur_opp = cur_out - 1;
		}
		for (int j = 0; j < now_out.size(); j++)
		{
			if (now_out[j] == cur_opp) //存在
			{
				opp_count++;
			}
		}
	}
	if (opp_count == size_save)
	{
		return true;
	}
	return false;
}

index_cells::index_cells()
{
}

index_cells::~index_cells()
{
}

void index_cells::add_cell_to_map(obj_cell* cp)
{
	map_pos.insert(pair<int3v, obj_cell*>(cp->get_int3v(),cp));
}

void index_cells::add_cell_to_tree(obj_cell* cp)
{
	oc_tree.add_obj(cp);
}




