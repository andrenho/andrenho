class Comunicador:
	pass


class Configurador:
	pass


class Raciocinador:
	pass


class Conversor:
	pass


class Eprofile:

	def conecta_aplicacao(self, app):
		pass


class Aplicacao:
	
	def conecta_gerenciador_trilhas(self, gerenciador):
		self.gr_trilhas = gerenciador

	def conecta_gerenciador_perfis(self, gerenciador):
		self.gr_perfis = gerenciador
		self.gr_perfis.conecta_aplicacao(self)


class GerenciadorTrilhas:
	pass


if __name__ == '__main__':
	app = Aplicacao()
	trail = GerenciadorTrilhas()
	eprofile = Eprofile()

	app.conecta_gerenciador_trilhas(trail)
	app.conecta_gerenciador_perfis(eprofile)
