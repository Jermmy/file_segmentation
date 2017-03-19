# FileSegment

FileSegment is a tool to segment big file into small file segments or to merge file segments into the original big file. It is designed for people who needs to transfer big file between computers but with only small storage device. You can segment the file and then transfer the relatively small segmented files one by one and finally merge them on another computer.

## Compile

For *nix system, you can run `bash run.sh`, or just compile the source files using `g++ -std=c++11 main.cc file_segment.cc input_parser.cc -o main`.

The only dependent library is [json](https://github.com/nlohmann/json), and it is already included as a head file.

## Usage

Once you compile the code, you can segment your file by running 

```./main -s [your_file] [segment number] [json file] ``` 

 Note that for now you should put your file in the same directory with the program. The number of file segments is provided by `[segment number]`. The third parameter `[json file]` is a file name for configuration. It is optional and is set to `config.json` in default.

For merger, you can put the file segments and the configuration file together in the directory of the program, and run the command

```c++
./main -m [json file]
```

The parameter `[json file]` is optional and is set to `config.json` in default. But it should be match with your configuration file.









