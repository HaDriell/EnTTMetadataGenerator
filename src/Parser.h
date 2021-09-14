#pragma once

#include <string>
#include <vector>

#include <HeaderParserLib/Token.h>
#include <HeaderParserLib/Tokenizer.h>

#include "Metadata/Scope.h"


class Parser
{
public:
    Parser();
    bool Parse(const std::string& source);
    bool ParseStatement();
    bool ParseDeclaration(const Token& token);

    bool ParseClass();
    bool ParseProperty();
    bool ParseFunction();

    bool ParseMetadata();

    Scope& GetGlobalScope() { return m_GlobalScope; }

protected:
    virtual void OnClassBegin(const std::string& className) { PushScope(className); }
    virtual void OnClassEnd(){ PopScope(); }

private:
    void PushScope(const std::string& name);
    void PopScope();

private:
    Scope m_GlobalScope;
    Scope* m_CurrentScope;
    Tokenizer m_Tokenizer;
};