# MySQL 辅助工具
主要原理是查询mysql的information_schema数据库
## 已完成
根据MySQL数据库生成数据库设计文档，文档包含表的字段，类型，特殊属性，注释，也包含定义视图的SQL
## TODO
- ~~去掉对Spring Boot的依赖~~
- ~~生成建表的SQL~~
- 解释特殊属性中出现的mul值
- 支持外键
- 生成model类
- 生成mybatis的mapper接口
- 生成service，带接口，可以指定物理主键和逻辑主键
- 生成controller

如果指定物理主键，则id用物理主键，否则id用逻辑主键