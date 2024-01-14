#include "ResourceView.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


namespace graphics
{

ResourceView::ResourceView()
{
#ifdef _DEBUG
    std::cout << "\t\tResourceView Constructed\n";
#endif // _DEBUG
}

} // namespace graphics