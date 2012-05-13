#!/usr/bin/python3

import webservices
import dummy

webservices = webservices.WebServices()
webservices.register_service(dummy.Dummy)
webservices.start()
