//
// Created by Achiote Tory on 5/27/22.
//

#include "../algorithm/SearchAlgorithm.hpp"
#include "../algorithm/Heuristics.hpp"

int main(int ac, char **av) {

	SearchAlgorithm	*algo = new AStar();
    Puzzle  *puzzle;

    if (ac > 1) {
        std::pair<int, std::vector<int>> args;
        if ((args = getPuzzle(av[1])).second.empty()) {
			std::cerr << "Wrong file\n";
            exit(EXIT_FAILURE);
        }

        puzzle = new Puzzle(args.first, args.second);

    } else {
        std::vector<int> sequence = {1, 2, 3, 8, 0, 4, 7, 6, 5};
        puzzle = new Puzzle(3, sequence);
    }

    puzzle->print();
    unsigned int start = clock();

//	((AStar*)algo)->select_heuristics(&hammingDistance);
//    start = clock();
//    algo->solve(puzzle);
//    std::cout << "time = " << (double)(clock() - start) / 1000000 << "s\n";

	delete algo;
	algo = new DepthFirstSearch();
	start = clock();
	algo->solve(puzzle);
	std::cout << "time = " << (double)(clock() - start) / 1000000 << "s\n";

    delete puzzle;
	delete algo;
    return 0;
}
