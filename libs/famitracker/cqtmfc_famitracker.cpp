#include "cqtmfc.h"
#include "cqtmfc_famitracker.h"
#include "resource.h"

#include "stdafx.h"

#include "FamiTrackerDoc.h"

#ifdef _WIN32
#include <windows.h>
#include <afxwin.h> // Include MFC headers
typedef unsigned int UINT;
#else
#include <QToolBar>
typedef unsigned int UINT;
#endif

#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QFrame>


// Some constants
#ifndef IDOK
#define IDOK 1
#endif

#ifndef IDCANCEL
#define IDCANCEL 2
#endif

#ifndef IDC_STATIC
#define IDC_STATIC -1
#endif

#ifndef IDC_CHANNELS_NR
#define IDC_CHANNELS_NR 1001
#endif

#ifndef IDC_SONGLIST
#define IDC_SONGLIST 1002
#endif

#ifndef IDC_SONG_ADD
#define IDC_SONG_ADD 1003
#endif

#ifndef IDC_SONG_REMOVE
#define IDC_SONG_REMOVE 1004
#endif

#ifndef IDC_SONG_UP
#define IDC_SONG_UP 1005
#endif

#ifndef IDC_SONG_DOWN
#define IDC_SONG_DOWN 1006
#endif

#ifndef IDC_SONG_IMPORT
#define IDC_SONG_IMPORT 1007
#endif

#ifndef IDC_SONGNAME
#define IDC_SONGNAME 1008
#endif

#ifndef IDC_EXPANSION
#define IDC_EXPANSION 1009
#endif

#ifndef IDC_VIBRATO
#define IDC_VIBRATO 1010
#endif

#ifndef IDC_CHANNELS
#define IDC_CHANNELS 1011
#endif




void qtMfcInitMenuResource_IDR_MAINFRAME(CMenu *parent)
{
	QAction *menuAction;

	// IDR_MAINFRAME MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "&File"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&File");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&File");

	// BEGIN
	// MENUITEM "&New\tCtrl+N", ID_FILE_NEW
	subMenu->AppendMenu(MF_STRING, ID_FILE_NEW, "&New\tCtrl+N");

	// MENUITEM "&Open...\tCtrl+O", ID_FILE_OPEN
	subMenu->AppendMenu(MF_STRING, ID_FILE_OPEN, "&Open...\tCtrl+O");

	// MENUITEM "&Save\tCtrl+S", ID_FILE_SAVE
	subMenu->AppendMenu(MF_STRING, ID_FILE_SAVE, "&Save\tCtrl+S");

	// MENUITEM "Save &As...", ID_FILE_SAVE_AS
	subMenu->AppendMenu(MF_STRING, ID_FILE_SAVE_AS, "Save &As...");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "&Create NSF...\tCtrl+E", ID_FILE_CREATE_NSF
	subMenu->AppendMenu(MF_STRING, ID_FILE_CREATE_NSF, "&Create NSF...\tCtrl+E");

	// MENUITEM "Create WAV...", ID_FILE_CREATEWAV
	subMenu->AppendMenu(MF_STRING, ID_FILE_CREATEWAV, "Create WAV...");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Import text...", ID_FILE_IMPORTTEXT
	subMenu->AppendMenu(MF_STRING, ID_FILE_IMPORTTEXT, "Import text...");

	// MENUITEM "Export text...", ID_FILE_EXPORTTEXT
	subMenu->AppendMenu(MF_STRING, ID_FILE_EXPORTTEXT, "Export text...");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "&Configuration", ID_FILE_GENERALSETTINGS
	subMenu->AppendMenu(MF_STRING, ID_FILE_GENERALSETTINGS, "&Configuration");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Recent File", ID_FILE_MRU_FILE1
	subMenu->AppendMenu(MF_STRING, ID_FILE_MRU_FILE1, "Recent File");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "E&xit\tAlt+F4", ID_APP_EXIT
	subMenu->AppendMenu(MF_STRING, ID_APP_EXIT, "E&xit\tAlt+F4");

	// END
	subMenu = subMenuTree.takeLast();

	// POPUP "&Edit"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Edit");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Edit");

	// BEGIN
	// MENUITEM "&Undo\tCtrl+Z", ID_EDIT_UNDO
	subMenu->AppendMenu(MF_STRING, ID_EDIT_UNDO, "&Undo\tCtrl+Z");

	// MENUITEM "&Redo\tCtrl+Y", ID_EDIT_REDO
	subMenu->AppendMenu(MF_STRING, ID_EDIT_REDO, "&Redo\tCtrl+Y");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Cu&t\tCtrl+X", ID_EDIT_CUT
	subMenu->AppendMenu(MF_STRING, ID_EDIT_CUT, "Cu&t\tCtrl+X");

	// MENUITEM "&Copy\tCtrl+C", ID_EDIT_COPY
	subMenu->AppendMenu(MF_STRING, ID_EDIT_COPY, "&Copy\tCtrl+C");

	// MENUITEM "&Paste\tCtrl+V", ID_EDIT_PASTE
	subMenu->AppendMenu(MF_STRING, ID_EDIT_PASTE, "&Paste\tCtrl+V");

	// MENUITEM "Paste (mix)", ID_EDIT_PASTEMIX
	subMenu->AppendMenu(MF_STRING, ID_EDIT_PASTEMIX, "Paste (mix)");

	// MENUITEM "&Delete\tDel", ID_EDIT_DELETE
	subMenu->AppendMenu(MF_STRING, ID_EDIT_DELETE, "&Delete\tDel");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Select &All\tCtrl+A", ID_EDIT_SELECTALL
	subMenu->AppendMenu(MF_STRING, ID_EDIT_SELECTALL, "Select &All\tCtrl+A");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// POPUP "Transpose"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Transpose");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Transpose");

	// BEGIN
	// MENUITEM "Decrease Note\tCtrl+F1", ID_TRANSPOSE_DECREASENOTE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_DECREASENOTE, "Decrease Note\tCtrl+F1");

	// MENUITEM "Increase Note\tCtrl+F2", ID_TRANSPOSE_INCREASENOTE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_INCREASENOTE, "Increase Note\tCtrl+F2");

	// MENUITEM "Decrease Octave\tCtrl+F3", ID_TRANSPOSE_DECREASEOCTAVE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_DECREASEOCTAVE, "Decrease Octave\tCtrl+F3");

	// MENUITEM "Increase Octave\tCtrl+F4", ID_TRANSPOSE_INCREASEOCTAVE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_INCREASEOCTAVE, "Increase Octave\tCtrl+F4");

	// END
	subMenu = subMenuTree.takeLast();

	// MENUITEM "Interpolate\tCtrl+G", ID_EDIT_INTERPOLATE
	subMenu->AppendMenu(MF_STRING, ID_EDIT_INTERPOLATE, "Interpolate\tCtrl+G");

	// MENUITEM "&Reverse\tCtrl+R", ID_EDIT_REVERSE
	subMenu->AppendMenu(MF_STRING, ID_EDIT_REVERSE, "&Reverse\tCtrl+R");

	// MENUITEM "R&eplace instrument\tAlt+S", ID_EDIT_REPLACEINSTRUMENT
	subMenu->AppendMenu(MF_STRING, ID_EDIT_REPLACEINSTRUMENT, "R&eplace instrument\tAlt+S");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Expand pattern", ID_EDIT_EXPANDPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_EDIT_EXPANDPATTERNS, "Expand pattern");

	// MENUITEM "Shrink pattern", ID_EDIT_SHRINKPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_EDIT_SHRINKPATTERNS, "Shrink pattern");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Clear patterns", ID_EDIT_CLEARPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_EDIT_CLEARPATTERNS, "Clear patterns");

	// POPUP "Clean up"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Clean up");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Clean up");

	// BEGIN
	// MENUITEM "Remove unused instruments", ID_CLEANUP_REMOVEUNUSEDINSTRUMENTS
	subMenu->AppendMenu(MF_STRING, ID_CLEANUP_REMOVEUNUSEDINSTRUMENTS, "Remove unused instruments");

	// MENUITEM "Remove unused patterns", ID_CLEANUP_REMOVEUNUSEDPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_CLEANUP_REMOVEUNUSEDPATTERNS, "Remove unused patterns");

	// MENUITEM "Merge duplicated patterns", ID_CLEANUP_MERGEDUPLICATEDPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_CLEANUP_MERGEDUPLICATEDPATTERNS, "Merge duplicated patterns");

	// END
	subMenu = subMenuTree.takeLast();

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Instrument Mask\tAlt+T", ID_EDIT_INSTRUMENTMASK
	subMenu->AppendMenu(MF_STRING, ID_EDIT_INSTRUMENTMASK, "Instrument Mask\tAlt+T");

	// MENUITEM "Volume Mask", ID_EDIT_VOLUMEMASK
	subMenu->AppendMenu(MF_CHECKED | MF_STRING, ID_EDIT_VOLUMEMASK, "Volume Mask");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Enable MIDI", ID_EDIT_ENABLEMIDI
	subMenu->AppendMenu(MF_STRING, ID_EDIT_ENABLEMIDI, "Enable MIDI");

	// END
	subMenu = subMenuTree.takeLast();

	// POPUP "&Module"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Module");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Module");

	// BEGIN
	// MENUITEM "Insert frame", ID_MODULE_INSERTFRAME
	subMenu->AppendMenu(MF_STRING, ID_MODULE_INSERTFRAME, "Insert frame");

	// MENUITEM "Remove frame", ID_MODULE_REMOVEFRAME
	subMenu->AppendMenu(MF_STRING, ID_MODULE_REMOVEFRAME, "Remove frame");

	// MENUITEM "&Duplicate frame", ID_MODULE_DUPLICATEFRAME
	subMenu->AppendMenu(MF_STRING, ID_MODULE_DUPLICATEFRAME, "&Duplicate frame");

	// MENUITEM "Duplicate patterns", ID_MODULE_DUPLICATEFRAMEPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_MODULE_DUPLICATEFRAMEPATTERNS, "Duplicate patterns");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Move Frame Up", ID_MODULE_MOVEFRAMEUP
	subMenu->AppendMenu(MF_STRING, ID_MODULE_MOVEFRAMEUP, "Move Frame Up");

	// MENUITEM "Move Frame Down", ID_MODULE_MOVEFRAMEDOWN
	subMenu->AppendMenu(MF_STRING, ID_MODULE_MOVEFRAMEDOWN, "Move Frame Down");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Comments", ID_MODULE_COMMENTS
	subMenu->AppendMenu(MF_STRING, ID_MODULE_COMMENTS, "Comments");

	// MENUITEM "Module Properties\tCtrl+P", ID_MODULE_MODULEPROPERTIES
	subMenu->AppendMenu(MF_STRING, ID_MODULE_MODULEPROPERTIES, "Module Properties\tCtrl+P");

	// MENUITEM "Channels", ID_MODULE_CHANNELS
	subMenu->AppendMenu(MF_STRING, ID_MODULE_CHANNELS, "Channels");

	// END
	subMenu = subMenuTree.takeLast();

	// POPUP "&Instrument"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Instrument");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Instrument");

	// BEGIN
	// MENUITEM "New instrument", ID_INSTRUMENT_NEW
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_NEW, "New instrument");

	// MENUITEM "Remove instrument", ID_INSTRUMENT_REMOVE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_REMOVE, "Remove instrument");

	// MENUITEM "Clone instrument", ID_INSTRUMENT_CLONE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_CLONE, "Clone instrument");

	// MENUITEM "Deep clone instrument", ID_INSTRUMENT_DEEPCLONE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_DEEPCLONE, "Deep clone instrument");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Load from file...", ID_INSTRUMENT_LOAD
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_LOAD, "Load from file...");

	// MENUITEM "Save to file...", ID_INSTRUMENT_SAVE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_SAVE, "Save to file...");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Edit\tCtrl+I", ID_INSTRUMENT_EDIT
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_EDIT, "Edit\tCtrl+I");

	// END
	subMenu = subMenuTree.takeLast();

	// POPUP "T&racker"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "T&racker");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "T&racker");

	// BEGIN
	// MENUITEM "&Play\tReturn", ID_TRACKER_PLAY
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_PLAY, "&Play\tReturn");

	// MENUITEM "P&lay Pattern\tShift+Return", ID_TRACKER_PLAYPATTERN
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_PLAYPATTERN, "P&lay Pattern\tShift+Return");

	// MENUITEM "Play from start", ID_TRACKER_PLAY_START
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_PLAY_START, "Play from start");

	// MENUITEM "Play from cursor", ID_TRACKER_PLAY_CURSOR
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_PLAY_CURSOR, "Play from cursor");

	// MENUITEM "&Stop\tReturn", ID_TRACKER_STOP
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_STOP, "&Stop\tReturn");

	// MENUITEM "Toggle &Edit mode\tSpace", ID_TRACKER_EDIT
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_EDIT, "Toggle &Edit mode\tSpace");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Toggle channel\tAlt+F9", ID_TRACKER_TOGGLECHANNEL
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_TOGGLECHANNEL, "Toggle channel\tAlt+F9");

	// MENUITEM "Solo channel\tAlt+F10", ID_TRACKER_SOLOCHANNEL
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_SOLOCHANNEL, "Solo channel\tAlt+F10");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Switch to track instrument", ID_TRACKER_SWITCHTOTRACKINSTRUMENT
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_SWITCHTOTRACKINSTRUMENT, "Switch to track instrument");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Display register state", ID_TRACKER_DISPLAYREGISTERSTATE
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_DISPLAYREGISTERSTATE, "Display register state");

	// MENUITEM "&Display DPCM state", ID_TRACKER_DPCM
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_DPCM, "&Display DPCM state");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "&Kill Sound\tF12", ID_TRACKER_KILLSOUND
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_KILLSOUND, "&Kill Sound\tF12");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "NTSC", ID_TRACKER_NTSC
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_NTSC, "NTSC");

	// MENUITEM "PAL", ID_TRACKER_PAL
	subMenu->AppendMenu(MF_STRING, ID_TRACKER_PAL, "PAL");

	// POPUP "Engine Speed"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Engine Speed");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Engine Speed");

	// BEGIN
	// MENUITEM "Default", ID_SPEED_DEFAULT
	subMenu->AppendMenu(MF_STRING, ID_SPEED_DEFAULT, "Default");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Custom", ID_SPEED_CUSTOM
	subMenu->AppendMenu(MF_STRING, ID_SPEED_CUSTOM, "Custom");

	// END
	subMenu = subMenuTree.takeLast();

	// END
	subMenu = subMenuTree.takeLast();

	// POPUP "&View"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&View");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&View");

	// BEGIN
	// MENUITEM "&Toolbar", ID_VIEW_TOOLBAR
	subMenu->AppendMenu(MF_STRING, ID_VIEW_TOOLBAR, "&Toolbar");

	// MENUITEM "&Status Bar", ID_VIEW_STATUS_BAR
	subMenu->AppendMenu(MF_STRING, ID_VIEW_STATUS_BAR, "&Status Bar");

	// MENUITEM "Control panel", ID_VIEW_CONTROLPANEL
	subMenu->AppendMenu(MF_STRING, ID_VIEW_CONTROLPANEL, "Control panel");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// POPUP "Frame editor position"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Frame editor position");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Frame editor position");

	// BEGIN
	// MENUITEM "Top", ID_FRAMEEDITOR_TOP
	subMenu->AppendMenu(MF_CHECKED | MF_STRING, ID_FRAMEEDITOR_TOP, "Top");

	// MENUITEM "Left", ID_FRAMEEDITOR_LEFT
	subMenu->AppendMenu(MF_STRING, ID_FRAMEEDITOR_LEFT, "Left");

	// END
	subMenu = subMenuTree.takeLast();

	// END
	subMenu = subMenuTree.takeLast();

	// POPUP "&Help"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Help");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "&Help");

	// BEGIN
	// MENUITEM "&Help Topics\tF1", ID_HELP_FINDER
	subMenu->AppendMenu(MF_STRING, ID_HELP_FINDER, "&Help Topics\tF1");

	// MENUITEM "Effect table", ID_HELP_EFFECTTABLE
	subMenu->AppendMenu(MF_STRING, ID_HELP_EFFECTTABLE, "Effect table");

	// MENUITEM "FAQ", ID_HELP_FAQ
	subMenu->AppendMenu(MF_STRING, ID_HELP_FAQ, "FAQ");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Performance", ID_HELP_PERFORMANCE
	subMenu->AppendMenu(MF_STRING, ID_HELP_PERFORMANCE, "Performance");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "&About FamiTracker...", ID_APP_ABOUT
	subMenu->AppendMenu(MF_STRING, ID_APP_ABOUT, "&About FamiTracker...");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_PATTERN_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_PATTERN_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Popup"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");

	// BEGIN
	// MENUITEM "&Undo", ID_EDIT_UNDO
	subMenu->AppendMenu(MF_STRING, ID_EDIT_UNDO, "&Undo");

	// MENUITEM "&Redo", ID_EDIT_REDO
	subMenu->AppendMenu(MF_STRING, ID_EDIT_REDO, "&Redo");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Cu&t", ID_EDIT_CUT
	subMenu->AppendMenu(MF_STRING, ID_EDIT_CUT, "Cu&t");

	// MENUITEM "&Copy", ID_EDIT_COPY
	subMenu->AppendMenu(MF_STRING, ID_EDIT_COPY, "&Copy");

	// MENUITEM "&Paste", ID_EDIT_PASTE
	subMenu->AppendMenu(MF_STRING, ID_EDIT_PASTE, "&Paste");

	// MENUITEM "&Delete", ID_POPUP_DELETE
	subMenu->AppendMenu(MF_STRING, ID_POPUP_DELETE, "&Delete");

	// MENUITEM "Select &All", ID_EDIT_SELECTALL
	subMenu->AppendMenu(MF_STRING, ID_EDIT_SELECTALL, "Select &All");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// POPUP "Transpose"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Transpose");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Transpose");

	// BEGIN
	// MENUITEM "Increase Note", ID_TRANSPOSE_INCREASENOTE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_INCREASENOTE, "Increase Note");

	// MENUITEM "Decrease Note", ID_TRANSPOSE_DECREASENOTE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_DECREASENOTE, "Decrease Note");

	// MENUITEM "Increase Octave", ID_TRANSPOSE_INCREASEOCTAVE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_INCREASEOCTAVE, "Increase Octave");

	// MENUITEM "Decrease Octave", ID_TRANSPOSE_DECREASEOCTAVE
	subMenu->AppendMenu(MF_STRING, ID_TRANSPOSE_DECREASEOCTAVE, "Decrease Octave");

	// END
	subMenu = subMenuTree.takeLast();

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "&Interpolate", ID_EDIT_INTERPOLATE
	subMenu->AppendMenu(MF_STRING, ID_EDIT_INTERPOLATE, "&Interpolate");

	// MENUITEM "&Reverse", ID_EDIT_REVERSE
	subMenu->AppendMenu(MF_STRING, ID_EDIT_REVERSE, "&Reverse");

	// MENUITEM "Pick up row", ID_POPUP_PICKUPROW
	subMenu->AppendMenu(MF_STRING, ID_POPUP_PICKUPROW, "Pick up row");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Expand pattern", ID_EDIT_EXPANDPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_EDIT_EXPANDPATTERNS, "Expand pattern");

	// MENUITEM "Shrink pattern", ID_EDIT_SHRINKPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_EDIT_SHRINKPATTERNS, "Shrink pattern");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "R&eplace instrument", ID_EDIT_REPLACEINSTRUMENT
	subMenu->AppendMenu(MF_STRING, ID_EDIT_REPLACEINSTRUMENT, "R&eplace instrument");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "&Toggle channel", ID_POPUP_TOGGLECHANNEL
	subMenu->AppendMenu(MF_STRING, ID_POPUP_TOGGLECHANNEL, "&Toggle channel");

	// MENUITEM "&Solo channel", ID_POPUP_SOLOCHANNEL
	subMenu->AppendMenu(MF_STRING, ID_POPUP_SOLOCHANNEL, "&Solo channel");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_FRAME_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_FRAME_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Frame"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Frame");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Frame");

	// BEGIN
	// MENUITEM "&Insert frame\tIns", ID_MODULE_INSERTFRAME
	subMenu->AppendMenu(MF_STRING, ID_MODULE_INSERTFRAME, "&Insert frame\tIns");

	// MENUITEM "&Remove frame\tDel", ID_MODULE_REMOVEFRAME
	subMenu->AppendMenu(MF_STRING, ID_MODULE_REMOVEFRAME, "&Remove frame\tDel");

	// MENUITEM "&Duplicate frame", ID_MODULE_DUPLICATEFRAME
	subMenu->AppendMenu(MF_STRING, ID_MODULE_DUPLICATEFRAME, "&Duplicate frame");

	// MENUITEM "D&uplicate patterns", ID_MODULE_DUPLICATEFRAMEPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_MODULE_DUPLICATEFRAMEPATTERNS, "D&uplicate patterns");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Move &up", ID_MODULE_MOVEFRAMEUP
	subMenu->AppendMenu(MF_STRING, ID_MODULE_MOVEFRAMEUP, "Move &up");

	// MENUITEM "Move d&own", ID_MODULE_MOVEFRAMEDOWN
	subMenu->AppendMenu(MF_STRING, ID_MODULE_MOVEFRAMEDOWN, "Move d&own");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Cu&t\tCtrl+X", ID_FRAME_CUT
	subMenu->AppendMenu(MF_STRING, ID_FRAME_CUT, "Cu&t\tCtrl+X");

	// MENUITEM "&Copy\tCtrl+C", ID_FRAME_COPY
	subMenu->AppendMenu(MF_STRING, ID_FRAME_COPY, "&Copy\tCtrl+C");

	// MENUITEM "&Paste\tCtrl+V", ID_FRAME_PASTE
	subMenu->AppendMenu(MF_STRING, ID_FRAME_PASTE, "&Paste\tCtrl+V");

	// MENUITEM "Paste && duplicate", ID_FRAME_PASTENEWPATTERNS
	subMenu->AppendMenu(MF_STRING, ID_FRAME_PASTENEWPATTERNS, "Paste && duplicate");

	// MENUITEM "D&elete\tDel", ID_FRAME_DELETE
	subMenu->AppendMenu(MF_STRING, ID_FRAME_DELETE, "D&elete\tDel");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_INSTRUMENT_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_INSTRUMENT_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Instrument"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Instrument");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Instrument");

	// BEGIN
	// MENUITEM "Add", ID_INSTRUMENT_NEW
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_NEW, "Add");

	// MENUITEM "Remove", ID_INSTRUMENT_REMOVE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_REMOVE, "Remove");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "&Load from file...", ID_INSTRUMENT_LOAD
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_LOAD, "&Load from file...");

	// MENUITEM "&Save to file...", ID_INSTRUMENT_SAVE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_SAVE, "&Save to file...");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Clone instrument", ID_INSTRUMENT_CLONE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_CLONE, "Clone instrument");

	// MENUITEM "Deep clone instrument", ID_INSTRUMENT_DEEPCLONE
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_DEEPCLONE, "Deep clone instrument");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Edit", ID_INSTRUMENT_EDIT
	subMenu->AppendMenu(MF_STRING, ID_INSTRUMENT_EDIT, "Edit");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_SAMPLES_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_SAMPLES_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Popup"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");

	// BEGIN
	// MENUITEM "Preview", IDC_PREVIEW
	subMenu->AppendMenu(MF_STRING, IDC_PREVIEW, "Preview");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Edit", IDC_EDIT
	subMenu->AppendMenu(MF_STRING, IDC_EDIT, "Edit");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Unload", IDC_UNLOAD
	subMenu->AppendMenu(MF_STRING, IDC_UNLOAD, "Unload");

	// MENUITEM "Save", IDC_SAVE
	subMenu->AppendMenu(MF_STRING, IDC_SAVE, "Save");

	// MENUITEM "Load", IDC_LOAD
	subMenu->AppendMenu(MF_STRING, IDC_LOAD, "Load");

	// MENUITEM "Import", IDC_IMPORT
	subMenu->AppendMenu(MF_STRING, IDC_IMPORT, "Import");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_SAMPLE_WND_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_SAMPLE_WND_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Popup"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");

	// BEGIN
	// MENUITEM "Sample scope", ID_POPUP_SAMPLESCOPE1
	subMenu->AppendMenu(MF_STRING, ID_POPUP_SAMPLESCOPE1, "Sample scope");

	// MENUITEM "Sample scope (blur)", ID_POPUP_SAMPLESCOPE2
	subMenu->AppendMenu(MF_STRING, ID_POPUP_SAMPLESCOPE2, "Sample scope (blur)");

	// MENUITEM "Spectrum analyzer", ID_POPUP_SPECTRUMANALYZER
	subMenu->AppendMenu(MF_STRING, ID_POPUP_SPECTRUMANALYZER, "Spectrum analyzer");

	// MENUITEM "Nothing", ID_POPUP_NOTHING
	subMenu->AppendMenu(MF_STRING, ID_POPUP_NOTHING, "Nothing");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_PATTERN_HEADER_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_PATTERN_HEADER_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Popup"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");

	// BEGIN
	// MENUITEM "&Toggle channel\tAlt+F9", ID_POPUP_TOGGLECHANNEL
	subMenu->AppendMenu(MF_STRING, ID_POPUP_TOGGLECHANNEL, "&Toggle channel\tAlt+F9");

	// MENUITEM "&Solo channel\tAlt+F10", ID_POPUP_SOLOCHANNEL
	subMenu->AppendMenu(MF_STRING, ID_POPUP_SOLOCHANNEL, "&Solo channel\tAlt+F10");

	// MENUITEM "&Unmute all channels", ID_POPUP_UNMUTEALLCHANNELS
	subMenu->AppendMenu(MF_STRING, ID_POPUP_UNMUTEALLCHANNELS, "&Unmute all channels");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_SAMPLE_EDITOR_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_SAMPLE_EDITOR_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Popup"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");

	// BEGIN
	// MENUITEM "Play\tP", IDC_PLAY
	subMenu->AppendMenu(MF_STRING, IDC_PLAY, "Play\tP");

	// MENUITEM SEPARATOR
	subMenu->AppendMenu(MF_SEPARATOR);

	// MENUITEM "Delete\tDel", IDC_DELETE
	subMenu->AppendMenu(MF_STRING, IDC_DELETE, "Delete\tDel");

	// MENUITEM "Tilt", IDC_TILT
	subMenu->AppendMenu(MF_STRING, IDC_TILT, "Tilt");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource_IDR_SEQUENCE_POPUP(CMenu *parent)
{
	QAction *menuAction;

	// IDR_SEQUENCE_POPUP MENU
	// BEGIN
	QList<CMenu *> subMenuTree;
	CMenu *subMenu;

	// POPUP "Popup"
	subMenu = new CMenu;
	subMenuTree.append(subMenu);
	QObject::connect(subMenu->toQMenu(), SIGNAL(aboutToShow()), subMenu, SLOT(menu_aboutToShow()));
	if (subMenuTree.count() == 1)
		parent->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");
	else
		subMenuTree.at(subMenuTree.count() - 2)->AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)subMenu->m_hMenu, "Popup");

	// BEGIN
	// MENUITEM "&Clone sequence", ID_CLONE_SEQUENCE
	subMenu->AppendMenu(MF_STRING, ID_CLONE_SEQUENCE, "&Clone sequence");

	// END
	subMenu = subMenuTree.takeLast();

	// END
}

void qtMfcInitMenuResource(UINT menuID, CMenu *parent)
{
	switch (menuID)
	{
	case IDR_MAINFRAME:
		qtMfcInitMenuResource_IDR_MAINFRAME(parent);
		break;

	case IDR_PATTERN_POPUP:
		qtMfcInitMenuResource_IDR_PATTERN_POPUP(parent);
		break;

	case IDR_FRAME_POPUP:
		qtMfcInitMenuResource_IDR_FRAME_POPUP(parent);
		break;

	case IDR_INSTRUMENT_POPUP:
		qtMfcInitMenuResource_IDR_INSTRUMENT_POPUP(parent);
		break;

	case IDR_SAMPLES_POPUP:
		qtMfcInitMenuResource_IDR_SAMPLES_POPUP(parent);
		break;

	case IDR_SAMPLE_WND_POPUP:
		qtMfcInitMenuResource_IDR_SAMPLE_WND_POPUP(parent);
		break;

	case IDR_PATTERN_HEADER_POPUP:
		qtMfcInitMenuResource_IDR_PATTERN_HEADER_POPUP(parent);
		break;

	case IDR_SAMPLE_EDITOR_POPUP:
		qtMfcInitMenuResource_IDR_SAMPLE_EDITOR_POPUP(parent);
		break;

	case IDR_SEQUENCE_POPUP:
		qtMfcInitMenuResource_IDR_SEQUENCE_POPUP(parent);
		break;
	}

	// Fixup shortcuts
	int menu = 0;
	CMenu *subMenu = parent->GetSubMenu(menu);
	while (subMenu)
	{
		foreach (QAction *action, subMenu->toQMenu()->actions())
		{
			if (action->text().contains("\t"))
			{
				action->setShortcut(QKeySequence(action->text().split("\t").at(1)));
			}
		}
		menu++;
		subMenu = parent->GetSubMenu(menu);
	}
}

void qtMfcInitStringResources()
{
	qtMfcStringResources.clear();

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDR_MAINFRAME, "FamiTracker\n\nFamiTracker\nFamiTracker files (*.ftm)\n.ftm\nFamiTracker.Module\nFamiTracker.Module");
	qtMfcStringResources.insert(IDS_FRAME_DROP_MOVE, "Drop selection to move frames");
	qtMfcStringResources.insert(IDS_DPCM_IMPORT_QUALITY_FORMAT, "Quality: %1");
	qtMfcStringResources.insert(IDS_CLIPBOARD_ERROR, "Could not register clipboard format");
	qtMfcStringResources.insert(IDS_FILE_OPEN_ERROR, "Could not open the file!");
	qtMfcStringResources.insert(IDS_FILE_VALID_ERROR, "File is not a valid FamiTracker module");
	qtMfcStringResources.insert(IDS_FILE_VERSION_ERROR, "File version is not supported");
	qtMfcStringResources.insert(IDS_INST_LIMIT, "You cannot add more instruments");
	qtMfcStringResources.insert(IDS_CLIPBOARD_OPEN_ERROR, "Cannot open clipboard.");
	qtMfcStringResources.insert(IDS_CLIPBOARD_NOT_AVALIABLE, "Clipboard data is not available.");
	qtMfcStringResources.insert(ID_TRACKER_PLAY_START, "Play module from start");
	qtMfcStringResources.insert(IDS_INSTRUMENT_FILE_FAIL, "Instrument file was not vaild");
	qtMfcStringResources.insert(IDS_CLIPPING_MESSAGE, "Warning: Audio is clipping, decrease mixing levels!");
	qtMfcStringResources.insert(IDS_FILTER_FTI, "FamiTracker Instrument (*.fti)");
	qtMfcStringResources.insert(IDS_SAVE_FILE_ERROR, "Could not save file: %1");
	qtMfcStringResources.insert(IDS_START_ERROR, "Program could not start properly, default settings has been restored. Please restart the program.");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(AFX_IDS_APP_TITLE, "FamiTracker");
	qtMfcStringResources.insert(AFX_IDS_IDLEMESSAGE, "For Help, press F1");
	qtMfcStringResources.insert(AFX_IDS_HELPMODEMESSAGE, "Select an object on which to get Help");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_INDICATOR_EXT, "EXT");
	qtMfcStringResources.insert(ID_INDICATOR_CAPS, "CAP");
	qtMfcStringResources.insert(ID_INDICATOR_NUM, "NUM");
	qtMfcStringResources.insert(ID_INDICATOR_SCRL, "SCRL");
	qtMfcStringResources.insert(ID_INDICATOR_OVR, "OVR");
	qtMfcStringResources.insert(ID_INDICATOR_REC, "REC");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_FILE_NEW, "Create a new document\nNew");
	qtMfcStringResources.insert(ID_FILE_OPEN, "Open an existing document\nOpen");
	qtMfcStringResources.insert(ID_FILE_CLOSE, "Close the active document\nClose");
	qtMfcStringResources.insert(ID_FILE_SAVE, "Save the active document\nSave");
	qtMfcStringResources.insert(ID_FILE_SAVE_AS, "Save the active document with a new name\nSave As");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_APP_ABOUT, "Display program information, version number and copyright\nAbout");
	qtMfcStringResources.insert(ID_APP_EXIT, "Quit the application; prompts to save documents\nExit");
	qtMfcStringResources.insert(ID_HELP_INDEX, "Opens Help\nHelp Topics");
	qtMfcStringResources.insert(ID_HELP_FINDER, "List Help topics\nHelp Topics");
	qtMfcStringResources.insert(ID_HELP_USING, "Display instructions about how to use help\nHelp");
	qtMfcStringResources.insert(ID_CONTEXT_HELP, "Display help for clicked on buttons, menus and windows\nHelp");
	qtMfcStringResources.insert(ID_HELP, "Display help for current task or command\nHelp");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_FILE_MRU_FILE1, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE2, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE3, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE4, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE5, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE6, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE7, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE8, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE9, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE10, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE11, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE12, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE13, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE14, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE15, "Open this document");
	qtMfcStringResources.insert(ID_FILE_MRU_FILE16, "Open this document");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_NEXT_PANE, "Switch to the next window pane\nNext Pane");
	qtMfcStringResources.insert(ID_PREV_PANE, "Switch back to the previous window pane\nPrevious Pane");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_WINDOW_SPLIT, "Split the active window into panes\nSplit");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_EDIT_CLEAR, "Erase the selection\nErase");
	qtMfcStringResources.insert(ID_EDIT_CLEAR_ALL, "Erase everything\nErase All");
	qtMfcStringResources.insert(ID_EDIT_COPY, "Copy the selection and put it on the Clipboard\nCopy");
	qtMfcStringResources.insert(ID_EDIT_CUT, "Cut the selection and put it on the Clipboard\nCut");
	qtMfcStringResources.insert(ID_EDIT_FIND, "Find the specified text\nFind");
	qtMfcStringResources.insert(ID_EDIT_PASTE, "Insert Clipboard contents\nPaste");
	qtMfcStringResources.insert(ID_EDIT_REPEAT, "Repeat the last action\nRepeat");
	qtMfcStringResources.insert(ID_EDIT_REPLACE, "Replace specific text with different text\nReplace");
	qtMfcStringResources.insert(ID_EDIT_SELECT_ALL, "Select the entire document\nSelect All");
	qtMfcStringResources.insert(ID_EDIT_UNDO, "Undo the last action\nUndo");
	qtMfcStringResources.insert(ID_EDIT_REDO, "Redo the previously undone action\nRedo");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_VIEW_TOOLBAR, "Show or hide the toolbar\nToggle ToolBar");
	qtMfcStringResources.insert(ID_VIEW_STATUS_BAR, "Show or hide the status bar\nToggle StatusBar");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(AFX_IDS_SCSIZE, "Change the window size");
	qtMfcStringResources.insert(AFX_IDS_SCMOVE, "Change the window position");
	qtMfcStringResources.insert(AFX_IDS_SCMINIMIZE, "Reduce the window to an icon");
	qtMfcStringResources.insert(AFX_IDS_SCMAXIMIZE, "Enlarge the window to full size");
	qtMfcStringResources.insert(AFX_IDS_SCNEXTWINDOW, "Switch to the next document window");
	qtMfcStringResources.insert(AFX_IDS_SCPREVWINDOW, "Switch to the previous document window");
	qtMfcStringResources.insert(AFX_IDS_SCCLOSE, "Close the active window and prompts to save the documents");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(AFX_IDS_SCRESTORE, "Restore the window to normal size");
	qtMfcStringResources.insert(AFX_IDS_SCTASKLIST, "Activate Task List");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_TRACKER_PLAY, "Play module\nPlay");
	qtMfcStringResources.insert(ID_TRACKER_PLAYPATTERN, "Play and loop current pattern\nPlay and loop");
	qtMfcStringResources.insert(ID_TRACKER_STOP, "Stop playing\nStop");
	qtMfcStringResources.insert(ID_TRACKER_EDIT, "Enable/disable edit mode\nToggle edit mode");
	qtMfcStringResources.insert(ID_TRACKER_KILLSOUND, "Promptly stop all channels");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_EDIT_DELETE, "Delete selection, or note if there is no selection.");
	qtMfcStringResources.insert(ID_EDIT_UNLOCKCURSOR, "Makes it possible to edit without scrolling the view");
	qtMfcStringResources.insert(ID_TRACKER_NTSC, "Switch to NTSC emulation");
	qtMfcStringResources.insert(ID_TRACKER_PAL, "Switch to PAL emulation");
	qtMfcStringResources.insert(ID_SPEED_DEFALUT, "Default playback rate (60 Hz for NTSC, 50 Hz for PAL)");
	qtMfcStringResources.insert(ID_SPEED_CUSTOM, "Set the playback rate manually");
	qtMfcStringResources.insert(ID_HELP_PERFORMANCE, "Display application performance");
	qtMfcStringResources.insert(ID_EDIT_PASTEOVERWRITE, "Pasted notes will overwrite existing notes");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_FILE_CREATE_NSF, "Brings up the create NSF dialog\nCreate NSF");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_TRANSPOSE_INCREASENOTE, "Increase selected note/notes by one step");
	qtMfcStringResources.insert(ID_TRANSPOSE_DECREASENOTE, "Decrease selected note/notes by one step");
	qtMfcStringResources.insert(ID_TRANSPOSE_INCREASEOCTAVE, "Increase selected octave/octaves by one step");
	qtMfcStringResources.insert(ID_TRANSPOSE_DECREASEOCTAVE, "Decrease selected octave/octaves by one step");
	qtMfcStringResources.insert(ID_EDIT_SELECTALL, "Select pattern or all patterns\nSelect All");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_FILE_GENERALSETTINGS, "Opens FamiTracker settings\nSettings");
	qtMfcStringResources.insert(ID_EDIT_ENABLEMIDI, "Temporarly enable / disable commands from the MIDI device");
	qtMfcStringResources.insert(ID_FRAME_INSERT, "Insert a new frame on current location\nAdd frame");
	qtMfcStringResources.insert(ID_FRAME_REMOVE, "Remove current frame\nRemove frame");
	qtMfcStringResources.insert(ID_TRACKER_PLAYROW, "Play a single row");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_CREATE_NSF, "Export module to NSF");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_SPEED_DEFAULT, "Chooses default playback rate corresponding to selected video standard");
	qtMfcStringResources.insert(ID_MODULE_MODULEPROPERTIES, "Opens the module properties window\nModule properties");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDS_FILE_LOAD_ERROR, "Couldn't load file properly. Make sure you have the latest version of FamiTracker.");
	qtMfcStringResources.insert(IDS_CONFIG_WINDOW, "FamiTracker configuration");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_EDIT_PASTEMIX, "Pasted notes will mix with existing notes");
	qtMfcStringResources.insert(ID_MODULE_MOVEFRAMEDOWN, "Move selected frame one step down\nMove frame down");
	qtMfcStringResources.insert(ID_MODULE_MOVEFRAMEUP, "Move selected frame one step up\nMove frame up");
	qtMfcStringResources.insert(ID_MODULE_SAVEINSTRUMENT, "Save instrument to file\nSave instrument");
	qtMfcStringResources.insert(ID_MODULE_LOADINSTRUMENT, "Load instrument from file\nLoad instrument");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_MODULE_ADDINSTRUMENT, "Add a new instrument to the module\nAdd instrument");
	qtMfcStringResources.insert(ID_MODULE_REMOVEINSTRUMENT, "Remove instrument from module\nRemove instrument");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_NEXT_SONG, "Select next song\nNext song");
	qtMfcStringResources.insert(ID_PREV_SONG, "Select previous song\nPrevious song");
	qtMfcStringResources.insert(ID_EDIT_INSTRUMENTMASK, "Disables insertion of values in the instrument column");
	qtMfcStringResources.insert(ID_TRACKER_SWITCHTOTRACKINSTRUMENT, "Switch to channel instruments when playing");
	qtMfcStringResources.insert(ID_FRAME_INSERT_UNIQUE, "Insert new frame with empty patterns");
	qtMfcStringResources.insert(ID_FILE_CREATEWAV, "Saves the file as a WAV-file\nCreate WAV");
	qtMfcStringResources.insert(ID_VIEW_CONTROLPANEL, "Show or hide the control panel");
	qtMfcStringResources.insert(ID_EDIT_CLEARPATTERNS, "Resets all patterns and frames");
	qtMfcStringResources.insert(ID_EDIT_INTERPOLATE, "Interpolates a selection between two values\nInterpolate");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_TRACKER_SOLOCHANNEL, "Mutes/unmutes all but the selected channel");
	qtMfcStringResources.insert(ID_TRACKER_TOGGLECHANNEL, "Mute/unmute selected channel");
	qtMfcStringResources.insert(ID_EDIT_GRADIENT, "Interpolates a selection of values");
	qtMfcStringResources.insert(ID_MODULE_EDITINSTRUMENT, "Open instrument editor\nEdit instrument");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDS_INFO_TITLE, "(title)");
	qtMfcStringResources.insert(IDS_INFO_AUTHOR, "(author)");
	qtMfcStringResources.insert(IDS_OUT_OF_SLOTS, "Out of sample slots");
	qtMfcStringResources.insert(IDS_OUT_OF_SAMPLEMEM_FORMAT, "Couldn't load sample, out of sample memory (max %1 kB is avaliable)");
	qtMfcStringResources.insert(IDS_DPCM_IMPORT_GAIN_FORMAT, "Gain: %1 dB");
	qtMfcStringResources.insert(IDS_OPEN_FILE_ERROR, "Could not open file: %1");
	qtMfcStringResources.insert(IDS_INFO_COPYRIGHT, "(copyright)");
	qtMfcStringResources.insert(IDS_IMPORT_FAILED, "Import module failed");
	qtMfcStringResources.insert(IDS_IMPORT_CHIP_MISMATCH, "Imported file must be of the same expansion chip type as current file.");
	qtMfcStringResources.insert(IDS_IMPORT_INSTRUMENT_COUNT, "Can't import file, out of instrument slots!");
	qtMfcStringResources.insert(IDS_IMPORT_SAMPLE_SLOTS, "Could not import all samples, out of sample slots!");
	qtMfcStringResources.insert(IDS_DPCM_IMPORT_TITLE_FORMAT, "PCM Import (%1)");
	qtMfcStringResources.insert(IDS_DPCM_IMPORT_WAVE_FORMAT, "%1 Hz, %2 bits, %3");
	qtMfcStringResources.insert(IDS_DPCM_IMPORT_TARGET_FORMAT, "Target sample rate: %1 Hz");
	qtMfcStringResources.insert(IDS_PERFORMANCE_FRAMERATE_FORMAT, "Frame rate: %1 Hz");
	qtMfcStringResources.insert(IDS_PERFORMANCE_UNDERRUN_FORMAT, "Underruns: %1");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_MODULE_DUPLICATEFRAME, "Inserts a copy of current frame\nDuplicate frame");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_EDIT_REVERSE, "Reverses a selection\nReverse");
	qtMfcStringResources.insert(ID_TRACKER_DPCM, "Display information about the DPCM channel");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_INSTRUMENT_REMOVE, "Remove instrument from module\nRemove instrument");
	qtMfcStringResources.insert(ID_INSTRUMENT_EDIT, "Open instrument edtor\nEdit instrument");
	qtMfcStringResources.insert(ID_INSTRUMENT_CLONE, "Create a copy of selected instrument\nClone instrument");
	qtMfcStringResources.insert(ID_EDIT_REPLACEINSTRUMENT, "Replaces all instruments in a selection with the selected instrument\nReplace instrument");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_CLEANUP_REMOVEUNUSEDPATTERNS, "Removes all unused patterns\nRemove unused patterns");
	qtMfcStringResources.insert(ID_HELP_EFFECTTABLE, "Open help window with effect table");
	qtMfcStringResources.insert(ID_CLEANUP_REMOVEUNUSEDINSTRUMENTS, "Removes all unused instruments\nRemove unused instruments");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_MODULE_FRAME_INSERT, "Insert a new frame on current location");
	qtMfcStringResources.insert(ID_MODULE_FRAME_REMOVE, "Removes selected frame");
	qtMfcStringResources.insert(ID_MODULE_REMOVEFRAME, "Removes selected frame\nRemove frame");
	qtMfcStringResources.insert(ID_MODULE_COMMENTS, "Open module comments dialog\nComments");
	qtMfcStringResources.insert(ID_MODULE_INSERTFRAME, "Inserts a new frame\nInsert frame");
	qtMfcStringResources.insert(ID_INSTRUMENT_NEW, "Add a new instrument to the module\nAdd instrument");
	qtMfcStringResources.insert(ID_INSTRUMENT_LOAD, "Load instrument from file\nLoad instrument");
	qtMfcStringResources.insert(ID_INSTRUMENT_SAVE, "Save instrument to file\nSave instrument");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDS_SAVE_ERROR, "Couldn't save file, check that it isn't write protected or shared with other applications and enough disk space is available.");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDC_OPT_WRAPCURSOR, "Wrap around the cursor when reaching top or bottom in the pattern editor.");
	qtMfcStringResources.insert(IDC_OPT_FREECURSOR, "Unlocks the cursor from the center of the pattern editor.");
	qtMfcStringResources.insert(IDC_OPT_WAVEPREVIEW, "Preview wave and DPCM files in the open file dialog when loading samples to the module.");
	qtMfcStringResources.insert(IDC_OPT_KEYREPEAT, "Enable key repetition in the pattern editor.");
	qtMfcStringResources.insert(IDC_OPT_HEXROW, "Display row numbers in hexadecimal.");
	qtMfcStringResources.insert(IDC_OPT_WRAPFRAMES, "Move to next or previous frame when reaching top or bottom in the pattern editor.");
	qtMfcStringResources.insert(IDC_OPT_FRAMEPREVIEW, "Preview next and previous frame in the pattern editor.");
	qtMfcStringResources.insert(IDC_OPT_NODPCMRESET, "Prevents resetting the DPCM channel on note stop commands.");
	qtMfcStringResources.insert(IDC_OPT_NOSTEPMOVE, "Ignore the pattern step setting when moving the cursor, only use it when inserting notes.");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDC_OPT_PULLUPDELETE, "Makes delete key pull up rows rather than only deleting the value.");
	qtMfcStringResources.insert(IDC_OPT_BACKUPS, "Creates a backup copy of the existing file when saving a module.");
	qtMfcStringResources.insert(IDC_OPT_SINGLEINSTANCE, "Only allow one single instance of the FamiTracker application.");
	qtMfcStringResources.insert(IDC_OPT_PREVIEWFULLROW, "Preview all channels when inserting notes in the pattern editor.");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_MODULE_DUPLICATEFRAMEPATTERNS, "Inserts a copy of current frame including all patterns\nDuplicate patterns");
	qtMfcStringResources.insert(ID_EDIT_EXPANDPATTERNS, "Expands selected pattern\nExpand pattern");
	qtMfcStringResources.insert(ID_EDIT_SHRINKPATTERNS, "Shrinks selected pattern\nShrink pattern");
	qtMfcStringResources.insert(ID_FRAMEEDITOR_TOP, "Moves the frame editor to the top of the window (default)\nTop");
	qtMfcStringResources.insert(ID_FRAMEEDITOR_LEFT, "Moves the frame editor to the left of the window\nLeft");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_INSTRUMENT_DEEPCLONE, "Creates a copy of selected instrument including all sequences\nDeep clone instrument");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_TRACKER_PLAY_CURSOR, "Play pattern from cursor");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDS_CLEARPATTERN, "Do you want to reset all patterns and frames? There is no undo for this command.");
	qtMfcStringResources.insert(IDS_CLIPBOARD_COPY_ERROR, "An error occured while trying to copy data to the clipboard.");
	qtMfcStringResources.insert(IDS_CLIPBOARD_PASTE_ERROR, "An error occured while trying to paste data from the clipboard.");
	qtMfcStringResources.insert(IDS_DPCM_SPACE_FORMAT, "Space used %1 kB, left %2 kB (%3 kB available)");
	qtMfcStringResources.insert(IDS_FILE_VERSION_TOO_NEW, "This file was created in a newer version of FamiTracker. Please download the most recent version to open this file.");
	qtMfcStringResources.insert(IDS_INSTRUMENT_EDITOR_TITLE, "Instrument editor - %1");
	qtMfcStringResources.insert(IDS_INST_VERSION_UNSUPPORTED, "File version not supported!");
	qtMfcStringResources.insert(IDS_FILE_SAVED, "File saved (%1 bytes)");
	qtMfcStringResources.insert(IDS_MIDI_ERR_INPUT, "MIDI Error: Could not open MIDI input device!");
	qtMfcStringResources.insert(IDS_MIDI_ERR_OUTPUT, "MIDI Error: Could not open MIDI output device!");
	qtMfcStringResources.insert(IDS_NEW_SOUND_CONFIG, "New sound configuration has been loaded");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDS_REMOVE_INSTRUMENTS, "Do you want to remove all unused instruments? There is no undo for this action.");
	qtMfcStringResources.insert(IDS_REMOVE_PATTERNS, "Do you want to remove all unused patterns? There is no undo for this action.");
	qtMfcStringResources.insert(IDS_SONG_DELETE, "Do you want to delete this song? There is no undo for this action.");
	qtMfcStringResources.insert(IDS_SOUND_FAIL, "It appears the current sound settings aren't working, change settings and try again.");
	qtMfcStringResources.insert(IDS_UNDERRUN_MESSAGE, "Warning: Audio buffer underrun, increase the audio buffer size!");
	qtMfcStringResources.insert(IDS_WELCOME_VER_FORMAT, "Welcome to FamiTracker %1, press F1 for help");
	qtMfcStringResources.insert(IDS_DPCM_IMPORT_INVALID_WAVEFILE, "Cannot load this sample, file is invalid or incompatible. (Only uncompressed PCM is supported.)");
	qtMfcStringResources.insert(IDS_INST_FILE_ERROR, "Could not load instrument file! Check that you have the most recent version of FamiTracker.");
	qtMfcStringResources.insert(IDS_NEW_2A03_INSTRUMENT, "New 2A03 instrument");
	qtMfcStringResources.insert(IDS_NEW_VRC6_INSTRUMENT, "New VRC6 instrument");
	qtMfcStringResources.insert(IDS_NEW_VRC7_INSTRUMENT, "New VRC7 instrument");
	qtMfcStringResources.insert(IDS_NEW_FDS_INSTRUMENT, "New FDS instrument");
	qtMfcStringResources.insert(IDS_NEW_N163_INSTRUMENT, "New Namco instrument");
	qtMfcStringResources.insert(IDS_NEW_S5B_INSTRUMENT, "New Sunsoft instrument");
	qtMfcStringResources.insert(IDS_FRAME_DROP_COPY_NEW, "Drop selection to copy frames to new pattern numbers");
	qtMfcStringResources.insert(IDS_FRAME_DROP_COPY, "Drop selection to copy frames");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_INDICATOR_CHIP, "No expansion chip");
	qtMfcStringResources.insert(ID_INDICATOR_INSTRUMENT, "Instrument: %1");
	qtMfcStringResources.insert(ID_INDICATOR_OCTAVE, "Octave: %1");
	qtMfcStringResources.insert(ID_INDICATOR_RATE, "000 Hz");
	qtMfcStringResources.insert(ID_INDICATOR_TEMPO, "000.00 BPM");
	qtMfcStringResources.insert(ID_INDICATOR_TIME, "00:00:00 ");
	qtMfcStringResources.insert(ID_INDICATOR_POS, "00 / 00    ");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_HELP_FAQ, "Open help window with the FAQ");
	qtMfcStringResources.insert(ID_TRACKER_DISPLAYREGISTERSTATE, "Display channel register values and tuning information");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDS_WAVE_PROGRESS_FILE_FORMAT, "Saving to: %1");
	qtMfcStringResources.insert(IDS_WAVE_PROGRESS_FRAME_FORMAT, "Frame: %1 (%2 done)");
	qtMfcStringResources.insert(IDS_WAVE_PROGRESS_TIME_FORMAT, "Time: %1 (%2 done)");
	qtMfcStringResources.insert(IDS_WAVE_PROGRESS_ELAPSED_FORMAT, "Elapsed time: %1");
	qtMfcStringResources.insert(IDS_DSOUND_ERROR, "DirectX: DirectSound error!");
	qtMfcStringResources.insert(IDS_DSOUND_BUFFER_ERROR, "DirectX: DirectSound error: Could not create buffer!");
	qtMfcStringResources.insert(IDS_EDIT_MODE, "Changed to edit mode");
	qtMfcStringResources.insert(IDS_NORMAL_MODE, "Changed to normal mode");
	qtMfcStringResources.insert(IDS_MIDI_MESSAGE_ON_FORMAT, "MIDI message: Note on (note = %1, octave = %2, velocity = %3)");
	qtMfcStringResources.insert(IDS_MIDI_MESSAGE_OFF, "MIDI message: Note off");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDC_OPT_DOUBLECLICK, "Don't select the whole channel when double-clicking in the pattern editor.");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(IDS_LOADING_FILE, "Loading file...");
	qtMfcStringResources.insert(IDS_FILTER_DMC, "Delta modulated samples (*.dmc)");
	qtMfcStringResources.insert(IDS_FILTER_WAV, "Waveform Audio File Format (*.wav)");
	qtMfcStringResources.insert(IDS_FILTER_TXT, "Text files (*.txt)");
	qtMfcStringResources.insert(IDS_DPCM_EDIT_INFO_FORMAT, "Wave end: %1, Size: %2 bytes ");
	qtMfcStringResources.insert(IDS_WAVE_EXPORT_DONE, "Done");
	qtMfcStringResources.insert(IDS_WAVE_EXPORT_FINISHED, "finished");
	qtMfcStringResources.insert(IDS_ABOUT_TOOLTIP_MAIL, "Send mail to jsr@famitracker.com");
	qtMfcStringResources.insert(IDS_ABOUT_TOOLTIP_WEB, "Go to http://www.famitracker.com");
	qtMfcStringResources.insert(IDS_ABOUT_VERSION_FORMAT, "FamiTracker version %1");
	qtMfcStringResources.insert(IDS_PROPERTIES_CHANNELS, "Channels:");
	qtMfcStringResources.insert(IDS_LOADING_DONE, "File loaded");
	qtMfcStringResources.insert(IDS_DPCM_IMPORT_SIZE_FORMAT, "Converted size: %1 bytes");
	qtMfcStringResources.insert(IDS_INSTRUMENT_FOLDER, "Choose a folder where you have instrument files");
	// END

	// STRINGTABLE
	// BEGIN
	qtMfcStringResources.insert(ID_FILE_IMPORTTEXT, "Imports pattern text files");
	qtMfcStringResources.insert(ID_FILE_EXPORTTEXT, "Exports pattern text files");
	qtMfcStringResources.insert(ID_EDIT_VOLUMEMASK, "Disables insertion of values in the volume column");
	// END

	// AFX resources
	qtMfcStringResources.insert(AFX_IDS_ALLFILTER, "All files|");
	qtMfcStringResources.insert(AFX_IDS_OPENFILE, "Open");
	qtMfcStringResources.insert(AFX_IDS_SAVEFILE, "Save As");
	qtMfcStringResources.insert(AFX_IDS_SAVEFILECOPY, "Save As");
	qtMfcStringResources.insert(AFX_IDS_UNTITLED, "Untitled");
	qtMfcStringResources.insert(AFX_IDP_ASK_TO_SAVE, "Save changes to %s?");
	qtMfcStringResources.insert(AFX_IDP_FAILED_TO_CREATE_DOC, "Failed to create empty document.");
}

// IDR_MAINFRAME ACCELERATORS
ACCEL ACCEL_IDR_MAINFRAME[] =
	{
		// BEGIN
		// 'C', ID_EDIT_COPY, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'C', ID_EDIT_COPY},

		// VK_INSERT, ID_EDIT_COPY, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, VK_INSERT, ID_EDIT_COPY},

		// 'X', ID_EDIT_CUT, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'X', ID_EDIT_CUT},

		// 'V', ID_EDIT_PASTE, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'V', ID_EDIT_PASTE},

		// VK_INSERT, ID_EDIT_PASTE, FVIRTKEY|FSHIFT|FNOINVERT
		{FVIRTKEY | FSHIFT | FNOINVERT, VK_INSERT, ID_EDIT_PASTE},

		// 'Y', ID_EDIT_REDO, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'Y', ID_EDIT_REDO},

		// VK_BACK, ID_EDIT_UNDO, FVIRTKEY|FALT|FNOINVERT
		{FVIRTKEY | FALT | FNOINVERT, VK_BACK, ID_EDIT_UNDO},

		// 'Z', ID_EDIT_UNDO, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'Z', ID_EDIT_UNDO},

		// VK_F4, ID_FILE_CLOSE, FVIRTKEY|FALT|FNOINVERT
		{FVIRTKEY | FALT | FNOINVERT, VK_F4, ID_FILE_CLOSE},

		// 'E', ID_FILE_CREATE_NSF, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'E', ID_FILE_CREATE_NSF},

		// 'N', ID_FILE_NEW, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'N', ID_FILE_NEW},

		// 'O', ID_FILE_OPEN, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'O', ID_FILE_OPEN},

		// 'S', ID_FILE_SAVE, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'S', ID_FILE_SAVE},

		// VK_F1, ID_HELP, FVIRTKEY|FNOINVERT
		{FVIRTKEY | FNOINVERT, VK_F1, ID_HELP},

		// 'P', ID_MODULE_MODULEPROPERTIES, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'P', ID_MODULE_MODULEPROPERTIES},

		// 'S', ID_TOGGLE_SPEED, FVIRTKEY|FSHIFT|FNOINVERT|FCONTROL
		{FVIRTKEY | FSHIFT | FNOINVERT | FCONTROL, 'S', ID_TOGGLE_SPEED},

		// VK_F12, ID_TRACKER_KILLSOUND, FVIRTKEY|FNOINVERT
		{FVIRTKEY | FNOINVERT, VK_F12, ID_TRACKER_KILLSOUND},

		// END
		{0, 0, 0},
};

// IDR_FRAMEWND ACCELERATORS
ACCEL ACCEL_IDR_FRAMEWND[] =
	{
		// BEGIN
		// 'C', ID_EDIT_COPY, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'C', ID_EDIT_COPY},

		// VK_DELETE, ID_EDIT_DELETE, FVIRTKEY|FNOINVERT
		{FVIRTKEY | FNOINVERT, VK_DELETE, ID_EDIT_DELETE},

		// 'V', ID_EDIT_PASTE, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'V', ID_EDIT_PASTE},

		// 'Y', ID_EDIT_REDO, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'Y', ID_EDIT_REDO},

		// 'Z', ID_EDIT_UNDO, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'Z', ID_EDIT_UNDO},

		// VK_DOWN, ID_MODULE_MOVEFRAMEDOWN, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, VK_DOWN, ID_MODULE_MOVEFRAMEDOWN},

		// VK_UP, ID_MODULE_MOVEFRAMEUP, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, VK_UP, ID_MODULE_MOVEFRAMEUP},

		// 'X', ID_EDIT_CUT, FVIRTKEY|FNOINVERT|FCONTROL
		{FVIRTKEY | FNOINVERT | FCONTROL, 'X', ID_EDIT_CUT},

		// END
		{0, 0, 0},
};

ACCEL *qtMfcAcceleratorResource(UINT id)
{
	switch (id)
	{
	case IDR_MAINFRAME:
		return ACCEL_IDR_MAINFRAME;
		break;

	case IDR_FRAMEWND:
		return ACCEL_IDR_FRAMEWND;
		break;
	}
	return NULL;
}

void qtMfcInitBitmapResources()
{
	qtMfcBitmapResources.clear();

	// IDR_MAINFRAME BITMAP ":/resources/MainToolbar-16.bmp"
	qtMfcBitmapResources.insert(IDR_MAINFRAME, new CBitmap(":/resources/MainToolbar-16.bmp"));

	// IDR_INSTRUMENT_TOOLBAR BITMAP ":/resources/InstrumentToolbar-16.bmp"
	qtMfcBitmapResources.insert(IDR_INSTRUMENT_TOOLBAR, new CBitmap(":/resources/InstrumentToolbar-16.bmp"));

	// IDB_SAMPLEBG BITMAP ":/resources/VisualizerBg.bmp"
	qtMfcBitmapResources.insert(IDB_SAMPLEBG, new CBitmap(":/resources/VisualizerBg.bmp"));

	// IDB_KEY_BLACK BITMAP ":/resources/key_black_unpressed.bmp"
	qtMfcBitmapResources.insert(IDB_KEY_BLACK, new CBitmap(":/resources/key_black_unpressed.bmp"));

	// IDB_KEY_BLACK_MARK BITMAP ":/resources/key_black_pressed.bmp"
	qtMfcBitmapResources.insert(IDB_KEY_BLACK_MARK, new CBitmap(":/resources/key_black_pressed.bmp"));

	// IDB_KEY_WHITE BITMAP ":/resources/key_white_unpressed.bmp"
	qtMfcBitmapResources.insert(IDB_KEY_WHITE, new CBitmap(":/resources/key_white_unpressed.bmp"));

	// IDB_KEY_WHITE_MARK BITMAP ":/resources/key_white_pressed.bmp"
	qtMfcBitmapResources.insert(IDB_KEY_WHITE_MARK, new CBitmap(":/resources/key_white_pressed.bmp"));

	// IDB_TOOLBAR_256 BITMAP ":/resources/MainToolbar-256.bmp"
	qtMfcBitmapResources.insert(IDB_TOOLBAR_256, new CBitmap(":/resources/MainToolbar-256.bmp"));

	// IDB_TOOLBAR_INST_256 BITMAP ":/resources/InstrumentToolbar-256.bmp"
	qtMfcBitmapResources.insert(IDB_TOOLBAR_INST_256, new CBitmap(":/resources/InstrumentToolbar-256.bmp"));

	// IDB_ABOUT BITMAP ":/resources/About.bmp"
	qtMfcBitmapResources.insert(IDB_ABOUT, new CBitmap(":/resources/About.bmp"));
}

void qtInitIconResources()
{
	qtIconNames.clear();
	qtIconResources.clear();

	// Icon with lowest ID value placed first to ensure application icon
	// remains consistent on all systems.

	// IDR_MAINFRAME ICON ":/resources/Application.ico"
	qtIconNames.insert(IDR_MAINFRAME, ":/resources/Application.ico");

	// IDI_INST_2A03 ICON ":/resources/Inst_2A03.ico"
	qtIconNames.insert(IDI_INST_2A03, ":/resources/Inst_2A03.ico");

	// IDI_INST_VRC6 ICON ":/resources/Inst_VRC6.ico"
	qtIconNames.insert(IDI_INST_VRC6, ":/resources/Inst_VRC6.ico");

	// IDI_INST_VRC7 ICON ":/resources/Inst_VRC7.ico"
	qtIconNames.insert(IDI_INST_VRC7, ":/resources/Inst_VRC7.ico");

	// IDR_FamiTrackerTYPE ICON ":/resources/Document.ico"
	qtIconNames.insert(IDR_FamiTrackerTYPE, ":/resources/Document.ico");

	// IDI_INST_N163 ICON ":/resources/Inst_N163.ico"
	qtIconNames.insert(IDI_INST_N163, ":/resources/Inst_N163.ico");

	// IDI_INST_FDS ICON ":/resources/Inst_FDS.ico"
	qtIconNames.insert(IDI_INST_FDS, ":/resources/Inst_FDS.ico");

	// IDI_INST_S5B ICON ":/resources/Inst_S5B.ico"
	qtIconNames.insert(IDI_INST_S5B, ":/resources/Inst_S5B.ico");

	// IDI_INST_2A07 ICON ":/resources/Inst_2A07.ico"
	qtIconNames.insert(IDI_INST_2A07, ":/resources/Inst_2A07.ico");

	// IDI_LEFT ICON ":/resources/LeftArrow.ico"
	qtIconNames.insert(IDI_LEFT, ":/resources/LeftArrow.ico");

	// IDI_RIGHT ICON ":/resources/RightArrow.ico"
	qtIconNames.insert(IDI_RIGHT, ":/resources/RightArrow.ico");
}

void qtMfcInitDialogResource_IDD_ABOUTBOX(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_ABOUTBOX DIALOGEX 0, 0, 285, 336
	CRect rect(CPoint(0, 0), CSize(285, 336));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "About FamiTracker"
	parent->SetWindowText("About FamiTracker");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|DS_CENTER|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// LTEXT "Copyright (C) 2005 - 2015 jsr",IDC_ABOUT3,54,92,167,11
	CStatic *mfc0 = new CStatic(parent);
	CRect r0(CPoint(54, 92), CSize(167, 11));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Copyright (C) 2005 - 2015 jsr"), WS_VISIBLE | WS_BORDER, r0, parent, IDC_ABOUT3);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER|WS_GROUP,228,64,50,16
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(228, 64), CSize(50, 16));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("OK"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER | WS_GROUP, r1, parent, IDOK);
	mfcToQtWidget->insert(IDOK, mfc1);

	// LTEXT "* FDS sound emulator from nezplug (including a fix by rainwarrior)",IDC_STATIC,54,313,224,8
	CStatic *mfc2 = new CStatic(parent);
	CRect r2(CPoint(54, 313), CSize(224, 8));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("* FDS sound emulator from nezplug (including a fix by rainwarrior)"), WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "E-mail:",IDC_STATIC,54,108,24,10
	CStatic *mfc3 = new CStatic(parent);
	CRect r3(CPoint(54, 108), CSize(24, 10));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("E-mail:"), WS_VISIBLE | WS_BORDER, r3, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "This software is licensed under the GNU General Public\n License. Source is available on the webpage.",IDC_STATIC,54,167,224,17
	CStatic *mfc4 = new CStatic(parent);
	CRect r4(CPoint(54, 167), CSize(224, 17));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("This software is licensed under the GNU General Public\n License. Source is available on the webpage."), WS_VISIBLE | WS_BORDER, r4, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Contributions:",IDC_STATIC,54,191,224,9
	CStatic *mfc6 = new CStatic(parent);
	CRect r6(CPoint(54, 191), CSize(224, 9));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Contributions:"), WS_VISIBLE | WS_BORDER, r6, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "All comments and feedback are welcome\nGreets to everyone at the 2A03.org forum and everyone who has contributed with bug reports and suggestions!",IDC_STATIC,54,137,224,26
	CStatic *mfc7 = new CStatic(parent);
	CRect r7(CPoint(54, 137), CSize(224, 26));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("All comments and feedback are welcome\nGreets to everyone at the 2A03.org forum and everyone who has contributed with bug reports and suggestions!"), WS_VISIBLE | WS_BORDER, r7, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "jsr@famitracker.com",IDC_MAIL,84,108,70,10
	CStatic *mfc8 = new CStatic(parent);
	CRect r8(CPoint(84, 108), CSize(70, 10));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("jsr@famitracker.com"), WS_VISIBLE | WS_BORDER | SS_NOTIFY, r8, parent, IDC_MAIL);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "http://www.famitracker.com",IDC_WEBPAGE,84,121,95,9
	CStatic *mfc9 = new CStatic(parent);
	CRect r9(CPoint(84, 121), CSize(95, 9));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("http://www.famitracker.com"), WS_VISIBLE | WS_BORDER | SS_NOTIFY, r9, parent, IDC_WEBPAGE);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Web:",IDC_STATIC,54,121,24,9
	CStatic *mfc10 = new CStatic(parent);
	CRect r10(CPoint(54, 121), CSize(24, 9));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("Web:"), WS_VISIBLE | WS_BORDER, r10, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Libraries:",IDC_STATIC,54,260,224,8
	CStatic *mfc11 = new CStatic(parent);
	CRect r11(CPoint(54, 260), CSize(224, 8));
	parent->MapDialogRect(&r11);
	mfc11->Create(_T("Libraries:"), WS_VISIBLE | WS_BORDER, r11, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "* Blip_buffer 0.4.0 is Copyright (C) blargg (http://www.slack.net/~ant/nes-emu/)\n",IDC_STATIC,54,273,224,16
	CStatic *mfc12 = new CStatic(parent);
	CRect r12(CPoint(54, 273), CSize(224, 16));
	parent->MapDialogRect(&r12);
	mfc12->Create(_T("* Blip_buffer 0.4.0 is Copyright (C) blargg (http://www.slack.net/~ant/nes-emu/)\n"), WS_VISIBLE | WS_BORDER, r12, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "* Fast Fourier Transform code is (C) Reliable Software",IDC_STATIC,54,292,224,8
	CStatic *mfc13 = new CStatic(parent);
	CRect r13(CPoint(54, 292), CSize(224, 8));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("* Fast Fourier Transform code is (C) Reliable Software"), WS_VISIBLE | WS_BORDER, r13, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "* YM2413 && YM2149 emulators are written by Mitsutaka Okazaki",IDC_STATIC,54,303,224,8
	CStatic *mfc14 = new CStatic(parent);
	CRect r14(CPoint(54, 303), CSize(224, 8));
	parent->MapDialogRect(&r14);
	mfc14->Create(_T("* YM2413 && YM2149 emulators are written by Mitsutaka Okazaki"), WS_VISIBLE | WS_BORDER, r14, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDHORZ, 54, 271, 215, 1
	CStatic *mfc15 = new CStatic(parent);
	CRect r15(CPoint(54, 271), CSize(215, 1));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDHORZ, r15, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc15);

	// LTEXT "* Export plugin support by Gradualore",IDC_STATIC,54,204,224,9
	CStatic *mfc16 = new CStatic(parent);
	CRect r16(CPoint(54, 204), CSize(224, 9));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T("* Export plugin support by Gradualore"), WS_VISIBLE | WS_BORDER, r16, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "* Icon is made by Kuhneghetz",IDC_STATIC,54,214,224,9
	CStatic *mfc17 = new CStatic(parent);
	CRect r17(CPoint(54, 214), CSize(224, 9));
	parent->MapDialogRect(&r17);
	mfc17->Create(_T("* Icon is made by Kuhneghetz"), WS_VISIBLE | WS_BORDER, r17, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "* Toolbar icons are made by ilkke",IDC_STATIC,54,223,224,9
	CStatic *mfc18 = new CStatic(parent);
	CRect r18(CPoint(54, 223), CSize(224, 9));
	parent->MapDialogRect(&r18);
	mfc18->Create(_T("* Toolbar icons are made by ilkke"), WS_VISIBLE | WS_BORDER, r18, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDHORZ, 54, 201, 211, 1
	CStatic *mfc19 = new CStatic(parent);
	CRect r19(CPoint(54, 201), CSize(211, 1));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDHORZ, r19, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc19);

	// LTEXT "* DPCM import resampler by Jarhmander",IDC_STATIC,54,233,224,9
	CStatic *mfc20 = new CStatic(parent);
	CRect r20(CPoint(54, 233), CSize(224, 9));
	parent->MapDialogRect(&r20);
	mfc20->Create(_T("* DPCM import resampler by Jarhmander"), WS_VISIBLE | WS_BORDER, r20, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "A Famicom/NES music tracker",IDC_ABOUT2,54,76,167,11
	CStatic *mfc21 = new CStatic(parent);
	CRect r21(CPoint(54, 76), CSize(167, 11));
	parent->MapDialogRect(&r21);
	mfc21->Create(_T("A Famicom/NES music tracker"), WS_VISIBLE | WS_BORDER | SS_NOPREFIX, r21, parent, IDC_ABOUT2);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "* Module text import/export by rainwarrior",IDC_STATIC,54,244,224,9
	CStatic *mfc22 = new CStatic(parent);
	CRect r22(CPoint(54, 244), CSize(224, 9));
	parent->MapDialogRect(&r22);
	mfc22->Create(_T("* Module text import/export by rainwarrior"), WS_VISIBLE | WS_BORDER, r22, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDHORZ, 0, 49, 287, 1
	CStatic *mfc23 = new CStatic(parent);
	CRect r23(CPoint(0, 49), CSize(287, 1));
	parent->MapDialogRect(&r23);
	mfc23->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDHORZ, r23, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc23);

	// LTEXT "A Famicom/NES music tracker",IDC_ABOUT1,54,58,167,11
	CStatic *mfc24 = new CStatic(parent);
	CRect r24(CPoint(54, 58), CSize(167, 11));
	parent->MapDialogRect(&r24);
	mfc24->Create(_T("A Famicom/NES music tracker"), WS_VISIBLE | WS_BORDER | SS_NOPREFIX, r24, parent, IDC_ABOUT1);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_HEAD, "Static", WS_VISIBLE|WS_BORDER|SS_OWNERDRAW, 0, 0, 287, 49
	CStatic *mfc25 = new CStatic(parent);
	CRect r25(CPoint(0, 0), CSize(287, 49));
	parent->MapDialogRect(&r25);
	mfc25->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_OWNERDRAW, r25, parent, IDC_HEAD);
	mfcToQtWidget->insert(IDC_HEAD, mfc25);

	// END
}

void qtMfcInitDialogResource_IDD_MAINFRAME(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_MAINFRAME DIALOGEX 0, 0, 413, 126
	CRect rect(CPoint(0, 0), CSize(413, 126));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// GROUPBOX "Song settings",IDC_STATIC,7,5,78,71
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 5), CSize(78, 71));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Song settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Edit settings",IDC_STATIC,7,78,78,43
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 78), CSize(78, 43));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Edit settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER | 0, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Song information",IDC_STATIC,91,5,96,61
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(91, 5), CSize(96, 61));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Song information"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Songs",IDC_STATIC,91,94,96,27
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(91, 94), CSize(96, 27));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Songs"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r3, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Speed",IDC_STATIC,13,17,29,10
	CStatic *mfc5 = new CStatic(parent);
	CRect r5(CPoint(13, 17), CSize(29, 10));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Speed"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_SPEED,43,15,38,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY|ES_NUMBER
	CEdit *mfc6 = new CEdit(parent);
	CRect r6(CPoint(43, 15), CSize(38, 12));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY | ES_NUMBER, r6, parent, IDC_SPEED);
	mfcToQtWidget->insert(IDC_SPEED, mfc6);

	// CONTROL "", IDC_SPEED_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 81, 15, 11, 13
	CSpinButtonCtrl *mfc7 = new CSpinButtonCtrl(parent);
	CRect r7(CPoint(81, 15), CSize(11, 13));
	parent->MapDialogRect(&r7);
	mfc7->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r7, parent, IDC_SPEED_SPIN);
	mfcToQtWidget->insert(IDC_SPEED_SPIN, mfc7);

	// LTEXT "Tempo",IDC_STATIC,13,31,29,10
	CStatic *mfc8 = new CStatic(parent);
	CRect r8(CPoint(13, 31), CSize(29, 10));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("Tempo"), WS_VISIBLE | WS_BORDER, r8, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_TEMPO,43,29,38,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc9 = new CEdit(parent);
	CRect r9(CPoint(43, 29), CSize(38, 12));
	parent->MapDialogRect(&r9);
	mfc9->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r9, parent, IDC_TEMPO);
	mfcToQtWidget->insert(IDC_TEMPO, mfc9);

	// CONTROL "", IDC_TEMPO_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 81, 28, 11, 13
	CSpinButtonCtrl *mfc10 = new CSpinButtonCtrl(parent);
	CRect r10(CPoint(81, 28), CSize(11, 13));
	parent->MapDialogRect(&r10);
	mfc10->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r10, parent, IDC_TEMPO_SPIN);
	mfcToQtWidget->insert(IDC_TEMPO_SPIN, mfc10);

	// LTEXT "Rows",IDC_STATIC,13,45,29,10
	CStatic *mfc11 = new CStatic(parent);
	CRect r11(CPoint(13, 45), CSize(29, 10));
	parent->MapDialogRect(&r11);
	mfc11->Create(_T("Rows"), WS_VISIBLE | WS_BORDER, r11, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_ROWS,43,43,38,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY|ES_WANTRETURN
	CEdit *mfc12 = new CEdit(parent);
	CRect r12(CPoint(43, 43), CSize(38, 12));
	parent->MapDialogRect(&r12);
	mfc12->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY | ES_WANTRETURN, r12, parent, IDC_ROWS);
	mfcToQtWidget->insert(IDC_ROWS, mfc12);

	// CONTROL "", IDC_ROWS_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 81, 43, 11, 13
	CSpinButtonCtrl *mfc13 = new CSpinButtonCtrl(parent);
	CRect r13(CPoint(81, 43), CSize(11, 13));
	parent->MapDialogRect(&r13);
	mfc13->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r13, parent, IDC_ROWS_SPIN);
	mfcToQtWidget->insert(IDC_ROWS_SPIN, mfc13);

	// LTEXT "Frames",IDC_STATIC,13,59,29,10
	CStatic *mfc14 = new CStatic(parent);
	CRect r14(CPoint(13, 59), CSize(29, 10));
	parent->MapDialogRect(&r14);
	mfc14->Create(_T("Frames"), WS_VISIBLE | WS_BORDER, r14, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_FRAMES,43,57,38,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc15 = new CEdit(parent);
	CRect r15(CPoint(43, 57), CSize(38, 12));
	parent->MapDialogRect(&r15);
	mfc15->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r15, parent, IDC_FRAMES);
	mfcToQtWidget->insert(IDC_FRAMES, mfc15);

	// CONTROL "", IDC_FRAME_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 81, 58, 11, 13
	CSpinButtonCtrl *mfc16 = new CSpinButtonCtrl(parent);
	CRect r16(CPoint(81, 58), CSize(11, 13));
	parent->MapDialogRect(&r16);
	mfc16->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r16, parent, IDC_FRAME_SPIN);
	mfcToQtWidget->insert(IDC_FRAME_SPIN, mfc16);

	// LTEXT "Step",IDC_STATIC,13,91,29,10
	CStatic *mfc18 = new CStatic(parent);
	CRect r18(CPoint(13, 91), CSize(29, 10));
	parent->MapDialogRect(&r18);
	mfc18->Create(_T("Step"), WS_VISIBLE | WS_BORDER | 0, r18, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_KEYSTEP,43,90,38,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc19 = new CEdit(parent);
	CRect r19(CPoint(43, 90), CSize(38, 12));
	parent->MapDialogRect(&r19);
	mfc19->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r19, parent, IDC_KEYSTEP);
	mfcToQtWidget->insert(IDC_KEYSTEP, mfc19);

	// CONTROL "", IDC_KEYSTEP_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 81, 88, 11, 13
	CSpinButtonCtrl *mfc20 = new CSpinButtonCtrl(parent);
	CRect r20(CPoint(81, 88), CSize(11, 13));
	parent->MapDialogRect(&r20);
	mfc20->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r20, parent, IDC_KEYSTEP_SPIN);
	mfcToQtWidget->insert(IDC_KEYSTEP_SPIN, mfc20);

	// CONTROL "Key repetition", IDC_KEYREPEAT, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 105, 68, 9
	CButton *mfc21 = new CButton(parent);
	CRect r21(CPoint(13, 105), CSize(68, 9));
	parent->MapDialogRect(&r21);
	mfc21->Create(_T("Key repetition"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r21, parent, IDC_KEYREPEAT);
	mfcToQtWidget->insert(IDC_KEYREPEAT, mfc21);

	// EDITTEXT IDC_SONG_NAME,97,18,83,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc23 = new CEdit(parent);
	CRect r23(CPoint(97, 18), CSize(83, 12));
	parent->MapDialogRect(&r23);
	mfc23->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r23, parent, IDC_SONG_NAME);
	mfcToQtWidget->insert(IDC_SONG_NAME, mfc23);

	// EDITTEXT IDC_SONG_ARTIST,97,33,83,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc24 = new CEdit(parent);
	CRect r24(CPoint(97, 33), CSize(83, 12));
	parent->MapDialogRect(&r24);
	mfc24->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r24, parent, IDC_SONG_ARTIST);
	mfcToQtWidget->insert(IDC_SONG_ARTIST, mfc24);

	// EDITTEXT IDC_SONG_COPYRIGHT,97,49,83,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc25 = new CEdit(parent);
	CRect r25(CPoint(97, 49), CSize(83, 12));
	parent->MapDialogRect(&r25);
	mfc25->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r25, parent, IDC_SONG_COPYRIGHT);
	mfcToQtWidget->insert(IDC_SONG_COPYRIGHT, mfc25);

	// COMBOBOX IDC_SUBTUNE,97,104,84,85,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc27 = new CComboBox(parent);
	CRect r27(CPoint(97, 104), CSize(84, 85));
	parent->MapDialogRect(&r27);
	mfc27->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r27, parent, IDC_SUBTUNE);
	mfcToQtWidget->insert(IDC_SUBTUNE, mfc27);

	// CONTROL "", IDC_INSTRUMENTS, "SysListView32", WS_VISIBLE|WS_BORDER|LVS_LIST|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_EDITLABELS|LVS_ALIGNLEFT|LVS_NOCOLUMNHEADER|LVS_NOSORTHEADER|WS_BORDER|WS_TABSTOP, 193, 5, 202, 103
	CListCtrl *mfc28 = new CListCtrl(parent);
	CRect r28(CPoint(193, 5), CSize(202, 103));
	parent->MapDialogRect(&r28);
	mfc28->Create(WS_VISIBLE | WS_BORDER | LVS_LIST | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_EDITLABELS | LVS_ALIGNLEFT | LVS_NOCOLUMNHEADER | LVS_NOSORTHEADER | WS_BORDER | WS_TABSTOP, r28, parent, IDC_INSTRUMENTS);
	mfcToQtWidget->insert(IDC_INSTRUMENTS, mfc28);

	// EDITTEXT IDC_INSTNAME,324,109,71,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc29 = new CEdit(parent);
	CRect r29(CPoint(324, 109), CSize(71, 12));
	parent->MapDialogRect(&r29);
	mfc29->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r29, parent, IDC_INSTNAME);
	mfcToQtWidget->insert(IDC_INSTNAME, mfc29);

	// END
}

void qtMfcInitDialogResource_IDD_PCMIMPORT(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_PCMIMPORT DIALOGEX 0, 0, 211, 144
	CRect rect(CPoint(0, 0), CSize(211, 144));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "PCM import"
	parent->SetWindowText("PCM import");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Quality: 0",IDC_QUALITY_FRM,7,7,136,36
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(136, 36));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Quality: 0"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_QUALITY_FRM);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Gain: +0dB",IDC_VOLUME_FRM,7,47,136,35
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 47), CSize(136, 35));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Gain: +0dB"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_VOLUME_FRM);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "File info",IDC_STATIC,7,86,136,51
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(7, 86), CSize(136, 51));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("File info"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Low",IDC_STATIC,15,21,15,10
	CStatic *mfc4 = new CStatic(parent);
	CRect r4(CPoint(15, 21), CSize(15, 10));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("Low"), WS_VISIBLE | WS_BORDER, r4, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_QUALITY, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 30, 19, 90, 15
	CSliderCtrl *mfc5 = new CSliderCtrl(parent);
	CRect r5(CPoint(30, 19), CSize(90, 15));
	parent->MapDialogRect(&r5);
	mfc5->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r5, parent, IDC_QUALITY);
	mfcToQtWidget->insert(IDC_QUALITY, mfc5);

	// LTEXT "High",IDC_STATIC,123,21,16,10
	CStatic *mfc6 = new CStatic(parent);
	CRect r6(CPoint(123, 21), CSize(16, 10));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("High"), WS_VISIBLE | WS_BORDER, r6, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Low",IDC_STATIC,15,61,15,10
	CStatic *mfc8 = new CStatic(parent);
	CRect r8(CPoint(15, 61), CSize(15, 10));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("Low"), WS_VISIBLE | WS_BORDER, r8, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_VOLUME, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 30, 59, 90, 15
	CSliderCtrl *mfc9 = new CSliderCtrl(parent);
	CRect r9(CPoint(30, 59), CSize(90, 15));
	parent->MapDialogRect(&r9);
	mfc9->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r9, parent, IDC_VOLUME);
	mfcToQtWidget->insert(IDC_VOLUME, mfc9);

	// LTEXT "High",IDC_STATIC,123,61,16,10
	CStatic *mfc10 = new CStatic(parent);
	CRect r10(CPoint(123, 61), CSize(16, 10));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("High"), WS_VISIBLE | WS_BORDER, r10, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Static",IDC_SAMPLE_RATE,15,99,118,8
	CStatic *mfc12 = new CStatic(parent);
	CRect r12(CPoint(15, 99), CSize(118, 8));
	parent->MapDialogRect(&r12);
	mfc12->Create(_T("Static"), WS_VISIBLE | WS_BORDER, r12, parent, IDC_SAMPLE_RATE);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Static",IDC_RESAMPLING,15,110,118,8
	CStatic *mfc13 = new CStatic(parent);
	CRect r13(CPoint(15, 110), CSize(118, 8));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("Static"), WS_VISIBLE | WS_BORDER, r13, parent, IDC_RESAMPLING);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// PUSHBUTTON "Preview",IDC_PREVIEW,154,7,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc14 = new CButton(parent);
	CRect r14(CPoint(154, 7), CSize(50, 14));
	parent->MapDialogRect(&r14);
	mfc14->Create(_T("Preview"), WS_VISIBLE | WS_BORDER, r14, parent, IDC_PREVIEW);
	mfcToQtWidget->insert(IDC_PREVIEW, mfc14);

	// DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,154,24,50,14
	CButton *mfc15 = new CButton(parent);
	CRect r15(CPoint(154, 24), CSize(50, 14));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T("OK"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r15, parent, IDOK);
	mfcToQtWidget->insert(IDOK, mfc15);

	// PUSHBUTTON "Cancel",IDCANCEL,154,41,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc16 = new CButton(parent);
	CRect r16(CPoint(154, 41), CSize(50, 14));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T("Cancel"), WS_VISIBLE | WS_BORDER, r16, parent, IDCANCEL);
	mfcToQtWidget->insert(IDCANCEL, mfc16);

	// LTEXT "Static",IDC_SAMPLESIZE,15,121,118,8
	CStatic *mfc17 = new CStatic(parent);
	CRect r17(CPoint(15, 121), CSize(118, 8));
	parent->MapDialogRect(&r17);
	mfc17->Create(_T("Static"), WS_VISIBLE | WS_BORDER, r17, parent, IDC_SAMPLESIZE);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// END
}

void qtMfcInitDialogResource_IDD_INSTRUMENT_INTERNAL(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_INSTRUMENT_INTERNAL DIALOGEX 0, 0, 372, 172
	CRect rect(CPoint(0, 0), CSize(372, 172));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// GROUPBOX "Sequence editor",IDC_STATIC,120,7,245,158
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(120, 7), CSize(245, 158));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Sequence editor"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Instrument settings",IDC_STATIC,7,7,107,158
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 7), CSize(107, 158));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Instrument settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER | 0, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_INSTSETTINGS, "SysListView32", WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_ALIGNLEFT|LVS_NOSORTHEADER|WS_BORDER|WS_TABSTOP, 12, 18, 96, 109
	CListCtrl *mfc2 = new CListCtrl(parent);
	CRect r2(CPoint(12, 18), CSize(96, 109));
	parent->MapDialogRect(&r2);
	mfc2->Create(WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | LVS_NOSORTHEADER | WS_BORDER | WS_TABSTOP, r2, parent, IDC_INSTSETTINGS);
	mfcToQtWidget->insert(IDC_INSTSETTINGS, mfc2);

	// PUSHBUTTON "Select next empty slot",IDC_FREE_SEQ,12,129,96,15,WS_VISIBLE|WS_BORDER
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(12, 129), CSize(96, 15));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Select next empty slot"), WS_VISIBLE | WS_BORDER, r3, parent, IDC_FREE_SEQ);
	mfcToQtWidget->insert(IDC_FREE_SEQ, mfc3);

	// CONTROL "Sequence #", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_LEFTNOWORDWRAP|SS_CENTERIMAGE|WS_GROUP, 12, 149, 53, 10
	CStatic *mfc4 = new CStatic(parent);
	CRect r4(CPoint(12, 149), CSize(53, 10));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("Sequence #"), WS_VISIBLE | WS_BORDER | SS_LEFTNOWORDWRAP | SS_CENTERIMAGE | WS_GROUP, r4, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc4);

	// EDITTEXT IDC_SEQ_INDEX,69,147,39,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER
	CEdit *mfc5 = new CEdit(parent);
	CRect r5(CPoint(69, 147), CSize(39, 12));
	parent->MapDialogRect(&r5);
	mfc5->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER, r5, parent, IDC_SEQ_INDEX);
	mfcToQtWidget->insert(IDC_SEQ_INDEX, mfc5);

	// CONTROL "", IDC_SEQUENCE_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 66, 153, 11, 9
	CSpinButtonCtrl *mfc6 = new CSpinButtonCtrl(parent);
	CRect r6(CPoint(66, 153), CSize(11, 9));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r6, parent, IDC_SEQUENCE_SPIN);
	mfcToQtWidget->insert(IDC_SEQUENCE_SPIN, mfc6);

	// EDITTEXT IDC_SEQUENCE_STRING,126,149,232,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc7 = new CEdit(parent);
	CRect r7(CPoint(126, 149), CSize(232, 13));
	parent->MapDialogRect(&r7);
	mfc7->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r7, parent, IDC_SEQUENCE_STRING);
	mfcToQtWidget->insert(IDC_SEQUENCE_STRING, mfc7);

	// END
}

void qtMfcInitDialogResource_IDD_INSTRUMENT_DPCM(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_INSTRUMENT_DPCM DIALOGEX 0, 0, 372, 174
	CRect rect(CPoint(0, 0), CSize(372, 174));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// GROUPBOX "Assigned samples",IDC_STATIC,7,7,179,160
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(179, 160));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Assigned samples"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Loaded samples",IDC_STATIC,192,7,173,160
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(192, 7), CSize(173, 160));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Loaded samples"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_TABLE, "SysListView32", WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_ALIGNLEFT|LVS_NOSORTHEADER|WS_BORDER|WS_TABSTOP, 15, 19, 117, 125
	CListCtrl *mfc3 = new CListCtrl(parent);
	CRect r3(CPoint(15, 19), CSize(117, 125));
	parent->MapDialogRect(&r3);
	mfc3->Create(WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | LVS_NOSORTHEADER | WS_BORDER | WS_TABSTOP, r3, parent, IDC_TABLE);
	mfcToQtWidget->insert(IDC_TABLE, mfc3);

	// COMBOBOX IDC_SAMPLES,15,148,117,125,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|CBS_SORT|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc4 = new CComboBox(parent);
	CRect r4(CPoint(15, 148), CSize(117, 125));
	parent->MapDialogRect(&r4);
	mfc4->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP, r4, parent, IDC_SAMPLES);
	mfcToQtWidget->insert(IDC_SAMPLES, mfc4);

	// LTEXT "Octave",IDC_STATIC,138,19,30,9
	CStatic *mfc5 = new CStatic(parent);
	CRect r5(CPoint(138, 19), CSize(30, 9));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Octave"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_OCTAVE,138,29,42,53,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc6 = new CComboBox(parent);
	CRect r6(CPoint(138, 29), CSize(42, 53));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r6, parent, IDC_OCTAVE);
	mfcToQtWidget->insert(IDC_OCTAVE, mfc6);

	// LTEXT "Pitch",IDC_STATIC,138,44,30,8
	CStatic *mfc7 = new CStatic(parent);
	CRect r7(CPoint(138, 44), CSize(30, 8));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("Pitch"), WS_VISIBLE | WS_BORDER, r7, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_PITCH,138,54,42,53,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc8 = new CComboBox(parent);
	CRect r8(CPoint(138, 54), CSize(42, 53));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r8, parent, IDC_PITCH);
	mfcToQtWidget->insert(IDC_PITCH, mfc8);

	// CONTROL "Loop", IDC_LOOP, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 138, 71, 42, 9
	CButton *mfc9 = new CButton(parent);
	CRect r9(CPoint(138, 71), CSize(42, 9));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("Loop"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r9, parent, IDC_LOOP);
	mfcToQtWidget->insert(IDC_LOOP, mfc9);

	// EDITTEXT IDC_DELTA_COUNTER,138,97,42,14,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc10 = new CEdit(parent);
	CRect r10(CPoint(138, 97), CSize(42, 14));
	parent->MapDialogRect(&r10);
	mfc10->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r10, parent, IDC_DELTA_COUNTER);
	mfcToQtWidget->insert(IDC_DELTA_COUNTER, mfc10);

	// CONTROL "", IDC_DELTA_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 170, 106, 11, 14
	CSpinButtonCtrl *mfc11 = new CSpinButtonCtrl(parent);
	CRect r11(CPoint(170, 106), CSize(11, 14));
	parent->MapDialogRect(&r11);
	mfc11->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r11, parent, IDC_DELTA_SPIN);
	mfcToQtWidget->insert(IDC_DELTA_SPIN, mfc11);

	// PUSHBUTTON "",IDC_ADD,138,130,42,14,WS_VISIBLE|WS_BORDER|BS_ICON
	CButton *mfc12 = new CButton(parent);
	CRect r12(CPoint(138, 130), CSize(42, 14));
	parent->MapDialogRect(&r12);
	mfc12->Create(_T(""), WS_VISIBLE | WS_BORDER | BS_ICON, r12, parent, IDC_ADD);
	mfcToQtWidget->insert(IDC_ADD, mfc12);

	// PUSHBUTTON "",IDC_REMOVE,138,148,42,14,WS_VISIBLE|WS_BORDER|BS_ICON
	CButton *mfc13 = new CButton(parent);
	CRect r13(CPoint(138, 148), CSize(42, 14));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T(""), WS_VISIBLE | WS_BORDER | BS_ICON, r13, parent, IDC_REMOVE);
	mfcToQtWidget->insert(IDC_REMOVE, mfc13);

	// CONTROL "", IDC_SAMPLE_LIST, "SysListView32", WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_ALIGNLEFT|LVS_NOSORTHEADER|WS_BORDER|WS_TABSTOP, 198, 19, 108, 125
	CListCtrl *mfc15 = new CListCtrl(parent);
	CRect r15(CPoint(198, 19), CSize(108, 125));
	parent->MapDialogRect(&r15);
	mfc15->Create(WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | LVS_NOSORTHEADER | WS_BORDER | WS_TABSTOP, r15, parent, IDC_SAMPLE_LIST);
	mfcToQtWidget->insert(IDC_SAMPLE_LIST, mfc15);

	// LTEXT "Space used 16 / 16 kb",IDC_SPACE,198,151,166,9
	CStatic *mfc16 = new CStatic(parent);
	CRect r16(CPoint(198, 151), CSize(166, 9));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T("Space used 16 / 16 kb"), WS_VISIBLE | WS_BORDER, r16, parent, IDC_SPACE);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// DEFPUSHBUTTON "Load",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,312,19,47,14
	CButton *mfc17 = new CButton(parent);
	CRect r17(CPoint(312, 19), CSize(47, 14));
	parent->MapDialogRect(&r17);
	mfc17->Create(_T("Load"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r17, parent, IDC_LOAD);
	mfcToQtWidget->insert(IDC_LOAD, mfc17);

	// PUSHBUTTON "Unload",IDC_UNLOAD,312,35,47,14,WS_VISIBLE|WS_BORDER
	CButton *mfc18 = new CButton(parent);
	CRect r18(CPoint(312, 35), CSize(47, 14));
	parent->MapDialogRect(&r18);
	mfc18->Create(_T("Unload"), WS_VISIBLE | WS_BORDER, r18, parent, IDC_UNLOAD);
	mfcToQtWidget->insert(IDC_UNLOAD, mfc18);

	// PUSHBUTTON "Save",IDC_SAVE,312,51,47,14,WS_VISIBLE|WS_BORDER
	CButton *mfc19 = new CButton(parent);
	CRect r19(CPoint(312, 51), CSize(47, 14));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T("Save"), WS_VISIBLE | WS_BORDER, r19, parent, IDC_SAVE);
	mfcToQtWidget->insert(IDC_SAVE, mfc19);

	// PUSHBUTTON "Import",IDC_IMPORT,312,67,47,14,WS_VISIBLE|WS_BORDER
	CButton *mfc20 = new CButton(parent);
	CRect r20(CPoint(312, 67), CSize(47, 14));
	parent->MapDialogRect(&r20);
	mfc20->Create(_T("Import"), WS_VISIBLE | WS_BORDER, r20, parent, IDC_IMPORT);
	mfcToQtWidget->insert(IDC_IMPORT, mfc20);

	// PUSHBUTTON "Edit",IDC_EDIT,312,83,47,14,WS_VISIBLE|WS_BORDER
	CButton *mfc21 = new CButton(parent);
	CRect r21(CPoint(312, 83), CSize(47, 14));
	parent->MapDialogRect(&r21);
	mfc21->Create(_T("Edit"), WS_VISIBLE | WS_BORDER, r21, parent, IDC_EDIT);
	mfcToQtWidget->insert(IDC_EDIT, mfc21);

	// PUSHBUTTON "Preview",IDC_PREVIEW,312,99,47,14,WS_VISIBLE|WS_BORDER
	CButton *mfc22 = new CButton(parent);
	CRect r22(CPoint(312, 99), CSize(47, 14));
	parent->MapDialogRect(&r22);
	mfc22->Create(_T("Preview"), WS_VISIBLE | WS_BORDER, r22, parent, IDC_PREVIEW);
	mfcToQtWidget->insert(IDC_PREVIEW, mfc22);

	// LTEXT "D-counter",IDC_STATIC,138,86,33,8
	CStatic *mfc23 = new CStatic(parent);
	CRect r23(CPoint(138, 86), CSize(33, 8));
	parent->MapDialogRect(&r23);
	mfc23->Create(_T("D-counter"), WS_VISIBLE | WS_BORDER, r23, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// END
}

void qtMfcInitDialogResource_IDD_INSTRUMENT(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_INSTRUMENT DIALOGEX 0, 0, 389, 242
	CRect rect(CPoint(0, 0), CSize(389, 242));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Instrument editor"
	parent->SetWindowText("Instrument editor");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|DS_CENTER|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// CONTROL "", IDC_INST_TAB, "SysTabControl32", WS_VISIBLE|WS_BORDER|0x0, 7, 7, 375, 185
	CTabCtrl *mfc0 = new CTabCtrl(parent);
	CRect r0(CPoint(7, 7), CSize(375, 185));
	parent->MapDialogRect(&r0);
	mfc0->Create(WS_VISIBLE | WS_BORDER | 0x0, r0, parent, IDC_INST_TAB);
	mfcToQtWidget->insert(IDC_INST_TAB, mfc0);

	// CONTROL "", IDC_KEYBOARD, "Static", WS_VISIBLE|WS_BORDER|SS_OWNERDRAW|SS_REALSIZEIMAGE|SS_SUNKEN, 7, 198, 375, 37
	CStatic *mfc1 = new CStatic(parent);
	CRect r1(CPoint(7, 198), CSize(375, 37));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_OWNERDRAW | SS_REALSIZEIMAGE | SS_SUNKEN, r1, parent, IDC_KEYBOARD);
	mfcToQtWidget->insert(IDC_KEYBOARD, mfc1);

	// END
}

void qtMfcInitDialogResource_IDD_CONFIG_APPEARANCE(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CONFIG_APPEARANCE DIALOGEX 0, 0, 280, 167
	CRect rect(CPoint(0, 0), CSize(280, 167));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Appearance"
	parent->SetWindowText("Appearance");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Color schemes",IDC_STATIC,7,7,149,39
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(149, 39));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Color schemes"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Colors",IDC_STATIC,7,54,149,65
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 54), CSize(149, 65));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Colors"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Pattern font and size",IDC_STATIC,7,126,149,34
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(7, 126), CSize(149, 34));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Pattern font and size"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Preview",IDC_STATIC,166,7,107,153
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(166, 7), CSize(107, 153));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Preview"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r3, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_SCHEME,15,22,135,126,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|CBS_SORT|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc5 = new CComboBox(parent);
	CRect r5(CPoint(15, 22), CSize(135, 126));
	parent->MapDialogRect(&r5);
	mfc5->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP, r5, parent, IDC_SCHEME);
	mfcToQtWidget->insert(IDC_SCHEME, mfc5);

	// LTEXT "Item",IDC_STATIC,15,68,16,8
	CStatic *mfc7 = new CStatic(parent);
	CRect r7(CPoint(15, 68), CSize(16, 8));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("Item"), WS_VISIBLE | WS_BORDER, r7, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_COL_ITEM,35,66,115,172,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc8 = new CComboBox(parent);
	CRect r8(CPoint(35, 66), CSize(115, 172));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r8, parent, IDC_COL_ITEM);
	mfcToQtWidget->insert(IDC_COL_ITEM, mfc8);

	// CONTROL "", IDC_COL_PREVIEW, "Static", WS_VISIBLE|WS_BORDER|SS_OWNERDRAW, 15, 85, 69, 15
	CStatic *mfc9 = new CStatic(parent);
	CRect r9(CPoint(15, 85), CSize(69, 15));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_OWNERDRAW, r9, parent, IDC_COL_PREVIEW);
	mfcToQtWidget->insert(IDC_COL_PREVIEW, mfc9);

	// PUSHBUTTON "Pick color",IDC_PICK_COL,96,85,54,15,WS_VISIBLE|WS_BORDER
	CButton *mfc10 = new CButton(parent);
	CRect r10(CPoint(96, 85), CSize(54, 15));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("Pick color"), WS_VISIBLE | WS_BORDER, r10, parent, IDC_PICK_COL);
	mfcToQtWidget->insert(IDC_PICK_COL, mfc10);

	// CONTROL "Pattern colors", IDC_PATTERNCOLORS, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 15, 105, 58, 9
	CButton *mfc11 = new CButton(parent);
	CRect r11(CPoint(15, 105), CSize(58, 9));
	parent->MapDialogRect(&r11);
	mfc11->Create(_T("Pattern colors"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r11, parent, IDC_PATTERNCOLORS);
	mfcToQtWidget->insert(IDC_PATTERNCOLORS, mfc11);

	// COMBOBOX IDC_FONT,15,139,102,93,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|CBS_SORT|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc13 = new CComboBox(parent);
	CRect r13(CPoint(15, 139), CSize(102, 93));
	parent->MapDialogRect(&r13);
	mfc13->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP, r13, parent, IDC_FONT);
	mfcToQtWidget->insert(IDC_FONT, mfc13);

	// COMBOBOX IDC_FONT_SIZE,122,139,28,30,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc14 = new CComboBox(parent);
	CRect r14(CPoint(122, 139), CSize(28, 30));
	parent->MapDialogRect(&r14);
	mfc14->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r14, parent, IDC_FONT_SIZE);
	mfcToQtWidget->insert(IDC_FONT_SIZE, mfc14);

	// CONTROL "", IDC_PREVIEW, "Static", WS_VISIBLE|WS_BORDER|SS_OWNERDRAW, 176, 18, 90, 135
	CStatic *mfc16 = new CStatic(parent);
	CRect r16(CPoint(176, 18), CSize(90, 135));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_OWNERDRAW, r16, parent, IDC_PREVIEW);
	mfcToQtWidget->insert(IDC_PREVIEW, mfc16);

	// CONTROL "Display flats", IDC_DISPLAYFLATS, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 83, 105, 58, 9
	CButton *mfc17 = new CButton(parent);
	CRect r17(CPoint(83, 105), CSize(58, 9));
	parent->MapDialogRect(&r17);
	mfc17->Create(_T("Display flats"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r17, parent, IDC_DISPLAYFLATS);
	mfcToQtWidget->insert(IDC_DISPLAYFLATS, mfc17);

	// END
}

void qtMfcInitDialogResource_IDD_CONFIG_GENERAL(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CONFIG_GENERAL DIALOGEX 0, 0, 280, 167
	CRect rect(CPoint(0, 0), CSize(280, 167));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "General"
	parent->SetWindowText("General");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "General settings",IDC_STATIC,7,7,125,153
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(125, 153));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("General settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Pattern edit style",IDC_STATIC,138,7,135,48
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(138, 7), CSize(135, 48));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Pattern edit style"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Edit settings",IDC_STATIC,137,57,135,30
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(137, 57), CSize(135, 30));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Edit settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Keys",IDC_STATIC,138,89,135,71
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(138, 89), CSize(135, 71));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Keys"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r3, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "Wrap cursor", IDC_OPT_WRAPCURSOR, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 18, 113, 9
	CButton *mfc5 = new CButton(parent);
	CRect r5(CPoint(13, 18), CSize(113, 9));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Wrap cursor"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r5, parent, IDC_OPT_WRAPCURSOR);
	mfcToQtWidget->insert(IDC_OPT_WRAPCURSOR, mfc5);

	// CONTROL "Wrap across frames", IDC_OPT_WRAPFRAMES, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 28, 113, 9
	CButton *mfc6 = new CButton(parent);
	CRect r6(CPoint(13, 28), CSize(113, 9));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Wrap across frames"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r6, parent, IDC_OPT_WRAPFRAMES);
	mfcToQtWidget->insert(IDC_OPT_WRAPFRAMES, mfc6);

	// CONTROL "Free cursor edit", IDC_OPT_FREECURSOR, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 38, 113, 9
	CButton *mfc7 = new CButton(parent);
	CRect r7(CPoint(13, 38), CSize(113, 9));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("Free cursor edit"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r7, parent, IDC_OPT_FREECURSOR);
	mfcToQtWidget->insert(IDC_OPT_FREECURSOR, mfc7);

	// CONTROL "Preview wave-files", IDC_OPT_WAVEPREVIEW, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 48, 113, 9
	CButton *mfc8 = new CButton(parent);
	CRect r8(CPoint(13, 48), CSize(113, 9));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("Preview wave-files"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r8, parent, IDC_OPT_WAVEPREVIEW);
	mfcToQtWidget->insert(IDC_OPT_WAVEPREVIEW, mfc8);

	// CONTROL "Key repeat", IDC_OPT_KEYREPEAT, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 58, 113, 9
	CButton *mfc9 = new CButton(parent);
	CRect r9(CPoint(13, 58), CSize(113, 9));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("Key repeat"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r9, parent, IDC_OPT_KEYREPEAT);
	mfcToQtWidget->insert(IDC_OPT_KEYREPEAT, mfc9);

	// CONTROL "Show row numbers in hex", IDC_OPT_HEXROW, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 68, 113, 9
	CButton *mfc10 = new CButton(parent);
	CRect r10(CPoint(13, 68), CSize(113, 9));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("Show row numbers in hex"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r10, parent, IDC_OPT_HEXROW);
	mfcToQtWidget->insert(IDC_OPT_HEXROW, mfc10);

	// CONTROL "Preview next/previous frame", IDC_OPT_FRAMEPREVIEW, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 78, 113, 9
	CButton *mfc11 = new CButton(parent);
	CRect r11(CPoint(13, 78), CSize(113, 9));
	parent->MapDialogRect(&r11);
	mfc11->Create(_T("Preview next/previous frame"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r11, parent, IDC_OPT_FRAMEPREVIEW);
	mfcToQtWidget->insert(IDC_OPT_FRAMEPREVIEW, mfc11);

	// CONTROL "Don't reset DPCM on note stop", IDC_OPT_NODPCMRESET, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 88, 113, 9
	CButton *mfc12 = new CButton(parent);
	CRect r12(CPoint(13, 88), CSize(113, 9));
	parent->MapDialogRect(&r12);
	mfc12->Create(_T("Don't reset DPCM on note stop"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r12, parent, IDC_OPT_NODPCMRESET);
	mfcToQtWidget->insert(IDC_OPT_NODPCMRESET, mfc12);

	// CONTROL "Ignore Step when moving", IDC_OPT_NOSTEPMOVE, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 98, 113, 9
	CButton *mfc13 = new CButton(parent);
	CRect r13(CPoint(13, 98), CSize(113, 9));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("Ignore Step when moving"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r13, parent, IDC_OPT_NOSTEPMOVE);
	mfcToQtWidget->insert(IDC_OPT_NOSTEPMOVE, mfc13);

	// CONTROL "Delete-key pulls up rows", IDC_OPT_PULLUPDELETE, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 108, 113, 9
	CButton *mfc14 = new CButton(parent);
	CRect r14(CPoint(13, 108), CSize(113, 9));
	parent->MapDialogRect(&r14);
	mfc14->Create(_T("Delete-key pulls up rows"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r14, parent, IDC_OPT_PULLUPDELETE);
	mfcToQtWidget->insert(IDC_OPT_PULLUPDELETE, mfc14);

	// CONTROL "Backup files", IDC_OPT_BACKUPS, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 118, 113, 9
	CButton *mfc15 = new CButton(parent);
	CRect r15(CPoint(13, 118), CSize(113, 9));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T("Backup files"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r15, parent, IDC_OPT_BACKUPS);
	mfcToQtWidget->insert(IDC_OPT_BACKUPS, mfc15);

	// CONTROL "Single instance", IDC_OPT_SINGLEINSTANCE, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 128, 113, 9
	CButton *mfc16 = new CButton(parent);
	CRect r16(CPoint(13, 128), CSize(113, 9));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T("Single instance"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r16, parent, IDC_OPT_SINGLEINSTANCE);
	mfcToQtWidget->insert(IDC_OPT_SINGLEINSTANCE, mfc16);

	// CONTROL "FastTracker 2", IDC_STYLE1, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 144, 18, 120, 8
	CButton *mfc18 = new CButton(parent);
	CRect r18(CPoint(144, 18), CSize(120, 8));
	parent->MapDialogRect(&r18);
	mfc18->Create(_T("FastTracker 2"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r18, parent, IDC_STYLE1);
	mfcToQtWidget->insert(IDC_STYLE1, mfc18);

	// CONTROL "ModPlug tracker", IDC_STYLE2, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 144, 30, 120, 8
	CButton *mfc19 = new CButton(parent);
	CRect r19(CPoint(144, 30), CSize(120, 8));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T("ModPlug tracker"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r19, parent, IDC_STYLE2);
	mfcToQtWidget->insert(IDC_STYLE2, mfc19);

	// CONTROL "Impulse Tracker", IDC_STYLE3, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 144, 42, 120, 8
	CButton *mfc20 = new CButton(parent);
	CRect r20(CPoint(144, 42), CSize(120, 8));
	parent->MapDialogRect(&r20);
	mfc20->Create(_T("Impulse Tracker"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r20, parent, IDC_STYLE3);
	mfcToQtWidget->insert(IDC_STYLE3, mfc20);

	// LTEXT "Page jump length",IDC_STATIC,143,70,56,9
	CStatic *mfc22 = new CStatic(parent);
	CRect r22(CPoint(143, 70), CSize(56, 9));
	parent->MapDialogRect(&r22);
	mfc22->Create(_T("Page jump length"), WS_VISIBLE | WS_BORDER, r22, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_PAGELENGTH,215,68,48,65,WS_VISIBLE|WS_BORDER|CBS_DROPDOWN|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc23 = new CComboBox(parent);
	CRect r23(CPoint(215, 68), CSize(48, 65));
	parent->MapDialogRect(&r23);
	mfc23->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | WS_VSCROLL | WS_TABSTOP, r23, parent, IDC_PAGELENGTH);
	mfcToQtWidget->insert(IDC_PAGELENGTH, mfc23);

	mfc23->AddString(_T("2"));

	mfc23->AddString(_T("4"));

	mfc23->AddString(_T("8"));

	mfc23->AddString(_T("16"));

	// LTEXT "Note cut",IDC_STATIC,144,100,50,11
	CStatic *mfc25 = new CStatic(parent);
	CRect r25(CPoint(144, 100), CSize(50, 11));
	parent->MapDialogRect(&r25);
	mfc25->Create(_T("Note cut"), WS_VISIBLE | WS_BORDER, r25, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_KEY_NOTE_CUT,204,99,60,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc26 = new CEdit(parent);
	CRect r26(CPoint(204, 99), CSize(60, 13));
	parent->MapDialogRect(&r26);
	mfc26->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r26, parent, IDC_KEY_NOTE_CUT);
	mfcToQtWidget->insert(IDC_KEY_NOTE_CUT, mfc26);

	// LTEXT "Clear field",IDC_STATIC,144,115,50,11
	CStatic *mfc27 = new CStatic(parent);
	CRect r27(CPoint(144, 115), CSize(50, 11));
	parent->MapDialogRect(&r27);
	mfc27->Create(_T("Clear field"), WS_VISIBLE | WS_BORDER, r27, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_KEY_CLEAR,204,114,60,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc28 = new CEdit(parent);
	CRect r28(CPoint(204, 114), CSize(60, 13));
	parent->MapDialogRect(&r28);
	mfc28->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r28, parent, IDC_KEY_CLEAR);
	mfcToQtWidget->insert(IDC_KEY_CLEAR, mfc28);

	// LTEXT "Repeat",IDC_STATIC,144,129,50,11
	CStatic *mfc29 = new CStatic(parent);
	CRect r29(CPoint(144, 129), CSize(50, 11));
	parent->MapDialogRect(&r29);
	mfc29->Create(_T("Repeat"), WS_VISIBLE | WS_BORDER, r29, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_KEY_REPEAT,204,128,60,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc30 = new CEdit(parent);
	CRect r30(CPoint(204, 128), CSize(60, 13));
	parent->MapDialogRect(&r30);
	mfc30->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r30, parent, IDC_KEY_REPEAT);
	mfcToQtWidget->insert(IDC_KEY_REPEAT, mfc30);

	// LTEXT "Note release",IDC_STATIC,144,143,50,11
	CStatic *mfc31 = new CStatic(parent);
	CRect r31(CPoint(144, 143), CSize(50, 11));
	parent->MapDialogRect(&r31);
	mfc31->Create(_T("Note release"), WS_VISIBLE | WS_BORDER, r31, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_KEY_NOTE_RELEASE,204,142,60,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc32 = new CEdit(parent);
	CRect r32(CPoint(204, 142), CSize(60, 13));
	parent->MapDialogRect(&r32);
	mfc32->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r32, parent, IDC_KEY_NOTE_RELEASE);
	mfcToQtWidget->insert(IDC_KEY_NOTE_RELEASE, mfc32);

	// CONTROL "Preview full row", IDC_OPT_PREVIEWFULLROW, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 138, 113, 9
	CButton *mfc33 = new CButton(parent);
	CRect r33(CPoint(13, 138), CSize(113, 9));
	parent->MapDialogRect(&r33);
	mfc33->Create(_T("Preview full row"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r33, parent, IDC_OPT_PREVIEWFULLROW);
	mfcToQtWidget->insert(IDC_OPT_PREVIEWFULLROW, mfc33);

	// CONTROL "Don't select on double-click", IDC_OPT_DOUBLECLICK, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 148, 113, 9
	CButton *mfc34 = new CButton(parent);
	CRect r34(CPoint(13, 148), CSize(113, 9));
	parent->MapDialogRect(&r34);
	mfc34->Create(_T("Don't select on double-click"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r34, parent, IDC_OPT_DOUBLECLICK);
	mfcToQtWidget->insert(IDC_OPT_DOUBLECLICK, mfc34);

	// END
}

void qtMfcInitDialogResource_IDD_CONFIG_MIDI(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CONFIG_MIDI DIALOGEX 0, 0, 280, 167
	CRect rect(CPoint(0, 0), CSize(280, 167));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "MIDI"
	parent->SetWindowText("MIDI");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Input Device",IDC_STATIC,7,7,266,35
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(266, 35));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Input Device"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Output Device",IDC_STATIC,7,48,266,35
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 48), CSize(266, 35));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Output Device"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Options",IDC_STATIC,7,89,266,71
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(7, 89), CSize(266, 71));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Options"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_INDEVICES,13,20,253,50,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc4 = new CComboBox(parent);
	CRect r4(CPoint(13, 20), CSize(253, 50));
	parent->MapDialogRect(&r4);
	mfc4->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r4, parent, IDC_INDEVICES);
	mfcToQtWidget->insert(IDC_INDEVICES, mfc4);

	// COMBOBOX IDC_OUTDEVICES,13,61,253,50,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc6 = new CComboBox(parent);
	CRect r6(CPoint(13, 61), CSize(253, 50));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r6, parent, IDC_OUTDEVICES);
	mfcToQtWidget->insert(IDC_OUTDEVICES, mfc6);

	// CONTROL "Receive sync ticks", IDC_MASTER_SYNC, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 102, 173, 10
	CButton *mfc7 = new CButton(parent);
	CRect r7(CPoint(13, 102), CSize(173, 10));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("Receive sync ticks"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r7, parent, IDC_MASTER_SYNC);
	mfcToQtWidget->insert(IDC_MASTER_SYNC, mfc7);

	// CONTROL "Skip key releases", IDC_KEY_RELEASE, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 112, 173, 10
	CButton *mfc8 = new CButton(parent);
	CRect r8(CPoint(13, 112), CSize(173, 10));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("Skip key releases"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r8, parent, IDC_KEY_RELEASE);
	mfcToQtWidget->insert(IDC_KEY_RELEASE, mfc8);

	// CONTROL "Map MIDI channels to NES channels", IDC_CHANMAP, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 122, 173, 10
	CButton *mfc9 = new CButton(parent);
	CRect r9(CPoint(13, 122), CSize(173, 10));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("Map MIDI channels to NES channels"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r9, parent, IDC_CHANMAP);
	mfcToQtWidget->insert(IDC_CHANMAP, mfc9);

	// CONTROL "Record velocities", IDC_VELOCITY, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 132, 173, 10
	CButton *mfc10 = new CButton(parent);
	CRect r10(CPoint(13, 132), CSize(173, 10));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("Record velocities"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r10, parent, IDC_VELOCITY);
	mfcToQtWidget->insert(IDC_VELOCITY, mfc10);

	// CONTROL "Auto arpeggiate chords", IDC_ARPEGGIATE, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 13, 142, 173, 10
	CButton *mfc11 = new CButton(parent);
	CRect r11(CPoint(13, 142), CSize(173, 10));
	parent->MapDialogRect(&r11);
	mfc11->Create(_T("Auto arpeggiate chords"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r11, parent, IDC_ARPEGGIATE);
	mfcToQtWidget->insert(IDC_ARPEGGIATE, mfc11);

	// END
}

void qtMfcInitDialogResource_IDD_CONFIG_SOUND(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CONFIG_SOUND DIALOGEX 0, 0, 280, 167
	CRect rect(CPoint(0, 0), CSize(280, 167));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Sound"
	parent->SetWindowText("Sound");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Device",IDC_STATIC,7,7,266,35
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(266, 35));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Device"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Sample rate",IDC_STATIC,7,48,113,33
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 48), CSize(113, 33));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Sample rate"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Sample size",IDC_STATIC,7,90,113,33
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(7, 90), CSize(113, 33));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Sample size"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Buffer length",IDC_STATIC,7,129,113,31
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(7, 129), CSize(113, 31));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Buffer length"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r3, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Bass filtering",IDC_STATIC,126,48,147,33
	CButton *mfc4 = new CButton(parent);
	CRect r4(CPoint(126, 48), CSize(147, 33));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("Bass filtering"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r4, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Treble filtering",IDC_STATIC,126,86,147,43
	CButton *mfc5 = new CButton(parent);
	CRect r5(CPoint(126, 86), CSize(147, 43));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Treble filtering"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r5, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Volume",IDC_STATIC,126,133,147,27
	CButton *mfc6 = new CButton(parent);
	CRect r6(CPoint(126, 133), CSize(147, 27));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Volume"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r6, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_DEVICES,13,20,253,12,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc8 = new CComboBox(parent);
	CRect r8(CPoint(13, 20), CSize(253, 12));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r8, parent, IDC_DEVICES);
	mfcToQtWidget->insert(IDC_DEVICES, mfc8);

	// COMBOBOX IDC_SAMPLE_RATE,13,61,101,62,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|CBS_SORT|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc10 = new CComboBox(parent);
	CRect r10(CPoint(13, 61), CSize(101, 62));
	parent->MapDialogRect(&r10);
	mfc10->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP, r10, parent, IDC_SAMPLE_RATE);
	mfcToQtWidget->insert(IDC_SAMPLE_RATE, mfc10);

	mfc10->AddString(_T("11 025 Hz"));

	mfc10->AddString(_T("22 050 Hz"));

	mfc10->AddString(_T("44 100 Hz"));

	mfc10->AddString(_T("48 000 Hz"));

	mfc10->AddString(_T("96 000 Hz"));

	// COMBOBOX IDC_SAMPLE_SIZE,13,102,101,62,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|CBS_SORT|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc12 = new CComboBox(parent);
	CRect r12(CPoint(13, 102), CSize(101, 62));
	parent->MapDialogRect(&r12);
	mfc12->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP, r12, parent, IDC_SAMPLE_SIZE);
	mfcToQtWidget->insert(IDC_SAMPLE_SIZE, mfc12);

	mfc12->AddString(_T("16 bit"));

	mfc12->AddString(_T("8 bit"));

	// CONTROL "", IDC_BUF_LENGTH, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_BOTH|TBS_NOTICKS|WS_TABSTOP, 13, 141, 69, 12
	CSliderCtrl *mfc14 = new CSliderCtrl(parent);
	CRect r14(CPoint(13, 141), CSize(69, 12));
	parent->MapDialogRect(&r14);
	mfc14->Create(WS_VISIBLE | WS_BORDER | TBS_BOTH | TBS_NOTICKS | WS_TABSTOP, r14, parent, IDC_BUF_LENGTH);
	mfcToQtWidget->insert(IDC_BUF_LENGTH, mfc14);

	// CTEXT "20 ms",IDC_BUF_LEN,83,142,31,11
	CStatic *mfc15 = new CStatic(parent);
	CRect r15(CPoint(83, 142), CSize(31, 11));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T("20 ms"), WS_VISIBLE | WS_BORDER, r15, parent, IDC_BUF_LEN);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Frequency",IDC_STATIC,132,63,36,11
	CStatic *mfc17 = new CStatic(parent);
	CRect r17(CPoint(132, 63), CSize(36, 11));
	parent->MapDialogRect(&r17);
	mfc17->Create(_T("Frequency"), WS_VISIBLE | WS_BORDER, r17, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_BASS_FREQ, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_BOTH|TBS_NOTICKS|WS_TABSTOP, 174, 63, 55, 12
	CSliderCtrl *mfc18 = new CSliderCtrl(parent);
	CRect r18(CPoint(174, 63), CSize(55, 12));
	parent->MapDialogRect(&r18);
	mfc18->Create(WS_VISIBLE | WS_BORDER | TBS_BOTH | TBS_NOTICKS | WS_TABSTOP, r18, parent, IDC_BASS_FREQ);
	mfcToQtWidget->insert(IDC_BASS_FREQ, mfc18);

	// CTEXT "16 Hz",IDC_BASS_FREQ_T,234,64,32,10
	CStatic *mfc19 = new CStatic(parent);
	CRect r19(CPoint(234, 64), CSize(32, 10));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T("16 Hz"), WS_VISIBLE | WS_BORDER, r19, parent, IDC_BASS_FREQ_T);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Damping",IDC_STATIC,132,99,36,10
	CStatic *mfc21 = new CStatic(parent);
	CRect r21(CPoint(132, 99), CSize(36, 10));
	parent->MapDialogRect(&r21);
	mfc21->Create(_T("Damping"), WS_VISIBLE | WS_BORDER, r21, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_TREBLE_DAMP, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_BOTH|TBS_NOTICKS|WS_TABSTOP, 174, 99, 55, 12
	CSliderCtrl *mfc22 = new CSliderCtrl(parent);
	CRect r22(CPoint(174, 99), CSize(55, 12));
	parent->MapDialogRect(&r22);
	mfc22->Create(WS_VISIBLE | WS_BORDER | TBS_BOTH | TBS_NOTICKS | WS_TABSTOP, r22, parent, IDC_TREBLE_DAMP);
	mfcToQtWidget->insert(IDC_TREBLE_DAMP, mfc22);

	// CTEXT "-24 dB",IDC_TREBLE_DAMP_T,234,99,32,9
	CStatic *mfc23 = new CStatic(parent);
	CRect r23(CPoint(234, 99), CSize(32, 9));
	parent->MapDialogRect(&r23);
	mfc23->Create(_T("-24 dB"), WS_VISIBLE | WS_BORDER, r23, parent, IDC_TREBLE_DAMP_T);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Frequency",IDC_STATIC,132,112,36,10
	CStatic *mfc24 = new CStatic(parent);
	CRect r24(CPoint(132, 112), CSize(36, 10));
	parent->MapDialogRect(&r24);
	mfc24->Create(_T("Frequency"), WS_VISIBLE | WS_BORDER, r24, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_TREBLE_FREQ, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_BOTH|TBS_NOTICKS|WS_TABSTOP, 174, 112, 55, 12
	CSliderCtrl *mfc25 = new CSliderCtrl(parent);
	CRect r25(CPoint(174, 112), CSize(55, 12));
	parent->MapDialogRect(&r25);
	mfc25->Create(WS_VISIBLE | WS_BORDER | TBS_BOTH | TBS_NOTICKS | WS_TABSTOP, r25, parent, IDC_TREBLE_FREQ);
	mfcToQtWidget->insert(IDC_TREBLE_FREQ, mfc25);

	// CTEXT "12000 Hz",IDC_TREBLE_FREQ_T,234,110,32,11
	CStatic *mfc26 = new CStatic(parent);
	CRect r26(CPoint(234, 110), CSize(32, 11));
	parent->MapDialogRect(&r26);
	mfc26->Create(_T("12000 Hz"), WS_VISIBLE | WS_BORDER, r26, parent, IDC_TREBLE_FREQ_T);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_VOLUME, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_BOTH|TBS_NOTICKS|WS_TABSTOP, 132, 144, 96, 12
	CSliderCtrl *mfc28 = new CSliderCtrl(parent);
	CRect r28(CPoint(132, 144), CSize(96, 12));
	parent->MapDialogRect(&r28);
	mfc28->Create(WS_VISIBLE | WS_BORDER | TBS_BOTH | TBS_NOTICKS | WS_TABSTOP, r28, parent, IDC_VOLUME);
	mfcToQtWidget->insert(IDC_VOLUME, mfc28);

	// CTEXT "100 %",IDC_VOLUME_T,234,144,31,8
	CStatic *mfc29 = new CStatic(parent);
	CRect r29(CPoint(234, 144), CSize(31, 8));
	parent->MapDialogRect(&r29);
	mfc29->Create(_T("100 %"), WS_VISIBLE | WS_BORDER, r29, parent, IDC_VOLUME_T);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// END
}

void qtMfcInitDialogResource_IDD_CONFIG_SHORTCUTS(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CONFIG_SHORTCUTS DIALOGEX 0, 0, 280, 167
	CRect rect(CPoint(0, 0), CSize(280, 167));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Shortcuts"
	parent->SetWindowText("Shortcuts");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// CONTROL "", IDC_SHORTCUTS, "SysListView32", WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_ALIGNLEFT|WS_BORDER|WS_TABSTOP, 7, 7, 266, 136
	CListCtrl *mfc0 = new CListCtrl(parent);
	CRect r0(CPoint(7, 7), CSize(266, 136));
	parent->MapDialogRect(&r0);
	mfc0->Create(WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | WS_BORDER | WS_TABSTOP, r0, parent, IDC_SHORTCUTS);
	mfcToQtWidget->insert(IDC_SHORTCUTS, mfc0);

	// LTEXT "Keys:",IDC_STATIC,7,149,23,12
	CStatic *mfc1 = new CStatic(parent);
	CRect r1(CPoint(7, 149), CSize(23, 12));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Keys:"), WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_KEY,36,147,144,14,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc2 = new CEdit(parent);
	CRect r2(CPoint(36, 147), CSize(144, 14));
	parent->MapDialogRect(&r2);
	mfc2->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r2, parent, IDC_KEY);
	mfcToQtWidget->insert(IDC_KEY, mfc2);

	// PUSHBUTTON "Clear",IDC_CLEAR,186,147,36,14,WS_VISIBLE|WS_BORDER
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(186, 147), CSize(36, 14));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Clear"), WS_VISIBLE | WS_BORDER, r3, parent, IDC_CLEAR);
	mfcToQtWidget->insert(IDC_CLEAR, mfc3);

	// PUSHBUTTON "Default",IDC_DEFAULT,228,147,45,14,WS_VISIBLE|WS_BORDER
	CButton *mfc4 = new CButton(parent);
	CRect r4(CPoint(228, 147), CSize(45, 14));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("Default"), WS_VISIBLE | WS_BORDER, r4, parent, IDC_DEFAULT);
	mfcToQtWidget->insert(IDC_DEFAULT, mfc4);

	// END
}

void qtMfcInitDialogResource_IDD_OCTAVE(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_OCTAVE DIALOGEX 0, 0, 276, 12
	CRect rect(CPoint(0, 0), CSize(276, 12));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// COMBOBOX IDC_OCTAVE,36,0,30,74,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|CBS_SORT|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc0 = new CComboBox(parent);
	CRect r0(CPoint(36, 0), CSize(30, 74));
	parent->MapDialogRect(&r0);
	mfc0->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP, r0, parent, IDC_OCTAVE);
	mfcToQtWidget->insert(IDC_OCTAVE, mfc0);

	mfc0->AddString(_T("0"));

	mfc0->AddString(_T("1"));

	mfc0->AddString(_T("2"));

	mfc0->AddString(_T("3"));

	mfc0->AddString(_T("4"));

	mfc0->AddString(_T("5"));

	mfc0->AddString(_T("6"));

	mfc0->AddString(_T("7"));

	// CONTROL "Octave", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_LEFTNOWORDWRAP|WS_GROUP, 6, 1, 24, 8
	CStatic *mfc1 = new CStatic(parent);
	CRect r1(CPoint(6, 1), CSize(24, 8));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Octave"), WS_VISIBLE | WS_BORDER | SS_LEFTNOWORDWRAP | WS_GROUP, r1, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc1);

	// CONTROL "Follow-mode", IDC_FOLLOW, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|BS_PUSHLIKE|WS_TABSTOP, 72, 0, 52, 13
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(72, 0), CSize(52, 13));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Follow-mode"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | BS_PUSHLIKE | WS_TABSTOP, r2, parent, IDC_FOLLOW);
	mfcToQtWidget->insert(IDC_FOLLOW, mfc2);

	// CONTROL "Row highlight, 1st", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_LEFTNOWORDWRAP|WS_GROUP, 129, 1, 58, 8
	CStatic *mfc3 = new CStatic(parent);
	CRect r3(CPoint(129, 1), CSize(58, 8));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Row highlight, 1st"), WS_VISIBLE | WS_BORDER | SS_LEFTNOWORDWRAP | WS_GROUP, r3, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc3);

	// EDITTEXT IDC_HIGHLIGHT1,191,0,27,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER
	CEdit *mfc4 = new CEdit(parent);
	CRect r4(CPoint(191, 0), CSize(27, 12));
	parent->MapDialogRect(&r4);
	mfc4->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER, r4, parent, IDC_HIGHLIGHT1);
	mfcToQtWidget->insert(IDC_HIGHLIGHT1, mfc4);

	// CONTROL "", IDC_HIGHLIGHTSPIN1, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS|UDS_HOTTRACK, 213, 2, 11, 6
	CSpinButtonCtrl *mfc5 = new CSpinButtonCtrl(parent);
	CRect r5(CPoint(213, 2), CSize(11, 6));
	parent->MapDialogRect(&r5);
	mfc5->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS | UDS_HOTTRACK, r5, parent, IDC_HIGHLIGHTSPIN1);
	mfcToQtWidget->insert(IDC_HIGHLIGHTSPIN1, mfc5);

	// CONTROL "2nd", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_LEFTNOWORDWRAP|WS_GROUP, 225, 1, 13, 8
	CStatic *mfc6 = new CStatic(parent);
	CRect r6(CPoint(225, 1), CSize(13, 8));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("2nd"), WS_VISIBLE | WS_BORDER | SS_LEFTNOWORDWRAP | WS_GROUP, r6, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc6);

	// EDITTEXT IDC_HIGHLIGHT2,241,0,27,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER
	CEdit *mfc7 = new CEdit(parent);
	CRect r7(CPoint(241, 0), CSize(27, 12));
	parent->MapDialogRect(&r7);
	mfc7->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER, r7, parent, IDC_HIGHLIGHT2);
	mfcToQtWidget->insert(IDC_HIGHLIGHT2, mfc7);

	// CONTROL "", IDC_HIGHLIGHTSPIN2, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS|UDS_HOTTRACK, 263, 2, 11, 6
	CSpinButtonCtrl *mfc8 = new CSpinButtonCtrl(parent);
	CRect r8(CPoint(263, 2), CSize(11, 6));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS | UDS_HOTTRACK, r8, parent, IDC_HIGHLIGHTSPIN2);
	mfcToQtWidget->insert(IDC_HIGHLIGHTSPIN2, mfc8);

	// END
}

void qtMfcInitDialogResource_IDD_EXPORT(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_EXPORT DIALOGEX 0, 0, 247, 283
	CRect rect(CPoint(0, 0), CSize(247, 283));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Export file"
	parent->SetWindowText("Export file");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "NSF file options",IDC_STATIC,7,7,173,75
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(173, 75));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("NSF file options"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Progress",IDC_STATIC,7,120,233,156
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 120), CSize(233, 156));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Progress"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Type of file",IDC_STATIC,7,87,233,29
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(7, 87), CSize(233, 29));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Type of file"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// DEFPUSHBUTTON "&Export",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,187,7,53,14
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(187, 7), CSize(53, 14));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("&Export"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r3, parent, IDC_EXPORT);
	mfcToQtWidget->insert(IDC_EXPORT, mfc3);

	// PUSHBUTTON "&Close",IDC_CLOSE,187,23,53,14,WS_VISIBLE|WS_BORDER
	CButton *mfc4 = new CButton(parent);
	CRect r4(CPoint(187, 23), CSize(53, 14));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("&Close"), WS_VISIBLE | WS_BORDER, r4, parent, IDC_CLOSE);
	mfcToQtWidget->insert(IDC_CLOSE, mfc4);

	// EDITTEXT IDC_NAME,60,18,114,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc5 = new CEdit(parent);
	CRect r5(CPoint(60, 18), CSize(114, 13));
	parent->MapDialogRect(&r5);
	mfc5->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r5, parent, IDC_NAME);
	mfcToQtWidget->insert(IDC_NAME, mfc5);

	// EDITTEXT IDC_ARTIST,60,33,114,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc6 = new CEdit(parent);
	CRect r6(CPoint(60, 33), CSize(114, 13));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r6, parent, IDC_ARTIST);
	mfcToQtWidget->insert(IDC_ARTIST, mfc6);

	// EDITTEXT IDC_COPYRIGHT,60,49,114,13,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc7 = new CEdit(parent);
	CRect r7(CPoint(60, 49), CSize(114, 13));
	parent->MapDialogRect(&r7);
	mfc7->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r7, parent, IDC_COPYRIGHT);
	mfcToQtWidget->insert(IDC_COPYRIGHT, mfc7);

	// CONTROL "NTSC", IDC_NTSC, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 16, 67, 33, 10
	CButton *mfc8 = new CButton(parent);
	CRect r8(CPoint(16, 67), CSize(33, 10));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("NTSC"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r8, parent, IDC_NTSC);
	mfcToQtWidget->insert(IDC_NTSC, mfc8);

	// CONTROL "PAL", IDC_PAL, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 54, 67, 28, 10
	CButton *mfc9 = new CButton(parent);
	CRect r9(CPoint(54, 67), CSize(28, 10));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("PAL"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r9, parent, IDC_PAL);
	mfcToQtWidget->insert(IDC_PAL, mfc9);

	// CONTROL "Dual", IDC_DUAL, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 88, 67, 30, 10
	CButton *mfc10 = new CButton(parent);
	CRect r10(CPoint(88, 67), CSize(30, 10));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("Dual"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r10, parent, IDC_DUAL);
	mfcToQtWidget->insert(IDC_DUAL, mfc10);

	// COMBOBOX IDC_TYPE,16,97,218,100,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc11 = new CComboBox(parent);
	CRect r11(CPoint(16, 97), CSize(218, 100));
	parent->MapDialogRect(&r11);
	mfc11->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r11, parent, IDC_TYPE);
	mfcToQtWidget->insert(IDC_TYPE, mfc11);

	// LTEXT "Name",IDC_STATIC,16,20,38,11
	CStatic *mfc13 = new CStatic(parent);
	CRect r13(CPoint(16, 20), CSize(38, 11));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("Name"), WS_VISIBLE | WS_BORDER, r13, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Artist",IDC_STATIC,16,35,38,11
	CStatic *mfc14 = new CStatic(parent);
	CRect r14(CPoint(16, 35), CSize(38, 11));
	parent->MapDialogRect(&r14);
	mfc14->Create(_T("Artist"), WS_VISIBLE | WS_BORDER, r14, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Copyright",IDC_STATIC,16,51,38,11
	CStatic *mfc15 = new CStatic(parent);
	CRect r15(CPoint(16, 51), CSize(38, 11));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T("Copyright"), WS_VISIBLE | WS_BORDER, r15, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_OUTPUT,16,132,218,139,WS_VISIBLE|ES_MULTILINE|ES_AUTOHSCROLL|ES_READONLY|WS_VSCROLL
	CEdit *mfc17 = new CEdit(parent);
	CRect r17(CPoint(16, 132), CSize(218, 139));
	parent->MapDialogRect(&r17);
	mfc17->Create(WS_VISIBLE | ES_MULTILINE | ES_AUTOHSCROLL | ES_READONLY | WS_VSCROLL, r17, parent, IDC_OUTPUT);
	mfcToQtWidget->insert(IDC_OUTPUT, mfc17);

	// PUSHBUTTON "&Play",IDC_PLAY,187,68,53,14,WS_BORDER
	CButton *mfc19 = new CButton(parent);
	CRect r19(CPoint(187, 68), CSize(53, 14));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T("&Play"), WS_BORDER, r19, parent, IDC_PLAY);
	mfcToQtWidget->insert(IDC_PLAY, mfc19);

	// END
}

void qtMfcInitDialogResource_IDD_INSTRUMENT_VRC7(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_INSTRUMENT_VRC7 DIALOGEX 0, 0, 372, 172
	CRect rect(CPoint(0, 0), CSize(372, 172));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// GROUPBOX "Patch",IDC_STATIC,7,7,310,30
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(310, 30));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Patch"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Modulator settings",IDC_STATIC,7,42,153,123
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 42), CSize(153, 123));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Modulator settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Carrier settings",IDC_STATIC,166,42,152,123
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(166, 42), CSize(152, 123));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Carrier settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_PATCH,15,18,295,128,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc4 = new CComboBox(parent);
	CRect r4(CPoint(15, 18), CSize(295, 128));
	parent->MapDialogRect(&r4);
	mfc4->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r4, parent, IDC_PATCH);
	mfcToQtWidget->insert(IDC_PATCH, mfc4);

	// PUSHBUTTON "Copy",IDC_COPY,322,7,43,14,WS_VISIBLE|WS_BORDER
	CButton *mfc5 = new CButton(parent);
	CRect r5(CPoint(322, 7), CSize(43, 14));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Copy"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_COPY);
	mfcToQtWidget->insert(IDC_COPY, mfc5);

	// PUSHBUTTON "Paste",IDC_PASTE,322,23,43,14,WS_VISIBLE|WS_BORDER
	CButton *mfc6 = new CButton(parent);
	CRect r6(CPoint(322, 23), CSize(43, 14));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Paste"), WS_VISIBLE | WS_BORDER, r6, parent, IDC_PASTE);
	mfcToQtWidget->insert(IDC_PASTE, mfc6);

	// CONTROL "Amplitude modulation", IDC_M_AM, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 14, 54, 84, 10
	CButton *mfc8 = new CButton(parent);
	CRect r8(CPoint(14, 54), CSize(84, 10));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("Amplitude modulation"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r8, parent, IDC_M_AM);
	mfcToQtWidget->insert(IDC_M_AM, mfc8);

	// CONTROL "Vibrato", IDC_M_VIB, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 109, 54, 39, 10
	CButton *mfc9 = new CButton(parent);
	CRect r9(CPoint(109, 54), CSize(39, 10));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("Vibrato"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r9, parent, IDC_M_VIB);
	mfcToQtWidget->insert(IDC_M_VIB, mfc9);

	// CONTROL "Sustained", IDC_M_EG, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 14, 70, 47, 10
	CButton *mfc10 = new CButton(parent);
	CRect r10(CPoint(14, 70), CSize(47, 10));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("Sustained"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r10, parent, IDC_M_EG);
	mfcToQtWidget->insert(IDC_M_EG, mfc10);

	// CONTROL "Key scaling", IDC_M_KSR2, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 14, 86, 51, 10
	CButton *mfc11 = new CButton(parent);
	CRect r11(CPoint(14, 86), CSize(51, 10));
	parent->MapDialogRect(&r11);
	mfc11->Create(_T("Key scaling"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r11, parent, IDC_M_KSR2);
	mfcToQtWidget->insert(IDC_M_KSR2, mfc11);

	// CONTROL "Wave rectification", IDC_M_DM, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 74, 70, 74, 10
	CButton *mfc12 = new CButton(parent);
	CRect r12(CPoint(74, 70), CSize(74, 10));
	parent->MapDialogRect(&r12);
	mfc12->Create(_T("Wave rectification"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r12, parent, IDC_M_DM);
	mfcToQtWidget->insert(IDC_M_DM, mfc12);

	// LTEXT "Level",IDC_STATIC,69,87,18,8
	CStatic *mfc13 = new CStatic(parent);
	CRect r13(CPoint(69, 87), CSize(18, 8));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("Level"), WS_VISIBLE | WS_BORDER, r13, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_M_KSL, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 90, 86, 58, 11
	CSliderCtrl *mfc14 = new CSliderCtrl(parent);
	CRect r14(CPoint(90, 86), CSize(58, 11));
	parent->MapDialogRect(&r14);
	mfc14->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r14, parent, IDC_M_KSL);
	mfcToQtWidget->insert(IDC_M_KSL, mfc14);

	// LTEXT "Mult. factor",IDC_STATIC,14,108,38,8
	CStatic *mfc15 = new CStatic(parent);
	CRect r15(CPoint(14, 108), CSize(38, 8));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T("Mult. factor"), WS_VISIBLE | WS_BORDER, r15, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_M_MUL, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 51, 107, 105, 11
	CSliderCtrl *mfc16 = new CSliderCtrl(parent);
	CRect r16(CPoint(51, 107), CSize(105, 11));
	parent->MapDialogRect(&r16);
	mfc16->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r16, parent, IDC_M_MUL);
	mfcToQtWidget->insert(IDC_M_MUL, mfc16);

	// LTEXT "Attack",IDC_STATIC,14,127,22,8
	CStatic *mfc17 = new CStatic(parent);
	CRect r17(CPoint(14, 127), CSize(22, 8));
	parent->MapDialogRect(&r17);
	mfc17->Create(_T("Attack"), WS_VISIBLE | WS_BORDER, r17, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_M_AR, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 40, 126, 42, 11
	CSliderCtrl *mfc18 = new CSliderCtrl(parent);
	CRect r18(CPoint(40, 126), CSize(42, 11));
	parent->MapDialogRect(&r18);
	mfc18->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r18, parent, IDC_M_AR);
	mfcToQtWidget->insert(IDC_M_AR, mfc18);

	// LTEXT "Decay",IDC_STATIC,87,127,21,8
	CStatic *mfc19 = new CStatic(parent);
	CRect r19(CPoint(87, 127), CSize(21, 8));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T("Decay"), WS_VISIBLE | WS_BORDER, r19, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_M_DR, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 114, 126, 42, 11
	CSliderCtrl *mfc20 = new CSliderCtrl(parent);
	CRect r20(CPoint(114, 126), CSize(42, 11));
	parent->MapDialogRect(&r20);
	mfc20->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r20, parent, IDC_M_DR);
	mfcToQtWidget->insert(IDC_M_DR, mfc20);

	// LTEXT "Sustain",IDC_STATIC,14,144,24,8
	CStatic *mfc21 = new CStatic(parent);
	CRect r21(CPoint(14, 144), CSize(24, 8));
	parent->MapDialogRect(&r21);
	mfc21->Create(_T("Sustain"), WS_VISIBLE | WS_BORDER, r21, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_M_SL, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 39, 143, 42, 11
	CSliderCtrl *mfc22 = new CSliderCtrl(parent);
	CRect r22(CPoint(39, 143), CSize(42, 11));
	parent->MapDialogRect(&r22);
	mfc22->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r22, parent, IDC_M_SL);
	mfcToQtWidget->insert(IDC_M_SL, mfc22);

	// LTEXT "Release",IDC_STATIC,85,144,26,8
	CStatic *mfc23 = new CStatic(parent);
	CRect r23(CPoint(85, 144), CSize(26, 8));
	parent->MapDialogRect(&r23);
	mfc23->Create(_T("Release"), WS_VISIBLE | WS_BORDER, r23, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_M_RR, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 114, 143, 42, 11
	CSliderCtrl *mfc24 = new CSliderCtrl(parent);
	CRect r24(CPoint(114, 143), CSize(42, 11));
	parent->MapDialogRect(&r24);
	mfc24->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r24, parent, IDC_M_RR);
	mfcToQtWidget->insert(IDC_M_RR, mfc24);

	// CONTROL "Amplitude modulation", IDC_C_AM, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 171, 54, 84, 10
	CButton *mfc26 = new CButton(parent);
	CRect r26(CPoint(171, 54), CSize(84, 10));
	parent->MapDialogRect(&r26);
	mfc26->Create(_T("Amplitude modulation"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r26, parent, IDC_C_AM);
	mfcToQtWidget->insert(IDC_C_AM, mfc26);

	// CONTROL "Vibrato", IDC_C_VIB, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 267, 54, 39, 10
	CButton *mfc27 = new CButton(parent);
	CRect r27(CPoint(267, 54), CSize(39, 10));
	parent->MapDialogRect(&r27);
	mfc27->Create(_T("Vibrato"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r27, parent, IDC_C_VIB);
	mfcToQtWidget->insert(IDC_C_VIB, mfc27);

	// CONTROL "Sustained", IDC_C_EG, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 171, 70, 47, 10
	CButton *mfc28 = new CButton(parent);
	CRect r28(CPoint(171, 70), CSize(47, 10));
	parent->MapDialogRect(&r28);
	mfc28->Create(_T("Sustained"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r28, parent, IDC_C_EG);
	mfcToQtWidget->insert(IDC_C_EG, mfc28);

	// CONTROL "Key scaling", IDC_C_KSR, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 171, 86, 51, 10
	CButton *mfc29 = new CButton(parent);
	CRect r29(CPoint(171, 86), CSize(51, 10));
	parent->MapDialogRect(&r29);
	mfc29->Create(_T("Key scaling"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r29, parent, IDC_C_KSR);
	mfcToQtWidget->insert(IDC_C_KSR, mfc29);

	// CONTROL "Wave rectification", IDC_C_DM, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 232, 70, 74, 10
	CButton *mfc30 = new CButton(parent);
	CRect r30(CPoint(232, 70), CSize(74, 10));
	parent->MapDialogRect(&r30);
	mfc30->Create(_T("Wave rectification"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r30, parent, IDC_C_DM);
	mfcToQtWidget->insert(IDC_C_DM, mfc30);

	// LTEXT "Level",IDC_STATIC,226,87,18,8
	CStatic *mfc31 = new CStatic(parent);
	CRect r31(CPoint(226, 87), CSize(18, 8));
	parent->MapDialogRect(&r31);
	mfc31->Create(_T("Level"), WS_VISIBLE | WS_BORDER, r31, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_C_KSL, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 247, 86, 59, 11
	CSliderCtrl *mfc32 = new CSliderCtrl(parent);
	CRect r32(CPoint(247, 86), CSize(59, 11));
	parent->MapDialogRect(&r32);
	mfc32->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r32, parent, IDC_C_KSL);
	mfcToQtWidget->insert(IDC_C_KSL, mfc32);

	// LTEXT "Mult. factor",IDC_STATIC,171,108,38,8
	CStatic *mfc33 = new CStatic(parent);
	CRect r33(CPoint(171, 108), CSize(38, 8));
	parent->MapDialogRect(&r33);
	mfc33->Create(_T("Mult. factor"), WS_VISIBLE | WS_BORDER, r33, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_C_MUL, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 208, 107, 106, 11
	CSliderCtrl *mfc34 = new CSliderCtrl(parent);
	CRect r34(CPoint(208, 107), CSize(106, 11));
	parent->MapDialogRect(&r34);
	mfc34->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r34, parent, IDC_C_MUL);
	mfcToQtWidget->insert(IDC_C_MUL, mfc34);

	// LTEXT "Attack",IDC_STATIC,171,127,22,8
	CStatic *mfc35 = new CStatic(parent);
	CRect r35(CPoint(171, 127), CSize(22, 8));
	parent->MapDialogRect(&r35);
	mfc35->Create(_T("Attack"), WS_VISIBLE | WS_BORDER, r35, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_C_AR, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 199, 126, 42, 11
	CSliderCtrl *mfc36 = new CSliderCtrl(parent);
	CRect r36(CPoint(199, 126), CSize(42, 11));
	parent->MapDialogRect(&r36);
	mfc36->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r36, parent, IDC_C_AR);
	mfcToQtWidget->insert(IDC_C_AR, mfc36);

	// LTEXT "Decay",IDC_STATIC,247,127,21,8
	CStatic *mfc37 = new CStatic(parent);
	CRect r37(CPoint(247, 127), CSize(21, 8));
	parent->MapDialogRect(&r37);
	mfc37->Create(_T("Decay"), WS_VISIBLE | WS_BORDER, r37, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_C_DR, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 271, 126, 43, 11
	CSliderCtrl *mfc38 = new CSliderCtrl(parent);
	CRect r38(CPoint(271, 126), CSize(43, 11));
	parent->MapDialogRect(&r38);
	mfc38->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r38, parent, IDC_C_DR);
	mfcToQtWidget->insert(IDC_C_DR, mfc38);

	// LTEXT "Sustain",IDC_STATIC,171,144,24,8
	CStatic *mfc39 = new CStatic(parent);
	CRect r39(CPoint(171, 144), CSize(24, 8));
	parent->MapDialogRect(&r39);
	mfc39->Create(_T("Sustain"), WS_VISIBLE | WS_BORDER, r39, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_C_SL, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 199, 143, 42, 11
	CSliderCtrl *mfc40 = new CSliderCtrl(parent);
	CRect r40(CPoint(199, 143), CSize(42, 11));
	parent->MapDialogRect(&r40);
	mfc40->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r40, parent, IDC_C_SL);
	mfcToQtWidget->insert(IDC_C_SL, mfc40);

	// LTEXT "Release",IDC_STATIC,245,144,26,8
	CStatic *mfc41 = new CStatic(parent);
	CRect r41(CPoint(245, 144), CSize(26, 8));
	parent->MapDialogRect(&r41);
	mfc41->Create(_T("Release"), WS_VISIBLE | WS_BORDER, r41, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_C_RR, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 271, 143, 43, 11
	CSliderCtrl *mfc42 = new CSliderCtrl(parent);
	CRect r42(CPoint(271, 143), CSize(43, 11));
	parent->MapDialogRect(&r42);
	mfc42->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | WS_TABSTOP, r42, parent, IDC_C_RR);
	mfcToQtWidget->insert(IDC_C_RR, mfc42);

	// CTEXT "Modulator\nlevel",IDC_STATIC,322,42,36,17
	CStatic *mfc43 = new CStatic(parent);
	CRect r43(CPoint(322, 42), CSize(36, 17));
	parent->MapDialogRect(&r43);
	mfc43->Create(_T("Modulator\nlevel"), WS_VISIBLE | WS_BORDER, r43, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_TL, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_VERT|TBS_BOTH|TBS_NOTICKS|WS_TABSTOP, 329, 59, 16, 53
	CSliderCtrl *mfc44 = new CSliderCtrl(parent);
	CRect r44(CPoint(329, 59), CSize(16, 53));
	parent->MapDialogRect(&r44);
	mfc44->Create(WS_VISIBLE | WS_BORDER | TBS_VERT | TBS_BOTH | TBS_NOTICKS | WS_TABSTOP, r44, parent, IDC_TL);
	mfcToQtWidget->insert(IDC_TL, mfc44);

	// CTEXT "Feedback",IDC_STATIC,322,112,36,9
	CStatic *mfc45 = new CStatic(parent);
	CRect r45(CPoint(322, 112), CSize(36, 9));
	parent->MapDialogRect(&r45);
	mfc45->Create(_T("Feedback"), WS_VISIBLE | WS_BORDER, r45, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_FB, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 325, 124, 25, 41
	CSliderCtrl *mfc46 = new CSliderCtrl(parent);
	CRect r46(CPoint(325, 124), CSize(25, 41));
	parent->MapDialogRect(&r46);
	mfc46->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r46, parent, IDC_FB);
	mfcToQtWidget->insert(IDC_FB, mfc46);

	// END
}

void qtMfcInitDialogResource_IDD_CREATEWAV(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CREATEWAV DIALOGEX 0, 0, 151, 208
	CRect rect(CPoint(0, 0), CSize(151, 208));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Create wave file"
	parent->SetWindowText("Create wave file");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Song length",IDC_STATIC,7,7,137,47
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(137, 47));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Song length"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Channels",IDC_STATIC,7,96,137,87
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 96), CSize(137, 87));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Channels"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Song",IDC_STATIC,7,60,137,30
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(7, 60), CSize(137, 30));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Song"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// DEFPUSHBUTTON "Begin",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,37,187,52,14
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(37, 187), CSize(52, 14));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Begin"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r3, parent, IDC_BEGIN);
	mfcToQtWidget->insert(IDC_BEGIN, mfc3);

	// PUSHBUTTON "Cancel",IDCANCEL,92,187,52,14,WS_VISIBLE|WS_BORDER
	CButton *mfc4 = new CButton(parent);
	CRect r4(CPoint(92, 187), CSize(52, 14));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("Cancel"), WS_VISIBLE | WS_BORDER, r4, parent, IDCANCEL);
	mfcToQtWidget->insert(IDCANCEL, mfc4);

	// CONTROL "Play the song", IDC_RADIO_LOOP, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 14, 20, 59, 10
	CButton *mfc6 = new CButton(parent);
	CRect r6(CPoint(14, 20), CSize(59, 10));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Play the song"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r6, parent, IDC_RADIO_LOOP);
	mfcToQtWidget->insert(IDC_RADIO_LOOP, mfc6);

	// CONTROL "Play for", IDC_RADIO_TIME, "Button", WS_VISIBLE|WS_BORDER|BS_AUTORADIOBUTTON, 14, 38, 41, 10
	CButton *mfc7 = new CButton(parent);
	CRect r7(CPoint(14, 38), CSize(41, 10));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("Play for"), WS_VISIBLE | WS_BORDER | BS_AUTORADIOBUTTON, r7, parent, IDC_RADIO_TIME);
	mfcToQtWidget->insert(IDC_RADIO_TIME, mfc7);

	// EDITTEXT IDC_TIMES,73,19,36,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc8 = new CEdit(parent);
	CRect r8(CPoint(73, 19), CSize(36, 12));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r8, parent, IDC_TIMES);
	mfcToQtWidget->insert(IDC_TIMES, mfc8);

	// CONTROL "", IDC_SPIN_LOOP, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 105, 17, 11, 17
	CSpinButtonCtrl *mfc9 = new CSpinButtonCtrl(parent);
	CRect r9(CPoint(105, 17), CSize(11, 17));
	parent->MapDialogRect(&r9);
	mfc9->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r9, parent, IDC_SPIN_LOOP);
	mfcToQtWidget->insert(IDC_SPIN_LOOP, mfc9);

	// LTEXT "time(s)",IDC_STATIC,115,20,21,10
	CStatic *mfc10 = new CStatic(parent);
	CRect r10(CPoint(115, 20), CSize(21, 10));
	parent->MapDialogRect(&r10);
	mfc10->Create(_T("time(s)"), WS_VISIBLE | WS_BORDER | SS_CENTERIMAGE, r10, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_SECONDS,53,37,44,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc11 = new CEdit(parent);
	CRect r11(CPoint(53, 37), CSize(44, 12));
	parent->MapDialogRect(&r11);
	mfc11->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r11, parent, IDC_SECONDS);
	mfcToQtWidget->insert(IDC_SECONDS, mfc11);

	// CONTROL "", IDC_SPIN_TIME, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 93, 36, 11, 14
	CSpinButtonCtrl *mfc12 = new CSpinButtonCtrl(parent);
	CRect r12(CPoint(93, 36), CSize(11, 14));
	parent->MapDialogRect(&r12);
	mfc12->Create(WS_VISIBLE | WS_BORDER | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r12, parent, IDC_SPIN_TIME);
	mfcToQtWidget->insert(IDC_SPIN_TIME, mfc12);

	// LTEXT "mm:ss",IDC_STATIC,106,38,21,10
	CStatic *mfc13 = new CStatic(parent);
	CRect r13(CPoint(106, 38), CSize(21, 10));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("mm:ss"), WS_VISIBLE | WS_BORDER | SS_CENTERIMAGE, r13, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LISTBOX IDC_CHANNELS,14,107,124,70,WS_VISIBLE|WS_BORDER|LBS_OWNERDRAWFIXED|LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT|WS_VSCROLL|WS_TABSTOP
	CListBox *mfc15 = new CListBox(parent);
	CRect r15(CPoint(14, 107), CSize(124, 70));
	parent->MapDialogRect(&r15);
	mfc15->Create(WS_VISIBLE | WS_BORDER | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_TABSTOP, r15, parent, IDC_CHANNELS);
	mfcToQtWidget->insert(IDC_CHANNELS, mfc15);

	// COMBOBOX IDC_TRACKS,14,72,124,30,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|CBS_SORT|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc17 = new CComboBox(parent);
	CRect r17(CPoint(14, 72), CSize(124, 30));
	parent->MapDialogRect(&r17);
	mfc17->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | CBS_SORT | WS_VSCROLL | WS_TABSTOP, r17, parent, IDC_TRACKS);
	mfcToQtWidget->insert(IDC_TRACKS, mfc17);

	// END
}

void qtMfcInitDialogResource_IDD_MAINBAR(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_MAINBAR DIALOGEX 0, 0, 111, 128
	CRect rect(CPoint(0, 0), CSize(111, 128));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// END
}

void qtMfcInitDialogResource_IDD_INSTRUMENT_FDS(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_INSTRUMENT_FDS DIALOGEX 0, 0, 372, 172
	CRect rect(CPoint(0, 0), CSize(372, 172));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// GROUPBOX "Wave editor",IDC_STATIC,7,7,228,111
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(228, 111));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Wave editor"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Frequency modulation",IDC_STATIC,240,7,124,79
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(240, 7), CSize(124, 79));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Frequency modulation"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// PUSHBUTTON "Sine",IDC_PRESET_SINE,14,101,41,12,WS_VISIBLE|WS_BORDER
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(14, 101), CSize(41, 12));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Sine"), WS_VISIBLE | WS_BORDER, r3, parent, IDC_PRESET_SINE);
	mfcToQtWidget->insert(IDC_PRESET_SINE, mfc3);

	// PUSHBUTTON "Triangle",IDC_PRESET_TRIANGLE,57,101,41,12,WS_VISIBLE|WS_BORDER
	CButton *mfc4 = new CButton(parent);
	CRect r4(CPoint(57, 101), CSize(41, 12));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("Triangle"), WS_VISIBLE | WS_BORDER, r4, parent, IDC_PRESET_TRIANGLE);
	mfcToQtWidget->insert(IDC_PRESET_TRIANGLE, mfc4);

	// PUSHBUTTON "Sawtooth",IDC_PRESET_SAWTOOTH,100,101,41,12,WS_VISIBLE|WS_BORDER
	CButton *mfc5 = new CButton(parent);
	CRect r5(CPoint(100, 101), CSize(41, 12));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Sawtooth"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_PRESET_SAWTOOTH);
	mfcToQtWidget->insert(IDC_PRESET_SAWTOOTH, mfc5);

	// LTEXT "Modulation rate",IDC_STATIC,246,24,51,8
	CStatic *mfc6 = new CStatic(parent);
	CRect r6(CPoint(246, 24), CSize(51, 8));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Modulation rate"), WS_VISIBLE | WS_BORDER, r6, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_MOD_RATE,318,22,37,14,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER
	CEdit *mfc7 = new CEdit(parent);
	CRect r7(CPoint(318, 22), CSize(37, 14));
	parent->MapDialogRect(&r7);
	mfc7->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER, r7, parent, IDC_MOD_RATE);
	mfcToQtWidget->insert(IDC_MOD_RATE, mfc7);

	// CONTROL "", IDC_MOD_RATE_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS|UDS_NOTHOUSANDS, 344, 25, 11, 14
	CSpinButtonCtrl *mfc8 = new CSpinButtonCtrl(parent);
	CRect r8(CPoint(344, 25), CSize(11, 14));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS | UDS_NOTHOUSANDS, r8, parent, IDC_MOD_RATE_SPIN);
	mfcToQtWidget->insert(IDC_MOD_RATE_SPIN, mfc8);

	// LTEXT "Modulation depth",IDC_STATIC,246,46,56,8
	CStatic *mfc9 = new CStatic(parent);
	CRect r9(CPoint(246, 46), CSize(56, 8));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("Modulation depth"), WS_VISIBLE | WS_BORDER, r9, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_MOD_DEPTH,318,43,37,14,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER
	CEdit *mfc10 = new CEdit(parent);
	CRect r10(CPoint(318, 43), CSize(37, 14));
	parent->MapDialogRect(&r10);
	mfc10->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER, r10, parent, IDC_MOD_DEPTH);
	mfcToQtWidget->insert(IDC_MOD_DEPTH, mfc10);

	// CONTROL "", IDC_MOD_DEPTH_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 344, 43, 11, 14
	CSpinButtonCtrl *mfc11 = new CSpinButtonCtrl(parent);
	CRect r11(CPoint(344, 43), CSize(11, 14));
	parent->MapDialogRect(&r11);
	mfc11->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r11, parent, IDC_MOD_DEPTH_SPIN);
	mfcToQtWidget->insert(IDC_MOD_DEPTH_SPIN, mfc11);

	// LTEXT "Modulation delay",IDC_STATIC,246,68,55,8
	CStatic *mfc12 = new CStatic(parent);
	CRect r12(CPoint(246, 68), CSize(55, 8));
	parent->MapDialogRect(&r12);
	mfc12->Create(_T("Modulation delay"), WS_VISIBLE | WS_BORDER, r12, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_MOD_DELAY,318,65,37,14,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_NUMBER
	CEdit *mfc13 = new CEdit(parent);
	CRect r13(CPoint(318, 65), CSize(37, 14));
	parent->MapDialogRect(&r13);
	mfc13->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER, r13, parent, IDC_MOD_DELAY);
	mfcToQtWidget->insert(IDC_MOD_DELAY, mfc13);

	// CONTROL "", IDC_MOD_DELAY_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 344, 63, 11, 14
	CSpinButtonCtrl *mfc14 = new CSpinButtonCtrl(parent);
	CRect r14(CPoint(344, 63), CSize(11, 14));
	parent->MapDialogRect(&r14);
	mfc14->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r14, parent, IDC_MOD_DELAY_SPIN);
	mfcToQtWidget->insert(IDC_MOD_DELAY_SPIN, mfc14);

	// PUSHBUTTON "Flat",IDC_MOD_PRESET_FLAT,318,131,46,12,WS_VISIBLE|WS_BORDER
	CButton *mfc15 = new CButton(parent);
	CRect r15(CPoint(318, 131), CSize(46, 12));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T("Flat"), WS_VISIBLE | WS_BORDER, r15, parent, IDC_MOD_PRESET_FLAT);
	mfcToQtWidget->insert(IDC_MOD_PRESET_FLAT, mfc15);

	// PUSHBUTTON "Sine",IDC_MOD_PRESET_SINE,318,148,46,12,WS_VISIBLE|WS_BORDER
	CButton *mfc16 = new CButton(parent);
	CRect r16(CPoint(318, 148), CSize(46, 12));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T("Sine"), WS_VISIBLE | WS_BORDER, r16, parent, IDC_MOD_PRESET_SINE);
	mfcToQtWidget->insert(IDC_MOD_PRESET_SINE, mfc16);

	// PUSHBUTTON "Copy wave",IDC_COPY_WAVE,240,90,52,14,WS_VISIBLE|WS_BORDER
	CButton *mfc18 = new CButton(parent);
	CRect r18(CPoint(240, 90), CSize(52, 14));
	parent->MapDialogRect(&r18);
	mfc18->Create(_T("Copy wave"), WS_VISIBLE | WS_BORDER, r18, parent, IDC_COPY_WAVE);
	mfcToQtWidget->insert(IDC_COPY_WAVE, mfc18);

	// PUSHBUTTON "Paste wave",IDC_PASTE_WAVE,240,104,52,14,WS_VISIBLE|WS_BORDER
	CButton *mfc19 = new CButton(parent);
	CRect r19(CPoint(240, 104), CSize(52, 14));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T("Paste wave"), WS_VISIBLE | WS_BORDER, r19, parent, IDC_PASTE_WAVE);
	mfcToQtWidget->insert(IDC_PASTE_WAVE, mfc19);

	// PUSHBUTTON "Copy table",IDC_COPY_TABLE,305,90,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc20 = new CButton(parent);
	CRect r20(CPoint(305, 90), CSize(50, 14));
	parent->MapDialogRect(&r20);
	mfc20->Create(_T("Copy table"), WS_VISIBLE | WS_BORDER, r20, parent, IDC_COPY_TABLE);
	mfcToQtWidget->insert(IDC_COPY_TABLE, mfc20);

	// PUSHBUTTON "Paste table",IDC_PASTE_TABLE,305,104,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc21 = new CButton(parent);
	CRect r21(CPoint(305, 104), CSize(50, 14));
	parent->MapDialogRect(&r21);
	mfc21->Create(_T("Paste table"), WS_VISIBLE | WS_BORDER, r21, parent, IDC_PASTE_TABLE);
	mfcToQtWidget->insert(IDC_PASTE_TABLE, mfc21);

	// PUSHBUTTON "50% pulse",IDC_PRESET_PULSE_50,143,101,41,12,WS_VISIBLE|WS_BORDER
	CButton *mfc22 = new CButton(parent);
	CRect r22(CPoint(143, 101), CSize(41, 12));
	parent->MapDialogRect(&r22);
	mfc22->Create(_T("50% pulse"), WS_VISIBLE | WS_BORDER, r22, parent, IDC_PRESET_PULSE_50);
	mfcToQtWidget->insert(IDC_PRESET_PULSE_50, mfc22);

	// PUSHBUTTON "25% pulse",IDC_PRESET_PULSE_25,186,101,41,12,WS_VISIBLE|WS_BORDER
	CButton *mfc23 = new CButton(parent);
	CRect r23(CPoint(186, 101), CSize(41, 12));
	parent->MapDialogRect(&r23);
	mfc23->Create(_T("25% pulse"), WS_VISIBLE | WS_BORDER, r23, parent, IDC_PRESET_PULSE_25);
	mfcToQtWidget->insert(IDC_PRESET_PULSE_25, mfc23);

	// END
}

void qtMfcInitDialogResource_IDD_FRAMECONTROLS(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_FRAMECONTROLS DIALOGEX 0, 0, 107, 12
	CRect rect(CPoint(0, 0), CSize(107, 12));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// STYLE DS_SETFONT|DS_FIXEDSYS|DS_CONTROL|WS_CHILD|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::WindowSystemMenuHint);

	// BEGIN
	// PUSHBUTTON "+",IDC_FRAME_INC,0,0,17,12,WS_VISIBLE|WS_BORDER
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(0, 0), CSize(17, 12));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("+"), WS_VISIBLE | WS_BORDER, r0, parent, IDC_FRAME_INC);
	mfcToQtWidget->insert(IDC_FRAME_INC, mfc0);

	// PUSHBUTTON "-",IDC_FRAME_DEC,23,0,17,12,WS_VISIBLE|WS_BORDER
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(23, 0), CSize(17, 12));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("-"), WS_VISIBLE | WS_BORDER, r1, parent, IDC_FRAME_DEC);
	mfcToQtWidget->insert(IDC_FRAME_DEC, mfc1);

	// CONTROL "Change all", IDC_CHANGE_ALL, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 51, 2, 56, 10
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(51, 2), CSize(56, 10));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Change all"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r2, parent, IDC_CHANGE_ALL);
	mfcToQtWidget->insert(IDC_CHANGE_ALL, mfc2);

	// END
}

void qtMfcInitDialogResource_IDD_INSTRUMENT_FDS_ENVELOPE(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_INSTRUMENT_FDS_ENVELOPE DIALOGEX 0, 0, 372, 172
	CRect rect(CPoint(0, 0), CSize(372, 172));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// BEGIN
	// EDITTEXT IDC_SEQUENCE_STRING,75,151,290,14,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc0 = new CEdit(parent);
	CRect r0(CPoint(75, 151), CSize(290, 14));
	parent->MapDialogRect(&r0);
	mfc0->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r0, parent, IDC_SEQUENCE_STRING);
	mfcToQtWidget->insert(IDC_SEQUENCE_STRING, mfc0);

	// COMBOBOX IDC_TYPE,8,151,63,30,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc1 = new CComboBox(parent);
	CRect r1(CPoint(8, 151), CSize(63, 30));
	parent->MapDialogRect(&r1);
	mfc1->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r1, parent, IDC_TYPE);
	mfcToQtWidget->insert(IDC_TYPE, mfc1);

	mfc1->AddString(_T("Volume"));

	mfc1->AddString(_T("Arpeggio"));

	mfc1->AddString(_T("Pitch"));

	// END
}

void qtMfcInitDialogResource_IDD_CHANNELS(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CHANNELS DIALOGEX 0, 0, 303, 236
	CRect rect(CPoint(0, 0), CSize(303, 236));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Channels"
	parent->SetWindowText("Channels");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Available channels",IDC_STATIC,7,7,138,197
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(138, 197));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Available channels"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Added channels",IDC_STATIC,151,7,145,197
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(151, 7), CSize(145, 197));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Added channels"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,194,215,50,14
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(194, 215), CSize(50, 14));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("OK"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r2, parent, IDOK);
	mfcToQtWidget->insert(IDOK, mfc2);

	// PUSHBUTTON "Cancel",IDCANCEL,246,215,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(246, 215), CSize(50, 14));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Cancel"), WS_VISIBLE | WS_BORDER, r3, parent, IDCANCEL);
	mfcToQtWidget->insert(IDCANCEL, mfc3);

	// PUSHBUTTON "Move up",IDC_MOVE_UP,7,215,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc4 = new CButton(parent);
	CRect r4(CPoint(7, 215), CSize(50, 14));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("Move up"), WS_VISIBLE | WS_BORDER, r4, parent, IDC_MOVE_UP);
	mfcToQtWidget->insert(IDC_MOVE_UP, mfc4);

	// PUSHBUTTON "Move down",IDC_MOVE_DOWN,62,215,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc5 = new CButton(parent);
	CRect r5(CPoint(62, 215), CSize(50, 14));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Move down"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_MOVE_DOWN);
	mfcToQtWidget->insert(IDC_MOVE_DOWN, mfc5);

	// CONTROL "", IDC_ADDED_LIST, "SysListView32", WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_ALIGNLEFT|LVS_NOCOLUMNHEADER|WS_BORDER|WS_TABSTOP, 159, 17, 129, 181
	CListCtrl *mfc6 = new CListCtrl(parent);
	CRect r6(CPoint(159, 17), CSize(129, 181));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | LVS_ALIGNLEFT | LVS_NOCOLUMNHEADER | WS_BORDER | WS_TABSTOP, r6, parent, IDC_ADDED_LIST);
	mfcToQtWidget->insert(IDC_ADDED_LIST, mfc6);

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDHORZ, 7, 209, 289, 1
	CStatic *mfc7 = new CStatic(parent);
	CRect r7(CPoint(7, 209), CSize(289, 1));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDHORZ, r7, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc7);

	// CONTROL "", IDC_AVAILABLE_TREE, "SysTreeView32", WS_VISIBLE|WS_BORDER|TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|WS_BORDER|WS_HSCROLL|WS_TABSTOP, 14, 17, 122, 181
	CTreeCtrl *mfc10 = new CTreeCtrl(parent);
	CRect r10(CPoint(14, 17), CSize(122, 181));
	parent->MapDialogRect(&r10);
	mfc10->Create(WS_VISIBLE | WS_BORDER | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | WS_BORDER | WS_HSCROLL | WS_TABSTOP, r10, parent, IDC_AVAILABLE_TREE);
	mfcToQtWidget->insert(IDC_AVAILABLE_TREE, mfc10);

	// END
}

void qtMfcInitDialogResource_IDD_HEADER(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_HEADER DIALOGEX 0, 0, 530, 21
	CRect rect(CPoint(0, 0), CSize(530, 21));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// STYLE DS_SETFONT|DS_FIXEDSYS|WS_CHILD|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::WindowSystemMenuHint);

	// BEGIN
	// END
}

void qtMfcInitDialogResource_IDD_COMMENTS(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_COMMENTS DIALOGEX 0, 0, 358, 230
	CRect rect(CPoint(0, 0), CSize(358, 230));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Module comments"
	parent->SetWindowText("Module comments");

	// STYLE DS_SETFONT|DS_FIXEDSYS|WS_MINIMIZEBOX|WS_MAXIMIZEBOX|WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// PUSHBUTTON "Cancel",IDCANCEL,304,211,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(304, 211), CSize(50, 14));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Cancel"), WS_VISIBLE | WS_BORDER, r0, parent, IDCANCEL);
	mfcToQtWidget->insert(IDCANCEL, mfc0);

	// EDITTEXT IDC_COMMENTS,0,0,358,206,WS_VISIBLE|WS_BORDER|ES_MULTILINE|ES_AUTOVSCROLL|ES_AUTOHSCROLL|ES_WANTRETURN|WS_VSCROLL|WS_HSCROLL
	CEdit *mfc1 = new CEdit(parent);
	CRect r1(CPoint(0, 0), CSize(358, 206));
	parent->MapDialogRect(&r1);
	mfc1->Create(WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL, r1, parent, IDC_COMMENTS);
	mfcToQtWidget->insert(IDC_COMMENTS, mfc1);

	// CONTROL "Show when loading file", IDC_SHOWONOPEN, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 5, 215, 89, 10
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(5, 215), CSize(89, 10));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Show when loading file"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r2, parent, IDC_SHOWONOPEN);
	mfcToQtWidget->insert(IDC_SHOWONOPEN, mfc2);

	// DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,248,211,50,14
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(248, 211), CSize(50, 14));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("OK"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r3, parent, IDOK);
	mfcToQtWidget->insert(IDOK, mfc3);

	// END
}

void qtMfcInitDialogResource_IDD_CONFIG_MIXER(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_CONFIG_MIXER DIALOGEX 0, 0, 280, 167
	CRect rect(CPoint(0, 0), CSize(280, 167));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Mixer"
	parent->SetWindowText("Mixer");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// CONTROL "", IDC_SLIDER_APU1, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 7, 30, 26, 114
	CSliderCtrl *mfc0 = new CSliderCtrl(parent);
	CRect r0(CPoint(7, 30), CSize(26, 114));
	parent->MapDialogRect(&r0);
	mfc0->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r0, parent, IDC_SLIDER_APU1);
	mfcToQtWidget->insert(IDC_SLIDER_APU1, mfc0);

	// CTEXT "APU1",IDC_STATIC,7,22,26,8
	CStatic *mfc1 = new CStatic(parent);
	CRect r1(CPoint(7, 22), CSize(26, 8));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("APU1"), WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_SLIDER_APU2, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 41, 30, 26, 114
	CSliderCtrl *mfc2 = new CSliderCtrl(parent);
	CRect r2(CPoint(41, 30), CSize(26, 114));
	parent->MapDialogRect(&r2);
	mfc2->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r2, parent, IDC_SLIDER_APU2);
	mfcToQtWidget->insert(IDC_SLIDER_APU2, mfc2);

	// CTEXT "APU2",IDC_STATIC,41,22,26,8
	CStatic *mfc3 = new CStatic(parent);
	CRect r3(CPoint(41, 22), CSize(26, 8));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("APU2"), WS_VISIBLE | WS_BORDER, r3, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_SLIDER_VRC6, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 75, 30, 26, 114
	CSliderCtrl *mfc4 = new CSliderCtrl(parent);
	CRect r4(CPoint(75, 30), CSize(26, 114));
	parent->MapDialogRect(&r4);
	mfc4->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r4, parent, IDC_SLIDER_VRC6);
	mfcToQtWidget->insert(IDC_SLIDER_VRC6, mfc4);

	// CTEXT "VRC6",IDC_STATIC,75,22,26,8
	CStatic *mfc5 = new CStatic(parent);
	CRect r5(CPoint(75, 22), CSize(26, 8));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("VRC6"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_SLIDER_VRC7, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 109, 30, 26, 114
	CSliderCtrl *mfc6 = new CSliderCtrl(parent);
	CRect r6(CPoint(109, 30), CSize(26, 114));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r6, parent, IDC_SLIDER_VRC7);
	mfcToQtWidget->insert(IDC_SLIDER_VRC7, mfc6);

	// CTEXT "VRC7",IDC_STATIC,109,22,26,8
	CStatic *mfc7 = new CStatic(parent);
	CRect r7(CPoint(109, 22), CSize(26, 8));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("VRC7"), WS_VISIBLE | WS_BORDER, r7, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_SLIDER_MMC5, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 143, 30, 26, 114
	CSliderCtrl *mfc8 = new CSliderCtrl(parent);
	CRect r8(CPoint(143, 30), CSize(26, 114));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r8, parent, IDC_SLIDER_MMC5);
	mfcToQtWidget->insert(IDC_SLIDER_MMC5, mfc8);

	// CTEXT "MMC5",IDC_STATIC,143,22,26,8
	CStatic *mfc9 = new CStatic(parent);
	CRect r9(CPoint(143, 22), CSize(26, 8));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("MMC5"), WS_VISIBLE | WS_BORDER, r9, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_SLIDER_FDS, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 177, 30, 26, 114
	CSliderCtrl *mfc10 = new CSliderCtrl(parent);
	CRect r10(CPoint(177, 30), CSize(26, 114));
	parent->MapDialogRect(&r10);
	mfc10->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r10, parent, IDC_SLIDER_FDS);
	mfcToQtWidget->insert(IDC_SLIDER_FDS, mfc10);

	// CTEXT "FDS",IDC_STATIC,177,22,26,8
	CStatic *mfc11 = new CStatic(parent);
	CRect r11(CPoint(177, 22), CSize(26, 8));
	parent->MapDialogRect(&r11);
	mfc11->Create(_T("FDS"), WS_VISIBLE | WS_BORDER, r11, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_SLIDER_N163, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_TABSTOP, 211, 30, 26, 114
	CSliderCtrl *mfc12 = new CSliderCtrl(parent);
	CRect r12(CPoint(211, 30), CSize(26, 114));
	parent->MapDialogRect(&r12);
	mfc12->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_TABSTOP, r12, parent, IDC_SLIDER_N163);
	mfcToQtWidget->insert(IDC_SLIDER_N163, mfc12);

	// CTEXT "N163",IDC_STATIC,211,22,26,8
	CStatic *mfc13 = new CStatic(parent);
	CRect r13(CPoint(211, 22), CSize(26, 8));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("N163"), WS_VISIBLE | WS_BORDER, r13, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_SLIDER_S5B, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|TBS_VERT|TBS_BOTH|WS_DISABLED|WS_TABSTOP, 245, 30, 26, 114
	CSliderCtrl *mfc14 = new CSliderCtrl(parent);
	CRect r14(CPoint(245, 30), CSize(26, 114));
	parent->MapDialogRect(&r14);
	mfc14->Create(WS_VISIBLE | WS_BORDER | TBS_AUTOTICKS | TBS_VERT | TBS_BOTH | WS_DISABLED | WS_TABSTOP, r14, parent, IDC_SLIDER_S5B);
	mfcToQtWidget->insert(IDC_SLIDER_S5B, mfc14);

	// CTEXT "S5B",IDC_STATIC,245,22,26,8
	CStatic *mfc15 = new CStatic(parent);
	CRect r15(CPoint(245, 22), CSize(26, 8));
	parent->MapDialogRect(&r15);
	mfc15->Create(_T("S5B"), WS_VISIBLE | WS_BORDER, r15, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_APU1,7,149,30,8
	CStatic *mfc16 = new CStatic(parent);
	CRect r16(CPoint(7, 149), CSize(30, 8));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r16, parent, IDC_LEVEL_APU1);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_APU2,40,149,30,8
	CStatic *mfc17 = new CStatic(parent);
	CRect r17(CPoint(40, 149), CSize(30, 8));
	parent->MapDialogRect(&r17);
	mfc17->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r17, parent, IDC_LEVEL_APU2);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_VRC6,73,149,30,8
	CStatic *mfc18 = new CStatic(parent);
	CRect r18(CPoint(73, 149), CSize(30, 8));
	parent->MapDialogRect(&r18);
	mfc18->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r18, parent, IDC_LEVEL_VRC6);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_VRC7,108,149,30,8
	CStatic *mfc19 = new CStatic(parent);
	CRect r19(CPoint(108, 149), CSize(30, 8));
	parent->MapDialogRect(&r19);
	mfc19->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r19, parent, IDC_LEVEL_VRC7);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_MMC5,142,149,30,8
	CStatic *mfc20 = new CStatic(parent);
	CRect r20(CPoint(142, 149), CSize(30, 8));
	parent->MapDialogRect(&r20);
	mfc20->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r20, parent, IDC_LEVEL_MMC5);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_FDS,176,149,30,8
	CStatic *mfc21 = new CStatic(parent);
	CRect r21(CPoint(176, 149), CSize(30, 8));
	parent->MapDialogRect(&r21);
	mfc21->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r21, parent, IDC_LEVEL_FDS);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_N163,209,149,30,8
	CStatic *mfc22 = new CStatic(parent);
	CRect r22(CPoint(209, 149), CSize(30, 8));
	parent->MapDialogRect(&r22);
	mfc22->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r22, parent, IDC_LEVEL_N163);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CTEXT "0.0dB",IDC_LEVEL_S5B,243,149,30,8
	CStatic *mfc23 = new CStatic(parent);
	CRect r23(CPoint(243, 149), CSize(30, 8));
	parent->MapDialogRect(&r23);
	mfc23->Create(_T("0.0dB"), WS_VISIBLE | WS_BORDER, r23, parent, IDC_LEVEL_S5B);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Hardware mixing levels",IDC_STATIC,7,7,74,8
	CStatic *mfc24 = new CStatic(parent);
	CRect r24(CPoint(7, 7), CSize(74, 8));
	parent->MapDialogRect(&r24);
	mfc24->Create(_T("Hardware mixing levels"), WS_VISIBLE | WS_BORDER, r24, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// END
}

void qtMfcInitDialogResource_IDD_INSTRUMENT_N163_WAVE(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_INSTRUMENT_N163_WAVE DIALOGEX 0, 0, 372, 172
	CRect rect(CPoint(0, 0), CSize(372, 172));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// STYLE DS_SETFONT|DS_FIXEDSYS|WS_CHILD|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Wave editor",IDC_STATIC,7,7,228,116
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(228, 116));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Wave editor"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "MML string",IDC_STATIC,7,132,358,33
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 132), CSize(358, 33));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("MML string"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Wave RAM settings",IDC_STATIC,244,45,121,52
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(244, 45), CSize(121, 52));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Wave RAM settings"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Wave #",IDC_STATIC,244,7,121,35
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(244, 7), CSize(121, 35));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Wave #"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r3, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// PUSHBUTTON "Sine",IDC_PRESET_SINE,14,104,41,14,WS_VISIBLE|WS_BORDER
	CButton *mfc5 = new CButton(parent);
	CRect r5(CPoint(14, 104), CSize(41, 14));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Sine"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_PRESET_SINE);
	mfcToQtWidget->insert(IDC_PRESET_SINE, mfc5);

	// PUSHBUTTON "Triangle",IDC_PRESET_TRIANGLE,57,104,41,14,WS_VISIBLE|WS_BORDER
	CButton *mfc6 = new CButton(parent);
	CRect r6(CPoint(57, 104), CSize(41, 14));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Triangle"), WS_VISIBLE | WS_BORDER, r6, parent, IDC_PRESET_TRIANGLE);
	mfcToQtWidget->insert(IDC_PRESET_TRIANGLE, mfc6);

	// PUSHBUTTON "Sawtooth",IDC_PRESET_SAWTOOTH,100,104,41,14,WS_VISIBLE|WS_BORDER
	CButton *mfc7 = new CButton(parent);
	CRect r7(CPoint(100, 104), CSize(41, 14));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("Sawtooth"), WS_VISIBLE | WS_BORDER, r7, parent, IDC_PRESET_SAWTOOTH);
	mfcToQtWidget->insert(IDC_PRESET_SAWTOOTH, mfc7);

	// PUSHBUTTON "50% pulse",IDC_PRESET_PULSE_50,143,104,41,14,WS_VISIBLE|WS_BORDER
	CButton *mfc8 = new CButton(parent);
	CRect r8(CPoint(143, 104), CSize(41, 14));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("50% pulse"), WS_VISIBLE | WS_BORDER, r8, parent, IDC_PRESET_PULSE_50);
	mfcToQtWidget->insert(IDC_PRESET_PULSE_50, mfc8);

	// PUSHBUTTON "25% pulse",IDC_PRESET_PULSE_25,186,104,41,14,WS_VISIBLE|WS_BORDER
	CButton *mfc9 = new CButton(parent);
	CRect r9(CPoint(186, 104), CSize(41, 14));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T("25% pulse"), WS_VISIBLE | WS_BORDER, r9, parent, IDC_PRESET_PULSE_25);
	mfcToQtWidget->insert(IDC_PRESET_PULSE_25, mfc9);

	// EDITTEXT IDC_MML,16,145,342,14,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
	CEdit *mfc11 = new CEdit(parent);
	CRect r11(CPoint(16, 145), CSize(342, 14));
	parent->MapDialogRect(&r11);
	mfc11->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, r11, parent, IDC_MML);
	mfcToQtWidget->insert(IDC_MML, mfc11);

	// PUSHBUTTON "Copy wave",IDC_COPY,249,105,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc12 = new CButton(parent);
	CRect r12(CPoint(249, 105), CSize(50, 14));
	parent->MapDialogRect(&r12);
	mfc12->Create(_T("Copy wave"), WS_VISIBLE | WS_BORDER, r12, parent, IDC_COPY);
	mfcToQtWidget->insert(IDC_COPY, mfc12);

	// PUSHBUTTON "Paste wave",IDC_PASTE,308,105,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc13 = new CButton(parent);
	CRect r13(CPoint(308, 105), CSize(50, 14));
	parent->MapDialogRect(&r13);
	mfc13->Create(_T("Paste wave"), WS_VISIBLE | WS_BORDER, r13, parent, IDC_PASTE);
	mfcToQtWidget->insert(IDC_PASTE, mfc13);

	// EDITTEXT IDC_INDEX,253,20,39,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc14 = new CEdit(parent);
	CRect r14(CPoint(253, 20), CSize(39, 12));
	parent->MapDialogRect(&r14);
	mfc14->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r14, parent, IDC_INDEX);
	mfcToQtWidget->insert(IDC_INDEX, mfc14);

	// CONTROL "", IDC_INDEX_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 281, 26, 11, 14
	CSpinButtonCtrl *mfc15 = new CSpinButtonCtrl(parent);
	CRect r15(CPoint(281, 26), CSize(11, 14));
	parent->MapDialogRect(&r15);
	mfc15->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r15, parent, IDC_INDEX_SPIN);
	mfcToQtWidget->insert(IDC_INDEX_SPIN, mfc15);

	// LTEXT "of",IDC_STATIC,300,22,8,8
	CStatic *mfc16 = new CStatic(parent);
	CRect r16(CPoint(300, 22), CSize(8, 8));
	parent->MapDialogRect(&r16);
	mfc16->Create(_T("of"), WS_VISIBLE | WS_BORDER, r16, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// EDITTEXT IDC_WAVES,316,20,37,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL|ES_READONLY
	CEdit *mfc17 = new CEdit(parent);
	CRect r17(CPoint(316, 20), CSize(37, 12));
	parent->MapDialogRect(&r17);
	mfc17->Create(WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, r17, parent, IDC_WAVES);
	mfcToQtWidget->insert(IDC_WAVES, mfc17);

	// CONTROL "", IDC_WAVES_SPIN, "msctls_updown32", WS_VISIBLE|WS_BORDER|UDS_SETBUDDYINT|UDS_ALIGNRIGHT|UDS_AUTOBUDDY|UDS_ARROWKEYS, 342, 19, 11, 14
	CSpinButtonCtrl *mfc18 = new CSpinButtonCtrl(parent);
	CRect r18(CPoint(342, 19), CSize(11, 14));
	parent->MapDialogRect(&r18);
	mfc18->Create(WS_VISIBLE | WS_BORDER | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_AUTOBUDDY | UDS_ARROWKEYS, r18, parent, IDC_WAVES_SPIN);
	mfcToQtWidget->insert(IDC_WAVES_SPIN, mfc18);

	// LTEXT "Wave size",IDC_STATIC,253,59,34,8
	CStatic *mfc20 = new CStatic(parent);
	CRect r20(CPoint(253, 59), CSize(34, 8));
	parent->MapDialogRect(&r20);
	mfc20->Create(_T("Wave size"), WS_VISIBLE | WS_BORDER, r20, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_WAVE_SIZE,305,57,48,30,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc21 = new CComboBox(parent);
	CRect r21(CPoint(305, 57), CSize(48, 30));
	parent->MapDialogRect(&r21);
	mfc21->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST | WS_VSCROLL | WS_TABSTOP, r21, parent, IDC_WAVE_SIZE);
	mfcToQtWidget->insert(IDC_WAVE_SIZE, mfc21);

	// LTEXT "Wave position",IDC_STATIC,253,78,46,8
	CStatic *mfc22 = new CStatic(parent);
	CRect r22(CPoint(253, 78), CSize(46, 8));
	parent->MapDialogRect(&r22);
	mfc22->Create(_T("Wave position"), WS_VISIBLE | WS_BORDER, r22, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// COMBOBOX IDC_WAVE_POS,305,75,48,30,WS_VISIBLE|WS_BORDER|CBS_DROPDOWN|WS_VSCROLL|WS_TABSTOP
	CComboBox *mfc23 = new CComboBox(parent);
	CRect r23(CPoint(305, 75), CSize(48, 30));
	parent->MapDialogRect(&r23);
	mfc23->Create(WS_VISIBLE | WS_BORDER | CBS_DROPDOWN | WS_VSCROLL | WS_TABSTOP, r23, parent, IDC_WAVE_POS);
	mfcToQtWidget->insert(IDC_WAVE_POS, mfc23);

	mfc23->AddString(_T("32"));

	mfc23->AddString(_T("16"));

	// END
}

void qtMfcInitDialogResource_IDD_IMPORT(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_IMPORT DIALOGEX 0, 0, 161, 209
	CRect rect(CPoint(0, 0), CSize(161, 209));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Import options"
	parent->SetWindowText("Import options");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "Tracks",IDC_STATIC,7,7,147,137
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(147, 137));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Tracks"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Options",IDC_STATIC,7,148,147,29
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(7, 148), CSize(147, 29));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Options"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,51,188,50,14
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(51, 188), CSize(50, 14));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("OK"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r2, parent, IDOK);
	mfcToQtWidget->insert(IDOK, mfc2);

	// PUSHBUTTON "Cancel",IDCANCEL,104,188,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(104, 188), CSize(50, 14));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Cancel"), WS_VISIBLE | WS_BORDER, r3, parent, IDCANCEL);
	mfcToQtWidget->insert(IDCANCEL, mfc3);

	// CONTROL "Include instruments", IDC_INSTRUMENTS, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 14, 161, 116, 10
	CButton *mfc5 = new CButton(parent);
	CRect r5(CPoint(14, 161), CSize(116, 10));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("Include instruments"), WS_VISIBLE | WS_BORDER | BS_AUTOCHECKBOX | WS_TABSTOP, r5, parent, IDC_INSTRUMENTS);
	mfcToQtWidget->insert(IDC_INSTRUMENTS, mfc5);

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDHORZ, 7, 183, 147, 1
	CStatic *mfc6 = new CStatic(parent);
	CRect r6(CPoint(7, 183), CSize(147, 1));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDHORZ, r6, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc6);

	// LISTBOX IDC_TRACKS,14,18,133,120,WS_VISIBLE|WS_BORDER|LBS_OWNERDRAWFIXED|LBS_HASSTRINGS|LBS_NOINTEGRALHEIGHT|WS_VSCROLL|WS_TABSTOP
	CListBox *mfc8 = new CListBox(parent);
	CRect r8(CPoint(14, 18), CSize(133, 120));
	parent->MapDialogRect(&r8);
	mfc8->Create(WS_VISIBLE | WS_BORDER | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | WS_TABSTOP, r8, parent, IDC_TRACKS);
	mfcToQtWidget->insert(IDC_TRACKS, mfc8);

	// END
}

void qtMfcInitDialogResource_IDD_PERFORMANCE(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_PERFORMANCE DIALOGEX 0, 0, 177, 95
	CRect rect(CPoint(0, 0), CSize(177, 95));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Performance"
	parent->SetWindowText("Performance");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|DS_CENTER|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// GROUPBOX "CPU usage",IDC_STATIC,7,7,68,53
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(7, 7), CSize(68, 53));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("CPU usage"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r0, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Other",IDC_STATIC,81,7,88,26
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(81, 7), CSize(88, 26));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Other"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r1, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// GROUPBOX "Audio",IDC_STATIC,81,34,88,26
	CButton *mfc2 = new CButton(parent);
	CRect r2(CPoint(81, 34), CSize(88, 26));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Audio"), BS_GROUPBOX | WS_VISIBLE | WS_BORDER, r2, parent, IDC_STATIC);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// DEFPUSHBUTTON "Close",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,58,74,60,14
	CButton *mfc3 = new CButton(parent);
	CRect r3(CPoint(58, 74), CSize(60, 14));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("Close"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r3, parent, IDOK);
	mfcToQtWidget->insert(IDOK, mfc3);

	// CTEXT "--%",IDC_CPU,43,30,29,10
	CStatic *mfc5 = new CStatic(parent);
	CRect r5(CPoint(43, 30), CSize(29, 10));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T("--%"), WS_VISIBLE | WS_BORDER, r5, parent, IDC_CPU);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_CPU_BAR, "msctls_progress32", WS_VISIBLE|WS_BORDER|PBS_SMOOTH|PBS_VERTICAL|WS_BORDER, 18, 19, 18, 34
	CProgressCtrl *mfc6 = new CProgressCtrl(parent);
	CRect r6(CPoint(18, 19), CSize(18, 34));
	parent->MapDialogRect(&r6);
	mfc6->Create(WS_VISIBLE | WS_BORDER | PBS_SMOOTH | PBS_VERTICAL | WS_BORDER, r6, parent, IDC_CPU_BAR);
	mfcToQtWidget->insert(IDC_CPU_BAR, mfc6);

	// LTEXT "Frame rate: 0 Hz",IDC_FRAMERATE,89,18,72,8
	CStatic *mfc7 = new CStatic(parent);
	CRect r7(CPoint(89, 18), CSize(72, 8));
	parent->MapDialogRect(&r7);
	mfc7->Create(_T("Frame rate: 0 Hz"), WS_VISIBLE | WS_BORDER, r7, parent, IDC_FRAMERATE);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// LTEXT "Underruns: 0",IDC_UNDERRUN,89,45,66,8
	CStatic *mfc8 = new CStatic(parent);
	CRect r8(CPoint(89, 45), CSize(66, 8));
	parent->MapDialogRect(&r8);
	mfc8->Create(_T("Underruns: 0"), WS_VISIBLE | WS_BORDER, r8, parent, IDC_UNDERRUN);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDHORZ, 7, 67, 162, 1
	CStatic *mfc9 = new CStatic(parent);
	CRect r9(CPoint(7, 67), CSize(162, 1));
	parent->MapDialogRect(&r9);
	mfc9->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDHORZ, r9, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc9);

	// END
}

void qtMfcInitDialogResource_IDD_SPEED(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_SPEED DIALOGEX 0, 0, 196, 44
	CRect rect(CPoint(0, 0), CSize(196, 44));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Custom speed"
	parent->SetWindowText("Custom speed");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,139,7,50,14
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(139, 7), CSize(50, 14));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("OK"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_BORDER, r0, parent, IDOK);
	mfcToQtWidget->insert(IDOK, mfc0);

	// PUSHBUTTON "Cancel",IDCANCEL,139,23,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc1 = new CButton(parent);
	CRect r1(CPoint(139, 23), CSize(50, 14));
	parent->MapDialogRect(&r1);
	mfc1->Create(_T("Cancel"), WS_VISIBLE | WS_BORDER, r1, parent, IDCANCEL);
	mfcToQtWidget->insert(IDCANCEL, mfc1);

	// CONTROL "", IDC_SPEED_SLD, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|WS_TABSTOP, 7, 7, 101, 16
	CSliderCtrl *mfc2 = new CSliderCtrl(parent);
	CRect r2(CPoint(7, 7), CSize(101, 16));
	parent->MapDialogRect(&r2);
	mfc2->Create(WS_VISIBLE | WS_BORDER | WS_TABSTOP, r2, parent, IDC_SPEED_SLD);
	mfcToQtWidget->insert(IDC_SPEED_SLD, mfc2);

	// LTEXT "60 Hz",IDC_SPEED,112,11,26,12
	CStatic *mfc3 = new CStatic(parent);
	CRect r3(CPoint(112, 11), CSize(26, 12));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T("60 Hz"), WS_VISIBLE | WS_BORDER, r3, parent, IDC_SPEED);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// END
}

/**
 * @brief Initializes the dialog resource for the module properties dialog in a Qt-based application.
 *
 * This function sets up the module properties dialog by defining its size, window properties, and creating various controls 
 * (buttons, sliders, labels, group boxes) using Qt equivalents to simulate the MFC-based UI. The function maps the MFC controls to 
 * their Qt counterparts and sets the necessary properties to maintain the original dialog's appearance and behavior.
 *
 * @param parent A pointer to the parent `CDialog` which will contain the controls. This is dynamically cast
 *               to a `QWidget` to enable Qt-based functionality.
 *
 * Usage:
 * This function should be called during the initialization phase of the application, specifically
 * when setting up the UI components for the module properties dialog. The typical use case is within a Qt-based
 * application that mimics or replaces an MFC-based UI, providing similar dialog functionality.
 *
 * Example:
 *
 * void MyDialog::setupModulePropertiesDialog()
 * {
 *     // Assuming 'this' is a pointer to a CDialog that needs initialization
 *     qtMfcInitDialogResource_IDD_PROPERTIES(this);
 * }
 *
 * Implementation Details:
 * 1. The function starts by setting the size and caption of the parent dialog.
 * 2. It sets window flags to simulate MFC window styles.
 * 3. Various controls are created using Qt equivalents (QPushButton, QSlider, QLabel, QGroupBox, QComboBox).
 * 4. Each control's geometry and properties are set to match the original MFC dialog layout.
 * 5. Controls are inserted into a mapping for further reference within the application.
 *
 * Platform Considerations:
 * - The function uses Qt classes and methods to replace MFC-specific controls and styles.
 * - The `MapDialogRect` function is adjusted to match the expected type for cross-platform compatibility.
 *
 * Note: This function assumes that `qtMfcBitmapResource` and `qtMfcStringResource` are available
 * functions that retrieve the respective resources in a format compatible with Qt.
 */
void qtMfcInitDialogResource_IDD_PROPERTIES(CDialog *parent)
{
    QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

    // IDD_PROPERTIES DIALOGEX 0, 0, 213, 259
    QRect rect(0, 0, 213, 259);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&rect)); // Adjust as needed for your environment
    parent->toQWidget()->setFixedSize(rect.width(), rect.height());

    // CAPTION "Module properties"
    parent->SetWindowText("Module properties");

    // STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU
    parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    // BEGIN
    // GROUPBOX "Song editor",IDC_STATIC,7,7,199,147
    QGroupBox *qtGroupBox0 = new QGroupBox("Song editor", parent->toQWidget());
    QRect r0(7, 7, 199, 147);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r0)); // Adjust as needed for your environment
    qtGroupBox0->setGeometry(r0);
    qtGroupBox0->setVisible(true);

    // GROUPBOX "Expansion sound",IDC_STATIC,7,162,131,30
    QGroupBox *qtGroupBox1 = new QGroupBox("Expansion sound", parent->toQWidget());
    QRect r1(7, 162, 131, 30);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r1)); // Adjust as needed for your environment
    qtGroupBox1->setGeometry(r1);
    qtGroupBox1->setVisible(true);

    // GROUPBOX "Vibrato",IDC_STATIC,7,194,199,31
    QGroupBox *qtGroupBox2 = new QGroupBox("Vibrato", parent->toQWidget());
    QRect r2(7, 194, 199, 31);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r2)); // Adjust as needed for your environment
    qtGroupBox2->setGeometry(r2);
    qtGroupBox2->setVisible(true);

    // GROUPBOX "Channels: 0",IDC_CHANNELS_NR,141,162,65,30
    QGroupBox *qtGroupBox3 = new QGroupBox("Channels: 0", parent->toQWidget());
    QRect r3(141, 162, 65, 30);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r3)); // Adjust as needed for your environment
    qtGroupBox3->setGeometry(r3);
    qtGroupBox3->setVisible(true);
    mfcToQtWidget->insert(IDC_CHANNELS_NR, reinterpret_cast<CWnd *>(qtGroupBox3));

    // CONTROL "", IDC_SONGLIST, "SysListView32", WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|LVS_ALIGNLEFT|LVS_NOCOLUMNHEADER|WS_BORDER|WS_TABSTOP, 14, 18, 124, 114
    QTableWidget *qtTableWidget = new QTableWidget(parent->toQWidget());
    QRect r5(14, 18, 124, 114);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r5)); // Adjust as needed for your environment
    qtTableWidget->setGeometry(r5);
    qtTableWidget->setVisible(true);
    qtTableWidget->setColumnCount(1);
    qtTableWidget->horizontalHeader()->hide();
    qtTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    qtTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    mfcToQtWidget->insert(IDC_SONGLIST, reinterpret_cast<CWnd *>(qtTableWidget));

    // PUSHBUTTON "Add",IDC_SONG_ADD,144,18,54,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton0 = new QPushButton("Add", parent->toQWidget());
    QRect r6(144, 18, 54, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r6)); // Adjust as needed for your environment
    qtButton0->setGeometry(r6);
    qtButton0->setVisible(true);
    qtButton0->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_SONG_ADD, reinterpret_cast<CWnd *>(qtButton0));

    // PUSHBUTTON "Remove",IDC_SONG_REMOVE,144,35,54,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton1 = new QPushButton("Remove", parent->toQWidget());
    QRect r7(144, 35, 54, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r7)); // Adjust as needed for your environment
    qtButton1->setGeometry(r7);
    qtButton1->setVisible(true);
    qtButton1->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_SONG_REMOVE, reinterpret_cast<CWnd *>(qtButton1));

    // PUSHBUTTON "Move up",IDC_SONG_UP,144,52,54,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton2 = new QPushButton("Move up", parent->toQWidget());
    QRect r8(144, 52, 54, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r8)); // Adjust as needed for your environment
    qtButton2->setGeometry(r8);
    qtButton2->setVisible(true);
    qtButton2->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_SONG_UP, reinterpret_cast<CWnd *>(qtButton2));

    // PUSHBUTTON "Move down",IDC_SONG_DOWN,144,69,54,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton3 = new QPushButton("Move down", parent->toQWidget());
    QRect r9(144, 69, 54, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r9)); // Adjust as needed for your environment
    qtButton3->setGeometry(r9);
    qtButton3->setVisible(true);
    qtButton3->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_SONG_DOWN, reinterpret_cast<CWnd *>(qtButton3));

    // PUSHBUTTON "Import file",IDC_SONG_IMPORT,144,86,54,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton4 = new QPushButton("Import file", parent->toQWidget());
    QRect r10(144, 86, 54, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r10)); // Adjust as needed for your environment
    qtButton4->setGeometry(r10);
    qtButton4->setVisible(true);
    qtButton4->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_SONG_IMPORT, reinterpret_cast<CWnd *>(qtButton4));

    // LTEXT " Title",IDC_STATIC,14,135,17,12
    QLabel *qtLabel0 = new QLabel(" Title", parent->toQWidget());
    QRect r11(14, 135, 17, 12);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r11)); // Adjust as needed for your environment
    qtLabel0->setGeometry(r11);
    qtLabel0->setVisible(true);
    qtLabel0->setAlignment(Qt::AlignCenter); // Simulate SS_CENTERIMAGE

    // EDITTEXT IDC_SONGNAME,38,135,100,12,WS_VISIBLE|WS_BORDER|ES_AUTOHSCROLL
    QLineEdit *qtLineEdit0 = new QLineEdit(parent->toQWidget());
    QRect r12(38, 135, 100, 12);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r12)); // Adjust as needed for your environment
    qtLineEdit0->setGeometry(r12);
    qtLineEdit0->setVisible(true);
    qtLineEdit0->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    qtLineEdit0->setPlaceholderText("Enter song name"); // Simulate ES_AUTOHSCROLL
    mfcToQtWidget->insert(IDC_SONGNAME, reinterpret_cast<CWnd *>(qtLineEdit0));

    // COMBOBOX IDC_EXPANSION,14,173,113,61,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
    QComboBox *qtComboBox0 = new QComboBox(parent->toQWidget());
    QRect r14(14, 173, 113, 61);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r14)); // Adjust as needed for your environment
    qtComboBox0->setGeometry(r14);
    qtComboBox0->setVisible(true);
    qtComboBox0->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    qtComboBox0->setFocusPolicy(Qt::StrongFocus); // Simulate WS_TABSTOP
    mfcToQtWidget->insert(IDC_EXPANSION, reinterpret_cast<CWnd *>(qtComboBox0));

    // COMBOBOX IDC_VIBRATO,14,204,184,61,WS_VISIBLE|WS_BORDER|CBS_DROPDOWNLIST|WS_VSCROLL|WS_TABSTOP
    QComboBox *qtComboBox1 = new QComboBox(parent->toQWidget());
    QRect r16(14, 204, 184, 61);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r16)); // Adjust as needed for your environment
    qtComboBox1->setGeometry(r16);
    qtComboBox1->setVisible(true);
    qtComboBox1->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    qtComboBox1->setFocusPolicy(Qt::StrongFocus); // Simulate WS_TABSTOP
    qtComboBox1->addItem("New style (bend up & down)");
    qtComboBox1->addItem("Old style (bend up)");
    mfcToQtWidget->insert(IDC_VIBRATO, reinterpret_cast<CWnd *>(qtComboBox1));

    // CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDHORZ, 7, 231, 199, 1
    QFrame *qtFrame0 = new QFrame(parent->toQWidget());
    QRect r17(7, 231, 199, 1);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r17)); // Adjust as needed for your environment
    qtFrame0->setGeometry(r17);
    qtFrame0->setVisible(true);
    qtFrame0->setFrameStyle(QFrame::HLine | QFrame::Sunken); // Simulate SS_ETCHEDHORZ

    // DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,95,238,53,14
    QPushButton *qtButton5 = new QPushButton("OK", parent->toQWidget());
    QRect r18(95, 238, 53, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r18)); // Adjust as needed for your environment
    qtButton5->setGeometry(r18);
    qtButton5->setDefault(true);
    qtButton5->setVisible(true);
    qtButton5->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDOK, reinterpret_cast<CWnd *>(qtButton5));

    // PUSHBUTTON "Cancel",IDCANCEL,153,238,53,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton6 = new QPushButton("Cancel", parent->toQWidget());
    QRect r19(153, 238, 53, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r19)); // Adjust as needed for your environment
    qtButton6->setGeometry(r19);
    qtButton6->setVisible(true);
    qtButton6->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDCANCEL, reinterpret_cast<CWnd *>(qtButton6));

    // CONTROL "", IDC_CHANNELS, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 147, 173, 51, 13
    QSlider *qtSlider0 = new QSlider(Qt::Horizontal, parent->toQWidget());
    QRect r21(147, 173, 51, 13);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r21)); // Adjust as needed for your environment
    qtSlider0->setGeometry(r21);
    qtSlider0->setVisible(true);
    qtSlider0->setTickPosition(QSlider::TicksBothSides); // Simulate TBS_AUTOTICKS
    qtSlider0->setFocusPolicy(Qt::StrongFocus); // Simulate WS_TABSTOP
    mfcToQtWidget->insert(IDC_CHANNELS, reinterpret_cast<CWnd *>(qtSlider0));

    // END
}


void qtMfcInitDialogResource_IDD_WAVE_PROGRESS(CDialog *parent)
{
	QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

	// IDD_WAVE_PROGRESS DIALOGEX 0, 0, 220, 111
	CRect rect(CPoint(0, 0), CSize(220, 111));
	parent->MapDialogRect(&rect);
	parent->setFixedSize(rect.Width(), rect.Height());

	// CAPTION "Creating WAV..."
	parent->SetWindowText("Creating WAV...");

	// STYLE DS_SETFONT|DS_MODALFRAME|DS_FIXEDSYS|DS_CENTER|WS_POPUP|WS_CAPTION|WS_SYSMENU
	parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	// BEGIN
	// PUSHBUTTON "Cancel",IDC_CANCEL,84,90,50,14,WS_VISIBLE|WS_BORDER
	CButton *mfc0 = new CButton(parent);
	CRect r0(CPoint(84, 90), CSize(50, 14));
	parent->MapDialogRect(&r0);
	mfc0->Create(_T("Cancel"), WS_VISIBLE | WS_BORDER, r0, parent, IDC_CANCEL);
	mfcToQtWidget->insert(IDC_CANCEL, mfc0);

	// CONTROL "", IDC_PROGRESS_BAR, "msctls_progress32", WS_VISIBLE|WS_BORDER|WS_BORDER, 7, 65, 206, 12
	CProgressCtrl *mfc1 = new CProgressCtrl(parent);
	CRect r1(CPoint(7, 65), CSize(206, 12));
	parent->MapDialogRect(&r1);
	mfc1->Create(WS_VISIBLE | WS_BORDER | WS_BORDER, r1, parent, IDC_PROGRESS_BAR);
	mfcToQtWidget->insert(IDC_PROGRESS_BAR, mfc1);

	// CTEXT "Progress",IDC_PROGRESS_LBL,7,37,206,11
	CStatic *mfc2 = new CStatic(parent);
	CRect r2(CPoint(7, 37), CSize(206, 11));
	parent->MapDialogRect(&r2);
	mfc2->Create(_T("Progress"), WS_VISIBLE | WS_BORDER, r2, parent, IDC_PROGRESS_LBL);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDFRAME, 7, 83, 206, 1
	CStatic *mfc3 = new CStatic(parent);
	CRect r3(CPoint(7, 83), CSize(206, 1));
	parent->MapDialogRect(&r3);
	mfc3->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDFRAME, r3, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc3);

	// CTEXT "File",IDC_PROGRESS_FILE,7,7,206,20
	CStatic *mfc4 = new CStatic(parent);
	CRect r4(CPoint(7, 7), CSize(206, 20));
	parent->MapDialogRect(&r4);
	mfc4->Create(_T("File"), WS_VISIBLE | WS_BORDER | SS_CENTERIMAGE, r4, parent, IDC_PROGRESS_FILE);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// CONTROL "", IDC_STATIC, "Static", WS_VISIBLE|WS_BORDER|SS_ETCHEDFRAME, 7, 29, 206, 1
	CStatic *mfc5 = new CStatic(parent);
	CRect r5(CPoint(7, 29), CSize(206, 1));
	parent->MapDialogRect(&r5);
	mfc5->Create(_T(""), WS_VISIBLE | WS_BORDER | SS_ETCHEDFRAME, r5, parent, IDC_STATIC);
	mfcToQtWidget->insert(IDC_STATIC, mfc5);

	// CTEXT "Progress",IDC_TIME,7,49,206,11
	CStatic *mfc6 = new CStatic(parent);
	CRect r6(CPoint(7, 49), CSize(206, 11));
	parent->MapDialogRect(&r6);
	mfc6->Create(_T("Progress"), WS_VISIBLE | WS_BORDER, r6, parent, IDC_TIME);
	// IDC_STATIC do not get added to MFC-to-Qt map.

	// END
}

/**
 * @brief Initializes the dialog resource for the sample editor in a Qt-based application.
 *
 * This function is used to initialize a dialog resource identified by `IDD_SAMPLE_EDITOR` within a parent
 * dialog (represented by `parent`). It sets the dialog size, window properties, and creates various controls
 * (buttons, labels, sliders) using Qt equivalents to simulate the MFC-based UI.
 *
 * @param parent A pointer to the parent `CDialog` which will contain the controls. This is dynamically cast
 *               to a `QWidget` to enable Qt-based functionality.
 *
 * Usage:
 * This function should be called during the initialization phase of the application, specifically
 * when setting up the UI components for the sample editor dialog. The typical use case is within a Qt-based
 * application that mimics or replaces an MFC-based UI, providing similar dialog functionality.
 *
 * Example:
 *
 * void MyDialog::setupSampleEditor()
 * {
 *     // Assuming 'this' is a pointer to a CDialog that needs initialization
 *     qtMfcInitDialogResource_IDD_SAMPLE_EDITOR(this);
 * }
 *
 * Implementation Details:
 * 1. The function starts by setting the size and caption of the parent dialog.
 * 2. It sets window flags to simulate MFC window styles.
 * 3. Various controls are created using Qt equivalents (QPushButton, QLabel, QSlider, QCheckBox).
 * 4. Each control's geometry and properties are set to match the original MFC dialog layout.
 * 5. Controls are inserted into a mapping for further reference within the application.
 *
 * Platform Considerations:
 * - The function uses Qt classes and methods to replace MFC-specific controls and styles.
 * - The `MapDialogRect` function is adjusted to match the expected type for cross-platform compatibility.
 *
 * Note: This function assumes that `qtMfcBitmapResource` and `qtMfcStringResource` are available
 * functions that retrieve the respective resources in a format compatible with Qt.
 */

void qtMfcInitDialogResource_IDD_SAMPLE_EDITOR(CDialog *parent)
{
    QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

    // IDD_SAMPLE_EDITOR DIALOGEX 0, 0, 481, 255
    QRect rect(0, 0, 481, 255);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&rect)); // Adjust as needed for your environment
    parent->toQWidget()->setFixedSize(rect.width(), rect.height());

    // CAPTION "DPCM sample editor"
    parent->SetWindowText("DPCM sample editor");

    // STYLE DS_SETFONT|DS_FIXEDSYS|WS_MAXIMIZEBOX|WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME
    parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::WindowMaximizeButtonHint | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    // BEGIN
    // DEFPUSHBUTTON "OK",BS_DEFPUSHBUTTON|WS_VISIBLE|WS_BORDER,424,217,50,14
    QPushButton *qtButton0 = new QPushButton("OK", parent->toQWidget());
    QRect r0(424, 217, 50, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r0)); // Adjust as needed for your environment
    qtButton0->setGeometry(r0);
    qtButton0->setDefault(true);
    qtButton0->setVisible(true);
    qtButton0->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDOK, reinterpret_cast<CWnd *>(qtButton0));

    // PUSHBUTTON "Cancel",IDCANCEL,424,234,50,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton1 = new QPushButton("Cancel", parent->toQWidget());
    QRect r1(424, 234, 50, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r1)); // Adjust as needed for your environment
    qtButton1->setGeometry(r1);
    qtButton1->setVisible(true);
    qtButton1->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDCANCEL, reinterpret_cast<CWnd *>(qtButton1));

    // CONTROL "", IDC_SAMPLE, "Static", WS_VISIBLE|WS_BORDER|SS_WHITERECT|SS_NOTIFY|SS_SUNKEN, 7, 7, 467, 204
    QLabel *qtLabel0 = new QLabel(parent->toQWidget());
    QRect r2(7, 7, 467, 204);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r2)); // Adjust as needed for your environment
    qtLabel0->setGeometry(r2);
    qtLabel0->setVisible(true);
    qtLabel0->setFrameStyle(QFrame::Box | QFrame::Plain); // Simulate WS_BORDER, SS_WHITERECT, SS_SUNKEN
    mfcToQtWidget->insert(IDC_SAMPLE, reinterpret_cast<CWnd *>(qtLabel0));

    // PUSHBUTTON "Play",IDC_PLAY,7,233,50,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton2 = new QPushButton("Play", parent->toQWidget());
    QRect r3(7, 233, 50, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r3)); // Adjust as needed for your environment
    qtButton2->setGeometry(r3);
    qtButton2->setVisible(true);
    qtButton2->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_PLAY, reinterpret_cast<CWnd *>(qtButton2));

    // LTEXT "Offset: 0, Pos: 0",IDC_POS,7,217,105,11
    QLabel *qtLabel1 = new QLabel("Offset: 0, Pos: 0", parent->toQWidget());
    QRect r4(7, 217, 105, 11);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r4)); // Adjust as needed for your environment
    qtLabel1->setGeometry(r4);
    qtLabel1->setVisible(true);
    qtLabel1->setFrameStyle(QFrame::Box | QFrame::Plain); // Simulate WS_BORDER, SS_SUNKEN
    // IDC_STATIC do not get added to MFC-to-Qt map.

    // PUSHBUTTON "Delete",IDC_DELETE,204,234,50,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton3 = new QPushButton("Delete", parent->toQWidget());
    QRect r5(204, 234, 50, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r5)); // Adjust as needed for your environment
    qtButton3->setGeometry(r5);
    qtButton3->setVisible(true);
    qtButton3->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_DELETE, reinterpret_cast<CWnd *>(qtButton3));

    // CONTROL "", IDC_PITCH, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 110, 236, 79, 12
    QSlider *qtSlider0 = new QSlider(Qt::Horizontal, parent->toQWidget());
    QRect r6(110, 236, 79, 12);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r6)); // Adjust as needed for your environment
    qtSlider0->setGeometry(r6);
    qtSlider0->setVisible(true);
    qtSlider0->setTickPosition(QSlider::TicksBothSides); // Simulate TBS_AUTOTICKS
    qtSlider0->setFocusPolicy(Qt::StrongFocus); // Simulate WS_TABSTOP
    mfcToQtWidget->insert(IDC_PITCH, reinterpret_cast<CWnd *>(qtSlider0));

    // PUSHBUTTON "Tilt",IDC_TILT,257,234,50,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton4 = new QPushButton("Tilt", parent->toQWidget());
    QRect r7(257, 234, 50, 14);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r7)); // Adjust as needed for your environment
    qtButton4->setGeometry(r7);
    qtButton4->setVisible(true);
    qtButton4->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_TILT, reinterpret_cast<CWnd *>(qtButton4));

    // LTEXT "0 bytes",IDC_INFO,115,217,87,11
    QLabel *qtLabel2 = new QLabel("0 bytes", parent->toQWidget());
    QRect r8(115, 217, 87, 11);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r8)); // Adjust as needed for your environment
    qtLabel2->setGeometry(r8);
    qtLabel2->setVisible(true);
    qtLabel2->setFrameStyle(QFrame::Box | QFrame::Plain); // Simulate WS_BORDER, SS_SUNKEN
    // IDC_STATIC do not get added to MFC-to-Qt map.

    // LTEXT "Pitch (15)",IDC_STATIC_PITCH,63,236,34,11
    QLabel *qtLabel3 = new QLabel("Pitch (15)", parent->toQWidget());
    QRect r9(63, 236, 34, 11);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r9)); // Adjust as needed for your environment
    qtLabel3->setGeometry(r9);
    qtLabel3->setVisible(true);
    qtLabel3->setFrameStyle(QFrame::Box | QFrame::Plain); // Simulate WS_BORDER
    // IDC_STATIC do not get added to MFC-to-Qt map.

    // CONTROL "Center wave", IDC_DELTASTART, "Button", WS_VISIBLE|WS_BORDER|BS_AUTOCHECKBOX|WS_TABSTOP, 314, 238, 57, 10
    QCheckBox *qtCheckBox0 = new QCheckBox("Center wave", parent->toQWidget());
    QRect r10(314, 238, 57, 10);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r10)); // Adjust as needed for your environment
    qtCheckBox0->setGeometry(r10);
    qtCheckBox0->setVisible(true);
    qtCheckBox0->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    qtCheckBox0->setFocusPolicy(Qt::StrongFocus); // Simulate WS_TABSTOP
    mfcToQtWidget->insert(IDC_DELTASTART, reinterpret_cast<CWnd *>(qtCheckBox0));

    // CONTROL "", IDC_ZOOM, "msctls_trackbar32", WS_VISIBLE|WS_BORDER|TBS_AUTOTICKS|WS_TABSTOP, 360, 217, 61, 12
    QSlider *qtSlider1 = new QSlider(Qt::Horizontal, parent->toQWidget());
    QRect r11(360, 217, 61, 12);
    parent->MapDialogRect(reinterpret_cast<LPRECT>(&r11)); // Adjust as needed for your environment
    qtSlider1->setGeometry(r11);
    qtSlider1->setVisible(true);
    qtSlider1->setTickPosition(QSlider::TicksBothSides); // Simulate TBS_AUTOTICKS
    qtSlider1->setFocusPolicy(Qt::StrongFocus); // Simulate WS_TABSTOP
    mfcToQtWidget->insert(IDC_ZOOM, reinterpret_cast<CWnd *>(qtSlider1));

    // END
}


void qtMfcInitDialogResource_IDD_EXPORT_TEST(CDialog *parent)
{
    QHash<int, CWnd *> *mfcToQtWidget = parent->mfcToQtWidgetMap();

    // IDD_EXPORT_TEST DIALOGEX 0, 0, 303, 383
    QRect rect(0, 0, 303, 383);
    parent->MapDialogRect(reinterpret_cast<int*>(&rect)); // Adjust to match expected type
    parent->toQWidget()->setFixedSize(rect.width(), rect.height());

    // CAPTION "Export test report"
    parent->SetWindowText("Export test report");

    // STYLE DS_SETFONT|DS_FIXEDSYS|WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME
    parent->toQWidget()->setWindowFlags(parent->toQWidget()->windowFlags() | Qt::Popup | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    // BEGIN
    // PUSHBUTTON "Abort",IDC_ABORT,60,7,50,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton0 = new QPushButton("Abort", parent->toQWidget());
    QRect r0(60, 7, 50, 14);
    parent->MapDialogRect(reinterpret_cast<int*>(&r0)); // Adjust to match expected type
    qtButton0->setGeometry(r0.left(), r0.top(), r0.width(), r0.height());
    qtButton0->setVisible(true);
    qtButton0->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_ABORT, reinterpret_cast<CWnd *>(qtButton0));

    // PUSHBUTTON "Continue",IDC_CONTINUE,7,7,50,14,WS_VISIBLE|WS_BORDER
    QPushButton *qtButton1 = new QPushButton("Continue", parent->toQWidget());
    QRect r1(7, 7, 50, 14);
    parent->MapDialogRect(reinterpret_cast<int*>(&r1)); // Adjust to match expected type
    qtButton1->setGeometry(r1.left(), r1.top(), r1.width(), r1.height());
    qtButton1->setVisible(true);
    qtButton1->setStyleSheet("border: 1px solid black;"); // Simulate WS_BORDER
    mfcToQtWidget->insert(IDC_CONTINUE, reinterpret_cast<CWnd *>(qtButton1));

    // END
}



void qtMfcInitDialogResource(UINT dlgID, CDialog *parent)
{
	switch (dlgID)
	{
	case IDD_ABOUTBOX:
		qtMfcInitDialogResource_IDD_ABOUTBOX(parent);
		break;

	case IDD_MAINFRAME:
		qtMfcInitDialogResource_IDD_MAINFRAME(parent);
		break;

	case IDD_PCMIMPORT:
		qtMfcInitDialogResource_IDD_PCMIMPORT(parent);
		break;

	case IDD_INSTRUMENT_INTERNAL:
		qtMfcInitDialogResource_IDD_INSTRUMENT_INTERNAL(parent);
		break;

	case IDD_INSTRUMENT_DPCM:
		qtMfcInitDialogResource_IDD_INSTRUMENT_DPCM(parent);
		break;

	case IDD_INSTRUMENT:
		qtMfcInitDialogResource_IDD_INSTRUMENT(parent);
		break;

	case IDD_CONFIG_APPEARANCE:
		qtMfcInitDialogResource_IDD_CONFIG_APPEARANCE(parent);
		break;

	case IDD_CONFIG_GENERAL:
		qtMfcInitDialogResource_IDD_CONFIG_GENERAL(parent);
		break;

	case IDD_CONFIG_MIDI:
		qtMfcInitDialogResource_IDD_CONFIG_MIDI(parent);
		break;

	case IDD_CONFIG_SOUND:
		qtMfcInitDialogResource_IDD_CONFIG_SOUND(parent);
		break;

	case IDD_CONFIG_SHORTCUTS:
		qtMfcInitDialogResource_IDD_CONFIG_SHORTCUTS(parent);
		break;

	case IDD_OCTAVE:
		qtMfcInitDialogResource_IDD_OCTAVE(parent);
		break;

	case IDD_EXPORT:
		qtMfcInitDialogResource_IDD_EXPORT(parent);
		break;

	case IDD_INSTRUMENT_VRC7:
		qtMfcInitDialogResource_IDD_INSTRUMENT_VRC7(parent);
		break;

	case IDD_CREATEWAV:
		qtMfcInitDialogResource_IDD_CREATEWAV(parent);
		break;

	case IDD_MAINBAR:
		qtMfcInitDialogResource_IDD_MAINBAR(parent);
		break;

	case IDD_INSTRUMENT_FDS:
		qtMfcInitDialogResource_IDD_INSTRUMENT_FDS(parent);
		break;

	case IDD_FRAMECONTROLS:
		qtMfcInitDialogResource_IDD_FRAMECONTROLS(parent);
		break;

	case IDD_INSTRUMENT_FDS_ENVELOPE:
		qtMfcInitDialogResource_IDD_INSTRUMENT_FDS_ENVELOPE(parent);
		break;

	case IDD_CHANNELS:
		qtMfcInitDialogResource_IDD_CHANNELS(parent);
		break;

	case IDD_HEADER:
		qtMfcInitDialogResource_IDD_HEADER(parent);
		break;

	case IDD_COMMENTS:
		qtMfcInitDialogResource_IDD_COMMENTS(parent);
		break;

	case IDD_CONFIG_MIXER:
		qtMfcInitDialogResource_IDD_CONFIG_MIXER(parent);
		break;

	case IDD_INSTRUMENT_N163_WAVE:
		qtMfcInitDialogResource_IDD_INSTRUMENT_N163_WAVE(parent);
		break;

	case IDD_IMPORT:
		qtMfcInitDialogResource_IDD_IMPORT(parent);
		break;

	case IDD_PERFORMANCE:
		qtMfcInitDialogResource_IDD_PERFORMANCE(parent);
		break;

	case IDD_SPEED:
		qtMfcInitDialogResource_IDD_SPEED(parent);
		break;

	case IDD_PROPERTIES:
		qtMfcInitDialogResource_IDD_PROPERTIES(parent);
		break;

	case IDD_WAVE_PROGRESS:
		qtMfcInitDialogResource_IDD_WAVE_PROGRESS(parent);
		break;

	case IDD_SAMPLE_EDITOR:
		qtMfcInitDialogResource_IDD_SAMPLE_EDITOR(parent);
		break;

	case IDD_EXPORT_TEST:
		qtMfcInitDialogResource_IDD_EXPORT_TEST(parent);
		break;

	case 0:
		// CP: Allow blank dialogs.
		break;
	default:
		qFatal("dialog resource not implemented...");
	}
}

void qtMfcInitToolBarResource_IDR_MAINFRAME(UINT dlgID, CToolBar *parent)
{
	QImage toolBarImage = qtMfcBitmapResource(IDR_MAINFRAME)->toQPixmap()->toImage();
	QToolBar *toolBar = dynamic_cast<QToolBar *>(parent->toQWidget());
	QPixmap toolBarActionPixmap;
	QAction *toolBarAction;
	QRgb pixel00;
	int x, y;

	toolBarImage = toolBarImage.convertToFormat(QImage::Format_ARGB32);
	pixel00 = toolBarImage.pixel(0, 0);
	for (y = 0; y < toolBarImage.height(); y++)
	{
		for (x = 0; x < toolBarImage.width(); x++)
		{
			if (toolBarImage.pixel(x, y) == pixel00)
			{
				toolBarImage.setPixel(x, y, qRgba(0, 0, 0, 0));
			}
		}
	}

	// IDR_MAINFRAME TOOLBAR 16, 15
	toolBar->setIconSize(QSize(16, 15));
	// BEGIN
	// BUTTON ID_FILE_NEW
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(0 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_FILE_NEW);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_FILE_OPEN
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(1 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_FILE_OPEN);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_FILE_SAVE
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(2 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_FILE_SAVE);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_EDIT_CUT
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(3 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_EDIT_CUT);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_EDIT_COPY
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(4 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_EDIT_COPY);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_EDIT_PASTE
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(5 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_EDIT_PASTE);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_APP_ABOUT
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(6 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_APP_ABOUT);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_CONTEXT_HELP
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(7 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_CONTEXT_HELP);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_MODULE_INSERTFRAME
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(8 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_MODULE_INSERTFRAME);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_MODULE_REMOVEFRAME
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(9 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_MODULE_REMOVEFRAME);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_MODULE_MOVEFRAMEDOWN
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(10 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_MODULE_MOVEFRAMEDOWN);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_MODULE_MOVEFRAMEUP
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(11 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_MODULE_MOVEFRAMEUP);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_MODULE_DUPLICATEFRAME
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(12 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_MODULE_DUPLICATEFRAME);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_MODULE_MODULEPROPERTIES
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(13 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_MODULE_MODULEPROPERTIES);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_TRACKER_PLAY
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(14 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_TRACKER_PLAY);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_TRACKER_PLAYPATTERN
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(15 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_TRACKER_PLAYPATTERN);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_TRACKER_STOP
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(16 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_TRACKER_STOP);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_TRACKER_EDIT
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(17 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_TRACKER_EDIT);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_PREV_SONG
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(18 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_PREV_SONG);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// BUTTON ID_NEXT_SONG
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(19 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_NEXT_SONG);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_FILE_GENERALSETTINGS
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(20 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_FILE_GENERALSETTINGS);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// SEPARATOR
	toolBar->addSeparator();

	// BUTTON ID_FILE_CREATE_NSF
	toolBarAction = new QAction(parent);
	toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(21 * 16, 0, 16, 15));
	toolBarAction->setIcon(QIcon(toolBarActionPixmap));
	toolBarAction->setData(ID_FILE_CREATE_NSF);
	QObject::connect(toolBarAction, SIGNAL(triggered()), parent, SLOT(toolBarAction_triggered()));
	toolBar->addAction(toolBarAction);

	// END

	for (x = 0; x < toolBar->actions().count(); x++)
	{
		CString toolTipCString = qtMfcStringResource(toolBar->actions().at(x)->data().toInt());
		QString toolTip = toolTipCString;
		if (toolTip.indexOf('\n') >= 0)
		{
			toolBar->actions().value(x)->setToolTip(toolTip.right(toolTip.length() - toolTip.indexOf('\n') - 1));
		}
	}
}

/**
 * @brief Initializes the toolbar resource for the instrument toolbar in a Qt-based application.
 * 
 * This function is used to initialize a toolbar resource identified by `dlgID` within a parent 
 * toolbar (represented by `parent`). It dynamically casts the parent to a `QToolBar`, processes 
 * the toolbar bitmap resource, sets up individual toolbar buttons with specific icons and 
 * actions, and configures tooltips for each button. The function uses Qt's signal-slot mechanism 
 * to connect the button actions to their corresponding slots.
 * 
 * @param dlgID The identifier of the dialog resource. This parameter is kept for consistency 
 *              but is not used directly in this function.
 * @param parent A pointer to the parent `CToolBar` which will contain the toolbar buttons. This 
 *               is dynamically cast to a `QToolBar` to enable Qt-based functionality.
 * 
 * Usage:
 * This function should be called during the initialization phase of the application, specifically 
 * when setting up the UI components. The typical use case is within a Qt-based application that 
 * mimics or replaces an MFC-based UI, providing similar toolbar functionality.
 * 
 * Example:
 * 
 * void MyDialog::setupToolbar()
 * {
 *     // Assuming 'this' is a pointer to a CToolBar that needs initialization
 *     qtMfcInitToolBarResource_IDR_INSTRUMENT_TOOLBAR(IDR_INSTRUMENT_TOOLBAR, this);
 * }
 * 
 * Implementation Details:
 * 1. The function starts by loading the toolbar image resource and converting it to a format 
 *    suitable for Qt (ARGB32).
 * 2. It then identifies the background color (top-left pixel) and makes all pixels of this color 
 *    transparent.
 * 3. The toolbar's icon size is set to 16x15 pixels.
 * 4. A structure array is used to define toolbar buttons, each associated with an ID and a slot 
 *    function (`toolBarAction_triggered`).
 * 5. For each button, an action is created, its icon is set using a portion of the toolbar image, 
 *    and the action is connected to the specified slot.
 * 6. Separators are added between specific buttons to organize the toolbar visually.
 * 7. Tooltips for each action are set by retrieving the string resource associated with the action 
 *    ID and processing it to remove any preceding lines.
 * 
 * Platform Considerations:
 * - On Windows, `UINT` is defined in `windows.h`.
 * - On non-Windows platforms, `UINT` is typedefed as `unsigned int`.
 * - `CToolBar` is a Windows/MFC-specific class, so the parent is dynamically cast to `QToolBar` 
 *   to work with Qt.
 * 
 * Note: This function assumes that `qtMfcBitmapResource` and `qtMfcStringResource` are available 
 * functions that retrieve the respective resources in a format compatible with Qt.
 */
void qtMfcInitToolBarResource_IDR_INSTRUMENT_TOOLBAR(UINT dlgID, CToolBar *parent)
{
    QImage toolBarImage = qtMfcBitmapResource(IDR_INSTRUMENT_TOOLBAR)->toQPixmap()->toImage();
    QToolBar *toolBar = dynamic_cast<QToolBar *>(parent->toQWidget());
    if (!toolBar) {
        // Handle error
        return;
    }

    toolBarImage = toolBarImage.convertToFormat(QImage::Format_ARGB32);
    QRgb pixel00 = toolBarImage.pixel(0, 0);
    for (int y = 0; y < toolBarImage.height(); y++)
    {
        for (int x = 0; x < toolBarImage.width(); x++)
        {
            if (toolBarImage.pixel(x, y) == pixel00)
            {
                toolBarImage.setPixel(x, y, qRgba(0, 0, 0, 0));
            }
        }
    }

    toolBar->setIconSize(QSize(16, 15));

    struct ToolBarButton {
        int id;
        int position;
        const char *slot;
    };

    ToolBarButton buttons[] = {
        { ID_INSTRUMENT_NEW, 0, SLOT(toolBarAction_triggered()) },
        { ID_INSTRUMENT_REMOVE, 1, SLOT(toolBarAction_triggered()) },
        { ID_INSTRUMENT_CLONE, 2, SLOT(toolBarAction_triggered()) },
        { ID_INSTRUMENT_LOAD, 3, SLOT(toolBarAction_triggered()) },
        { ID_INSTRUMENT_SAVE, 4, SLOT(toolBarAction_triggered()) },
        { ID_INSTRUMENT_EDIT, 5, SLOT(toolBarAction_triggered()) },
    };

    for (const auto& button : buttons) {
        QAction *toolBarAction = new QAction(parent);
        QPixmap toolBarActionPixmap = QPixmap::fromImage(toolBarImage.copy(button.position * 16, 0, 16, 15));
        toolBarAction->setIcon(QIcon(toolBarActionPixmap));
        toolBarAction->setData(button.id);
        QObject::connect(toolBarAction, SIGNAL(triggered()), parent, button.slot);
        toolBar->addAction(toolBarAction);
    }

    toolBar->addSeparator();
    toolBar->addSeparator();

    for (int x = 0; x < toolBar->actions().count(); x++)
    {
        CString toolTipCString = qtMfcStringResource(toolBar->actions().at(x)->data().toInt());
        QString toolTip = QString::fromStdString(toolTipCString.GetString());
        if (toolTip.indexOf('\n') >= 0)
        {
            toolBar->actions().value(x)->setToolTip(toolTip.mid(toolTip.indexOf('\n') + 1));
        }
    }
}



void qtMfcInitToolBarResource(UINT dlgID, CToolBar *parent)
{
	switch (dlgID)
	{
	case IDR_MAINFRAME:
		qtMfcInitToolBarResource_IDR_MAINFRAME(dlgID, parent);
		break;

	case IDR_INSTRUMENT_TOOLBAR:
		qtMfcInitToolBarResource_IDR_INSTRUMENT_TOOLBAR(dlgID, parent);
		break;
	}
}

void qtMfcInit(QMainWindow *parent)
{
	// Hook Qt to this MFC app...
	AfxGetApp()->qtMainWindow = parent;
	AfxGetApp()->moveToThread(QApplication::instance()->thread());

	qtMfcInitStringResources();
	qtMfcInitBitmapResources();
	qtInitIconResources();
}
