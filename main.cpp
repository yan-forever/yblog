//
// Created by root on 3/5/26.
//
#include <drogon/drogon.h>

int main() {
  drogon::app().registerHandler("/api/v1/status",
    [](const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr&)> &&callback) {
      Json::Value ret;
      ret["status"]   = "success";
      ret["message"]  = "yblog is running!";
      ret["version"]  = "1.0.0";
      auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
      callback(resp);
  },{drogon::HttpMethod::Get});
  drogon::app().addListener("0.0.0.0",8080);
  drogon::app().run();
  return 0;
}