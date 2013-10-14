package wm

type MapConfig struct {
	Seed         int64
	PointDensity float64
}

func LoadMapConfig() *MapConfig {
	return &MapConfig{
		Seed:         1,
		PointDensity: 0.05,
	}
}

// vim: ts=4:sw=4:sts=4:noexpandtab
