#include "StateMachineComponents.h"
#include <Urho3D/Resource/XMLElement.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/DecalSet.h>
#include <Urho3D/Graphics/Technique.h>
#include <Urho3D/Graphics/Drawable.h>
#include <Urho3D/Graphics/AnimatedModel.h>

#include <map>



using namespace Urho3D;



ProjectNMetaData::ProjectNMetaData(Urho3D::Context* context)
:Component(context)
,_groundPathClickable(false)
{}

ProjectNMetaData::~ProjectNMetaData()
{}

bool ProjectNMetaData::LoadXML(const Urho3D::XMLElement& source)
{
    if (!Component::LoadXML(source)) {
        return false;
    }
    
    Urho3D::XMLElement compElem = source.GetChild("attribute");
    while (compElem)
    {
        Urho3D::String name = compElem.GetAttribute("name");
        Urho3D::String value = compElem.GetAttribute("value");
            
        if (name == "groundPathClickable") {
            _groundPathClickable = value == "True";
        }
        else if (name == "clicksDisabled") {
            _clicksDisabled = value == "True";
        }
        else if (name == "isRoof") {
            _isRoof = value == "True";
        }
        else if (name == "gameObjectType") {
            _gameObjectType = atoi(value.CString());
        }
        else if (name == "gameObjectId") {
            _gameObjectId = value;
        }
        else if (name == "gameObjectElementId") {
            _gameObjectElementId = value;
        }
        
        compElem = compElem.GetNext("attribute");
    }
    
    return true;
}

void ProjectNMetaData::RegisterObject(Urho3D::Context* context)
{
    context->RegisterFactory<ProjectNMetaData>("ProjectNMetaData");
}

void ProjectNMetaData::setRoofVisible(bool visible, std::map<Urho3D::SharedPtr<Urho3D::Material>, Urho3D::SharedPtr<Urho3D::Material>> &roofMaterials, std::map<Urho3D::SharedPtr<Urho3D::Technique>, Urho3D::SharedPtr<Urho3D::Technique>> &roofTechniques)
{
    if (_roofVisible == visible) {
        return;
    }
    _roofVisible = visible;
    
    
    StaticModel *model = GetComponent<StaticModel>();
    
    if (visible) {
        for (unsigned i = 0; i < model->GetBatches().Size(); i++) {
            model->SetMaterial(i, _visibleMaterials[i]);
        }
        return;
    }
    
    DecalSet *decals = GetComponent<DecalSet>();
    if (decals) {
        decals->RemoveAllDecals();
    }
    if (_invisibleMaterials.size() != 0) {
        for (unsigned i = 0; i < model->GetBatches().Size(); i++) {
            model->SetMaterial(i, _invisibleMaterials[i]);
        }
        return;
    }
    
    for (unsigned i = 0; i < model->GetBatches().Size(); i++)
    {
        SharedPtr<Material> material = model->GetBatches()[i].material_;
        _visibleMaterials.push_back(material);
        
        auto replaceMaterial = roofMaterials.find(material);
        if (replaceMaterial != roofMaterials.end()) {
            // already have necessary material
            model->SetMaterial(i, replaceMaterial->second);
        }
        else {
            
            SharedPtr<Material> newMaterial = material->Clone();
            
            for (unsigned t = 0; t < newMaterial->GetNumTechniques(); t++) {
                
                SharedPtr<Technique> technique = SharedPtr<Technique>(newMaterial->GetTechnique(t));
                SharedPtr<Technique> newTechnique = nullptr;
                auto replaceTechnique = roofTechniques.find(technique);
                
                if (replaceTechnique != roofTechniques.end()) {
                    newMaterial->SetTechnique(t, replaceTechnique->second);
                }
                else {
                    newTechnique = newMaterial->GetTechnique(t)->Clone();
                    
                    auto names = newTechnique->GetPassNames();
                    for (unsigned p = 0; p < names.Size(); p++) {
                        if (names[p] == "shadow") {
                            continue;
                        }
                        newTechnique->RemovePass(names[p]);
                    }
                    roofTechniques[technique] = newTechnique;
                    newMaterial->SetTechnique(t, newTechnique);
                }
            }
            
            model->SetMaterial(i, newMaterial);
            roofMaterials[material] = newMaterial;
            _invisibleMaterials.push_back(newMaterial);
        }
    }
    
    
//    GetNode()->SetEnabled(visible);
}



GameSceneObject::GameSceneObject(const Urho3D::String &objectId, int objectType)
:_objectId(objectId)
,_objectType(objectType)
{}

void GameSceneData::analyseNode(Urho3D::Node *node)
{
    auto metadata = node->GetComponent<ProjectNMetaData>();
    if (metadata) {
        if (metadata->_isRoof) {
            _roofs.push_back(node);
        }
        
        if (metadata->_gameObjectType != 0) {
            
            auto iterator = _objects.find(metadata->_gameObjectId);
            std::shared_ptr<GameSceneObject> object = nullptr;
            if (iterator != _objects.end()) {
                object = iterator->second;
            }
            else {
                object = std::shared_ptr<GameSceneObject>(new GameSceneObject(metadata->_gameObjectId, metadata->_gameObjectType));
                _objects[metadata->_gameObjectId] = object;
            }
            
            GameSceneObjectNode objectNode;
            objectNode._node = node;
            object->_nodes[metadata->_gameObjectElementId] = objectNode;
        }
    }
    
    for (unsigned i = 0; i < node->GetNumChildren(); i++) {
        analyseNode(node->GetChild(i));
    }
}

void GameSceneData::analyse(Urho3D::Scene *scene)
{
    analyseNode(scene);
}


