#ifndef SCROLLABLECONTAINER_EX_HPP
#define SCROLLABLECONTAINER_EX_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Application.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
using namespace touchgfx;

class ScrollableContainerEx : public ScrollableContainer
{
public:

	/**
	* @fn ScrollableContainer::ScrollableContainer();
	*
	* @brief Default constructor.
	*
	*        Default constructor.
	*/
	ScrollableContainerEx();

	/**
	* @fn virtual ScrollableContainer::~ScrollableContainer()
	*
	* @brief Destructor.
	*
	*        Destructor.
	*/
	virtual ~ScrollableContainerEx() { }

	virtual bool doScroll(int16_t deltaX, int16_t deltaY){
		return ScrollableContainer::doScroll(deltaX, deltaY);
	};
};
#endif /*SCROLLABLECONTAINER_EX_HPP*/