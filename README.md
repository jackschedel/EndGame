<h1 align="center"><b>EndGame</b></h1>

<h4 align="center"><b>Deterministic Chess Engine for Checkmate Puzzles</b></h4>

<p align="center">
<a href="https://github.com/jackschedel/EndGame/blob/main/LICENSE" target="_blank">
<img src="https://img.shields.io/github/license/jackschedel/EndGame?style=flat-square" alt="licence" />
</a>
<a href="https://github.com/jackschedel/EndGame/issues" target="_blank">
<img src="https://img.shields.io/github/issues/jackschedel/EndGame?style=flat-square" alt="issues"/>
</a>
<a href="https://github.com/jackschedel/EndGame/pulls" target="_blank">
<img src="https://img.shields.io/github/issues-pr/jackschedel/EndGame?style=flat-square" alt="pull-requests"/>
</a>

## 🌐 Overview

EndGame is a deterministic chess engine written in C++ that aims to find guaranteed checkmate lines in chess puzzles. It focuses on solving two and three move checkmate puzzles due to RAM limitations for the decision tree.

<p align="center">
<a href="https://youtu.be/Iw1JJTNcNFo" target="_blank">
<b>Video Demo:</b>
</a>
</p>
<p align="center">
<a href="https://youtu.be/Iw1JJTNcNFo" target="_blank">
<img width="50%" src="https://img.youtube.com/vi/Iw1JJTNcNFo/maxresdefault.jpg" alt="issues"/>
</a>
</p>



## ⚙️ Features

- **Deterministic Algorithm:** EndGame uses a deterministic approach to solve chess puzzles, ensuring a correct answer for each problem.
- **Large Database of Test Cases:** With a database of 550,000 puzzles, including 300,000 two-move puzzles, EndGame has a wide range of test cases to work with.
- **FEN Notation Parsing:** EndGame parses standardized chess FEN notation to generate the board state for each puzzle.
- **Legal Move Generation:** The engine generates a vector of legal moves, starting with a list of pseudo-legal moves and then filtering out those that would result in a self-check.
- **n-ary Tree of Board States:** EndGame utilizes an n-ary tree to map all possible move combinations and board states, allowing for efficient exploration of the decision tree.
- **Backward Pathfinding:** The algorithm goes backward through the decision tree to identify the guaranteed checkmate path and presents the solution.

## 💡 About

EndGame starts by selecting a random mate-in-two puzzle from the test case file. It then parses the FEN string and generates the board, using lowercase letters for black pieces and uppercase letters for white pieces.

Once the board is set up, the engine generates a vector of legal moves by first creating a list of pseudo-legal moves without considering self-checks. The engine then filters out any moves that would result in a self-check.

To explore all possible move combinations, EndGame creates an n-ary tree of board states. The algorithm then traverses the decision tree in reverse to find the guaranteed checkmate path. Finally, the program prints out the correct solution path for the given puzzle.
