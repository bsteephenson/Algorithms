
all: rank rb lcs interval bfs dij

rank: randomized_rank_selection.c
	clang -o randomized_rank_selection randomized_rank_selection.c

rb: red_black.cpp
	clang++ -g -o red_black red_black.cpp

lcs: longest_common_subsequence.cpp
	clang++ -g -o longest_common_subsequence longest_common_subsequence.cpp


interval: interval_tree.cpp
	clang++ -g -o interval_tree interval_tree.cpp

bfs: bfs.cpp
	clang++ -g -o bfs bfs.cpp

dij: dijkstra.cpp
	clang++ -g -Wno-c++11-extensions -o dijkstra dijkstra.cpp