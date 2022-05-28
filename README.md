<img align="center" src="https://media.giphy.com/media/3orifdwhYHTto6JSec/giphy.gif" width="300" alt="algorithm"/>

# N-Puzzle
 Implementation of A* search algorithm to solve N-puzzle (taquin, пятнашки)

<details>
<summary> General rules </summary>

- game starts with a square board made up of N*N cells in random order;  
- every cell contains unique number from 1 to N^2 - 1 and one is empty;  
- algorithm has to find a valid sequence of moves to reach the final state, a.k.a the "snail solution"
- only move one can do in the N-puzzle is to swap the empty cell with one of its
  neighbors
```
3-PUZZLE :                                                          'SNAIL SOLUTION'
                                                                        ⤴
╔═════╦═════╦═════╗                                 ╔═════╦═════╦═════╗
║  3  ║  5  ║  1  ║                                 ║  1  ║  2  ║  3  ║
╠═════╬═════╬═════╣                                 ╠═════╬═════╬═════╣
║  4  ║     ║  8  ║ ──≻ some sequence of moves ──≻  ║  8  ║     ║  4  ║
╠═════╬═════╬═════╣               ...               ╠═════╬═════╬═════╣
║  7  ║  2  ║  6  ║                                 ║  7  ║  6  ║  5  ║
╚═════╩═════╩═════╝                                 ╚═════╩═════╩═════╝
                   ⤵                                                  ⤵
                INITIAL STATE                                       GOAL STATE
```
</details>




