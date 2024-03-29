//
// Created by atory & csherill on 01.06.22.
//

#pragma once
#include "../models/Puzzle.hpp"
#include "../utility/utility.hpp"
#include <queue>
#include <set>
#include <utility>

/**
 * Abstract class Search Algorithm
 */
class   SearchAlgorithm {
  public:
    using   Solution = std::tuple < /* timing */ double,
                                    /* total checked states*/ long,
                                    /* list of moves*/ std::vector<Move>>;

    virtual Solution    solve(Puzzle const&) = 0;
    virtual ~SearchAlgorithm() = default;
};


/**
 * Informed Search Algorithm
 * Uses heuristics function to find high priority puzzle configurations
 */
class   AStar : public SearchAlgorithm {

  public:
    using   State = std::pair </* priority value */ float,
                               /* current sequence */ Puzzle>;
    using   Comporator = struct priorityComparator {
        bool operator()(State const &a, State const &b) const noexcept {
            return (a.first > b.first);
		}
	};

    using   ClosedSet = std::set</*puzzle sequences */ std::vector<int>>;
    using   OpenSet = std::priority_queue</*value type*/ State, std::deque<State>, Comporator>;
    using   HeuristicsFunc = float (*)(Puzzle const&, std::map<int, int> const&);

  private:
    HeuristicsFunc  heuristics;
    OpenSet         queue;
    ClosedSet       visited;

  public:

    void        select_heuristics(HeuristicsFunc func) {
        this->heuristics = func;
    }

    float       priority(Puzzle const& puzzle, std::map<int, int> const &goal_state) {
        return (float)puzzle.get_cost() / 4 + heuristics(puzzle, goal_state);
    }

    Solution    solve(Puzzle const& puzzle) override {

        Puzzle              current, next;
        std::vector<int>    goal = snailSolution(puzzle.size());
        std::map<int, int>  goal_state = get_goal_map(goal);
        bool                success = false;

		unsigned long 		start = clock();

        queue.push(std::pair{priority(puzzle, goal_state), puzzle});
        while (!queue.empty() && !success) {
            current = queue.top().second;
            queue.pop();
            visited.insert(current.get_sequence());
            if (current.get_sequence() == goal) {
                success = true;
            } else {
                for (int dir = Move::UP; dir != Move::NONE; ++dir) {
                    next = current;
                    if (!next.try_move((Move) dir)) {
                        continue;
                    } else if (next.get_sequence() == goal) {
                        success = true;
                        break;
                    } else if (!visited.count(next.get_sequence())) {
                        queue.push(std::pair{priority(next, goal_state), next});
                    }
                }
            }
        }
        return Solution {(double)(clock() - start) / 1000000, visited.size(), next.get_moves()};
    }
};


class   DepthFirstSearch : public SearchAlgorithm {

    using   ClosedSet = std::set</*puzzle sequences */ std::vector<int>>;
    using   OpenSet = std::queue<Puzzle>;

  private:
    OpenSet     stack;
    ClosedSet   visited;

  public:
    Solution solve(Puzzle const& puzzle) override {

        Puzzle              current, next;
        std::vector<int>    goal = snailSolution(puzzle.size());
		unsigned long		start = clock();

        stack.push(puzzle);
        while (!stack.empty()) {
            current = stack.front();
            stack.pop();
            visited.insert(current.get_sequence());
            if (current.get_sequence() == goal)
                break;
            for (int dir = Move::UP; dir != Move::NONE; ++dir) {
                next = current;
                if (!next.try_move((Move) dir))
                    continue;
                if (!visited.count(next.get_sequence()))
                    stack.push(next);
            }
        }

        return Solution {(double)(clock() - start) / 1000000, visited.size(), current.get_moves()};
    }
};