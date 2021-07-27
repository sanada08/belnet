
#include <QApplication>
#include <QMessageBox>
#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>

int uninstall();

int main(int argc, char * argv[])
{
  QApplication app{argc, argv};
  if(QMessageBox::question(nullptr, "Belnet Uninstaller", "Do You want to uninstall Belnet?",
                        QMessageBox::Yes|QMessageBox::No)
     == QMessageBox::Yes)
  {
    QMessageBox msgBox;
    const auto  retcode = uninstall();
    if(retcode == 0)
    {
      msgBox.setText("Belnet has been successfully uninstalled, you may now remove the uninstaller if you wish.");
    }
    else
    {
      msgBox.setText("Failed to uninstall belnet");
    }
    msgBox.exec();
  }
  return 0;
}

int uninstall()
{
  AuthorizationRef authorizationRef;
  OSStatus status;
  
  status = AuthorizationCreate(nullptr, kAuthorizationEmptyEnvironment, kAuthorizationFlagDefaults, &authorizationRef);
  if(status != 0)
    return status;
  char* tool = "/bin/sh";
  char* args[] = {"/opt/belnet/bin/belnet_uninstall.sh", nullptr};
  FILE* pipe = stdout;
  
  return AuthorizationExecuteWithPrivileges(authorizationRef, tool, kAuthorizationFlagDefaults, args, &pipe);
}

