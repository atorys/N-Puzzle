//
// Created by atory on 01.06.22.
//

#pragma once
#include "../models/Puzzle.hpp"
#include "../utility/utility.hpp"
#include <queue>
#include <set>

class SearchAlgorithm {
  public:
	typedef std::tuple </*is puzzle solvable*/ bool,
	        			/*list of moves for empty block*/ std::vector<Move>,
						/*total checked states*/ long>	Solution;

	virtual Solution solve(Puzzle *) = 0;
	virtual ~SearchAlgorithm() = default;
};

class UniformSearchAlgorithm : public SearchAlgorithm {};

class InformSearchAlgorithm : public SearchAlgorithm {

	typedef float ( *HeuristicsFunc )(Puzzle *, std::map<int, int>);
	HeuristicsFunc heuristics;

  public:
	void	select_heuristics(HeuristicsFunc func)	{ this->heuristics = func; }
	float	priority(Puzzle *puzzle, std::map<int, int> const &goal_state) {
		return (float) puzzle->get_cost() / 4 + heuristics(puzzle, goal_state);
	}
};


class AStar : public InformSearchAlgorithm {

	typedef std::pair<float, Puzzle>	State;

	struct Comparator {
		constexpr bool
		operator()(State const &a, State const &b) const noexcept {
			return a.first > b.first;
		}
	};

  private:
	std::priority_queue<State, std::vector<State>, Comparator>	open_set;
	std::map<std::vector<int>, float>							closed_set;

  public:
	Solution solve(Puzzle *puzzle) override {

		Puzzle current, next;
		bool success = false;
		Puzzle solution(puzzle->get_size(),
						snailSolution(puzzle->get_size()));
		std::map<int, int> goal_state = get_goal_map(
				solution.get_sequence());

		if (!is_solvable(puzzle, &solution)) {
			return Solution {false, 0, 0};
		}

		long long step = 0;

		open_set.push(
				std::make_pair(priority(puzzle, goal_state), *puzzle));
		while (!open_set.empty() && !success) {
			current = open_set.top().second;
//				std::cout << open_set.top().first - current.get_moves().size() << "   ";
			if (current.get_sequence() == solution.get_sequence()) {
				success = true;
			} else {
				closed_set.insert(std::make_pair(current.get_sequence(),
												 open_set.top().first));
//					std::cout << open_set.top().first - open_set.top().second.get_cost() << "\n";
				open_set.pop();
				for (int dir = Move::UP; dir != Move::NONE; ++dir) {
					next = current;
					if (!next.try_move((Move) dir))
						continue;
					if (next.get_sequence() == solution.get_sequence()) {
						success = true;
						break;
					} else {
						//					float h = closed_set[state.get_sequence()] + heuristics(&child, reference);
						float h = priority(&next, goal_state);
						if (closed_set.count(next.get_sequence()) &&
							closed_set.at(next.get_sequence()) < h)
							continue;
						else {
							open_set.push(std::make_pair(h, next));
						}
					}
				}
			}
		}
//		std::cout << "SOLVED\n";
		return Solution {true, next.get_moves(), closed_set.size()};
	}
};

class DepthFirstSearch : public UniformSearchAlgorithm {

  private:
	std::queue<Puzzle> stack;
	std::set<std::vector<int>> visited;

  public:
	Solution solve(Puzzle *puzzle) override {

		Puzzle solution(puzzle->get_size(), snailSolution(puzzle->get_size()));
		Puzzle current, next;

		if (!is_solvable(puzzle, &solution)) {
			return Solution{false, 0, 0};
		}

		stack.push(*puzzle);
		while (!stack.empty()) {
			current = stack.front();
			visited.insert(current.get_sequence());
			stack.pop();
			if (current.get_sequence() == solution.get_sequence())
				break;
			for (int dir = Move::UP; dir != Move::NONE; ++dir) {
				next = current;
				if (!next.try_move((Move) dir))
					continue;
				if (!visited.count(next.get_sequence()))
					stack.push(next);
			}
		}

//		current.print();
//		std::cout << "SOLVED\n";
		return Solution {true, current.get_moves(), visited.size()};
	}
};