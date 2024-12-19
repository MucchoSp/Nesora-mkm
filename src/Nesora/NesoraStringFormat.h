#include <string>
#include <cstdint>
#include <vector>
#include "NesoraInterpreter.h"

namespace nesora{

    class NesoraStringFormat {
    private:
        uint32_t language_code = 0;
        uint16_t dialect_code = 0;
        std::string string_buffer = "";
    public:
        NesoraStringFormat();
        NesoraStringFormat(const std::string&);
        NesoraStringFormat(uint32_t, uint16_t = 0, std::string = "");
    };

    class NesoraLanguage{
    private:

    public:
    };
}