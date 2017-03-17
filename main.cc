#include <iostream>
#include <fstream>

using namespace std;

#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char const *argv[])
{
	// json j = {
	// 	{"pi", 3.141},
	// 	{"happt", true},
	// 	{"nothing", nullptr},
	// 	{"list", {1,0,2}},
	// 	{"answer", {
	// 		{"everything", 42}
	// 	}},
	// 	{"object", {
	// 		{"currency", "USD"}
	// 	}}
	// };

	// cout << j << endl;
	json j;

	ifstream fin("test.json");
	fin >> j;
	fin.close();
	cout << j << endl;
	cout << j["answer"] << endl;
	cout << j["nothing"] << endl;
	return 0;
}

