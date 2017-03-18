#include "file_segment.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char const *argv[])
{

	FileSegment fs;
	fs.segment("test.zip", 3);
	fs.merge();

	return 0;
}

