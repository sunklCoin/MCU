/***********************************/
/********** sunkelong add **********/
/*************2017-10-07************/
#ifndef SHORTCUTCONTAINER_HPP
#define SHORTCUTCONTAINER_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/Container.hpp>
using namespace touchgfx;

class ShortcutContainer : public Container
{
public:
	ShortcutContainer();
	virtual ~ShortcutContainer() {}

protected:
    FrontendApplication& application() { 
        return *static_cast<FrontendApplication*>(Application::getInstance()); 
    }

    /*
     * Member Declarations
     */
    Image image1;
    Button buttonScreenSaver;
    Button buttonSleep;

private:
	
	Callback<ShortcutContainer, const AbstractButton&> onshortcutContainer;
	void shortcutContainerHandler(const AbstractButton& button);
};

#endif // SHORTCUTCONTAINER_HPP
