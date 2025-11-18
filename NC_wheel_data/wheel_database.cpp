#include "pch.h"

#define NC_wheel_data_EXPORTS
#include "wheel_database.h"

namespace wheel_database_namespace
{
    void data_rw::Init_dir(std::string& _dir)
    {
        dir = _dir;
    }

    void data_rw::writeToFile(std::streampos pos, wheel_data& val)
    {
        file.open(dir, std::ios::in | std::ios::out | std::ios::binary);
        file.seekp(pos);
        file.write(reinterpret_cast<char*>(&val), sizeof(val));
        file.close();
    }

    void data_rw::readFromFile(std::streampos pos, wheel_data& val)
    {
        file.open(dir, std::ios::in | std::ios::binary);
        file.seekg(pos);
        file.read(reinterpret_cast<char*>(&val), sizeof(val));
        file.close();
    }

    void data_rw::writeToFile(std::streampos pos, group_data& val)
    {
        file.open(dir, std::ios::in | std::ios::out | std::ios::binary);
        file.seekp(pos);
        file.write(reinterpret_cast<char*>(&val), sizeof(val));
        file.close();
    }

    void data_rw::readFromFile(std::streampos pos, group_data& val)
    {
        file.open(dir, std::ios::in | std::ios::binary);
        file.seekg(pos);
        file.read(reinterpret_cast<char*>(&val), sizeof(val));
        file.close();
    }
    void list_rw::Init_dir(std::string& _dir)
    {
        dir = _dir;
    }

    void list_rw::writeToList(std::set<list_time>& val)
    {
        file.open(dir, std::ios::out | std::ios::trunc | std::ios::binary);
        
        size_t temp = pos_temp.size();
        //写入空位的数量
        file.write(reinterpret_cast<char*>(&temp), sizeof(size_t));
        temp = sizeof(size_t) * temp;
        //写入空位pos
        file.write(reinterpret_cast<char*>(pos_temp.data()), temp);

        file.seekp(sizeof(size_t) * 200);
        size_t size_slz = val.size();
        //写入索引的数量
        file.write(reinterpret_cast<char*>(&size_slz), sizeof(size_slz));
        //写入索引数据
        for (auto it = val.begin(); it != val.end(); ++it)
        {
            file.write(reinterpret_cast<const char*>(&(*it)), sizeof(list_time));
        }
        file.close();
    }

    void list_rw::readFromList(std::set<list_time>& val)
    {
        file.open(dir, std::ios::in | std::ios::binary);
        pos_temp.clear();
        size_t size_n = 0;
        //读取数量
        file.read(reinterpret_cast<char*>(&size_n), sizeof(size_n));
        pos_temp.resize(size_n);
        size_n = size_n * sizeof(pos_temp[0]);
        file.read(reinterpret_cast<char*>(pos_temp.data()), size_n);

        file.seekg(sizeof(size_t) * 200);

        val.clear();
        list_time temp;
        //读取数量
        file.read(reinterpret_cast<char*>(&size_n), sizeof(size_n));
        //读取数据
        for (size_t i = 0; i < size_n; i++)
        {
            file.read(reinterpret_cast<char*>(&temp), sizeof(list_time));
            val.insert(temp);
        }
        file.close();
    }

    void wheel_data::set_name(std::string name)
    {
        for (size_t i = 0; i < sizeof(name_wheel); i++)
        {
            name_wheel[i] = 0;
        }
        if (name.size() <= sizeof(name_wheel))
        {
            std::memcpy(name_wheel, name.data(), name.size());
        }
        else
        {
            std::memcpy(name_wheel, name.data(), sizeof(name_wheel));
        }
    }

    std::string wheel_data::get_name()
    {
        std::string ans = name_wheel;
        return ans;
    }

    void wheel_data::set_dir_dxf(std::string name)
    {
        if (name.size() <= sizeof(dir_dxf))
        {
            std::memcpy(dir_dxf, name.data(), name.size());
        }
        else
        {
            std::memcpy(dir_dxf, name.data(), sizeof(dir_dxf));
        }
    }

    std::string wheel_data::get_dir_dxf()
    {
        std::string ans = dir_dxf;
        return ans;
    }

    void wheel_data::clear()
    {
        key_wheel = -1;
        type_wheel = -1;
        key_group = -1;
        daozhuang = 0;
        Celiang_flag = 0;
        for (size_t i = 0; i < sizeof(name_wheel); i++)
        {
            name_wheel[i] = 0;
        }
        for (size_t i = 0; i < sizeof(dir_dxf); i++)
        {
            dir_dxf[i] = 0;
        }
        for (size_t i = 0; i < (sizeof(data) / sizeof(data[0])); i++)
        {
            data[i] = 0.0;
        }
    }

    void group_data::set_name(std::string name)
    {
        for (size_t i = 0; i < sizeof(name_group); i++)
        {
            name_group[i] = 0;
        }
        if (name.size() <= sizeof(name_group))
        {
            std::memcpy(name_group, name.data(), name.size());
        }
        else
        {
            std::memcpy(name_group, name.data(), sizeof(name_group));
        }
    }

    std::string group_data::get_name()
    {
        std::string ans = name_group;
        return ans;
    }

    void group_data::clear()
    {
        key_group = -1;
        num_daojia = -1;
        gan_D = 0;
        nut_D = 0;
        nut_L = 0;
        weizhi_cankao temp;
        for (size_t i = 0; i < sizeof(weizhi)/ sizeof(weizhi[0]); i++)
        {
            weizhi[i] = temp;
        }
    }
}

//全部砂轮索引
std::set<wheel_database_namespace::list_time> wheel_database::list_wheel_all;

//全部砂轮组索引
std::set<wheel_database_namespace::list_time> wheel_database::list_group_all;

//被修改的砂轮id缓存
std::set<int> wheel_database::edit_buff_wheel;

void wheel_database::set_wheel_group_key(wheel_database_namespace::group_data& val)
{
    for (size_t i = 0; i < sizeof(val.weizhi) / sizeof(val.weizhi[0]); i++)
    {
        if (val.weizhi[i].key_wheel == -1)
        {
            continue;
        }
        auto temp = read_wheel(val.weizhi[i].key_wheel);
        temp.key_group = val.key_group;
        temp.data[0] = val.weizhi[i].distance;
        edit_wheel(temp.key_wheel, temp, 1);
    }
}

void wheel_database::clear_wheel_group_key(wheel_database_namespace::group_data& val)
{
    for (size_t i = 0; i < sizeof(val.weizhi) / sizeof(val.weizhi[0]); i++)
    {
        if (val.weizhi[i].key_wheel == -1)
        {
            continue;
        }
        auto temp = read_wheel(val.weizhi[i].key_wheel);
        temp.key_group = -1;
        temp.data[0] = 0;
        edit_wheel(temp.key_wheel, temp, 1);
        val.weizhi[i].key_wheel = -1;
    }
}

void wheel_database::Init_Dir(
    std::string dir_list_wheel,
    std::string dir_data_wheel,
    std::string dir_list_group,
    std::string dir_data_group)
{
    rw_list_wheel.Init_dir(dir_list_wheel);
    rw_data_wheel.Init_dir(dir_data_wheel);
    rw_list_group.Init_dir(dir_list_group);
    rw_data_group.Init_dir(dir_data_group);

    rw_list_wheel.readFromList(list_wheel_all);
    rw_list_group.readFromList(list_group_all);
}

int wheel_database::add_wheel(wheel_database_namespace::wheel_data val)
{
    std::streampos pos;
    //获取文件pos
    if (rw_list_wheel.pos_temp.size() > 0)
    {
        pos = rw_list_wheel.pos_temp.back();
        rw_list_wheel.pos_temp.pop_back();
    }
    else
    {
        pos = list_wheel_all.size() * sizeof(val);
    }
    val.key_wheel = pos;
    rw_data_wheel.writeToFile(pos, val);
    //更新索引
    wheel_database_namespace::list_time temp;
    temp.pos = pos;
    list_wheel_all.insert(temp);
    rw_list_wheel.writeToList(list_wheel_all);

    return temp.pos;
}

int wheel_database::add_group(wheel_database_namespace::group_data val)
{
    std::streampos pos;
    //获取文件pos
    if (rw_list_group.pos_temp.size() > 0)
    {
        pos = rw_list_group.pos_temp.back();
        rw_list_group.pos_temp.pop_back();
    }
    else
    {
        pos = list_group_all.size() * sizeof(val);
    }
    val.key_group = pos;

    set_wheel_group_key(val);

    rw_data_group.writeToFile(pos, val);
    //更新索引
    wheel_database_namespace::list_time temp;
    temp.pos = pos;
    list_group_all.insert(temp);
    rw_list_group.writeToList(list_group_all);
    return temp.pos;
}

void wheel_database::delete_wheel(int pos)
{
    for (auto it = list_wheel_all.begin(); it != list_wheel_all.end(); ++it)
    {
        if (it->pos == pos)
        {
            if ((list_wheel_all.size() - 1) * sizeof(wheel_database_namespace::wheel_data) != pos)
            {
                rw_list_wheel.pos_temp.push_back(pos);
            }
            list_wheel_all.erase(it);
            if (list_wheel_all.size() == 0)
            {
                rw_list_wheel.pos_temp.clear();
            }
            break;
        }
    }
    rw_list_wheel.writeToList(list_wheel_all);
}

void wheel_database::delete_group(int pos)
{
    auto group_data = read_group(pos);
    //删除砂轮上的砂轮组主键
    for (size_t i = 0; i < sizeof(group_data.weizhi) / sizeof(group_data.weizhi[0]); i++)
    {
        if (group_data.weizhi[i].key_wheel != -1)
        {
            auto wheel_data = read_wheel(group_data.weizhi[i].key_wheel);
            wheel_data.key_group = -1;
            rw_data_wheel.writeToFile(group_data.weizhi[i].key_wheel, wheel_data);
        }
    }

    for (auto it = list_group_all.begin(); it != list_group_all.end(); ++it)
    {
        if (it->pos == pos)
        {
            if ((list_group_all.size() - 1) * sizeof(wheel_database_namespace::group_data) != pos)
            {
                rw_list_group.pos_temp.push_back(pos);
            }
            list_group_all.erase(it);
            if (list_group_all.size() == 0)
            {
                rw_list_group.pos_temp.clear();
            }
            break;
        }
    }

    rw_list_group.writeToList(list_group_all);
}

void wheel_database::edit_wheel(int pos, wheel_database_namespace::wheel_data val, bool flag)
{
    auto temp = read_wheel(pos);
    for (size_t i = 0; i < sizeof(val.data) / sizeof(val.data[0]); i++)
    {
        temp.data[i] = val.data[i];
    }
    temp.set_dir_dxf(val.get_dir_dxf());
    temp.set_name(val.get_name());
    temp.L0 = val.L0;
    temp.L1 = val.L1;
    temp.Ry0 = val.Ry0;
    temp.Ry1 = val.Ry1;
    temp.Celiang_flag = val.Celiang_flag;
    temp.daozhuang = val.daozhuang;
    //判断是否修改砂轮组主键
    if (flag)
    {
        temp.key_group = val.key_group;
    }
    else
    {
        temp.time_new.set_current_time();
        wheel_database_namespace::list_time new_time_pos;
        new_time_pos.pos = pos;

        //更新索引文件
        for (auto it = list_wheel_all.begin(); it != list_wheel_all.end(); ++it)
        {
            if (it->pos == pos)
            {
                list_wheel_all.erase(it);
                break;
            }
        }
        list_wheel_all.insert(new_time_pos);
        rw_list_wheel.writeToList(list_wheel_all);
    }
    rw_data_wheel.writeToFile(pos, temp);
    edit_buff_wheel.insert(pos);
}

void wheel_database::edit_group(int pos, wheel_database_namespace::group_data val)
{
    auto data = read_group(pos);
    val.key_group = pos;
    clear_wheel_group_key(data);
    set_wheel_group_key(val);
    rw_data_group.writeToFile(pos, val);

    for (auto it = list_group_all.begin(); it != list_group_all.end(); ++it)
    {
        if (it->pos == pos)
        {
            list_group_all.erase(it);
            break;
        }
    }

    //更新索引
    wheel_database_namespace::list_time temp;
    temp.pos = pos;
    list_group_all.insert(temp);
    rw_list_group.writeToList(list_group_all);

}

wheel_database_namespace::wheel_data wheel_database::read_wheel(int pos)
{
    wheel_database_namespace::wheel_data temp;
    rw_data_wheel.readFromFile(pos, temp);
    return temp;
}

wheel_database_namespace::group_data wheel_database::read_group(int pos)
{
    wheel_database_namespace::group_data temp;
    rw_data_group.readFromFile(pos, temp);
    return temp;
}

