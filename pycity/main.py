from city import *
from gui import *

city = City(15, 15)
gui = GUI(400, 300, city)

active = True
while active:
    gui.update_screen()
    gui.wait()
    active = gui.handle_events()
    city.process()
