
#ifndef _DDS_C_DEFINE_
#define _DDS_C_DEFINE_
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define DDS_DEFAULT_DOMAIN "1"

#define DDS_MSG_SUCCESS 0
#define DDS_MSG_TOPICERR 0xe001
#define DDS_MSG_WRITERERR 0xe002
#define DDS_MSG_PUBSUBERR 0xe003
#define DDS_MSG_WRITEDATAERR 0xe004
#define DDS_MSG_NOTCONNECT 0xe005
#define DDS_MSG_NODEUNEXSIT 0xe006
#define DDS_MSG_TOPICNAMEERR 0xe007
#define DDS_MSG_DATAERR 0xe008

#define DDS_MSG_OTHERERR 0xfe01
#define DDS_MSG_PARAMSERR 0xfe02

#define DDSSERIDLEN 8
#define DDSSERNAMELEN 20
#define DDSTOPICNAMELEN 20
#define DDS_SHM_DATASEG 2 * 1024 * 1024
#define DDS_SER_CONFIG_XML_PATH "../resource/comDDSProtoConfig.xml"

    typedef void (*dds_recvcallback)(void *, uint32_t);

    typedef int16_t DDS_MSGCODE;
    typedef int32_t dds_fd;

    enum _DDS_SIDE_
    {
        DDS_DEFAULT,
        DDS_SERVER,
        DDS_CLIENT,
    };

    typedef enum _DDS_SIDE_ DDS_SIDE;

    /*用于DDS协议接口交互*/
    typedef struct
    {
        uint16_t serviceID;              // 服务ID
        char serviceName[DDSSERNAMELEN]; // 服务名称
        char topicN[DDSTOPICNAMELEN];    // TOPIC名称
    } DDSProtocolS;

    /*用于储存服务列表*/
    typedef struct
    {
        char serId[DDSSERIDLEN];
        char sername[DDSTOPICNAMELEN];
        char domain[5];
        DDS_MSGCODE topic;

    } DDSServiceS;

#ifdef __cplusplus
}
#endif

#endif