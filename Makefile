run:
	make MA
	./build/CppGame

CM:
	cmake -S . -B build

MA:
	make -C ./build

clean:
	rm -rf build/*
