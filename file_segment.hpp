#include <string>
#include <ifstream>
using namespace std;

class FileSegment {
public:
	void segment(string file_name, int segment_num, string json_file);
	void merge(string json_file);
private:
	bool exist(string name);
	size_t file_size(ifstream &file);
	void copy_file(ifstream &input, ofstream &output, size_t input_size);

	inline void read_file_in_block(char* data, ifstream &input, int size=kBlockSize) {
		input.read(data, size);
	}
	inline void write_file_in_block(char* data, ofstream &output, int size=kBlockSize) {
		output.write(data, size);
	}
private:
	static const string kSegmentFileNum = "SegmentNum";
	static const string kSourceFileName = "SourceFileName";
	static const string kSegmentFiles = "SegmentFiles";

	static const int kBlockSize = 1024 * 1024;  // 1MB
	
};