#include "mprpcconfig.h"

#include<iostream>
//负责解析加载配置文件
void MprpcConfig::LoadConfigFile(const char *config_file)
{
    FILE *pf=fopen()
}

//查询配置项的信息
std::string MprpcConfig::Load(const std::string &key)
{

}

void MprpcConfig::Trim(std::string &src_buf)
{
    int idx=src_buf.find_first_not_of(' ');
    if(idx!=-1)
    {
        src_buf=src_buf.substr(idx,src_buf.size()-idx);
    }

    idx=src_buf.find_last_not_of(' ');
    if(idx!=-1)
    {
        src_buf=src_buf.substr(0,idx+1);
    }
}