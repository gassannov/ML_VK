.PHONY: build test coverage

build:
	mkdir build
	cd build && cmake .. && cmake --build .
	
test:
	./build/tests/dz1_test

coverage:
	cd build && lcov -t "tests/test_roads" -o coverage.info -c -d storage_device/ && genhtml -o report coverage.info
	
