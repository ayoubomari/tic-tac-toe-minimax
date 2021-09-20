# tic-tac-toe-minimax
tic-tac-toe-minimax is a c++ console application for teaching the computer how to play tic-tac-toe using minimax AI algorithm.


<p align="center">
	<img src="preview/tictactoe.png" style="width: 220px;"></img>
</p>


## Definition of tic-tac-toe

tic-tac-toe is a game in which two players alternately put Xs and Os in compartments of a figure formed by two vertical lines crossing two horizontal lines and each tries to get a row of three Xs or three Os before the opponent does.


## First Known Use of tic-tac-toe

circa 1866, in the meaning defined above.


## History and Etymology for tic-tac-toe

tic-tac-toe, former game in which players with eyes shut brought a pencil down on a slate marked with numbers and scored the number hit.


## Play tic-tac-toe with computer by using the random method

they are lot of way to play tic-tac-toe with the computer one of them is the random method, when It's the turn of the computer the computer choose form availables slot one randomly

* Example of the random method on our code :

The function __getListofChooses__ is a function that return all availables slot that the computer can choose and mark one from It.
And after that the computer choose randomly one of the slot that stored in the class variable __listChooses__ by the function rand(), "rand() % (max - min + 1) + min".


```c++
int computerRandomSlot(char **board, std::vector<int> listChooses){
	listChooses.clear();
	listChooses = getListofChooses(board);

	//decision
	srand(time(NULL));
	return  ( listChooses.at( (rand() % ( (listChooses.size() - 1) + 1)) ) );
}
```