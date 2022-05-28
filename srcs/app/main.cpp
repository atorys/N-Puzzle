//
// Created by Achiote Tory on 5/27/22.
//

#include "../models/Game.hpp"
#include "../utility/utility.hpp"

int main(int ac, char **av) {
	Game	solver;

    if (ac > 1) {
        std::pair<int, std::vector<int>> args;
        if ((args = getPuzzle(av[1])).second.empty()) {
			std::cerr << "Wrong file\n";
            exit(EXIT_FAILURE);
        }
		solver.setPuzzle(new Puzzle(args.first, args.second));
		solver.getPuzzle()->print();
		solver.getPuzzle()->print(solver.getPuzzle()->getGoalState());
    }

    return 0;
}
