#include "pch.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "executor.h"

void Executor::my_readfile(std::string file, std::vector<std::string>& text) {
	std::ifstream file1;
	file1.open(file);
	if (file1.is_open()) {
		std::string line;
		while (getline(file1, line))
			text.push_back(line);
		file1.close();
	}
}

void Executor::writefile(std::vector<std::string>& text, std::string file) {
	std::ofstream out(file, std::ios::app);
	if (out.is_open()) {
		for (int i = 0; i < text.size(); ++i)
			out << text[i] << '\n';
		out.close();
	}
	text.clear();
}

void Executor::grep(std::vector<std::string>& text, std::string word) {
	std::vector<std::string> new_text;
	for (int i = 0; i < text.size(); ++i)
		if (text[i].find(word) != std::string::npos)
			new_text.push_back(text[i]);
	text = new_text;
}

void Executor::my_replace(std::vector<std::string>& text, std::string word1, std::string word2) {
	for (int i = 0; i < text.size(); ++i) {
		std::string::size_type index;
		while ((index = text[i].find(word1)) != std::string::npos)
			text[i].replace(index, word1.size(), word2);
	}
}

void Executor::threadFunction(std::string line) {
	std::vector <std::string> text;
	std::string n = "";
	int fl_lock = 0;

	for (int j = 0; j < line.size(); ++j) {

		if ('0' <= line[j] && line[j] <= '9')
			n += line[j];
		if (line[j] == '>' || j == line.size() - 1) {

			if (mtx_fl) {
				mtx.lock();
				fl_lock = 1;
			}
			// std::cout << std::this_thread::get_id() << "\n";
			if (!dict.count(n)) {
				n = "";
				continue;
			}
			std::string comand = "";
			for (int i = 0; i < dict[n].size(); ++i) {
				if (dict[n][i] == ' ')
					break;
				comand += dict[n][i];
			}
			if (comand == needle1) {
				std::string filename;
				for (int i = needle1.size() + 1; i < dict[n].size(); ++i)
					filename += dict[n][i];
				my_readfile(filename, text);
			}
			else if (comand == needle2) {
				std::string filename = "";
				for (int i = needle2.size() + 1; i < dict[n].size(); ++i)
					filename += dict[n][i];
				writefile(text, filename);
			}
			else if (comand == needle3) {
				std::string word = "";
				for (int i = needle3.size() + 1; i < dict[n].size(); ++i)
					word += dict[n][i];
				grep(text, word);
			}
			else if (comand == needle4) {
				std::sort(text.begin(), text.end(), my_comp);
			}
			else if (comand == needle5) {
				int i;
				std::string word1 = "";
				std::string word2 = "";
				for (i = needle5.size() + 1; dict[n][i] != ' '; ++i)
					word1 += dict[n][i];
				for (i = i + 1; i < dict[n].size(); ++i)
					word2 += dict[n][i];
				my_replace(text, word1, word2);
			}
			else if (comand == needle6) {
				mtx_fl = 1;
			}
			//std::cout << std::this_thread::get_id() << "\n";
			if (mtx_fl && fl_lock) {
				mtx.unlock();
				//Sleep(50);
				fl_lock = 0;
			}
			n = "";
			continue;
		}
	}
}

void Executor::read(std::string f) {
	std::ifstream file;
	file.open(f);
	std::string line;
	if (file.is_open()) {
		getline(file, line);
		while (getline(file, line) && line != "end" && line != "End" && line != "END") {
			while (line[line.size() - 1] == ' ')
				line.erase(line.size() - 1, 1);
			if (line == "" || line == "\n")
				continue;
			std::string n = "";
			std::string word = "";
			int i;
			for (i = 0; i < line.size(); ++i) {
				if ('0' <= line[i] && line[i] <= '9')
					n += line[i];
				else
					break;
			}
			while (!(line[i] >= 'a' && line[i] <= 'z') && i < line.size())
				i++;

			for (; i < line.size(); ++i)
				word += line[i];
			dict[n] = word;
		}
		
		while (getline(file, line)) {
			//std::cout << "!!!\n";
			ths.push_back(std::thread(&Executor::threadFunction, this, line));
		}
		file.close();
		for (int i = 0; i < ths.size(); ++i) {
			if (ths[i].joinable()) {
				ths[i].join();
			}
		}
	}
	
}
bool my_comp(std::string a, std::string b) {
	int i, j;
	i = j = 0;
	int n1, n2;

	while (i < a.size() && j < b.size()) {
		n1 = n2 = 0;
		while (tolower(a[i]) == tolower(b[j]) && i < a.size() && j < b.size()) {
			i++;
			j++;
		}
		if (i == a.size() || j == b.size())
			break;

		if (!(a[i] >= '0' && a[i] <= '9') && !(b[j] >= '0' && b[j] <= '9')) {
			return tolower(a[i]) < tolower(b[j]);
		}
		if (!(a[i] >= '0' && a[i] <= '9') && (b[j] >= '0' && b[j] <= '9')) {
			if (j == 0 || (b[j - 1] >= '0' && b[j - 1] <= '9'))
				return 1;
			return 0;
		}
			
		if ((a[i] >= '0' && a[i] <= '9') && !(b[j] >= '0' && b[j] <= '9')) {
			if (i == 0 || (a[i - 1] >= '0' && a[i - 1] <= '9'))
				return 1;
			return 0;
		}
			

		while ((a[i] >= '0' && a[i] <= '9') && i < a.size()) {
			n1 = n1 * 10 + a[i] - '0';
			i++;
		}
		while ((b[j] >= '0' && b[j] <= '9') && j < b.size()) {
			n2 = n2 * 10 + b[j] - '0';
			j++;
		}
		if (n1 == n2)
			continue;
		return n1 < n2;
	}
	if (j == b.size())
		return 0;
	if (i == a.size())
		return 1;
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		std::string file = argv[1];
		//std::cout << file << "\n";
		Executor a(file);
		//std::cout << "GOOD BYE\n";
	}
	return 0;
}
