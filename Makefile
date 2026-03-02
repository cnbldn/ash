default:
	gcc src/ash.c -o ash

run:
	gcc src/ash.c -o ash && ./ash

debug:
	gcc src/ash.c -g -o ashdebug
