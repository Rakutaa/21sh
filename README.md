# 42-21sh
Hive Helsinki project. **WIP**

**Compilation**

Clone repository and compile the program into your current working directory with the following commands:  
$ `git clone https://github.com/vkuokka/42-21sh.git 21sh`   
$ `make`  
Now you should have binary file inside the repository which you can run with the following command:  
$ `./21sh`  
  
**Keybindings**

| KEY  | FUNCTION |
| ------------- | ------------- |
| <kbd>right</kbd> | Move cursor right. |
| <kbd>left</kbd> | Move cursor left. |
| <kbd>ctrl+right</kbd> | Jump to the beginning of a word. |
| <kbd>ctrl+left</kbd> | Jump to the beginning of a word. |
| <kbd>ctrl+up</kbd> | Jump one line up. |
| <kbd>ctrl+down</kbd> | Jump one line down. |
| <kbd>up</kbd> | Navigate command history. |
| <kbd>down</kbd> | Navigate command history. |
| <kbd>home</kbd> | Jump to the beginning of the input. |
| <kbd>end</kbd> | Jump to the ending of the input. |
| <kbd>ctrl+k</kbd> | Cut the part of the current command after the cursor, and add it to the internal clipboard buffer. |
| <kbd>ctrl+u</kbd> | Cut the part of the current command before the cursor, and add it to the internal clipboard buffer. |
| <kbd>ctrl+y</kbd> | Paste contents of the internal clipboad to the current command. |

**MacOS Mojave clipboard shortcuts**

| KEY  | FUNCTION |
| ------------- | ------------- |
| <kbd>option+c</kbd> | Copy the current command into OS clipboard. |
| <kbd>option+x</kbd> | Cut the current command into OS clipboard. |
| <kbd>option+v</kbd> | Paste contents of the OS clipboad to the current command. |
