.PHONY: build test coverage

build:
	sudo apt install libgtest-dev
	sudo apt install libgtest-dev
	mkdir build
	cd build
	ls
	cmake .. 
	make
	
test:
	./build/tests/dz1_test

coverage:
	lcov -t "build/tests/dz1_test" -o coverage.info -c -d build/storage_device/
	genhtml -o report coverage.info
	
