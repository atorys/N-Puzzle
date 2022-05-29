[//]: # (<img align="center" src="https://media.giphy.com/media/3orifdwhYHTto6JSec/giphy.gif" width="300" alt="algorithm"/>)

# N-Puzzle
 Implementation of A* search algorithm to solve N-puzzle  
 ([_пятнашки_](https://ru.wikipedia.org/wiki/%D0%98%D0%B3%D1%80%D0%B0_%D0%B2_15),
 [_15-Puzzle_](https://en.wikipedia.org/w/index.php?title=15_puzzle&oldid=1086625326), taquin)  
#### Сontents :
- [<img src="data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSI0Mi41NCIgaGVpZ2h0PSIzNSIgdmlld0JveD0iMCAwIDQyLjU0IDM1Ij48cmVjdCBjbGFzcz0ic3ZnX19yZWN0IiB4PSIwIiB5PSIwIiB3aWR0aD0iNDIuNTQiIGhlaWdodD0iMzUiIGZpbGw9IiM4OEM3RDQiLz48cmVjdCBjbGFzcz0ic3ZnX19yZWN0IiB4PSI0Mi41NCIgeT0iMCIgd2lkdGg9IjAiIGhlaWdodD0iMzUiIGZpbGw9IiMzODlBRDUiLz48cGF0aCBjbGFzcz0ic3ZnX190ZXh0IiBkPSJNMTkuODAgMjJMMTQuMjIgMjJMMTQuMjIgMTMuNDdMMTkuNzUgMTMuNDdMMTkuNzUgMTQuNjZMMTUuNzAgMTQuNjZMMTUuNzAgMTcuMDJMMTkuMjAgMTcuMDJMMTkuMjAgMTguMTlMMTUuNzAgMTguMTlMMTUuNzAgMjAuODJMMTkuODAgMjAuODJMMTkuODAgMjJaTTI1LjQ3IDIyTDIzLjk5IDIyTDIzLjk5IDEzLjQ3TDI1LjQ3IDEzLjQ3TDI5LjI5IDE5LjU0TDI5LjI5IDEzLjQ3TDMwLjc2IDEzLjQ3TDMwLjc2IDIyTDI5LjI4IDIyTDI1LjQ3IDE1Ljk1TDI1LjQ3IDIyWiIgZmlsbD0iI0ZGRkZGRiIvPjxwYXRoIGNsYXNzPSJzdmdfX3RleHQiIGQ9IiIgZmlsbD0iI0ZGRkZGRiIgeD0iNTUuNTQiLz48L3N2Zz4=">](#about)
- [<img src="data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSI0Mi43MSIgaGVpZ2h0PSIzNSIgdmlld0JveD0iMCAwIDQyLjcxIDM1Ij48cmVjdCBjbGFzcz0ic3ZnX19yZWN0IiB4PSIwIiB5PSIwIiB3aWR0aD0iNDIuNzEiIGhlaWdodD0iMzUiIGZpbGw9IiNBN0JGQzEiLz48cmVjdCBjbGFzcz0ic3ZnX19yZWN0IiB4PSI0Mi43MSIgeT0iMCIgd2lkdGg9IjAiIGhlaWdodD0iMzUiIGZpbGw9IiMzODlBRDUiLz48cGF0aCBjbGFzcz0ic3ZnX190ZXh0IiBkPSJNMTUuNzAgMjJMMTQuMjIgMjJMMTQuMjIgMTMuNDdMMTcuMjIgMTMuNDdRMTguNjkgMTMuNDcgMTkuNTAgMTQuMTNRMjAuMzAgMTQuNzkgMjAuMzAgMTYuMDVMMjAuMzAgMTYuMDVRMjAuMzAgMTYuOTAgMTkuODkgMTcuNDhRMTkuNDcgMTguMDYgMTguNzMgMTguMzdMMTguNzMgMTguMzdMMjAuNjUgMjEuOTJMMjAuNjUgMjJMMTkuMDYgMjJMMTcuMzUgMTguNzFMMTUuNzAgMTguNzFMMTUuNzAgMjJaTTE1LjcwIDE0LjY2TDE1LjcwIDE3LjUyTDE3LjIyIDE3LjUyUTE3Ljk3IDE3LjUyIDE4LjM5IDE3LjE1UTE4LjgyIDE2Ljc3IDE4LjgyIDE2LjExTDE4LjgyIDE2LjExUTE4LjgyIDE1LjQzIDE4LjQzIDE1LjA1UTE4LjA0IDE0LjY4IDE3LjI2IDE0LjY2TDE3LjI2IDE0LjY2TDE1LjcwIDE0LjY2Wk0yNC41NiAxOS4xNkwyNC41NiAxOS4xNkwyNC41NiAxMy40N0wyNi4wNCAxMy40N0wyNi4wNCAxOS4xOFEyNi4wNCAyMC4wMyAyNi40NyAyMC40OFEyNi45MCAyMC45MyAyNy43NSAyMC45M0wyNy43NSAyMC45M1EyOS40NiAyMC45MyAyOS40NiAxOS4xM0wyOS40NiAxOS4xM0wyOS40NiAxMy40N0wzMC45MyAxMy40N0wzMC45MyAxOS4xN1EzMC45MyAyMC41MyAzMC4wNiAyMS4zMlEyOS4xOSAyMi4xMiAyNy43NSAyMi4xMkwyNy43NSAyMi4xMlEyNi4yOCAyMi4xMiAyNS40MiAyMS4zM1EyNC41NiAyMC41NSAyNC41NiAxOS4xNloiIGZpbGw9IiNGRkZGRkYiLz48cGF0aCBjbGFzcz0ic3ZnX190ZXh0IiBkPSIiIGZpbGw9IiNGRkZGRkYiIHg9IjU1LjcxIi8+PC9zdmc+">](#about-ru) 
- [[![forthebadge](data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSI0Mi41NCIgaGVpZ2h0PSIzNSIgdmlld0JveD0iMCAwIDQyLjU0IDM1Ij48cmVjdCBjbGFzcz0ic3ZnX19yZWN0IiB4PSIwIiB5PSIwIiB3aWR0aD0iNDIuNTQiIGhlaWdodD0iMzUiIGZpbGw9IiM4OEM3RDQiLz48cmVjdCBjbGFzcz0ic3ZnX19yZWN0IiB4PSI0Mi41NCIgeT0iMCIgd2lkdGg9IjAiIGhlaWdodD0iMzUiIGZpbGw9IiMzODlBRDUiLz48cGF0aCBjbGFzcz0ic3ZnX190ZXh0IiBkPSJNMTkuODAgMjJMMTQuMjIgMjJMMTQuMjIgMTMuNDdMMTkuNzUgMTMuNDdMMTkuNzUgMTQuNjZMMTUuNzAgMTQuNjZMMTUuNzAgMTcuMDJMMTkuMjAgMTcuMDJMMTkuMjAgMTguMTlMMTUuNzAgMTguMTlMMTUuNzAgMjAuODJMMTkuODAgMjAuODJMMTkuODAgMjJaTTI1LjQ3IDIyTDIzLjk5IDIyTDIzLjk5IDEzLjQ3TDI1LjQ3IDEzLjQ3TDI5LjI5IDE5LjU0TDI5LjI5IDEzLjQ3TDMwLjc2IDEzLjQ3TDMwLjc2IDIyTDI5LjI4IDIyTDI1LjQ3IDE1Ljk1TDI1LjQ3IDIyWiIgZmlsbD0iI0ZGRkZGRiIvPjxwYXRoIGNsYXNzPSJzdmdfX3RleHQiIGQ9IiIgZmlsbD0iI0ZGRkZGRiIgeD0iNTUuNTQiLz48L3N2Zz4=)](https://forthebadge.com)](#contents)

___
## About
<details>
<summary> General rules </summary>

- game starts with a square board made up of N*N cells;  
- every cell contains unique number from 1 to N^2 - 1 in random order
  and one cell is empty;  
- algorithm has to find a valid sequence of moves to reach the final state, a.k.a the "snail solution";
- only move one can do in the N-puzzle is to swap the empty cell with one of its
  neighbors
```
    3-PUZZLE :  
   ───────────                                                     'SNAIL SOLUTION'
                                                                        ⤴   
            ┌───┬───┬───┐                                 ┌───┬───┬───┐
            │ 3 │ 5 │   │                                 │ 1 │ 2 │ 3 │
            ╞───╪───╪───╡                                 ╞───╪───╪───╡
            │ 6 │ 7 │ 2 │ ──≻ some sequence of moves ──≻  │ 8 │   │ 4 │
            ╞───╪───╪───╡               ...               ╞───╪───╪───╡
            │ 4 │ 1 │ 8 │                                 │ 7 │ 6 │ 5 │
            └───┴───┴───┘                                 └───┴───┴───┘
                         ⤵                                            ⤵
                        INITIAL STATE                                 GOAL STATE
```
</details>




## Program algorithm :
<details>
<summary> 1. Check that puzzle is solvable </summary>


Solvable cases :  
- N is `odd` and **both** numbers of inversions in initial the initial and goal states are either even or odd
  - > Inversion - a pair of tiles **(a,b)** form an inversion if **a** appears before **b** but **a > b**
  - ```
    ┌───┬───┬───┐     N = 3 is odd
    │ 3 │ 5 │   │     initial state as sequence   (3, 5, 6, 7, 2, 4, 1, 8)
    ╞───╪───╪───╡     number of inversions = 13   (3,2) (3,1) (5,2) (5,4) (5,1) (6,2) (6,4) (6,1) (7,2) (7,4) (7,1) (2,1) (4,1)
    │ 6 │ 7 │ 2 │                                  
    ╞───╪───╪───╡     goal state as sequence      (1, 2, 3, 8, 4, 7, 6, 5)                       
    │ 4 │ 1 │ 8 │     number of inversions = 7    (8,4) (8,7) (8,6) (8,5) (7,6) (7,5) (6,5)
    └───┴───┴───┘
                      numbers of inversions are even
    ```
- N is `even` and 

</details>

<details>
<summary> 2. bla </summary>
</details>
<details>
<summary> 3. bla </summary>
</details>


___
## About Ru

<details>
<summary> Основные правила </summary>

- головоломка состоит из квадратного поля N*N элементов;
- каждая ячейка содержит уникальное число от 1 до N^2 - 1 в рандомном порядке,
  одна из ячеек остается пустой;
- реализуемый алгоритм должен найти кратчайшую последовательность движений пустого блока,
  которая преобразует поле головоломки в конечный вид "snail solution";
- за один ход можно менять местами пустой блок с соседними ячейками;

```
    3-PUZZLE :  
   ───────────                                                              'SNAIL SOLUTION'
                                                                                ⤴   
            ┌───┬───┬───┐                                           ┌───┬───┬───┐
            │ 3 │ 5 │   │                                           │ 1 │ 2 │ 3 │
            ╞───╪───╪───╡                                           ╞───╪───╪───╡
            │ 6 │ 7 │ 2 │   ──≻ последовательность перемещений ──≻  │ 8 │   │ 4 │
            ╞───╪───╪───╡             пустой ячейки                 ╞───╪───╪───╡
            │ 4 │ 1 │ 8 │                                           │ 7 │ 6 │ 5 │
            └───┴───┴───┘                                           └───┴───┴───┘
                         ⤵                                                       ⤵
                       начальный вид                                            конечный вид
```
</details>