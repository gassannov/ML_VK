.PHONY: build test coverage

build:
	sudo apt install libgtest-dev
	sudo apt install lcov
	mkdir build
	cmake -B ./build
	cd build
	make
	
test:
	./build/tests/dz1_test

coverage:
	lcov -t "build/tests/dz1_test" -o coverage.info -c -d build/storage_device/
	genhtml -o report coverage.info
	
