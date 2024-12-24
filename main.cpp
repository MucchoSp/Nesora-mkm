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

    std::vector<nesora::nsfloat> waves(48000 * 5);
    for (int i = 0; i < waves.size();i++) {
        waves[i] = std::sin((float)i * 2.0 * nesora::ns_pi / 48000.0 * 440.0) * 0.5;
    }
    nesora::NesoraWaveFile wavefile;
    wavefile.SetWave(waves);
    wavefile.save("generated/test_A.wav");

    return 0;
}

