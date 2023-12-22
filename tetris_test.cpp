#include<iostream>
#include<conio.h>
#include<windows.h>

void InitGame() {
    std::cout << "Start with Enter button" << std::endl;
    char c = _getch();
    if(c == 13) {
        std::cout << "Start!" << std::endl;
    }
}

void showScreen(int col, int row, const char* back[][12], int point) {
    //화면 보여주기
    for(int i=0;i<col;i++) {
        for(int j=0;j<row;j++) {
            std::cout << back[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << "point : " << point << std::endl;
    std::cout << "If you want to exit, press button Enter key." << std::endl;
}

int main() {
    int col = 14; int row = 12;
    int time = 0; int point = 0;
    char c; boolean trigger = false;
    const char* back[col][12] = {0,};
    const char* block[4][4] = {
                {" ", "■", " ", " "},
                {" ", "■", " ", " "},
                {" ", "■", " ", " "},
                {" ", "■", " ", " "}
    };

    //배경 생성 □■
    for(int i=0;i<col;i++) {
        for(int j=0;j<row;j++) {
            if(i==col-1) back[i][j] = "□";
            else if(i<4) back[i][j] = " ";
            else{
                if(j==0 || j==row-1) back[i][j] = "□";
                else back[i][j] = " ";
            }
        }
    }

    InitGame();

    while (true) {
        //키 입력 시
        if(_kbhit() > 0) {
            c = _getch();
            showScreen(col, row, back, point);
            if(c == 13) {
                std::cout << "Bye!" << std::endl;
                break;
            }
        }

        //블록 생성
        if(trigger) {
            for(int i=0;i<4;i++) {
                for(int j=0;j<4;j++) {
                    back[i][j+4] = block[i][j];
                }
                std::cout << std::endl;
            }
        }

        showScreen(col, row, back, point);

        //난이도(프레임)
        Sleep(1000);
        time++;
        
        system("cls");
    }
        
}