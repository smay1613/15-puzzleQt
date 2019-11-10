#include "sqlitemanager.h"

sqlitemanager::sqlitemanager(QObject *parent) : QObject(parent) {
  path = QCoreApplication::applicationDirPath() + "/Gamedb.db";

  if (databaseExists(path)) {
    QSqlDatabase gameDB = QSqlDatabase::addDatabase("QSQLITE");
    gameDB.setDatabaseName(path);
    connectionOpen(&gameDB);
    createDB(&gameDB);
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
  query.bindValue(":time", static_cast<long long>(time));
  query.bindValue(":steps", score);
  return query.exec();
}

void sqlitemanager::ConnectionClose(QSqlDatabase *base) {
  base->close();
  base->removeDatabase(QSqlDatabase::defaultConnection);
}

bool sqlitemanager::databaseExists(QString &path) {
  QFileInfo check_file(path);
  // check if file exists and if yes: Is it really a file and no directory?
  if (check_file.exists() && check_file.isFile())
    qDebug() << "File exists";
  else
    qDebug() << "File doesnt exist: " << path;

  return (check_file.exists() && check_file.isFile());
}

bool sqlitemanager::createDB(QSqlDatabase *base) {
  auto *createTable = new QString(
      "CREATE TABLE IF NOT EXISTS score (`time` INTEGER NOT NULL , `steps` "
      "INTEGER NOT NULL ,  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT)");
  if (!base->open()) {
    qDebug() << "Error opening db: " << base->lastError().text();
  }
  if (!base->exec(*createTable).exec()) {
    qDebug() << "Error creating sell: " << base->lastError().text();
    delete createTable;
    return false;
  }
  delete createTable;

  return true;
}

bool sqlitemanager::connectionOpen(QSqlDatabase *base) {

  if (!base->open()) {
    qDebug() << "Error opening db: " << base->lastError().text();

  } else {
    // qDebug() << "Opened db";
    qDebug() << "Opened dbs: " << QSqlDatabase::connectionNames();
    base->exec("pragma journal_mode = wal;");
    return true;
  }
  return false;
}
