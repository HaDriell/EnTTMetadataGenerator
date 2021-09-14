#include "Metadata/Scope.h"

#include <algorithm>

Scope::Scope(const std::string& name)
    : m_Name(name)
    , m_Parent(nullptr)
    , m_Children()
{
}

Scope::~Scope()
{
    for (Scope* scope : m_Children)
    {
        delete scope;
    }
}

void Scope::Bake(std::ostream& stream) const
{
    stream << "[ScopeBegin(" << GetScopeDepth() << ")] " << GetAbsoluteName() << "\n";

    for (Scope* scope : m_Children)
    {
        scope->Bake(stream);
    }

    stream << "[ScopeEnd(" << GetScopeDepth() << ")  ] " << GetAbsoluteName() << "\n";
}


std::string Scope::GetAbsoluteName() const
{
    const Scope* scope = this;
    std::string name;

    while (scope != nullptr)
    {
        name += "::" + scope->GetName();
        scope = scope->GetParent();
    }

    return name;
}

uint32_t Scope::GetScopeDepth() const
{
    const Scope* parent = m_Parent;
    uint32_t depth = 0;

    while (parent != nullptr)
    {
        depth++;
        parent = parent->GetParent();
    }

    return depth;
}

void Scope::SetParent(Scope* scope)
{
    if (m_Parent != nullptr)
    {
        m_Parent->RemoveChild(this);
    }

    m_Parent = scope;

    if (m_Parent != nullptr)
    {
        m_Parent->AddChild(this);
    }
}

Scope* Scope::FindChild(const std::string& name) const
{
    for (Scope* scope : m_Children)
    {
        if (scope->GetName() == name)
        {
            return scope;
        }
    }

    return nullptr;
}

void Scope::AddChild(Scope* scope)
{
    auto it = std::find(m_Children.begin(), m_Children.end(), scope);
    if (it == m_Children.end())
    {
        m_Children.push_back(scope);
    }
}

void Scope::RemoveChild(Scope* scope)
{
    auto it = std::find(m_Children.begin(), m_Children.end(), scope);
    if (it != m_Children.end())
    {
        m_Children.erase(it);
    }
}
