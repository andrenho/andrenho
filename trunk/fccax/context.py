import sys

class Unit:
    def __init__(self):
        self.x = 1
        self.y = 1

class Nation:
    def __init__(self, name):
        self.name = name
        self.gold = 0
        self.units = {}


class Context:
    
    def __init__(self, w, h=None):
        self.year = 0
        self.current = 0
        self.map = []
        self.nations = []
        if h != None:
            for y in range(0, h):
                self.map.append(['O'] * w)
        else:
            self.load(w)


    def load(self, file):
        context = None
        obj = 'context'
        for line in file.readlines():
            if line[-1] == '\n':
                line = line[0:-1]

            if line != '' and line[0] != '#':

                if obj == 'context':
                    if line == '%%':
                        obj = 'map'
                    else:
                        cmd, val = line.split(':')
                        if cmd == 'Year':
                            self.year = int(val)
                        if cmd == 'Current':
                            self.current = int(val)

                elif obj == 'map':
                    y = 0
                    if line == '%%':
                        obj = 'nation'
                    else:
                        self.map.append(line.split(':'))

                elif obj == 'nation':
                    name, gold = line.split(':')
                    nation = Nation(name)
                    nation.gold = int(gold)
                    self.nations.append(nation)
                    context = nation
                    obj = 'units'

                elif obj == 'units':
                    if line == '%%':
                        obj = 'nation'
                    else:
                        n, x, y = line.split(':')
                        u = Unit()
                        u.x, u.y = int(x), int(y)
                        context.units[int(n)] = u


    def print(self, f):
        # data
        print("Year: {0}".format(self.year), file=f)
        print("Current: {0}".format(self.current), file=f)
        print("\n%%\n", file=f)
        # map
        for row in self.map:
            print(':'.join(row), file=f)
        # nations
        print("\n%%\n", file=f)
        for nation in self.nations:
            print(nation.name + ':' + str(nation.gold), file=f)
            n = 0
            for n, unit in nation.units.items():
                print(':'.join((str(n), str(unit.x), str(unit.y))), file=f)
            print("\n%%\n", file=f)

