dim arg, args, desktop, path, WshShell, fso

'CustomActionData�𕪉�
arg = Session.Property("CustomActionData")
args = Split(arg, ":::")

'�f�X�N�g�b�v�̃p�X���擾
set WshShell = CreateObject("WScript.Shell")
if args(1)="1" then
    desktop = WshShell.SpecialFolders("AllUsersDesktop")
else
    desktop = WshShell.SpecialFolders("Desktop")
end if
'�폜����t�@�C���̃p�X
path = desktop & "\" & args(0) & ".lnk"
'�V���[�g�J�b�g���폜
set fso = CreateObject("Scripting.FileSystemObject")
if (fso.FileExists(path)) then
    On Error Resume Next
    fso.DeleteFile(path)
end if
