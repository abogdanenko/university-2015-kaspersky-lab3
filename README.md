# Simple antivirus scanner
Check files for viruses using ClamAV database.

Authors: Alexey Bogdanenko, Kamil Khamitov

The program scans files and directories recursively, checks files MD5 signatures
in ClamAV database file. User specifies path, action (delete, ignore, etc) and
other settings in graphical interface.

The database must be provided in file *main.mdb* in plain text format.
