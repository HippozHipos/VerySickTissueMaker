#pragma once
#include "pch.h"

namespace be {

	class ResourcePathHandler
	{
    public:
        static void Init()
        {
            m_resource_path = LoadResourcePathFromConfigFile();
        }

    public:
        static std::string GetResourcePath();
        static std::string GetModelsPath();
        static std::string GetTexturesPath();
        static std::string GetShadersPath();
        static std::string GetFontsPath();

	private:
        static std::string LoadResourcePathFromConfigFile();

    private:
        static std::string m_resource_path;
	};

}