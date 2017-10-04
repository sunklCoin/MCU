/***********************************/
/********** sunkelong add **********/
/*************2017-10-03************/

#include <gui/custom_controls_screen/HorizontalWheelSelector.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/EasingEquations.hpp>

HorizontalWheelSelector::HorizontalWheelSelector() :
currentAnimationState(NO_ANIMATION),
elementSelectedAction(0),
textMoveEndedCallback(this, &HorizontalWheelSelector::textMoveEndedHandler)
{
}

HorizontalWheelSelector::~HorizontalWheelSelector()
{
}

void HorizontalWheelSelector::setup(int width, int height, int textXPosition, int textYPosition, TEXTS wheelText)
{
    setWidth(width);
    setHeight(height);
    setTouchable(true);

    selectedTextXPosition = textXPosition;

    textContainer.setPosition(0, 0, getWidth(), getHeight());
    add(textContainer);

    text.setTypedText(TypedText(wheelText));
    text.setXY(selectedTextXPosition, textYPosition);
    text.setMoveAnimationEndedAction(textMoveEndedCallback);
    textContainer.add(text);

    int charWidth = text.getTypedText().getFont()->getCharWidth(0x006D); //"m"
    //int charsWidth = text.getTypedText().getFont()->getCharWidth(0x0073); //"s"
    spaceBetweenTextRows = (text.getTextWidth() - charWidth * 5 * 7)/6; //  text.getTextWidth() / 8; // For blank lines between texts;

    // Prepare textSelected (if colors are different)
    // Position of textSelectedContainer (y coordinate) updated later in setTextColor()
    textSelectedContainer.setPosition(textContainer.getX(), textContainer.getY(), textContainer.getWidth(), textContainer.getHeight());
    add(textSelectedContainer);

    textSelectedBackground.setPosition(0, textContainer.getY(), textSelectedContainer.getWidth(), textSelectedContainer.getHeight());
    textSelectedContainer.add(textSelectedBackground);

    textSelected.setTypedText(text.getTypedText());
    // Position of textSelected updated later in setTextColor()
    textSelected.setXY(text.getX(), text.getY());
    textSelected.setMoveAnimationEndedAction(textMoveEndedCallback);
    textSelectedContainer.add(textSelected);
    // Hide selected text, shown when normal/selected colors differ, see setTextColor()
    textSelectedContainer.setVisible(false);

    leftCutOff = selectedTextXPosition + (spaceBetweenTextRows);
    rightCutOff = leftCutOff - text.getTextWidth() - (spaceBetweenTextRows);

    reset();
}


void HorizontalWheelSelector::setTextColor(colortype normalColor, colortype selectedColor, colortype selectedBackgroundColor, int selectedXOffset, int selectedWidth)
{
    text.setColor(normalColor);
    if (normalColor != selectedColor)
    {
        selectedAreaXOffset = selectedXOffset;
        textSelectedBackground.setWidth(selectedWidth);
        textSelectedBackground.setColor(selectedBackgroundColor);
        textSelectedContainer.setX(textContainer.getX() + selectedAreaXOffset);
        textSelectedContainer.setWidth(selectedWidth);
        textSelected.setColor(selectedColor);
        textSelected.setX(text.getX() - selectedAreaXOffset);
        textSelectedContainer.setVisible(true);
    }
    else
    {
        textSelectedContainer.setVisible(false);
    }
    text.invalidate(); // This also overlaps with textSelected which is therefore also redrawn
}

void HorizontalWheelSelector::handleDragEvent(const DragEvent& evt)
{
    if (currentAnimationState == ANIMATING_DRAG)
    {
        moveText(text.getX() + evt.getDeltaX());
    }
}

void HorizontalWheelSelector::handleClickEvent(const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::PRESSED)
    {
        if (currentAnimationState != NO_ANIMATION)
        {
            text.cancelMoveAnimation();
            textSelected.cancelMoveAnimation();
        }
        currentAnimationState = ANIMATING_DRAG;
    }
    else if (evt.getType() == ClickEvent::RELEASED && currentAnimationState == ANIMATING_DRAG)
    {
        snap();
    }
}

void HorizontalWheelSelector::handleGestureEvent(const GestureEvent& evt)
{
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
        currentAnimationState = ANIMATING_GESTURE;

        int delta = evt.getVelocity() * 5;
        int newYPosition = text.getX() + delta;
        adjustForBoundries(newYPosition);

        int distanceToMove = newYPosition - text.getX();
        int distanceToMoveABS = (distanceToMove > 0) ? distanceToMove : -distanceToMove;
        int duration = distanceToMoveABS / 10;
        duration = (duration < 2) ? 2 : duration;

        animateMoveText(newYPosition, duration, EasingEquations::cubicEaseOut);
    }
}

void HorizontalWheelSelector::snap()
{
    int deltaUp = (spaceBetweenTextRows - (text.getX() - selectedTextXPosition)) % spaceBetweenTextRows;

    // Invert % value for negative values
    deltaUp = (deltaUp > 0) ? deltaUp : spaceBetweenTextRows + deltaUp;

    int deltaDown = spaceBetweenTextRows - deltaUp;

    if (deltaUp < deltaDown)
    {
        animateMoveText(text.getX() + deltaUp, 10, EasingEquations::backEaseInOut);
    }
    else
    {
        animateMoveText(text.getX() - deltaDown, 10, EasingEquations::backEaseInOut);
    }
    currentAnimationState = ANIMATING_SNAP;
}

int HorizontalWheelSelector::getSelectedIndex()
{
    return (selectedTextXPosition - text.getX()) / spaceBetweenTextRows;
}

void HorizontalWheelSelector::setSelectedIndex(int index, int duration, EasingEquation equation)
{
    int newYPosition = selectedTextXPosition - (spaceBetweenTextRows * index);
    adjustForBoundries(newYPosition);

    if (duration == 0)
    {
        moveText(newYPosition);
    }
    else
    {
        currentAnimationState = ANIMATING_GESTURE;
        animateMoveText(newYPosition, duration, equation);
    }

}

void HorizontalWheelSelector::textMoveEndedHandler(const MoveAnimator<TextArea>& textArea)
{
    if (currentAnimationState == ANIMATING_GESTURE)
    {
        if (!textArea.isRunning() && !textSelected.isRunning())
        {
            snap();
        }
    }
    else if (currentAnimationState == ANIMATING_SNAP)
    {
        currentAnimationState = NO_ANIMATION;
        if (elementSelectedAction && elementSelectedAction->isValid())
        {
            elementSelectedAction->execute(*this, getSelectedIndex());
        }
    }
    else
    {
        currentAnimationState = NO_ANIMATION;
    }
}

void HorizontalWheelSelector::adjustForBoundries(int& newYValue)
{
    if (newYValue > leftCutOff)
    {
        newYValue = leftCutOff;
    }
    else if (newYValue < rightCutOff)
    {
        newYValue = rightCutOff;
    }
}

void HorizontalWheelSelector::moveText(int newYPosition)
{
    adjustForBoundries(newYPosition);

    text.moveTo(newYPosition,text.getY());
    if (textSelectedContainer.isVisible())
    {
        textSelected.moveTo(newYPosition - selectedAreaXOffset, text.getY());
    }
}

void HorizontalWheelSelector::animateMoveText(int newYPosition, int duration, EasingEquation equation)
{
    text.startMoveAnimation(newYPosition,text.getY(), duration, EasingEquations::linearEaseNone, equation);
    if (textSelectedContainer.isVisible())
    {
        textSelected.startMoveAnimation(newYPosition - selectedAreaXOffset, text.getY(), duration, EasingEquations::linearEaseNone, equation);
    }
}

void HorizontalWheelSelector::reset()
{
    moveText(selectedTextXPosition);
}
