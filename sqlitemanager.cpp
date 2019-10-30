#include "sqlitemanager.h"

sqlitemanager::sqlitemanager(QObject *parent) : QObject(parent) {
  path = QCoreApplication::applicationDirPath() + "/Gamedb.db";

  if (databaseExists(path)) {
    QSqlDatabase gameDB = QSqlDatabase::addDatabase("QSQLITE");
    gameDB.setDatabaseName(path);
    connectionOpen(&gameDB);
    createDB(&gameDB);
    // gameDB.close();
    // gameDB.removeDatabase();
    ConnectionClose(&gameDB);
  }
}

bool sqlitemanager::writeResult(int score, size_t time) {
  QSqlDatabase gameDB = QSqlDatabase::addDatabase("QSQLITE");
  gameDB.setDatabaseName(path);
  connectionOpen(&gameDB);
  QSqlQuery query(gameDB);
  query.prepare("INSERT INTO score (time, steps) "
                "VALUES (:time, :steps)");
  query.bindValue(":time", time);
  query.bindValue(":steps", score);
  if (query.exec()) {
    ConnectionClose(&gameDB);
    return true;
  } else {
    ConnectionClose(&gameDB);
    return false;
  }
}

void sqlitemanager::ConnectionClose(QSqlDatabase *base) {
  base->close();
  base->removeDatabase(QSqlDatabase::defaultConnection);
}

bool sqlitemanager::databaseExists(QString &path) {
  QFileInfo check_file(path);
  // check if file exists and if yes: Is it really a file and no directory?
  if (check_file.exists() && check_file.isFile()) {
    qDebug() << "File exists";
    return true;
  } else {
    qDebug() << "File doesnt exist: " << path;
    return false;
  }
}

bool sqlitemanager::createDB(QSqlDatabase *base) {
  QString *createTable = new QString(
      "CREATE TABLE IF NOT EXISTS score (`time` INTEGER NOT NULL , `steps` "
      "INTEGER NOT NULL ,  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT)");
  if (!base->open()) {
    qDebug() << "Error opening db: " << base->lastError().text();
  }
  if (!base->exec(*createTable).exec()) {
    qDebug() << "Error creating sell: " << base->lastError().text();
    delete createTable;
    return false;
  } else {
    delete createTable;
  }

  return true;
}

bool sqlitemanager::connectionOpen(QSqlDatabase *base) {
  QString path = QCoreApplication::applicationDirPath() + "/Gamedb.db";
  // gameDB=QSqlDatabase::addDatabase("QSQLITE");
  // mydb.setDatabaseName(path);
  if (!base->open()) {
    qDebug() << "Error opening db: " << base->lastError().text();
    return false;
  } else {
    // qDebug() << "Opened db";
    qDebug() << "Opened dbs: " << QSqlDatabase::connectionNames();
    base->exec("pragma journal_mode = wal;");
  }
  return true;
}
