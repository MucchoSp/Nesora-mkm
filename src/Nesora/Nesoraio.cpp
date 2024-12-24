#include "Nesoraio.h"

nesora::NesoraWaveFile::NesoraWaveFile(){

}

nesora::NesoraWaveFile::NesoraWaveFile(const std::vector<nsfloat>& in_wave) {
    buffer.resize(in_wave.size());
    std::copy(in_wave.begin(), in_wave.end(), buffer.begin());
}


int nesora::NesoraWaveFile::save(std::string filename) {

    std::ofstream file(filename, std::ios::binary);
    if(!file)
        return 1;

    uint32_t work32 = 0;
    uint16_t work16 = 0;
    uint8_t work8 = 0;

    file << "RIFF";
    auto fileSize = file.tellp();
    work32 = 0;//riff chank size
    file.write((char*)&work32, 4);
    file << "WAVE";

    file << "fmt ";
    work32 = 16;					//format chank size
    file.write((char*)&work32, 4);
    work16 = 1;						//format tag(WAVE_FORMAT_PCM:PCM)
    file.write((char*)&work16, 2);
    file.write((char*)&channelNum, 2);
    file.write((char*)&samplingFrequency, 4);
    work32 = samplingFrequency * channelNum * (bitPerSample / 8);
    file.write((char*)&work32, 4);
    work16 = channelNum * (bitPerSample / 8);
    file.write((char*)&work16, 2);
    file.write((char*)&bitPerSample, 2);
    //fmt チャンクここまで

    std::vector<int16_t> wavedata(buffer.size());
    for(size_t i = 0;i < buffer.size();i++)
        wavedata[i] = (int16_t)(buffer[i] * (INT16_MAX - 1));
    file << "data";
    int padding = 2;
    file.write((char*)&(work32 = wavedata.size() * (channelNum * bitPerSample / 8) + padding), 4);	//data chank size
    file.write((char*)wavedata.data(), wavedata.size() * (bitPerSample / 8));
    file.write((char*)&(work32 = 0), padding);
    //dataチャンクここまで

    work16 = 0;
    file << "LIST";
    auto ListSize = file.tellp();
    file.write((char*)&(work32 = 0), 4);
    file << "INFO";
    //製作者
    std::string workInfoString = metaData.IART;
    if (workInfoString != "") {
        file << "IART";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //依頼者
    workInfoString = metaData.ICMS;
    if (workInfoString != "") {
        file << "ICMS";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //コメント
    workInfoString = metaData.ICMT;
    if (workInfoString != "") {
        file << "ICMT";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //著作権情報
    workInfoString = metaData.ICOP;
    if (workInfoString != "") {
        file << "ICOP";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //作成日
    workInfoString = metaData.ICRD;
    if (workInfoString != "") {
        file << "ICRD";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //ジャンル
    workInfoString = metaData.IGNR;
    if (workInfoString != "") {
        file << "IGNR";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //タイトル
    workInfoString = metaData.INAM;
    if (workInfoString != "") {
        file << "INAM";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //アルバム名
    workInfoString = metaData.IPRD;
    if (workInfoString != "") {
        file << "IPRD";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //ソフトウエア名
    workInfoString = metaData.ISFT;
    if (workInfoString != "") {
        file << "ISFT";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }
    //トラック
    workInfoString = metaData.ITRK;
    if (workInfoString != "") {
        file << "ITRK";
        file.write((char*)&(work32 = workInfoString.size() + (2 - workInfoString.size() % 2)), 4);
        file.write(workInfoString.data(), workInfoString.size());
        file.write((char*)&(work16 = 0), (std::streamsize)(2 - workInfoString.size() % 2));
    }

    auto ListSize_work32 = file.tellp() - ListSize - 4;
    auto ListChankEnd = file.tellp();
    file.seekp(ListSize);
    file.write((char*)&ListSize_work32, 4);
    file.seekp(ListChankEnd);
    //LISTチャンクここまで


    file << "id3 ";
    auto id3Size = file.tellp();
    file.write((char*)&(work32 = 0), 4);

    file << "ID3";
    file.write((char*)&(work16 = 3), 2);
    file.write((char*)&(work8 = 0), 1);
    auto ID3Size = file.tellp();
    file.write((char*)&(work32 = 0), 4);

    int is_ShiftJIS = 1;
    //製作者
    workInfoString = metaData.IART;
    if (workInfoString != "") {
        file << "TPE1";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + is_ShiftJIS)));
        file.write(workInfoString.data(), workInfoString.size());
    }
    //コメント
    workInfoString = metaData.ICMT;
    if (workInfoString != "") {
        file << "COMM";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + dataSize)));
        file.write(workInfoString.data(), workInfoString.size());
    }
    //著作権情報
    workInfoString = metaData.ICOP;
    if (workInfoString != "") {
        file << "TCOP";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + dataSize)));
        file.write(workInfoString.data(), workInfoString.size());
    }
    //作成日
    workInfoString = metaData.ICRD;
    if (workInfoString != "") {
        file << "TDAT";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + dataSize)));
        file.write(workInfoString.data(), workInfoString.size());
    }
    //ジャンル
    workInfoString = metaData.IGNR;
    if (workInfoString != "") {
        file << "TCON";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + dataSize)));
        file.write(workInfoString.data(), workInfoString.size());
    }
    //タイトル
    workInfoString = metaData.INAM;
    if (workInfoString != "") {
        file << "TIT2";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + dataSize)));
        file.write(workInfoString.data(), workInfoString.size());
    }
    //アルバム名
    workInfoString = metaData.IPRD;
    if (workInfoString != "") {
        file << "TALB";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + dataSize)));
        file.write(workInfoString.data(), workInfoString.size());
    }
    //ソフトウエア名
    // workInfoString = info.ISFT;
    // if (workInfoString == "")
    // 	workInfoString = "Nesora I type IV";
    // file << "ISFT";
    // file.write((char*)&(work8 = (workInfoString.size() >> 24) % 0xff), 1);
    // file.write((char*)&(work8 = (workInfoString.size() >> 16) % 0xff), 1);
    // file.write((char*)&(work8 = (workInfoString.size() >> 8) % 0xff), 1);
    // file.write((char*)&(work8 = workInfoString.size() % 0xff), 1);
    // file.write((char*)&(work16 = 0), 2);
    // file.write(workInfoString.data(), workInfoString.size());

    //トラック
    workInfoString = metaData.ITRK;
    if (workInfoString != "") {
        file << "TRCK";
        int dataSize = workInfoString.size() + is_ShiftJIS;
        file.write((char*)&(work8 = (dataSize >> 24) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 16) % 0xff), 1);
        file.write((char*)&(work8 = (dataSize >> 8) % 0xff), 1);
        file.write((char*)&(work8 = dataSize % 0xff), 1);
        file.write((char*)&(work32 = 0), (std::streamsize)((int)(2 + dataSize)));
        file.write(workInfoString.data(), workInfoString.size());
    }

    auto ID3Size_work32 = file.tellp() - ID3Size - 4;
    auto id3Size_work32 = file.tellp() - id3Size - 4;
    auto fileSize_work32 = file.tellp() - fileSize - 4;
    file.seekp(ID3Size);
    file.write((char*)&(work8 = (ID3Size_work32 >> 21) % 0x7f), 1);
    file.write((char*)&(work8 = (ID3Size_work32 >> 14) % 0x7f), 1);
    file.write((char*)&(work8 = (ID3Size_work32 >> 7) % 0x7f), 1);
    file.write((char*)&(work8 = ID3Size_work32 % 0x7f), 1);
    //ID3 チャンクここまで

    file.seekp(id3Size);
    file.write((char*)&id3Size_work32, 4);
    //id3 チャンクここまで

    file.seekp(fileSize);
    file.write((char*)&fileSize_work32, 4);
    //RIFFチャンクここまで


    file.close();


    return 0;
}

void nesora::NesoraWaveFile::SetMetaData(const WaveFileMetaData& waveFileMetaData) {

    metaData = waveFileMetaData;

    return;
}

nesora::WaveFileMetaData nesora::NesoraWaveFile::GetMetaData() {
    return metaData;
}

const nesora::WaveFileMetaData& nesora::NesoraWaveFile::GetMetaData() const {
    return metaData;
}

void nesora::NesoraWaveFile::SetWave(const std::vector<nsfloat> & in_wave) {
    buffer.resize(in_wave.size());
    std::copy(in_wave.begin(), in_wave.end(), buffer.begin());
}

std::vector<nesora::nsfloat> nesora::NesoraWaveFile::GetWave() {
    return buffer;
}

void nesora::NesoraWaveFile::SetSamplingFrequency(const nsuint& smpl) {

    samplingFrequency = smpl;

    return;
}

nesora::nsuint nesora::NesoraWaveFile::GetSamplingFrequency() {
    return samplingFrequency;
}
