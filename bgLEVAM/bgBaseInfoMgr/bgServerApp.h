#ifndef _bgServerApp_H_
#define _bgServerApp_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Poco/Util/Application.h"
#include "Poco/Util/ServerApplication.h"

class bgServerApp : public Poco::Util::ServerApplication
{
public:
	// ��ʼ��
	void initialize(Poco::Util::Application& self);

public:
	// ��ں���
	int main(const std::vector<std::string>& args);
};

#endif//_bgServerApp_H_
