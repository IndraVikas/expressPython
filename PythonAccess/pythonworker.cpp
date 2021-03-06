#include "PythonAccess/emb.h"
#include "pythonworker.h"

PythonWorker::PythonWorker(QObject *parent) : QObject(parent) {}

void PythonWorker::RunPython(const QString &startme, const QString &code) {
  emit StartPythonRun();
  PyImport_AppendInittab("emb", emb::PyInitEmbConnect);
  PyImport_AppendInittab("express_api", emb::PyInitApiConnection);
  Py_Initialize();
  PyImport_ImportModule("emb");

  emb::StdOutWriteType write = [this](std::string s) {
    emit this->WriteOutput(QString::fromStdString(s));
  };

  emb::SetStdout(write);
  PyRun_SimpleString(startme.toStdString().c_str());
  PyRun_SimpleString(code.toStdString().c_str());
  emb::ResetStdOut();
  Py_Finalize();
  emit EndPythonRun();
}
