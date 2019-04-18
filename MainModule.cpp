#include "MainModule.h"

MainModule::MainModule(QObject *parent) : QObject(parent)
{

    m_mainmodule = new QProcess(this);
    m_processMainId = 0;
    m_updatestatus = 0;
    QObject::connect(this, SIGNAL(SIG_StartMainModule()), this, SLOT(SLOT_StartMainModule()));
    QObject::connect(m_mainmodule, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SLOT_MainModuleFinished(int,QProcess::ExitStatus)));

}

void MainModule::SLOT_StartMainModule()
{

    qDebug() << "1 MainModule::SLOT_StartMainModule()";
    m_updatestatus = 0;
    QString filePath(IVFDMAIN_EXE);
    QFile file(filePath);
    if(!file.exists())
    {
        qDebug() << "1 no such a file to exec";
        return;
    }
    QStringList m_processargs;
    m_processargs << "1" << "1" << "1" << "1" << "&";
    m_mainmodule->start(IVFDMAIN_EXE, m_processargs);
    m_processMainId = m_mainmodule->processId();

    qDebug() << "1 m_mainmodule->start the id is:" << m_processMainId;

}

void MainModule::SLOT_RestartMainModule()
{
    if(m_mainmodule->state() == QProcess::Running)
    {
        m_mainmodule->terminate();
    }
    if(m_mainmodule != NULL)
    {
        emit SIG_StartMainModule();
    }
}

void MainModule::SLOT_MainModuleFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "1 MainModule::SLOT_MainModuleFinished";
    qDebug() << exitCode;
    qDebug() << exitStatus;
    qDebug() << "m_updatestatus=" << m_updatestatus;
    if(exitStatus == QProcess::CrashExit)
    {
//        qDebug() << "1 Dip process crashed";
//        QLog_("survey", InfoLevel, QString("MainModule process crashed!"));
        if(m_updatestatus == 0){//m_updatestatus == 1 means now are updating program,no need to restart
            emit SIG_StartMainModule();
        }
    }else{
//        qDebug() << "1 Dip process exit in normal.";
//        QLog_("survey", InfoLevel, QString("MainModule process exit in normal!"));
        if(m_updatestatus == 0){
            emit SIG_StartMainModule();
        }
    }

}
