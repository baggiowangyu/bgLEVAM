//////////////////////////////////////////////////////////////////////////
//
// ������Ϣ����ģ��

#include <iostream>

#include "bgServerApp.h"

int main(int argc, char *argv[])
{
	bgServerApp app;
	int err_code = app.run(argc, argv);

	return err_code;
}