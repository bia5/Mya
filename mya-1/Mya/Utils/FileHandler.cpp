#include "FileHandler.h"

FileHandler::FileHandler() {}

std::vector<std::string> FileHandler::listDir(std::string folder) {
	std::vector<std::string> paths;
	for (std::filesystem::recursive_directory_iterator i(folder), end; i != end; ++i)
		if (!is_directory(i->path()))
			paths.push_back(i->path().u8string());
	return paths;
}

int FileHandler::getSize(std::vector<std::string> v){
	return v.size();
}

std::string FileHandler::get(std::vector<std::string> v, int i){
	return v[i];
}

bool FileHandler::dirExists(std::string path) {
	if (std::filesystem::exists(path))
		return std::filesystem::is_directory(path);
	return false;
}

bool FileHandler::fileExists(std::string path) {
	if (std::filesystem::exists(path))
		return std::filesystem::is_regular_file(path);
	return false;
}

void FileHandler::createDir(std::string path) {
	std::filesystem::create_directories(path);
}

void FileHandler::createFile(std::string path) {
	std::ofstream{path};
}
