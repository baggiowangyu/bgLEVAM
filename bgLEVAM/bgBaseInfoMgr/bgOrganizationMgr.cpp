#include "bgOrganizationMgr.h"

#include <sstream>

bgOrganizationMgr::bgOrganizationMgr()
{

}

bgOrganizationMgr::~bgOrganizationMgr()
{

}

int bgOrganizationMgr::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response, bgServerApp *app)
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
				std::string result_json_string;
				err_code = this->InsertOrg(request_body, result_json_string, app);

				if (err_code != 0)
				{
					// ��¼ʧ�ܵ����
				}
				else
				{
					// ��¼�ɹ������
				}
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

int bgOrganizationMgr::InsertOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app)
{
	int err_code = 0;

	// �����Ӹ����ݿ�
	if (app->database_ == NULL)
		return -1;

	std::string mysql_result_json;
	err_code = app->database_->AddOrg(json_string, mysql_result_json);
	if (err_code != 0)
	{
		// ���ݿ⴦��ʧ��
	}

	// ��ӵ�������
	err_code = app->cache_->AddOrg(mysql_result_json, result_json_string);
	if (err_code != 0)
	{
		// ���洦��ʧ��
	}

	return err_code;
}

int bgOrganizationMgr::RemoveOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app)
{
	int err_code = 0;

	return err_code;
}

int bgOrganizationMgr::QueryOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app)
{
	int err_code = 0;

	return err_code;
}

int bgOrganizationMgr::ModifyOrg(std::string &json_string, std::string &result_json_string, bgServerApp *app)
{
	int err_code = 0;

	return err_code;
}