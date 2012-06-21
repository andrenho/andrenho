import logging
logger = logging.getLogger('eprofile')
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
ch = logging.StreamHandler()
ch.setFormatter(formatter)
logger.addHandler(ch)


class Eprofile:

	class Comunicador:
		
		def __init__(self, bd_aplicacoes):
			self.bd_aplicacoes = bd_aplicacoes

		def registra_aplicacao(self, app):
			self.bd_aplicacoes.append(app)
			logger.debug('Aplicação ' + app + ' registrada.')


	class Configurador:
		
		def __init__(self, bd_modelos):
			self.bd_modelos = bd_modelos

		def registra_modelo(self, app, modelo):
			self.bd_modelos[app] = modelo
			logger.debug('Modelo do aplicativo ' + app + ' registrado.')


	class Raciocinador:
		pass


	class Conversor:
		pass


	def __init__(self):
		# bancos de dados
		self.bd_aplicacoes = []
		self.bd_modelos = {}
		# agentes
		self.comunicador = Eprofile.Comunicador(self.bd_aplicacoes)
		self.configurador = Eprofile.Configurador(self.bd_modelos)
		self.raciocinador = Eprofile.Raciocinador()
		self.conversor = Eprofile.Conversor()

	def conecta_aplicacao(self, app):
		self.comunicador.registra_aplicacao(app.codigo())

	def registra_modelo(self, app, modelo):
		self.configurador.registra_modelo(app.codigo(), modelo)


class Aplicacao:

	def __init__(self):
		self.modelo = None
	
	def conecta_gerenciador_trilhas(self, gerenciador):
		self.gr_trilhas = gerenciador

	def conecta_gerenciador_perfis(self, gerenciador):
		self.gr_perfis = gerenciador
		self.gr_perfis.conecta_aplicacao(self)

	def registra_modelo(self, modelo):
		self.modelo = modelo
		self.gr_perfis.registra_modelo(self, modelo)

	def codigo(self):
		raise Exception('Implementar este método.')


class Exemplo(Aplicacao):

	def codigo(self):
		return 'exemplo'


class GerenciadorTrilhas:
	pass


if __name__ == '__main__':
	app = Exemplo()
	trail = GerenciadorTrilhas()
	eprofile = Eprofile()

	app.conecta_gerenciador_trilhas(trail)
	app.conecta_gerenciador_perfis(eprofile)
	app.registra_modelo({ 'nome': str, 'idade': int })
