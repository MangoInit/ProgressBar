#include "findfile.h"

using namespace QtConcurrent;

FindFile::FindFile(QObject *parent) : QObject(parent)
{

    qDebug() << "finding files...";
    QStringList files = findFiles("../../", QStringList() << "*.cpp");
    qDebug() << files.count() << "files";

    int singleThreadTime = 0;
    {
        QTime time;
        time.start();
        //单线程统计，与mapreduce机制实现的作对比
        WordCount total = singleThreadedWordCount(files);
        singleThreadTime = time.elapsed();
        //打印出所耗费的时间
        qDebug() << "single thread" << singleThreadTime;
    }

    int mapReduceTime = 0;
    {
        QTime time;
        time.start();
        //mappedReduced方式进行统计
//        WordCount total = mappedReduced(files, countWords, reduce);
        mapReduceTime = time.elapsed();
        qDebug() << "MapReduce" << mapReduceTime;
    }
    //输出mappedReduced方式比单线程处理方式要快的倍数
    qDebug() << "MapReduce speedup x" << ((double)singleThreadTime - (double)mapReduceTime)/(double)mapReduceTime +1;
}

//递归搜索文件
QStringList FindFile::findFiles(const QString &startDir, QStringList filters)
{
    QStringList names;
    QDir dir(startDir);

    foreach(QString file, dir.entryList(filters, QDir::Files))
        names += startDir + '/' +file;
    foreach(QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
        names += findFiles(startDir + '/' + subdir, filters);
    return names;
}

//单线程单词计数器函数
FindFile::WordCount FindFile::singleThreadedWordCount(QStringList files)
{
    WordCount wordCount;
    foreach(QString file, files)
    {
        QFile f(file);
        f.open(QIODevice::ReadOnly);
        QTextStream textStream(&f);
        while(textStream.atEnd() == false)
            foreach(const QString &word, textStream.readLine().split(' '))
                wordCount[word] +=1;
    }
    return wordCount;
}

//coutWords计算单个文件单词数，该函数由多个线程并调用，并且必须是线程安全的
FindFile::WordCount FindFile::countWords(const QString &file)
{
    QFile f(file);
    f.open(QIODevice::ReadOnly);
    QTextStream textStream(&f);
    WordCount wordCount;

    while(textStream.atEnd() == false)
        foreach (const QString &word, textStream.readLine().split(' '))
            wordCount[word] +=1;
    return wordCount;
}

//reduce将map的结果添加到最终结果，该函数只能由一个线程一次调用
void FindFile::reduce(FindFile::WordCount &result, const FindFile::WordCount &w)
{
    QMapIterator<QString, int> i(w);
    while(i.hasNext())
    {
        i.next();
        result[i.key()] += i.value();
    }
}

