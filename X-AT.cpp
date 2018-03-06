#define _CRT_SECURE_NO_WARNINGS
#include "skiui.h"
#include <time.h>
int menu_id = 0;
Window *win1 = NULL;

typedef Window* (*DllLoadPlugin)(HWND win, int x, int y, int w, int d);
typedef const char* (*DllGetPluginName)();
using namespace std;

string rootDir = "";//"C:\\Users\\ftp\\source\\repos\\skiui\\x64\\Release\\";

int xx = 0;
const int record_sec = 10;
const int fps = 5;
double countDown = 3000;
int mutex = 0;
tstring curProject = _T("none");
int forceStop = 0;
tim::timer t;
tstring main_dir = _T("none");
HINSTANCE hinst;
DllLoadPlugin loadPlugin;
DllGetPluginName getPluginName;
Label * vec = NULL;
void callback()
{
	size_t i = 0;
	WHILE_TRUE if (i == 1000)
	{
		//std::cout << "1000";
		break;
	}
	else
	{
		//std::cout << i;
		i++;
	}
	win1->showMenuPage(menu_id);
}

DWORD (WINAPI fun1)(LPVOID lpThreadParameter)
{
	loadPlugin(vec->_hwnd, 30, 30, 490, 350);
	return 0;
}
int main(int argc, char *argv[])
{
	global::init(&argc, &argv);
	
	tchar buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	rootDir = enc::t2a(buffer);
	int sz = rootDir.rfind(_T('\\'), rootDir.length());

	tstring sxx(_TS(rootDir));
	sxx.erase(sz +1);
	main_dir = sxx;

	win1 = Window::create(NULL, _TS("Window1"), 300, 300, 1200, 500);
	NoteBox *nbox1 = NoteBox::create(win1, _TS("NoteBox1"), 10, 10, 500, 400);
	vec = Label::create(win1, _TS(""), 0, 0, 490, 364);
	int page_id = nbox1->addPage(-1, _T("APNG录制插件"));
	nbox1->addWidget(vec, 1, true, 4, 5);
	GroupBox *gbox1 = GroupBox::create(win1, _TS("GroupBox1"), 550, 3, 350, 230);
    Edit *edit1 = Edit::create(win1, _TS("edit1"), 900, 60, 200);

	menu_id = win1->createMenuPage(0, _TS("page1"), false);
    int item_id = win1->createMenuPageItem(menu_id, _TS("item1"), callback);
	int menu_id2 = win1->createMenuPage(0, _TS("menu"));
    int item_id2 = win1->createMenuPageItem(menu_id2, _TS("item2"), callback);

	tstring recordPluginDllDir = main_dir + _T("plugin\\record_plugin\\child.dll");
	//tstring recordPluginDllDir = _T("C:\\Users\\ftp\\source\\repos\\child\\x64\\Release\\child.dll");
	hinst = LoadLibraryEx(recordPluginDllDir.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	loadPlugin = (DllLoadPlugin)GetProcAddress(hinst, "loadPlugin");
	getPluginName = (DllGetPluginName)GetProcAddress(hinst, "getPluginName");
	tim::__doEvents();
	if (NULL != hinst)
	{
		if (loadPlugin)
		{
			std::cout<< "主程序：插件加载"<<std::endl;
			loadPlugin(vec->_hwnd, 30, 30, 490, 350);
		}
		if (getPluginName)
		{
			std::cout << getPluginName() << std::endl;
		}
	}
	return global::loop();
}