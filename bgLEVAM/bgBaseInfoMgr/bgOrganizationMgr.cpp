#include "bgOrganizationMgr.h"

bgOrganizationMgr::bgOrganizationMgr()
{

}

bgOrganizationMgr::~bgOrganizationMgr()
{

}

int bgOrganizationMgr::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	try
	{
		std::string uri = request.getURI();
		std::string method = request.getMethod();
		//std::string host = request.getHost();

		// 这里开始判断接口
		if (uri.compare("/api/v1/BaseInfo/AddOrg") == 0)
		{
			// 添加组织架构，只支持POST数据
			if (method.compare("POST") != 0)
			{
				// 这里抛出异常
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// 正常来说这里会拿到一个Json，我们解析为Json
			}
		}
		else if (uri.compare("/api/v1/BaseInfo/RemoveOrg") == 0)
		{
			// 移除组织架构，只支持POST数据
			if (method.compare("POST") != 0)
			{
				// 这里抛出异常
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// 正常来说这里会拿到一个Json，我们解析为Json
			}
		}
		else if (uri.compare("/api/v1/BaseInfo/QueryOrg") == 0)
		{
			// 查询组织架构，支持GET数据
			if (method.compare("GET") != 0)
			{
				// 这里抛出异常
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// 正常来说这里会拿到一个Json，我们解析为Json
			}
		}
		else if (uri.compare("/api/v1/BaseInfo/ModifyOrg") == 0)
		{
			// 修改组织架构，只支持POST数据
			if (method.compare("POST") != 0)
			{
				// 这里抛出异常
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// 正常来说这里会拿到一个Json，我们解析为Json
			}
		}
		else
		{
			// 没有其他的接口了
			response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		}
	}
	catch(Poco::Exception e)
	{
		e.code();
		e.displayText();
		
		// 写日志
	}
}

int bgOrganizationMgr::InsertOrg()
{
	int err_code = 0;

	return err_code;
}

int bgOrganizationMgr::RemoveOrg()
{
	int err_code = 0;

	return err_code;
}

int bgOrganizationMgr::QueryOrg()
{
	int err_code = 0;

	return err_code;
}

int bgOrganizationMgr::ModifyOrg()
{
	int err_code = 0;

	return err_code;
}