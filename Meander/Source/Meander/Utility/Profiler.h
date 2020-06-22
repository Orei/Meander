#pragma once
#include "Timer.h"
#include <stack>

namespace Meander
{
    struct ProfilerScope
    {
        std::string Identifier;
        Timer Timer;
    };

    class Profiler
    {
    public:
        static void Push(const std::string& identifier);
        static const ProfilerScope& Pop();

        static const std::vector<ProfilerScope>& GetStoredScopes() { return s_StoredScopes; }

    private:
        Profiler(){}
        ~Profiler(){}
        
        static std::stack<ProfilerScope> s_ActiveScopes;
        static std::vector<ProfilerScope> s_StoredScopes;
    };
}
