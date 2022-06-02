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
		virtual std::vector<Move>	solve(Puzzle*) = 0;
		virtual ~SearchAlgorithm()= default;

		virtual bool				is_solvable(Puzzle* puzzle, Puzzle* solution) {

			int i_puzzle = count_inversions(puzzle->get_sequence());
			int i_goal = count_inversions(solution->get_sequence());

			if (puzzle->getSize() % 2) {
				return i_goal % 2 == i_puzzle % 2;
			} else {
				return i_goal % 2 == (i_puzzle + puzzle->get_space().first + solution->get_space().first) % 2;
			}
		}
};

class InformSearchAlgorithm : public  SearchAlgorithm {

	typedef float ( *HeuristicsFunc )( Puzzle*, std::map<int, int> );
	HeuristicsFunc	heuristics;
	public:
		virtual void    select_heuristics(HeuristicsFunc func) {
			this->heuristics = func;
		}
		virtual float 	priority(Puzzle* puzzle, std::map<int, int> const& goal_state) {
			return (float)puzzle->get_cost() + heuristics(puzzle, goal_state);
		}
};

class UniformSearchAlgorithm : public  SearchAlgorithm {
};


class AStar : public InformSearchAlgorithm {

	typedef std::pair<float, Puzzle>	State;
	struct Comparator {
		constexpr bool operator()(State const& a, State const& b) const noexcept {
			return a.first > b.first;
		}
	};

	private:
		std::priority_queue< State, std::vector<State>, Comparator >		open_set;
		std::map< std::vector<int>, float >                                   	closed_set;

	public:

		std::vector<Move>    solve(Puzzle* puzzle) override {

			Puzzle	current, next;
			bool 	success = false;
			Puzzle	solution(puzzle->getSize(), snailSolution(puzzle->getSize()));
			std::map<int, int>	goal_state = get_goal_map(solution.get_sequence());

			if (!is_solvable(puzzle, &solution)) {
				std::cout << "NOT SOLVABLE :(\n";
				return std::vector<Move> {};
			}
			open_set.push(std::make_pair(priority(puzzle, goal_state), *puzzle));
			while (!open_set.empty() && !success) {
				current = open_set.top().second;
//				std::cout << open_set.top().first - current.get_moves().size() << "   ";
				if (current.get_sequence() == solution.get_sequence()) {
					success = true;
				} else {
					closed_set.insert(std::make_pair(current.get_sequence(), open_set.top().first));
//					std::cout << open_set.top().first - open_set.top().second.get_cost() << "\n";
					open_set.pop();
					for (int dir = up; dir != none; ++dir) {
						next = current;
						if (!next.try_move((Move)dir))
							continue;
						if (next.get_sequence() == solution.get_sequence()) {
							success = true;
							break;
						} else {
							//					float h = closed_set[state.get_sequence()] + heuristics(&child, reference);
							float h = priority(&next, goal_state);
							if (closed_set.count(next.get_sequence()) && closed_set.at(next.get_sequence()) < h)
								continue;
							else {
								open_set.push(std::make_pair(h, next));
							}
						}
					}
				}
			}
			std::cout << "SOLVED\n";
			return next.get_moves();
		}
};

class DepthFirstSearch : public UniformSearchAlgorithm {

	private:
		std::queue<Puzzle>	stack;
		std::set<std::vector<int>>	visited;

	public:
		std::vector<Move>     solve(Puzzle* puzzle) override {

			Puzzle	solution(puzzle->getSize(), snailSolution(puzzle->getSize()));
			Puzzle current, next;

			if (!is_solvable(puzzle, &solution)) {
				std::cout << "NOT SOLVABLE :(\n";
				return std::vector<Move> {};
			} else {
				stack.push(*puzzle);
				while (!stack.empty()) {
					current = stack.front();
					visited.insert(current.get_sequence());
					stack.pop();
					if (current.get_sequence() == solution.get_sequence())
						break;
					for (int dir = up; dir != none; ++dir) {
						next = current;
						if (!next.try_move((Move)dir))
							continue;
						if (!visited.count(next.get_sequence()))
							stack.push(next);
					}
				}
			}
			current.print();
			std::cout << "SOLVED\n";
			return current.get_moves();
		}
};