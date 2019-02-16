#ifndef FINDFILE_H
#define FINDFILE_H

#include <QObject>
#include <qtconcurrentmap.h>
#include <QApplication>
#include <QList>
#include <QMap>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QTime>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

class FindFile : public QObject
{
    Q_OBJECT
public:
    explicit FindFile(QObject *parent = 0);

    typedef QMap< QString, int> WordCount;

    QStringList findFiles(const QString &startDir, QStringList filters);

    WordCount singleThreadedWordCount(QStringList files);

    WordCount countWords(const QString &file);

    void reduce(WordCount &result, const WordCount &w);

signals:

public slots:

private:

};

#endif // FINDFILE_H
