#include "NesoraReadNSML.h"
#include "NesoraLocale.h"

nesora::NesoraMarkupLanguage::NesoraMarkupLanguage() {

}

nesora::NesoraMarkupLanguage::NesoraMarkupLanguage(const std::string& filename) {
    LoadFile(filename);
}

int nesora::NesoraMarkupLanguage::LoadFile(const std::string& filename) {
    std::ifstream ifs(filename);

    if(!ifs)
        return 1;

    std::string str;
    getline(ifs, str);
    if(!(str == "nesoɾä mʲikomʲi"))
        return 2;

    buffer.clear();
    int nowState = 0;
    std::string nowKey = "";
    while (getline(ifs, str)) {
        if(str.rfind("ä ", 0) == 0) {
            nowState = 0;
        }
        else if(str.rfind("ɾ ", 0) == 0) {
            nowKey = str.substr(3);
            if (buffer.count(nowKey))
                nowState = 0;
            else
                keyList.push_back(nowKey);
                nowState = 1;
        }
        else {
            if(nowState) {
                if(buffer.count(nowKey))
                    buffer[nowKey].append("\n");
                else
                    buffer[nowKey] = "";
                buffer[nowKey].append(str);
            }
        }
    }

    return 0;
}

std::map<std::string, std::string> nesora::NesoraMarkupLanguage::GetNSML(){
    return buffer;
}

const std::map<std::string, std::string> nesora::NesoraMarkupLanguage::GetNSML() const {
    return buffer;
}

std::string nesora::NesoraMarkupLanguage::operator[](const std::string& key) {
    return buffer[key];
}

const std::string nesora::NesoraMarkupLanguage::operator[](const std::string& key) const {
    return buffer.at(key);
}

std::string nesora::NesoraMarkupLanguage::operator[](const size_t& num){
    return keyList[num];
}

const std::string nesora::NesoraMarkupLanguage::operator[](const size_t& num) const{
    return keyList[num];
}
