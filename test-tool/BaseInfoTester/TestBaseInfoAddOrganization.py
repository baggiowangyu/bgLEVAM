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
    org_count = 100
    for index in range(1, org_count):
        org = dict()
        org["org_name"] = "测试部门%d" % index
        org["org_code"] = ""
        org["org_parent"] = ""
        org["org_path"] = ""
        org["source"] = ""
        org["order_no"] = ""
        org["create_time"] = ""
        org["update_time"] = ""
        org["duty_range"] = ""
        org["extend"] = ""
        org_info.append(org)

    url_string = "http://%s:%d/api/v1/BaseInfo/AddOrganization" % (REST_HOST, REST_PORT)

    post_header = dict()
    post_header["Content-Type"] = "application/json"
    post_header["Accept"] = "application/json"

    response = requests.post(url=url_string, data=json.dumps(org_info), headers=post_header)