class Pos:

	def __init__(self, long, lat):
		self.long = long
		self.lat = lat

	def x(self, config):
		return (self.lat + config.lat) * config.scale

	def y(self, config):
		return (self.long + config.long) * config.scale


class City(Pos):

	def __init__(self, name, pop, long, lat):
		Pos.__init__(self, long, lat)
		self.name = name
		self.pop = pop
	
	def svg(self, config):
		x = self.x(config)
		y = self.y(config)
		size = config.city_same_size
		if size == 0:
			size = self.pop * config.pop
		s =  '  <circle cx="{0}" cy="{1}" r="{2}" stroke-width="3" style="stroke:#000000; fill:#ffffff;"/>\n'
		s += '  <text x="{0}" y="{3}" style="text-anchor: middle; font-family: helvetica; font-size: 8pt;">{4}</text>'
		return s.format(x, y, size, y+size+12, self.name)


class Road:

	def __init__(self, segments, name=''):
		self.segments = segments
		self.name = name

	def svg(self, config):
		sz = 5
		path = ['M{} {}'.format(self.segments[0].x(config), self.segments[0].y(config))]
		for segment in self.segments[1:]:
			x, y = segment.x(config), segment.y(config)
			path.append('L{} {}'.format(x, y))
			a = 5

		return '  <path d="' + ' '.join(path) + '" />'


def output(cities, roads, config):
	print('<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">')
	for road in roads:
		print(road.svg(config))
	for city in cities:
		print(city.svg(config))
	print('</svg>')
