
#ifndef NESORA_COMMON_READ_NSML_H
#define NESORA_COMMON_READ_NSML_H

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

namespace nesora {

    class NesoraMarkupLanguage {
    private:
        std::map<std::string, std::string> buffer = {};
        std::vector<std::string> keyList = {};

    public:
        NesoraMarkupLanguage();
        NesoraMarkupLanguage(const std::string& filename);

        int LoadFile(const std::string& filename);

        std::map<std::string, std::string> GetNSML();
        const std::map<std::string, std::string> GetNSML() const;

        std::string operator[](const std::string&);
        const std::string operator[](const std::string&) const;

        std::string operator[](const size_t&);
        const std::string operator[](const size_t&) const;

    }; // class NesoraMarkupLanguage

}//namespace nesora




#endif //NESORA_COMMON_READ_NSML_H