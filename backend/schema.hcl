schema "yblog" {
  charset = "utf8mb4"
  # MariaDB 通常默认的排序规则是 utf8mb4_general_ci 或 utf8mb4_unicode_ci
  collate = "utf8mb4_general_ci"
}

table "users" {
  schema = schema.yblog
  column "id" {
    null           = false
    type           = int
    auto_increment = true
  }
  column "username" {
    null = false
    type = varchar(50)
  }
  column "password_hash" {
    null = false
    type = varchar(255)
  }
  column "email" {
    null = true
    type = varchar(100)
  }
  column "created_at" {
    null    = true
    type    = datetime
    default = sql("CURRENT_TIMESTAMP")
  }
  primary_key {
    columns = [column.id]
  }
  index "username" {
    unique  = true
    columns = [column.username]
  }
  index "email" {
    unique  = true
    columns = [column.email]
  }
}

table "posts" {
  schema = schema.yblog
  column "id" {
    null           = false
    type           = int
    auto_increment = true
  }
  column "title" {
    null = false
    type = varchar(255)
  }
  column "content" {
    null = false
    type = text
  }
  column "user_id" {
    null = false
    type = int
  }
  column "status" {
    null    = true
    type    = enum("draft", "published")
    default = "draft"
  }
  column "created_at" {
    null    = true
    type    = datetime
    default = sql("CURRENT_TIMESTAMP")
  }
  column "updated_at" {
    null    = true
    type    = datetime
    default = sql("CURRENT_TIMESTAMP")
    on_update = sql("CURRENT_TIMESTAMP")
  }
  primary_key {
    columns = [column.id]
  }
  index "fk_post_user" {
    columns = [column.user_id]
  }
  foreign_key "fk_post_user" {
    columns     = [column.user_id]
    ref_columns = [table.users.column.id]
    on_delete   = CASCADE
    on_update   = NO_ACTION
  }
}

table "tags" {
  schema = schema.yblog
  column "id" {
    null           = false
    type           = int
    auto_increment = true
  }
  column "name" {
    null = false
    type = varchar(50)
  }
  primary_key {
    columns = [column.id]
  }
  index "name" {
    unique  = true
    columns = [column.name]
  }
}

table "post_tags" {
  schema = schema.yblog
  column "post_id" {
    null = false
    type = int
  }
  column "tag_id" {
    null = false
    type = int
  }
  primary_key {
    columns = [column.post_id, column.tag_id]
  }
  index "fk_pt_tag" {
    columns = [column.tag_id]
  }
  foreign_key "fk_pt_post" {
    columns     = [column.post_id]
    ref_columns = [table.posts.column.id]
    on_delete   = CASCADE
    on_update   = NO_ACTION
  }
  foreign_key "fk_pt_tag" {
    columns     = [column.tag_id]
    ref_columns = [table.tags.column.id]
    on_delete   = CASCADE
    on_update   = NO_ACTION
  }
}