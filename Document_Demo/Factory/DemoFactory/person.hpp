#pragma once
#include "./burger.h"
#include <print>
struct Person {
	Person() = default;
	Person(Burger::BurgerType t)
	    : preferType(t) { }
	// I like that lol
	Burger::BurgerType preferType { Burger::BurgerType::Beef };
	void enjoy_burger(const Burger* aBurger) {
		std::println("The Person is enjoying the burger:");
		std::println("{}", aBurger->format_self());
		std::println("Yami!");
	}
};
