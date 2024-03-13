#include <iostream>
#include <memory>
#include <vector>
#include <ctime>

class User {
protected:
	const std::string _login;
	std::string _password;
	std::string _name;
public:
	User(const std::string& login, const std::string& password, const std::string& name):_login(login), _password(password), _name(name){}
	~User(){}
	std::string getLogin() const {
		return _login;
	}
	std::string getPassword() const {
		return _password;
	}
	std::string getName() const {
		return _name;
	}
	std::string setPassword(const std::string& newPassword) {
		_password = newPassword;
	}
	std::string setName(const std::string& newName) {
		_name = newName;
	}
};

class Message {
protected:
	const std::string _text;
	const std::string _sender;
	const std::string _receiver;

public:
	Message(const std::string& text, const std::string& sender, const std::string& receiver): _text(text), _sender(sender), _receiver(receiver) {}
	const std::string &getText() const {
		return _text;
	}
	const std::string &getSender() const {
		return _sender;
	}
	const std::string &getReceiver() const {
		return _receiver;
	}
};



class Chat {
private:
	bool _Work=false;
	std::vector<User> _users;
	std::vector<Message> _messages;
	std::shared_ptr<User> _thisUser = nullptr;
	void login() {
		std::string login, password;
		char operation;
		do {
			std::cout << "Enter login: ";
			std::cin >> login;
			std::cout << "Enter password: ";
			std::cin >> password;
			_thisUser = getUserLogin(login);

		} while (!_thisUser);
	};
	void signUp() {
	
	};
	void showChat() {
	
	};
	void sendMessage() {
	
	};
	void AllChatUsers() {
	
	};
	std::vector<User> &getUsers() {
		return _users;
	}
	std::vector<Message> &getMessages() {
		return _messages;
	}
	std::shared_ptr<User> getUserLogin(const std::string& login) const {
		for (auto& user : _users) {
			if (login == user.getLogin()) {
				return std::make_shared<User>(user);
			}
		}
		return nullptr;
	};
	std::shared_ptr<User> getUserName(const std::string& name) const {
		for (auto& user : _users) {
			if (name == user.getName()) {
				return std::make_shared<User>(user);
			}
		}
	}
public:
	void startChat() {
		_Work = true;	
	}
	bool Work() const { return _Work; }
	std::shared_ptr<User> getthisUser() const { return _thisUser; }
	void loginMenu();
	void userMenu();
};

auto main() -> int {






	return 0;
}