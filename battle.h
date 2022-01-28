#ifndef JNP1_4_BATTLE_H
#define JNP1_4_BATTLE_H

#include <type_traits>
#include <array>
#include <tuple>
#include <iostream>
#include <typeinfo>

template<typename T, T t0, T t1, typename... S>
class SpaceBattle {
private:
    T actTime = t0;
    const T endTime = t1;
    std::tuple<S...> fleet;

    // Oblicza rozmiar tablicy attackTimes.
    static constexpr size_t countAttackTimesSize(T timeLimit) {
        size_t size = 0;
        auto limit = static_cast<size_t>(timeLimit);
        while (size * size <= limit) size++;
        return size;
    }

    // Tworzy tablicę z czasami ataków.
	template <typename U = T, size_t size>
    static constexpr std::array<U, size> getAttackTimes() {
        std::array<U, size> array{};
        for (size_t i = 0; i < array.size(); ++i) {
            array[i] = i * i;
        }
        return array;
    }

    static constexpr auto attackTimes = getAttackTimes<T, countAttackTimesSize(t1)>();

    // Sprawdza czy czas ataku jest dozwolony.
    bool attackTime(T actTime) const {
        for (auto time : attackTimes)
            if (time == actTime)
                return true;
        return false;
    }

    // Wykonuje pojedyńczy atak.
    template<typename U>
    void attackSingle(ImperialStarship <U> &impShip) {
        if (impShip.getShield() > 0)
            std::apply([&](auto &...x) { (..., attack(impShip, x)); }, fleet);
    }

    // Jeśli przesłane są inne parametry to nie robi nic.
    template<typename I>
    void attackSingle(I impShip) {
        (void) impShip;
    }

    // Wykonanie ataku
    void doAttack() {
        std::apply([&](auto &...x) { (..., attackSingle(x)); }, fleet);
    }

    // Zliczanie żywych statków Imperium.
    template<typename U>
    void countImperial(size_t &count, ImperialStarship <U> ship) {
        (void) ship;
        if (ship.getShield() > 0) count++;
    }

    // Jeśli przesłane są inne parametry to nie robi nic.
    template<typename U>
    void countImperial(size_t &count, U ship) {
		(void) count;
        (void) ship;
    }

    // Zliczanie żywych statków Rebelii.
    template<typename U>
    void countRebel(size_t &count, U ship) {
        (void) ship;
        if (ship.getShield() > 0) count++;
    }

    // Jeśli przesłane są inne parametry to nie robi nic.
    template<typename U>
    void countRebel(size_t &count, ImperialStarship <U> ship) {
		(void) count;
        (void) ship;
    }

public:
    explicit SpaceBattle(S... ships)
            : fleet(std::make_tuple(ships...)) {
        static_assert(std::is_integral<T>::value, "time parameter must be an integral type.");
        static_assert(t0 >= 0, "t0 must be greater than 0.");
        static_assert(t1 >= t0, "t1 must be greater than t0.");
    }
    // Oblicza liczebność floty Imperium.
    size_t countImperialFleet() {
        size_t impShips = 0;
        std::apply([&](auto ...x) { (..., countImperial(impShips, x)); }, fleet);
        return impShips;
    }

    // Oblicza liczebność floty Rebelii.
    size_t countRebelFleet() {
        size_t rebShips = 0;
        std::apply([&](auto ...x) { (..., countRebel(rebShips, x)); }, fleet);
        return rebShips;
    }

    void tick(T timeStep) {
        // Sprawdza czy mamy zwyciezce.
        if (countRebelFleet() == 0 && countImperialFleet() == 0) {
            std::cout << "DRAW" << std::endl;
        } else if (countRebelFleet() == 0) {
            std::cout << "IMPERIUM WON" << std::endl;
        } else if (countImperialFleet() == 0) {
            std::cout << "REBELLION WON" << std::endl;
        } else if (attackTime(actTime)) {
                doAttack();
        }
        actTime = (actTime + timeStep) % endTime;
    }
};
//to moj kolejny commit
#endif //JNP1_4_BATTLE_H
