import pygame
from pygame.locals import *

class UI:

    def __init__(self, w, h):
        pygame.init()
        self.init_window(w, h)
        self.load_images()


    def run(self):
        while True:
            for evt in pygame.event.get():
                if evt.type == QUIT:
                    pygame.quit()
                    return


    def init_window(self, w, h):
        self.sf = pygame.display.set_mode((w, h))
        pygame.display.set_caption('citymanager')


    def load_images(self):
        pass
