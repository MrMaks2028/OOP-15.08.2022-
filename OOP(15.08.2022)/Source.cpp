#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <chrono>

class User {
public:
	int id;
	std::string name;
	int salary;
	bool dayShift = true;

	User(int id, std::string name):id(id), name(name){}

	bool operator==(const User& other)const {
		return id == other.id && name == other.name;
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
}

void task2() {

}



//map � unordered_map
//map - ������ ������. ��������� ��� ���������: ��������(����) � ��� ������(��������).
//at - ���������� ����������, � [] - ���! 
//pair - ������ ��� �������� ������ � ������. ����� �����������
//���������� ���������(map-�) ����� ����� �������� � ������� insert.

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

	auto &[login, user] = *(g_Users.find("User3")); // ���������� ���������
	user.id;

	//������� ������ ������ �� 10.000 ���������.
	// ��������� ���������� ��������� map
	// �������� ����� ����������� �� ����� � ������������ ���������
	// ������ � ����� �� ����� � ����������� map
	*/

	task1(100'000);

	//����� ��. �������� ����������� ����/�������/������
	//����� 10 ����� � ����������� ������� � ����� �������� �����������



	return 0;
}