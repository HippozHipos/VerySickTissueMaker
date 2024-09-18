#pragma once
#include "pch.h"
#include "ECS/SceneObject.h"
#include "BehaviourProvider.h"

namespace be {

    /*!
     * See Related BehaviourManager
     * 
     * \class BehaviourObject
     * \brief Base class for objects with behaviour.
     * 
     * This class can be inherited from by any class in the scene that has behaviour. Any classes that
     * inherit from this class will be able to define the following methods that will be automatically called.
     *
     * 1. PreStart - Called once when the object is created
     * 2. Start - Called once after PreStart
     * 3. Update - Called once every frame
     * 4. UI - Called once every frame. Any ImGui calls need to be made in this function.
     * 5. End - Called once when the object's scope ends (i.e. when it's deleted)
     * 6. PostEnd - Called once after End. The object is destroyed after this.
     *
     * The order in which methods are called depends on the order in which objects are created.
     * Consider the code below:
     * \code
        class ThingWithBehaviour : public BehaviouralSceneObject<ThingWithBehaviour>
        {
        public:
            void PreStart() {}
            void Start() {}
            void Update() {}
            void End() {}
        };

        class NextThingWithBehaviour : public BehaviouralSceneObject<NextThingWithBehaviour>
        {
        public:
            void PreStart() {}
            void Start() {}
            void Update() {}
            void End() {}
        };

        class Example
        {
        public:
            Example()
            {
                ThingWithBehaviour thing;
            }
            NextThingWithBehaviour nextThing;
            ThingWithBehaviour thing1;
        };
     * \endcode
     *
     * In the above code, when `Example` is instantiated, the following would be called in the order listed:
     * 1. nextThing.PreStart() once
     * 2. thing1.PreStart() once
     * 3. thing.PreStart() once
     * 4. thing.End() once
     * 5. nextThing.Start() once
     * 6. thing1.Start() once
     * 7. nextThing.Update() every frame
     * 8. thing1.Update() every frame
     * 9. thing1.End() once
     * 10. nextThing.End() once
     *
     * \par Note:
     * - thing.Start() doesn't get called because thing gets destroyed straight away.
     * - thing.Update() doesn't get called because thing gets destroyed straight away.
     */

    template<typename Derived>
    class BehaviourObject : public SceneContainer, public BehaviourProvider<Derived> {};
}