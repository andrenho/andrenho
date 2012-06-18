#!/usr/bin/python3

import logging

import webservices
import communicator

logger = logging.getLogger('eprofile')
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
ch = logging.StreamHandler()
ch.setFormatter(formatter)
logger.addHandler(ch)

webservices = webservices.WebServices(logger)
webservices.register_service(communicator.Communicator)
