## linux应用编程参考代码：

### 一、缓存IO部分：

#### 1、标准IO缓存大小计算问题
* 1.1：参考Buffer_IO/stdBufType_test.c
* 1.2: 参考Buffer_IO/fileBufType_test.c
* 1.3: 参考Buffer_IO/bufIoSize_test.c

#### 2、标准IO文件拷贝问题
* 2.1：参考Buffer_IO/copyFileChar.c 单字节拷贝
* 2.2：参考Buffer_IO/copyFileLine.c 单行拷贝
* 2.3：参考Buffer_IO/copyFileBuffer.c 块格式拷贝	

#### 3、日志文件生成问题

* 参考Buffer_IO/timeLog.c

### 二、文件IO部分

#### 1、文件IO文件拷贝问题

* 参考File_IO/copyFile.c	文件IO的拷贝

#### 2、目录遍历问题

* 参考File_IO/listDirFile.c	遍历目录里的文件信息

#### 3、ls -l的自实现编程问题

* 参考File_IO/listInfo.c		ls -l的简化版

### 三、管道IPC通信

#### 1、无名管道信息交互问题

* 参考 pipe_IPC/pipe_test.c

#### 2、有名管道信息交互问题

* 参考 pipe_IPC/fifo_reader.c		pipe_IPC/fifo_writer.c

### 四、信号IPC通信

#### 1、信号实现亲缘关系进程的同步问题

* 参考 signal_IPC/signal_sync.c

#### 2、司机售票员模拟问题
* 参考 signal_IPC/simulate_bus.c

### 五、SYSV_IPC通信

#### 1、通过共享内存完成数据交互，信号完成同步

* 参考 sysv_IPC/signal_shm_reader.c  signal_shm_writer.c

#### 2、通过共享内存完成数据交互，信号量完成同步
* 参考 sysv_IPC/shmSem_reader.c shmSem_writer.c

### 六、TCP网络编程练习题
#### 1、简单的TCP服务器、客户端程序
* 参考 tcp_base/tcp_server.c  tcp_client.c

#### 2、简单的文件上传下载TCP客户服务器模型
* 参考 tcp_base/file_server.c file_client.c

