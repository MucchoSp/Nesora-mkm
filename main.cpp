#include <iostream>
#include "src/Nesora/Nesora.h"
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
        : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar(menuBar);
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

/*
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
//*/
