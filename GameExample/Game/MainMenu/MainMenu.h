#pragma once

class CTestCheckboxSkin : public IANCheckboxSkin
{
public:
	CTestCheckboxSkin(ANImageID bgImage, ANImageID markImage);
	~CTestCheckboxSkin();

	void SetSkin(
		bool IsHovered, bool IsPressed, bool IsClicked,
		anRect* pBgRect, anColor* pBgColor, ANImageID* pBgImage,
		anRect* pMarkRect, anColor* pMarkColor, ANImageID* pMarkImage) override;

private:
	ANImageID m_bgImage;
	ANImageID m_markImage;
};

class CTestSliderSkin : public IANSliderSkin
{
public:
	CTestSliderSkin(ANImageID bgImage, ANImageID sliderImage);
	~CTestSliderSkin();

	void SetSkin(
		bool IsHovered, bool IsPressed, bool IsClicked,
		anRect* pBgRect, anColor* pBgColor, ANImageID* pBgImage,
		anRect* pSliderRect, anColor* pSliderColor, ANImageID* pSliderImage) override;

private:
	ANImageID m_bgImage;
	ANImageID m_sliderImage;
};

class CTestGameScene : public IANGameScene
{
public:
	CTestGameScene();
	~CTestGameScene();

	void OnLoadScene(IANApi* pApi) override;
	void OnUnloadScene(IANApi* pApi) override;
	void Entry(IANApi* pApi) override;

private:
	ANImageID m_imgImageKrolik;
	ANFontID m_fontStolzLight;
	ANGuiWindowID m_AnotherWindow;

	IANCheckboxSkin* m_pTestCheckboxSkin;
	IANSliderSkin* m_pSliderSkin;
};