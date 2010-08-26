#ifndef ENTITIES_HPP
#define	ENTITIES_HPP

#include "Managers/EventManager.hpp"
#include "Systems/GraphicSystem.hpp"
#include "Core/Types.hpp"
#include "Core/Utils.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

using boost::property_tree::ptree;
using namespace std;

class Entity : private boost::noncopyable
{
    protected:
        string mEntityName;
        string mEntityMesh;
        bool mDrawable;

        // TODO: Move entity object to entity class only
        Ogre::Entity *mEntity;
        Ogre::SceneNode *mNode;

        float *parseArguments(const string &argName);

    public:
        virtual ~Entity();
        void _defaultLoader(string EntityName);
        virtual void _loadData() = 0;  // From info-file
        virtual void update(float elapsed) = 0;
        virtual string type() = 0;

        template<typename EventType>
        void AddBehavior(const string &eventName, const typename EventType::SignatureSlotType &eventSlot)
        {
            CONNECT(EventType, eventName, eventSlot);
        }

        template<typename EventType>
        void RemoveBehavior()
        {
            // TODO: Implement me!
        }

        const string getName() const;
        const string getMeshName() const;
        bool isDrawable() const;

        Ogre::SceneNode *getNode() const;
        Ogre::Entity *getEntity() const;
        
        const vec3 &getPosition() const;
        const quat &getOrientation() const;
        const vec3 &getScale() const;

        void setName(const string &entityName);
        void setMeshName(const string &meshPath);
        void setDrawable(bool state);
        
        void setMaterial(const string &matName, const string &group = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        void setPosition(const vec3 pos = vec3());
        void setRotation(const quat rot = quat());
        void setScale(const vec3 scale = vec3());
};


#endif	/* ENTITIES_HPP */
