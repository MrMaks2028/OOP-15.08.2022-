#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <fstream>

//создать список юзеров на 10.000 элементов.
// Заполнить элементами коллекции map
// Сравнить время необходимое на поиск в оригинальной коллекции
// данных и время на поиск и составление map

//Найти 10 юзеров с максимально близкими к ср. зарплатам
//записать в файл список юзеров(в режиме дозаписи)

class User {
public:
	int id;
	std::string name;
	int salary;
	bool dayShift;

	User() = default;
	User(int id, std::string name):id(id), name(name) {
		salary = ::rand() % (20'000 - 10'000) + 10'000;
		dayShift = ::rand() % 2;
	}

	int averageSalary(int mapSize) {
		int count = 0;
		for (int i = 0; i < mapSize; i++) {
			count += this->salary;
		}
		return count / mapSize;
	}

	bool operator==(const User& other)const {
		return id == other.id && name == other.name;
	}
	friend std::ostream& operator<<(std::ostream& out, const User& obj) {
		out << obj.id << ' ' << obj.name << ' ' << obj.dayShift << ' '
			<< obj.salary << ' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, User& obj) {
		in >> obj.id >> obj.name >> obj.dayShift >> obj.salary;
		return in;
	}
};

std::map<std::string, User> g_Users;

void task1(int count) {
	std::vector<User> database;
	database.reserve(count);

	auto begin = std::chrono::steady_clock::now();
	for (int i = 0; i < database.capacity(); i++) {
		database.emplace_back(i + 1, "user" + std::to_string(i + 1));
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>
		(end - begin);
	std::cout << "create vector: " << elapsed_ms.count() << "ms\n";

	std::map<std::string, User*> searchTree;
	begin = std::chrono::steady_clock::now();
	for (auto& user : database) {
		searchTree.insert({ user.name, &user });
	}
	end = std::chrono::steady_clock::now();
	elapsed_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>
		(end - begin);
	std::cout << "create map: " << elapsed_ms.count() << "ms\n";
	begin = std::chrono::steady_clock::now();
	auto vec_tmp = find(
		database.begin(),
		database.end(),
		User{ count, "user" + std::to_string(count) }
	);
	end = std::chrono::steady_clock::now();
	elapsed_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>
		(end - begin);
	std::cout << "Find in vector: " <<
		elapsed_ms.count() << "ms\n";

	begin = std::chrono::steady_clock::now();
	auto map_tmp = searchTree.find("user" + std::to_string(count));
	end = std::chrono::steady_clock::now();

	elapsed_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>
		(end - begin);
	std::cout << "Find in map: " <<
		elapsed_ms.count() << "ms\n";

	std::ofstream out("Текст.txt");
	for (auto &user : database) {
		out << user << '\n';
		std::cout << user << '\n';
	}
	out.close();

}

void task2() {
	std::vector<User> database;
	std::ifstream in("base.txt");
	while (!in.eof()) {
		User tmp;
		in >> tmp;
		tmp.id = database.size();
		database.push_back(tmp);
		in.close();
		database.pop_back();
		for (auto& user : database) {
			std::cout << user << '\n';
		}
	}
}



//map и unordered_map
//map - дерево поиска. Принимает два параметра: название(ключ) и что хранит(значение).
//at - генерирует исключение, а [] - нет! 
//pair - хранит два элемента первый и второй. Ключи константные
//наполнение коллекции(map-а) лучше всего делается с помощью insert.

//multimap

int main() {
	using namespace std;
	setlocale(LC_ALL, "Russian");
	
	/*g_Users.insert({"user", {1, "user"}});
	User local;
	local.id = 2;
	local.name = "User2";
	g_Users.insert({ local.name, local });
	g_Users["User3"];
	g_Users["User3"].id = 3;
	g_Users["User3"].name = "User3";
	std::pair<const std::string, User> &tmp =
		*(g_Users.begin());

	auto where_ = g_Users.find("User3");
	where_->second.id;

	auto &[login, user] = *(g_Users.find("User3")); // разложение структуры
	user.id;
	*/

	task1(10);
	
	/*multimap<std::string, User> searchTree;
	const auto&[begin, end] = searchTree.equal_range("key");
	vector<User> names(begin, end);
	for (auto& el : names) {
		std::cout << el << '\n';
	}*/

	return 0;
}