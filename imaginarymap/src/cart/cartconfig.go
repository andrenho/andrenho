package cart

type CartConfig struct {
	// grid options
	DrawGrid      bool
	GridPointSize float64
	GridLineWidth float64
}

func LoadCartographerConfig() *CartConfig {
	return &CartConfig{
		DrawGrid:      true,
		GridPointSize: 2,
		GridLineWidth: 0.4,
	}
}

// vim: ts=4:sw=4:sts=4:noexpandtab
