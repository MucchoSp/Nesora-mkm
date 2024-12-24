#ifndef NESORA_INTERPRETER_H
#define NESORA_INTERPRETER_H

#include <string>
#include <cstdint>
#include <vector>
#include <map>
#include <iostream>

namespace nesora{

    struct NesoraLanguageCode{
        uint32_t language = 0;  //言語(4,294,967,295 = 42億)
        uint32_t dialect = 0;   //方言(4,294,967,295 = 42億)
        uint64_t speaker = 0;   //話者(18,446,744,073,709,551,615 = 1844京)

        friend bool operator<(const NesoraLanguageCode& a, const NesoraLanguageCode& b) {    // x, y, zの順に比較。条件6, 7を満たす 
            if (a.language != b.language) { 
                return a.language < b.language;
            }
            if(a.dialect != b.dialect){
                return a.dialect < b.dialect;
            }
            return a.speaker < b.speaker;
        }
        friend bool operator>(const NesoraLanguageCode& a, const NesoraLanguageCode& b) { return b < a; }             // 条件1より
        friend bool operator<=(const NesoraLanguageCode& a, const NesoraLanguageCode& b) { return !(b < a); }         // 条件4より
        friend bool operator>=(const NesoraLanguageCode& a, const NesoraLanguageCode& b) { return b <= a; }           // 条件2より
        friend bool operator==(const NesoraLanguageCode& a, const NesoraLanguageCode& b) { return a <= b && b >= a; } // 条件5より
        friend bool operator!=(const NesoraLanguageCode& a, const NesoraLanguageCode& b) { return !(a == b); }        // 条件3より

    };

    struct NesoraWord{
        std::vector<uint8_t> buffer;
        std::string word;
        bool enabled = false;
        bool error = false;
    };

    class NesoraDictionary{
    private:
        size_t maxLenght = 0;
        NesoraLanguageCode language_code;
        std::map<std::string, NesoraWord> dictionary;

    public:

        NesoraDictionary();

        friend bool operator<(const NesoraDictionary& a, const NesoraDictionary& b) {
            return a.language_code < b.language_code;
        }
        friend bool operator>(const NesoraDictionary& a, const NesoraDictionary& b) { return b < a; }             // 条件1より
        friend bool operator<=(const NesoraDictionary& a, const NesoraDictionary& b) { return !(b < a); }         // 条件4より
        friend bool operator>=(const NesoraDictionary& a, const NesoraDictionary& b) { return b <= a; }           // 条件2より
        friend bool operator==(const NesoraDictionary& a, const NesoraDictionary& b) { return a <= b && b >= a; } // 条件5より
        friend bool operator!=(const NesoraDictionary& a, const NesoraDictionary& b) { return !(a == b); }        // 条件3より

        void add(std::string word, NesoraWord nsword);
        bool isWord(const std::string &word);
        NesoraWord searchWord(const std::string &word);
        size_t GetMaxLenght() { return maxLenght; }
        void SetLanguageCode(const NesoraLanguageCode &nslc) { language_code = nslc; }
        NesoraLanguageCode GetLanguageCode() { return language_code; }

        // NesoraWord operator[](const std::string &idx) { return dictionary[idx]; }
        const NesoraWord &operator[](const std::string &idx) const { return dictionary.at(idx); }

    };

    class NesoraInterpreter {
    private:
        std::string string_buffer = "";
        NesoraDictionary dictionary;

    public:
        NesoraInterpreter();
        NesoraInterpreter(const NesoraDictionary&);

        void SetDictionaly(const NesoraDictionary &nsdic) { dictionary = nsdic; }

        std::vector<NesoraWord> I_InterpretYourPoem(const std::string &);
    };

    
}// namespace nesora

namespace nesora_literals {
    // 0xFFFFFFFF'FFFFFFFF'FFFFFFFF'FFFFFFFF_NSLC
    // 16進数 言語'方言'話者 のID
    inline nesora::NesoraLanguageCode operator""_NSLC(const char* val){
        std::string str = val;
        nesora::NesoraLanguageCode nslc;
        if (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X") {      // とりあえず符号無し16進数のみ許可
            str.erase(0, 2);                                             // 接頭辞 (0x) の除去
            str.erase(std::remove(std::begin(str), std::end(str), '\''), // 区切り文字 (') を後ろに追いやって
                        std::end(str));                                  // 除去する
            int len = std::size(str);
            if (len > 24)
                nslc.language = std::stoull(str.substr(0, (std::max)(0, len - 24)), nullptr, 16); // 前半8文字分を16進数で変換
            if (len > 16)
                nslc.dialect = std::stoull(str.substr((std::max)(0, len - 24), (std::max)(0, len - 16)), nullptr, 16); // 真ん中8文字分を16進数で変換
            nslc.speaker = std::stoull(str.substr((std::max)(0, len - 16)), nullptr, 16); // 後半16文字分を16進数で変換
        }
        return nslc;
    }
} // namespace nesora_literals
using namespace nesora_literals;

#endif //NESORA_INTERPRETER_H

