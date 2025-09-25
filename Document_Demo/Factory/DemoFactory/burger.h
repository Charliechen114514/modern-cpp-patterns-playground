#pragma once
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
struct Person;
struct Burger {
	// Burgers we support
	enum class BurgerType {
		Cheese,
		Beef,
		Chicken
	};
	Burger() = default;
	virtual ~Burger() = default;

	virtual std::string format_self() const = 0;
};

struct ConcreteBurgerFactory {
	virtual ~ConcreteBurgerFactory() = default;
	virtual std::unique_ptr<Burger> create(Burger::BurgerType p) const = 0;
};

struct BurgerFactory {
	using FactoryCreator = std::function<std::unique_ptr<ConcreteBurgerFactory>()>;

	static void registerFactory(const std::string& key, FactoryCreator c) {
		getRegistry()[key] = c;
	}

	static std::unique_ptr<Burger> createBurgerFromPreference(const Person& person);

private:
	static std::map<std::string, FactoryCreator>& getRegistry() {
		static std::map<std::string, FactoryCreator> registry;
		return registry;
	}

	static std::string chooseFactoryKey(const Person& person);
};