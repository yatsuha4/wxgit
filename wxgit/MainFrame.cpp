﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/Application.hpp"
#include "wxgit/FileList.hpp"
#include "wxgit/MainFrame.hpp"
#include "wxgit/Menu.hpp"
#include "wxgit/RepoBrowser.hpp"
#include "wxgit/git/Repository.hpp"
#include "wxgit/history/History.hpp"
#include "wxgit/outliner/Outliner.hpp"
#include "wxgit/outliner/Repository.hpp"

namespace wxgit {
/***********************************************************************//**
	@brief 
***************************************************************************/
enum {
  LAYER_HISTORY, 
  LAYER_OUTLINER
};
/***********************************************************************//**
	@brief コンストラクタ
***************************************************************************/
MainFrame::MainFrame(Application* application)
  : super(nullptr, wxID_ANY, Application::Version.GetName(), 
          wxDefaultPosition, wxSize(960, 640)), 
    application_(application), 
    statusBar_(CreateStatusBar()), 
    auiManager_(this), 
    outliner_(new outliner::Outliner(this)), 
    history_(new history::History(this)), 
    fileList_(new FileList(this))
{
  setupMenuBar();
  setupToolBar();
  //notebook_->AddPage(repoBrowser_, "Repository");
  statusBar_->PushStatusText(Application::Version.ToString());
  auiManager_.AddPane(outliner_, 
                      wxAuiPaneInfo().
                      Name("Outliner").
                      Caption("Outliner").
                      CloseButton(false).
                      Left().
                      BestSize(200, 800).
                      Layer(LAYER_OUTLINER));
  auiManager_.AddPane(history_, 
                      wxAuiPaneInfo().
                      Name("History").
                      Caption("History").
                      CloseButton(false).
                      CenterPane().
                      Layer(LAYER_HISTORY));
  auiManager_.AddPane(fileList_, 
                      wxAuiPaneInfo().
                      Name("FileList").
                      Caption("FileList").
                      CloseButton(false).
                      BestSize(800, 800).
                      Bottom());
  auiManager_.Update();
  Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
MainFrame::~MainFrame() {
  auiManager_.UnInit();
}
/***********************************************************************//**
	@brief 
***************************************************************************/
wxXmlNode* MainFrame::serialize() const {
  auto xml = Serializable::serialize();
  xml->AddChild(outliner_->serialize());
  return xml;
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool MainFrame::deserialize(const wxXmlNode* xml) {
  if(Serializable::deserialize(xml)) {
    for(auto child = xml->GetChildren(); child; child = child->GetNext()) {
      if(child->GetName() == outliner::Outliner::GetSerialName()) {
        outliner_->deserialize(child);
      }
      else {
        Warning("illegal node", child);
      }
    }
    return true;
  }
  return false;
}
/***********************************************************************//**
	@brief メニューバーを設定する
***************************************************************************/
void MainFrame::setupMenuBar() {
  auto menuBar = new wxMenuBar();
  {
    auto menu = new Menu();
    menu->append(Menu::Id::FILE_QUIT);
    menuBar->Append(menu, "File");
  }
  {
    auto menu = new Menu();
    menu->append(Menu::Id::REPOSITORY_ADD);
    menu->append(Menu::Id::REPOSITORY_CLONE);
    menuBar->Append(menu, "Repository");
  }
  SetMenuBar(menuBar);
  Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::onSelectMenu, this);
}
/***********************************************************************//**
	@brief ツールバーを設定する
***************************************************************************/
void MainFrame::setupToolBar() {
  auto toolBar = CreateToolBar(wxTB_DEFAULT_STYLE | wxTB_TEXT);
  toolBar->AddTool(static_cast<int>(Menu::Id::REPOSITORY_CLONE), 
                   Menu::GetText(Menu::Id::REPOSITORY_CLONE), 
                   wxArtProvider::GetBitmap(wxART_COPY));
  toolBar->AddTool(static_cast<int>(Menu::Id::REPOSITORY_ADD), 
                   Menu::GetText(Menu::Id::REPOSITORY_ADD), 
                   wxArtProvider::GetBitmap(wxART_NEW));
  toolBar->Realize();
  Bind(wxEVT_TOOL, &MainFrame::onSelectMenu, this);
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void MainFrame::onSelectMenu(wxCommandEvent& event) {
  switch(static_cast<Menu::Id>(event.GetId())) {
  case Menu::Id::FILE_QUIT:
    Close();
    break;
  case Menu::Id::REPOSITORY_ADD:
    addRepository();
    break;
  default:
    break;
  }
}
/***********************************************************************//**
	@brief 
***************************************************************************/
void MainFrame::onClose(wxCloseEvent& event) {
  if(event.CanVeto()) {
    application_->savePreference();
    Destroy();
  }
}
/***********************************************************************//**
	@brief ローカルリポジトリを追加する
***************************************************************************/
void MainFrame::addRepository() {
  wxDirDialog dialog(this, "Select repository");
  if(dialog.ShowModal() == wxID_OK) {
    auto repository = new outliner::Repository(dialog.GetPath());
    outliner_->appendNode(repository);
    history_->showCommits(repository->getRepository()->getCommits());
  }
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
