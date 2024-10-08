/**
 * @file Winch.cpp
 * @author Jacob Stacy
 */

#include "pch.h"

#include "Winch.h"

/**
 * Constructor
 * @param name Name
 * @param backImage Back Image
 * @param wheelImage Wheel Image
 */
Winch::Winch(const std::wstring& name, const std::wstring& backImage, const std::wstring& wheelImage) : Component(name),
                                                                                                        mSource(this)
{
    mBasePolygon.SetImage(backImage);
    mBasePolygon.BottomCenteredRectangle();

    mWheelPolygon.SetImage(wheelImage);
    mWheelPolygon.CenteredSquare();
}

/**
 * Draws the component
 * @param graphics Graphics
 */
void Winch::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mBasePolygon.DrawPolygon(graphics, GetPosition().x, GetPosition().y);

    mWheelPolygon.DrawPolygon(graphics, GetPosition().x, GetPosition().y - (mBasePolygon.GetImageHeight() / 2));

}


/**
 * Set the current time
 * @param time New time
 */
void Winch::SetTime(double time)
{
    if(mDuration > 0)
    {
        double speed = (mRotation - mWheelPolygon.GetRotation()) / mDuration;

        double addedRotation = (speed * (time - mPrevTime));

        mWheelPolygon.SetRotation(mWheelPolygon.GetRotation() + addedRotation);
        mSource.Move(time, mDuration, mWheelPolygon.GetRotation());

        mDuration -= (time - mPrevTime);

        mPrevTime = time;

    } else
    {
        mPrevTime = time;
    }



}

/**
 * Loadss XML Event
 * @param node node with event
 */
void Winch::XmlLoad(wxXmlNode* node)
{
    mRotation = wxAtof(node->GetAttribute(L"rotate-to"));
    mDuration = wxAtof(node->GetAttribute(L"duration"));

    mPrevTime = wxAtof(node->GetAttribute(L"time"));
}

/**
 * Resets the component to default
 * @param frame Frame
 */
void Winch::Reset(int frame)
{
    mWheelPolygon.SetRotation(0);
    mDuration = 0;
    mRotation = 0;
    mSource.Move(0,0,mWheelPolygon.GetRotation());
}
