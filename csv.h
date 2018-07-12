#ifndef CSV_H
#define CSV_H

#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QList>
#include <QFile>


class CSVParser
{
    QList<QStringList> csvLines;
    QString seperator;
public:
    CSVParser();
    CSVParser(QString sep);
    QList<QStringList> read(QString filename);
    int write(QString filename, QList<QStringList> lines);

};

#endif // CSV_H

