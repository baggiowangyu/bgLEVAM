#include "bgBaseInfoDatabase.h"

#include "Poco/JSON/Parser.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Array.h"
#include "Poco/RandomStream.h"

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

	Poco::Data::Statement stat(*session_);

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

	std::vector<std::string> org_rids;
	std::vector<std::string> org_names;
	std::vector<std::string> org_codes;
	std::vector<std::string> org_parents;
	std::vector<std::string> org_paths;
	std::vector<std::string> sources;
	std::vector<std::string> create_times;
	std::vector<std::string> update_times;
	std::vector<int> states;
	std::vector<int> order_nos;
	std::vector<std::string> duty_ranges;
	std::vector<std::string> extends;
	std::string sql = "INSERT "
		"INTO bg_baseinfo_organization(org_rid, org_name, org_code, org_parent, org_path, source, create_time, update_time, state, order_no, duty_range, extend) "
		"VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

	try
	{
		Poco::JSON::Array::Ptr object_array = result.extract<Poco::JSON::Array::Ptr>();
		int object_array_count = object_array->size();

		Poco::JSON::Array::ConstIterator iter;
		for (iter = object_array->begin(); iter != object_array->end(); ++iter)
		{
			if (iter->type() == typeid(Poco::JSON::Object::Ptr))
			{
				// 这里按照规则创建一个rid
				// 规则GMO + 8位区位码 + 年月日时分秒 + 一个随机数
				std::string random_string;
				Poco::RandomInputStream rnd;
				rnd>>random_string;

				std::string area_code = "44010000";

				Poco::DateTime datetime;
				char rid[4096] = {0};
				sprintf(rid, "GMO%s%04d%02d%02d%02d%02d%02d%02x", area_code.c_str(),
					datetime.year(), datetime.month(), datetime.day(), datetime.hour(), datetime.minute(), datetime.second(),
					random_string.c_str());

				Poco::JSON::Object::Ptr element = iter->extract<Poco::JSON::Object::Ptr>();
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

				stat<<sql.c_str(), 
					Poco::Data::Keywords::use(rid), 
					Poco::Data::Keywords::use(org_name), 
					Poco::Data::Keywords::use(org_code),
					Poco::Data::Keywords::use(org_parent), 
					Poco::Data::Keywords::use(org_path), 
					Poco::Data::Keywords::use(source), 
					Poco::Data::Keywords::use(create_time), 
					Poco::Data::Keywords::use(update_time), 
					Poco::Data::Keywords::use(state),
					Poco::Data::Keywords::use(order_no),
					Poco::Data::Keywords::use(duty_range), 
					Poco::Data::Keywords::use(extend);

				org_rids.push_back(rid);
				org_names.push_back(org_name);
				org_codes.push_back(org_code);
				org_parents.push_back(org_parent);
				org_paths.push_back(org_path);
				sources.push_back(source);
				create_times.push_back(create_time);
				update_times.push_back(update_time);
				states.push_back(state);
				order_nos.push_back(order_no);
				duty_ranges.push_back(duty_range);
				extends.push_back(extend);
			}

		}

		std::size_t affect_rows = stat.execute();
		if (affect_rows == object_array_count)
		{
			Poco::JSON::Array org_array;
			for (int index = 0; index < org_rids.size(); ++index)
			{
				Poco::JSON::Object org_info;
				org_info.set("org_rid", org_rids[index]);
				org_info.set("org_name", org_names[index]);
				org_info.set("org_code", org_codes[index]);
				org_info.set("org_parent", org_parents[index]);
				org_info.set("org_path", org_paths[index]);
				org_info.set("source", sources[index]);
				org_info.set("create_time", create_times[index]);
				org_info.set("update_time", update_times[index]);
				org_info.set("state", states[index]);
				org_info.set("order_no", order_nos[index]);
				org_info.set("duty_range", duty_ranges[index]);
				org_info.set("extend", extends[index]);

				//Poco::Dynamic::Var org_info_var(org_info);
				org_array.add(org_info);
			}

			Poco::Dynamic::Var org_array_var(org_array);
			result_json_string = org_array_var.toString();
		}
	}
	catch(Poco::JSON::JSONException &e)
	{
		e.code();
		e.displayText();
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