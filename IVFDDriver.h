#ifndef IVFDDRIVER_H
#define IVFDDRIVER_H


#include <QThread>
#include <QString>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include <QSettings>
#include <QList>
#include <QVariant>
#include <QByteArray>
#include <QReadWriteLock>

#define GPIO_TEST 1
#define GPIO_SDCDPIN 238 //PH14 sd cd pin
#define GPIO_OUTLED1 237 //PH13 YELLOW
#define GPIO_OUTLED2 239 //PH15 GREEN
#define GPIO_OUTLED3 240 //PH16 RED
#define GPIO_OUTBUZZ 244 //PH20

#define GPIO_RELAYOUT1 241 //PH17
#define GPIO_RELAYOUT2 242 //PH18VENT, TOOLIGHT, TOODARK, FIREDET, VLOST};



#define MAINMODULE_INI "/mainmodule.ini"
#define NEWFILE "/ftproot/IVFDMain"
#define UPDATEIVFDMAIN_SH "/updateivfdmain.sh"
#define IVFDMAIN_EXE "/IVFDMain"
//#define MAINMODULE_INI "/data/mainmodule.ini"
//#define NEWFILE "/data/ftproot/IVFDMain"
//#define UPDATEIVFDMAIN_SH "/data/updateivfdmain.sh"
//#define IVFDMAIN_EXE "/data/IVFDMain"

enum GPIOTERM{RED, GREEN, YELLOW, RELAY1, RELAY2, BUZZER};
enum GPIOSTATUS{ON, OFF, FLASH};

typedef struct CmdActiveX{
    int cmdtype;
    int cmdval;
    char cmdstr[128];
}CmdActiveX;


int gpio_export(int pin);
int gpio_unexport(int pin);

int gpio_direction(int pin, int dir);
int gpio_write(int pin, int value);
int gpio_read(int pin);
int gpio_edge(int pin, int edge);
int gpio_test();
void gpio_setstate(int pinnum, int derection, int val);


int InitFileExist(QString filepath);
int modifyAutoRunFile(QString filename, QString findstr, QString altstr);
int modifyInitFile(QString filename, QString findstr, QString altstr, QReadWriteLock &lock);
int GetCFG(QString filename, QString mainkey, QString subkey, QVariant *subkeyval);
QString Get_NetMask();
QString Get_HostIpAddress();
QString Get_LocalMachine();
int SetEnviroment(QString mainkey, QString subkey, QVariant subkeyval);
int GetEnviroment(QString mainkey, QString subkey, QVariant *subkeyval);

int ConvertMsgToByteArray(QByteArray *bytearray);

void ControlGPIODev(int dev, enum GPIOSTATUS state, int ms, int cnt);
#endif // IVFDDRIVER_H

