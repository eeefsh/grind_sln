#include"..\pch.h"
#define NC_Prog_WorkPart_EXPORTS
#include "octree.h"
#include"obj_cell.h"


octree::octree()
{
    father = nullptr;
    for (size_t i = 0; i < 8; i++)
    {
        child[i] = nullptr;
    }
    place_flag = 0;
    depth = 0;
    L = 0;
}

octree::octree(octree* p,
    int L_in,
    unsigned char depth_in,
    int3v C_point_in,
    unsigned char Place_flag_in)
{
    father = p;
    L = L_in;
    depth = depth_in;
    c_point = C_point_in;
    place_flag = Place_flag_in;
    for (size_t i = 0; i < 8; i++)
    {
        child[i] = nullptr;
    }
}

octree::~octree()
{

    for (size_t i = 0; i < 8; i++)
    {
        if (child[i] != nullptr)
        {
            //判断到第1层
            if (is_bottom())
            {
                delete ((obj_cell*)(child[i]));
            }
            else
            {
                delete child[i];
            }
            child[i] = nullptr;
        }
    }
}

void octree::init_tree(cube_box& box)
{
    int temp = 0;
    //判断是在顶层
    if (!is_top())
    {
        return;
    }
    //获得八叉树中心位置
    c_point = box.get_double3v();
    //计算八叉树的深度
    //
    for (unsigned char i = 0; i < 20; i++)
    {
        temp = pow(2, i);//当前盒子边长上cell的个数（能装下的最大值）
        if (box.get_n() <= temp)
        {
            depth = i;
            break;
        }
    }
    //计算八叉树的宽度
    L = temp * box.get_w();//能装下cell数的2倍
}

bool octree::add_obj(obj_cell* p)
{
    int3v c_temp;
    unsigned char n;
    
    //获取当前子级位置
    n = (((p->c_point.x - c_point.x) > 0) << 2) 
        | (((p->c_point.y - c_point.y) > 0) << 1) 
        | ((p->c_point.z - c_point.z) > 0); 
    //判断没有到第1层
    if (!is_bottom())
    {
        //判断子级不存在
        if (child[n] == nullptr)
        {
            //创建一个八叉树
            c_temp.x = (p->c_point.x - c_point.x) > 0 ? c_point.x + L / 4 : c_point.x - L / 4;
            c_temp.y = (p->c_point.y - c_point.y) > 0 ? c_point.y + L / 4 : c_point.y - L / 4;
            c_temp.z = (p->c_point.z - c_point.z) > 0 ? c_point.z + L / 4 : c_point.z - L / 4;
            child[n] = new octree(this, L / 2, depth - 1, c_temp, n);
            //set_p.erase(child[n]);

            if (child[n] == nullptr)
            {
                return false;
            }
        }
        //递归到子级中去添加对象
        child[n]->add_obj(p);
    }
    //到第1层，将对象指针转换后存到父级八叉树对应位置
    else
    {
        p->place_flag = n;
        child[n] = reinterpret_cast<octree*>(p);
        p->father = this;
    }
    return true;
}


void octree::delete_obj(obj_cell* p, octree*& ptr_zu, int aim_depth)
{
    unsigned char n = 0;
    unsigned char n1 = 0;
    octree* p_temp = nullptr;
    //在父级把当前指针位置指空
    p->father->child[p->place_flag] = nullptr;
    //获取父级指针
    p_temp = p->father;

    //删除对象
    delete p;

    //删除没有子级的八叉树
    while (n1 < 100)
    {
        //判断到顶层跳出循环
        if (p_temp->is_top())
        {
            break;
        }
        //判断是没有子级的八叉树
        if (!(p_temp->has_child()))
        {
            //获取当前在父级下面的位置
            n = p_temp->place_flag;
            //指针向上移动一层
            octree* box_up = p_temp->father;

            box_up->child[n] = nullptr;
            
            //计算当前树的组号 如果删除在group里也删除
            //int cur_list_index = cal_list_num(*p_temp);
            /*if (group_octree.find(p_temp) != group_octree.end())
            {
                group_octree.erase(p_temp);
            }*/
            if (p_temp->get_depth() == aim_depth) 
            {
                ptr_zu = p_temp;
            }
            else
            {
                ptr_zu = nullptr;
            }
            delete p_temp;

            p_temp = box_up;

        }
        else
        {
            break;
        }
        n1++;
    }
}





unsigned char octree::get_child_octree(queue<octree*> &ptrVector)
{
    unsigned char n = 0;
    if (!is_bottom())
    {
        for (size_t i = 0; i < 8; i++)
        {
            if (child[i] != nullptr) 
            {
                ptrVector.push(child[i]);
                n++;
            }
        }
    }
    return n;
}


unsigned char octree::get_child_obj(queue<obj_cell*>& ptrVector)
{
    unsigned char n = 0;
    if (is_bottom())
    {
        for (size_t i = 0; i < 8; i++)
        {
            if (child[i] != nullptr)
            {
                ptrVector.push(reinterpret_cast<obj_cell*>(child[i]));
                n++;
            }
        }
    }
    return n;
}



octree* octree::get_father_octree()
{
    return father;
}

void octree::get_all_obj(queue<obj_cell*>& ptrVector)
{

    unsigned char n = 0;
    queue<octree*> ptrOctree;
    if (is_bottom())
    {
        get_child_obj(ptrVector);
    }
    else
    {
        n = get_child_octree(ptrOctree);
        while (!ptrOctree.empty())
        {
            ptrOctree.front()->get_all_obj(ptrVector);
            ptrOctree.pop();
        }
    }
}

double3v octree::get_double3v(double acc)
{
    
    return c_point.turn_point_double(acc);
}

bool octree::is_bottom()
{
    if (depth > 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

unsigned char octree::get_depth()
{
    return depth;
}

int octree::get_L()
{
    //L就是一行cell的个数
    return L;
}

double octree::get_r(double acc_d)
{   
   /* return double(L) * acc_d / 2.0 * sqrt(3.0);;*/
    double L_shiji = L /1000.0/2.0;
    return sqrt(3.0) * L_shiji ;
}

unsigned int octree::get_nodes2last(unsigned char n)
{
    int temp = 0;
    if (is_top())
    {
        temp = pow(8, depth - n);
        return temp;
    }
    return 0;
}

int3v octree::get_c_point()
{
    return c_point;
}

bool octree::has_child()
{
    for (size_t i = 0; i < 8; i++)
    {
        if (child[i] != nullptr)
        {
            return true;
        }
    }
    return false;
}

bool octree::is_top()
{
    if (father == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}