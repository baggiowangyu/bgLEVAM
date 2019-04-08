#include "bgHttpServer.h"

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
		err_code = iter->handleRequest(request, response);
		if (err_code != Msghandler_NotSupported)
		{
			// 说明是此处理对象处理的，跳出
			break;
		}
	}

	std::ostream &out = response.send();
	return ;
}


Poco::Net::HTTPRequestHandler*  bgRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	bgRequestHandler *handler = new bgRequestHandler;

	// 装载消息处理对象
	handler->SetMsgHandler(&org_mgr_);

	return handler;
}