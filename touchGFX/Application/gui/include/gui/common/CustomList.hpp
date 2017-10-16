/*
 * CustomList.hpp
 *
 *  Created on: 2017/09/26
 *      Author: yuhang
 */
#ifndef CUSTOM_LIST_HPP
#define CUSTOM_LIST_HPP

#include <gui/common/CustomListElement.hpp>
#include <touchgfx/containers/ListLayout.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/widgets/AnimatedImage.hpp>
#include <list>
//#include <map>

using namespace touchgfx;
using namespace std;

class CustomList
{
protected:
    list<CustomListElement> mList;
    //map<int, CustomListElement> mList;
    GenericCallback< CustomListElement& >* mCallback;
    AnimatedImage animation;
    CustomListElement* curElement;
public:
    CustomList();
    virtual ~CustomList() {}
    void clear();
    void markClear();
    void doClear();
    //void refreshStart();
    void addElement(uint8_t address[], const Bitmap& bmp, const Unicode::UnicodeChar* strName, int rssi = 0, bool needPwd = false);
    //void refreshEnd();
    void sort();
    void setAction(GenericCallback< CustomListElement& >* callback) { mCallback = callback; }
    void genListLayout(ListLayout &listLayout);
    void addAnimation(Container& list) { list.add(animation); } 
    void startAnimation();
    void stopAnimation();
    CustomListElement* getCurElement() { return curElement; }
    void setCurElement(CustomListElement* element) { curElement = element; }
    void setCurElementStatus(CustomListElementStatus status);
    void clearElementStatus(CustomListElementStatus status = cesAll);
    CustomListElement* getElement(uint8_t address[]);
};

#endif /* CUSTOM_LIST_HPP */
