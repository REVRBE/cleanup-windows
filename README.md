### cleanup-windows

Project aimed at cleaning certain stuff on a Windows system.

## What it cleans so far:

* Iconcache
* Thumbcache
* AppCompat Installs
* SharedFileCache

The iconcache & thumbcache are found in this folder path. We restart the explorer.exe right before we delete the files and therefore it's able to get those that were 'in use'.
```
%user_profile%\AppData\Local\Microsoft\Windows\Explorer
```

The AppCompat Installs folder are found here; it logs installed applications in .txt files; and we clean it by simply deleting the files.
```
C:\Windows\appcompat\Programs\Install
```

The SharedFileCache are found at this path; we delete the files in the folder.
```
C:\Windows\SoftwareDistribution\Download\SharedFileCache
```

I've been working on a project which heavily relied on research upon evidence of process execution and other ways to find traces of a program. Therefore I won't release everything right away; and we'll start of with the iconcache and thumbcache.

I'll be updating this source and release methods to clean registry, prefetch and other Windows components and services.
