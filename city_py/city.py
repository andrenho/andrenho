#!/usr/bin/env python

import _thread

from ui.ui import *
from ui.prompt import *
from building import *


class City:

    def __init__(self):
        self.buildings = []
        self.people = []

    def build(self, building):
        self.buildings.append(building)


#
# main procedure
#
if __name__ == '__main__':
    city = City()
    ui = UI(city)
    prompt = Prompt(city, ui)
    _thread.start_new_thread(prompt.cmdloop, ())
    ui.run()
    #_thread.start_new_thread(ui.run, ())
    #city.build(Farm((1, 1), (4, 4)))
    #ui.run()


# vim: ts=8 et sw=4 sts=4
