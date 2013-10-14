package cart

type CartConfig struct {
	// grid options
	DrawGrid      bool
	GridPointSize float64
}

func LoadCartographerConfig() *CartConfig {
	return &CartConfig{
		DrawGrid:      true,
		GridPointSize: 2,
	}
}

// vim: ts=4:sw=4:sts=4:noexpandtab
