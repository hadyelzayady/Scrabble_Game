#include"pipes.h"
#include <locale>
#include <codecvt>
#include <iomanip>

#define BufferSize 1024
BOOL bResult;
BOOL bResult2;

pipe::pipe()
{

	this->PipeName.Format(_T("\\\\%s\\pipe\\%s"),
		_T("."),			// Server name
		_T("Server1")	// Pipe name
	);
	while (TRUE)
	{
		this->hPipe = CreateFile(
			this->PipeName,			// Pipe name 
			GENERIC_READ |			// Read and write access 
			GENERIC_WRITE,
			0,						// No sharing 
			NULL,					// Default security attributes
			OPEN_EXISTING,			// Opens existing pipe 
			0,						// Default attributes 
			NULL);					// No template file 

		// Break if the pipe handle is valid. 
		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		if (// Exit if an error other than ERROR_PIPE_BUSY occurs
			GetLastError() != ERROR_PIPE_BUSY
			||
			// All pipe instances are busy, so wait for 5 seconds
			!WaitNamedPipe(this->PipeName, 5000))
		{
			_tprintf(_T("Unable to open named pipe %s w/err 0x%08lx\n"),
				this->PipeName, GetLastError());
			break;
		}
	}
	_tprintf(_T("The named pipe, %s, is connected.\n"), this->PipeName);
	// Set data to be read from the pipe as a stream of messages
	DWORD dwMode = PIPE_READMODE_MESSAGE;
	bResult = SetNamedPipeHandleState(this->hPipe, &dwMode, NULL, NULL);
	if (!bResult)
		_tprintf(_T("SetNamedPipeHandleState failed w/err 0x%08lx\n"),
			GetLastError());

	// second pipe
	CString strPipeNameServer2;
	strPipeNameServer2.Format(_T("\\\\%s\\pipe\\%s"),
		_T("."),			// Server name
		_T("Server2")	// Pipe name
	);

	while (TRUE)
	{
		hPipe2 = CreateFile(
			strPipeNameServer2,			// Pipe name 
			GENERIC_READ |			// Read and write access 
			GENERIC_WRITE,
			0,						// No sharing 
			NULL,					// Default security attributes
			OPEN_EXISTING,			// Opens existing pipe 
			0,						// Default attributes 
			NULL);					// No template file 

		// Break if the pipe handle is valid. 
		if (hPipe2 != INVALID_HANDLE_VALUE)
			break;

		if (// Exit if an error other than ERROR_PIPE_BUSY occurs
			GetLastError() != ERROR_PIPE_BUSY
			||
			// All pipe instances are busy, so wait for 5 seconds
			!WaitNamedPipe(strPipeNameServer2, 5000))
		{
			_tprintf(_T("Unable to open named pipe %s w/err 0x%08lx\n"),
				strPipeNameServer2, GetLastError());
		}
	}
	DWORD dwMode2 = PIPE_READMODE_MESSAGE;
	bResult2 = SetNamedPipeHandleState(this->hPipe2, &dwMode, NULL, NULL);
	if (!bResult2)
		_tprintf(_T("SetNamedPipeHandleState failed w/err 0x%08lx\n"),
			GetLastError());
}

CString pipe::getPipeName()
{
	return this->PipeName;
}

void pipe::sendPipe(string Message)
{
	TCHAR chRequest[BufferSize];	// Client -> Server
	DWORD cbBytesWritten, cbRequestBytes;
	wstring stemp = std::wstring(Message.begin(), Message.end());
	LPCWSTR result = stemp.c_str();
	StringCchCopy(chRequest, BufferSize, result);
	cbRequestBytes = sizeof(TCHAR) * (lstrlen(chRequest) + 1);
	bResult = WriteFile(			// Write to the pipe.
		hPipe2,						// Handle of the pipe
		chRequest,					// Message to be written
		cbRequestBytes,				// Number of bytes to write
		&cbBytesWritten,			// Number of bytes written
		NULL);						// Not overlapped 

	if (!bResult/*Failed*/ || cbRequestBytes != cbBytesWritten/*Failed*/)
		_tprintf(_T("WriteFile failed w/err 0x%08lx\n"), GetLastError());

	_tprintf(_T("Sends %ld bytes; Message: \"%s\"\n"),
		cbBytesWritten, chRequest);
}

string pipe::readpipe()
{
	string Message;
	TCHAR chReply[BufferSize];		// Server -> Client
	DWORD cbBytesRead, cbReplyBytes;

	// Receive the response from the server.
	cbReplyBytes = sizeof(TCHAR) * BufferSize;
	bResult = ReadFile(			// Read from the pipe.
		hPipe,					// Handle of the pipe
		chReply,				// Buffer to receive the reply
		cbReplyBytes,			// Size of buffer 
		&cbBytesRead,			// Number of bytes read 
		NULL);					// Not overlapped 

	if (!bResult && GetLastError() != ERROR_MORE_DATA)
	{
		_tprintf(_T("ReadFile failed w/err 0x%08lx\n"), GetLastError());
		return " ";
	}

	/*_tprintf(_T("Receives %ld bytes; Message: \"%s\"\n"),
		cbBytesRead, chReply);*/
	wstring ws(chReply);
	int size = cbBytesRead / 2;
	Message = string(ws.begin(), ws.begin() + size);
	return Message;
}