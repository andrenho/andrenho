import http.server
import traceback

class WebService(http.server.CGIHTTPRequestHandler):

	log = None
	
	def name():
		raise NotImplementedError()


	def do_GET(self):
		path = [c for c in self.path.split('/') if c != '']
		try:
			method = getattr(self, 'GET_' + path[0])
			method(*path[1:])
		except AttributeError:
			err_desc = 'Invalid method GET_' + path[0] + ' called.'
			self.log.warning(err_desc)
			self.error(400, err_desc)
		except TypeError:
			err_desc = 'Invalid number of arguments for GET_' + path[0] + '.'
			self.log.warning(err_desc)
			self.error(400, err_desc)
		except Exception as e:
			self.send_response(500)
			self.send_header("Content-type", "text/xml")
			self.end_headers()
			xml = '<?xml version="1.0"?><exception><description>' + str(e) + '</description><traceback><![CDATA[' + traceback.format_exc() + ']]></traceback></exception>\n'
			self.wfile.write(bytes(xml, 'utf-8'))


	def do_POST(self):
		pass


	def error(self, code, description):
		self.send_response(code)
		self.send_header("Content-type", "text/xml")
		self.end_headers()
		xml = '<?xml version="1.0"?><error code="' + str(code) + '">' + description + '</error>'
		self.wfile.write(bytes(xml, 'utf-8'))

	
	def response(self, xml, code=200):
		self.send_response(code)
		self.send_header("Content-type", "text/xml")
		self.end_headers()
		self.wfile.write(bytes('<?xml version="1.0"?>' + xml, 'utf-8'))
