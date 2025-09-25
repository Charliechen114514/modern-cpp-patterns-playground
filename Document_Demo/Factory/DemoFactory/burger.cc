#include "./burger.h"
#include "./person.hpp"

std::string BurgerFactory::chooseFactoryKey(const Person& person) {
	if (person.preferType == Burger::BurgerType::Chicken) {
		return "healthy";
	}
	return "simple";
}

std::unique_ptr<Burger> BurgerFactory::createBurgerFromPreference(const Person& person) {
	std::string chosenKey = chooseFactoryKey(person);

	auto it = getRegistry().find(chosenKey);
	if (it == getRegistry().end()) {
		throw std::runtime_error("Factory key not found: " + chosenKey);
	}
	auto factory = (it->second)();
	return factory->create(person.preferType);
}