ENV := CC=/usr/bin/clang CXX=/usr/bin/clang++

build:
	$(ENV) cmake -B build
	cd build && make -j$(nproc)

clean:
	rm -rf build

commit ?= test

push:
	@git add .
	@git commit -m "$(commit)"
	@git push
	@sync #sync all files in os
