
build:
	cmake -B build -G Ninja
	cd build && ninja -j 8

format:
	clang-format --style=file -i include/*.h include/frame/*.h src/*.cpp test/*.cpp

clean:
	rm -rf build

commit ?= test

push:
	@git add .
	@git commit -m "$(commit)"
	@git push
	@sync #sync all files in os
