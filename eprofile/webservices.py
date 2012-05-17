import threading
import http.server

class WebServices:

	def __init__(self, logger):
		self.log = logger
		self.log.debug('Webservice manager initialized')
		self.port = 8080

	def register_service(self, klass):
		httpd = None
		def ws():
			self.log.debug('Initializing service ' + klass.name() + ' in port ' + str(self.port))
			httpd = http.server.HTTPServer(('', self.port), klass)
			klass.log = self.log
			self.port += 1
			httpd.serve_forever()
		th = threading.Thread(target=ws)
		th.daemon = False
		th.start()
		self.log.debug('Service ' + klass.name() + ' initialized.')
