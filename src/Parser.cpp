#include "Parser.h"


Parser::Parser()
    : m_CurrentScope(&m_GlobalScope)
    , m_GlobalScope("")
{
    m_CurrentScope = &m_GlobalScope;
}


bool Parser::Parse(const std::string& source)
{
    m_Tokenizer.SetSource(source);

    while (ParseStatement())
    {
    }

    return true;
}


bool Parser::ParseStatement()
{
    Token token;
    if (m_Tokenizer.GetToken(token))
    {
        return ParseDeclaration(token);        
    }

    return false;
}


bool Parser::ParseDeclaration(const Token& token)
{
    switch (token.Type)
    {
    case TokenType::Identifier:
        if (token.Value == "CLASS") return ParseClass();
        if (token.Value == "PROPERTY") return ParseProperty();
        if (token.Value == "FUNCTION") return ParseFunction();
        break;

    default:
        break;
    }

    return true;
}


bool Parser::ParseClass()
{
    if (!ParseMetadata()) return false;

    //Expect 'class' or 'struct'
    if (!m_Tokenizer.ExpectIdentifier("class") && !m_Tokenizer.ExpectIdentifier("struct")) return false;

    //Read the ClassName
    Token className;
    if (!m_Tokenizer.GetIdentifier(className)) return false;
    //We try to avoid capturing dll export macros there, we should hit a Symbol ':' or '{' at some point
    while (m_Tokenizer.GetIdentifier(className))
    {
    }

    //MAYDO : Parse Inheritance tree ?

    //Skip to the Class Scope
    if (!m_Tokenizer.SkipToSymbol("{")) return false;

    OnClassBegin(className.Value);

    while (!m_Tokenizer.ExpectSymbol("}"))
    {
        ParseStatement();
    }

    OnClassEnd();
    return true;
}


bool Parser::ParseProperty()
{
    if (!ParseMetadata()) return false;

    Token propertyTypeName;
    if (!m_Tokenizer.GetIdentifier(propertyTypeName)) return false;

    Token propertyName;
    if (!m_Tokenizer.GetIdentifier(propertyName)) return false;

    //MAYDO : Parse initialization expression ?

    if (!m_Tokenizer.SkipToSymbol(";")) return false;

    return true;
}


bool Parser::ParseFunction()
{
    if (!ParseMetadata()) return false;

    Token returnTypeName;
    if (!m_Tokenizer.GetIdentifier(returnTypeName)) return false;

    Token functionName;
    if (!m_Tokenizer.GetIdentifier(functionName)) return false;

    if (!m_Tokenizer.SkipToSymbol(";")) return false;

    

    return true;
}


bool Parser::ParseMetadata()
{
    if (!m_Tokenizer.ExpectSymbol("(")) return false;

    // Parse Metadata here instead of Skipping

    if (!m_Tokenizer.SkipToSymbol(")")) return false;

    return true;
}


void Parser::PushScope(const std::string& name)
{
    Scope* scope = new Scope(name);
    scope->SetParent(m_CurrentScope);
    m_CurrentScope = scope;
}


void Parser::PopScope()
{
    m_CurrentScope = m_CurrentScope->GetParent();
}