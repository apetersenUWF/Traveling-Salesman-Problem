#include <iostream>
#include "menu.hpp"
using namespace std;
int main() {
    Menu* menu;
    menu = new Menu();
    menu->run();
    delete menu;
  return 0;
}