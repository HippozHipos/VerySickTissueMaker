#pragma once
#include "pch.h"
#include <entt/entt.hpp>

namespace be {
    /*!
     * \class ECS
     * \brief Just stores static instance of entt::registry
     */

	struct ECS { static entt::registry registry; };

}