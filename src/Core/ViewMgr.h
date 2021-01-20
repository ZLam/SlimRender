#pragma once

#include <vector>
#include "BaseView.h"

class ViewMgr
{
	std::vector<BaseView*> ViewArr;
	
public:
	ViewMgr();
	~ViewMgr();
	ViewMgr(const ViewMgr&) = delete;
	ViewMgr(ViewMgr&&) = delete;

	void RegisterViews();
	bool InitViews();
	void DrawViews();
};