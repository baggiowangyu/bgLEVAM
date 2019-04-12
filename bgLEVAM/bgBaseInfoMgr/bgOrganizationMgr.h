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

#include "bgMsgHandler.h"


class bgOrganizationMgr : public MsgHandler
{
public:
	bgOrganizationMgr();
	~bgOrganizationMgr();

public:
	virtual int handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, bgServerApp *app);

private:
	// ������֯�ܹ�
	int InsertOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app);

	// ɾ����֯�ܹ�
	int RemoveOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app);

	// ��ѯ��֯�ܹ�
	int QueryOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app);

	// �޸���֯�ܹ�
	int ModifyOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app);

};

#endif//_bgOrganizationMgr_H_
