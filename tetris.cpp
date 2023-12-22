#include<iostream>
#include<conio.h>
#include<windows.h>

#define COL 11
#define ROW 20
#define ENTER 13
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80


struct Table {
    int table[COL*ROW] = {0,};
};

struct Block 
{
    int x = 0;
    int y = 0;
    int type = 0;
    int rotat = 0;
    int block[16] = {0,};
};

int tetris[4][4][16] = {
    {
        {
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        }, {
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        }, {
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        }, {
            0,0,0,0,
            0,1,1,0,
            0,1,1,0,
            0,0,0,0
        }
    }, {
        {
            0,1,0,0,
            0,1,0,0,
            0,1,0,0,
            0,1,0,0
        }, {
            0,0,0,0,
            1,1,1,1,
            0,0,0,0,
            0,0,0,0
        }, {
            0,0,1,0,
            0,0,1,0,
            0,0,1,0,
            0,0,1,0
        }, {
            0,0,0,0,
            0,0,0,0,
            1,1,1,1,
            0,0,0,0
        }
    }, {
        {
            0,1,0,0,
            0,1,0,0,
            0,1,1,0,
            0,0,0,0
        }, {
            0,0,0,0,
            0,1,1,1,
            0,1,0,0,
            0,0,0,0
        }, {
            0,0,0,0,
            0,1,1,0,
            0,0,1,0,
            0,0,1,0
        }, {
            0,0,0,0,
            0,0,1,0,
            1,1,1,0,
            0,0,0,0
        }
    }, {
        {
            0,0,0,0,
            0,1,0,0,
            1,1,1,0,
            0,0,0,0
        }, {
            0,1,0,0,
            0,1,1,0,
            0,1,0,0,
            0,0,0,0
        }, {
            0,0,0,0,
            0,1,1,1,
            0,0,1,0,
            0,0,0,0
        }, {
            0,0,0,0,
            0,0,1,0,
            0,1,1,0,
            0,0,1,0
        }
    }
};

void makeBack(int table[]) {
    for(int i=0;i<COL*ROW;i++) {
        if(i%ROW == 0 || i%ROW == ROW-1 || i/ROW == COL-1 || i/ROW == 0) table[i] = 2;
        else table[i] = 0;
    }
}

void initGame() {
    std::cout << "Start with any button" << std::endl;
    _getch();
    system("cls");
}

void makeBlock(int table[], struct Block * block) {
    for(int i=0;i<ROW*COL;i++) {
        if(table[i] == 1) return;
    }

    block->x = ROW/2;
    block->y = 1;
    block->type = rand()%4;
    block->rotat = rand()%4;

    for(int i=0;i<16;i++) {
        block->block[i] = tetris[block->type][block->rotat][i];
    }
}

void insertBlock(int table[], int block[], int x, int y) {
    for(int i=0;i<16;i++) {
        table[x-2+(i%4)+(y+(i/4))*ROW] = block[i];
    }
}

void fallBlock(int table[], struct Block * block) {

    for(int i=0;i<COL*ROW;i++) table[i] != 2 ? table[i] = 0:table[i] = 2;

    block->y += 1;

    for(int i=0;i<16;i++) {
        if(table[block->x-2+(i%4)+(block->y+(i/4))*ROW] == 2 && block->block[i] == 1) {
            block->y -= 1;
            for(int i=0;i<16;i++) {
                if(block->block[i] == 1) {
                    table[block->x-2+(i%4)+(block->y+(i/4))*ROW] = 2;
                }
            }
            return;
        }
    }

    for(int i=0;i<16;i++) {
        if(table[block->x-2+(i%4)+(block->y+(i/4))*ROW] == 0) {
            table[block->x-2+(i%4)+(block->y+(i/4))*ROW] = block->block[i];
        } else {
            
        }
    }
}

void terminateGame() {
    system("cls");
    std::cout << "Bye!" << std::endl;
}

void inputKey(int table[], struct Block * block) {
    if(_kbhit() > 0) {
        char c = _getch();
        
        if(c == ENTER) terminateGame();

        if(c == LEFT)  {
            block->x -= 1;

            for(int i=0;i<16;i++) {
                if(table[block->x-2+(i%4)+(block->y+(i/4))*ROW] == 2 && block->block[i] == 1){
                    block->x += 1;
                    
                    return;
                }
            }

            for(int i=0;i<16;i++) {
                if(table[block->x-2+(i%4)+(block->y+(i/4))*ROW] != 2) {
                    table[block->x-2+(i%4)+(block->y+(i/4))*ROW] = block->block[i];
                }
            }
        } else if(c == RIGHT) {
            block->x += 1;

            for(int i=0;i<16;i++) {
                if(table[block->x-2+(i%4)+(block->y+(i/4))*ROW] == 2 && block->block[i] == 1){
                    block->x -= 1;
                    
                    return;
                }
            }
        } else if(c == UP) {
            block->rotat = (block->rotat+1)%4;

            for(int i=0;i<16;i++) {
                block->block[i] = tetris[block->type][block->rotat][i];
            }

            for(int i=0;i<16;i++) {
                if(table[block->x-2+(i%4)+(block->y+(i/4))*ROW] == 2 && block->block[i] == 1){
                    
                    block->rotat = (block->rotat-1)%4;

                    for(int i=0;i<16;i++) {
                        block->block[i] = tetris[block->type][block->rotat][i];
                    }

                    return;
                }
            }

        } //else if(c == DOWN) block->y += 1;
        else ;
    }
}

void showGame(int table[]) {
    for(int i=0;i<COL*ROW;i++) {
        if(i%ROW == 0) std::cout << std::endl;
        if(table[i] == 2) std::cout << "¢Ë ";
        else if(table[i] == 1) std::cout << "¢Ê ";
        else std::cout << "  ";
    }
    Sleep(300);
    system("cls");
}

int main() {
    Table back;
    Block block;
    makeBack(back.table);

    initGame();

    while (true)
    {
        makeBlock(back.table, &block);

        insertBlock(back.table, block.block, block.x, block.y);

        showGame(back.table);
        
        fallBlock(back.table, &block);

        //inputKey(back.table, &block);
    }
    

    terminateGame();
    return 0;
}