# pthreads
CPPFLAGS += -pthread
LDFLAGS += -pthread

# GLFW+GLEW libraries
CPPFLAGS += `pkg-config --cflags glfw3 glew`
LDFLAGS += `pkg-config --libs glfw3 glew`

# chipmkunk library
#CPPFLAGS += -isystem/usr/include/chipmunk
#LDFLAGS += -lchipmunk -lm
