

#ifndef NESORA_WINDOW_IDS_H
#define NESORA_WINDOW_IDS_H

#include <wx/defs.h>

constexpr int NS_ID_MANAGER_LEN = 100;

enum nesoraEditorID {

    NS_ID_MANAGER_START = wxID_HIGHEST,
    NS_ID_MANAGER_END = NS_ID_MANAGER_START + NS_ID_MANAGER_LEN

};

#endif