import webservice

class Dummy(webservice.WebService):
	
	def name():
		return 'Dummy'

	def GET_start(self, n):
		print(0/0)
