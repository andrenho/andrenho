import random, sys, pprint
pp = pprint.PrettyPrinter(indent=4)

tries = 100

class Attempts:
  def __init__(self):
    self.data = {}
    self.max_semester = 0
  
  def new_attempt(self, similarity, semester, confidence):
    if similarity not in self.data:
      self.data[similarity] = {}
    if semester not in self.data[similarity]:
      self.data[similarity][semester] = []
    self.data[similarity][semester].append(confidence)
    if semester > self.max_semester:
      self.max_semester = semester

  def print(self):
    for i in range(0, self.max_semester):
      print(i, self.avg(i, 0.3), self.avg(i, 0.4), self.avg(i, 0.5), self.avg(i, 0.6), self.avg(i, 0.7))

  def avg(self, semester, similarity):
    try:
      return sum(self.data[similarity][semester]) / float(len(self.data[similarity][semester]))
    except KeyError:
      return 0.0
  

attempts = Attempts()

random.seed()

for j in range(tries):
  for similarity in [round(x*0.1, 2) for x in range(3,8)]:

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
      for _ in range(random.randint(2,3)):
        subjects = []
        for _ in range(random.randint(2,3)):
          subjects.append(n)
          n += 1
        course.debates.append(subjects)

    #
    # faz vincluação entre os assuntos
    #
    vinc = {}
    for i in range(n):
      for _ in range(random.randint(1,2)):
        x = random.randint(0,n)
        if x not in vinc:
          vinc[x] = []
        if i not in vinc:
          vinc[i] = []
        if x != i:
          vinc[i].append(x)
          vinc[x].append(i) # TODO - verificar se todos os assuntos estão tendo vinculações
    # pp.pprint(vinc)

    #
    # cria alunos
    #
    class Student:

      def __init__(self, n):
        self.courses_taken = []
        self.n = n
        self.preferences = []
        self.__choice_on_debate = {}

      def set_choice_on_debate(self, subjects, subject):
        self.__choice_on_debate[':'.join(str(n) for n in sorted(subjects))] = subject

      def choice_on_debate(self, subjects):
        try:
          return self.__choice_on_debate[':'.join(str(n) for n in sorted(subjects))]
        except KeyError:
          return None

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

      def closest_students(self, n):
        st = {}
        for s in all_students:
          st[s] = self.similarity(s)
        return sorted(st, key=st.get)[0:n]

      #def similarity(self, other_student):
      #  n = 0
      #  for pref in self.preferences:
      #    for pref2 in other_student.preferences:
      #      n += 1
      #  return n
      def similarity(self, other_student):
        if len(self.preferences) == 0:
          return 0.0
        intersect = set(self.preferences).intersection(set(other_student.preferences))
        return len(intersect) / float(len(self.preferences))
        


    all_students = []
    st = 1
    for _ in range(50): # XXX
      all_students.append(Student(st))
      st += 1

    #
    # eProfile
    #
    class EProfile:
      def __init__(self, courses, students, similarity):
        self.courses = courses
        self.students = students
        self.similarity = similarity

      def similar_students(self, student, similarity):
        ss = []
        for other_student in set(self.students) - set([student]):
          if other_student.similarity(student) >= self.similarity:
            ss.append(other_student)
        return ss
      
      def suggest(self, debate, student):
        choices = {}
        for subject in debate:
          choices[subject] = 0
        # find similar
        for similar_student in self.similar_students(student, self.similarity):
          if similar_student.choice_on_debate(debate):
            choices[similar_student.choice_on_debate(debate)] += 1
        # check if one was chosen
        if sum(choices.values()) == 0:
          return None, 0
        # choose a value
        chosen = max(choices, key=lambda w: choices[w])
        n = choices[chosen] / float(sum(choices.values()))
        return chosen, n


    #
    # semestre
    #
    eprofile = EProfile(courses, all_students, similarity)
    semester = 0
    choices = 0
    automatic = 0

    semester_data = []

    while True:

      #if semester == 8:
      #  search_others = True

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
      n_deb_student = 0
      confidence_total = 0.0
      for course in (cr for cr in courses if cr.happening_this_semester()):
        for debate in course.debates:
          n_debates += 1
          for student in course.students:
            suggestion, confidence = eprofile.suggest(debate, student)
            confidence_total += confidence
            n_deb_student += 1
            if not suggestion:
              suggestion = debate[random.randint(0, len(debate)-1)]
            student.set_choice_on_debate(debate, suggestion)
            student.preferences.append(suggestion)
              

      #
      # relatório
      #
      attempts.new_attempt(similarity, semester, round(confidence_total/float(n_deb_student)*100, 2))
      #if 0:
      #  print('Semestre:', semester)
      #  print('Disciplinas ocorrendo:', len(list((cr for cr in courses if cr.happening_this_semester()))))
      #  print('Alunos cursando:', len(list(s for s in all_students if not s.graduated())))
      #  print('Alunos graduados:', len(list(s for s in all_students if s.graduated())))
      #  print('Debates:', n_debates)
      #  print('Escolhas automaticas:', automatic)
      #  print('Escolhas manuais:', choices)
      #  try:
      #    print('% escolhas automáticas:', round(automatic/float(choices+automatic)*100, 2))
      #  except ZeroDivisionError:
      #    print('% escolhas automáticas: 0.0')
      #  print('--------------------------')
      #else:
      #  #print(semester, round(automatic/float(choices+automatic)*100, 2))
      #  print(semester, round(confidence_total/float(n_deb_student)*100, 2))

      #choices = 0
      #automatic = 0
      #semester += 1

      print("Attempt ", j, similarity, semester+1, round(confidence_total/float(n_deb_student)*100, 2))
      semester += 1

attempts.print()

#pp.pprint(attempts.data)

# testes:
#  - tempo
#  - aumento das vinculações
#  - aumento do número de debates (?)
