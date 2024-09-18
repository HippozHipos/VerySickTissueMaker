#pragma once

#include "pch.h"

#include "ECS/ECS.h"

namespace be {

	//defaults
	template <class T, class = void>
	struct HasStartMethod : std::false_type {};
	template <class T, class = void>
	struct HasUpdateMethod : std::false_type {};
	template <class T, class = void>
	struct HasUIMethod : std::false_type {};
	template <class T, class = void>
	struct HasEndMethod : std::false_type {};


	//has methods
	template <class T>
	struct HasStartMethod<T, std::void_t<decltype(std::declval<T>().Start())>> : std::true_type {};
	template <class T>
	struct HasUpdateMethod<T, std::void_t<decltype(std::declval<T>().Update())>> : std::true_type {};
	template <class T>
	struct HasUIMethod<T, std::void_t<decltype(std::declval<T>().UI())>> : std::true_type {};
	template <class T>
	struct HasEndMethod<T, std::void_t<decltype(std::declval<T>().End())>> : std::true_type {};


    /*!
     * See related: BehaviouralSceneObject
     * 
     * \class BehaviourManager
     * \brief Manages behaviours of scene objects by calling specific behaviour methods.
     *
     * The BehaviourManager class manages the behaviour method invocations of objects that inherit from BehaviouralSceneObject class. 
     * It allows adding, removing, and invoking various methods related to object behaviour, such as PreStart, Start, Update, UI, End, and PostEnd.
     *
     * The behaviour methods are checked using SFINAE (e.g., `HasPreStartMethod`) and are only invoked if they are present in the object.
     *
     * The following behaviour methods can be managed:
     * 1. Start - Called once after PreStart.
     * 2. Update - Called every frame.
     * 3. UI - Called every frame for UI rendering (ImGui).
     * 4. End - Called once when the object is deleted.
     */

    class BehaviourManager
    {
    public:
        /*!
         * \brief Default constructor for BehaviourManager.
         */
        BehaviourManager() = default;

        /*!
         * \brief Adds a behaviour object to the manager and calls the objects PreStart method if it has one.
         *
         * \tparam BehaviouralSceneObject Class that the object with behaviour inherits from.
         * \tparam T The specific type of the behaviour object (Will be the Derived template argument for BehaviouralSceneObject).
         * \param thing A pointer to the object being added.
         */
        template<template<class> class BehaviouralObject, class T>
        void AddBehaviour(BehaviouralObject<T>* thing)
        {
            //call prestart
            if constexpr (HasStartMethod<T>::value)
            {
                static_cast<T*>(thing)->Start();
            }
            if constexpr (HasUpdateMethod<T>::value)
            {
                m_update_functions.push_back(std::pair<void*, std::function<void()>>(static_cast<void*>(thing), [thing] { static_cast<T*>(thing)->Update(); }));
            }
            if constexpr (HasUIMethod<T>::value)
            {
                m_gui_functions.push_back(std::pair<void*, std::function<void()>>(static_cast<void*>(thing), [thing] { static_cast<T*>(thing)->UI(); }));
            }
        }

        /*!
         * \brief Calls all Update methods for added behaviour objects.
         *
         * Iterates through the list of registered objects and invokes their Update method.
         */
        void CallAllUpdateFunctions() const;

        /*!
         * \brief Calls all UI methods for added behaviour objects.
         *
         * Iterates through the list of registered objects and invokes their UI method.
         */
        void CallAllUIFunctions() const;

        /*!
         * \brief Removes a behaviour function from the manager, invoking End and PostEnd if available.
         *
         * \tparam BehaviouralSceneObject Class that the object with behaviour inherits from.
         * \tparam T The specific type of the behaviour object (Will be the Derived template argument for BehaviouralSceneObject).
         * \param thing A pointer to the object being removed.
         */
        template<template<class> class BehaviouralObject, class T>
        void RemoveBehaviour(BehaviouralObject<T>* thing)
        {
            if constexpr (HasEndMethod<T>::value)
            {
                static_cast<T*>(thing)->End();
            }

            RemoveBehaviourFromList(m_update_functions, thing);
            RemoveBehaviourFromList(m_gui_functions, thing);
        }

    private:
        /*!
         * \brief Removes a behaviour from a list of behaviour methods.
         *
         * \tparam T The specific type of the behaviour object (Will be the Derived template argument for BehaviouralSceneObject).
         * \param list The list of behaviour functions from which the object will be removed.
         * \param thing A pointer to the object to remove from the list.
         */
        template<class T>
        void RemoveBehaviourFromList(std::list<std::pair<void*, std::function<void()>>>& list, T* thing)
        {
            for (auto it = list.begin(); it != list.end(); it++)
            {
                if (static_cast<T*>(it->first) == thing)
                {
                    it = list.erase(it);
                    return;
                }
            }
        }

    private:
        std::list<std::pair<void*, std::function<void()>>> m_update_functions; /*!< List of a pair of behaviour object* and its Update method. */
        std::list<std::pair<void*, std::function<void()>>> m_gui_functions; /*!< List of a pair of behaviour object* and its UI method. */
    };


}