### cleanup-windows

Project aimed at cleaning certain stuff on a Windows system.

## What it cleans so far:

* Iconcache
* Thumbcache
* AppCompat Installs
* SharedFileCache
* CrashDumps

The iconcache & thumbcache are found in this folder path. We restart the explorer.exe right before we delete the files and therefore it's able to get those that were 'in use'.
```
C:\Users\%user_profile%\AppData\Local\Microsoft\Windows\Explorer
```

The AppCompat Installs folder are found here; it logs installed applications in .txt files; and we clean it by simply deleting the files.
```
C:\Windows\appcompat\Programs\Install
```

The SharedFileCache are found at this path; we delete the files in the folder.
```
C:\Windows\SoftwareDistribution\Download\SharedFileCache
```

The CrashDumps are found here; the files contain process names of the crash dump data as the file name. We delete the files as they're not needed.
```
C:\Users\%user_profile%\AppData\Local\CrashDumps
```

I've been working on a project which heavily relied on research upon evidence of process execution and other ways to find traces of a program. Therefore I won't release everything right away; and we'll start of with a few simple ones.

I'll be updating this source and release methods to clean registry, prefetch and other Windows components and services.
