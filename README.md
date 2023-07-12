# dds-usingc

dds重新编译为动态库，这个工程只有ddsc和dds和openssl三个动态库

为了用于c环境，封装所有FastDDS的C++接口，暴露几个C接口

cmake可以配置编译架构：arm64/x86_64，构建执行文件。
