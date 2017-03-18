#include <string>
#include <vector>
#include <exception>
using namespace std;

class InputParser {
public:
	InputParser(int argc, const char **argv);
	vector<string> get_tokens();
private:
	vector<string> tokens;
};