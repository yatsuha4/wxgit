﻿/***********************************************************************//**
	@file
***************************************************************************/
#pragma once

namespace wxgit {
namespace git {
/***********************************************************************//**
	@brief 
***************************************************************************/
class Commit {
 private:
  git_commit* commit_;
  wxString message_;
  SignaturePtr committer_;
  wxDateTime time_;

 public:
  Commit(git_commit* commit);
  ~Commit();

  WXGIT_GETTER(Message, message_);
  WXGIT_GETTER(Committer, committer_);
  WXGIT_GETTER(Time, time_);
};
/***********************************************************************//**
	$Id$
***************************************************************************/
}
}
