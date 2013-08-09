OgreBatchConverter

- Contributed by Carlo Carollo. Converts multiple Ogre .mesh.xml files (also from 
  subdirectories) by invoking the OgreImporter tool.
- Enable in build by uncommenting at the bottom of the Urho3D root CMakeLists.txt

OgreMaxscriptExport

- Contributed by Vladimir Pobedinsky. A modified version of the Maxscript 
  Exporter from the Ogre SDK that will import Ogre .mesh.xml files (for feeding
  into OgreImporter) and materials in Urho3D .xml format.

CharacterDemo

- A moving character example, with 1st/3rd person camera. Creates the same scene as
  the TestScene script application.
- Enable in build by uncommenting at the bottom of the Urho3D root CMakeLists.txt

LuaScript

- Lua bindings for Urho3D. Contributed by Aster Jian. Uncomment ENABLE_LUA near
  the bottom of Urho3D's root CMakeLists.txt to enable.
  
