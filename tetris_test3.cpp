#include<iostream>
#include<conio.h>
#include<windows.h>

#define COL 21
#define ROW 20
#define ENTER 13
#define LEFT 75     // ←
#define RIGHT 77    // →
#define UP 72       // ↑
#define DOWN 80     // ↓

int type;
int rotat;

struct Block {
    int x;  
    int y;
    int block[16];
};

int block1[4][4][16] = {
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

struct Table {
    int table[COL*ROW];
};

void makeTable(int table[]) {
    for(int i=0;i<COL*ROW;i++) {
        if(i%ROW == 0 || i%ROW == ROW-1 || i/ROW == COL-1) table[i] = 2;
        else table[i] = 0;
    }
}

void initGame() {
    std::cout << "TETRIS"<<std::endl;
    std::cout << "Start with any button" << std::endl;
    _getch();
    system("cls");
}

void makeBlock(int block[]) {
    type = rand()%4;
    rotat = rand()%4;

    for(int i=0;i<16;i++) {
        block[i] = block1[type][rotat][i];
    }
}

void insertBlock(int table[], int block[], int x, int y) {
    for(int i=0;i<16;i++) {
        table[x-2+(i%4)+(y+(i/4))*ROW] = block[i];
    }
}

boolean freeze(int table[]) {
    for(int i=0;i<COL*ROW;i++) {
        if(table[i] == 1 && table[i+ROW] == 2) return true;
    }
    return false;
}

void showTable(int table[]) {
    for(int i=0;i<COL*ROW;i++) {
        if(i%ROW == 0) std::cout << std::endl;
        if(table[i] == 2) std::cout << "▦ ";
        else if(table[i] == 1) std::cout << "▧ ";
        else std::cout << "  ";
    }
    Sleep(1000);
    system("cls");
}

boolean checkNum1(int table[]) {
    for(int i=0;i<COL*ROW;i++) if(table[i] == 1) return false;
    return true;
}

void terminateGame() {
    system("cls");
    std::cout << "Bye!" << std::endl;
}

int main() {
    Table table;
    Block block;

    makeTable(table.table);

    initGame();

    while(true) {
        if(checkNum1(table.table)) {
            makeBlock(block.block);
            block.x = ROW/2;
            block.y = 0;

            insertBlock(table.table, block.block, block.x, block.y);
        }

        if(freeze(table.table)) {
            for(int i=0;i<COL*ROW;i++) {
                if(table.table[i] == 1) table.table[i] = 2;
            }
            block.y = 0;
        } else {
            block.y += 1;

            for(int i=COL*ROW-1;i>=0;i--) {
                if(table.table[i] == 1) {
                    table.table[i] = 0;
                    table.table[i+ROW] = 1;
                }
            }
        }
            

        if(_kbhit() > 0) {
            char c = _getch();
            if(c == ENTER) {
                terminateGame();
                return 0;//비정상종료
            }
            if(c == LEFT) {
                for(int i=0;i<COL*ROW;i++) {
                    if(table.table[i] == 1 && table.table[i-1] != 2) {
                        table.table[i] = 0;
                        table.table[i-1] = 1;
                        block.x -=  1;
                    }
                }
            }
            if(c == RIGHT) {
                for(int i=COL*ROW-1;i>=0;i--) {
                    if(table.table[i] == 1 && table.table[i+1] != 2) {
                        table.table[i] = 0;
                        table.table[i+1] = 1;
                        block.x += 1;
                    }
                }
            }
            if(c == UP) {
                rotat = (rotat+1)%4;
                for(int i=0;i<16;i++) {
                    block.block[i] = block1[type][rotat][i];
                }
                insertBlock(table.table, block.block, block.x, block.y);
            }
            if(c == DOWN) {
                for(int i=16;i>=0;i--) {
                    
                }
            }
        }

        showTable(table.table);
    }

    terminateGame();

    return 1;//정상종료
}