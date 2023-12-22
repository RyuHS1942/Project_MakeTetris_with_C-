#include<iostream>
#include<conio.h>
#include<windows.h>
#include<array>

void InitGame() {
    std::cout << "Start game with Enter button!" << std::endl;
    char c = _getch();
    if(c == 13) std::cout << "Start!" << std::endl;
    //Sleep(2000);
}

void showView(int background[], int size, int point) {
    system("cls");
    for(int i=0;i<size;i++) {
        if(background[i] == 1) std::cout << "▦" << " ";
        else if(background[i] == 2) std::cout << "▧ ";
        else std::cout << "  ";
        if(i%15 == 14) std::cout << std::endl;
    }

    std::cout << "point : " << point << std::endl;
    std::cout << "If you want to exit, press button Enter key." << std::endl;
    
    Sleep(100);
}

boolean isNum2(int background[], int size) {
    for(int i=0;i<size;i++) {
        if(background[i] == 2) {
            return true;
        }
    }
    return false;
}

boolean endGame(int background[], int row) {
    for(int i=0;i<row*5;i++) {
        if(background[i] == 1) {
            std::cout << "Bye!" << std::endl;
            return true;
        }
    }
    return false;
}
//▦ ▧
int main() {
    int col = 21;
    int row = 15;
    int background[col * row] = {0,};
    int block[4*4] = {
        0,2,0,0,
        0,2,0,0,
        0,2,0,0,
        0,2,0,0
        };
    int point = 0;

    //배경 생성
    for(int i=0;i<col*row;i++) {
        if(i/row > 4 && (i%row == 14 || i%row == 0)) background[i] = 1;
        if(i/row == col-1) background[i] = 1;
    }

    InitGame();

    while(true) {
        if(_kbhit() > 0) {
            char c = _getch();

            if(c == 13) {
                std::cout << "Bye!" << std::endl;
                return false;
            }
            if(c == 72) {

            }
            if(c == 75) {
                for(int i=0;i<col*row;i++) {
                    if(background[i] == 2 && background[i-1] != 1) {
                        background[i] = 0;
                        background[i-1] = 2;
                    }
                }
            }
            if(c == 80) {
                for(int i=col*row-1;i>=0;i--) {
                    if(background[i] == 2 && background[i+row] != 1) {
                        background[i] = 0;
                        background[i+row] = 2;
                    }
                }
            }
            if(c == 77) {
                for(int i=col*row-1;i>=0;i--) {
                    if(background[i] == 2 && background[i+1] != 1) {
                        background[i] = 0;
                        background[i+1] = 2;
                    }
                }
            }
        }
        
        
        //블록 삽입
        if(!isNum2(background, col*row)) {
            for(int i=0;i<16;i++) {
                background[(i%4)+row/2-1+(i/4)*row] = block[i];
            }
        }

        showView(background, col*row, point);

        if(isNum2(background, col*row)) {
            for(int i=col*row-1;i>=0;i--) {
                if(background[i] == 2 && background[i+row] != 1) {
                    background[i] = 0;
                    background[i+row] = 2;
                }

                if(background[i+row] == 1) {
                    if(background[i] == 2) {
                        background[i] = 1;
                    }
                }
            }
        }

        if(endGame(background, row)) break;
    }

    return true;
}