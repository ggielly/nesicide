#include "MainWindow.hpp"
#include <QDebug>
#include <QFileDialog>
#include "AboutDialog.hpp"
#include "CreateWAV.hpp"
#include "GUI.hpp"
#include "GUI_App.hpp"
#include "InstrumentEditor.hpp"
#include "ModuleProperties.hpp"
#include "Settings.hpp"
#include "famitracker-core/FtmDocument.hpp"
#include "styles.hpp"

namespace gui {
MainWindow::MainWindow(App *a) : m_close_shutdown(false), m_app(a) {
  setupUi(this);
  setDocumentName("");
  instruments->setIconSize(QSize(16, 16));

  speed->setRange(MIN_SPEED, MAX_SPEED);
  tempo->setRange(MIN_TEMPO, MAX_TEMPO);
  rows->setRange(1, MAX_PATTERN_LENGTH);
  frames->setRange(1, MAX_FRAMES);

  title->setMaxLength(MAX_SONGINFO_LENGTH);
  author->setMaxLength(MAX_SONGINFO_LENGTH);
  copyright->setMaxLength(MAX_SONGINFO_LENGTH);
  instrumentName->setMaxLength(MAX_INSTRUMENT_NAME_LENGTH);

  QObject::connect(actionNew, SIGNAL(triggered()), this, SLOT(newDoc()));
  actionNew->setIcon(QIcon::fromTheme("document-new"));
  QObject::connect(action_Open, SIGNAL(triggered()), this, SLOT(open()));
  action_Open->setIcon(QIcon::fromTheme("document-open"));
  QObject::connect(action_Save, SIGNAL(triggered()), this, SLOT(save()));
  action_Save->setIcon(QIcon::fromTheme("document-save"));
  QObject::connect(actionSave_As, SIGNAL(triggered()), this, SLOT(saveAs()));
  QObject::connect(action_Create_NSF, SIGNAL(triggered()), this, SLOT(unimplemented()));
  QObject::connect(actionCreate_WAV, SIGNAL(triggered()), this, SLOT(createWAV()));
  QObject::connect(actionImport_MIDI, SIGNAL(triggered()), this, SLOT(unimplemented()));
  QObject::connect(action_Configuration, SIGNAL(triggered()), this, SLOT(unimplemented()));
  QObject::connect(actionE_xit, SIGNAL(triggered()), this, SLOT(quit()));

  QObject::connect(actionModule_Properties, SIGNAL(triggered()), this, SLOT(moduleProperties()));

  QObject::connect(action_ViewToolbar, SIGNAL(toggled(bool)), this, SLOT(viewToolbar(bool)));
  QObject::connect(action_ViewStatusBar, SIGNAL(toggled(bool)), this, SLOT(viewStatusBar(bool)));
  QObject::connect(action_ViewControlpanel, SIGNAL(toggled(bool)), this,
                   SLOT(viewControlpanel(bool)));
  QObject::connect(toolBar, SIGNAL(visibilityChanged(bool)), action_ViewToolbar,
                   SLOT(setChecked(bool)));
  QObject::connect(controlPanel, SIGNAL(visibilityChanged(bool)), this,
                   SLOT(controlPanelVisibilityChanged()));

  QObject::connect(action_About, SIGNAL(triggered()), this, SLOT(about()));
  QObject::connect(actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QObject::connect(songs, SIGNAL(activated(int)), this, SLOT(setSong(int)));

  QObject::connect(incPattern, SIGNAL(clicked()), this, SLOT(incrementPattern()));
  QObject::connect(decPattern, SIGNAL(clicked()), this, SLOT(decrementPattern()));
  QObject::connect(instruments, SIGNAL(itemSelectionChanged()), this, SLOT(instrumentSelect()));
  QObject::connect(instrumentName, SIGNAL(textEdited(QString)), this,
                   SLOT(instrumentNameChange(QString)));
  QObject::connect(instruments, SIGNAL(doubleClicked(QModelIndex)), this,
                   SLOT(instrumentDoubleClicked(QModelIndex)));

  QObject::connect(speed, SIGNAL(valueChanged(int)), this, SLOT(speedTempoChange(int)));
  QObject::connect(tempo, SIGNAL(valueChanged(int)), this, SLOT(speedTempoChange(int)));
  QObject::connect(rows, SIGNAL(valueChanged(int)), this, SLOT(rowsChange(int)));
  QObject::connect(frames, SIGNAL(valueChanged(int)), this, SLOT(framesChange(int)));

  QObject::connect(title, SIGNAL(editingFinished()), this, SLOT(changeSongTitle()));
  QObject::connect(author, SIGNAL(editingFinished()), this, SLOT(changeSongAuthor()));
  QObject::connect(copyright, SIGNAL(editingFinished()), this, SLOT(changeSongCopyright()));

  QObject::connect(action_Play, SIGNAL(triggered()), this, SLOT(play()));
  action_Play->setIcon(QIcon::fromTheme("media-playback-start"));
  QObject::connect(action_Stop, SIGNAL(triggered()), this, SLOT(stop()));
  action_Stop->setIcon(QIcon::fromTheme("media-playback-stop"));
  QObject::connect(actionToggle_edit_mode, SIGNAL(triggered()), this, SLOT(toggleEditMode()));
  actionToggle_edit_mode->setIcon(QIcon::fromTheme("media-record"));

  QObject::connect(addInstrument_button, SIGNAL(clicked()), this, SLOT(addInstrument_2A03()));
  addInstrument_button->setIcon(QIcon::fromTheme("list-add"));
  addInstrument_button->setText(tr("Add Instrument"));
  QObject::connect(removeInstrument_button, SIGNAL(clicked()), this, SLOT(removeInstrument()));
  removeInstrument_button->setIcon(QIcon::fromTheme("list-remove"));
  removeInstrument_button->setText(tr("Remove Instrument"));
  QObject::connect(editInstrument_button, SIGNAL(clicked()), this, SLOT(editInstrument()));
  editInstrument_button->setText(tr("Edit Instrument"));

  {
    QMenu *m = new QMenu(this);
    QAction *add2a03 = m->addAction(tr("New 2A03 Instrument"));
    QAction *addmmc5 = m->addAction(tr("New MMC5 Instrument"));
    QAction *addvrc6 = m->addAction(tr("New VRC6 Instrument"));
    QAction *addvrc7 = m->addAction(tr("New VRC7 Instrument"));
    QAction *addfds = m->addAction(tr("New FDS Instrument"));

    QObject::connect(add2a03, SIGNAL(triggered()), this, SLOT(addInstrument_2A03()));
    QObject::connect(addvrc6, SIGNAL(triggered()), this, SLOT(addInstrument_VRC6()));
    QObject::connect(addvrc7, SIGNAL(triggered()), this, SLOT(addInstrument_VRC7()));
    QObject::connect(addmmc5, SIGNAL(triggered()), this, SLOT(addInstrument_MMC5()));
    QObject::connect(addfds, SIGNAL(triggered()), this, SLOT(addInstrument_FDS()));

    m->setDefaultAction(add2a03);
    addInstrument_button->setMenu(m);
  }

  QObject::connect(step, SIGNAL(valueChanged(int)), this, SLOT(changeEditSettings()));
  QObject::connect(keyRepetition, SIGNAL(stateChanged(int)), this, SLOT(changeEditSettings()));

  {
    // recent files
    int capacity = gui::recentFileCapacity();
    m_recentFiles = new QAction *[capacity];
    for (int i = 0; i < capacity; i++) {
      QAction *a = new QAction(this);
      a->setVisible(false);
      connect(a, SIGNAL(triggered()), this, SLOT(openRecentFile()));
      m_recentFiles[i] = a;
      menuRecent->addAction(a);
    }

    // end recent files
  }

  reloadRecentFiles();

  // the designer doesn't allow adding widgets

  {
    octave = new QComboBox;
    for (int i = 0; i < 8; i++) {
      octave->addItem(QString("%1").arg(i));
    }
    connect(octave, SIGNAL(currentIndexChanged(int)), this, SLOT(octaveChange()));
    toolBar->addWidget(new QLabel(tr("Octave")));
    toolBar->addWidget(octave);
  }

  // temporary style changing (for demonstration)
  {
    menu_View->addSeparator();
    QMenu *styles = new QMenu(tr("Styles"));
    QAction *style_default = styles->addAction(tr("Default"));
    QAction *style_monochrome = styles->addAction(tr("Monochrome"));
    menu_View->addMenu(styles);

    connect(style_default, SIGNAL(triggered()), this, SLOT(selectDefaultStyle()));
    connect(style_monochrome, SIGNAL(triggered()), this, SLOT(selectMonochromeStyle()));
  }

  QMenu *m = new QMenu;
  m->addAction(tr("New 2A03 instrument"));

  actionAdd_instrument->setMenu(m);

  setDocInfo(m_app->activeDocInfo());

  m_instrumenteditor = new InstrumentEditor(this);

  blockSignals(true);
  blockSignals(false);
}
MainWindow::~MainWindow() {
  delete m_instrumenteditor;
}
void MainWindow::setDocInfo(DocInfo *dinfo) {
  m_dinfo = dinfo;
  patternView->setDocInfo(dinfo);
}

void MainWindow::selectDefaultStyle() {
  styles::selectStyle("Default");
  updateStyles();
}
void MainWindow::selectMonochromeStyle() {
  styles::selectStyle("Monochrome");
  updateStyles();
}

void MainWindow::DoSave(const QString &path) {
  core::FileIO *io = new core::FileIO(path.toLocal8Bit(), core::IO_WRITE);
  m_dinfo->doc()->write(io);

  delete io;
}

void MainWindow::updateFrameChannel(bool modified) {
  frameView->update(modified);
  patternView->update(modified);
}

void MainWindow::updateOctave() {
  octave->blockSignals(true);
  octave->setCurrentIndex(m_dinfo->currentOctave());
  octave->blockSignals(false);
}

void MainWindow::updateStyles() {
  frameView->updateStyles();
  patternView->updateStyles();
}

void MainWindow::updateEditMode() {
  bool b = gui::isEditing();
  actionToggle_edit_mode->setChecked(b);
  patternView->update();
}
void MainWindow::setPlaying(bool playing) {
  rows->setEnabled(!playing);
  frames->setEnabled(!playing);
  action_Play->setEnabled(!playing);
  actionPlay_and_loop->setEnabled(!playing);
  action_Stop->setEnabled(playing);
}

static void doclose_cb(MainWindow *mw, void *) {
  mw->close();
}

void MainWindow::close_cb(MainWindow *mw, void *) {
  mw->m_close_shutdown = true;
  mw->close();
}

void MainWindow::closeEvent(QCloseEvent *e) {
  if (gui::isPlaying()) {
    ((QEvent *)e)->ignore();
    gui::stopSongConcurrent(doclose_cb);
  } else if (!m_close_shutdown) {
    ((QEvent *)e)->ignore();
    gui::deleteSinkConcurrent(close_cb);
  } else {
    ((QEvent *)e)->accept();
  }
}

bool MainWindow::event(QEvent *event) {
  if (event->type() == UPDATEEVENT) {
    UpdateEvent *e = (UpdateEvent *)event;

    e->mtx_updateEvent->lock();
    updateFrameChannel();

    e->cond_updateEvent->notify_all();
    e->mtx_updateEvent->unlock();
    return true;
  } else if (event->type() == CALLBACKEVENT) {
    CallbackEvent *e = (CallbackEvent *)event;

    if (e->callback != NULL) {
      (*e->callback)(this, e->callback_data);
    }
    return true;
  } else if (event->type() == ISPLAYINGSONGEVENT) {
    IsPlayingSongEvent *e = (IsPlayingSongEvent *)event;

    setPlaying(e->playing);
    return true;
  }

  return QMainWindow::event(event);
}

static void setInstrumentName(QListWidgetItem *item, int i, const char *s) {
  char buf[256];
  sprintf(buf, "%02X - %s", i, s);

  item->setText(buf);
}

void MainWindow::updateDocument() {
  FtmDocument *d = m_dinfo->doc();

  title->blockSignals(true);
  author->blockSignals(true);
  copyright->blockSignals(true);

  title->setText(d->GetSongName());
  title->setCursorPosition(0);
  author->setText(d->GetSongArtist());
  author->setCursorPosition(0);
  copyright->setText(d->GetSongCopyright());
  copyright->setCursorPosition(0);

  copyright->blockSignals(false);
  author->blockSignals(false);
  title->blockSignals(false);

  songs->clear();
  int c = d->GetTrackCount();
  for (int i = 0; i < c; i++) {
    QString s(d->GetTrackTitle(i));
    songs->addItem(s);
  }

  songs->setCurrentIndex(d->GetSelectedTrack());
  setSong(-1);
  frameView->update();

  refreshInstruments();

  updateOctave();

  step->blockSignals(true);
  step->setValue(m_dinfo->editStep());
  step->blockSignals(false);

  keyRepetition->blockSignals(true);
  keyRepetition->setChecked(m_dinfo->keyRepetition());
  keyRepetition->blockSignals(false);
}
void MainWindow::reloadRecentFiles() {
  bool containsRecentFiles = false;
  int capacity = gui::recentFileCapacity();
  for (int i = 0; i < capacity; i++) {
    QVariant v = gui::recentFileVariant(i);
    m_recentFiles[i]->setVisible(v.isValid());
    if (v.isValid()) {
      containsRecentFiles = true;
      m_recentFiles[i]->setText(QString("%1. %2").arg(i + 1).arg(v.toString()));
      m_recentFiles[i]->setData(v.toString());
    }
  }
  actionNo_recent_files->setVisible(!containsRecentFiles);
}
void MainWindow::setDocumentName(const QString &documentName) {
  if (documentName.isEmpty()) {
    setWindowTitle(QApplication::applicationName());
  } else {
    setWindowTitle(QString("%1 - %2").arg(documentName).arg(QApplication::applicationName()));
  }
}

void MainWindow::refreshInstruments() {
  FtmDocument *d = m_dinfo->doc();

  int current = m_dinfo->currentInstrument();

  instruments->clear();
  int instc = d->GetInstrumentCount();

  instrumentName->clear();
  instrumentName->setEnabled(instc > 0);
  for (int i = 0; i < 64; i++) {
    if (!d->IsInstrumentUsed(i)) continue;

    CInstrument *inst = d->GetInstrument(i);

    QListWidgetItem *item = new QListWidgetItem;
    const char *res;
    switch (inst->GetType()) {
      case INST_NONE:
      case INST_2A03:
        res = ":/inst/2a03";
        break;
      case INST_VRC6:
        res = ":/inst/vrc6";
        break;
      case INST_VRC7:
        res = ":/inst/vrc7";
        break;
      case INST_FDS:
        res = ":/inst/fds";
        break;
      default:
        res = NULL;
        break;
    }

    if (res != NULL) item->setIcon(QIcon(res));
    setInstrumentName(item, i, inst->GetName());

    item->setData(Qt::UserRole, qVariantFromValue(i));
    instruments->addItem(item);

    if (i == current) {
      instruments->setCurrentItem(item);
      instrumentName->setText(inst->GetName());
    }
  }
}

void MainWindow::unimplemented() {
  gui::promptUnimplemented(this);
}

void MainWindow::newDoc_cb(MainWindow *mw, void *) {
  mw->m_instrumenteditor->removedInstrument();
  gui::newDocument(true);
  mw->setDocumentName("");
  mw->updateDocument();
}

void MainWindow::open_cb(MainWindow *mw, void *data) {
  mw->m_instrumenteditor->removedInstrument();
  core::IO *io = (core::IO *)data;
  if (mw->m_app->openDocument(io, true)) {
    mw->updateDocument();
  }
  delete io;
}

void MainWindow::newDoc() {
  gui::stopSongConcurrent(newDoc_cb);
}

void MainWindow::open() {
  QString ftmpath = settings()->value(SETTINGS_FTMPATH).toString();
  QString path = QFileDialog::getOpenFileName(
      this, tr("Open"), ftmpath, tr("FamiTracker files (*.ftm);;All files (*.*)"), 0, 0);
  if (path.isEmpty()) return;

  openFile(path);
}
void MainWindow::openRecentFile() {
  QAction *action = qobject_cast<QAction *>(sender());
  if (action) {
    openFile(action->data().toString());
  }
}

void MainWindow::openFile(const QString &path) {
  QString ftmpath = QFileInfo(path).absoluteDir().absolutePath();
  settings()->setValue(SETTINGS_FTMPATH, ftmpath);

  core::FileIO *io = new core::FileIO(path.toLocal8Bit(), core::IO_READ);

  gui::stopSongConcurrent(open_cb, io);
  gui::addRecentFile(path);
  reloadRecentFiles();

  setDocumentName(QFileInfo(path).fileName());
  current_filename_ = path;
}
QString MainWindow::saveFileDialog(const QString &settingspath, const QString &filter) {
  const QString allFilesFilter = tr("All files (*.*)");
  QString selectedFilter;

  QString filetypepath = settings()->value(settingspath).toString();
  QString path = QFileDialog::getSaveFileName(this, tr("Save As"), filetypepath,
                                              filter + ";;" + allFilesFilter, &selectedFilter, 0);
  if (path.isEmpty()) return path;

  QFileInfo file(path);
  if (selectedFilter.compare(allFilesFilter) != 0) {
    // horrible, lame fix for no default suffixes in Linux
    if (file.suffix().isEmpty()) {
      // (*.EXT)
      // fixme, someday
      QString ext = selectedFilter.right(5).left(4);
      path += ext;
    }
  }
  filetypepath = file.absoluteDir().absolutePath();
  settings()->setValue(settingspath, filetypepath);

  return path;
}

void MainWindow::save() {
  if (current_filename_.isEmpty())
    saveAs();
  else
    DoSave(current_filename_);
}

void MainWindow::saveAs() {
  QString path = saveFileDialog(SETTINGS_FTMPATH, tr("FamiTracker files (*.ftm)"));
  if (path.isEmpty()) {
    return;
  }

  DoSave(path);
  current_filename_ = path;
}

void MainWindow::createwav_cb(MainWindow *mw, void *data) {
  core::FileIO *io = (core::FileIO *)data;

  QDialog *dialog = new QDialog(mw);
  dialog->exec();

  delete io;
}

void MainWindow::createWAV() {
  CreateWAVDialog *d = new CreateWAVDialog(this);
  if (d->exec() == QDialog::Accepted) {
    bool select_playCount = d->select_playCount->isChecked();
    int playCount, playSeconds;
    if (select_playCount) {
      // play the song a number of times
      playCount = d->playCount->value();
    } else {
      // play the song for an amount of time
      playSeconds = d->playForTime->time().minute() * 60 + d->playForTime->time().second();
    }

    gui::stopSongTrackerConcurrent();

    QString path = saveFileDialog(SETTINGS_WAVPATH, tr("WAV PCM files (*.wav)"));
    if (path.isEmpty()) return;

    core::FileIO *io = new core::FileIO(path.toLocal8Bit(), core::IO_WRITE);
    // io->write()

    gui::stopSongConcurrent(createwav_cb, io);
  }
}

void MainWindow::quit() {
  close();
}

void MainWindow::moduleProperties() {
  ModulePropertiesDialog *d = new ModulePropertiesDialog(this, m_app);
  if (d->exec() == QDialog::Accepted) {
  }
  delete d;

  updateDocument();
  m_app->reloadAudio();
}

void MainWindow::viewToolbar(bool v) {
  this->toolBar->setVisible(v);
}
void MainWindow::viewStatusBar(bool v) {
  this->statusbar->setVisible(v);
}
void MainWindow::viewControlpanel(bool v) {
  this->controlPanel->setVisible(v);
}
void MainWindow::controlPanelVisibilityChanged() {
  action_ViewControlpanel->blockSignals(true);
  action_ViewControlpanel->setChecked(controlPanel->isVisible());
  action_ViewControlpanel->blockSignals(false);
  viewControlpanel(controlPanel->isVisible());
}

void MainWindow::about() {
  AboutDialog *d = new AboutDialog(this);
  d->exec();
  delete d;
}

void MainWindow::setSong_mw_cb() {
  FtmDocument *d = m_dinfo->doc();
  int i = songs->currentIndex();

  d->lock();

  d->SelectTrack(i);

  speed->blockSignals(true);
  tempo->blockSignals(true);
  rows->blockSignals(true);
  frames->blockSignals(true);

  speed->setValue(d->GetSongSpeed());
  tempo->setValue(d->GetSongTempo());
  rows->setValue(d->GetPatternLength());
  frames->setValue(d->GetFrameCount());

  frames->blockSignals(false);
  rows->blockSignals(false);
  tempo->blockSignals(false);
  speed->blockSignals(false);

  d->unlock();

  m_dinfo->setCurrentChannel(0);
  m_dinfo->setCurrentFrame(0);
  m_dinfo->setCurrentRow(0);

  updateFrameChannel(true);
}

void MainWindow::setSong_cb(MainWindow *mw, void *) {
  mw->setSong_mw_cb();
}

void MainWindow::setSong(int i) {
  FtmDocument *d = m_dinfo->doc();

  if (d->GetSelectedTrack() == i) return;

  gui::stopSongTrackerConcurrent(setSong_cb, NULL);
}

void MainWindow::incrementPattern() {
  FtmDocument *doc = m_dinfo->doc();

  doc->lock();

  int current_frame = m_dinfo->currentFrame();
  int current_channel = m_dinfo->currentChannel();
  if (changeAll->checkState() == Qt::Checked) {
    for (int i = 0; i < doc->GetAvailableChannels(); i++) {
      doc->IncreasePattern(current_frame, i, 1);
    }
  } else {
    doc->IncreasePattern(current_frame, current_channel, 1);
  }

  doc->unlock();

  gui::updateFrameChannel(true);
}
void MainWindow::decrementPattern() {
  FtmDocument *doc = m_dinfo->doc();

  doc->lock();

  int current_frame = m_dinfo->currentFrame();
  int current_channel = m_dinfo->currentChannel();
  if (changeAll->checkState() == Qt::Checked) {
    for (int i = 0; i < doc->GetAvailableChannels(); i++) {
      doc->DecreasePattern(current_frame, i, 1);
    }
  } else {
    doc->DecreasePattern(current_frame, current_channel, 1);
  }

  doc->unlock();

  gui::updateFrameChannel(true);
}
void MainWindow::instrumentSelect() {
  QModelIndex idx = instruments->currentIndex();
  int i = idx.data(Qt::UserRole).value<int>();

  CInstrument *inst;

  FtmDocument *doc = m_dinfo->doc();
  {
    FtmDocument_lock_guard lock(doc);

    inst = doc->GetInstrument(i);
    if (inst == NULL) return;
    instrumentName->setText(inst->GetName());
  }

  m_dinfo->setCurrentInstrument(i);

  m_instrumenteditor->setInstrument(doc, inst);
}
void MainWindow::instrumentNameChange(QString s) {
  QModelIndex idx = instruments->currentIndex();
  if (idx.row() < 0) return;

  int i = idx.data(Qt::UserRole).value<int>();

  FtmDocument *doc = m_dinfo->doc();
  doc->lock();

  CInstrument *inst = doc->GetInstrument(i);
  inst->SetName(s.toLatin1());

  doc->unlock();

  setInstrumentName(instruments->currentItem(), idx.row(), s.toLatin1());
}
void MainWindow::instrumentDoubleClicked(QModelIndex) {
  m_instrumenteditor->show();
}

void MainWindow::speedTempoChange(int i) {
  FtmDocument *d = m_dinfo->doc();
  d->lock();

  d->SetSongSpeed(speed->value());
  d->SetSongTempo(tempo->value());

  d->unlock();
}
void MainWindow::rowsChange(int i) {
  FtmDocument *d = m_dinfo->doc();
  d->lock();

  d->SetPatternLength(i);

  d->unlock();

  gui::updateFrameChannel(true);
}
void MainWindow::framesChange(int i) {
  FtmDocument *d = m_dinfo->doc();
  d->lock();

  d->SetFrameCount(i);

  d->unlock();

  gui::updateFrameChannel(true);
}

void MainWindow::octaveChange() {
  m_dinfo->setCurrentOctave(octave->currentIndex());
}

void MainWindow::changeSongTitle() {
  FtmDocument *doc = m_dinfo->doc();
  FtmDocument_lock_guard lock(doc);
  doc->SetSongInfo(title->text().toLatin1(), doc->GetSongArtist(), doc->GetSongCopyright());
}
void MainWindow::changeSongAuthor() {
  FtmDocument *doc = m_dinfo->doc();
  FtmDocument_lock_guard lock(doc);
  doc->SetSongInfo(doc->GetSongName(), author->text().toLatin1(), doc->GetSongCopyright());
}
void MainWindow::changeSongCopyright() {
  FtmDocument *doc = m_dinfo->doc();
  FtmDocument_lock_guard lock(doc);
  doc->SetSongInfo(doc->GetSongName(), doc->GetSongArtist(), copyright->text().toLatin1());
}

void MainWindow::play() {
  gui::playSongConcurrent();
}
void MainWindow::stop() {
  gui::stopSongTrackerConcurrent();
}
void MainWindow::toggleEditMode() {
  gui::toggleEditMode();
}

void MainWindow::addInstrument(int chip) {
  FtmDocument *d = m_dinfo->doc();
  d->lock();
  int inst = d->AddInstrument("New instrument", chip);
  d->unlock();

  m_dinfo->setCurrentInstrument(inst);

  refreshInstruments();
  patternView->update(true);
}
void MainWindow::addInstrument_2A03() {
  addInstrument(SNDCHIP_NONE);
}
void MainWindow::addInstrument_VRC6() {
  addInstrument(SNDCHIP_VRC6);
}
void MainWindow::addInstrument_VRC7() {
  addInstrument(SNDCHIP_VRC7);
}
void MainWindow::addInstrument_MMC5() {
  addInstrument(SNDCHIP_MMC5);
}
void MainWindow::addInstrument_FDS() {
  addInstrument(SNDCHIP_FDS);
}
void MainWindow::removeInstrument() {
  FtmDocument *d = m_dinfo->doc();

  int inst = m_dinfo->currentInstrument();

  m_instrumenteditor->removedInstrument();

  d->lock();

  d->RemoveInstrument(inst);

  int ni = -1;

  for (int i = inst + 1; i < MAX_INSTRUMENTS; i++) {
    if (d->GetInstrument(i) != NULL) {
      ni = i;
      break;
    }
  }
  if (ni == -1) {
    for (int i = inst - 1; i >= 0; i--) {
      if (d->GetInstrument(i) != NULL) {
        ni = i;
        break;
      }
    }
  }
  if (ni == -1) {
    ni = 0;
  }

  d->unlock();

  m_dinfo->setCurrentInstrument(ni);

  refreshInstruments();
  patternView->update(true);
}
void MainWindow::editInstrument() {
  m_instrumenteditor->show();
}
void MainWindow::changeEditSettings() {
  m_dinfo->setEditStep(step->value());
  m_dinfo->setKeyRepetition(keyRepetition->checkState() == Qt::Checked);
}
}  // namespace gui
