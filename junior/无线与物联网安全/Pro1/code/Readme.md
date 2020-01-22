`Message.txt`是Client需要传给AP的数据

使用`g++ AP.cpp -o AP -lcrypto` 编译 AP.cpp

使用`g++ Client.cpp -o Client -lcrypto -pthread`编译Client.cpp

使用`g++ Adversary.cpp -o Adversary -pthread` 编译 Adversary.cpp

由于AP设置了recv超时结束，三个终端必须几乎同时启动。所以,请在三个终端下分别**依次快速**开启AP Adversary Client 。

提供的样例参数如下：
`./AP 234 123`
`./Adversary 127.0.0.1 123 1018`
`./Client 127.0.0.1 1018 234 Message.txt`
执行完成后会生成captured_cipher文件



使用`python decrypt.py` 进行解密
使用`python GetKey.py` 得到密钥