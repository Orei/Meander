#include "pch.h"
#include "Profiler.h"

namespace Meander
{
    std::stack<ProfilerScope> Profiler::s_ActiveScopes = { };
    std::vector<ProfilerScope> Profiler::s_StoredScopes = { };

    void Profiler::Push(const std::string& identifier)
    {
        ProfilerScope scope;
        scope.Identifier = identifier;
        scope.Timer.Start();
        
        s_ActiveScopes.push(scope);
    }

    const ProfilerScope& Profiler::Pop()
    {
        ProfilerScope& scope = s_ActiveScopes.top();
        scope.Timer.Stop();
        
        s_StoredScopes.push_back(scope);
        s_ActiveScopes.pop();
        
        return scope;
    }
}