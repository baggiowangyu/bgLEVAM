#include "bgServerApp.h"
#include "bgHttpServer.h"

#include "Poco/DateTimeFormatter.h"
#include "Poco/FileChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/Timestamp.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"


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

	std::cout<<"bgBaseInfoMgr >>> Version : "<<MODULE_VERSION<<std::endl;

	try
	{
		// 拿IP、端口进行绑定
		std::string ipaddress = config().getString("SERVICE.IP");
		unsigned int port = config().getUInt("SERVICE.PORT");
		Poco::Net::SocketAddress socket_address(ipaddress, port);
		Poco::Net::ServerSocket server_socket(socket_address);

		// 创建工厂类，加载插件对象给工厂类
		Poco::SharedPtr<bgRequestHandlerFactory> factory = new bgRequestHandlerFactory;

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