#pragma once
#include "Stage.h"
#include <memory>
using namespace std;
class StageManager
{
private:
	Stage* StageList;
	int count;
public:
	StageManager();
	StageManager(int count);
	~StageManager();
	void init_Stage();
	Stage* operator[](int level);
};

