import pygame

from ui.color import *

class Cube:
    
    def __init__(self, w, h):
        self.sf = pygame.Surface((100, 100))
        self.sf.fill(Color.WHITE)
        self.draw_cube(w, h)


    def surface(self):
        return self.sf

    def draw_cube(self, w, h):
        # Points:
        #
        #  /1\
        # 0\ /2
        # | 3 |
        # 4 | 5
        #  \6/
        p = [ (10, 20), (30, 10), (51, 20), (31, 30), (10, 40), (51, 40),
              (31, 50) ]
        # draw lines
        conn = ((0, 1), (1, 2), (0, 3), (2, 3), (0, 4), (3, 6), (4, 6), (5, 6), 
                (2, 5))
        for cn in conn:
            pygame.draw.line(self.sf, Color.BLACK, p[cn[0]], p[cn[1]], 1)
