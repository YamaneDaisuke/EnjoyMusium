dim arg, args, desktop, WshShell, WshShortcut

'CustomActionData�𕪉�
arg = Session.Property("CustomActionData")
args = Split(arg, ":::")

if args(2)="1" then
    set WshShell = CreateObject("WScript.Shell")
    '�f�X�N�g�b�v�̃p�X���擾
    if args(3)="1" then
        desktop = WshShell.SpecialFolders("AllUsersDesktop")
    else
        desktop = WshShell.SpecialFolders("Desktop")
    end if
    '�V���[�g�J�b�g���쐬
    On Error Resume Next
    set WshShortcut = _
        WshShell.CreateShortcut(desktop & "\" & args(1) & ".lnk")
    WshShortcut.TargetPath = args(0)
    WshShortcut.Save
end if
