#include "ResourcePathHandler.h"
#include "Diagnostics/Logger.h"

namespace be {

    std::string ResourcePathHandler::m_resource_path;

    std::string ResourcePathHandler::GetResourcePath()
    {
        return m_resource_path;
    }

    std::string ResourcePathHandler::GetModelsPath()
    {
        return m_resource_path + "/models/";
    }

    std::string ResourcePathHandler::GetTexturesPath()
    {
        return m_resource_path + "/Textures/";
    }

    std::string ResourcePathHandler::GetShadersPath()
    {
        return m_resource_path + "/Shaders/";
    }

    std::string ResourcePathHandler::GetFontsPath()
    {
        return m_resource_path + "/Fonts/";
    }

    std::string ResourcePathHandler::LoadResourcePathFromConfigFile()
    {
        std::ifstream file("BEApplicationConfig.txt");
        if (!file.is_open())
        {
            BELOG_CD_ERR("ResourcePathHanlder expecs a BEApplicationConfig.txt file in the same directory as the excecutable");
            return "";
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream lineStream(line);
            std::string key;

            //get the key before the :
            if (std::getline(lineStream, key, ':'))
            {
                std::string value;

                if (std::getline(lineStream, value)) {
                    //remove any leading/trailing spaces
                    key.erase(0, key.find_first_not_of(" \t"));
                    key.erase(key.find_last_not_of(" \t") + 1);

                    //trim quotes and spaces from value
                    value.erase(0, value.find_first_not_of(" \t\""));
                    value.erase(value.find_last_not_of(" \t\"") + 1);

                    if (key == "ResourcePath")
                    {
                        BELOG_CD_ERR(value);
                        return value;
                    }
                }
            }
        }

        BELOG_CD_ERR("Config.txt does not contain ResourcePath");
        return "";
    }

}