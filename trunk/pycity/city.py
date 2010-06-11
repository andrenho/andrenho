from residence import *
from person import *
import sys


class Tile:

    WALKING = 1
    DRIVING = 2

    def __init__(self, x, y):
        self.x, self.y = x, y
        self.structure = None

    def speed(self, type):
        if type == WALKING:
            return 5
        elif type == DRIVING:
            return 20
        else:
            sys.exit('aborted')


class City:

    def __init__(self, w, h):
        self.w, self.h = w, h
        self.tiles = dict()
        self.structures = []
        self.people = [Person()]
        for x in range(0, w):
            for y in range(0, h):
                self.tiles[(x, y)] = Tile(x, y)


    def process(self):
        for p in self.people:
            p.process()


    def build(self, structure):
        if structure.x < 0 or structure.y < 0 \
        or (structure.x+structure.w) >= self.w \
        or (structure.y+structure.h) >= self.h:
            return False
        else:
            tiles = []
            for x in range(structure.x, structure.x+structure.w):
                for y in range(structure.y, structure.y+structure.h):
                    tiles.append((x,y))
                    if self.tiles[(x,y)].structure != None:
                        return False
            self.structures.append(structure)
            for xy in tiles:
                self.tiles[xy].structure = structure
            return True
