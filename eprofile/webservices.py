import threading
import http.server

class WebServices:

	def __init__(self, logger):
		self.threads = []
		self.log = logger
		self.log.debug('Webservice manager initialized')

	def register_service(self, klass):
		def ws():
			self.log.debug('Initializing service...') # TODO service name
			httpd = http.server.HTTPServer(('', 8080), klass) # TODO port
			httpd.serve_forever()
		th = threading.Thread(target=ws)
		th.daemon = False
		th.start()
		self.threads.append(th)
		self.log.debug('Service initialized.')
