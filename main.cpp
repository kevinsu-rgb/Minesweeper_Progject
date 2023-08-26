#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"
using namespace std;


int main(){
    bool game_closed = false;
    string Name = "";
    startwindow(Name, game_closed);
    if (game_closed == true){

    }
    else{
        gamewindow(Name);
    }
}