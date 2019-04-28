#include "bgBaseInfoCache.h"

#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Array.h"
#include "Poco/JSON/Object.h"
#include "Poco/Redis/Command.h"

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
		// 首先，读取全局组织架构节点“orgs"
		Poco::JSON::Array redis_org_json_array;
		Poco::Redis::Command getCommand = Poco::Redis::Command::get("orgs");
		Poco::Redis::BulkString getValue = redis_client_->execute<Poco::Redis::BulkString>(getCommand);
		if (getValue.isNull())
		{
			// 新建一个空的Array数组对象
		}
		else
		{
			// 解析为Json对象，后面的组织架构信息需要增加到这个Json对象中，实际上就是一个队列
			Poco::JSON::Parser redis_parser;
			Poco::Dynamic::Var redis_org_json_val = redis_parser.parse(getValue.value());
			redis_org_json_array = redis_org_json_val.extract<Poco::JSON::Array::Ptr>();
		}

		Poco::JSON::Parser parser;
		Poco::Dynamic::Var json_var = parser.parse(json_string);
		if (json_var.type() != typeid(Poco::JSON::Array::Ptr))
			return -1;

		Poco::JSON::Array::Ptr json_array = json_var.extract<Poco::JSON::Array::Ptr>();
		int json_array_count = json_array->size();

		Poco::JSON::Array::ConstIterator iter;
		for (iter = json_array->begin(); iter != json_array->end(); ++iter)
		{
			Poco::JSON::Object::Ptr element = iter->extract<Poco::JSON::Object::Ptr>();
			std::string org_rid		= element->get("org_rid").toString();
			std::string org_name	= element->get("org_name").toString();
			std::string org_code	= element->get("org_code").toString();
			std::string org_parent	= element->get("org_parent").toString();
			std::string org_path	= element->get("org_path").toString();
			std::string source		= element->get("source").toString();
			std::string create_time = element->get("create_time").toString();
			std::string update_time = element->get("update_time").toString();
			int state				= element->get("state").convert<int>();
			int order_no			= element->get("order_no").convert<int>();
			std::string duty_range	= element->get("duty_range").toString();
			std::string extend		= element->get("extend").toString();

			redis_org_json_array->add()
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