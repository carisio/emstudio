/*
 * AboutDialog.h
 *
 *  Created on: 3 de fev de 2018
 *      Author: caris
 */

#ifndef SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_ABOUTDIALOG_H_
#define SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_ABOUTDIALOG_H_

/**********************************************************************
 * Description:     AboutDialog header
 * Author(s):       zoom
 * Last modif.:     23/10/08
 * Licence:         linkware, just put a reference to askorn.free.fr
*********************************************************************/
#include "emstudio/util/resources/UtilResource.h"
#include "emstudio/moderator/ConfigApp.h"
#include <wx/wx.h>
#include <wx/bitmap.h>
#include <wx/statline.h>
#include <wx/mstream.h>

//Some vars
//wxString wsAppName = wxT("Mascott");
wxString wsAppMaker = _("CompanyName");
wxString wsAppCopyDate = _("2008");


enum
{
    ID_ABOUT_WXBUTTONOK = 4101,
    ID_ABOUT_WXBUTTONREGISTER = 4102,

};


//My AboutDialog class
class AboutDialog : public wxDialog
{
public:
	AboutDialog(wxWindowID id);
	void OnClose( wxCommandEvent& event );
	void OnBoutonOK( wxCommandEvent& event );
	virtual ~AboutDialog() {}
private:
   //DECLARE_EVENT_TABLE();
};

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
AboutDialog::AboutDialog(wxWindowID id)
                  : wxDialog(NULL,id,_("About EM Studio"),wxDefaultPosition, wxSize(300,425), wxDEFAULT_DIALOG_STYLE,wxT("myAboutFrame")) {
	Connect(ID_ABOUT_WXBUTTONOK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AboutDialog::OnBoutonOK));
	Connect(wxEVT_CLOSE_WINDOW, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AboutDialog::OnClose));

	wxString appName = "EM Studio [" + AppType + "] v. " + wxString::Format(wxT("%i"),AppV1) + "." + wxString::Format(wxT("%i"),AppV2) + "." + wxString::Format(wxT("%i"),AppV3);

    //Init all image handlers...
    wxInitAllImageHandlers();

    //Load bg picture
    wxStaticBitmap *mySBBackGround = new wxStaticBitmap(this, -1, UtilResource::GetBitmap("about"), wxPoint(0,-20));

    //Write the application name
    wxStaticText *myAppName = new wxStaticText(this, -1, appName, wxPoint(12,150), wxSize(200,40), 0, appName);
    myAppName->SetForegroundColour(wxColour(255, 0, 0));

    wxString appInfo = wxString("Developed by Leandro Carísio Fernandes and Antonio José Martins Soares.\n\n") +
    				   "Contact: carisio at gmail.com, martins at ene.unb.br\n\n" +
					   "https://doi.org/10.1109/MAP.2013.6474511";

    //Write the app version
    wxStaticText *myAppInfo = new wxStaticText(this, -1, appInfo, wxPoint(myAppName->GetPosition().x,myAppName->GetPosition().y+35), wxSize(20,100), 0, appInfo);
    myAppInfo->Wrap((int)(this->GetSize().x-2*15));

    //Static line
    wxStaticLine *myStaticLine = new wxStaticLine(this, -1, wxPoint(0,this->GetSize().y-78), wxSize(this->GetSize().x,2), wxLI_HORIZONTAL, wxT("staticLine"));

    //Button 'OK'
    wxButton *myButtonOK = new wxButton(this, ID_ABOUT_WXBUTTONOK, _("OK"), wxPoint(this->GetSize().x-70-15,this->GetSize().y-50-15), wxSize(70,23), 0, wxDefaultValidator, wxT("myBOK"));

}
//---------------------------------------------------------------------------------------------------------
void
AboutDialog::OnClose( wxCommandEvent& WXUNUSED(event) )
{
   Close(TRUE);
   Destroy();
}


//---------------------------------------------------------------------------------------------------------
void
AboutDialog::OnBoutonOK( wxCommandEvent& WXUNUSED(event) )
{
   Close(TRUE);
   Destroy();
}
//---------------------------------------------------------------------------------------------------------

#endif /* SRC_EMSTUDIO_GUI_FRAMESANDPANELS_MAIN_ABOUTDIALOG_H_ */
