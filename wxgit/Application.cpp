﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/Application.hpp"
#include "wxgit/MainFrame.hpp"

namespace wxgit {
const wxVersionInfo Application::Version("wxGit", 0, 0, 1, "", "towerb.com");
/***********************************************************************//**
	@brief 
***************************************************************************/
Application::Application()
  : mainFrame_(nullptr)
{
}
/***********************************************************************//**
	@brief デストラクタ
***************************************************************************/
Application::~Application() {
}
/***********************************************************************//**
	@brief 
***************************************************************************/
bool Application::OnInit() {
  if(!super::OnInit()) {
    return false;
  }
  git_libgit2_init();
  mainFrame_ = new MainFrame();
  mainFrame_->Show(true);
  return true;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
