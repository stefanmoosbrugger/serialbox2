//===-- Core/FieldMap.cpp -----------------------------------------------------------*- C++ -*-===//
//
//                                    S E R I A L B O X
//
// This file is distributed under terms of BSD license.
// See LICENSE.txt for more information
//
//===------------------------------------------------------------------------------------------===//
//
/// \file
/// This file implements the field map which stores the meta-information of each field.
///
//===------------------------------------------------------------------------------------------===//

#include "serialbox/Core/FieldMap.h"

namespace serialbox {

json::json FieldMap::toJSON() const {
  json::json jsonNode;

  if(empty())
    return jsonNode;

  for(const_iterator it = this->begin(), end = this->end(); it != end; ++it)
    jsonNode["field_map"][it->first] = it->second.toJSON();

  return jsonNode;
}

void FieldMap::fromJSON(const json::json& jsonNode) {
  clear();

  if(jsonNode.is_null() || jsonNode.empty())
    return;
  
  if(!jsonNode.count("field_map"))
    throw Exception("cannot create FieldMap: no node 'field_map'");

  for(auto it = jsonNode["field_map"].begin(), end = jsonNode["field_map"].end(); it != end; ++it) {
    bool insertSuccess = false;
    
    try {
      insertSuccess = insert(it.key(), it.value());      
    } catch(Exception& e) {
      throw Exception("cannot insert node '%s' in FieldMap: JSON node ill-formed: %s", it.key(),
                      e.what());
    }

    if(!insertSuccess)
      throw Exception("cannot insert node '%s' in FieldMap: node already exists", it.key());
  }
}

std::ostream& operator<<(std::ostream& stream, const FieldMap& s) {
  return (stream << "FieldMap = " << s.toJSON().dump(4));
}

} // namespace serialbox
