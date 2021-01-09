﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "Application.hpp"
#include "MainFrame.hpp"

namespace wxgit {
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
  mainFrame_ = new MainFrame();
  mainFrame_->Show(true);
  return true;
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
