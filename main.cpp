//
// Created by kacper on 24.11.18.
//
#include <iostream>
#include "battle.h"
#include "imperialfleet.h"
#include "rebelfleet.h"

int main()
{
    ImperialDestroyer<int> a(1,2);
    ImperialStarship<int> b(10,10);
    Explorer<int> c(12,12);
    XWing<int> w(5, 2997959, 22);
    attack(a,w);
    std::cout << w.getShield() << " " << b.getShield() ;
}