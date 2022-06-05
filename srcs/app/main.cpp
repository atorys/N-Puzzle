//
// Created by Achiote Tory on 5/27/22.
//

#include <iomanip>
#include "../algorithm/SearchAlgorithm.hpp"
#include "../algorithm/Heuristics.hpp"
#include "../graphics/Visualizer.hpp"

int main(int ac, char **av) {

	if (ac == 0) {

	}

	SearchAlgorithm		*algo;
	Puzzle				*puzzle;
	unsigned int		start;

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

	std::cout << "A* searching algorithm: \n";
	algo = new AStar();
	AStar::Solution moves;
	{
		std::cout << std::left << std::setw(25) << "2. chebishev distance: ";

		((AStar *) algo)->select_heuristics(&chebDistance);
		start = clock();
		auto [solvable, move, count] = algo->solve(puzzle);
		if (!solvable) {
			std::cout << "unsolvable ;(\n";
		} else {
			double time = (double) (clock() - start) / 1000000;
			std::cout << "time = " << time << "s\t";
			std::cout << "moves = " << move.size() << "\t";
			std::cout << "total states = " << count << "\n";

			Visualizer visualizer;
			visualizer.visualize(puzzle, SearchAlgorithm::Solution{solvable, move, count}, time);
		}


		std::cout << std::left << std::setw(25) << "1. euclidean distance: ";

		((AStar *) algo)->select_heuristics(&euclideanDistance);
		start = clock();
		std::tie(solvable, move, count) = algo->solve(puzzle);
		if (!solvable) {
			std::cout << "unsolvable ;(\n";
		} else {
			std::cout << "time = " << (double) (clock() - start) / 1000000 << "s\t";
			std::cout << "moves = " << move.size() << "\t";
			std::cout << "total states = " << count << "\n";
		}


//		std::cout << std::left << std::setw(25) << "3. my distance: ";
//
//		((AStar *) algo)->select_heuristics(&myDistance);
//		start = clock();
//		algo->solve(puzzle);
//		std::cout << "time = " << (double) (clock() - start) / 1000000 << "s\t";
//		std::cout << "moves = " << moves.size() << "\n";

	}
//	delete algo;
//	algo = new DepthFirstSearch();
//	std::cout << std::endl << std::left << std::setw(25) << "DFS algorithm: ";
//	{
//		start = clock();
//		moves = algo->solve(puzzle);
//		std::cout << "time = " << (double) (clock() - start) / 1000000 << "s\t";
//		std::cout << "moves = " << moves.size() << "\n";
//
//	}

    delete puzzle;
	delete algo;
    return 0;
}
