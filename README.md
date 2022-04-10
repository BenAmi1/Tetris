# Tetris-Game
# The Good old-fashioned Tetris game. 
# Play vs friend, vs the computer, or just watch 2 computers playing against each other :)
# Several difficulty levels
# Code -- Bullets:
* C++
* AI mode - human vs computer / computer vs computer: A Function which calculates where is the ideal spot to put the current brick, 
considering the shape of the given brick and the given congestion of the board.
The function programmed to search for the best position by a certain priority: The computer will first try to delete as many rows as possible,
then delete a row, then fit to the board (by not creating empty "holes"), 
and finally - go as deep as possible into the board. If one of the above is not possible / not effective, the computer will go for a random move.

![Preview](https://user-images.githubusercontent.com/75504717/162624566-c7011e31-8f54-4baf-b245-2453fc446efa.gif)
