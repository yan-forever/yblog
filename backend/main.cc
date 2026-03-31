#include <drogon/drogon.h>
#include <filesystem>

int main() {
    std::string configPath = "config.yaml";

    if (std::filesystem::exists(configPath)) {
        drogon::app().loadConfigFile(configPath);
    } else {
        std::cout << "FATAL: 找不到配置文件,请依照示例填写 " << configPath << std::endl;
        return -1;
    }
    // --- 跨域处理 ---
    drogon::app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS, PUT, DELETE");
            resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
        });

    // drogon::app().addListener("0.0.0.0", 8080);
    // run() 之后程序进入事件循环
    drogon::app().loadConfigFile("config.yaml");
    drogon::app().run();
    return 0;
}