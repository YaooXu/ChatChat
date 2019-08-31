# ChatChat
北理工小学期linux网络编程项目

## Client
### 流程（目前仅考虑一个socket的情况）
在main函数中有一个handle_recv的函数，该函数用来接受服务器发送的数据，并按照server_id，对数据进行相应的反序列化（解包），并调用相关函数（ex：显示好友列表）

以获取个人信息为例
1. 用户通过点击头像触发SLOT函数
2. 将需要传给服务器的数据序列化（外部接口见下）
3. 将序列化得到的字符串send给服务器
> ps：注意此时并没有返回值的，对recv数据的处理是在handle_recv中


### 序列化外部接口
#### 文档
- 名称：encode
- 路径：utils/chat_proto.cpp 
  (*在测试阶段为了避免使用make的麻烦，直接include源文件，之后再写makefile*)
- 描述：把server_id 还有要发送的Json序列化
- 作成日期：2019-8-31
- 参数：
  - 参数1：名称 server_id、参数类型 uint16_t、输入参数、含义：请求的服务类型
  - 参数2：名称 message、类型 Json::Value、输入参数、含义：准备发送的Json对象
  - 参数3：名称 len、类型 len、**输出参数**、含义：实际要send的字符串长度
- 返回值：返回值名称 pData、类型 unsigned char*、含义: 序列化之后的字符串

#### DEMO
```C++
#include "utils/chat_proto.cpp"
int main(int argc, char const *argv[]) {
    Json::Value message;
    message["name"] = "xy";
    message["ID"] = "123456";

    uint32_t len = 0;
    uint8_t *pData = encode(REGISTER, message, len);

    send(fd, pData, len, 0);
    return 0;
}
```

