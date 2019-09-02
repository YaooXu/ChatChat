#include "utils/chat_proto.cpp"

int main(int argc, char const *argv[]) {
    Json::Value message;
    message["name"] = "xy";
    message["ID"] = "123456";

    uint32_t len = 0;
    uint8_t *pData = encode(REGISTER_REQ, message, len);

    Json::Value array;
    Json::Value temp;
    for (int i = 0; i < 2; i++) {
        temp["is"] = "xy";
        temp["position"] = i;
        array["list"].append(temp);
    }
    array["len"] = 2;

    for (int i = 0; i < array["len"].asInt(); i++) {
        printf("%d\n", array["list"][i]["position"].asInt());
    }
    return 0;
}