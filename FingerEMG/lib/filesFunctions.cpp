#ifndef FILESFUNCTIONS_CPP
#define FILESFUNCTIONS_CPP

#include "pre_headers.h"

//#define MATLAB     "../matlab/"
//#define FILE_NAME  "out"
//#define EXT        ".wav"

inline QString get_unique_filename(QString filename, bool overide_empty_files_true = true)
{
  int i = 0;
  if(filename.isEmpty())
    filename = MATLAB FILE_NAME EXT;

  QFileInfo fi(filename);

  while( fi.exists() )
  {
    if(overide_empty_files_true)
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

inline void showFileInFolder(const QString &path)
{
    #ifdef _WIN32    //Code for Windows
        QProcess::startDetached("explorer.exe", {"/select,", QDir::toNativeSeparators(path)});
    #elif defined(__APPLE__)    //Code for Mac
        QProcess::execute("/usr/bin/osascript", {"-e", "tell application \"Finder\" to reveal POSIX file \"" + path + "\""});
        QProcess::execute("/usr/bin/osascript", {"-e", "tell application \"Finder\" to activate"});
    #elif defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
        if (QFileInfo(path).exists()) {
            QProcess proc;
            QString output;
            proc.start("xdg-mime", QStringList() << "query" << "default" << "inode/directory");
            proc.waitForFinished();
            output = proc.readLine().simplified();
            if (output == "dolphin.desktop" || output == "org.kde.dolphin.desktop")
                proc.startDetached("dolphin", QStringList() << "--select" << Utils::Fs::toNativePath(path));
            else if (output == "nautilus.desktop" || output == "org.gnome.Nautilus.desktop"
                     || output == "nautilus-folder-handler.desktop")
                proc.startDetached("nautilus", QStringList() << "--no-desktop" << Utils::Fs::toNativePath(path));
            else if (output == "caja-folder-handler.desktop")
                proc.startDetached("caja", QStringList() << "--no-desktop" << Utils::Fs::toNativePath(path));
            else if (output == "nemo.desktop")
                proc.startDetached("nemo", QStringList() << "--no-desktop" << Utils::Fs::toNativePath(path));
            else if (output == "kfmclient_dir.desktop")
                proc.startDetached("konqueror", QStringList() << "--select" << Utils::Fs::toNativePath(path));
            else
                openPath(path.left(path.lastIndexOf("/")));
        }
        else {
            // If the item to select doesn't exist, try to open its parent
            openPath(path.left(path.lastIndexOf("/")));
        }
    #else
        openPath(path.left(path.lastIndexOf("/")));
    #endif
}

#endif
