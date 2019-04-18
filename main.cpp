#include <QCoreApplication>
#include "IVFDDriver.h"
#include <QDebug>
#include <QSettings>
#include <QProcess>
#include <QVariant>
#include <QThread>
#include <QReadWriteLock>

#include "MainModule.h"

QReadWriteLock lock;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //check the request flag of update mainmodule

    QVariant keyval;
    GetCFG(MAINMODULE_INI, "update", "update", &keyval);

    int val = keyval.toInt();

    if(val == 1){
        qDebug() << "need to update!";
        QFile newfile(NEWFILE);
        if(newfile.exists()){
            QProcess copynewfile;
            copynewfile.start(UPDATEIVFDMAIN_SH);
            copynewfile.waitForFinished();
            copynewfile.close();
            qDebug() << "copynewfile  start success!";

            QThread::msleep(1000);
        }else{
            qDebug() << "no update file exists!";
        }
        modifyInitFile(MAINMODULE_INI, "update=", "update=0", lock);

    }else if(val == 0){
        qDebug() << "no update!";
    }
    //beging to start mainmodule
    MainModule *m = new MainModule(0);
    m->SIG_StartMainModule();

    gpio_export(GPIO_OUTBUZZ);
    gpio_direction(GPIO_OUTBUZZ, 1);
    gpio_write(GPIO_OUTBUZZ, 1);//buzzer
    QThread::msleep(1000);
    gpio_write(GPIO_OUTBUZZ, 0);//silence
    return a.exec();
}

