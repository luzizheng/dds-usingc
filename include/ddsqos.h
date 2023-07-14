#ifndef _DDS_C_QOS_H_
#define _DDS_C_QOS_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define QOS_IP_LEN 20
#define QOS_DOMAIN_LEN 20
#define QOS_DIR_LEN 30
#define QOS_WHITELIST_IP_NUM 10
#define QOS_DATASHARE_DOMAIN_NUM 10

    enum qos_trans_protocol
    {
        SHM,
        UDPv4,
        UDPv6,
        TCPv4,
        TCPv6
    };

    enum qos_datasharing
    {
        ON,
        OFF,
        AUTO
    };

    enum qos_reliable_mode
    {
        besteffort,
        reliable
    };

    typedef struct qos_ipconfig_
    {
        char wan_ip[QOS_IP_LEN];
        uint16_t port_locator;
        uint16_t port_listen;
        char whitelist_ips[QOS_WHITELIST_IP_NUM][QOS_IP_LEN];
    } ipconfig;

    typedef struct qos_disable_positive_acks_
    {
        bool enable;
        uint64_t keep_duration_ms;
    } qos_disable_positive_acksS;

    typedef struct qos_transfer_
    {
        enum qos_trans_protocol mode;
        uint64_t sendBufferSize;
        uint64_t receiveBufferSize;
        ipconfig *tcp_ip_Conf;

    } qos_transferS;

    typedef struct qos_data_sharing_
    {
        enum qos_datasharing mode;
        char shared_dir[QOS_DIR_LEN];
        uint32_t max_domains;
        char domain_ids[QOS_DATASHARE_DOMAIN_NUM][QOS_DOMAIN_LEN];
    } qos_data_sharingS;

    typedef struct qos_reliable_
    {
        enum qos_reliable_mode mode;
    }qos_reliableS;

    /// @brief qos结构体，后续可以添加更多字段，以支持更多qos策略
    typedef struct c_qos_
    {
        qos_transferS *transfer;
        qos_disable_positive_acksS *disable_positive_acks;
        qos_data_sharingS *qos_data_sharing;
        qos_reliableS *qos_reliable;
    } c_qos;

    /// @brief 根据xml文件生成一个qos结构体
    /// @param qos_ptr qos结构体指针
    /// @param xmlfile xml文件路径
    bool genqosconf(c_qos *qos_ptr,const char *xmlfile);

    /// @brief 释放结构体
    bool freeQos(c_qos *qos_ptr);

    /// @brief 创建默认qos结构体
    c_qos *dds_qos_createDefaultQoS();


#ifdef __cplusplus
}
#endif

#endif