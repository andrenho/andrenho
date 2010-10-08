import sys

class Nation:
    def __init__(self, name):
        self.name = name
        self.gold = 0
        self.units = []

class Context:
    
    def __init__(self, w, h=None):
        self.year = 0
        self.map = []
        self.nations = []
        if h != None:
            for y in range(0, h):
                self.map.append(['O'] * w)
        else:
            self.load(w)


    def load(self, file):
        obj = self
        for line in file.readlines():
            if line[-1] == '\n':
                line = line[0:-1]

            if line != '' and line[0] != '#':

                if obj == self:
                    if line == '%%':
                        obj = self.map
                    else:
                        cmd, val = line.split(':')
                        if cmd == 'Year':
                            self.year = int(val)

                elif obj == self.map:
                    y = 0
                    if line == '%%':
                        obj = self.nations
                    else:
                        self.map.append(line.split(':'))

                elif obj == self.nations:
                    name, gold = line.split(':')
                    nation = Nation(name)
                    nation.gold = int(gold)
                    self.nations.append(nation)
                    obj = nation.units


    def print(self, f):
        # data
        print("Year: {0}".format(self.year), file=f)
        print("\n%%\n", file=f)
        # map
        for row in self.map:
            print(':'.join(row), file=f)
        # nations
        print("\n%%\n", file=f)
        for nation in self.nations:
            print(nation.name + ':' + str(nation.gold), file=f)
            print("\n%%\n", file=f)
