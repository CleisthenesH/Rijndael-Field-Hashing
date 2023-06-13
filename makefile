# Copyright 2023 Kieran W Harvie. All rights reserved.
.PHONY: clean

field_operations: examples/field_operations.c src/field_operations.o
	gcc examples/field_operations.c -o field_operations src/field_operations.o -Isrc

src/%.o:src/%.c src/%.h
	gcc -c $< -o $@ -Isrc  

clean:
	rm src/*.o
	find . -maxdepth 1 -type f -executable | xargs rm
