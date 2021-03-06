#include "bgServerApp.h"
#include "bgHttpServer.h"

#include "Poco/DateTimeFormatter.h"
#include "Poco/FileChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Timestamp.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"

#include <sstream>


#define MODULE_VERSION	"1.0.0.1"


void bgServerApp::initialize(Poco::Util::Application& self)
{
	Poco::Util::Application::initialize(self);

	std::string current_working_dir = Poco::Path::current();
	Poco::Path config_path(current_working_dir);
	config_path.append("config.ini");
	this->loadConfiguration(config_path.toString(Poco::Path::PATH_NATIVE));

	int log_level = config().getInt("LOG_INFO.LEVEL");

	// 初始化日志
	std::string name = "log_";
	name.append(Poco::DateTimeFormatter::format(Poco::Timestamp(), "%Y%m%d_%H%M%S"));
	name.append(".log");

	Poco::AutoPtr<Poco::FileChannel> fileChannel(new Poco::FileChannel);
	fileChannel->setProperty("path", name);
	fileChannel->setProperty("rotation", "50 M");
	fileChannel->setProperty("archive", "timestamp");

	// 每条日志的时间格式
	Poco::AutoPtr<Poco::PatternFormatter> patternFormatter(new Poco::PatternFormatter());
	patternFormatter->setProperty("pattern","[%Y-%m-%d %H:%M:%S] %p %s(%l): %t");

	//初始化　Channel
	Poco::AutoPtr<Poco::Channel> channel = new Poco::FormattingChannel(patternFormatter,fileChannel);
	logger().setChannel(channel);
	logger().setLevel(log_level);

	return ;
}

int bgServerApp::main(const std::vector<std::string>& args)
{
	int errCode = Poco::Util::Application::EXIT_OK;
	std::string errstr;
	std::stringstream stream;

	stream.str("");
	stream<<"bgBaseInfoMgr Started..."<<std::endl<<"Version : "<<MODULE_VERSION;
	std::cout<<stream.str().c_str()<<std::endl;
	logger().information(stream.str());

	try
	{
		// 拿IP、端口进行绑定
		std::string ipaddress = config().getString("SERVICE.HOST");
		unsigned int port = config().getUInt("SERVICE.PORT");
		Poco::Net::SocketAddress socket_address(ipaddress, port);
		Poco::Net::ServerSocket server_socket(socket_address);

		stream.str("");
		stream<<"Listen address : "<<ipaddress.c_str()<<":"<<port;
		std::cout<<stream.str().c_str()<<std::endl;
		logger().information(stream.str());

		// 初始化数据库
		int database_type = config().getInt("DATABASE.TYPE");
		std::string database_host = config().getString("DATABASE.HOST");
		int database_port = config().getInt("DATABASE.PORT");
		std::string database_username = config().getString("DATABASE.USER");
		std::string database_password = config().getString("DATABASE.PASS");
		std::string database_dbname = config().getString("DATABASE.DBNAME");
		database_ = new bgBaseInfoDatabase();
		errCode = database_->Initialize(database_host.c_str(), database_port, database_username.c_str(), database_password.c_str(), database_dbname.c_str());
		if (errCode != 0)
		{
			std::cout<<"Database connect failed..."<<std::endl;
		}

		// 初始化缓存
		int cache_mode = config().getInt("CACHE.MODE");
		std::string cache_host = config().getString("CACHE.HOST");
		int cache_port = config().getInt("CACHE.PORT");

		cache_ = new bgBaseInfoCache();
		errCode = cache_->Initialize(cache_mode, cache_host.c_str(), cache_port);
		if (errCode != 0)
		{
			std::cout<<"Database connect failed..."<<std::endl;
		}

		// 从数据库构建缓存数据
		std::string database_all_data_json;
		errCode = database_->GetAllData(database_all_data_json);
		if (errCode != 0)
		{
			std::cout<<"Database get all data failed..."<<std::endl;
		}

		errCode = cache_->BuildCache(database_all_data_json);
		if (errCode != 0)
		{
			std::cout<<"Cache build failed..."<<std::endl;
		}

		// 创建工厂类，加载插件对象给工厂类
		Poco::SharedPtr<bgRequestHandlerFactory> factory = new bgRequestHandlerFactory(database_, cache_, this);

		Poco::Net::HTTPServer server(factory, server_socket, new Poco::Net::HTTPServerParams);
		server.start();
		waitForTerminationRequest();
		server.stop();
	}
	catch (Poco::Exception e)
	{
		errCode = e.code(); 
		errstr = e.displayText();
	}

	return Poco::Util::Application::EXIT_OK;
}