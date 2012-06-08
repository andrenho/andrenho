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
    try:
        for line in open('init.txt'):
            prompt.onecmd(line)
    except IOError:
        pass
    _thread.start_new_thread(prompt.cmdloop, ())
    ui.run()


# vim: ts=8 et sw=4 sts=4
