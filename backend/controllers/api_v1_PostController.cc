#include "api_v1_PostController.h"
#include "../models/Posts.h"
using namespace api::v1;

// Add definition of your processing function here
void PostController::create(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  auto jsonptr = req->getJsonObject();
  if (!jsonptr) {
    Json::Value ret;
    ret["error"] = "Invalid or missing JSON body";
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(k400BadRequest);
    callback(res);
    return;
  }
  if (!(*jsonptr)["title"].isString()||
      !(*jsonptr)["content"].isString()||
      !(*jsonptr)["user_id"].isInt()
  ) {
    Json::Value ret;
    ret["error"] = "unsafe!check your type!";
    auto res = HttpResponse::newHttpJsonResponse(ret);
    res->setStatusCode(k400BadRequest);
    callback(res);
    return;
  }

  std::string title = (*jsonptr)["title"].asString();
  std::string content = (*jsonptr)["content"].asString();
  int userId = (*jsonptr)["user_id"].asInt();

  drogon_model::yblog::Posts newPost;
  newPost.setTitle(title);
  newPost.setContent(content);
  newPost.setUserId(userId);

  auto dbclient = drogon::app().getDbClient();
  drogon::orm::Mapper<drogon_model::yblog::Posts> mapper(dbclient);
  mapper.insert(
    newPost,[callback](const drogon_model::yblog::Posts &insertedPost)
  );
  Json::Value ret;
  ret["message"] = "post create successfully!";
  ret["data"]["receive_title"] = title;
  ret["data"]["receive_user_id"] = userId;

  auto res = HttpResponse::newHttpJsonResponse(ret);
  res->setStatusCode(k201Created);
  callback(res);
}

void PostController::list(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  Json::Value ret;
  ret["message"] = "this is post list";
  auto res  = HttpResponse::newHttpJsonResponse(ret);
  callback(res);
}

void PostController::getPost(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback, int postId) {
  Json::Value ret;
  ret["post_id"] = postId;
  auto res = HttpResponse::newHttpJsonResponse(ret);
  callback(res);
}