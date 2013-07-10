#include "world/mapbuild.h"

#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#include "util/logger.h"
#include "util/polygon.h"
#include "world/biome.h"
#include "world/city.h"

MapBuild::MapBuild(const MapParameters& pars)
	: pars(pars)
{
	CreatePolygons();
	CreateCoastline();
	CreateLakes();
	CreateElevation();
	CreateRivers();
	CreateMoisture();
	CreateLava();
	CreateBiomes();
	CreateCities();
	CreateRoads();
}


MapBuild::~MapBuild()
{
	for(const auto& city: cities) {
		delete city;
	}
	for(const auto& river: rivers) {
		delete river;
	}
	for(const auto& lavapath: lava) {
		delete lavapath;
	}
	for(const auto& road: roads) {
		delete road;
	}
	for(const auto& biome: biomes) {
		delete biome;
	}
}


void
MapBuild::CreatePolygons()
{
	logger.Debug("Generating map polygons...");

	// create layout
	vector<Polygon*> polygons;
	Polygon::FakeVoronoi(pars.seed, pars.w, pars.h, 60, polygons);

	// add biomes
	for(auto it(polygons.begin()); it != polygons.end(); it++)
		biomes.push_back(new Biome(*it));
}


void
MapBuild::CreateCoastline()
{
	logger.Debug("Generating map coastline...");

	// middle square
	int qw(pars.w / 8),
	    qh(pars.h / 8);
	Point<int> pts[] { { qw*2, qh*2 }, { qw*6, qh*2 }, 
		           { qw*6, qh*6 }, { qw*2, qh*6 } };

	// disturb points
	int max_disturb(qw);
	for(int i(0); i<4; i++) {
		pts[i].x += (rand() % max_disturb) - max_disturb/2;
		pts[i].y += (rand() % max_disturb) - max_disturb/2;
	}
	
	// create coastline
	Polygon polygon(pts, 4);
	polygon.MidlineDisplacement(4);
	for(const auto& biome: biomes) {
		Point<int> p(biome->polygon->Midpoint());
		if(!polygon.PointInPolygon(p)) {
			biome->terrain = t_WATER;
		}
	}
}


void
MapBuild::CreateLakes()
{
	// add lakes
	logger.Debug("Adding lakes...");
	for(int i(0); i<rand()%2+3; i++) {
		Rect r(rand() % 3000 + 800, rand() % 3000 + 800,
				rand() % 500 + 100, rand() % 500 + 100);
		Polygon lake(r);
		lake.MidlineDisplacement(2);
		for(const auto& biome : biomes) {
			if(lake.PointInPolygon(biome->polygon->Midpoint())) {
				biome->terrain = t_WATER;
			}
		}
	}
}


void
MapBuild::CreateElevation()
{
	logger.Debug("Generating map elevation...");

	// set water elevation
	for(const auto& biome : biomes) {
		if(biome->terrain == t_WATER) {
			for(const auto& point : biome->polygon->points) {
				point.elevation = -1;
			}
			biome->elevation = -1;
		}
	}

	// set other tiles elevation
	int max_alt(0);
	for(const auto& biome : biomes) {
		if(biome->terrain != t_WATER)
		{
			int tot_alt(0);
			for(const auto& point: biome->polygon->points) {
				point.elevation = DistanceFromWater(
						point, false);
				point.elevation += rand() % 200;
				tot_alt += point.elevation;
				max_alt = max(max_alt, point.elevation);
			}
			biome->elevation = tot_alt / 
				biome->polygon->points.size();
		}
	}
	
	// normalize elevation
	for(const auto& biome : biomes) {
		if(biome->elevation != -1) {
			biome->elevation = (double)biome->elevation /
				           (double)max_alt * (double)100;
		}
	}
}


void
MapBuild::CreateRivers()
{
	logger.Debug("Generating rivers...");

	int rivers_left(pars.n_rivers);

	while(rivers_left > 0) {
		int b(rand() % biomes.size());
		if(biomes[b]->terrain != t_WATER) {
			int k(rand() % biomes[b]->polygon->points.size());
			Point<int> p(biomes[b]->polygon->points[k]);
			if(DistanceFromWater(p, false) > 600) {
				rivers.push_back(CreateFlow(p));
				--rivers_left;
			}
		}
	}
}


void 
MapBuild::CreateMoisture()
{
	logger.Debug("Generating moisture...");

	// generate moisture
	int max_moi(0);
	for(const auto& biome : biomes)
	{
		if(biome->terrain == t_WATER) {
			biome->moisture = 0;
		} else {
			int tot_moi(0);
			for(const auto& point : biome->polygon->points) {
				int moi(DistanceFromWater(point, true));
				tot_moi += moi;
				max_moi = max(max_moi, moi);
			}
			biome->moisture = tot_moi / 
				biome->polygon->points.size();
		}
	}
	
	// normalize moisture
	for(const auto& biome : biomes) {
		biome->moisture = 100 - ((double)biome->moisture /
			                 (double)max_moi * (double)100);
	}
}


void
MapBuild::CreateLava()
{
	logger.Debug("Creating lava...");

	// find highest, dryest point
	vector<const Biome*> bs;
	copy(biomes.begin(), biomes.end(), back_inserter(bs));
	sort(bs.begin(), bs.end(), 
	[](const Biome* const& b1, const Biome* const& b2) -> bool
		{
			int i1((100 - b1->elevation) + b1->moisture);
			int i2((100 - b2->elevation) + b2->moisture);
			return i1 < i2;
		});

	// draw lava path
	for(int i=0; i<3; i++) {
		auto points(bs[i]->polygon->points);
		lava.push_back(CreateFlow(points[rand() % points.size()], 4));
	}
}


void
MapBuild::CreateBiomes()
{
	/*
	 * Elev/Moist   0-30       30-60      60-100
	 *  0-30        DIRT       EARTH      GRASS
	 * 30-60        ROCK       GRASS      HOTFOREST
	 * 60-100       LAVAROCK   SNOW       COLDFOREST
	 */
	for(const auto& biome : biomes) {
		if(biome->terrain == t_WATER) {
			continue;
		}

		int alt = biome->elevation;
		int moi = biome->moisture;
		TerrainType t = t_DIRT;
		if(alt < 20) {
			t = t_DIRT;
		} else if(alt < 40) {
			if(moi < 30)
				t = t_DIRT;
			else if(moi < 60)
				t = t_EARTH;
			else
				t = t_GRASS;
		} else if(alt < 70) {
			if(moi < 30)
				t = t_ROCK;
			else if(moi < 60)
				t = t_GRASS;
			else
				t = t_HOTFOREST;
		} else {
			if(moi < 60)
				t = t_LAVAROCK;
			else if(moi < 80)
				t = t_SNOW;
			else
				t = t_COLDFOREST;
		}
		biome->terrain = t;
	}
}


void
MapBuild::CreateCities()
{
	logger.Debug("Creating cities...");

	for(int i(0); i<pars.n_cities; i++) {
try_again:
		int b(rand() % biomes.size());
		
		// check if it's not in the sea
		if(biomes[b]->terrain == t_WATER) {
			goto try_again;
		}

		// check if neighbours don't have a city already
		vector<const Biome*> neighbours;
		BiomeNeighbours(*biomes[b], neighbours);
		for(const auto& neigh: neighbours) {
			if(neigh->has_city) {
				goto try_again;
			}
		}

		// add city
		Point<int> pos(biomes[b]->polygon->Midpoint());
		cities.push_back(new City(pos, *biomes[b]));
		biomes[b]->has_city = true;
	}
}


void
MapBuild::CreateRoads()
{
	logger.Debug("Creating roads...");

	for(const auto& city: cities) {
		// find closest city
		vector<City*> cs;
		copy(cities.begin(), cities.end(), back_inserter(cs));
		sort(cs.begin(), cs.end(), 
			[&city](City* const& c1, City* const& c2) -> bool
			{ 
				int d1 = c1->pos.Distance(city->pos);
				int d2 = c2->pos.Distance(city->pos);
				return d1 < d2;
			});

		// skip cities already connected
		unsigned int n; // [0] is the city itself
		for(n=1; ; n++) {
			if(n >= cs.size()) {
				goto next;
			}
			auto conn = cs[n]->connections;
			if(find(conn.begin(), conn.end(), city) == conn.end()) {
				break;
			}
		}

		// build road
		CreateRoad(*city, *cs[n]);
		
		// add connections
		cs[n]->connections.push_back(city);
		city->connections.push_back(cs[n]);

next: ;
	}

	FindUnconnectedCities();
}


void MapBuild::FindUnconnectedCities()
{
	// find city clusters
	vector<vector<const City*> > clusters;
	for(const auto& city: cities) {
		bool found(false);
		for(const auto& cluster: clusters) {
			if(find(cluster.begin(), cluster.end(), city) !=
					cluster.end())
			{
				found = true;
				break;
			}
		}
		if(found) {
			continue;
		}

		auto cluster = vector<const City*>();
		FindCityCluster(city, cluster);
		clusters.push_back(cluster);
	}
	
	// find closest cities and build roads among them
	for(unsigned int i(0); i<clusters.size(); i++) {
		for(unsigned int j(i+1); j<clusters.size(); j++) {
			ConnectClusters(clusters[i], clusters[j]);
		}
	}
}


void 
MapBuild::FindCityCluster(const City* city, vector<const City*>& cluster)
{
	if(find(cluster.begin(), cluster.end(), city) != cluster.end()) {
		return;
	}

	cluster.push_back(city);
	for(const auto& conn: city->connections) {
		FindCityCluster(conn, cluster); // recursive
	}
}


void
MapBuild::ConnectClusters(vector<const City*> const& c1, 
		vector<const City*> const& c2)
{
	int min_dist(INT_MAX);
	pair<const City*, const City*> cities(nullptr, nullptr);
	for(unsigned int i(0); i<c1.size(); i++) {
		for(unsigned int j(i+1); j<c2.size(); j++) {
			if(c1[i] != c2[j]) {
				int dist(c1[i]->pos.Distance(c2[j]->pos));
				if(dist < min_dist) {
					min_dist = dist;
					cities = make_pair(c1[i], c2[j]);
				}
			}
		}
	}
	if(cities.first) {
		CreateRoad(*cities.first, *cities.second);
	}
}


/*
void
MapBuild::FindNations()
{
	logger.Debug("Creating nations...");

	vector<vector<const City*> > nations;
	for(const auto& city: cities)
	{
		bool found = false;
		for(const auto& nation: nations)
			if(find(nation.begin(), nation.end(), city) !=
					nation.end())
			{
				found = true;
				break;
			}
		if(found)
			continue;

		auto nation = vector<const City*>();
		FindInterconnectedCities(*city, nation);
		nations.push_back(nation);
	}
}


void 
MapBuild::FindInterconnectedCities(const City& city, 
		vector<const City*>& cs)
{
	// TODO
}
*/


void 
MapBuild::CreateRoad(const City& c1, const City& c2)
{
	if(&c1 == &c2) {
		return;
	}

	const Biome* b(&c1.biome);
	Polygon* road(new Polygon());

	// create road points
	while(b != &c2.biome) {

		road->points.push_back(b->polygon->Midpoint());

		// find neighbour biomes
		vector<const Biome*> biomes;
		BiomeNeighbours(*b, biomes);

		// find closest biome
		sort(biomes.begin(), biomes.end(), 
			[&c2](const Biome* const& b1, const Biome* const& b2) -> bool
			{ 
				int d1(b1->polygon->Midpoint().Distance(
					c2.biome.polygon->Midpoint()));
				int d2(b2->polygon->Midpoint().Distance(
					c2.biome.polygon->Midpoint()));
				if(b1->terrain == t_WATER) {
					d1 = INT_MAX;
				}
				if(b2->terrain == t_WATER) {
					d2 = INT_MAX;
				}
				return d1 < d2;
			});
		
		// next biome
		road->points.push_back(b->polygon->Midpoint());
		b = biomes[0];
	}

	// add roads
	road->points.push_back(c2.biome.polygon->Midpoint());
	road->CalculateLimits();
	roads.push_back(road);
}


Polygon*
MapBuild::CreateFlow(Point<int> start, int iterations)
{
	Polygon* poly(new Polygon());
	Point<int> p(start);
	int iter(0);

	while(p.elevation != -1 && iter < iterations) {

		poly->points.push_back(p);
		
		// find neighbours
		vector<Point<int>> neighbours;
		for(const auto& biome : biomes) {
			if(biome->polygon->ContainsPoint(p)) {
				biome->polygon->NeighbourPoints(p, neighbours);
			}
		}
		assert(neighbours.size() > 0);

		// order by elevation
		sort(neighbours.begin(), neighbours.end(), 
		[](Point<int> const& p1, Point<int> const& p2) -> bool
		{ 
			return p1.elevation < p2.elevation; 
		});

		// skip points already added
		unsigned int n(0);
		while(true) {
			p = neighbours[n];
			if(find(poly->points.begin(), poly->points.end(), p) == 
					poly->points.end()) {
				break;
			}
			if(n >= neighbours.size()) {
				return poly;
			}
			++n;
		}

		--iter;
	}
	poly->CalculateLimits();
	return poly;
}


int 
MapBuild::DistanceFromWater(Point<int> const& p, bool include_rivers)
{
	int dist = INT_MAX;

	// distance from sea
	for(const auto& biome : biomes) {
		if(biome->terrain == t_WATER) {
			int new_dist(p.Distance(biome->polygon->Midpoint()));
			if(new_dist < dist) {
				dist = new_dist;
			}
		}
	}

	// distance from a river
	if(include_rivers) {
		for(const auto& river : rivers) {
			for(const auto& point : river->points) {
				int new_dist(point.Distance(p));
				if(new_dist < dist) {
					dist = new_dist;
				}
			}
		}
	}

	assert(dist != INT_MAX);
	return dist;
}


bool 
MapBuild::AreNeighbours(const Biome& b1, const Biome& b2)
{
	vector<const Biome*> neigh;
	BiomeNeighbours(b1, neigh);
	return find(neigh.begin(), neigh.end(), &b2) != neigh.end();
}


void 
MapBuild::BiomeNeighbours(const Biome& biome, vector<const Biome*>& biomes)
{
	for(const auto& b: this->biomes) {
		if(biome.polygon->IsTouching(*b->polygon) && &biome != b) {
			biomes.push_back(b);
		}
	}
}
