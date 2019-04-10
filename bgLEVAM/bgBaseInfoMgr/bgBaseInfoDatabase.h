#ifndef _bgBaseInfoDatabase_H_
#define _bgBaseInfoDatabase_H_

#include "Poco/Exception.h"
#include "Poco/Data/Session.h"
//#include "Poco/Data/Common.h"
//#include "Poco/Data/BLOB.h"
#include "Poco/Data/StatementImpl.h"
#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/SessionPool.h"
#include "Poco/Data/PooledSessionImpl.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"

class bgBaseInfoDatabase
{
public:
	bgBaseInfoDatabase();
	~bgBaseInfoDatabase();

public:
	int Initialize(const char *mysql_host = "127.0.0.1", int mysql_port = 3306, const char *mysql_username = "username", const char *mysql_password = "password", const char *mysql_dbname = "baseinfo");
	void Close();

public:
	int AddOrg(std::string &json_string, std::string &result_json_string);
	int RemoveOrg(std::string &json_string, std::string &result_json_string);
	int QueryOrg(std::string &json_string, std::string &result_json_string);
	int ModifyOrg(std::string &json_string, std::string &result_json_string);

public:
	int GetAllData(std::string &all_data);

private:
	std::string connection_string_;
	Poco::SharedPtr<Poco::Data::Session> session_;
};

#endif//_bgBaseInfoDatabase_H_
