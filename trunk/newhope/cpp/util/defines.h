#ifndef UTIL_DEFINES_H
#define UTIL_DEFINES_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);         \
	void operator=(const TypeName&)

const int TileSize = 32;

#endif
