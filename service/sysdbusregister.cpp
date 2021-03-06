#include "sysdbusregister.h"

SysDbusRegister::SysDbusRegister()
{

}

SysDbusRegister::~SysDbusRegister()
{

}

int SysDbusRegister::exitService()
{
    qApp->exit(0);
    return 0;
}

QString SysDbusRegister::writeKeyFile(QString devAddress, QString devName)
{
    if(devAddress.isNull())
        return QString("Address can not be empty ! ! !");
    if(devName.isNull())
        return QString("Name can not be empty ! ! !");
    if(devAddress.at(2) != ":" ||
       devAddress.at(5) != ":" ||
       devAddress.at(8) != ":" ||
       devAddress.at(11) != ":" ||
       devAddress.at(14) != ":")
        return QString("arg0 is not an address ! ! !");


    if(!QFile::exists(LIST_PATH)){
        QFile file(LIST_PATH);
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    GKeyFile *key_file = nullptr;
    key_file = g_key_file_new();
    char *data;
    gsize length = 0;
    g_key_file_load_from_file(key_file,QString(LIST_PATH).toStdString().c_str(),G_KEY_FILE_NONE,NULL);
    g_key_file_set_string(key_file,devAddress.toStdString().c_str(),"Name",devName.toStdString().c_str());
    g_key_file_set_string(key_file,devAddress.toStdString().c_str(),"ConnectTime",QString::number(QDateTime::currentMSecsSinceEpoch() / 1000).toStdString().c_str());


    data = g_key_file_to_data(key_file,&length,NULL);
    g_file_set_contents(QString(LIST_PATH).toStdString().c_str(),data,length,NULL);
    g_free(data);

    g_key_file_free(key_file);

    return QString("Key write ok!!!");
}

QString SysDbusRegister::getKeyFilePath()
{
    return QString(LIST_PATH);
}


