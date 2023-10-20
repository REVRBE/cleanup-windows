### cleanup-windows

Project aimed at cleaning certain stuff on a Windows system.

## What it cleans so far:

* Iconcache
* Thumbcache

The iconcache & thumbcache are found in this folder path. We restart the explorer.exe right before we delete the files and therefore it's able to get those that were 'in use'.
```
%user_profile%\AppData\Local\Microsoft\Windows\Explorer
```

I've been working on a project which heavily relied on research upon evidence of process execution and other ways to find traces of a program. Therefore I won't release everything right away; and we'll start of with the iconcache and thumbcache.

I'll be updating this source and release methods to clean registry, prefetch and other Windows components and services.
