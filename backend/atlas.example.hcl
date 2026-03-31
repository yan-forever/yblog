# atlas.HCL
# 声明式配置数据库

env "local" {
  # 目标数据库
  url = "mariadb://root:xxxxxxxx@127.0.0.1:3306/yblog"

  # 期望的结构文件来源
  src = "file://schema.hcl"

  # 用于比对演练的空数据库
  dev = "mariadb://root:xxxxxxx@127.0.0.1:3306/yblog_dev"
}