#include "bgHttpServer.h"

bgRequestHandler::bgRequestHandler(bgBaseInfoDatabase *database, bgBaseInfoCache *cache, Poco::Util::Application *app)
: database_(database)
, cache_(cache)
, app_(app)
{
}

void bgRequestHandler::SetMsgHandler(MsgHandler *msg_handler)
{
	msg_handlers_.push_back(msg_handler);
}

void bgRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	int err_code = 0;

	std::vector<MsgHandler *>::iterator iter;
	for (iter = msg_handlers_.begin(); iter != msg_handlers_.end(); ++iter)
	{
		MsgHandler *handler = *iter;
		err_code = handler->handleRequest(request, response);
		if (err_code != Msghandler_NotSupported)
		{
			// 说明是此处理对象处理的，跳出
			break;
		}
	}

	std::ostream &out = response.send();
	return ;
}


bgRequestHandlerFactory::bgRequestHandlerFactory(bgBaseInfoDatabase *database, bgBaseInfoCache *cache, Poco::Util::Application *app)
: database_(database)
, cache_(cache)
, app_(app)
, org_mgr_(new bgOrganizationMgr(database_, cache_))
{
}

Poco::Net::HTTPRequestHandler*  bgRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	bgRequestHandler *handler = new bgRequestHandler(database_, cache_, app_);

	// 装载消息处理对象
	handler->SetMsgHandler(org_mgr_);

	return handler;
}
