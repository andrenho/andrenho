import logging
logger = logging.getLogger('eprofile')
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
ch = logging.StreamHandler()
ch.setFormatter(formatter)
logger.addHandler(ch)


class Eprofile:

	class Comunicador:
		
		def __init__(self, bd_aplicacoes, bd_entidades):
			self.bd_aplicacoes = bd_aplicacoes
			self.bd_entidades = bd_entidades

		def registra_aplicacao(self, app):
			self.bd_aplicacoes.add(app)
			logger.debug('Aplicação ' + app + ' registrada.')

		def registra_entidade(self, entidade):
			self.bd_entidades.add(entidade)
			logger.debug('Entidade ' + entidade + ' registrada.')


	class Configurador:
		
		def __init__(self, bd_modelos, bd_regras):
			self.bd_modelos = bd_modelos
			self.bd_regras = bd_regras

		def registra_modelo(self, app, modelo):
			self.bd_modelos[app] = modelo
			logger.debug('Modelo do aplicativo ' + app + ' registrado.')

		def registra_regra(self, app, regra):
			if app not in self.bd_regras:
				self.bd_regras[app] = []
			self.bd_regras[app].append(regra)
			logger.debug('Regra registrada para o aplicativo ' + app + ': ' + regra)


	class Raciocinador:
		pass


	class Conversor:
		pass


	def __init__(self):
		# bancos de dados
		self.bd_aplicacoes = set()
		self.bd_entidades = set()
		self.bd_modelos = {}
		self.bd_regras = {}
		# agentes
		self.comunicador = Eprofile.Comunicador(self.bd_aplicacoes, self.bd_entidades)
		self.configurador = Eprofile.Configurador(self.bd_modelos, self.bd_regras)
		self.raciocinador = Eprofile.Raciocinador()
		self.conversor = Eprofile.Conversor()

	def conecta_aplicacao(self, app):
		self.comunicador.registra_aplicacao(app)

	def registra_modelo(self, app, modelo):
		self.configurador.registra_modelo(app, modelo)

	def registra_entidade(self, entidade):
		self.comunicador.registra_entidade(entidade)

	def registra_regra(self, app, regra):
		self.configurador.registra_regra(app, regra)


class Aplicacao:

	def __init__(self):
		self.modelo = None
	
	def conecta_gerenciador_trilhas(self, gerenciador):
		self.gr_trilhas = gerenciador

	def conecta_gerenciador_perfis(self, gerenciador):
		self.gr_perfis = gerenciador
		self.gr_perfis.conecta_aplicacao(self.codigo())

	def registra_modelo(self, modelo):
		self.modelo = modelo
		self.gr_perfis.registra_modelo(self.codigo(), modelo)

	def registra_regra(self, regra):
		self.gr_perfis.registra_regra(self.codigo(), regra)

	def nova_entidade(self, entidade):
		self.gr_perfis.registra_entidade(entidade)

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
	app.nova_entidade('andre')
	app.registra_regra('teste')
