#include "Nesoraio.h"

nesora::NesoraWaveFile::NesoraWaveFile(){

}

nesora::NesoraWaveFile::NesoraWaveFile(const std::vector<nsfloat>& in_wave){
    buffer.resize(in_wave.size());
    std::copy(in_wave.begin(), in_wave.end(), buffer.begin());
}


int nesora::NesoraWaveFile::save(const std::string & filename) {

    std::ofstream nesoraWaveFile(filename, std::ios::app | std::ios::binary);
    if(!nesoraWaveFile){
        return 1;
    }

    

    return 0;
}

