#include <iostream>
#include "src/Nesora/Nesora.h"


nesora::NesoraDictionary testDictionary(){
    nesora::NesoraDictionary dictionary;
    nesora::NesoraWord word;

    dictionary.SetLanguageCode(0x00000000'00000000'0000000000000000_NSLC);

    word.buffer.push_back(0);
    word.word = "_";
    word.enabled = true;
    dictionary.add(" ", word);

    word.buffer.push_back(1);
    word.word = "hell";
    dictionary.add("hell", word);

    word.buffer.push_back(2);
    word.word = "hello";
    dictionary.add("hello", word);

    word.buffer.push_back(3);
    word.word = "world";
    dictionary.add("world", word);

    word.buffer.push_back(4);
    word.word = "!";
    dictionary.add("!", word);

    return dictionary;
}


int main(int, char**){
    std::cout << "Hello, from Nesora!" << std::endl;

    nesora::NesoraInterpreter interpreter(testDictionary());
    std::vector<nesora::NesoraWord> output = interpreter.I_InterpretYourPoem("hello world!");
    std::cout << "Finish interpret" << std::endl;

    for(auto a : output){
        std::cout << a.word;
    }
    std::cout << std::endl;
    for(auto a : output){
        std::cout << " 0x" << std::hex << unsigned(a.buffer.back());
    }
    
    std::cout << std::endl << "Finish!" << std::endl;

    return 0;
}

