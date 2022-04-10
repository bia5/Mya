#pragma once

#include <iostream>
#include <vector>

#include <filesystem>
#include <fstream>


class FileHandler {
public:
	FileHandler();

	std::vector<std::string> listDir(std::string folder);
	int getSize(std::vector<std::string> v);
	std::string get(std::vector<std::string> v, int i);

	bool dirExists(std::string path);
	bool fileExists(std::string path);
	void createDir(std::string path);
	void createFile(std::string path);
};