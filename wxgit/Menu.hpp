﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Menu
  : public wxMenu
{
  using super = wxMenu;

 public:
  enum class Id {
    TOP = wxID_HIGHEST, 

    FILE_QUIT, 

    REPOSITORY_CLONE, 
    REPOSITORY_ADD, 
    REPOSITORY_REMOVE, 

    BOTTOM
  };

 public:
  Menu() = default;
  ~Menu() override = default;

  wxMenuItem* append(Id id);

  static const char* GetText(Id id);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
