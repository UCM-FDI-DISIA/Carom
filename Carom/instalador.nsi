OutFile "CaromInstaller.exe"
InstallDir "$PROGRAMFILES\Carom"
InstallDirRegKey HKCU "Software\Carom" "Install_Dir"
RequestExecutionLevel admin
Icon "Carom.ico"

!include nsDialogs.nsh
!include LogicLib.nsh
!include FileFunc.nsh
!insertmacro GetParameters

Page directory
Page custom CustomShortcutsPage
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Var SHORTCUT_DESKTOP
Var CHECKBOX_ID

Function CustomShortcutsPage
  nsDialogs::Create 1018
  Pop $0

  StrCpy $SHORTCUT_DESKTOP "1"

  ${NSD_CreateCheckbox} 0u 0u 100% 12u "Crear acceso directo en el escritorio"
  Pop $CHECKBOX_ID
  ${NSD_SetState} $CHECKBOX_ID ${BST_CHECKED}
  ${NSD_OnClick} $CHECKBOX_ID OnDesktopCheckboxClicked

  nsDialogs::Show
FunctionEnd

Function OnDesktopCheckboxClicked
  ${NSD_GetState} $CHECKBOX_ID $0
  StrCpy $SHORTCUT_DESKTOP "$0"
FunctionEnd

Section "Instalar"

  SetOutPath "$INSTDIR"
  WriteRegStr HKCU "Software\Carom" "Install_Dir" "$INSTDIR"

  # Copiar archivos
  SetOutPath "$INSTDIR\bin"
  File /r "bin\*.*"

  SetOutPath "$INSTDIR\resources"
  File /r "resources\*.*"

  SetOutPath "$INSTDIR"
  File "Carom.ico"

  # Crear acceso directo en escritorio si se marcó
  StrCmp $SHORTCUT_DESKTOP "1" 0 +2
    SetOutPath "$INSTDIR\bin\Release"
    CreateShortcut "$DESKTOP\Carom.lnk" "$INSTDIR\bin\Release\Carom.exe" "" "$INSTDIR\Carom.ico" 0 

  # Crear acceso en el menú inicio para desinstalar
  CreateDirectory "$SMPROGRAMS\Carom"
  CreateShortCut "$SMPROGRAMS\Carom\Desinstalar.lnk" "$INSTDIR\CaromUninstaller.exe"

  # Escribir el desinstalador
  WriteUninstaller "$INSTDIR\CaromUninstaller.exe"

  # Agregar entrada a "Agregar o quitar programas"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Carom" "DisplayName" "Carom"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Carom" "UninstallString" "$INSTDIR\CaromUninstaller.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Carom" "InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Carom" "DisplayIcon" "$INSTDIR\Carom.ico"
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Carom" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Carom" "NoRepair" 1

SectionEnd

Section "Uninstall"

  # Eliminar accesos directos
  Delete "$DESKTOP\Carom.lnk"
  Delete "$SMPROGRAMS\Carom\Desinstalar.lnk"
  RMDir "$SMPROGRAMS\Carom"

  # Borrar archivos
  RMDir /r "$INSTDIR\bin"
  RMDir /r "$INSTDIR\resources"
  Delete "$INSTDIR\Carom.ico"
  Delete "$INSTDIR\CaromUninstaller.exe"

  # Eliminar carpeta raíz si está vacía
  RMDir "$INSTDIR"

  # Eliminar claves del registro
  DeleteRegKey HKCU "Software\Carom"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Carom"

SectionEnd