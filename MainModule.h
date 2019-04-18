#ifndef MAINMODULE_H
#define MAINMODULE_H

#include <QObject>
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include "IVFDDriver.h"

class MainModule : public QObject
{
    Q_OBJECT
public:
    explicit MainModule(QObject *parent = 0);
    QProcess *m_mainmodule;
    int m_processMainId;
    int m_updatestatus;

signals:
    void SIG_StartMainModule();
    void SIG_RestartMainModule();
public slots:
    void SLOT_StartMainModule();
    void SLOT_RestartMainModule();
    void SLOT_MainModuleFinished(int exitCode, QProcess::ExitStatus exitStatus);

};

#endif // MAINMODULE_H
