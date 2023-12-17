exec = a.out
sources = $(wildcard src/*.c)
objects = $(patsubst src/%.c,obj/%.o,$(sources))
flags = -g -Wall -lm -ldl -fPIC -rdynamic

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

obj/%.o: src/%.c include/%.h
	mkdir -p obj
	gcc -c $(flags) $< -o $@

# Add a pattern rule to build .o files without specific dependencies
obj/%.o: src/%.c
	mkdir -p obj
	gcc -c $(flags) $< -o $@

clean:
	-rm -f $(exec)
	-rm -rf obj
	-rm -f *.a

lint:
	clang-tidy src/*.c src/include/*.h

lint-fix:
	clang-tidy -fix src/*.c src/include/*.h

format:
	clang-format src/*.c src/include/*.h
