#include "bgOrganizationMgr.h"

#include <sstream>

bgOrganizationMgr::bgOrganizationMgr()
{

}

bgOrganizationMgr::~bgOrganizationMgr()
{

}

int bgOrganizationMgr::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	int err_code = 0;

	try
	{
		std::string uri = request.getURI();
		std::string method = request.getMethod();
		//std::string host = request.getHost();

		std::cout<<method.c_str()<<" "<<uri.c_str()<<std::endl;

		// 这里开始判断接口
		if (uri.compare("/api/v1/BaseInfo/AddOrganization") == 0)
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
				std::string result_json_string;
				err_code = this->InsertOrg(request_body, result_json_string);

				if (err_code != 0)
				{
					// 记录失败的情况
				}
				else
				{
					// 记录成功的情况
				}
			}
		}
		else if (uri.compare("/api/v1/BaseInfo/RemoveOrganization") == 0)
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
		else if (uri.compare("/api/v1/BaseInfo/QueryOrganization") == 0)
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
		else if (uri.compare("/api/v1/BaseInfo/ModifyOrganization") == 0)
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
		err_code = e.code();
		e.displayText();
		
		// 写日志
	}

	return err_code;
}

int bgOrganizationMgr::InsertOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	// 首先扔给数据库
	if (database_ == NULL)
		return -1;

	err_code = database_->AddOrg(json_string, result_json_string);
	if (err_code != 0)
	{
		// 数据库处理失败
	}

	// 添加到缓存中
	err_code = cache_->AddOrg(json_string, result_json_string);
	if (err_code != 0)
	{
		// 缓存处理失败
	}

	return err_code;
}

int bgOrganizationMgr::RemoveOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}

int bgOrganizationMgr::QueryOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}

int bgOrganizationMgr::ModifyOrg(std::string &json_string, std::string &result_json_string)
{
	int err_code = 0;

	return err_code;
}