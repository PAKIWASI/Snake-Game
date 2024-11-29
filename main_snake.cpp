#include "functions.h"




int main()
{
    Setup();       
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }
    return 0;
}
