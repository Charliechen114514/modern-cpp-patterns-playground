#pragma once
#include "./burger.h"

struct CheeseBurger : public Burger {
public:
	CheeseBurger() = default;
	std::string format_self() const override {
		return "A burger with cheese!";
	}
};

struct BeefBurger : public Burger {
public:
	BeefBurger() = default;
	std::string format_self() const override {
		return "A burger with beeeeeeeeeeeeef!";
	}
};

struct ChickenBurger : public Burger {
public:
	ChickenBurger() = default;
	std::string format_self() const override {
		return "A burger with chicken!";
	}
};

// 一些具体子工厂

struct SimpleBurgerFactory : public ConcreteBurgerFactory {
	std::unique_ptr<Burger> create(Burger::BurgerType p) const override {
		switch (p) {
		case Burger::BurgerType::Cheese:
			return std::make_unique<CheeseBurger>();
		case Burger::BurgerType::Beef:
			return std::make_unique<BeefBurger>();
		case Burger::BurgerType::Chicken:
			return std::make_unique<ChickenBurger>();
		default:
			throw std::runtime_error("Unknown burger preference");
		}
	}
};

struct HealthyBurgerFactory : public ConcreteBurgerFactory {
	std::unique_ptr<Burger> create(Burger::BurgerType p) const override {
		// 比如健康版不允许 beef，就把 beef 映射到 chicken
		if (p == Burger::BurgerType::Beef) {
			return std::make_unique<ChickenBurger>();
		}
		// 其余不变
		return std::make_unique<CheeseBurger>(); // 简化示例：都做 CheeseBurger
	}
};