import pygame
from residence import *


class GUI:

    TILE = 20

    def __init__(self, screen_w, screen_h, city):
        self.city = city
        pygame.init()
        pygame.display.set_mode((screen_w, screen_h))
        pygame.display.set_caption('pycity 0.0.1')
        self.screen = pygame.display.get_surface()
        self.clock = pygame.time.Clock()
        self.font = pygame.font.Font(None, 16)


    def draw_structures(self):
        for s in self.city.structures:
            r = pygame.Rect(s.x*GUI.TILE+1, s.y*GUI.TILE+1, s.w*GUI.TILE-1, s.h*GUI.TILE-1)
            self.screen.fill((0,0,0), r)
            r.x += 1; r.y += 1; r.w -= 2; r.h -= 2
            self.screen.fill((255,255,255), r)
            txt = self.font.render("RL", True, (0,0,0))
            self.screen.blit(txt, (10,10))
            

    def update_screen(self):
        self.screen.fill((255, 255, 255))
        self.draw_structures()
        pygame.display.flip()


    def tile_mouse(self):
        x, y = pygame.mouse.get_pos()
        return (int(x/GUI.TILE), int(y/GUI.TILE))


    def handle_keyboard(self, e):
        tile = self.tile_mouse()
        if e.unicode == 'l':
            self.city.build(Residence(tile[0], tile[1], Residence.LOW, Residence.LOW))
        elif e.unicode == 'L':
            self.city.build(Residence(tile[0], tile[1], Residence.LOW, Residence.HIGH))


    def handle_events(self):
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                return False
            elif e.type == pygame.KEYDOWN:
                self.handle_keyboard(e)

        return True


    def wait(self):
        self.clock.tick(30)
