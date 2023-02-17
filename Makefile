#Copyright (C) Dragusin Daniela-Alexandra (311CA / 2021-2022) */

build:
	gcc -Wall -Wextra -std=c99 -o tema1 main.c utils.c add.c del.c show.c functions.c -lm

clean:
	-rm -f tema1
	-rm -f *~

.PHONY: pack clean