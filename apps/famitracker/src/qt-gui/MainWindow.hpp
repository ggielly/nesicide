#ifndef _MAINWINDOW_HPP_
#define _MAINWINDOW_HPP_

#include <QMainWindow>
#include <QEvent>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include "ui_mainwindow.h"

namespace gui
{
#define UPDATEEVENT QEvent::User
#define ISPLAYINGSONGEVENT (QEvent::Type)((int)QEvent::User+1)
#define CALLBACKEVENT (QEvent::Type)((int)QEvent::User+2)

	class App;
	class MainWindow;
	class InstrumentEditor;

	typedef void(*stopsong_callback)(MainWindow*, void*);

	class UpdateEvent : public QEvent
	{
	public:
		UpdateEvent() : QEvent(UPDATEEVENT){}
		boost::mutex * mtx_updateEvent;
		boost::condition * cond_updateEvent;
	};
	class CallbackEvent : public QEvent
	{
	public:
		CallbackEvent() : QEvent(CALLBACKEVENT){}
		stopsong_callback callback;
		void *callback_data;
	};

	class IsPlayingSongEvent : public QEvent
	{
	public:
		IsPlayingSongEvent() : QEvent(ISPLAYINGSONGEVENT){}
		bool playing;
	};

	class MainWindow : public QMainWindow, Ui_MainWindow
	{
		Q_OBJECT
	public:
		MainWindow(App *a);
		~MainWindow();

		void setDocInfo(DocInfo *dinfo);

		void updateFrameChannel(bool modified=false);
		void updateOctave();

		void updateStyles();

		void updateEditMode();
		void setPlaying(bool playing);

		void refreshInstruments();

		void stopSongConcurrent(void(*mainthread_callback)(void *data));

		void updateDocument();

		void reloadRecentFiles();
		void setDocumentName(const QString &documentName);
	protected:
		void closeEvent(QCloseEvent *);
		bool event(QEvent *event);
	private:
		QString saveFileDialog(const QString &settingspath, const QString &filter);

		void setSong_mw_cb();
		static void setSong_cb(MainWindow*, void*);

		static void newDoc_cb(MainWindow*, void*);
		static void open_cb(MainWindow*, void*);

		static void close_cb(MainWindow*, void*);

		static void createwav_cb(MainWindow*, void*);
		bool m_close_shutdown;
	public slots:
		void unimplemented();

		void newDoc();
		void open();
		void openRecentFile();
		void openFile(const QString &path);
		void save();
		void saveAs();
		void createWAV();
		void quit();

		void moduleProperties();

		void viewToolbar(bool);
		void viewStatusBar(bool);
		void viewControlpanel(bool);
		void controlPanelVisibilityChanged();

		void about();

		void setSong(int i);
		void incrementPattern();
		void decrementPattern();
		void instrumentSelect();
		void instrumentNameChange(QString);
		void instrumentDoubleClicked(QModelIndex);
		void speedTempoChange(int);
		void rowsChange(int);
		void framesChange(int);

		void octaveChange();

		void changeSongTitle();
		void changeSongAuthor();
		void changeSongCopyright();

		void play();
		void stop();
		void toggleEditMode();

		void addInstrument_2A03();
		void addInstrument_VRC6();
		void addInstrument_VRC7();
		void addInstrument_MMC5();
		void addInstrument_FDS();
		void removeInstrument();
		void editInstrument();

		void changeEditSettings();

		// temporary style stuff
		void selectDefaultStyle();
		void selectMonochromeStyle();
	private:
    void DoSave(const QString &path);

		App * m_app;
		DocInfo * m_dinfo;
		InstrumentEditor *m_instrumenteditor;
		QComboBox *octave;
		QAction ** m_recentFiles;
    QString current_filename_;

		void addInstrument(int chip);
	};
}

#endif

