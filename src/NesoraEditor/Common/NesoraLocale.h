#ifndef NESORA_COMMON_LOCALE_H
#define NESORA_COMMON_LOCALE_H

#include "NesoraReadNSML.h"

namespace nesora {
    namespace locale{

        extern NesoraMarkupLanguage language;



    }//namespace locale
}//namespace nesora

inline std::string operator"" _ns_locale(const char* key, std::size_t len) {
    return nesora::locale::language[key];
}

#endif //NESORA_COMMON_LOCALE_H
