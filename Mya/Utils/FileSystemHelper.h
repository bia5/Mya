#pragma once

#include <iostream>
#include <vector>
#include <filesystem>

class FileSystemHelper {
public:
	FileSystemHelper();

	std::vector<std::string> getAllFoldersInADirectory(std::string path);
	std::vector<std::string> getAllFilesInADirectory(std::string path);
};