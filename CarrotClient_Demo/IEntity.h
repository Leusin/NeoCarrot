#pragma once

namespace ge
{

class ICompoent;

class IEntity
{
public:
    ICompoent* GetComPonent();
    void       AddComPonent();

private:
    std::string Name;
    std::string Tag;
    std::string UUID;
};

} // namespace ge