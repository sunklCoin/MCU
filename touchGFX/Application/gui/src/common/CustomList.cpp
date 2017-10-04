/*
 * CustomList.cpp
 *
 *  Created on: 2017/09/26
 *      Author: yuhang
 */
#include <gui/common/CustomList.hpp>
#include "BitmapDatabase.hpp"


CustomList::CustomList() :
    animation(BITMAP_BTN_ANI_01_ID, BITMAP_BTN_ANI_04_ID, 10),
    curElement(NULL)
{
    animation.setVisible(false);
}

void CustomList::clear() {
    mList.clear();
}

void CustomList::addElement(uint8_t address[], const Bitmap& bmp, const Unicode::UnicodeChar* strName, int rssi) {
    mList.push_back(CustomListElement());
    CustomListElement& elNew = mList.back();

    elNew.setupListElement(bmp, address, strName, rssi);
    elNew.setAction(mCallback);
}

bool Comp(CustomListElement& a, CustomListElement& b) {
    return a.getRssi() > b.getRssi();
}

void CustomList::sort() {
    mList.sort(Comp);
}

void CustomList::genListLayout(ListLayout &listLayout) {
    listLayout.removeAll();

    list<CustomListElement>::iterator i;
    for (i = mList.begin(); i != mList.end(); ++i) {
        listLayout.add(*i);
    }
}

void CustomList::startAnimation(CustomListElement& element)
{
    animation.setX(element.getIconX());
    animation.setY(element.getIconY());
    element.setIconVisible(false);
    curElement = &element;
    animation.setVisible(true);
    animation.startAnimation(animation.isReverse(), false, true);
}

void CustomList::stopAnimation()
{
    if (curElement != NULL) {
        curElement->setIconVisible(true);
        curElement = NULL;
    }
    animation.setVisible(false);
    animation.stopAnimation();
}
