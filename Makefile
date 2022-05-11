# LIBS=`sdl2-config --libs`
# LIBS=`sdl2-config --static-libs`
# STATIC (/usr/local/lib/libSDL2main.a for windows might be needed)
LIBS=/usr/local/lib/libSDL2.a /usr/local/lib/libSDL2_image.a -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-weak_framework,CoreHaptics -Wl,-weak_framework,GameController -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
CPPFLAGS= -I. 

EXECUTABLES=pcx_viewer
all: $(EXECUTABLES)

pcx_viewer: pcx_viewer.o window.o
	$(CXX) -O2 $^ -o pcx_viewer $(LIBS)

clean:
	@rm -vf *.o $(EXECUTABLES)

