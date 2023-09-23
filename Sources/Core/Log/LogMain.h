#pragma once

#include "LogWindow.h"
#include "LogStorage.h"

class LogMain
{
public:
	LogMain();

	void Show();

	void Hide();

private:
	std::unique_ptr<LogWindow> logWindow;
};
