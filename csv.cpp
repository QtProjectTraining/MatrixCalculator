#include "csv.h"

CSVParser::CSVParser(){
    this->seperator = QString(",");
}

CSVParser::CSVParser(QString sep){
    this->seperator = sep;
}

QList<QStringList> CSVParser::read(QString filename){
    QFile file(filename);
    QString line;
    if(file.open(QFile::QIODevice::ReadOnly)){
        QTextStream stream(&file);
        while(!stream.atEnd()){
            line = stream.readLine();
            this->csvLines.append(line.split(this->seperator));
        }
        file.close();
    }
    return this->csvLines;
}

int CSVParser::write(QString filename, QList<QStringList> lines){
    QFile file(filename);
    QStringList line;
    if(file.open(QFile::QIODevice::WriteOnly)){
        QTextStream stream(&file);
        for(int i=0;i<lines.size();i++){
            line = lines[i];
            stream << line.join(this->seperator)<<"\n";
        }
        file.close();
        return 1;
    }
    return 0;
}
