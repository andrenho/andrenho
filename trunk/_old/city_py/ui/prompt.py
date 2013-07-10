import cmd
import sys

from building.building import *
from pos import *


class Prompt(cmd.Cmd):

    def __init__(self, city, ui):
        cmd.Cmd.__init__(self)
        self.city = city
        self.ui = ui

    def do_q(self, arg):
        self.ui.quit()
        sys.exit()

    def do_farm(self, arg):
        x, y, w, h = map(int, arg.split())
        self.city.build(Farm(Pos(x, y), Size(w, h)))
