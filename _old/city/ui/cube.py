import pygame

from ui.color import *

class Cube:

    def __init__(self, w, h, height=15):
        self.w = w
        self.h = h
        self.height = height
        self.draw_cube(w, h, height)


    def surface(self):
        return self.sf

    
    def center(self):
        return ((self.w * 20), (self.w * 10) + (self.h * 10) + self.height)


    def draw_cube(self, w, h, height):
        # calculate points:
        #
        #  /1\
        # 0\ /2
        # | 3 |
        # 4 | 5
        #  \6/
        # w   h
        p = [[0, 0]] * 7
        p[0] = [0, (h*10)]
        p[1] = [p[0][0] + (h * 20), p[0][1] - (h * 10)]
        p[2] = [p[1][0] + (w * 20), p[1][1] + (w * 10)]
        p[3] = [p[2][0] - (h * 20), p[2][1] + (h * 10)]
        p[4] = [p[0][0], p[0][1] + height]
        p[5] = [p[2][0], p[2][1] + height]
        p[6] = [p[3][0], p[3][1] + height]

        # draw lines
        self.sf = pygame.Surface((p[2][0]+1, p[6][1]+1))
        self.sf.set_colorkey(Color.TRANSPARENT)
        self.sf.fill(Color.TRANSPARENT)
        for polygon in ( (0,1,2,3), (0,3,6,4), (3,2,5,6) ):
            ptlist = []
            for pt in polygon:
                ptlist.append((p[pt][0], p[pt][1]))
            pygame.draw.polygon(self.sf, Color.WHITE, ptlist, 0)
            pygame.draw.polygon(self.sf, Color.BLACK, ptlist, 1)
