#ifndef _bgOrganizationMgr_H_
#define _bgOrganizationMgr_H_

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
#include "Poco/StreamCopier.h"

#include "bgHttpServer.h"

class bgOrganizationMgr : public MsgHandler
{
public:
	bgOrganizationMgr();
	~bgOrganizationMgr();

public:
	virtual int handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
	// 增加组织架构
	int InsertOrg();

	// 删除组织架构
	int RemoveOrg();

	// 查询组织架构
	int QueryOrg();

	// 修改组织架构
	int ModifyOrg();

private:
};

#endif//_bgOrganizationMgr_H_
