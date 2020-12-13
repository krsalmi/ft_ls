# FT_LS, recoding the Unix command ls
 In this project, the objective was to recode the shell command ls that lists directory contents of files and directories.  
 For my ft_ls, I recoded the the following options: `-a` (to list hidden files), `-t` (sort by time and date), `-r` (list in reverse order), `-R` (list directories recursively), `-l` (show file or directory, size, modified date and time, file or folder name and owner of file and its permission), and as a bonus, `-G` (add colors to the to the file names according to file type). As a bonus, I also handled the listing of ACL and extended attributes.
 The list of funtions we were allowed to use for this project is as follows: 
```
◦ write
◦ opendir
◦ readdir
◦ closedir
◦ stat
◦ lstat
◦ getpwuid
◦ getgrgid
◦ listxattr
◦ getxattr
◦ time
◦ ctime
◦ readlink
◦ malloc
◦ free
◦ perror
◦ strerror
◦ exit
```
In this project, I have used my function [ft_printf](https://github.com/krsalmi/ft_printf) for printing and [libft](https://github.com/krsalmi/libft) as my library.  
To test this program, run `make all` to compile the program and then run `./ft_ls` as you would `ls` with or without options.

 ## Remarks on this project
One of the most challenging parts of this project, was the recoding of the `-R` option, which recursively lists sub-directories encountered. I decided to save most of the information concerning each file into a lopsided binary tree -like data structure, where the contents of one directory are joined like a string of pearls by their left nodes, and any sub-directory by the right node and again, the contents of that directory by their left nodes. One of the pros of this kind of an approach is that all the information is at hand all the time. A serious con, however, is that the program uses a huge amount of memory before actually printing anything. I coded this program back in April 2020, but if I were to write this project now, I would choose to save the contents of a directory into a linked list, whose contents I could print out immediately and then free.