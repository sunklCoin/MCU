/*
 * CustomList.cpp
 *
 *  Created on: 2017/09/26
 *      Author: yuhang
 */
#include <gui/common/CustomList.hpp>
#include "BitmapDatabase.hpp"
#include <string.h>


CustomList::CustomList() :
    animation(BITMAP_BTN_ANI_01_ID, BITMAP_BTN_ANI_04_ID, 10),
    curElement(NULL)
{
    animation.setVisible(false);
}

void CustomList::clear() {
    mList.clear();
}

void CustomList::markClear() {
    list<CustomListElement>::iterator i;

    for (i = mList.begin(); i != mList.end(); ++i) {
        (*i).setNeedDel(true);
    }
}

void CustomList::doClear() {
    list<CustomListElement>::iterator i;

    for (i = mList.begin(); i != mList.end(); ) {
        if ((*i).isNeedDel()) {
            i = mList.erase(i);
        } else {
            ++i;
        }
    }
}

void CustomList::addElement(uint8_t address[], const Bitmap& bmp, const Unicode::UnicodeChar* strName, int rssi, bool needPwd) {
    CustomListElement* elOld = getElement(address);

    if (elOld == NULL) {
        mList.push_back(CustomListElement());
        CustomListElement& elNew = mList.back();
        elNew.setupListElement(bmp, address, strName, rssi, needPwd);
        elNew.setAction(mCallback);
        elNew.setNeedDel(false);
     } else {
        elOld->setupListElement(address, strName, rssi, needPwd);
        elOld->setNeedDel(false);
     }
}

bool Comp(CustomListElement& a, CustomListElement& b) {
    if (a.getStatus() == cesConnected && b.getStatus() != cesConnected)
        return true;
    else if (a.getStatus() != cesConnected && b.getStatus() == cesConnected)
        return false;
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

void CustomList::startAnimation( )
{
    animation.setX(curElement->getIconX());
    animation.setY(curElement->getIconY());
    curElement->setIconVisible(false);
    animation.setVisible(true);
    animation.startAnimation(animation.isReverse(), false, true);
}

void CustomList::stopAnimation()
{
    if (curElement != NULL) {
        curElement->setIconVisible(true);
    }
    animation.setVisible(false);
    animation.stopAnimation();
}

void CustomList::setCurElementStatus(CustomListElementStatus status) {
    if (curElement != NULL) {
        curElement->setStatus(status);
    }
}

void CustomList::clearElementStatus(CustomListElementStatus status) {
    list<CustomListElement>::iterator i;

    for (i = mList.begin(); i != mList.end(); ++i) {
        CustomListElement& element = *i;
        if (status == cesAll) {
            element.setStatus(cesNone);
        } else if (element.getStatus()== status) {
            element.setStatus(cesNone);
        }
     }
}

CustomListElement* CustomList::getElement(uint8_t address[]) {
    list<CustomListElement>::iterator i;

    for (i = mList.begin(); i != mList.end(); ++i) {
        if (memcmp((*i).getAddress(), address, CustomListElement::ADDRESS_SIZE) == 0) {
            return &(*i);
        }
    }
	return NULL;
}

