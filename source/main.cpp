#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


//classes
class TicTacToe{
    char **board;
    std::string player1;
    std::string player2;
    char carrentMarker = 'x';
    int carrentPlayer = 1;
    std::vector<int> listChooses;
    std::vector<std::vector<int>> minimax;


    //fill the board by spaces
    char **fillBoard(char **board){
        for(int i = 0; i < 3; i++){
            for(int o = 0; o < 3; o++){
                board[i][o] = ' ';
            }
        }

        return board;
    }


    //draw the board
    void drawBoard(char **board){
        for(int i = 0; i < 3; i++){
            std::cout << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << std::endl;
            if(i != 2) std::cout << "---------\n";
        }
    }


    //get row and column value from slot
    int getRow(int &slot){
        return (slot % 3 == 0)? (slot / 3) - 1 : slot / 3;
    }
    int getColumn(int &slot){
        return (slot % 3 == 0)? 2 : (slot % 3 - 1);
    }

    //get All board slots
    char **getAllboardcases(char **board){
        char **newBoard = new char*[3];
        for(int i = 0; i < 3; i++){
            newBoard[i] = new char[3];
        }

        for(int i = 0; i < 3; i++){
            for(int o = 0; o < 3; o++){
                newBoard[i][o] = board[i][o];
            }
        }

        return newBoard;
    }

    //check if the slot is empty
    bool checkSlot(int slot, char **board){
        if(slot < 1 || slot > 9){
            return false;
        }

        int row = getRow(slot);
        int column = getColumn(slot);
        
        if(board[row][column] != 'x' && board[row][column] != 'o'){
            return true;
        }
        return false;
    }

    //marke the place of the slot
    char **placeMarker(int &slot, char **board, char carrentMarker){ 
        int row = getRow(slot);
        int column = getColumn(slot);

        if(checkSlot(slot, board))
            board[row][column] = carrentMarker;

        return board;
    }


    //check if someone win and return his carrentPlayer value or return 0 if no one win yet
    int winner(char **board, int carrentPlayer, bool draw = false){
        for(int i = 0; i < 3; i++){
            //check rows
            if((board[i][0] != ' ' && board[i][1] != ' ' && board[i][3] != ' ') && (board[i][0] == board[i][1] && board[i][1] == board[i][2])){
                if(draw){
                    drawBoard(board);
                    std::cout << "\n\n\n";
                }
                return carrentPlayer;
            }

            //check column
            if((board[0][i] != ' ' && board[1][i] != ' ' && board[2][i] != ' ') && (board[0][i] == board[1][i] && board[1][i] == board[2][i])){
                if(draw){
                    drawBoard(board);
                    std::cout << "\n\n\n";
                }
                return carrentPlayer;
            }
        }
        //check revers
        if((board[0][0] != ' ' && board[1][1] != ' ' && board[2][2] != ' ') && (board[0][0] == board[1][1] && board[1][1] == board[2][2])){
            if(draw){
                drawBoard(board);
                std::cout << "\n\n\n";
            }
            return carrentPlayer;
        }
        if((board[0][2] != ' ' && board[1][1] != ' ' && board[2][0] != ' ') && (board[0][2] == board[1][1] && board[1][1] == board[2][0])){
            if(draw){
                drawBoard(board);
                std::cout << "\n\n\n";
            }
            return carrentPlayer;
        }

        //if no one win yet
        return 0;
    }


    //swap the player and the marker
    char swapMarker(char cm){
        if(cm == 'x')
            return 'o';
        else
            return 'x';
    }
    int swapPlayeer(int cp){
        if(cp == 1)
            return 2;
        else
            return 1;
    }

    //get the list of chooses available in the board
    std::vector<int> getListofChooses(char **board){
        std::vector<int> listChooses;
        for(int i = 1; i <= 9; i++){
            if(checkSlot(i, board))
                listChooses.push_back(i);
        }

        return listChooses;
    }

    //check if the board is full
    bool isFullBoard(char **board){
        for(int i = 1; i <= 9; i++){
            if(checkSlot(i, board))
                return false;
        }
        return true;
    }

    //computer slot turn (the random slot)--------------------------------------------
    //this function choose randomly a slot from slots available on the board
    int computerRandomSlot(char **board, std::vector<int> listChooses){
        listChooses.clear();
        listChooses = getListofChooses(board);

        //decision
        srand(time(NULL));
        return  ( listChooses.at( (rand() % ( (listChooses.size() - 1) + 1)) ) );
    }


    //computer slot turn (AI slot)-----------------------------------------------------
    //this function calculate all utilities for all available slot and set them in "minimax" variable of the class
    void allUtilities(int &globalSlot, int lastSlot, char **board, int flag, char carrentMarker, int carrentPlayer){
        char **newBoard = new char*[3];
        for(int i = 0; i < 3; i++){
            newBoard[i] = new char[3];
        }
        newBoard = getAllboardcases(board);

        newBoard = placeMarker(lastSlot, board, carrentMarker);
        /*
        //draw the sub Board
        drawBoard(newBoard);
        std::cout << "\n\n\n";
        */
        std::vector<int> listChooses = getListofChooses(newBoard);

        if(winner(newBoard, carrentPlayer, false)){
            std::vector<int> v;
            v.push_back(globalSlot);
            v.push_back(flag * (listChooses.size() + 1));

            minimax.push_back(v);
            return;
        }

        if(isFullBoard(newBoard)){
            std::vector<int> v;
            v.push_back(globalSlot);
            v.push_back(0);

            minimax.push_back(v);
            return;
        }



        for(int i = 0; i < listChooses.size(); i++){
            char **newNewBoard = new char*[3];
            for(int i = 0; i < 3; i++){
                newNewBoard[i] = new char[3];
            }
            newNewBoard = getAllboardcases(newBoard);
            allUtilities(globalSlot, listChooses.at(i), newNewBoard, (flag * (-1)), swapMarker(carrentMarker), swapPlayeer(carrentPlayer));
        }
    }

    //this function make smart decision from "minimax" variable of the class and return the value of the slot that it decide to choose it
    int makeAIdecision(std::vector<int> &listChooses){
        int defaultKey = listChooses[0];
        int defaultMin;
        int defaultReduceGood = 0;
        int defaultReduceBad = 0;
        int keyMinMax;
        int minMinMax; 
        int reduceGoodMinMax;
        int reduceBadMinMax;
        
        for(int o = 0; o < minimax.size(); o++){
            if(minimax[o][0] == defaultKey){
                defaultMin = minimax[o][1];
                break;
            }
        }
        for(int o = 0; o < minimax.size(); o++){
            if(minimax[o][0] == defaultKey && minimax[o][1] > 0){
                defaultReduceGood += minimax[o][1];
            }
            if(minimax[o][0] == defaultKey && minimax[o][1] < 0){
                defaultReduceBad += minimax[o][1];
            }
            if(minimax[o][0] == defaultKey && minimax[o][1] < defaultMin){
                defaultMin = minimax[o][1];
            }
        }
        keyMinMax = defaultKey;
        minMinMax = defaultMin;
        reduceGoodMinMax = defaultReduceGood;
        reduceBadMinMax = defaultReduceBad;



        for(int i = 1; i < listChooses.size(); i++){
            int key = listChooses.at(i);
            int min;
            int reduceGood = 0;
            int reduceBad = 0;
            
            for(int o = 0; o < minimax.size(); o++){
                if(minimax[o][0] == key){
                    min = minimax[o][1];
                    break;
                }
            }
            for(int o = 0; o < minimax.size(); o++){
                if(minimax[o][0] == key && minimax[o][1] > 0){
                    reduceGood += minimax[o][1];
                }
                if(minimax[o][0] == key && minimax[o][1] < 0){
                    reduceBad += minimax[o][1];
                }
                if(minimax[o][0] == key && minimax[o][1] < min){
                    min = minimax[o][1];
                }
            }
            /*
            //print all informations about eche available slot
            std::cout << "key = " << key << ", min = " << min  << ", good reduce = " << reduceGood << ", bad reduce = " << reduceBad << std::endl;
            */
            if(min > minMinMax){ //chose the slot that have the big min utility (maximize min)
                keyMinMax = key;
                minMinMax = min;
                reduceGoodMinMax = reduceGood;
                reduceBadMinMax = reduceBad;
            }else if(min == minMinMax){
                if(reduceBad > reduceBadMinMax){ //chose the slot that have the big reduce of bads utilities
                    reduceGoodMinMax = reduceGood;
                    reduceBadMinMax = reduceBad;
                    keyMinMax = key;
                    minMinMax = min;
                }else if(reduceBad == reduceBadMinMax){ 
                    if(reduceGood > reduceGoodMinMax){ //chose the slot that have the big reduce of goods utilities
                        reduceGoodMinMax = reduceGood;
                        reduceBadMinMax = reduceBad;
                        keyMinMax = key;
                        minMinMax = min;
                    } else if (reduceGood == reduceGoodMinMax){ //choose randomly
                        srand(time(NULL));
                        if(rand() % 2 == 0){
                            reduceGoodMinMax = reduceGood;
                            reduceBadMinMax = reduceBad;
                            keyMinMax = key;
                            minMinMax = min;
                        }
                    }
                }
            }
        }

        return keyMinMax;
    }

    //this function for choose a slot by using the minimax algorithm
    int computerPerfectSlot(char **board, std::vector<int> listChooses){
        listChooses.clear();
        listChooses = getListofChooses(board);


        //if the board is empty choose a random slot
        if(listChooses.size() == 9){
            //decision
            std::vector<int> randomSlot = {1,2,3,4,5,6,7,8,9};
            srand(time(NULL));
            return  ( randomSlot.at( (rand() % ( (randomSlot.size() - 1) + 1)) ) );
        }

        //calculate all utilities of availables slot
        minimax.clear();
        for(int i = 0; i < listChooses.size(); i++){
            char **newBoard = new char*[3];
            for(int i = 0; i < 3; i++){
                newBoard[i] = new char[3];
            }
            newBoard = getAllboardcases(board);
            allUtilities(listChooses.at(i), listChooses.at(i), newBoard, 1, carrentMarker, carrentPlayer);
        }

        /*
        //print all utilities
        for(int i = 0; i < minimax.size(); i++){
            std::cout << "[" << minimax[i][0] << "] => (" << minimax[i][1] << ").\n"; 
        }
        */

        /*
        //print the nomber of Prospects possible
        std::cout << minimax.size() << std::endl;
        */

        //make a decision by analyse all utilities on the "minimax" variable of the class
        return makeAIdecision(listChooses);
    }

    
public:
    void play(std::string _player1, std::string _player2){
        player1 = _player1;
        player2 = _player2;

        //create the board
        board = new char*[3];
        for(int i = 0; i < 3; i++){
            board[i] = new char[3];
        }

        //fill the board
        board = fillBoard(board);


        drawBoard(board);


        int slot;

        //choose who will start the game randomly
        srand(time(NULL));
        int turn = rand() % 2;

        for(int i = 0; i < 9; i++){
            if(player1 == "humain" && player2 == "humain"){
                std::cout << "It's player " << carrentPlayer << "'s turn. Enter your slot: ";
                std::cin >> slot;
            }

            else if(player1 == "random" && player2 == "random"){
                std::cout << "\n\n";
                slot = computerRandomSlot(board, listChooses);
            }

            else if(player1 == "AI" && player2 == "AI"){
                std::cout << "\n\n";
                char **newBoard = new char*[3];
                for(int i = 0; i < 3; i++){
                    newBoard[i] = new char[3];
                }
                newBoard = getAllboardcases(board);
                slot = computerPerfectSlot(newBoard, listChooses);
            }

            else if((player1 == "humain" && player2 == "random") || (player1 == "random" && player2 == "humain")){
                if((turn + i) % 2 == 0){
                    std::cout << "It's player " << carrentPlayer << "'s turn. Enter your slot: ";
                    std::cin >> slot;
                }else{
                    std::cout << "\n\n";
                    slot = computerRandomSlot(board, listChooses);
                }
            }

            else if((player1 == "humain" && player2 == "AI") || (player1 == "AI" && player2 == "humain")){
                if((turn + i) % 2 == 0){
                    std::cout << "It's player " << carrentPlayer << "'s turn. Enter your slot: ";
                    std::cin >> slot;
                }else{
                    std::cout << "\n\n";
                    char **newBoard = new char*[3];
                    for(int i = 0; i < 3; i++){
                        newBoard[i] = new char[3];
                    }
                    newBoard = getAllboardcases(board);
                    slot = computerPerfectSlot(newBoard, listChooses);
                }
            }

            else if((player1 == "random" && player2 == "AI") || (player1 == "AI" && player2 == "random")){
                if((turn + i) % 2 == 0){
                    std::cout << "\n\n";
                    slot = computerRandomSlot(board, listChooses);
                }else{
                    std::cout << "\n\n";
                    char **newBoard = new char*[3];
                    for(int i = 0; i < 3; i++){
                        newBoard[i] = new char[3];
                    }
                    newBoard = getAllboardcases(board);
                    slot = computerPerfectSlot(newBoard, listChooses);
                }
            }

            //if something wrong when you chose the couple of players you will go to the default two players ("humain","humain")
            else{
                std::cout << "It's player " << carrentPlayer << "'s turn. Enter your slot: ";
                std::cin >> slot;
            }


            
            //check if the slot that the player choose is available or not before mark it
            if(!checkSlot(slot, board)){
                std::cout << "The slot " << slot << " isn't not vailable, tyr another one!\n";
                i--;
                continue;
            }
            board = placeMarker(slot, board, carrentMarker);
            
            drawBoard(board);

            //check if someone win
            if(winner(board, carrentPlayer)){
                std::cout << carrentMarker << " has won!\n\n\n";
                board = fillBoard(board);
                //game(player1, player2);
                return;
            }

            //swap to the player who will play in the next turn
            carrentMarker = swapMarker(carrentMarker);
            carrentPlayer = swapPlayeer(carrentPlayer);
        }

        std::cout << "This is a tie game! :/\n\n\n";
        board = fillBoard(board);
        //game(player1, player2);
    }

    
    ~TicTacToe(){
        for(int i = 0; i < 3; i++){
            delete[] board[i];
        }
        delete[] board;
        listChooses.clear();
        minimax.clear();
    }
};

//main function--------------------------------------
int main(int argc, char *argv[])
{
    TicTacToe t;
    /*
    you choose the two players by passing two argument from this : 
        "humain" : choose the slot from the keyboard input.
        "random" : choose the slot just randomly from the variables slots.
        "AI"     : choose the slot by analysis all utilities possible and make the perfect decision.

    EX:
        t.play("humain", "humain");
        t.play("humain", "random");
        t.play("humain", "AI");
        t.play("AI", "AI");
        t.play("AI", "random");
        t.play("random", "random");
    */
    t.play("humain", "AI");



    //wait the user to Enter the key "Enter" to finish the programe
    std::string finish;
    std::cout << "\n\n\nEnter any key to continue..." << std::endl;
    std::cin >> finish;
    return 0;
}