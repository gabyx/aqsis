; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Aqsis
AppVerName=Aqsis Renderer v0.6.4
AppPublisher=The Aqsis Team
AppPublisherURL=http://www.aqsis.com
AppSupportURL=http://www.aqsis.com
AppUpdatesURL=http://www.aqsis.com
DefaultDirName={pf}\Aqsis
DefaultGroupName=Aqsis
AllowNoIcons=true
LicenseFile=C:\Projects\Aqsis\renderer\COPYING
OutputBaseFilename=aqsis-setup
Compression=zip/9
AppVersion=0.6.4

[Tasks]
Name: desktopicon; Description: Create a &desktop icon; GroupDescription: Additional icons:

[Files]
Source: Library\Release\aqsis.exe; DestDir: {app}; CopyMode: normal
Source: Library\Release\tga2tif.dll; DestDir: {app}\procedures; CopyMode: normal
Source: Library\Release\aqslcomp.exe; DestDir: {app}; CopyMode: normal
Source: Library\Release\ddmsock.ini; DestDir: {app}\displays; CopyMode: normal
Source: Library\Release\filebuffer.exe; DestDir: {app}\displays; CopyMode: normal
Source: Library\Release\framebuffer_glut.exe; DestDir: {app}\displays; CopyMode: normal
Source: Library\Release\framebuffer_glut_z.exe; DestDir: {app}\displays; CopyMode: normal
Source: Library\Release\gif2tif.dll; DestDir: {app}\procedures; CopyMode: normal
Source: Library\Release\jpg2tif.dll; DestDir: {app}\procedures; CopyMode: normal
Source: Library\Release\pcx2tif.dll; DestDir: {app}\procedures; CopyMode: normal
Source: Library\Release\ppm2tif.dll; DestDir: {app}\procedures; CopyMode: normal
Source: Library\Release\shadowmap.exe; DestDir: {app}\displays; CopyMode: normal
Source: Library\Release\slpp.exe; DestDir: {app}; CopyMode: normal
Source: Library\Release\teqser.exe; DestDir: {app}; CopyMode: normal
Source: Library\Release\aqsl.exe; DestDir: {app}; CopyMode: normal
Source: shaders\*.sl; DestDir: {app}\shaders
Source: shaders\*.slx; DestDir: {app}\shaders
Source: ribfiles\*.rib; DestDir: {app}\examples
Source: NEWS; DestDir: {app}
Source: BUILD; DestDir: {app}
Source: ChangeLog; DestDir: {app}
Source: COPYING; DestDir: {app}
Source: INSTALL; DestDir: {app}
Source: AUTHORS; DestDir: {app}
Source: README; DestDir: {app}
Source: Library\Release\aqsltell.exe; DestDir: {app}

[Icons]
Name: {group}\Aqsis; Filename: {app}\aqsis.exe
Name: {group}\Uninstall Aqsis; Filename: {uninstallexe}
Name: {userdesktop}\Aqsis; Filename: {app}\aqsis.exe; Tasks: desktopicon

[_ISTool]
EnableISX=false

[Dirs]
Name: {app}\shaders
Name: {app}\examples
Name: {app}\displays
Name: {app}\procedures

[Registry]
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: AQSIS_BASE_PATH; ValueData: {app}; MinVersion: 0,4.0.1381
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: AQSIS_DISPLAYS_PATH; ValueData: {app}\displays; MinVersion: 0,4.0.1381
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: AQSIS_SHADERS_PATH; ValueData: {app}\shaders; MinVersion: 0,4.0.1381
