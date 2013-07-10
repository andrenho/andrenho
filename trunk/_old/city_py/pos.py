class Pos:

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def tuple(self):
        return (self.x, self.y)

class Size:

    def __init__(self, w, h):
        self.w = w
        self.h = h

    def tuple(self):
        return (self.w, self.h)
