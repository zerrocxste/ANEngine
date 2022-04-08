#include "../../ANEngine.h"

IANError::IANError()
{

}

IANError::~IANError()
{

}

const char* IANError::What()
{
	return !*this->m_szWhat ? "NO_ERROR" : this->m_szWhat;
};

void IANError::SetError(const char* szErrorText, ...)
{
	va_list va_l;

	va_start(va_l, szErrorText);
	vsprintf_s(this->m_szWhat, szErrorText, va_l);
	va_end(va_l);
}