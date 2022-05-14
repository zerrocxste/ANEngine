#include "../../ANEngine.h"

int ANEntity::GetEntityID()
{
	return this->m_ID;
}

void ANEntity::SetOrigin(anVec2 Origin)
{
	this->m_Origin = Origin;
}

void ANEntity::MovePoint(IANApi* pApi, float Speed, anVec2 Origin)
{
	this->m_Origin += Origin * (Speed * pApi->Frametime);
}

float Interpolation(float t, float start, float end)
{
	return start + t * (end - start);
}

void ANEntity::MoveLeft(IANApi* pApi, float Speed)
{
	this->m_Origin.x -= Interpolation(Speed * pApi->Frametime, 0.f, 1.f);
}

void ANEntity::MoveRight(IANApi* pApi, float Speed)
{
	this->m_Origin.x += Speed * pApi->Frametime;
}

void ANEntity::MoveUp(IANApi* pApi, float Speed)
{
	this->m_Origin.y -= Interpolation(Speed * pApi->Frametime, 0.f, 1.f);
}

void ANEntity::MoveDown(IANApi* pApi, float Speed)
{
	this->m_Origin.y += Interpolation(Speed * pApi->Frametime, 0.f, 1.f);
}

anVec2 ANEntity::GetOrigin()
{
	return this->m_Origin;
}

void ANEntity::SetAnimationDuration(float flDuration)
{
	this->m_flAnimationDuration = flDuration;
}

bool ANEntity::IsNeedUpdateAnimation(IANApi* pApi)
{
	if (!this->m_flAnimationDuration)
		return false;

	auto ret = this->m_flAnimationTime <= 0.f;

	if (ret)
		this->m_flAnimationTime = this->m_flAnimationDuration;

	this->m_flAnimationTime -= pApi->Frametime;

	return ret;
}

void ANEntity::SetVisible(bool IsVisible)
{
	this->m_bIsVisible = IsVisible;
}

void ANEntity::SetEntityName(const char* szEntityName)
{
	auto LengthEntityName = strlen(szEntityName) + 1;
	memcpy(this->m_szEntityName = new char[LengthEntityName], szEntityName, LengthEntityName);
}

char* ANEntity::GetEntityName()
{
	return this->m_szEntityName;
}

