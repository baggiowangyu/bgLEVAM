#ifndef _MsgHandler_H_
#define _MsgHandler_H_

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

#include "bgServerApp.h"

//////////////////////////////////////////////////////////////////////////
//
// 定义消息处理抽象类
//
//////////////////////////////////////////////////////////////////////////
#define Msghandler_NotSupported	-6002

class MsgHandler
{
public:
	virtual int handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, bgServerApp *app) = 0;
};

#endif//_MsgHandler_H_
