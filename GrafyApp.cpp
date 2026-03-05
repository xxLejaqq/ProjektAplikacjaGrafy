/***************************************************************
 * Name:      GrafyApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Maja Darczuk i Jan Walkiewicz ()
 * Created:   2024-12-19
 * Copyright: Maja Darczuk i Jan Walkiewicz ()
 * License:
 **************************************************************/

#include "GrafyApp.h"

//(*AppHeaders
#include "GrafyMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(GrafyApp);

bool GrafyApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	GrafyDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
