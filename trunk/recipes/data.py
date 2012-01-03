from google.appengine.ext import db

class Ingredient(db.Model):
  name = db.StringProperty()
  parents = db.ListProperty(db.Key)
  wikipedia_link = db.LinkProperty()

  @staticmethod
  def reset():
    pass
