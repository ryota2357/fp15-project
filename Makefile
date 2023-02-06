.DEFAULT_GOAL = build

CFILES := $(wildcard src/*.c) $(wildcard src/*/src/*.c)
HFILES := $(wildcard src/*.h) $(wildcard src/*/include/*.h)

# ffmpeg:
#   - first `-r 30` means the span of ppm file (fps)
#   - second `-r 30` means the fps of gif/mp4 file
#   - `convert` can't be specified fps, only specified millisecond (in 10ms intervals by -delay)
#   - How to create clear gif: use palette (ref. https://linuxfan.info/ffmpeg-gif-anime)
build: src/build/main
	@mkdir -p build
	@rm -f build/*.ppm build/animation.gif build/animation.mp4 build/palette.png

	@echo "Generationg PPM files..."
	@src/build/main "$(shell pwd)/build"

	@echo "Converting MP4..."
	@ffmpeg -loglevel error -r 30 -i build/%04d.ppm -pix_fmt yuv420p -r 30 build/animation.mp4

	@echo "Converting GIF..."
	@ffmpeg -loglevel error -i build/animation.mp4 -vf palettegen build/palette.png
	@ffmpeg -loglevel error -r 30 -i build/%04d.ppm -i build/palette.png -filter_complex paletteuse -r 30 build/animation.gif
.PHONY: build

src/build/main: src/build $(CFILES) $(HFILES)
	@cmake --build src/build

src/build:
	@cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S src -B src/build

clean:
	@rm -rf build
	@rm -rf src/build
.PHONY: clean
