#ifndef JNP1_4_IMPERIALFLEET_H
#define JNP1_4_IMPERIALFLEET_H

#include <iostream>

template<typename U>
class ImperialStarship {
private:
    U shield, attackPower;

    ImperialStarship() = default;

public:
    typedef U valueType;

    ImperialStarship(U shield, U attackPower) : shield(shield), attackPower(attackPower) {}

    U getShield() const { return shield; }

    U getAttackPower() const { return attackPower; }

    void takeDamage(U damage) {
        if (damage < shield) {
            shield -= damage;
        } else {
            shield = 0;
        }
    }
};

// Specjalizacje ogólnego szablonu statku Imperium.
template<typename U>
using DeathStar = ImperialStarship<U>;

template<typename U>
using ImperialDestroyer = ImperialStarship<U>;

template<typename U>
using TIEFighter = ImperialStarship<U>;

// Wykonanie ataku między statkami Imperium, a Rebelii.
template<typename I, typename U>
void attack(ImperialStarship<I> &imperialShip, Explorer <U> &rebelShip) {
    // Sprawdzenie czy oba statki żyją.
    if (rebelShip.getShield() > 0 && imperialShip.getShield() > 0) {
        rebelShip.takeDamage(imperialShip.getAttackPower());
    }
}

template<typename I, typename U>
void attack(ImperialStarship<I> &imperialShip, XWing <U> &rebelShip) {

    if (rebelShip.getShield() > 0 && imperialShip.getShield() > 0) {
        rebelShip.takeDamage(imperialShip.getAttackPower());
        imperialShip.takeDamage(rebelShip.getAttackPower());
    }

}

template<typename I, typename U>
void attack(ImperialStarship<I> &imperialShip, StarCruiser <U> &rebelShip) {

    if (rebelShip.getShield() > 0 && imperialShip.getShield() > 0) {
        rebelShip.takeDamage(imperialShip.getAttackPower());
        imperialShip.takeDamage(rebelShip.getAttackPower());
    }
}
// Jeśli przesłane są inne parametry to nie robi nic.
template<typename I, typename R>
void attack(I &imperialShip, R &rebelShip) {
    (void) imperialShip;
    (void) rebelShip;
}


#endif //JNP1_4_IMPERIALFLEET_H
