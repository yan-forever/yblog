#include <drogon/drogon.h>
#include <filesystem> // 用于检查文件是否存在

int main() {
  // --- 核心新增：加载数据库配置 ---
  // 建议使用相对路径或绝对路径。如果你按照我之前的建议设置了 CLion 的 Working Directory 为 backend，
  // 那么这里直接写 "config.json" 即可。
  std::string configPath = "config.json";

  if (std::filesystem::exists(configPath)) {
    drogon::app().loadConfigFile(configPath);
  } else {
    // 如果找不到文件，打印错误并退出，防止后续断言失败
    std::cout << "FATAL: 找不到配置文件 " << configPath << std::endl;
    return -1;
  }

  // --- 跨域处理 ---
  drogon::app().registerPostHandlingAdvice([](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
      resp->addHeader("Access-Control-Allow-Origin", "*");
      resp->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS, PUT, DELETE");
      resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");
  });

  drogon::app().addListener("0.0.0.0", 8080);

  // run() 之后程序进入事件循环
  drogon::app().run();
  return 0;
}