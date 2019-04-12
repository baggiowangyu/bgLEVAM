#ifndef _bgServerApp_H_
#define _bgServerApp_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Poco/Util/Application.h"
#include "Poco/Util/ServerApplication.h"

#include "bgBaseInfoDatabase.h"
#include "bgBaseInfoCache.h"

class bgServerApp : public Poco::Util::ServerApplication
{
public:
	// 初始化
	void initialize(Poco::Util::Application& self);

public:
	// 入口函数
	int main(const std::vector<std::string>& args);

public:
	bgBaseInfoDatabase *database_;
	bgBaseInfoCache *cache_;
};

#endif//_bgServerApp_H_
