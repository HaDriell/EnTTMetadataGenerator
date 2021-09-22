#include <cstdint>
#include <string>

CLASS()
class MyComponent
{
public:
    FUNCTION()
    float GetMyFloat() const;

    //Not annotated function
    const std::string& GetMyString();

private:
    PROPERTY()
    float m_MyFloat;

    PROPERTY()
    std::string m_MyString;

    //Not annotated property
    uint32_t m_MyInt;
};