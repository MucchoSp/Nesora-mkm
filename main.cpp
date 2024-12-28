#include <iostream>
#include "src/Nesora/Nesora.h"
#include <wx/wx.h>


class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(
        wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxFrameNameStr
        );
 
private:
    wxMenu *menuFile;
    wxMenu *menuHelp;
    wxMenuBar *menuBar;

    wxPanel* panel;
    wxTextCtrl* textCtrl;
    wxButton* button_uc;
    wxButton* button_lc;

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum {
    ID_Hello = 1
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame(nullptr, wxID_ANY, "My test app");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(
    wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name
) : wxFrame(parent, id, title, pos, size, style, name) {
    menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    //パネル（親widgetはこのthisつまりmyFrame）
    panel = new wxPanel(this, wxID_ANY);

    //テキストコントロール（親widgetはpanel）
    textCtrl = new wxTextCtrl(panel, wxID_ANY);

    //ボタン（親widgetはpanel）
    button_uc = new wxButton(panel, wxID_ANY, "UpperCase");
    button_lc = new wxButton(panel, wxID_ANY, "LowerCase");

    //サイザー（垂直方向に詰める）
    auto vsizer = new wxBoxSizer(wxVERTICAL);

    //サイザー（水平方向に詰める）
    auto hsizer = new wxBoxSizer(wxHORIZONTAL);

    //レイアウトを整える
    panel->SetSizer(vsizer);

    vsizer->Add(textCtrl, 0, wxALIGN_CENTER);
    vsizer->Add(hsizer, 0, wxALIGN_CENTER);
    hsizer->Add(button_uc, 0, wxALIGN_CENTER);
    hsizer->Add(button_lc, 0, wxALIGN_CENTER);

    //UpperCaseボタンを押したら、TextCtrlの文字列をUpperCaseする
    button_uc->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        //ダイアログ（親widgetはこのthisつまりmyFrame）
        auto dialog = wxMessageDialog(this, "テキストをUpperCaseしますか？", "タイトル", wxCANCEL);

        //ダイアログを表示して、OKボタンを押したらテキストの変換を実施する
        if(dialog.ShowModal() == wxID_OK) {
            auto text = textCtrl->GetValue();
            text.UpperCase();
            textCtrl->SetValue(text);
        }
    });

    //LowerCaseボタンを押したら、TextCtrlの文字列をLowerCaseする
    button_lc->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        //ダイアログ（親widgetはこのthisつまりmyFrame）
        auto dialog = wxMessageDialog(this, "テキストをlowerCaseしますか？", "タイトル", wxCANCEL);

        //ダイアログを表示して、OKボタンを押したらテキストの変換を実施する    
        if(dialog.ShowModal() == wxID_OK) {
            auto text = textCtrl->GetValue();
            text.LowerCase();
            textCtrl->SetValue(text);
        }
    });

}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event) {
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
