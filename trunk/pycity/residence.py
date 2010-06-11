from structure import *

class Residence(Structure):

    LOW       = 1
    MEDIUM    = 2
    HIGH      = 3
    VERY_HIGH = 4

    def __init__(self, x, y, klass, density):
        self.x, self.y, self.klass, self.density = x, y, klass, density
        self.level = 0
        self.residents = 0
        if density == Residence.LOW:
            if klass == Residence.LOW:
                self.w, self.h = (1, 1)
                self.desc = 'rl'
            elif klass == Residence.MEDIUM:
                self.w, self.h = (2, 2)
                self.desc = 'rm'
            elif klass == Residence.HIGH:
                self.w, self.h = (3, 3)
                self.desc = 'rh'
            elif klass == Residence.VERY_HIGH:
                self.w, self.h = (4, 4)
                self.desc = 'rv'
        elif density == Residence.HIGH:
            if klass == Residence.LOW:
                self.w, self.h = (2, 2)
                self.desc = 'RL'
            elif klass == Residence.MEDIUM:
                self.w, self.h = (4, 4)
                self.desc = 'RM'
            elif klass == Residence.HIGH:
                self.w, self.h = (6, 6)
                self.desc = 'RH'
            else:
                raise Exception('Residence type not supported.')
        else:
            raise Exception('Residence type not supported.')
