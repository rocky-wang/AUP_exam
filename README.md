linux应用编程参考代码：
一、缓存IO部分：
	1、标准IO缓存大小计算问题
		1.1：参考Buffer_IO/stdBufType_test.c
		1.2: 参考Buffer_IO/fileBufType_test.c
		1.3: 参考Buffer_IO/bufIoSize_test.c
	2、标准IO文件拷贝问题
		2.1：参考Buffer_IO/copyFileChar.c 单字节拷贝
		2.2：参考Buffer_IO/copyFileLine.c 单行拷贝
		2.3：参考Buffer_IO/copyFileBuffer.c 块格式拷贝	
	3、日志文件生成问题
		参考Buffer_IO/timeLog.c
