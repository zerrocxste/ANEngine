#pragma once

class IANError
{
private:
	char m_szWhat[255];
public:
	IANError();
	~IANError();

	const char* What();
protected:
	//virtual void ShowError() = 0;
	void SetError(const char* szErrorText, ...);
};