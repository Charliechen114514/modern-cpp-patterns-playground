#include "html_org_build.h"
#include <array>
#include <print>
#include <string>
int main() {
	HtmlElement element { "ul", "" };
	std::array<std::string, 2> lists {
		"Charlie", "Chen"
	};

	for (const auto& each : lists) {
		element.element_children.emplace_back("li", each);
	}

	std::println("formatted:\n{}", element.factorize_printable());
}
