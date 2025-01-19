#ifndef NESORA_PLUGIN_HEADER_H
#define NESORA_PLUGIN_HEADER_H

#include <memory>
#include <wx/wx.h>

typedef std::unique_ptr<wxFrame> PluginInterfaceCreateFunction();

#endif //NESORA_PLUGIN_HEADER_H