#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "dds_c_interface.h"
#include <signal.h>
#include <pthread.h>
#include "ddsoptionalparse.h"

static dds_fd dds;

int listenThreadFlag = 0;

void sigint_handle(int sig)
{
    if (sig == SIGINT)
    {
        listenThreadFlag = 1;
        dds_close(dds);
    }
}

/// @brief 回调
void recvcallback(void *pdata, uint32_t datalen)
{
    char *str = (char *)malloc(datalen + 1);
    memcpy(str, pdata, datalen);
    str[datalen] = '\0';
    printf("接收到数据:%s\n", str);
    free(str);
}

// ‘send’ 操作
void *runSendThread(void *arg)
{
    struct OptionsArgs *targs = (struct OptionsArgs *)arg;
    if (targs == NULL)
    {
        printf("error:OptionsArgs is null\n");
        pthread_exit(NULL);
    }
    // const char *message = "abcdefg";
    // void *p = (void *)message;
    char *msg = malloc(strlen(targs->message) + 1);
    strcpy(msg,targs->message);

    uint32_t remain_samples = targs->samples;
    while (1)
    {
        // printf("remain samples = %d\n", remain_samples);

        if (remain_samples < 1)
        {
            break;
        }
        remain_samples--;

        usleep(targs->interval_u);

        char topic_ch[10];
        sprintf(topic_ch, "%d", targs->topic);
        const char *topic_str = topic_ch;

        // send data
        DDS_MSGCODE code = dds_send(dds, topic_str, msg, strlen(msg), true);
        if (code != DDS_MSG_SUCCESS)
        {
            break;
        }
    }
    free(msg);
    pthread_exit(NULL);
}

void *listenThread(void *arg)
{
    struct OptionsArgs *targs = (struct OptionsArgs *)arg;
    char topic_ch[10];
    sprintf(topic_ch, "%d", targs->topic);
    const char *topic_str = topic_ch;

    if (dds_revcDataCallback(dds, topic_str, recvcallback) != 0)
    {
        return NULL;
    }

    while (listenThreadFlag != 1)
    {
        sleep(1);
        if (listenThreadFlag != 0)
        {
            break;
        }
    }
    pthread_exit(NULL);
}

void *readThread(void *arg)
{
    struct OptionsArgs *targs = (struct OptionsArgs *)arg;
    void *pdata;
    uint32_t dataLen = 0;
    char topic_ch[10];
    sprintf(topic_ch, "%d", targs->topic);
    const char *topic_str = topic_ch;
    if (dds_read(dds, topic_str, 5, &pdata, &dataLen) == DDS_MSG_SUCCESS)
    {
        // printf("pdata = %p\n",pdata);
        // char *str = (char *)malloc(dataLen + 1);
        // memcpy(str, pdata, dataLen);
        // str[dataLen] = '\0';
        // printf("接收到数据:%s\n", str);
        // free(str);
        char *recvMsg = (char *)pdata;
        printf("接收到数据:");
        for (int i = 0; i < dataLen; i++)
        {
            printf("%c",recvMsg[i]);
        }
        putchar('\n');
        free(recvMsg);
    }
    else
    {
        printf("dds_read方法error");
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{

    struct OptionsArgs oa = {dundefault, INT32_MAX, 1, 0};
    int res = parseMainOptions(&oa, argc, argv);
    if (res != 0)
    {
        return res;
    }

    printf("samples = %d\n", oa.samples);

    signal(SIGINT, sigint_handle);

    // create dds node
    dds = dds_create(dds_qos_createDefaultQoS(), DDS_DEFAULT, NULL);

    // bind topic
    char topic_ch[5];
    snprintf(topic_ch, sizeof(topic_ch), "%d", oa.topic);
    const char *topic_str = topic_ch;
    dds_bindTopic(dds, topic_str);

    if (oa.operation == dsend)
    {
        pthread_t tid;
#ifdef __cplusplus
        int ret = pthread_create(&tid, NULL, runSendThread, (void *)&oa);
#else
        int ret = pthread_create(&tid, NULL, (void *)runSendThread, (void *)&oa);
#endif

        if (ret)
        {
            printf("创建send线程失败\n");
            exit(-1);
        }
        pthread_join(tid, NULL);
    }
    else if (oa.operation == dlisten)
    {
        pthread_t tid;

#ifdef __cplusplus
        int ret = pthread_create(&tid, NULL, listenThread, (void *)&oa);
#else
        int ret = pthread_create(&tid, NULL, (void *)listenThread, (void *)&oa);
#endif

        if (ret)
        {
            printf("创建listen线程失败\n");
            exit(-1);
        }
        pthread_join(tid, NULL);
    }
    else if (oa.operation == dread)
    {
        pthread_t tid;
#ifdef __cplusplus
        int ret = pthread_create(&tid, NULL, readThread, (void *)&oa);
#else
        int ret = pthread_create(&tid, NULL, (void *)readThread, (void *)&oa);
#endif

        if (ret)
        {
            printf("创建read线程失败\n");
            exit(-1);
        }
        pthread_join(tid, NULL);
    }
    else if (oa.operation == dboth)
    {
        pthread_t sendtid;
        pthread_t listentid;
#ifdef __cplusplus
        pthread_create(&sendtid, NULL, runSendThread, (void *)&oa);
        pthread_create(&listentid, NULL, listenThread, (void *)&oa);
#else
        pthread_create(&sendtid, NULL, (void *)runSendThread, (void *)&oa);
        pthread_create(&listentid, NULL, (void *)listenThread, (void *)&oa);
#endif
        pthread_join(sendtid, NULL);
        pthread_join(listentid, NULL);
    }
    else
    {
        printf("error operation option\n");
    }

    // dds_close(dds);
    return 0;
}