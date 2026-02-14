default:
	gcc src/ash.c -o ash

run:
	gcc src/ash.c -o ash && ./ash
