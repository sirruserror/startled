prog=startled
out=out
src=src
FLAGS=-Wall
cc=clang

.PHONY: all clean

$(prog): $(src)/main.c
	@-mkdir out/
	$(cc) $(FLAGS) $(src)/main.c $(src)/init.c -o $(out)/$(prog)

clean:
	@rm -rf $(out)/

