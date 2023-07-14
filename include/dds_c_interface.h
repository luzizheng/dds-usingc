
/*DDS 接口*/

#ifndef __DDS_C_INTERFACE_H__
#define __DDS_C_INTERFACE_H__
#include "dds_c_define.h"
#include "dds_c_qos.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /// @brief 初始化dds
    /// @param qos_ qos配置(使用默认的话传NULL)
    /// @param side_ 节点类型
    /// @param name_ 名称
    /// @return 返回dds描述符
    dds_fd dds_create(c_qos *qos_, DDS_SIDE side_, const char *name_);

    /// @brief 关闭dds
    /// @param fd_ dds描述符
    /// @return 成功返回0
    DDS_MSGCODE dds_close(const dds_fd fd_);

    /// @brief 更改Qos配置
    /// @param fd_ dds描述符
    /// @param qos_ qos配置 (使用默认的话传NULL)
    /// @return 成功返回0
    DDS_MSGCODE dds_setQos(const dds_fd fd_, c_qos *qos_);

    /// @brief 绑定topic
    /// @param fd_ dds描述符
    /// @param topicN topic名称
    /// @return 成功返回0
    DDS_MSGCODE dds_bindTopic(const dds_fd fd_, const char *topicN);

    /// @brief 注销绑定topic
    /// @param fd_
    /// @param topicN
    /// @param waituntilconnect
    /// @return
    DDS_MSGCODE dds_unbindTopic(const dds_fd fd_, const char *topicN);
    DDS_MSGCODE dds_send(const dds_fd fd_, const char *topicN, void *data, uint32_t data_len, bool waituntilconnect);

    /// @brief 读取数据(一次轮询读取)
    /// @param fd_ dds描述符
    /// @param topicN
    /// @param timeout_s 轮询超时时间
    /// @param data 接收数据的头地址
    /// @param data_len 接收数据的长度指针
    /// @return
    DDS_MSGCODE dds_read(const dds_fd fd_, const char *topicN, uint32_t timeout_s, void **data_pp, uint32_t *data_len);

    /// @brief 注册接收数据的回调函数（非阻塞接收数据）
    /// @param fd_ dds描述符
    /// @param topicN topic名称
    /// @param callback 回调函数
    DDS_MSGCODE dds_revcDataCallback(const dds_fd fd_, const char *topicN, dds_recvcallback callback);

#ifdef __cplusplus
}
#endif

#endif