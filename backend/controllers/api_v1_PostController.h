#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api::v1 {
class PostController : public drogon::HttpController<PostController> {
public:
  METHOD_LIST_BEGIN
  // use METHOD_ADD to add your custom processing function here;
  // METHOD_ADD(PostController::get, "/{2}/{1}", Get); // path is
  // /api/v1/PostController/{arg2}/{arg1}
  // METHOD_ADD(PostController::your_method_name, "/{1}/{2}/list", Get); // path
  // is /api/v1/PostController/{arg1}/{arg2}/list
  // ADD_METHOD_TO(PostController::your_method_name,
  // "/absolute/path/{1}/{2}/list", Get); // path is
  // /absolute/path/{arg1}/{arg2}/list
  ADD_METHOD_TO(PostController::create,"/api/v1/posts",Post);
  ADD_METHOD_TO(PostController::list,"/api/v1/posts",Get);
  ADD_METHOD_TO(PostController::getPost,"/api/v1/post/{1}",Get);
  METHOD_LIST_END
  // your declaration of processing function maybe like this:
  // void get(const HttpRequestPtr& req, std::function<void (const
  // HttpResponsePtr &)> &&callback, int p1, std::string p2); void
  // your_method_name(const HttpRequestPtr& req, std::function<void (const
  // HttpResponsePtr &)> &&callback, double p1, int p2) const;
  void create(const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback);
  void list(const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback);
  void getPost(const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback,int postId);
};
} // namespace
