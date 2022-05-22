#pragma once

class ANAnimationCompositionController : public IANAnimationCompositionController
{
public:
	
private:
	void SetAnimationDuration(float flDuration) override;
	bool IsNeedUpdateAnimation(IANApi* pApi) override;
	void SetAnimationComposition(ANAnimationComposition AnimationComposition) override;
	ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) override;
	int GetCurrentAnimationCompositionCount() override;
};