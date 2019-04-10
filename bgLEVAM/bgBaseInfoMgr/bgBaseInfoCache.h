#ifndef _bgBaseInfoCache_H_
#define _bgBaseInfoCache_H_

#include <string>

//////////////////////////////////////////////////////////////////////////
//
// �豸������Ϣ��������
//
// ����֧������ģʽ�Ļ������ݣ�Redis���棬�����ڴ滺��
// - ��ʹ�ü�Ⱥģʽ������ģʽʱ������ʹ��Redis����
// - ��ʵ��ģʽ��ʹ���ڴ滺��
//
//////////////////////////////////////////////////////////////////////////
#define WORKMODE_REDIS		0	// Redis����ģʽ
#define WORKMODE_MEMORY		1	// �ڴ滺��ģʽ

class bgBaseInfoCache
{
public:
	bgBaseInfoCache();
	~bgBaseInfoCache();

public:
	// ��ʼ��
	int Initialize(int work_mode = WORKMODE_REDIS, const char *cache_host = "127.0.0.1", int cache_port = 6379);
	void Close();

public:
	int AddOrg(std::string &json_string, std::string &result_json_string);
	int RemoveOrg(std::string &json_string, std::string &result_json_string);
	int QueryOrg(std::string &json_string, std::string &result_json_string);
	int ModifyOrg(std::string &json_string, std::string &result_json_string);

public:
	int BuildCache(std::string &all_data);

private:
	//////////////////////////////////////////////////////////////////////////
	//
	// �ڴ滺�漯��
	//
	//////////////////////////////////////////////////////////////////////////
};

#endif//_bgBaseInfoCache_H_
