#include <iostream>
#include <string>
#include <vector>

/**
 * @brief   For common, we need to set all the data members
 *          private for security reason, but this is the demo
 *          I decide to make the session easy!
 *          In real project, please expose getter/setter instead
 */
class HtmlElement {
public:
	std::string element_name {};
	std::string element_text {};
	std::vector<HtmlElement> element_children;
	HtmlElement() = default;
	HtmlElement(const std::string name, const std::string text)
	    : element_name(name)
	    , element_text(text) {
		// default we dont place children here
	}

	std::string factorize_printable() {
		return factorize_printable(*this);
	}

	static std::string factorize_printable(const HtmlElement& element, int tab_count = 1) {
		std::string result;
		result += factorize_printable_helper_begin(element);
		for (const auto& each : element.element_children) {
			result += "\n" + std::string("\t", tab_count) + factorize_printable(each, tab_count + 1);
		}
		if (!element.element_children.empty()) {
			result += "\n";
		}
		result += factorize_printable_helper_end(element);
		return result; // dont worry, we will call RVO default
	}

private:
	// helper to dump a HtmlElement
	static std::string factorize_printable_helper_begin(const HtmlElement& helper) {
		return "<" + helper.element_name + "> " + helper.element_text + " ";
	}
	static std::string factorize_printable_helper_end(const HtmlElement& helper) {
		return "</" + helper.element_name + ">";
	}
};
