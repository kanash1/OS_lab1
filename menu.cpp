#include "menu.h"

Item::Item(const std::string& name, const std::function<void()>& action) : name(name), action(action) {}

Menu::Menu(const std::string& name, const std::string& close_option, const std::vector<Item>& v_items) :
	name(name), close_option(close_option), v_items(v_items) {}

void Menu::display(const std::string& message = "") const {
	std::cout << name << '\n';
	for (size_t i = 0; i < v_items.size(); ++i)
		std::cout << i + 1 << ". " << v_items[i].name << '\n';
	std::cout << 0 << ". " << close_option << '\n';
	if (!message.empty())
		std::cout << "Message: " << message << '\n';
}

bool Menu::execute_request(const int& request) const {
	if (request > 0 && request <= v_items.size())
		v_items[request - 1].action();
	else if (request != 0)
		throw std::out_of_range("There is no option with this number");
	return request == 0;
}

size_t select_option() {
	int request;
	std::cout << "Select: ";
	InputError input_error = input(std::cin, request);
	if (input_error != InputError::ERROR_NORMAL) {
		if (input_error == InputError::ERROR_INVALID || input_error == InputError::ERROR_TRASH)
			throw std::invalid_argument("Invalid value was entered");
		else
			throw std::invalid_argument("Nothing was entered");
	}
	return request;
}

void menu_process(const Menu& menu) {
	bool is_close = false;
	std::string message;
	do {
		system("cls");
		menu.display(message);
		try {
			message = "";
			size_t request = select_option();
			is_close = menu.execute_request(request);
		}
		catch (std::exception& ex) {
			message = ex.what();
		}
	} while (!is_close);
}