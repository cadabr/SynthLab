#include "stdafx.h"
#include "LogMain.h"
#include "LogAppender.h"

LogMain::LogMain()
{
	plog::init(plog::debug, &LogAppender::getInstance());
	logWindow.reset(new LogWindow("LOG"));
}

void LogMain::Show()
{
	logWindow->setVisible(true);
}

void LogMain::Hide()
{
	logWindow->setVisible(false);
}
