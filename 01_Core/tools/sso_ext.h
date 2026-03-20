#ifndef SSO_EXT_H
#define SSO_EXT_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <array>
#include <memory>
#include <stdexcept>

namespace fs = std::filesystem;

inline int SSO_System(const std::string& cmd) {
    return std::system(cmd.c_str());
}

inline std::string SSO_GetOutput(const std::string& cmd) {
    std::array<char, 128> buffer;
    std::string result;
#ifdef _WIN32
    std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
#else
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
#endif
    if (!pipe) return "ERROR";
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

inline bool SSO_HasTool(const std::string& name) {
#ifdef _WIN32
    std::string check = "where " + name + " >nul 2>&1";
#else
    std::string check = "command -v " + name + " >/dev/null 2>&1";
#endif
    return (std::system(check.c_str()) == 0);
}

inline void SSO_Download(const std::string& url, const std::string& dest) {
    std::string cmd;
    if (SSO_HasTool("curl")) cmd = "curl -L \"" + url + "\" -o \"" + dest + "\"";
    else if (SSO_HasTool("wget")) cmd = "wget \"" + url + "\" -O \"" + dest + "\"";
    else {
#ifdef _WIN32
        cmd = "powershell -Command \"Invoke-WebRequest -Uri '" + url + "' -OutFile '" + dest + "'\"";
#else
        return;
#endif
    }
    SSO_System(cmd);
}

inline void SSO_Git(const std::string& args) {
    if (SSO_HasTool("git")) SSO_System("git " + args);
}

inline void SSO_Copy(const std::string& src, const std::string& dest) {
    if (fs::exists(src)) fs::copy(src, dest, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
}

inline void SSO_Move(const std::string& src, const std::string& dest) {
    if (fs::exists(src)) fs::rename(src, dest);
}

inline void SSO_Remove(const std::string& path) {
    if (fs::exists(path)) fs::remove_all(path);
}

inline void SSO_MakeFolder(const std::string& path) {
    if (!fs::exists(path)) fs::create_directories(path);
}

inline void SSO_Open(const std::string& target) {
#ifdef _WIN32
    SSO_System("start \"\" \"" + target + "\"");
#else
    SSO_System("xdg-open \"" + target + "\"");
#endif
}

inline void SSO_KillProcess(const std::string& name) {
#ifdef _WIN32
    SSO_System("taskkill /F /IM " + name + " /T >nul 2>&1");
#else
    SSO_System("pkill " + name + " >/dev/null 2>&1");
#endif
}

inline long long SSO_GetFileSize(const std::string& path) {
    if (fs::exists(path)) return fs::file_size(path);
    return -1;
}

inline std::string SSO_GetEnv(const std::string& var) {
    char* val = std::getenv(var.c_str());
    return (val == nullptr) ? "" : std::string(val);
}

inline void SSO_SetEnv(const std::string& var, const std::string& val) {
#ifdef _WIN32
    _putenv_s(var.c_str(), val.c_str());
#else
    setenv(var.c_str(), val.c_str(), 1);
#endif
}

#endif