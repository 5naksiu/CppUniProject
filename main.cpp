#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
#define usleep(usec) this_thread::sleep_for(std::chrono::microseconds(usec))
using namespace std;

int intro(int &size, char &character){
    cout <<"                                                  ,----,                           \n"
         <<"                        ,--,                    ,/   .`|                             \n"
         <<"   ,---,              ,--.'|   ,---,          ,`   .'  :   ,---,.          ,----..   \n"
         <<",`--.' |           ,--,  | :  '  .' \\       ;    ;     / ,'  .' |         /   /   \\  \n"
         <<"|   :  :        ,---.'|  : ' /  ;    '.   .'___,/    ,',---.'   |        |   :     : \n"
         <<":   |  '        |   | : _' |:  :       \\  |    :     | |   |   .'        .   |  ;. / \n"
         <<"|   :  |        :   : |.'  |:  |   /\\   \\ ;    |.';  ; :   :  |-,        .   ; /--`  \n"
         <<"'   '  ;        |   ' '  ; :|  :  ' ;.   :`----'  |  | :   |  ;/|        ;   | ;     \n"
         <<"|   |  |        '   |  .'. ||  |  ;/  \\   \\   '   :  ; |   :   .'        |   : |     \n"
         <<"'   :  ;        |   | :  | ''  :  | \\  \\ ,'   |   |  ' |   |  |-,        .   | '___  \n"
         <<"|   |  '        '   : |  : ;|  |  '  '--'     '   :  | '   :  ;/|        '   ; : .'| \n"
         <<"'   :  |        |   | '  ,/ |  :  :           ;   |.'  |   |    \\        '   | '/  : \n"
         <<";   |.'         ;   : ;--'  |  | ,'           '---'    |   :   .'        |   :    /  \n"
         <<"'---'           |   ,/      `--''                      |   | ,'           \\   \\ .'   \n"
         <<"                '---'                                  `----'              `---`     \n"
         <<"                                                                                     "
         <<endl<<endl<<"Made by Kewin Mejer s27134"<<endl<<endl;

    while(size < 3 || size > 30) {
        cout << "enter starting height(height has to be odd number between 3 and 30):";
        cin >> size; // pobieranie rozmiaru od użytkownika
        if(size%2==0){
            size++;
        }
    }
    cout << "enter ASCII character:";
    cin >> character; // pobieranie znaku ASCII od użytkownika

}
void Gotoxy(int x,int y){ // funkcja gotoxy służy do przemieszczania kursora
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Screensize(int& width,int& height) { // funkcja pobiera szerokość i wysokość okna
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
    height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
}
void Bounds(int &x,int &y,int &size,int width,int height){ // jeżeli użytkownik zmienił rozmiar okna to czyścimy pozostałości figury
    if(size > width){
        size = width;
        system("cls");
        Gotoxy(0,0);
    }
    if(size > height){
        size = height;
        system("cls");
        Gotoxy(0,0);
    }
    if(x+(size/2) > width-2){
        x = width-1-(size/2);
    }
    if(y+size > height-1){
        y--;
    }
}
void Print(int x,int y,char c,int size){ // funkcja rysowania figury
    bool half = false;     // jeżeli bool = true rysowana jest druga połowa figury
    int j = 0;

    for (int i = size; i > 0; --i) {
        Gotoxy(x+j,y+i);
        cout << c;
        if (j == size/2)
            half = true;
        if (!half)
            j++;
        else
            j--;
    }
}
void MovementResize(int key,int &x,int &y,int &size,int width,int height){ // funkcja poruszania się i skalowania figury
    if (key) {
        Print(x,y,' ',size); // czyszczenie poprzednich znaków
    }
    bool arrow = false;
    if (key == 224) {
        key = getch();
        arrow = true;
    }
    switch (key) { // poruszanie się strzałkami
        case 72:
            if (arrow && y >= 0) // blokada na wychodzenia poza okienko
                y--;
            break;
        case 80:
            if (arrow && y < height) // blokada na wychodzenia poza okienko
                y++;
            break;
        case 75:
            if (arrow && x > 0) // blokada na wychodzenia poza okienko
                x--;
            break;
        case 77:
            if (arrow && x + size/2 < width-1) // blokada na wychodzenia poza okienko
                x++;
            break;
        case 43:
            if(size/2 + x < width-1 && size/2 + x < height) // figura nie może być większa niż wysokość okna
                size = size+2;
            break;
        case 45:
            if (size > 3) // figura nie może być mniejsza niż 1 znak
                size = size-2;
            break;
        default:
            break;
    }
}
int main() {
    int size=0; // rozmiar figury
    char character; // znak ascii

    intro(size,character); // funkcja wywołująca intro

    int x=0,y=0,width=0,height=0; // wszystkie zmienne potrzebne do funkcji
    for (int key = 0; key != 'q'; key = kbhit() ? getch() : 0){ // jeżeli klikniemy q program zakończy działanie
        Screensize(width, height); // rozmiar okna
        Bounds(x,y,size,width,height); // blokada wychodzenia za okno
        MovementResize(key,x,y,size,width,height); // poruszanie figurą
        Print(x,y,character,size); // wyświetlanie figury

        usleep(500 * 30);
        system("cls"); // czyszczenie konsoli
    }
    cout << endl;
    return 2137;
}
