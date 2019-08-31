#include "utils/chat_proto.cpp"

int main(int argc, char const *argv[]) {
    Json::Value message;
    message["name"] = "xy";
    message["ID"] = "123456";

    uint32_t len = 0;
    uint8_t *pData = encode(REGISTER, message, len);
    /*
    ID
    name
    description
    头像
    */
    return 0;
}
