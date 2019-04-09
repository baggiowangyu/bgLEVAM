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

#include "bgMsgHandler.h"
#include "bgOrganizationMgr.h"

//////////////////////////////////////////////////////////////////////////
//
// HTTP���������
//
//////////////////////////////////////////////////////////////////////////
class bgRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	void SetMsgHandler(MsgHandler *msg_handler);

public:
	// �����ﴦ�����е�Restful����
	virtual void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	std::vector<MsgHandler *> msg_handlers_;
};

//////////////////////////////////////////////////////////////////////////
//
// HTTP���󴴽�����������һ�����������ζ�Ŵ�����һ������
//
//////////////////////////////////////////////////////////////////////////
class bgRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
	virtual Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);

public:
	// ����ӿڶ���
	bgOrganizationMgr org_mgr_;
};

#endif//_bgHttpServer_H_
