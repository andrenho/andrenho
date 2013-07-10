class Colors:

    colors = {
            'BLACK': (0, 0, 0),
            'WHITE': (255, 255, 255),
    }

    def __init__(self):
        self.numbers = {}
        n = 0
        self.palette = []
        for name, rgb in self.colors.items():
            self.numbers[name] = n
            self.palette.append(rgb)
            n += 1

    def __getattr__(self, name):
        if name in self.colors:
            return self.numbers[name]
        raise AttributeError

    def set_palette(self, surface):
        surface.set_palette(self.palette)

Color = Colors()
