#include "./burger.h"
#include "./concrete_burger.h"
#include "./person.hpp"
#include <vector>
struct BurgerFactoryRegistrar {
	BurgerFactoryRegistrar() {
		BurgerFactory::registerFactory("simple", []() {
			return std::make_unique<SimpleBurgerFactory>();
		});
		BurgerFactory::registerFactory("healthy", []() {
			return std::make_unique<HealthyBurgerFactory>();
		});
	}
};
// 一个静态变量，其构造函数会注册工厂
static BurgerFactoryRegistrar g_registrar;

void enjoy_our_meals(std::vector<Person>& crowds) {
	for (auto& each_person : crowds) {
		each_person.enjoy_burger(BurgerFactory::createBurgerFromPreference(each_person).get());
	}
}

int main() {
	std::vector<Person> persons {
		{}, { Burger::BurgerType::Cheese }, { Burger::BurgerType::Chicken }
	};

	enjoy_our_meals(persons);
}