﻿/***********************************************************************//**
	@file
***************************************************************************/
#include "wxgit/Serializable.hpp"

namespace wxgit {
/***********************************************************************//**
	@brief シリアライズ
***************************************************************************/
wxXmlNode* Serializable::serialize() const {
  return new wxXmlNode(wxXML_ELEMENT_NODE, getSerialName());
}
/***********************************************************************//**
	@brief デシリアライズ
***************************************************************************/
bool Serializable::deserialize(const wxXmlNode* xml) {
  return xml && xml->GetName() == getSerialName();
}
/***********************************************************************//**
	$Id$
***************************************************************************/
}
