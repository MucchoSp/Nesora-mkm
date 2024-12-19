#include "NesoraStringFormat.h"

namespace nesora{

NesoraStringFormat::NesoraStringFormat(){

}

NesoraStringFormat::NesoraStringFormat(const std::string& str){

}

NesoraStringFormat:: NesoraStringFormat(uint32_t lang_code, uint16_t dial_code, std::string str){
    language_code = lang_code;
    dialect_code = dial_code;
    string_buffer = str;
}
}