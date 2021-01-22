#include "ViewMgr.h"

#include <iostream>
#include "View/StatView.h"
#include "View/TestView.h"

ViewMgr::ViewMgr()
{
	
}

ViewMgr::~ViewMgr()
{
	if (!ViewArr.empty())
	{
		for (BaseView* View : ViewArr)
		{
			delete View;
			View = nullptr;
		}
		ViewArr.clear();
	}
}

void ViewMgr::RegisterViews()
{
	ViewArr.push_back(new StatView("StatView"));
	ViewArr.push_back(new TestView("TestView"));
}

bool ViewMgr::InitViews()
{
	bool ret = true;
	if (!ViewArr.empty())
	{
		for (BaseView* View : ViewArr)
		{
			if (!View->Init())
			{
				ret = false;
				std::cout << "[ViewMgr] init " << View->GetName() << " fail" << std::endl;
			}
		}
	}
	return ret;
}

void ViewMgr::DrawViews()
{
	if (!ViewArr.empty())
	{
		for (BaseView* View : ViewArr)
		{
			View->Draw();
		}
	}
}
