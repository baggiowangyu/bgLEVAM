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
#include "Poco/Util/Application.h"

#include "bgMsgHandler.h"
#include "bgOrganizationMgr.h"
#include "bgBaseInfoDatabase.h"
#include "bgBaseInfoCache.h"

//////////////////////////////////////////////////////////////////////////
//
// HTTP请求处理对象
//
//////////////////////////////////////////////////////////////////////////
class bgRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	bgRequestHandler(bgBaseInfoDatabase *database, bgBaseInfoCache *cache, bgServerApp *app);

public:
	void SetMsgHandler(MsgHandler *msg_handler);

public:
	// 在这里处理所有的Restful请求
	virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	std::vector<MsgHandler *> msg_handlers_;

	bgServerApp *app_;
	bgBaseInfoDatabase *database_;
	bgBaseInfoCache *cache_;
};

//////////////////////////////////////////////////////////////////////////
//
// HTTP请求创建工厂，创建一个请求对象意味着创建了一个连接
//
//////////////////////////////////////////////////////////////////////////
class bgRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
	bgRequestHandlerFactory(bgBaseInfoDatabase *database, bgBaseInfoCache *cache, bgServerApp *app);

public:
	virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

public:
	// 处理接口对象
	bgOrganizationMgr *org_mgr_;

private:
	bgServerApp *app_;
	bgBaseInfoDatabase *database_;
	bgBaseInfoCache *cache_;
};

#endif//_bgHttpServer_H_
