.PHONY: build assync static test coverage linter

build:
	sudo apt install libgtest-dev
	sudo apt install lcov
	mkdir build
	cd build && cmake .. && cmake --build .

assync:
	@mkdir build
	@cd build && cmake .. -DASYNC=ON > cmakelog.txt && make > makelog.txt && ./dz2
	@rm -r build
	
static:
	@mkdir build
	@cd build && cmake .. -DASYNC=OFF > cmakelog.txt && make > makelog.txt && ./dz2
	@rm -r build

test:
	@echo "STATIC LIBRARY"
	@mkdir build
	@mkdir log
	@cd build && cmake .. -DASYNC=OFF -DTEST=ON > ../log/cmakelog_static.txt && make > ../log/makelog_static.txt && ./tests/dz2_test > ../log/test_log_static.txt 
	@echo "ASYNC LIBRARY"
	@cd build && cmake .. -DASYNC=ON -DTEST=ON > ../log/cmakelog_assync.txt && make > ../log/makelog_assync.txt && ./tests/dz2_test > ../log/test_log_assync.txt 
	@rm -r build

coverage:
	@mkdir build
	@mkdir log
	@echo "STATIC LIBRARY"
	@cd build && cmake .. -DASYNC=OFF -DTEST=ON > ../log/cmakelog_static.txt && make > ../log/makelog_static.txt && ./tests/dz2_test 
	@cd build && lcov -t "tests/test_dz2" -o coverage.info -c -d dz2s/ && genhtml -o report coverage.info > ../log/static_cov.txt
	@echo "ASYNC LIBRARY"
	@cd build && cmake .. -DASYNC=ON -DTEST=ON > ../log/cmakelog_static.txt && make > ../log/makelog_static.txt && ./tests/dz2_test
	@cd build && lcov -t "tests/test_dz2" -o coverage.info -c -d dz2d/ && genhtml -o report coverage.info > ../log/async_cov.txt
	@rm -r build

linter:
	@cppcheck main.c
	@cppcheck dz2s/dz2_lib.c
	@cppcheck dz2d/dz2_lib.c