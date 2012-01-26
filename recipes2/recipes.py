import datetime

class Verb(object):
    def __init__(self):
        self.ingredient = None
        

class Ingredient(object):
    def __init__(self, name_en):
        self.name_en = name_en

    def text(self, lang):
        if lang == 'en':
            return self.name_en


class IngredientAmount(Ingredient):
    def __init__(self, ingredient, amt, measure):
        self.ingredient = ingredient
        self.amt = amt
        self.measure = measure

    def text(self, lang):
        if lang == 'en':
            return str(self.amt) + ' ' + self.measure + ' of ' + self.ingredient.text(lang)


class Recipe(Ingredient):
    def __init__(self, name='?'):
        self.name = name
        self.steps = []

    def ingredients(self):
        i = []
        for step in self.steps:
            if step.ingredient:
                i.append(step.ingredient)
        return i

    def write(self):
        print self.name
        print '-' * len(self.name)
        print
        self.write_detail()

    def write_detail(self):
        for ingredient in self.ingredients():
            print ingredient.text('en')
    

class Equipment(object):
    def __init__(self, name):
        self.name = name


class Preheat(Verb):
    def __init__(self, time):
        Verb.__init__(self)
        self.time = time

class Bake(Verb):
    def __init__(self, ingredient, time):
        Verb.__init__(self)
        self.ingredient = ingredient
        self.time = time

class Mix(Verb):
    def __init__(self, ingredient):
        Verb.__init__(self)
        self.ingredient = ingredient

class Put(Verb):
    def __init__(self, ingredient, equipment):
        Verb.__init__(self)
        self.ingredient = ingredient
        self.equipment = equipment

bowl = Equipment('bowl')

water = Ingredient('water')
salt = Ingredient('salt')
flour = Ingredient('flour')
olive_oil = Ingredient('oilve oil')


class CrackerMix(Recipe):
    def __init__(self):
        Recipe.__init__(self, 'Cracker Mix')
        self.steps.append(Put(IngredientAmount(flour, 50, 'g'), bowl))
        self.steps.append(Put(IngredientAmount(salt, 0.5, 'tsp'), bowl))
        self.steps.append(Put(IngredientAmount(olive_oil, 1, 'tbsp'), bowl))
        self.steps.append(Put(IngredientAmount(water, 30, 'ml'), bowl))

class CrackerDough(Recipe):
    def __init__(self):
        Recipe.__init__(self)
        self.steps.append(Mix(CrackerMix()))

class Cracker(Recipe):
    def __init__(self):
        Recipe.__init__(self, 'Crackers')
        self.steps.append(Preheat(datetime.timedelta(minutes=15)))
        self.steps.append(Bake(CrackerDough(), datetime.timedelta(minutes=30)))

CrackerMix().write()
