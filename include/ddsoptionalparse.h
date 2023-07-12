#ifndef __DDSOPTIONPARSE__
#define __DDSOPTIONPARSE__
#include <stdint.h>


#ifdef __cplusplus
extern "C"
{
#endif


enum ddsExampleOperation
{
    dundefault,
    dsend,
    dlisten,
    dread,
    dboth
};


struct OptionsArgs
{
    enum ddsExampleOperation operation;
    uint32_t samples;
    double interval_u;
    uint32_t topic;
};



/// @brief 解析main函数入口参数命令，返回示例参数结构体
/// @param argst 接收参数内容的参数结构体指针
/// @return 成功返回0
int parseMainOptions(struct OptionsArgs *const argst,int _argc, char **_argv);



#ifdef __cplusplus
}
#endif


#endif