// Header for interaction with database
// Warning!
// Now you to copy default database file to location near your executable file
// Please keep sure you did it

#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <QFileInfo>
#include <QObject>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

#include <QCoreApplication>

class sqlitemanager : public QObject {
  Q_OBJECT
public:
  explicit sqlitemanager(QObject *parent = nullptr);

  bool writeResult(int score, size_t time);
signals:

public slots:
private:
  bool databaseExists(QString &path);
  bool createDB(QSqlDatabase *base);
  void ConnectionClose(QSqlDatabase *base);
  bool connectionOpen(QSqlDatabase *base);

  QString path;
};

#endif // SQLITEMANAGER_H
