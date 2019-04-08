#ifndef _bgHttpServer_H_
#define _bgHttpServer_H_

#include "Poco/Net/SocketStream.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/NetException.h"

#include "bgOrganizationMgr.h"

//////////////////////////////////////////////////////////////////////////
//
// 定义消息处理抽象类
//
//////////////////////////////////////////////////////////////////////////
#define Msghandler_NotSupported	-6002
class MsgHandler
{
public:
	virtual int handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) = 0;
};


//////////////////////////////////////////////////////////////////////////
//
// HTTP请求处理对象
//
//////////////////////////////////////////////////////////////////////////
class bgRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	void SetMsgHandler(MsgHandler *msg_handler);

public:
	// 在这里处理所有的Restful请求
	virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	std::vector<MsgHandler *> msg_handlers_;
};

//////////////////////////////////////////////////////////////////////////
//
// HTTP请求创建工厂，创建一个请求对象意味着创建了一个连接
//
//////////////////////////////////////////////////////////////////////////
class bgRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
	virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

public:
	// 处理接口对象
	bgOrganizationMgr org_mgr_;
};

#endif//_bgHttpServer_H_
