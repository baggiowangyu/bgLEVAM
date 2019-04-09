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

		// ���￪ʼ�жϽӿ�
		if (uri.compare("/api/v1/BaseInfo/AddOrganization") == 0)
		{
			// �����֯�ܹ���ֻ֧��POST����
			if (method.compare("POST") != 0)
			{
				// �����׳��쳣
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// ������˵������õ�һ��Json�����ǽ���ΪJson
			}
		}
		else if (uri.compare("/api/v1/BaseInfo/RemoveOrganization") == 0)
		{
			// �Ƴ���֯�ܹ���ֻ֧��POST����
			if (method.compare("POST") != 0)
			{
				// �����׳��쳣
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// ������˵������õ�һ��Json�����ǽ���ΪJson
			}
		}
		else if (uri.compare("/api/v1/BaseInfo/QueryOrganization") == 0)
		{
			// ��ѯ��֯�ܹ���֧��GET����
			if (method.compare("GET") != 0)
			{
				// �����׳��쳣
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// ������˵������õ�һ��Json�����ǽ���ΪJson
			}
		}
		else if (uri.compare("/api/v1/BaseInfo/ModifyOrganization") == 0)
		{
			// �޸���֯�ܹ���ֻ֧��POST����
			if (method.compare("POST") != 0)
			{
				// �����׳��쳣
				response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
			}
			else
			{
				std::ostringstream ostr;
				std::istream &is = request.stream();
				std::istream *ptr_rs = &is;
				Poco::StreamCopier::copyStream(*ptr_rs, ostr);

				std::string request_body = ostr.str();

				// ������˵������õ�һ��Json�����ǽ���ΪJson
			}
		}
		else
		{
			// û�������Ľӿ���
			response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
		}
	}
	catch(Poco::Exception e)
	{
		err_code = e.code();
		e.displayText();
		
		// д��־
	}

	return err_code;
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