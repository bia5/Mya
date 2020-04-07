#include "FileSystemHelper.h"

FileSystemHelper::FileSystemHelper()
{
}

std::vector<std::string> FileSystemHelper::getAllFoldersInADirectory(std::string path)
{
    std::vector<std::string> r;
    for (auto& p : std::filesystem::recursive_directory_iterator(path))
        if (p.is_directory())
            r.push_back(p.path().string());
    return r;
}

std::vector<std::string> FileSystemHelper::getAllFilesInADirectory(std::string path)
{
    std::vector<std::string> r;
    for (auto& p : std::filesystem::recursive_directory_iterator(path))
        if (!p.is_regular_file())
            r.push_back(p.path().string());
    return r;
}
