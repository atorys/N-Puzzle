#  [<img src="https://img.shields.io/badge/en%20-6fa8dc?style=for-the-badge">](#about) [<img src="https://img.shields.io/badge/ru%20-lightgrey?style=for-the-badge">](#о-проекте)  N-Puzzle  
 Implementation of A* search algorithm to solve N-puzzle for learning about graph-based search algorithms
 ([_пятнашки_](https://ru.wikipedia.org/wiki/%D0%98%D0%B3%D1%80%D0%B0_%D0%B2_15),
 [_15-Puzzle_](https://en.wikipedia.org/w/index.php?title=15_puzzle&oldid=1086625326), taquin)  

 <img align="center" src="https://media.giphy.com/media/l2Je6sbvJEn1W9OWQ/giphy.gif" width="300" alt="algorithm"/>

## О Проекте

<details>
<summary> Основные правила </summary>

- головоломка состоит из квадратного поля N*N элементов;
- каждая ячейка содержит уникальное число от 1 до N^2 - 1 в рандомном порядке,
  одна из ячеек остается пустой;
- реализуемый алгоритм находит кратчайшую последовательность движений пустого блока,
  которая преобразует поле головоломки в конечный вид "snail solution";  
- за один ход можно менять местами пустой блок с соседними ячейками;  
  <img src="https://user-images.githubusercontent.com/83991209/171353109-3b08e489-011d-4119-881f-98715337fa70.png"  width="300" >
</details>

## Задачи :
 
1. <details> 
    <summary> Проверить, что головоломка имеет решение.    
    </summary>  
 
    Существуют такие начальные поля, из которых невозможно получить нужное решение, играя по правилам.

    Поле пазла можно представить в виде множества чисел `3, 5, 6, 7, 2, 4, 1, 8`, каждое перемещение пустой ячейки в пазле 
    образует новую перестановку из этих же чисел, существование решения головоломки будет зависеть от количества **инверсий** 
    в начальной и конечной перестановке пазла. [**больше про перестановки**](https://www.mccme.ru/shen/permutations.pdf)    
   
    > **Инверсия**: пара чисел **(a,b)** называется инверсией перестановки, если нарушен естественный порядок элементов, 
    где **a** находится левее, чем **b**, при этом **a > b**. В перестановке (1, 2, 4, 5, 3) ровно одна инверсия элементов (4, 3)
 
    <img src="https://user-images.githubusercontent.com/83991209/171353226-45e40d77-8e21-4210-8129-267d5ffac829.png" width="350">   
 
   ### Решение есть если:   
   - N - **нечетное** и количество инверсий в начальном и конечном состоянии имеет **одинаковую** четность;
   - N - **четное**, тогда сумма количества инверсий с номером строки, в которой находится пустая ячейка, должна иметь
   ту же четность, что и сумма количества инверсий в конечном состоянии с новым номером строки пустой ячейки;
   - в остальных случаях решения не существует.
 
     <img src="https://user-images.githubusercontent.com/83991209/171355664-4b7113e1-90b2-4f16-aba8-d18ca4671ebb.png"  width="550">

     <div align="right"><img src="https://media.giphy.com/media/xT5LMINTLCSOGdIyEo/giphy.gif" width="300" align="right"></div>
     </details>


3. <details> <summary> </summary>
   </details>
   
4. <details> <summary>  </summary>
   </details>

## About
<details>
<summary> General rules </summary>

- game starts with a square board made up of N*N cells;  
- every cell contains unique number from 1 to N^2 - 1 in random order
  and one cell is empty;  
- algorithm has to find a valid sequence of moves to reach the final state, a.k.a the "snail solution";
- only tiles adjacent to the empty space may be moved into that space.
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

 > Inversion - a pair of tiles **(a,b)** form an inversion if **a** appears before **b** but **a > b**
 
Solvable cases:
- N is **odd** and **both** numbers of inversions in the initial and 
 goal states are either even or odd
  ```
    ┌───┬───┬───┐     N = 3 is odd
    │ 3 │ 5 │   │     initial state as sequence   (3, 5, 6, 7, 2, 4, 1, 8)
    ╞───╪───╪───╡     number of inversions = 13   (3,2) (3,1) (5,2) (5,4) ... (2,1) (4,1)
    │ 6 │ 7 │ 2 │                                  
    ╞───╪───╪───╡     goal state as sequence      (1, 2, 3, 8, 4, 7, 6, 5)                       
    │ 4 │ 1 │ 8 │     number of inversions = 7    (8,4) (8,7) (8,6) (8,5) (7,6) (7,5) (6,5)
    └───┴───┴───┘
                      numbers of inversions are even
    ```
- N is **even**, then the sum of inversions number with the row of empty cell must have different partities than 
 the sum of inversions number of goal state with the row of empty cell in final table
- in other cases puzzle is not solvable


https://dreamgryphon.itch.io/pixel-art-templates