/***************************************************************
 * Name:      GrafyMain.h
 * Purpose:   Defines Application Frame
 * Author:    Maja Darczuk i Jan Walkiewicz ()
 * Created:   2024-12-19
 * Copyright: Maja Darczuk i Jan Walkiewicz ()
 * License:
 **************************************************************/

#ifndef GRAFYMAIN_H
#define GRAFYMAIN_H

//(*Headers(GrafyDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/filedlg.h>
#include <wx/radiobox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)


class GrafyDialog: public wxDialog
{
    public:

        GrafyDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~GrafyDialog();
        wxBitmap backgroundImage;

    private:

        //(*Handlers(GrafyDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnButton5Click(wxCommandEvent& event);
        void OnButton6Click(wxCommandEvent& event);
        void OnCheckBox1Click(wxCommandEvent& event);
        void OnCheckBox2Click(wxCommandEvent& event);
        void OnCheckBox3Click(wxCommandEvent& event);
        void OnButton6Click1(wxCommandEvent& event);
        void OnRadioBox1Select(wxCommandEvent& event);
        //*)

        //(*Identifiers(GrafyDialog)
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON2;
        static const long ID_RADIOBOX1;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        //*)

        //(*Declarations(GrafyDialog)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxButton* Button4;
        wxButton* Button5;
        wxButton* Button6;
        wxFileDialog* FileDialog1;
        wxRadioBox* RadioBox1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxTextCtrl* TextCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // GRAFYMAIN_H
