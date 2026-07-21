build:
	mkdir -p build

final:
	mkdir -p final

descript_consts.h: descript_consts.py
	python3 descript_consts.py > descript_consts.h

build/core_game_logic.o: build core_game_logic.cpp enums.h core_game_structs.hpp descript_decls.h descript_consts.h Textarr.hpp core_game_logic.hpp
	g++ -c core_game_logic.cpp -o build/core_game_logic.o -Os -flto -Wall -Werror -fmerge-all-constants -DNDEBUG

build/cli\ mode.o: build cli\ mode.cpp enums.h core_game_structs.hpp descript_decls.h Textarr.hpp core_game_logic.hpp
	g++ -c cli\ mode.cpp -o build/cli\ mode.o -Os -flto -Wall -Werror -fmerge-all-constants -DNDEBUG

final/cli\ text\ game: final build/core_game_logic.o build/cli\ mode.o
	g++ build/core_game_logic.o build/cli\ mode.o -o final/cli\ text\ game -Os -flto -Wall -Werror -fmerge-all-constants -DNDEBUG

build/core_game_logic\ \(debug\).o: build core_game_logic.cpp enums.h core_game_structs.hpp descript_decls.h descript_consts.h Textarr.hpp core_game_logic.hpp
	g++ -c core_game_logic.cpp -o build/core_game_logic\ \(debug\).o -Os -flto -Wall -fmerge-all-constants -g

build/cli\ mode\ \(debug\).o: build cli\ mode.cpp enums.h core_game_structs.hpp descript_decls.h Textarr.hpp core_game_logic.hpp
	g++ -c cli\ mode.cpp -o build/cli\ mode\ \(debug\).o -Os -flto -Wall -fmerge-all-constants -g

final/cli\ text\ game.debug: final build/core_game_logic\ \(debug\).o build/cli\ mode\ \(debug\).o
	g++ build/core_game_logic\ \(debug\).o build/cli\ mode\ \(debug\).o -o final/cli\ text\ game.debug -Os -flto -Wall -fmerge-all-constants -g

clean: build final
	rm -f build/*
	rm -d build

full_clean: build final
	rm -f build/* final/*
	rm -d build final

.PHONY: all clean full_clean test