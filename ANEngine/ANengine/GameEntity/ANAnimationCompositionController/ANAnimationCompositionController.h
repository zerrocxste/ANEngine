#pragma once

class ANAnimationCompositionController : public IANAnimationCompositionController
{
public:
	void SetAnimationDuration(float flDuration) override;
	int GetNeedUpdateAnimationCounter(IANApi* pApi) override;
	void SetAnimationComposition(ANAnimationComposition AnimationComposition) override;
	ANImageID GetCurrentAnimationCompositionFrame(IANApi* pApi) override;
	int GetCurrentAnimationCompositionCount() override;
};
