#include "pre_headers.h"

QString get_unique_filename(QString filename, bool allow_empty)
{
  int i = 0;
  if(filename.isEmpty())
    filename = FILE_NAME EXT;

  QFileInfo fi(filename);

  while( fi.exists() )
  {
    if(allow_empty)
      if( fi.size() == 0 )  // jeśli plik pusty, to nadpisz
        break;
    i++;
    QRegularExpression re("(\\d*)");
    filename = "";
    if ( !fi.path().isEmpty() && fi.path() != ".")
        filename = fi.path() + "/";
    filename += fi.completeBaseName().replace(re, "") + QVariant(i).toString() + "." + fi.completeSuffix();
    fi.setFile(filename);
  }
  return filename;
}


