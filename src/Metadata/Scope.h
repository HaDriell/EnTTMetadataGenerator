#pragma once

#include <ostream>
#include <string>
#include <vector>

class Scope
{
public:
    Scope(const std::string& name);
    virtual ~Scope();

    virtual void Bake(std::ostream& stream) const;
    
    std::string GetAbsoluteName() const;
    uint32_t GetScopeDepth() const;

    const std::string& GetName() const { return m_Name; }

    Scope* GetParent() const { return m_Parent; }
    void SetParent(Scope* scope);

    const std::vector<Scope*>& GetChildren() const { return m_Children; }
    Scope* FindChild(const std::string& name) const;
    void AddChild(Scope* scope);
    void RemoveChild(Scope* scope);


private:
    std::string         m_Name;
    Scope*              m_Parent;
    std::vector<Scope*> m_Children;
};