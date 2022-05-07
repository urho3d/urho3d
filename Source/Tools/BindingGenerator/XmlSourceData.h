// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

#include <PugiXml/pugixml.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace SourceData
{
    // All classes and structs
    extern std::unordered_map<std::string, pugi::xml_node> classesByID_; // id -> compounddef

    // All classes and structs from Urho3D namepace
    extern std::unordered_map<std::string, pugi::xml_node> classesByName_; // name -> compounddef

    // Huge table with all members of all classes and structs
    extern std::unordered_map<std::string, pugi::xml_node> members_; // id -> memberdef

    // All enums from Urho3D namepace
    extern std::unordered_map<std::string, pugi::xml_node> enums_; // name -> memberdef

    // List of all defines. Used to detect that some function is a #define actually
    extern std::vector<std::string> defines_;

    // Namespace Urho3D contains enums, global functions and global variables
    extern pugi::xml_node namespaceUrho3D_; // compounddef from file namespace_urho3_d.xml

    // All usings from namespace Urho3D
    extern std::vector<pugi::xml_node> usings_; // memberdefs

    // Header files with @nobindfile mark at the beginning
    extern std::vector<std::string> ignoredHeaders_;

    // Init all variables above
    void LoadAllXmls(const std::string& dir);
}
