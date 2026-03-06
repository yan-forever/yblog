#include "api_v1_Status.h"
#include "Articles.h"  // 必须引入生成的 ORM 头文件

using namespace api::v1;
using namespace drogon_model::yblog; // 引入 ORM 自动生成的命名空间

void Status::getStatus(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback) const {

  // 1. 获取数据库客户端指针
  auto dbClient = drogon::app().getDbClient();

  // 2. 创建一个 Articles 表的映射器 (Mapper)
  drogon::orm::Mapper<Articles> mapper(dbClient);

  // 3. 异步查询主键为 1 的文章
  // 这里使用了回调模式，确保不会阻塞主线程
  mapper.findByPrimaryKey(1,
      [callback](Articles a) {
          // 查询成功
          Json::Value ret;
          ret["status"] = "success";
          ret["data"]["title"] = a.getValueOfTitle();   // 从对象中取值
          ret["data"]["content"] = a.getValueOfContent();

          auto resp = HttpResponse::newHttpJsonResponse(ret);
          callback(resp);
      },
      [callback](const drogon::orm::DrogonDbException &e) {
    Json::Value ret;
    ret["status"] = "error";
    // 关键修正：显式转为 std::string 确保可以进行字符串拼接
    ret["message"] = std::string("Database error: ") + e.base().what();

    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
  );
}