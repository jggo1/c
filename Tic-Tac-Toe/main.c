#include <stdio.h>
#include <stdlib.h>

/*
 *      rows
 *
 * 7   = 000 000 111
 * 56  = 000 111 000
 * 448 = 111 000 000
 *
 *     columns
 *
 * 73  = 001 001 001
 * 146 = 010 010 010
 * 292 = 100 100 100
 *
 *    diagonals
 *
 * 84  = 001 010 100
 * 273 = 100 010 001
 *
 */
int win_code[8] = {7,56,448, 73,146,292, 84,273};

struct _Player{
    int    cod;
    char   symbol;
    struct _Player *next;
};

typedef struct _Player* Player;
Player player;

char board[9]="         ";

//after add on board: player->cod+=pow(2,index);
int add_board(int index);

// check_win()==false: player=player->next;
int check_win();

void print_board();

int main(){
    //Create player 1
    player                  = (Player) malloc(sizeof(Player));

    //player 1 variables
    player->symbol          = 'X';
    player->cod             = 0;

    //Create player 2
    //after player 1 is player 2
    player->next            = (Player) malloc(sizeof(Player));

    //player 2 variables
    player->next->symbol    = 'O';
    player->next->cod       = 0;

    //after player 2 is player 1
    player->next->next      = player;

    /*  one struct control two players.

         _________________|struct _Player*|_________________
        |                                                   |
        |                player=player->next;               |
        |            ___________________________            |
        |           |                           |           |
        |    _______|_______             ______\ /______    |
        |   |               |           |               |   |
        |   |       X       |           |       O       |   |
        |   |_______________|           |_______________|   |
        |          / \                          |           |
        |           |___________________________|           |
        |                                                   |
        |                 player=player->next;              |
        |___________________________________________________|

    */

    int index, turn=1;

    do{
        print_board();
        do{
            printf("Enter a number from 1 to 9 (Valid).\n");
            scanf("%d",&index);
            fflush(stdin);
        //correct range? try add on board.
        }while(index < 1 || index > 9 || !add_board(index));
    }while(!check_win()&&turn++<9);
    free(player->next); 
    free(player);
    return 0;
}

int add_board(int index){
    index--;
    //board is empty.
    if(board[index]==' '){
        //add on board.
        board[index]=player->symbol;
        /*
               |   |
            2^0|2^1|2^2
            ---|---|---
            2^3|2^4|2^5
            ---|---|---
            2^6|2^7|2^8
               |   |
        */
        player->cod |= 1 << index;
        return 1;
    }
    return 0;
}

int check_win(){
    int x;
    for(int x = 0; x < 8; x++){
        /*
            Example check:

                X| |O
                O|X|   player X cod = 337 = 101010001
                X|O|X

            player->cod:    101010001
                                     &
            win_code[8]:    100010001
                            ---------
                            100010001 == win_code[8]

        */
        if((player->cod&win_code[x])==win_code[x]){
            print_board();
            printf("\n\t   Player: %c Win!\n\n",player->symbol);
            return 1;
        }
    }
    //player did not win, next player.
    player=player->next;
    return 0;
}

void print_board(){
    system("cls");
    printf("\n\n\t   Tic Tac Toe\n\n");
    printf("\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c  \n",board[0],board[1],board[2]);
    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c  \n",board[3],board[4],board[5]);
    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c  \n",board[6],board[7],board[8]);
    printf("\t     |     |     \n");
    printf("\n");
}
