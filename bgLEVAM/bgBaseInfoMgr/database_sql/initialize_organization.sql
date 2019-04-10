DROP TABLE IF EXISTS bg_baseinfo_organization;
CREATE TABLE bg_baseinfo_organization(
org_rid VARCHAR(64) NOT NULL PRIMARY KEY,
org_name VARCHAR(64) NOT NULL, #部门名称
org_code VARCHAR(64) NOT NULL, #部门编码
org_parent VARCHAR(64) NOT NULL, #父部门
org_path VARCHAR(255) NOT NULL, #部门全路径
source VARCHAR(64) NOT NULL, #数据来源
create_time DATETIME NOT NULL, #创建时间
update_time DATETIME NOT NULL, #更新时间
state int NOT NULL, #状态信息
order_no int, #排序编号
duty_range VARCHAR(64),
extend VARCHAR(64)
);
