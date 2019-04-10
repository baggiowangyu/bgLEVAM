#!/usr/bin/env python
# -*- coding: utf-8 -*-
# encoding=utf8

import sys
reload(sys)
sys.setdefaultencoding('utf8')
import requests
import json


REST_HOST = "127.0.0.1"
REST_PORT = 6001

def add_organization():

    org_info = list()
    org_count = 1
    for index in range(0, org_count):
        org = dict()
        org["org_name"] = "测试部门%d" % index
        org["org_code"] = "44012200"
        org["org_parent"] = "44012200"
        org["org_path"] = "44012200"
        org["source"] = "1"
        org["order_no"] = 0
        org["create_time"] = "2019-04-11 01:11:01"
        org["update_time"] = "2019-04-11 01:11:01"
        org["duty_range"] = "none"
        org["extend"] = "none"
        org_info.append(org)

    url_string = "http://%s:%d/api/v1/BaseInfo/AddOrganization" % (REST_HOST, REST_PORT)

    post_header = dict()
    post_header["Content-Type"] = "application/json"
    post_header["Accept"] = "application/json"

    response = requests.post(url=url_string, data=json.dumps(org_info), headers=post_header)



add_organization()