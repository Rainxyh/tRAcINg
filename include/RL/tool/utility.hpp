#pragma once

#include <ctime>
#include <iomanip>
#include <string>
#include <io.h>  
#include <iostream>  

namespace ct
{
/**
 * @brief 获取本地时间日期字符串
 * @param fmt 时间日期格式，参见 https://en.cppreference.com/w/cpp/io/manip/put_time
 * @return 时间日期字符串
 */
inline std::string localTime(const char* fmt = "%Y-%m-%d %H:%M:%S %A", std::time_t* t = nullptr)
{
    std::time_t t_tmp;
    char buf[500];
    if (t == nullptr) {
        t_tmp = time(NULL);
        t     = &t_tmp;
    }
    strftime(buf, 500, fmt, localtime(t));
    return buf;
}

/**
 * @brief 在printf等函数前调用，使得字符在控制台单行滚动输出
 */
inline void setScrollOutput()
{
#ifdef _WIN32
    std::printf("\r");
#else
    std::printf("\r\033[k");
#endif  // _WIN32
    std::fflush(stdout);
}

/**
 * @brief 通过后缀获取文件名
 * @param dir_path 待查找文件夹
 * @param name_list 文件名列表
 * @param ext 待查找后缀名
 */
inline std::vector<std::string> get_files_by_ext(std::string dir_path, std::string ext)
{
    std::vector<std::string> name_list;
    intptr_t file_handle = 0;
    struct _finddata_t file_info;
    std::string temp;
    if ((file_handle = _findfirst(temp.assign(dir_path).append("/*" + ext).c_str(), &file_info)) != -1)
    {
        do
        {
            name_list.push_back(temp.assign(dir_path).append("/").append(file_info.name));
        } while (_findnext(file_handle, &file_info) == 0);
        _findclose(file_handle);
    }
    return name_list;
}
}  // namespace ct