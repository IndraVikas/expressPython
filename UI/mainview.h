#ifndef MAINVIEW_H
#define MAINVIEW_H
#define APP_NAME "Express Python"

//#include <cmath>
//#include "Python.h"

// fremework
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QMainWindow>
#include <QInputDialog>
#include <QThread>
#include <QApplication>
// internal
#include "CodeEditor/pythonsyntaxhighlighter.h"
#include "CodeEditor/codeeditor.h"
#include "Features/snippets.h"

#define SAVE_STATE_VERSION 1
#define KEY_DOCK_LOCATIONS "DOCK_LOCATIONS"
#define KEY_GEOMETRY "GEOMETRY"
#define KEY_INPUTBOX "INPUTBOX"
#define KEY_CODEBOX "CODEBOX"
#define KEY_OUTPUTBOX "OUTPUTBOX"
#define KEY_SNIPPETBOX "SNIPPETBOX"
#define KEY_FONT "FONT"
#define KEY_FONTSIZE "FONTSIZE"

#define STARTUP_SCRIPT_FILE                                                    \
  QApplication::applicationDirPath() + "/_express_startup_.py"

namespace Ui {
class MainView;
}

class MainView : public QMainWindow {

  Q_OBJECT

public:
  explicit MainView(QWidget *parent = 0);
  ~MainView();
  QString GetInput();
  QString GetOutput();
  QString GetCode();
  void SetSnippets(Snippets *snip);
private slots:
  void on_btnRun_clicked();
  void on_fntCombo_currentFontChanged(const QFont &font);
  void on_cmbFontSize_currentIndexChanged(const QString &fontSize);
  void on_btnCodeClear_clicked();
  void on_btnInputClear_clicked();
  void on_btnOutputClear_clicked();
  void on_btnOutputOpen_clicked();
  void on_btnInputOpen_clicked();
  void on_btnCodeOpen_clicked();
  void on_btnOutputSave_clicked();
  void on_btnInputSave_clicked();
  void on_btnCodeSave_clicked();
  void on_btnCodeDatabase_clicked();
  void on_btnRunSnippet_clicked();
  void on_btnLoadSnippet_clicked();
  void on_btnRemoveSnippet_clicked();
  void on_btnAddSnippet_clicked();
  void on_btnAbout_clicked();
  void on_btnUpdateSnippet_clicked();
  void on_btnSnippetClear_clicked();
  void on_btnSnippetSave_clicked();
  void on_btnSnippetOpen_clicked();
  void on_btnRunSnippetFromCombo_clicked();
  void SetInput(QString txt);
  void SetOutput(QString txt);
  void SetCode(QString txt);
  void SetSearchRegex(QString txt);
  void WriteOutput(QString output);
  void StartPythonRun();
  void EndPythonRun();

private:
  const QString FILETYPES_PYTHON = tr("Python Code (*.py);;All files (*.*)");
  const QString FILETYPES_OTHER = tr("Text files (*.txt);;All files (*.*)");
  QThread m_workerThread;
  Ui::MainView *ui;
  PythonSyntaxHighlighter *m_highlighterCodeArea;
  PythonSyntaxHighlighter *m_highlighterSnippetArea;
  QString m_startMe;
  QString m_about;
  Snippets *m_snippets;
  QCompleter *completer;
  void ChangeFontSize(QFont font, int size);
  void SetupHighlighter();
  void SaveFile(CodeEditor *codeEditor, const bool isPython = false);
  void BrowseAndLoadFile(CodeEditor *codeEditor, const bool isPython = false);
  QString LoadFile(const QString &fileName, bool &success,
                   const bool showMessage = true);
  void LoadResources();
  void LoadSnippetsToCombo();
  void RunPythonCode(const QString &code);
  void LoadSettings();
  void SetupPython();
  bool Confirm(const QString &what);
  void SetCompleter(CodeEditor *editor);

signals:
  void operate(const QString &, const QString &);
};

#endif // MAINVIEW_H
