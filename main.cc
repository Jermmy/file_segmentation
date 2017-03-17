#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

#include "json.hpp"

using json = nlohmann::json;

bool exist(string name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

size_t file_size(ifstream &file) {
	size_t size;
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0, std::ios::beg);

	return size;
}

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

	// cout << j["list"] << endl;

	// vector<int> v = j["list"];
	// for (auto it = v.begin(); it != v.end(); it++) {
	// 	cout << *it << " ";
	// }

	ifstream fin("t.txt");

    int size = file_size(fin);
	cout << file_size(fin) << endl;
	char i;
	fin >> i;
	cout << i << endl;

	ofstream fout("t_copy.txt");
	fout.seekp(size);
	fout.close();

	fin.close();

	return 0;
}

