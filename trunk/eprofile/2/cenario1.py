import random, sys, pprint
pp = pprint.PrettyPrinter(indent=4)

class Course:

  def __init__(self, name, depend, optional=False):
    self.name = name
    self.depend = depend
    self.optional = optional
    self.debates = []

  def new_semester(self):
    self.students = []

  def available(self):
    return 25 - len(self.students)

  def happening_this_semester(self):
    return (len(self.students) > 0)

  def __repr__(self):
    return "<" + self.name + ">"

#
# incializa cursos
#
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
#courses = (al1,mat,geo,por,an1)

#
# cria assuntos aleatórios
# 
n = 0
for course in courses:
  for _ in range(random.randint(3,5)):
    subjects = []
    for _ in range(random.randint(3,5)):
      subjects.append(n)
      n += 1
    course.debates.append(subjects)

#
# faz vincluação entre os assuntos
#
vinc = {}
for i in range(n):
  for _ in range(random.randint(5,10)):
    x = random.randint(0,n)
    if x not in vinc:
      vinc[x] = []
    if i not in vinc:
      vinc[i] = []
    if x != i:
      vinc[i].append(x)
      vinc[x].append(i) # TODO - verificar se todos os assuntos estão tendo vinculações
pp.pprint(vinc)

#
# cria alunos
#
class Student:

  def __init__(self, n):
    self.courses_taken = []
    self.n = n
    self.preferences = []
  
  def graduated(self):
    return (len(self.courses_taken) >= 25)

  def courses_available(self):
    c = []
    for course in set(courses) - set(self.courses_taken):
      n = len([x for x in course.depend if x in self.courses_taken])
      if len(course.depend) == n:
        c.append(course)
    c.extend(set(c for c in courses if c.depend == []) - set(self.courses_taken))
    return c

  def next_course(self):
    c = self.courses_available()
    n = len(c)
    if n > 0:
      return c[random.randint(0, n-1)]
    else:
      return None

all_students = []
st = 1
for _ in range(1): # XXX
  all_students.append(Student(st))
  st += 1

#
# semestre
# 
semester = 1
choices = 0
automatic = 0
while True:
  students = list(s for s in all_students if not s.graduated())
  if len(students) == 0:
    break

  #
  # matricula
  #
  for c in courses:
    c.new_semester()
  for s in students:
    for _ in range(random.randint(1,2)):
      c = s.next_course()
      if c == None:
        print('Fail.')
        sys.exit(1)
      if c.available():
        s.courses_taken.append(c)
        c.students.append(s)

  #
  # debates
  #
  n_debates = 0
  for course in (cr for cr in courses if cr.happening_this_semester()):
    for debate in course.debates:
      n_debates += 1
      for student in course.students:
        found = False
        for subject in debate:
          if subject in student.preferences:
            print(debate, sorted(student.preferences), 'auto')
            automatic += 1
            found = True
            break
          else:
            for preference in student.preferences:
              if preference in vinc[subject]:
                found = True
                print(debate, sorted(student.preferences), 'related')
                student.preferences.append(subject)
                automatic += 1
                break
            continue
        if not found:
          n = debate[random.randint(0, len(debate)-1)]
          print(debate, sorted(student.preferences), 'manual')
          student.preferences.append(n)
          choices += 1


  #
  # relatório
  #
  print('Semestre:', semester)
  print('Disciplinas ocorrendo:', len(list((cr for cr in courses if cr.happening_this_semester()))))
  print('Alunos cursando:', len(list(s for s in all_students if not s.graduated())))
  print('Alunos graduados:', len(list(s for s in all_students if s.graduated())))
  print('Debates:', n_debates)
  print('Escolhas automaticas:', automatic)
  print('Escolhas manuais:', choices)
  print('% escolhas automáticas:', round(automatic/float(choices+automatic)*100, 2))
  print('--------------------------')
  
  choices = 0
  automatic = 0
  semester += 1




# testes:
#  - tempo
#  - aumento das vinculações
#  - aumento do número de debates (?)
