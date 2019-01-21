LIBSDIRS="-Lglew-2.1.0/lib/"
LIBS="-lglfw3 -ldl -lX11 -lpthread -lXxf86vm -lXrandr  -lXinerama -lXi -lXcursor -lrt -lm -lGLEW -lGL"
ONAME="-o gltest"
CFILES="main.c polygon.c"

gcc $CFILES $LIBSDIRS $LIBS $ONAME