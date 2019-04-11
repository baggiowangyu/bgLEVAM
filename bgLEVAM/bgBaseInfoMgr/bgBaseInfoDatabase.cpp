#include "bgBaseInfoDatabase.h"

#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Array.h"

bgBaseInfoDatabase::bgBaseInfoDatabase()
: session_(NULL)
{
	Poco::Data::MySQL::Connector::registerConnector();
}

bgBaseInfoDatabase::~bgBaseInfoDatabase()
{
	Poco::Data::MySQL::Connector::unregisterConnector();
}

int bgBaseInfoDatabase::Initialize(const char *mysql_host /* = "127.0.0.1" */, int mysql_port /* = 3306 */, const char *mysql_username /* = "username" */, const char *mysql_password /* = "password" */, const char *mysql_dbname /* = "baseinfo" */)
{
	int err_code = 0;

	// 构建连接字符串
	char conn_str[4096] = {0};
	sprintf(conn_str, "host=%s;port=%d;db=%s;user=%s;password=%s;compress=true;auto-reconnect=true;secure-auth=true;protocol=tcp", mysql_host, mysql_port, mysql_dbname, mysql_username, mysql_password);
	connection_string_ = conn_str;

	try
	{
		session_ = new Poco::Data::Session(Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, connection_string_));
	}
	catch (Poco::Data::MySQL::ConnectionException &e)
	{
		err_code = e.code();
		e.displayText();

		return err_code;
	}
	catch (Poco::Data::MySQL::MySQLException &e)
	{
		err_code = e.code();
		e.displayText();

		return err_code;
	}

	if (session_ && !session_->isConnected())
	{
		// 连接失败！
		err_code = -2;
		return err_code;
	}

	return err_code;
}

void bgBaseInfoDatabase::Close()
{
	session_->close();
}

int bgBaseInfoDatabase::AddOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	// 这里考虑性能直接入库还是加入缓冲队列，由工作线程进行
	// 这里不考虑了，此接口应当兼容单条入库和多条入库模式
	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result;

	try
	{
		result = parser.parse(json_string);
	}
	catch(Poco::JSON::JSONException& jsone)
	{
		std::cout << jsone.message() << std::endl;
	}

	// 按照约定，这里应该传进来的是一个数组
	if (result.type() != typeid(Poco::JSON::Array::Ptr))
	{
		// 数据格式不对
		return -1;
	}

	Poco::JSON::Array::Ptr object_array = result.extract<Poco::JSON::Array::Ptr>();
	int object_array_count = object_array->size();

	Poco::JSON::Array::ConstIterator iter;
	for (iter = object_array->begin(); iter != object_array->end(); ++iter)
	{
		if (iter->type() == typeid(Poco::JSON::Object::Ptr))
		{
			Poco::JSON::Object::Ptr element = iter->extract<Poco::JSON::Object::Ptr>();
			std::string org_code = element->get("org_name");
			std::string org_code = element->get("org_code");
			std::string org_code = element->get("org_parent");
			std::string org_code = element->get("org_path");
			std::string org_code = element->get("source");
			std::string org_code = element->get("order_no");
			std::string org_code = element->get("create_time");
			std::string org_code = element->get("update_time");
			std::string org_code = element->get("duty_range");
			std::string org_code = element->get("extend");

			// 这里按照规则创建一个rid
			// 规则GMO + 8位区位码 + 年月日时分秒 + 
		}
		
	}

	return err_code;
}

int bgBaseInfoDatabase::RemoveOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}

int bgBaseInfoDatabase::QueryOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	// 此函数仅在构建缓存数据，以及缓存服务不可用的时候被调用

	return err_code;
}

int bgBaseInfoDatabase::ModifyOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}

int bgBaseInfoDatabase::GetAllData(std::string &all_data)
{
	int err_code = 0;

	return err_code;
}