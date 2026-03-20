schema "yblog" {
  charset = "utf8mb4"
  # MariaDB 通常默认的排序规则是 utf8mb4_general_ci 或 utf8mb4_unicode_ci
  collate = "utf8mb4_general_ci"
}

table "article" {
  schema = schema.yblog
  column "id" {
    null  = false
    type  = bigint
    auto_increment  = true
  }
  column "title" {
    null = false
    type = varchar(255)
  }
  column "content" {
    null = false
    type = text
  }
  column "created_at" {
    null    = false
    type    = timestamp
    default = sql("CURRENT_TIMESTAMP")
  }
  column "updated_at" {
    null      = false
    type      = timestamp
    default   = sql("CURRENT_TIMESTAMP")
    on_update = sql("CURRENT_TIMESTAMP")
  }
  primary_key {
    columns = [column.id]
  }
}