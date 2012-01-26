import datetime

class Verb(object):
    def __init__(self, name):
        self.name = name
        

class Ingredient(object):
    def __init__(self, name):
        self.name = name


class Recipe(Ingredient):
    def __init__(self, name='?'):
        self.name = name
        self.steps = []


class Equipment(object):
    def __init__(self, name):
        self.name = name


class Measure(object):
    def __init__(self, amount, measure):
        self.amount = amount
        self.measure = measure


class Weight(Measure):
    def __init__(self, amount, measure):
        self.amount = amount
        self.measure = measure


class Volume(Measure):
    def __init__(self, amount, measure):
        self.amount = amount
        self.measure = measure


put = Verb('put')
mix = Verb('mix')
preheat = Verb('preheat')
bake = Verb('bake')

bowl = Equipment('bowl')

water = Ingredient('water')
salt = Ingredient('salt')
flour = Ingredient('flour')
olive_oil = Ingredient('oilve_oil')

cracker_mix = Recipe('cracker_mix')
cracker_mix.steps.append((put, (flour, Weight(50, 'g')), bowl))
cracker_mix.steps.append((put, (salt, Weight(1/2, 'tsp')), bowl))
cracker_mix.steps.append((put, (olive_oil, Weight(1, 'tbsp')), bowl))
cracker_mix.steps.append((put, (flour, Volume(30, 'ml')), bowl))

cracker_dough = Recipe('cracker_dough')
cracker_dough.steps.append((mix, bowl))

cracker = Recipe('cracker')
cracker.steps.append((preheat, datetime.timedelta(minutes=15)))
cracker.steps.append((bake, (cracker_dough, 1), datetime.timedelta(minutes=30)))
