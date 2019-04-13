#include "bgBaseInfoCache.h"

bgBaseInfoCache::bgBaseInfoCache()
: redis_client_(new Poco::Redis::Client())
{

}

bgBaseInfoCache::~bgBaseInfoCache()
{
	delete redis_client_;
	redis_client_ = NULL;
}

int bgBaseInfoCache::Initialize(int work_mode /* = WORKMODE_REDIS */, const char *cache_host /* = "127.0.0.1" */, int cache_port /* = 6379 */)
{
	int err_code = 0;

	try
	{
		redis_client_->connect(cache_host, cache_port);
	}
	catch (Poco::Redis::RedisException &e)
	{
		err_code = e.code();
		e.displayText();
	}
	

	return err_code;
}

void bgBaseInfoCache::Close()
{
	redis_client_->disconnect();
}

int bgBaseInfoCache::AddOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;
	/*

	*/

	// KeyΪrid
	try
	{
		Poco::JSON::Parser parser;
		Poco::Dynamic::Var json_var = parser.parse(json_string);
		if (json_var.type() != typeid(Poco::JSON::Array::Ptr))
			return -1;

		Poco::JSON::Array::Ptr json_array = json_var.extract<Poco::JSON::Array::Ptr>();
		int json_array_count = json_array->size();

		for (int index = 0; index < 0; ++index)
		{
			Poco::JSON::Object *object = json_array->get(index);
		}
		
	}
	catch (Poco::JSON::JSONException &e)
	{
		e.code();
		e.displayText();
	}
	

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

int bgBaseInfoCache::BuildCache(std::string &all_data)
{
	int err_code = 0;

	return err_code;
}