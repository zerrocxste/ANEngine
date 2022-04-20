#pragma once

class ANScene : public IANError
{
public:
	ANScene(ANCore* pCore);
	~ANScene();

	bool Run();

private:
	ANCore* m_pCore;
};

