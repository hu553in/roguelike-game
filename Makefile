all: clean reload lint build exec

mkdir_build:
	[ -d ./cmake-build-debug ] | mkdir -p cmake-build-debug

build:
	cd cmake-build-debug;make

exec:
	./cmake-build-debug/roguelike-game

clean:
	rm -rf cmake-build-debug

reset_leaderboard:
	cd resources;rm leaderboard.txt;touch leaderboard.txt

reload: mkdir_build
	cd cmake-build-debug;cmake ..

fast_build:
	cd cmake-build-debug;make

run: fast_build exec

lint:
	cd cmake-build-debug;make lint

debug: fast_build debug_server

debug_server:
	gdbserver :1234 ./cmake-build-debug/roguelike-game

reformat:
	find src/ -iname *.h -o -iname* .cpp | xargs clang-format -i --style=file