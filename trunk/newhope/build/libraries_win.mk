# pthreads
CPPFLAGS += -pthread
LDFLAGS += -pthread

# GLFW+GLEW libraries
CPPFLAGS += 
LDFLAGS += -lglfw3dll -lopengl32 -lglew32.dll -lSOIL

# chipmkunk library
#CPPFLAGS += -isystem/usr/include/chipmunk
#LDFLAGS += -lchipmunk -lm
