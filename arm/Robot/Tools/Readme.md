# Tools in Robot

## 1. ntpclient
ntpclient用于联网更新时间，将ntpclient程序置于目录/usr/bin/目录下，使用方法如下：

```
ntpclient -s -h cn.pool.ntp.org
```

## 2. acount.sh和libacount.lib
用于统计项目中的代码行数，使用方法如下：

```
./acount.sh ..
```

## 3. upload_to_arm.sh和download_from_arm.sh
用于上传文件和下载文件到机器人，使用方法如下：

```
upload_to_arm.sh <filename> <IP> <port>
download_from_arm.sh <filename> <IP> <port>
```

> 机器人端的默认目录为/home/limin/，如需要修改目录，打开对应脚本文件自行修改即可。

## 4. record.sh
用于在机器人端自动打包运行结果（会自动清理运行结果），打包后的文件名字为record.tar.gz



