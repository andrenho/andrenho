class Course:
	def __init__(self, name, depend, optional=False):
		self.name = name
		self.depend = depend
		self.optional = optional

al1 = Course('Algoritmos I', [])
mat = Course('Matemática elementar', [])
geo = Course('Geometria analítica', [])
por = Course('Português', [])
an1 = Course('Análise de sistemas I', [])
al2 = Course('Algoritmos II', [al1])
est = Course('Estrutura de Dados', [al1])
ca1 = Course('Cálculo I', [mat, geo])
an2 = Course('Análise de Sistemas II', [an1])
ing = Course('Inglês', [])
co1 = Course('Compiladores I', [al2, est])
lip = Course('Linguagens de Programação', [al2, est])
arq = Course('Arquitetura de Computadores', [])
eng = Course('Engenharia de Software', [an2])
fil = Course('Filosofia', [por])
co2 = Course('Compiladores II', [co1], True)
mic = Course('Microprocessadores', [arq], True)
ca2 = Course('Cálculo II', [ca1], True)
bds = Course('Bancos de Dados', [an1], True)
red = Course('Redes', [], True)
tc1 = Course('TCC I', [co1, lip, arq, eng, bds])
ele = Course('Eletrônica Digital', [mic], True)
int = Course('Inteligência Artificial', [eng, ca2], True)
gra = Course('Computação Gráfica', [eng, ca2], True)
ger = Course('Gerência de TI', [eng, bds], True)
tc2 = Course('TCC II', [tc1])
rob = Course('Robótica', [ele])
sos = Course('Sistemas Operacionais', [co2, mic, eng], True)
gpr = Course('Gerência de Projetos', [ger], True)
ala = Course('Algoritmos Avançados', [al2, est], True)

courses = (al1, mat, geo, por, an1, al2, est, ca1, an2, ing, co1, lip, arq, eng, fil, co2, mic, ca2, bds, red, tc1, ele, int, gra, ger, tc2, rob, sos, gpr, ala)
