﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace git {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Signature {
 public:
  wxString name;
  wxString email;
  wxDateTime when;

 public:
  Signature() = default;
  Signature(const git_signature* signature);
  ~Signature() = default;
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}