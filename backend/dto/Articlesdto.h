//
// Created by root on 3/22/26.
//

#ifndef YBLOG_ARTICLESDTO_H
#define YBLOG_ARTICLESDTO_H
#include "Article.h"
#include <nlohmann/json.hpp>

namespace yblog::dto {
struct CreateArticle {
    std::string title;
    std::string content;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(CreateArticle, title, content)
};
} // namespace yblog::dto
#endif // YBLOG_ARTICLESDTO_H
