/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** GraphicalLibraryLoader
*/

#include "GraphicalLibraryLoader.hpp"

gui::LibraryObject::LibraryObject(const std::string &path)
{
    this->_path = path;
    this->_handle = dlopen(this->_path.c_str(), RTLD_LAZY);
    if (this->_handle == nullptr)
        return;

    auto nameHandle = reinterpret_cast<const char *(*)()>(dlsym(this->_handle, "name"));
    if (nameHandle == nullptr)
        return;
    this->_name = nameHandle();

    auto typeHandle = reinterpret_cast<gui::SharedLibraryType (*)()>(dlsym(this->_handle, "type"));
    if (typeHandle == nullptr)
        return;
    this->_type = typeHandle();

    _loaded = true;
}

gui::LibraryObject::~LibraryObject()
{
    if (_handle != nullptr)
        dlclose(_handle);
}

gui::LibraryLoader::LibraryLoader(const std::string &path)
{
    if (!std::filesystem::exists(path))
        return;

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        auto object = std::make_shared<LibraryObject>(entry.path().string());
        if (object->loaded())
            this->_libs.push_back(object);
    }
    std::cout << "Loaded " << _libs.size() << " libraries from path: " << path << std::endl;
}

gui::LibraryLoader::~LibraryLoader()
{
}

bool gui::LibraryLoader::contains(const std::string &lib, gui::SharedLibraryType type) const
{
    for (auto l : this->_libs)
        if (path_cmp(lib, l->path()) && l->type() == type)
            return true;
    return false;
}

bool gui::LibraryLoader::contains(const std::string &lib) const
{
    for (auto l : this->_libs) {
        if (path_cmp(lib, l->path()))
            return true;
    }
    return false;
}

bool gui::LibraryLoader::contains(gui::SharedLibraryType type) const
{
    for (auto l : this->_libs)
        if (l->type() == type)
            return true;
    return false;
}

std::shared_ptr<gui::LibraryObject> gui::LibraryLoader::nextLib()
{
    this->_libIndex = (this->_libIndex + 1) % _libs.size();
    while (this->_libs[this->_libIndex]->type() != gui::SharedLibraryType::LIBRARY)
        this->_libIndex = (this->_libIndex + 1) % _libs.size();
    return this->_libs[this->_libIndex];
}

std::shared_ptr<gui::LibraryObject> gui::LibraryLoader::load(const std::string &path, gui::SharedLibraryType type) {
    if (this->_libIndex < 0)
        this->_libIndex = 0;
    auto l = this->_libs[this->_libIndex];

    while (!path_cmp(l->path(), path))
        l = type == gui::SharedLibraryType::LIBRARY ? this->nextLib() : nullptr;
    return l;
}

bool gui::LibraryLoader::path_cmp(const std::string &a, const std::string& b) const
{
    std::string _a = a.starts_with(".") || a.starts_with("/") ? a : "./" + a;
    std::string _b = b.starts_with(".") || b.starts_with("/") ? b : "./" + b;
    _a = _a.starts_with("/") ? "." + _a.substr(std::filesystem::current_path().string().size()) : _a;
    _b = _b.starts_with("/") ? "." + _b.substr(std::filesystem::current_path().string().size()) : _b;
    return _a == _b;
}
