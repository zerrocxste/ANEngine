#pragma once

class IANError
{
private:
	char m_szWhat[1024 + 1];
public:
	IANError();
	~IANError();

	const char* What();
protected:
	void SetError(const char* szErrorText, ...);
};