/**
 * @file ZeroPointModule.cpp
 * @author Jacob Stacy
 */

#include "pch.h"

#include <sstream>

#include "ZeroPointModule.h"

/// Offset of the text
const double TextOffset = 80;

/// The ZPM output voltage
const double ZPMVoltage = 1000;

/// Location of the source on the ZPM
const wxPoint ZPMSourcePosition = wxPoint(15, -15);

/// Rotation to face right
const double FaceRight = .25;

/**
 * Constructor
 * @param name Name
 * @param imageDir Image Directory
 */
ZeroPointModule::ZeroPointModule(const std::wstring& name, const std::wstring& imageDir) : Component(name)
{
    mSource = std::make_shared<PowerSource>(this, imageDir, 100, wxPoint(0,0), FaceRight);
    mSource->SetPosition(GetPosition().x + ZPMSourcePosition.x, GetPosition().y + ZPMSourcePosition.y);
    mAmps = 0;
}

/**
 * Draws the component
 * @param graphics Graphics
 */
void ZeroPointModule::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.DrawPolygon(graphics, GetPosition().x, GetPosition().y); // Replace with visual shape

    mSource->Draw(graphics, GetPosition().x + ZPMSourcePosition.x, GetPosition().y + ZPMSourcePosition.y, FaceRight);

    wxFont font(wxSize(0, 25),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);

    graphics->SetFont(font, *wxWHITE);

    // Get Width of the String
    double numWidth, h;

    std::ostringstream ossV;
    ossV << mVoltage * 1000;
    graphics->GetTextExtent(ossV.str(), &numWidth, &h);
    graphics->DrawText(ossV.str(), GetPosition().x - (numWidth / 2) , GetPosition().y - TextOffset);

    std::ostringstream ossA;
    ossA << mAmps;
    graphics->GetTextExtent(ossA.str(), &numWidth, &h);
    graphics->DrawText(ossA.str(), GetPosition().x - (numWidth / 2) , GetPosition().y - (TextOffset - 25));

}

/**
 * Updates the Component
 * @param elapsed Current Time
 */
void ZeroPointModule::Update(double elapsed)
{
    Component::Update(elapsed);
}

/**
 * Set the current time
 * @param time New time
 */
void ZeroPointModule::SetTime(double time)
{
    if (time > 0)
    {
        Power(ZPMVoltage);
    } else
    {
        Power(0);
    }
}

/**
 * Powers the component
 * @param voltage Voltage Supplied
 * @return Current Drawn
 */
double ZeroPointModule::Power(double voltage)
{
    mAmps = mSource->Power(voltage);

    return 0;
}

/**
 * Resets the component to default
 * @param frame Frame
 */
void ZeroPointModule::Reset(int frame)
{
    Power(0);
}

void ZeroPointModule::SetPosition(double x, double y)
{
    Component::SetPosition(x, y);

    mSource->SetPosition(GetPosition().x + ZPMSourcePosition.x, GetPosition().y + ZPMSourcePosition.y);
}


