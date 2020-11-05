// Include Windows header files
#include <Windows.h>
#include <windowsx.h>

// Other includes
#include <map>
#include <string>

/*
** Resources:
**
** Write your first windows application (Basics):
** https://docs.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
**
**
** Resource used to build this application:
** http://www.directxtutorial.com/Lesson.aspx?lessonid=11-1-3
**
**
** Documentaion on the messaging system (Events):
** https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues
**
**
** Win32 Documentation:
** https://docs.microsoft.com/en-us/windows/win32/
*/


// WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Handle for the window
	HWND hWnd;

	// This struct holds information for the window class
	WNDCLASSEX wc;

	// Clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Filling the cleared window class with needed information
	wc.cbSize = sizeof(WNDCLASSEX);           // Set window class size
	wc.style = CS_HREDRAW | CS_VREDRAW;       // Set window style
	wc.lpfnWndProc = WindowProc;              // Set window process
	wc.hInstance = hInstance;                 // set window handle instace
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Set window cursor
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;  // Set window background color
	wc.lpszClassName = L"WindowClass1";       // Set window class name

	// Register the window class
	RegisterClassEx(&wc);

	// Create rectangle wr
	RECT wr = { 0, 0, 1000, 800 };

	// Adjust size
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",       // Name of window class
		L"JGAME",              // Tile of window
		WS_OVERLAPPEDWINDOW,   // Style of window
		300,                   // X-Position of window
		300,                   // Y-Position of window
		wr.right,              // Width of window
		wr.bottom,             // Height of window
		NULL,                  // We currently have no parent window, NULL
		NULL,                  // We aren't using menus, NULL
		hInstance,             // Application handle
		NULL);                 // We don't have multiple windows, NULL

	// Display the window on the screen
	ShowWindow(hWnd, nCmdShow);


	/*
	**
	** Enter the main loop:
	**
	*/

	// This struct holds Windows event messages
	MSG msg = { 0 };

	// Enter infinite message loop
	while (true)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			// Translate keystroke message into the proper format
			TranslateMessage(&msg);

			// Send message to WindowProc function
			DispatchMessage(&msg);

			// Check if it's time to quit
			if (msg.message == WM_QUIT)
			{
				break;
			}

		}
	}

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

/*
** For more about messages and message queues:
** https://docs.microsoft.com/en-us/windows/win32/winmsg/about-messages-and-message-queues
*/

// Main message handler for program (Event Handler)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Sort through and fin what code to run for the message given
	switch (message)
	{
	case WM_DESTROY:
	{
		// Close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
