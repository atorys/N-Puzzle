//
// Created by Achiote Tory on 5/27/22.
//

#include "../algorithm/AStar.hpp"
#include "../algorithm/Strategy.hpp"

int main(int ac, char **av) {

    AStar   algorithm(&myDistance);
    Puzzle  *puzzle;

    if (ac > 1) {
        std::pair<int, std::vector<int>> args;
        if ((args = getPuzzle(av[1])).second.empty()) {
			std::cerr << "Wrong file\n";
            exit(EXIT_FAILURE);
        }

        puzzle = new Puzzle(args.first, args.second);

    } else {
        std::vector<int> state = {1, 2, 3, 8, 0, 4, 7, 6, 5};
        puzzle = new Puzzle(3, state);
    }

    puzzle->print();
    unsigned int start = clock();
    algorithm.solve(puzzle);
    std::cout << "time = " << (double)(clock() - start) / 10000 << "ms\n";

    algorithm.set_strategy(&hammingDistance);
    start = clock();
    algorithm.solve(puzzle);
    std::cout << "time = " << (double)(clock() - start) / 10000 << "ms\n";

    delete puzzle;
    return 0;
}
