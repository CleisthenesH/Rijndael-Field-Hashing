# Copyright 2023 Kieran W Harvie. All rights reserved.
.PHONY: clean

gaussian_elimination: examples/gaussian_elimination.c src/field_operations.o src/augmented_matrix.o
	gcc examples/gaussian_elimination.c -o gaussian_elimination src/augmented_matrix.o src/field_operations.o -Isrc

field_operations: examples/field_operations.c src/field_operations.o
	gcc examples/field_operations.c -o field_operations src/field_operations.o -Isrc

src/%.o:src/%.c src/%.h
	gcc -c $< -o $@ -Isrc  

clean:
	rm src/*.o
	find . -maxdepth 1 -type f -executable | xargs rm
