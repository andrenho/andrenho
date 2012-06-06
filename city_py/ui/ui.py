import sys
import pygame
from pygame.locals import *

from ui.colors import *


class UI:

    scale = 10

    def __init__(self, city):
        self.city = city
        pygame.init()
        self.clock = pygame.time.Clock()
        self.sf = pygame.display.set_mode((640, 480), 0, 8)
        pygame.display.set_caption('city 0.0.1')
        Color.set_palette(self.sf)
        self.running = True

    def run(self):
        while self.running:
            self.draw()
            self.do_events()
            self.clock.tick(30)

    def draw(self):
        self.sf.fill(Color.WHITE)
        for b in self.city.buildings:
            self.draw_building(b)
        pygame.display.update()

    def draw_building(self, b):
        rect = pygame.Rect(b.pos.tuple(), b.size.tuple())
        pygame.draw.rect(self.sf, Color.BLACK, rect, 1)

    def do_events(self):
        for e in pygame.event.get():
            if e.type == QUIT:
                self.quit()
        return True

    def quit(self):
        pygame.quit()
        self.running = False



# vim: ts=8 et sw=4 sts=4
