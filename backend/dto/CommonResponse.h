//
// Created by root on 3/22/26.
//

#ifndef YBLOG_COMMONRESPONSE_H
#define YBLOG_COMMONRESPONSE_H
#include <drogon/HttpResponse.h>
#include <json/json.h>

namespace yblog::dto {
inline drogon::HttpResponsePtr sendResult(int code, const std::string &msg,
                                          const Json::Value &data = Json::nullValue) {
    Json::Value ret;
    ret["code"] = code;
    ret["message"] = msg;
    ret["data"] = data;
    auto res = drogon::HttpResponse::newHttpJsonResponse(ret);
    return res;
}
} // namespace yblog::dtio

#endif // YBLOG_COMMONRESPONSE_H
