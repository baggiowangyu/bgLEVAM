#include "bgBaseInfoCache.h"

bgBaseInfoCache::bgBaseInfoCache()
{

}

bgBaseInfoCache::~bgBaseInfoCache()
{

}

int bgBaseInfoCache::Initialize(int work_mode /* = WORKMODE_REDIS */, const char *cache_host /* = "127.0.0.1" */, int cache_port /* = 6379 */)
{
	int err_code = 0;

	return err_code;
}

void bgBaseInfoCache::Close()
{

}

int bgBaseInfoCache::AddOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}

int bgBaseInfoCache::RemoveOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}

int bgBaseInfoCache::QueryOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}

int bgBaseInfoCache::ModifyOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}
