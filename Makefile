ENV := CC=/usr/bin/clang CXX=/usr/bin/clang++

build:
	$(ENV) cmake -B build
	cd build && make -j$(nproc)

clean:
	rm -rf build
