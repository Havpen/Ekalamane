#include <iostream>
#include <vector>
#include <memory>
#include <exception>
#include <string>

struct NameExp : public std::exception {
	const char* what() const noexcept override {
		return "wrong name.";
	}
};
struct LoginExp : public std::exception {
	const char* what() const noexcept override {
		return "wrong login.";
	}
};

class User {
private:
	const std::string _login;
	std::string _password;
	std::string _name;
public:
	User(const std::string& login, const std::string& password, const std::string& name)
		: _login(login), _password(password), _name(name) {}
	const std::string& getLogin() const {
		return _login;
	}
	const std::string& getPassword() const {
		return _password;
	}
	const std::string& getName() const {
		return _name;
	}
	void setPassword(const std::string& password) {
		_password = password;
	}
	void setName(const std::string& name) {
		_name = name;
	}
};

class Message {
private:
	const std::string _from;
	const std::string _to;
	const std::string _text;
public:
	Message(const std::string& from, const std::string& to, const std::string& text)
		: _from(from), _to(to), _text(text) {}
	const std::string& getFrom() const {
		return _from;
	}
	const std::string& getTo() const {
		return _to;
	}
	const std::string& getText() const {
		return _text;
	}
};

class Chat {
private:
	bool _isChatWork = false;
	std::vector<User> _users;
	std::vector<Message> _messages;
	std::shared_ptr<User> _thisUser = nullptr;
	void SignIn() {
		std::string login, password;
		char choice;
		do {
			std::cout << "Enter your login: ";
			std::cin >> login;
			std::cout << "Enter your password: ";
			std::cin >> password;

			_thisUser = getUsersLogin(login);

			if (_thisUser == nullptr || (password != _thisUser->getPassword())) {
				_thisUser = nullptr;
				std::cout << "login error" << std::endl;
				std::cout << "type '0' to exit: ";
				std::cin >> choice;
				if (choice == '0') {
					break;
				}
			}
		} while (!_thisUser);
	}
	void SignUp() {
		std::string login, password, name;

		std::cout << "Enter your login: ";
		std::cin >> login;
		std::cout << "Enter your password: ";
		std::cin >> password;
		std::cout << "Enter your name: ";
		std::cin >> name;

		if (getUsersLogin(login) || login == "all") {
			throw LoginExp();
		}
		if (getUsersName(name) || name == "all") {
			throw NameExp();
		}
		User user = User(login, password, name);
		_users.push_back(user);
		_thisUser = std::make_shared<User>(user);
	}
	void showChat() {
		std::string from;
		std::string to;
		std::cout << "........Chat........" << std::endl;
		for (auto& mess : _messages) {
			if (_thisUser->getLogin() == mess.getFrom() || _thisUser->getLogin() == mess.getTo() || mess.getTo() == "all")
				from = (_thisUser->getLogin() == mess.getFrom()) ? "me" : getUsersLogin(mess.getFrom())->getName();
			if (mess.getTo() == "all") {
				to = " (all)";
			}
			else {
				to = (_thisUser->getLogin() == mess.getTo()) ? "me" : getUsersLogin(mess.getTo())->getName();
			}
			std::cout << "Message from " << from << "to" << to << std::endl;
			std::cout << "text: " << mess.getText() << std::endl;
		}
		std::cout << "...................." << std::endl;
	}
	void sendMessage() {
		std::string to, text;
		std::cout << "To (all) ";
		std::cin >> to;
		std::cout << "Your message: ";
		std::cin >> text;
		if (!(to == "all" || getUsersName(to))) {
			std::cout << "Error" << std::endl;
			return;
		}
		if (to == "all") {
			_messages.push_back(Message{ _thisUser->getLogin(), "all", text });
		}
		else { _messages.push_back(Message{ _thisUser->getLogin(), getUsersName(to)->getLogin(), text }); }
	}
	void AllChatUsers() {
		std::cout << "........Users........" << std::endl;
		for (auto& user : _users) {
			std::cout << user.getLogin();
			if (_thisUser->getLogin() == user.getLogin()) {
				std::cout << "-You" << std::endl;
			}
			std::cout << "...................." << std::endl;
		}
	}
	std::vector<User>& getUsers() {
		return _users;
	}
	std::vector<Message>& getMessages() {
		return _messages;
	}
	std::shared_ptr<User> getUsersLogin(const std::string& login) {
		for (auto& user : _users) {
			if (login == user.getLogin()) {
				return std::make_shared<User>(user);
			}
		}
		return nullptr;
	}
	std::shared_ptr<User> getUsersName(const std::string& _name) {
		for (auto& name : _users) {
			if (_name == name.getName()) {
				return std::make_shared<User>(name);
			}
		}
		return nullptr;
	}
public:
	void startChat() {
		_isChatWork = true;
	}
	bool isChatWork() const { return _isChatWork; }
	std::shared_ptr<User> getthisUser() const { return _thisUser; }
	void loginMenu() {
		_thisUser = nullptr;
		char choice;
		do {
			std::cout << "SignIn->1" << std::endl;
			std::cout << "SignUp->2" << std::endl;
			std::cout << "Exit->0" << std::endl;
			std::cout << "Choice: ";
			std::cin >> choice;
			switch (choice) {
			case '1': SignIn(); break;
			case '2':
				try {
					SignUp();
				}
				catch (const std::exception& e) {
					std::cout << e.what() << std::endl;
				}
				break;
			case '0':
				_isChatWork = false;
				break;
			default:
				std::cout << "error" << std::endl;
				break;
			}

		} while (!_thisUser && _isChatWork);
	}
	void userMenu() {
		char choice;
		std::cout << "Hello, " << (_thisUser ? _thisUser->getName() : "") << std::endl;
		while (_thisUser) {
			std::cout << "Menu: Chat->1 | New message->2 | Users->3 | Logout->0" << std::endl;
			std::cout << "Choice: ";
			std::cin >> choice;
			switch (choice) {
			case '1': showChat(); break;
			case '2': sendMessage(); break;
			case '3': AllChatUsers(); break;
			case '0': _thisUser = nullptr; break;
			default:
				std::cout << "Error" << std::endl;
				break;
			}
		}
	}
};

auto main() -> int {
	Chat chat;
	chat.startChat();

	while (chat.isChatWork()) {
		chat.loginMenu();
		while (chat.getthisUser()) {
			chat.userMenu();
		}
	}
	return 0;
}