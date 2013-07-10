from google.appengine.ext import db

class Recipe(db.Model):
  #name = db.StringProperty(required=True)
  ingredients = db.ListProperty(db.Key)
  # material required
  instructions = db.ListProperty(db.ListProperty(db.Key))
  wikipedia_link = db.LinkProperty()

  @staticmethod
  def reset():
    flour = Recipe(key_name="flour")
    flour.put()
    salt = Recipe(key_name="salt")
    salt.put()
    water = Recipe(key_name="water")
    water.put()
    oilve_oil = Recipe(key_name="olive_oil")
    olive_oil.put()
    cracker_dough = Recipe(key_name="cracker_dough",
        ingredients=[])
    cracker_dough.put()
