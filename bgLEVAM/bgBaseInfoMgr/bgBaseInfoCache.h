#ifndef _bgBaseInfoCache_H_
#define _bgBaseInfoCache_H_

#include <string>
#include "Poco/Redis/Client.h"

//////////////////////////////////////////////////////////////////////////
//
// 设备基础信息管理缓存类
//
// 此类支持两种模式的缓存数据：Redis缓存，本地内存缓存
// - 若使用集群模式或主备模式时，建议使用Redis缓存
// - 单实例模式可使用内存缓存
//
//////////////////////////////////////////////////////////////////////////
#define WORKMODE_REDIS		0	// Redis缓存模式
#define WORKMODE_MEMORY		1	// 内存缓存模式

class bgBaseInfoCache
{
public:
	bgBaseInfoCache();
	~bgBaseInfoCache();

public:
	// 初始化
	int Initialize(int work_mode = WORKMODE_REDIS, const char *cache_host = "127.0.0.1", int cache_port = 6379);
	void Close();

public:
	int AddOrg(std::string &json_string, std::string &result_json_string);
	int RemoveOrg(std::string &json_string, std::string &result_json_string);
	int QueryOrg(std::string &json_string, std::string &result_json_string);
	int ModifyOrg(std::string &json_string, std::string &result_json_string);

public:
	int BuildCache(std::string &all_data);

private:
	//////////////////////////////////////////////////////////////////////////
	//
	// 内存缓存集合
	//
	//////////////////////////////////////////////////////////////////////////

private:
	Poco::Redis::Client *redis_client_;
};

#endif//_bgBaseInfoCache_H_
