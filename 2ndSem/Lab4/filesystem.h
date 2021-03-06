#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <algorithm>
#include <optional>
#include <limits>
#include <regex>

#include "directory.h"
#include "file.h"

struct FilterForm {

    std::optional <std::regex> name;
    size_t minSize;
    std::optional <size_t> maxSize;

    FilterForm (std::optional <std::regex> _name,  std::optional <size_t> _maxSize, size_t _minSize)

            : name (std::move (_name)),
              minSize (_minSize),
              maxSize (_maxSize)
    {}
};

class Filesystem {           // Task 1

    Directory *mRoot;

public:

    Filesystem ()

        : mRoot (new Directory ("home")) {}


    explicit Filesystem (std::string_view startName)

            : mRoot(new Directory(startName)) {}

    Directory* root() const {

        return mRoot;
    }

    Directory* findDirectory (std::string path) const {     // part of task 2

        using namespace boost::algorithm;

        std::vector<std::string> directories;
        split (directories, path, is_any_of("/"));

        auto temp = mRoot;

        for (const auto &i : directories) {

            for (const auto &j : temp->children)
                if (j->name == i) {
                    temp = j;
                    break;
                }
        }

        if (directories.back() != temp->name || directories.empty())
            temp = nullptr;

        return temp;
    }

    File* findFile (std::string path) const {       // part of task 2

        size_t point = path.rfind('/');
        auto filename = path.substr (point + 1, path.size());

        path.resize(point);
        auto ourDir = findDirectory(path);

        for (auto &i : ourDir->files)
            if (i->name() == filename)
                return i;

        return nullptr;
    }



    std::vector <std::string> findByName (std::string_view name) const {    // part of task 2

         std::vector <std::string> paths;
         mRoot->findByNameHelper (name, paths);
         return paths;
    }


    void createDir (std::string path, std::string_view _name) {   // part of task 3

        findDirectory(std::move(path))->createDir(_name);
    }


    void createFile (std::string path, std::string_view _name, size_t size) {  // part of task 3

        findDirectory (std::move(path))->createFile(_name, size);
    }

    Directory* deleteDir (std::string_view path) {      // task 13

        const auto foundDir = findDirectory(path.data());
        auto parent = foundDir->parent;
        std::string ourName = foundDir->name;

        Directory *newDir = nullptr;

        parent->children.erase (std::remove_if (
                parent->children.begin(), parent->children.end(),

                [&ourName, &newDir] (auto dir) mutable {

            if (dir->name == ourName) {
                newDir = dir;
                return true;
            }

                    return false;
        }));

        newDir->parent = nullptr;

        for (auto &i : newDir->children)
            i->parent = newDir;

        for (auto &i : newDir->files)
            i->dir = newDir;

        return newDir;
    }


    File* deleteFile (std::string_view path) {      //task 13

        auto parent = findFile (path.data())->directory();
        std::string ourName = findFile (path.data())->name();

        File *newFile;

        parent->files.erase (std::remove_if (parent->files.begin(), parent->files.end(),

                [&ourName, &newFile] (auto file) {

            if (file->name() == ourName) {

                newFile = file;
                return true;
            }
        }));

        newFile->dir = nullptr;

        return newFile;
    }


    void filter (const FilterForm &criteria) {

        filterHelper (mRoot, criteria);
    }

private:

    void filterHelper (Directory *dir, const FilterForm &criteria) {

        for (auto it = dir->children.begin(); it < dir->children.end();) {

            if (!std::regex_match((*it)->name.begin(), (*it)->name.end(), criteria.name.value_or (std::regex (".*"))))

                it = dir->children.erase (it);

            else {

                filterHelper (*it, criteria);
                ++it;
            }
        }

        for (auto it = dir->files.begin(); it < dir->files.end();) {

            if (!std::regex_match((*it)->name().begin(), (*it)->name().end(), criteria.name.value_or (std::regex (".*")))
                || (*it)->size() < criteria.minSize
                || (*it)->size() > criteria.maxSize.value_or (std::numeric_limits<size_t>::max()))

                it = dir->files.erase (it);

            else
                ++it;
            }
    }
};

#endif
