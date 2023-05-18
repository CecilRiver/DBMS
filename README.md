# DBMS 迷你数据库系统

2023 年专业课程综合实训 II 大作业：用 Qt C++ 实现的简易数据库管理系统，基于文件系统存储数据库、表和 B-Tree 索引。

## 功能

- 用户注册与登录，密码简单加密后保存到 `user.txt`
- 数据库管理：`CREATE` / `RENAME` / `DROP` / `USE` / `SHOW DATABASES`、初始化、备份
- 表管理：`CREATE TABLE`、`DROP TABLE`、`ADD` / `MODIFY` / `DROP FIELD`、`CREATE INDEX`
- 数据操作：`INSERT INTO ... VALUES`
- 使用 B-Tree 实现索引，数据持久化到文本文件
- Qt 图形界面，通过 SQL 控制台执行语句

## 技术栈

- C++11 / Qt 5（Widgets）
- qmake 构建
- B-Tree、`QFile` / `QDataStream` 文件存储

## 目录结构

```
src/main.cpp         程序入口
src/login.*          登录 / 注册界面
src/widget.*         SQL 控制台
src/SQLanalysis.*    SQL 语句解析
src/database.*       数据库实体管理
src/table.*          表、字段、索引管理
src/btree.*          B-Tree 索引与文件读写
src/user.*           用户注册、登录、密码加解密
src/convert.*        类型转换工具
user.txt             默认账号数据
```

## 构建运行

1. 安装 Qt 5.x（Widgets），用 Qt Creator 打开 `DBMS.pro`。
2. 选择对应 Kit，构建并运行。
3. 默认账号：`ROOT / 111`、`123 / 123`。
4. 数据保存在程序运行时的当前目录，首次运行前请把 `user.txt` 复制到该目录（Qt Creator 默认是构建目录）。

## 说明

- 项目为 Windows 平台课程作业，用户模块使用了 `conio.h`。
