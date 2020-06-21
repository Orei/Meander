#pragma once
#include <unordered_map>
#include <string>

namespace Meander
{
    // TODO: Temporary resource manager, to be replaced with a proper implementation
    class Resources
    {
    public:
        template<class T>
        static T* Load(const std::string& path)
        {
            auto it = m_Assets.find(path);
            if (it != m_Assets.end())
                return static_cast<T*>(it->second);

            T* asset = T::Create(path.c_str());
            m_Assets.insert({{ path }, { (void*)asset }});
            
            return asset;
        }

        static const std::unordered_map<std::string, void*>& GetResources() { return m_Assets; };
    
    private:
        static std::string m_RootDirectory;
        static std::unordered_map<std::string, void*> m_Assets;
    };

    std::string Resources::m_RootDirectory = "Assets/";
    std::unordered_map<std::string, void*> Resources::m_Assets;
}