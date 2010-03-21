
// Qt includes
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QFile>
#include <QStringList>

// ctkDICOM includes
#include "ctkDICOM.h"

// STD includes
#include <iostream>

//----------------------------------------------------------------------------
class ctkDICOMPrivate: public qCTKPrivate<ctkDICOM>
{
public:
  ctkDICOMPrivate(); 
  bool executeScript(const QString& script);

  QSqlDatabase  Database;
  QString       DatabaseFileName;
  QString       LastError;
};

//----------------------------------------------------------------------------
// ctkDICOMPrivate methods

//------------------------------------------------------------------------------
ctkDICOMPrivate::ctkDICOMPrivate()
{
}

//----------------------------------------------------------------------------
// ctkDICOMWidget methods

//------------------------------------------------------------------------------
ctkDICOM::ctkDICOM(QObject* _parent): Superclass(_parent)
{
  QCTK_INIT_PRIVATE(ctkDICOM);
}

//----------------------------------------------------------------------------
ctkDICOM::~ctkDICOM()
{
}

//----------------------------------------------------------------------------
bool ctkDICOM::openDatabase(const QString& databaseFileName)
{
  QCTK_D(ctkDICOM);
  d->Database = QSqlDatabase::addDatabase("QSQLITE","DICOM-DB");
  d->Database.setDatabaseName(databaseFileName);
  if ( ! (d->Database.open()) )
    {
    d->LastError = d->Database.lastError().text();
    return false;
    }
  if ( d->Database.tables().empty() ) 
    {
    initializeDatabase();
    }
  return true;
}

//------------------------------------------------------------------------------
const QString& ctkDICOM::GetLastError() const {
  QCTK_D(const ctkDICOM);
  return d->LastError; 
}

//------------------------------------------------------------------------------
const QSqlDatabase& ctkDICOM::database() const {
  QCTK_D(const ctkDICOM);
  return d->Database;
}

//------------------------------------------------------------------------------
bool ctkDICOMPrivate::executeScript(const QString& script) {
  QFile scriptFile(script);
  scriptFile.open(QIODevice::ReadOnly);
  if  ( !scriptFile.isOpen() )
    {
    qDebug() << "Script file " << script << " could not be opened!\n";
    return false;
    }

  QString sqlCommands( QTextStream(&scriptFile).readAll() );
  sqlCommands.replace( '\n', ' ' );
  sqlCommands.replace("; ", ";\n");

  QStringList sqlCommandsLines = sqlCommands.split('\n');

  QSqlQuery query(Database);

  for (QStringList::iterator it = sqlCommandsLines.begin(); it != sqlCommandsLines.end()-1; ++it)
  {
    if (! (*it).startsWith("--") )
      {
      query.exec(*it);
      if (query.lastError().type())
        {
        qDebug() << "There was an error during execution of the statement: " << (*it);
        qDebug() << "Error message: " << query.lastError().text();
        return false;
        }
      }
  }
  return true;
}

//------------------------------------------------------------------------------
bool ctkDICOM::initializeDatabase(const char* sqlFileName)
{
  QCTK_D(ctkDICOM);
  return d->executeScript(sqlFileName);
}

//------------------------------------------------------------------------------
void ctkDICOM::closeDatabase()
{
  QCTK_D(ctkDICOM);
  d->Database.close();
}