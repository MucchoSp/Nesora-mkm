#include "NesoraInterpreter.h"

namespace nesora{

    NesoraDictionary::NesoraDictionary() {

    }

    void NesoraDictionary::add(std::string word, NesoraWord nsword) {
        if(nsword.enabled) {
            maxLenght = std::max(maxLenght, word.length());
            dictionary[word] = nsword;
        }
    }

    bool NesoraDictionary::isWord(const std::string& word) {
        return dictionary.find(word) != dictionary.end();
    }

    NesoraWord NesoraDictionary::searchWord(const std::string& word){
        std::map<std::string, NesoraWord>::iterator work = dictionary.find(word);
        if(work != dictionary.end())
            return work->second;
        NesoraWord zero;
        zero.enabled = false;
        return zero;
    }




    NesoraInterpreter::NesoraInterpreter() {

    }

    NesoraInterpreter::NesoraInterpreter(const NesoraDictionary& dic) {
        dictionary = dic;
    }

    std::vector<NesoraWord> NesoraInterpreter::I_InterpretYourPoem(const std::string& poem) {
        std::vector<NesoraWord> out;

        size_t stringLen = poem.length();
        size_t start = 0;
        std::cout << "Start interpret" << std::endl;
        while(start < poem.length()) {
            for (size_t i = std::min(dictionary.GetMaxLenght(), poem.length() - start) ; i > 0;i--) {
                NesoraWord word = dictionary.searchWord(poem.substr(start, i));
                if(word.enabled){
                    out.push_back(word);
                    start += i;
                    break;
                }
                if(i <= 1){
                    NesoraWord errorWord;
                    errorWord.word = poem[start];
                    errorWord.error = true;
                    out.push_back(errorWord);
                    start++;
                    break;
                }
            }
        }

        return out;
    }
}

