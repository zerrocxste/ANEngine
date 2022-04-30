#pragma once

class IANGuiButtonSkin
{
public:
	virtual void SetSkin(
		bool IsHovered, bool IsPressed, bool IsClicked,
		anRect* pRect, anColor* pColor, ANImageID* pImage) = 0;
};

class IANCheckboxSkin
{
public:
	virtual void SetSkin(
		bool IsHovered, bool IsPressed, bool IsClicked,
		anRect* pBgRect, anColor* pBgColor, ANImageID* pBgImage, 
		anRect* pMarkRect, anColor* pMarkColor, ANImageID* pMarkImage) = 0;
};

class IANSliderSkin
{
public:
	virtual void SetSkin(bool IsHovered, bool IsPressed, bool IsClicked,
		anRect* pBgRect, anColor* pBgColor, ANImageID* pBgImage,
		anRect* pSliderRect, anColor* pSliderColor, ANImageID* pSliderImage) = 0;
};