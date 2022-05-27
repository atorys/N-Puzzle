//
// Created by Achiote Tory on 5/27/22.
//

#include "Board.hpp"
#include "utility/utility.hpp"

int main(int ac, char **av) {

    if (ac > 1) {
        std::pair<int, std::vector<int>> args;
        if ((args = getBoard(av[1])).second.empty()) {
            exit(EXIT_FAILURE);
        }
        Board   game(args.first, args.second);
        game.print();
    }

    return 0;
}
