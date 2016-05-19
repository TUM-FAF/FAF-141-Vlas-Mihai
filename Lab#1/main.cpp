#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>

#define WND_BTN 1
#define TEXTBOX 2
#define BKGRND_BTN 3
#define FONT1_BTN 4
#define FONT2_BTN 5
#define FONT3_BTN 6
#define INPUT_TEXT 7
#define OUTPUT_TEXT 8
#define UPDATE_BTN 9
#define CLEAR_BTN 10
#define QUIT_BTN 11


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

COLORREF bkgndcolor = RGB(0,0,0);

// current instance
HINSTANCE hInst;
// The title bar text
TCHAR szTitle[500];
// the main window class name
TCHAR szWindowClass[500];


void change_bkgnd(HWND hWnd) {
        int iter;
        iter = (rand() % 4 + 1);
        switch(iter) {

            case 1: {
            bkgndcolor = RGB(195,200,115);
            InvalidateRect(hWnd,NULL, TRUE);

            break;
            }

            case 2: {
            bkgndcolor = RGB(200, 192.8, 88.15);
            InvalidateRect(hWnd,NULL, TRUE);

            break;
            }

            case 3:{
            bkgndcolor = RGB(113, 13.56, 44.80);
            InvalidateRect(hWnd,NULL, TRUE);

            break;
            }

            case 4: {
            bkgndcolor = RGB(10, 52.995, 40.58);
            InvalidateRect(hWnd,NULL, TRUE);

            break;
            }

        }
    }

int WINAPI WinMain ( HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow ) {

        /* This is the handle for our window */
        HWND hwnd;

        /* Here messages to the application are saved */
        MSG messages;

        /* Data structure for the window class */
        WNDCLASSEX wincl;

        wincl.hInstance = hThisInstance;
        wincl.lpszClassName = szClassName;

        /* This function is called by windows */
        wincl.lpfnWndProc = WindowProcedure;

        /* Catch double-clicks and redraw the window vertically and horizontally*/
        wincl.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
        wincl.cbSize = sizeof (WNDCLASSEX);
        wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);

        /* No menu */
        wincl.lpszMenuName = NULL;

        /* No extra bytes after the window class */
        wincl.cbClsExtra = 0;

        /* structure or the window instance */
        wincl.cbWndExtra = 0;
        wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

        if (!RegisterClassEx (&wincl))
        return 0;

        hwnd = CreateWindowEx (
           0,
           szClassName,
           _T("Lab1 PW"),
           WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           500,
           400,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

        ShowWindow (hwnd, nCmdShow);

        while (GetMessage (&messages, NULL, 0, 0)) {
            TranslateMessage(&messages);
            DispatchMessage(&messages);

        }

        return messages.wParam;
    }

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
        TCHAR info_string[] = "";
        static HWND hwndOutputText;
        static HWND hwndInputText;
        static HWND hwndTextbox;
        HINSTANCE hProgramInstance;
        HFONT hfFont;
        int iScreenW;
        int iScreenH;
        int iTextLength;
        char * szText;
        RECT rect;

        switch (message) {
            case WM_COMMAND: {
                switch(LOWORD(wParam)) {
                    case WND_BTN: {


                        int len = GetWindowTextLength(hwndTextbox) + 1;
                        static char title[500];

                        GetWindowText(hwndTextbox, title, len);
                        MessageBox(hwnd, title, "Message box", MB_OK | MB_ICONINFORMATION);

                    break;
                    }

                    case BKGRND_BTN: {
                        change_bkgnd(hwnd);

                    break;
                    }

                    case UPDATE_BTN: {
                        iTextLength = SendMessage(hwndInputText, WM_GETTEXTLENGTH, 0, 0);
                        szText = (char*)malloc(iTextLength+1);
                        SendMessage(hwndInputText, WM_GETTEXT, iTextLength+1, (LPARAM)szText);
                        SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)szText);
                        free(szText);

                    break;
                    }

                    case QUIT_BTN: {
                        if (MessageBox(NULL, TEXT("Are you sure you want to exit?"), TEXT("Exit?"),MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES) {
                            SendMessage(hwnd, WM_DESTROY, 0, 0);

                            };

                    break;
                    }

                    case FONT1_BTN: {
                        hfFont = CreateFont(20, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, TEXT("Times New Roman"));
                        SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);

                    break;
                    }

                    case FONT2_BTN: {
                        hfFont = CreateFont(42, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, TEXT("Courier New"));
                        SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);

                    break;
                    }

                    case FONT3_BTN: {
                        hfFont = CreateFont(25, 20, 30, 0, FW_DONTCARE, 0, 1, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                        CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, TEXT("Calibri"));
                        SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);

                    break;
                    }

                    case CLEAR_BTN: {
                        SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)"");

                    break;
                    }
                }

            break;
            }

            case WM_ERASEBKGND: {
                HPEN pen;
                HBRUSH	brush;
                RECT rect;

                pen=CreatePen(PS_SOLID, 1 , bkgndcolor);
                brush=CreateSolidBrush(bkgndcolor);
                SelectObject((HDC)wParam, pen);
                SelectObject((HDC)wParam, brush);
                GetClientRect(hwnd, &rect);
                Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);

            break;
            }

            case WM_CREATE: {
                hwndOutputText = CreateWindowEx(
                (DWORD)NULL,
                TEXT("edit"),
                TEXT("Lorem Ipsum"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_READONLY | ES_MULTILINE,
                10, 100, 270, 80,
                hwnd,
                (HMENU)OUTPUT_TEXT,
                hProgramInstance,
                NULL);

                hwndInputText = CreateWindowEx(
                (DWORD)NULL,
                TEXT("edit"),
                TEXT("Input text here"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
                10, 200, 200, 50,
                hwnd,
                (HMENU)INPUT_TEXT,
                hProgramInstance,
                NULL);


                CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),
                TEXT("Quit"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,
                220, 260, 60, 20,
                hwnd,
                (HMENU)QUIT_BTN,
                hProgramInstance,
                NULL);

                CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),
                TEXT("Times"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                10, 260, 60, 20,
                hwnd,
                (HMENU)FONT1_BTN,
                hProgramInstance,
                NULL);

                CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),
                TEXT("Courier"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                80, 260, 60, 20,
                hwnd,
                (HMENU)FONT2_BTN,
                hProgramInstance,
                NULL);

                CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),
                TEXT("Calibri"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                150, 260, 60, 20,
                hwnd,
                (HMENU)FONT3_BTN,
                hProgramInstance,
                NULL);

                CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),
                TEXT("Display"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                220, 200, 60, 20,
                hwnd,
                (HMENU)UPDATE_BTN,
                hProgramInstance,
                NULL);

                CreateWindowEx(
                (DWORD)NULL,
                TEXT("button"),
                TEXT("Erase"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                220, 230, 60, 20,
                hwnd,
                (HMENU)CLEAR_BTN,
                hProgramInstance,
                NULL);

                hfFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Times New Roman"));
                SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);

                hwndTextbox =   CreateWindow(TEXT("EDIT"),
                TEXT("This text will pop up in a new window"),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | WS_VSCROLL | ES_MULTILINE,
                10, 10, 270, 60,
                hwnd,
                (HMENU) TEXTBOX,
                NULL, NULL);

                CreateWindow(TEXT("BUTTON"),
                TEXT("Display text in a window"),
                WS_VISIBLE | WS_CHILD,
                300, 10, 200, 30,
                hwnd,
                (HMENU) WND_BTN,
                NULL, NULL);

                CreateWindow(TEXT("BUTTON"),
                TEXT("Change background color"),
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,
                300, 150, 200, 30,
                hwnd,
                (HMENU) BKGRND_BTN,
                NULL, NULL);

            break;
            }



            case WM_SYSCOLORCHANGE: {
                InvalidateRect (hwnd, NULL, TRUE) ;

            break ;
            }

            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint (hwnd, &ps);
                SetBkMode(hdc, TRANSPARENT);
                SetTextColor(hdc, RGB(9.8, 100, 92.2));
                TextOut(hdc, 0, 320, info_string, lstrlen(info_string));
                EndPaint (hwnd, &ps);

            break;
            }


            case WM_GETMINMAXINFO: {
                ((MINMAXINFO*)lParam)->ptMinTrackSize.x = 550;
                ((MINMAXINFO*)lParam)->ptMinTrackSize.y = 400;

            break;
            }



            case WM_NCHITTEST: {
                LRESULT hit = DefWindowProc(hwnd, message, wParam, lParam);

                if (hit == HTCLIENT) hit = HTCAPTION;
                return hit;

            break;
            }



            case WM_DRAWITEM: {
                if ((UINT)wParam == QUIT_BTN) {
                    LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                    SIZE size;
                    char szQuitBtnText[5];

                    strcpy(szQuitBtnText, "Exit");
                    GetTextExtentPoint32(lpdis->hDC, szQuitBtnText, strlen(szQuitBtnText), &size);
                    SetTextColor(lpdis->hDC, RGB(250, 250, 250));
                    SetBkColor(lpdis->hDC, RGB(200, 50, 50));

                    ExtTextOut(
                        lpdis->hDC,
                        ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                        ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                        ETO_OPAQUE | ETO_CLIPPED,
                        &lpdis->rcItem,
                        szQuitBtnText,
                        strlen(szQuitBtnText),
                        NULL);

                    DrawEdge(
                        lpdis->hDC,
                        &lpdis->rcItem,
                        (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                        BF_RECT);
                    return TRUE;
                }

                else if((UINT)wParam == BKGRND_BTN) {
                    LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
                    SIZE size;
                    char szChangeBtnText[22];

                    strcpy(szChangeBtnText, "Press to change Back");
                    GetTextExtentPoint32(lpdis->hDC, szChangeBtnText, strlen(szChangeBtnText), &size);
                    SetTextColor(lpdis->hDC, RGB(93.7, 100, 72.2));
                    SetBkColor(lpdis->hDC, RGB(20, 58.4, 89.8));

                    ExtTextOut(
                        lpdis->hDC,
                        ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,
                        ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,
                        ETO_OPAQUE | ETO_CLIPPED,
                        &lpdis->rcItem,
                        szChangeBtnText,
                        strlen(szChangeBtnText),
                        NULL);

                    DrawEdge(
                        lpdis->hDC,
                        &lpdis->rcItem,
                        (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                        BF_RECT);
                    return TRUE;
                }

            break;
            }









            default:

            return DefWindowProc (hwnd, message, wParam, lParam);

        }

    return 0;
    }
