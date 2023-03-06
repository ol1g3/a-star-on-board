# a-star-on-board


The code calculates a minimim distance between 2 dots on a board $n$ x $n$ with some number of obstacles. It reads 2 numbers - a size of a grid and a number of obstacles from **in.txt**, calculates and outputs in **out.txt** the grid with the path and a step-by-step path.

The algorithm used in a programm called A*, has a worst-case complexity of $O(m * log(n))$. It uses the Manhattan Distance to calculate the best node to go to. 
During the algorithm we change the values of edges:

$d_{new}(x,y)$ = $d_{old}(x,y) - f(x) + f(y)$, where $f(x)$ = $d_{manhattan}(x, target)$ = $|x_{1} - x_{2}| + |y_{1} - y_{2}|$

To make the algorithm fast I used the Dijkstra Algorithm on a priority queue with modified edges. 
