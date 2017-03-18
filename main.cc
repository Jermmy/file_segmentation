#include "file_segment.hpp"
#include "input_parser.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <exception>

using namespace std;

#include "json.hpp"

using json = nlohmann::json;

int main(int argc, char const *argv[])
{
	try {
		InputParser parser(argc, argv);
		vector<string> tokens = parser.get_tokens();
		
		FileSegment fs;
		if (tokens[0] == "-s") {
			if (tokens.size() < 2) {
				throw invalid_argument("please input segment file!");
			}
			if (tokens.size() < 3) {
			    throw invalid_argument("please input segment number!");	
			}
			string file = tokens[1];
			int segment_num = stoi(tokens[2]);

			if (tokens.size() == 4) {
				fs.segment(file, segment_num, tokens[3]);
			} else {
				fs.segment(file, segment_num);
			}
		} else if (tokens[0] == "-m") {
			if (tokens.size() < 2) {
				fs.merge();
			} else {
				fs.merge(tokens[1]);
			}
		}
	} catch (invalid_argument &e) {
		cout << "exception: " << e.what() << endl;
	}

	return 0;
}

