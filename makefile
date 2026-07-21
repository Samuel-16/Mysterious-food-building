build:
	mkdir -p build

final:
	mkdir -p final

build/descript_consts.h: src/core\ game/descript_consts.py
	python3 src/core\ game/descript_consts.py > build/descript_consts.h

build/core_game_logic.o: build src/core\ game/core_game_logic.cpp src/core\ game/enums.h src/core\ game/core_game_structs.hpp src/core\ game/descript_decls.h build/descript_consts.h src/core\ game/Textarr.hpp src/core\ game/core_game_logic.hpp
	g++ -c src/core\ game/core_game_logic.cpp -o build/core_game_logic.o -Os -flto -Wall -Werror -fmerge-all-constants -DNDEBUG

build/cli\ mode.o: build src/cli\ mode.cpp src/core\ game/enums.h src/core\ game/core_game_structs.hpp src/core\ game/descript_decls.h src/core\ game/Textarr.hpp src/core\ game/core_game_logic.hpp
	g++ -c src/cli\ mode.cpp -o build/cli\ mode.o -Os -flto -Wall -Werror -fmerge-all-constants -DNDEBUG

final/cli\ text\ game: final build/core_game_logic.o build/cli\ mode.o
	g++ build/core_game_logic.o build/cli\ mode.o -o final/cli\ text\ game -Os -flto -Wall -Werror -fmerge-all-constants -DNDEBUG

build/core_game_logic\ \(debug\).o: build src/core\ game/core_game_logic.cpp src/core\ game/enums.h src/core\ game/core_game_structs.hpp src/core\ game/descript_decls.h build/descript_consts.h src/core\ game/Textarr.hpp src/core\ game/core_game_logic.hpp
	g++ -c src/core\ game/core_game_logic.cpp -o build/core_game_logic\ \(debug\).o -Os -flto -Wall -fmerge-all-constants -g

build/cli\ mode\ \(debug\).o: build src/cli\ mode.cpp src/core\ game/enums.h src/core\ game/core_game_structs.hpp src/core\ game/descript_decls.h src/core\ game/Textarr.hpp src/core\ game/core_game_logic.hpp
	g++ -c src/cli\ mode.cpp -o build/cli\ mode\ \(debug\).o -Os -flto -Wall -fmerge-all-constants -g

final/cli\ text\ game.debug: final build/core_game_logic\ \(debug\).o build/cli\ mode\ \(debug\).o
	g++ build/core_game_logic\ \(debug\).o build/cli\ mode\ \(debug\).o -o final/cli\ text\ game.debug -Os -flto -Wall -fmerge-all-constants -g

clean: build final
	rm -f build/*
	rm -d build

full_clean: build final
	rm -f build/* final/*
	rm -d build final

.PHONY: all clean full_clean test