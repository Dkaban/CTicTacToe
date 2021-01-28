/**
 * Author: Dustin Kaban
 * Date: January 12th, 2021
 *
 * Class: main.c
 *
 * This class allows the user to play a game of Tic-Tac-Toe against the computer.
 * The player is X and the computer is O.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Function Declarations */
void drawBoard();
int nextUserMove();
void assignPlayerMove(int index);
void assignComputerMove();
bool checkForGameOver();
bool checkIfBoardFull();
bool checkIndexes(int i, int j, int k);
void displayFinalResult();

/* Static Variable Declarations */
static char gameBoard[10] = {'0','1','2','3','4','5','6','7','8','\0'};
static bool gameOver = false;
static char winner = ' ';
static const int BOARD_SIZE = 9;

int main()
{
    //Local string to store the users entered name
    char name[30];
    //The index that the player chooses
    int playerMovePosition = 0;

    //Display prompts to ask user for input
    printf("What is your name?\n");
    scanf("%[^\n]%*c",name);
    printf("Hello %s ... Let's have fun !!! You = X | Computer = O",name);
    drawBoard();

    while(!gameOver)
    {
        //Get the selected index from the user
        playerMovePosition = nextUserMove();
        //Assign an X to the selected index
        assignPlayerMove(playerMovePosition);
        //Assign an O based on the computers random selection
        assignComputerMove();
        //Display the board to the User
        drawBoard();
    }

    //Display the final outcome to the user
    displayFinalResult();

    return 0;
}

void drawBoard()
{
    //We draw the board using the gameBoard array to place the characters as they change
    printf("\n-----------------------------------");
    printf("\n %c  |   %c  |   %c",gameBoard[0],gameBoard[1],gameBoard[2]);
    printf("\n--- |  --- |  --- ");
    printf("\n %c  |   %c  |   %c",gameBoard[3],gameBoard[4],gameBoard[5]);
    printf("\n--- |  --- |  --- ");
    printf("\n %c  |   %c  |   %c",gameBoard[6],gameBoard[7],gameBoard[8]);
}

int nextUserMove()
{
    //Ask the user where to play their X, ask them again if space already contains O or X
    printf("\n-----------------------------------");
    int movePosition = 0;

    printf("\nEnter X,Y coordinates for your move:");
    scanf("%d",&movePosition);

    //Force the user to choose another index if an X,O already exists or it is outside the gameBoard arrays size
    while(gameBoard[movePosition] == 'X' || gameBoard[movePosition] == 'O'
    || movePosition >= BOARD_SIZE || movePosition < 0)
    {
        printf("\nInvalid Move, Enter X,Y coordinates for your move:");
        scanf("%d",&movePosition);
    }

    return movePosition;
}

bool checkForGameOver()
{
    //Check rows, columns, and diagonals for matching X's or O's
    if(checkIndexes(0,1,2) || checkIndexes(3,4,5) || checkIndexes(6,7,8)
    || checkIndexes(0,3,6) || checkIndexes(1,4,7) || checkIndexes(2,5,8)
    || checkIndexes(0,4,8) || checkIndexes(6,4,2))
    {
        return true;
    }
    else if(checkIfBoardFull())
    {
        return true;
    }

    return false;
}

bool checkIfBoardFull()
{
    //If the gameBoard is full, we want to end the game in a draw
    for(int i=0;i< BOARD_SIZE;i++)
    {
        if(gameBoard[i] != 'X' || gameBoard[i] != 'O')
        {
            return false;
        }
    }
    return true;
}

bool checkIndexes(int i, int j, int k)
{
    if(gameBoard[i] == 'X' && gameBoard[j] == 'X' && gameBoard[k] == 'X')
    {
        //X Wins
        winner = 'X';
        return true;
    }
    else if(gameBoard[i] == 'O' && gameBoard[j] == 'O' && gameBoard[k] == 'O')
    {
        //X Wins
        winner = 'O';
        return true;
    }

    return false;
}

void displayFinalResult()
{
    printf("\n-----------------------------------");

    if(winner == ' ')
    {
        printf("\nThe game is a draw");
    }
    else
    {
        printf("\nThe Winner is: %c",winner);
    }
}

void assignPlayerMove(int index)
{
    if(gameBoard[index] == 'X' || gameBoard[index] == 'O')
    {
        //We cannot make a move, ask player to try again
    }
    else
    {
        gameBoard[index] = 'X';
    }

    //Verify if the game is over based on the users move
    gameOver = checkForGameOver();
}

void assignComputerMove()
{
    //Pick a random index from the gameBoard array that does not contain an X or O and assign it an O
    if(!gameOver)
    {
        //Loop through the list and choose a position at random
        bool foundIndex = false;
        int r = rand() % BOARD_SIZE;

        while(!foundIndex)
        {
            if(gameBoard[r] != 'X' && gameBoard[r]!= 'O')
            {
                gameBoard[r] = 'O';
                foundIndex = true;
            }
            r = rand() % BOARD_SIZE;
        }
    }
    //Verify if the game has ended or not based on the computers move
    gameOver = checkForGameOver();
}
