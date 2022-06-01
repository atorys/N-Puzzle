//
// Created by Achiote Tory on 5/31/22.
//

#include "AStar.hpp"

AStar::AStar(HeuristicsFunc func): heuristics(func) {

}

void AStar::set_strategy(HeuristicsFunc func) {
    this->heuristics = func;
}

void AStar::solve(Puzzle *puzzle) {

    std::vector<int>    goal_state = snailSolution(puzzle->getSize());
    std::map<int, int>  reference;
    bool  success = false;

    for (int i = 0; i < goal_state.size(); ++i) {
        reference[goal_state[i]] = i;
    }

    open_set.push(*puzzle);
    while (!open_set.empty() && !success) {
        Puzzle state = open_set.top();
        if (state.get_state() == goal_state) {
            std::cout << "SOLVED\n";
            success = true;
        } else {
            open_set.pop();
            closed_set.insert(std::make_pair(state.get_state(), state.get_heuristics()));

            for (int i = 1; i < 5; ++i) {
                Puzzle child(state, i);
                if (child.get_state() == state.get_state())
                    continue;
                if (child.get_state() == goal_state) {
                    std::cout << "SOLVED\n";
                    success = true;
                    continue;
                } else {
                    child.set_heuristics(heuristics(&child, reference));
                    if (closed_set.find(child.get_state()) != closed_set.end() && closed_set[child.get_state()] < child.get_heuristics())
                        continue;
                    else
                        open_set.push(child);
                }
            }
        }
    }

//    std::cout << heuristics(goal_state);
}
