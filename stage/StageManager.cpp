#include "StageManager.h"
StageManager::StageManager() : StageManager(3){

}
StageManager::StageManager(int count) : count(count)
{
	StageList = new Stage[count];
	init_Stage();
}
StageManager::~StageManager() {
	if (StageList != nullptr)
	{
		delete[] StageList;
		StageList = nullptr;
	}
}
void StageManager::init_Stage() {
	for (int i = 0; i < this->count; i++)
	{
		this->StageList[i] = Stage(40 - 2 * i, 20 - i, 20);
	}
}

Stage* StageManager::operator[](int level)
{
	if (level < 0 || level >= count)
	{
		return nullptr;
	}
	return &this->StageList[level];
}
