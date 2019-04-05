#pragma once
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>

bool my_comp(std::string, std::string);

class Executor {
public:
	Executor() {}
	Executor(std::string file) { read(file); };

	const std::string needle1 = "readfile";
	const std::string needle2 = "writefile";
	const std::string needle3 = "grep";
	const std::string needle4 = "sort";
	const std::string needle5 = "replace";
	const std::string needle6 = "synch";
	std::map <std::string, std::string> dict;
	std::vector<std::thread> ths;
	std::mutex mtx;
	bool mtx_fl = 0;

	void my_readfile(std::string file, std::vector<std::string>& text);
	void writefile(std::vector<std::string>& text, std::string file);
	void grep(std::vector<std::string>&, std::string);
	void my_replace(std::vector<std::string>& text, std::string word1, std::string word2);
	void threadFunction(std::string line);// , std::mutex &mtx);
	void read(std::string);
};
