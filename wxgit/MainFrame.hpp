﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

#include "wxgit/Serializable.hpp"

namespace wxgit {
/***********************************************************************//**
	@brief 
***************************************************************************/
class MainFrame
  : public wxFrame, 
    public Serializable
{
  using super = wxFrame;

 private:
  Application* application_;
  wxStatusBar* statusBar_;
  wxAuiManager auiManager_;
  outliner::Outliner* outliner_;
  history::History* history_;
  FileList* fileList_;

 public:
  MainFrame(Application* application);
  ~MainFrame() override;

  WXGIT_GETTER(Outliner, outliner_);
  WXGIT_GETTER(History, history_);
  WXGIT_GETTER(FileList, fileList_);

  wxXmlNode* serialize() const override;
  bool deserialize(const wxXmlNode* xml) override;

  WXGIT_GET_SERIAL_NAME(MainFrame);

 private:
  void setupMenuBar();
  void setupToolBar();

  void onSelectMenu(wxCommandEvent& event);
  void onClose(wxCloseEvent& event);

  void addRepository();
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
