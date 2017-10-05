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

    int charWidth = text.getTypedText().getFont()->getCharWidth(0x006D); //char width of "m" ,all of char is monospaced font
	spaceBetweenTextCols = charWidth * 5 * 2;// For blank lines between texts;

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

	leftCutOff = selectedTextXPosition + (spaceBetweenTextCols / 2);
	rightCutOff = leftCutOff - text.getTextWidth() - (spaceBetweenTextCols / 3);

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
        int newXPosition = text.getX() + delta;
		adjustForBoundries(newXPosition);

		int distanceToMove = newXPosition - text.getX();
        int distanceToMoveABS = (distanceToMove > 0) ? distanceToMove : -distanceToMove;
        int duration = distanceToMoveABS / 10;
        duration = (duration < 2) ? 2 : duration;

		animateMoveText(newXPosition, duration, EasingEquations::cubicEaseOut);
    }
}

void HorizontalWheelSelector::snap()
{
	int deltaUp = (spaceBetweenTextCols - (text.getX() - selectedTextXPosition)) % spaceBetweenTextCols;

    // Invert % value for negative values
	deltaUp = (deltaUp > 0) ? deltaUp : spaceBetweenTextCols + deltaUp;

	int deltaDown = spaceBetweenTextCols - deltaUp;

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
	return (selectedTextXPosition - text.getX()) / spaceBetweenTextCols;
}

void HorizontalWheelSelector::setSelectedIndex(int index, int duration, EasingEquation equation)
{
	int newXPosition = selectedTextXPosition - (spaceBetweenTextCols * index);
	adjustForBoundries(newXPosition);

    if (duration == 0)
    {
		moveText(newXPosition);
    }
    else
    {
        currentAnimationState = ANIMATING_GESTURE;
		animateMoveText(newXPosition, duration, equation);
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

void HorizontalWheelSelector::moveText(int newXPosition)
{
	adjustForBoundries(newXPosition);

	text.moveTo(newXPosition, text.getY());
    if (textSelectedContainer.isVisible())
    {
		textSelected.moveTo(newXPosition - selectedAreaXOffset, text.getY());
    }
}

void HorizontalWheelSelector::animateMoveText(int newXPosition, int duration, EasingEquation equation)
{
	text.startMoveAnimation(newXPosition, text.getY(), duration, EasingEquations::linearEaseNone, equation);
    if (textSelectedContainer.isVisible())
    {
		textSelected.startMoveAnimation(newXPosition - selectedAreaXOffset, text.getY(), duration, EasingEquations::linearEaseNone, equation);
    }
}

void HorizontalWheelSelector::reset()
{
    moveText(selectedTextXPosition);
}
