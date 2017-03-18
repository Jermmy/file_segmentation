#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <iostream>

#include "json.hpp"
#include "file_segment.hpp"

using json = nlohmann::json;

 const string FileSegment::kSegmentFileNum = "SegmentNum";
 const string FileSegment::kSourceFileName = "SourceFileName";
 const string FileSegment::kSegmentFiles = "SegmentFiles";
 const int FileSegment::kBlockSize = 1024 * 1024;  // 1MB

void FileSegment::segment(string file_name, int segment_num, string json_file) {

	// 检查源文件是否存在
    if (!exist(file_name)) {
    	cout << "file [" << file_name << "] doesn't exist!" << endl;
    	return;
    }

    // 检查分片数量是否大于0
    if (segment_num <= 0) {
    	cout << "segment number should be greater than 0!" << endl;
    	return;
    }

    // 分片文件名
    vector<string> segment_files;
    for (int i = 0; i < segment_num; i++) {
    	segment_files.push_back(file_name + to_string(i+1) + ".tmp");
    	cout << "segment_file --- " << segment_files[i] << endl;
    }

    ifstream src_file_input(file_name);
    size_t src_file_size = file_size(src_file_input);
    size_t segment_size = src_file_size / segment_num;

    // 分片输出文件
    for (int i = 0; i < segment_num; i++) {
    	ofstream segment_file_output(segment_files[i]);
    	if (i == segment_num-1) {  // 最后一次，要将剩余文件片全部写入
    		size_t left_size = src_file_size % segment_size;
    		copy_file(src_file_input, segment_file_output, segment_size + left_size);
    	} else {
    		copy_file(src_file_input, segment_file_output, segment_size);
    	}
    	segment_file_output.close();
    }

    src_file_input.close();

	ofstream json_output(json_file);
	json j;
	j[kSegmentFileNum] = segment_num;
	j[kSourceFileName] = file_name;
	j[kSegmentFiles] = segment_files;
    json_output << j;
	json_output.close();
}


void FileSegment::merge(string json_file) {
	json j, array;

	if (!exist(json_file)) {
		cout << "json file [" << json_file << "] doesn't exist!" << endl;
		return;
	}

	ifstream json_input(json_file);
	json_input >> j;

	// 源文件名
	string src_file = j[kSourceFileName];

    // 检查源文件是否已经存在
	if (exist(src_file)) {
		// cout << "source file [" << src_file << "] is already existed!" << endl;
		// return;
		src_file += ".copy";
	}
	ofstream result(src_file);

    // 文件分片数量
	int segment_num = j[kSegmentFileNum];

    array = j[kSegmentFiles];
    vector<string> segment_files = j[kSegmentFiles];

    // 检查文件分片是否齐全
    for (auto it = segment_files.begin(); it != segment_files.end(); ++it) {
    	if (!exist(*it)) {
    		cout << "segment file [" << *it << "] doesn't exist!" << endl;
    		return; 
    	}
    }

    // 合并文件
    for (auto it = segment_files.begin(); it != segment_files.end(); it++) {
    	cout << "copy file [" << *it << "]" << endl;
    	ifstream seg_input(*it);
    	size_t seg_input_size = file_size(seg_input);
    	copy_file(seg_input, result, seg_input_size);
    	seg_input.close();
    }

	json_input.close();
	result.close();
}

void FileSegment::copy_file(ifstream &input, ofstream &output, size_t input_size) {
	char* data = new char[kBlockSize];
    
    for (size_t block = 0; block < input_size / kBlockSize; block++) {
    	read_file_in_block(data, input);
    	write_file_in_block(data, output);
    }

    size_t left_size = input_size % kBlockSize;
    if (left_size != 0) {
    	read_file_in_block(data, input, left_size);
    	write_file_in_block(data, output, left_size);
    }

	delete [] data;
	data = nullptr;
}

bool FileSegment::exist(string name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}


size_t FileSegment::file_size(ifstream &file) {
	size_t size;
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0, std::ios::beg);

	return size;
}

