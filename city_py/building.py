from pos import *

class Building:

    def __init__(self, pos):
        self.pos = pos
        self.size = Size(1, 1)


class Workplace(Building):
    pass


class Farm(Workplace):

    def __init__(self, pos, size):
        Workplace.__init__(self, pos)
        self.size = size


# vim: ts=8 et sw=4 sts=4
