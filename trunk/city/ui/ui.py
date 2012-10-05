import pygame
from pygame.locals import *

from ui.cube import *
from ui.color import *

class UI:

    def __init__(self, w, h):
        pygame.init()
        self.init_window(w, h)
        self.load_images()


    def __del__(self):
        pygame.quit()


    def run(self):
        while True:
            for evt in pygame.event.get():
                if evt.type == QUIT:
                    return


    def init_window(self, w, h):
        self.sf = pygame.display.set_mode((w, h))
        self.sf.fill(Color.WHITE)
        pygame.display.set_caption('citymanager')
        pygame.display.update()


    def load_images(self):
        pygame.display.update()
