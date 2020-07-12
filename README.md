# 42-21sh
**Work in progress**

___
 
### Introduction

*"A shell program is an application that allows interacting with the computer. In a shell the user
can run programs and also redirect the input to come from a file and output to come from a
file. Shells also provide programming constructions such as if, for, while, functions, variables
etc. Additionally, shell programs offer features such as line editing, history, file completion,
wildcards, environment variable expansion, and programing constructions."*  
<sup>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;\- Introduction to Systems Programming: a Hands-on Approach by Gustavo A. Junipero Rodriguez-Rivera and Justin Ennen</sup>

### Compilation

Clone repository into your current working directory and compile the program with the following commands:
```
$> git clone https://github.com/vkuokka/42-21sh.git 21sh  
$> cd 21sh  
$> make  
```
Now you should have binary file inside the repository which you can run with the following command:  
```
$> ./21sh  
```
  
### Keybindings

| KEY  | FUNCTION |
| ------------- | ------------- |
| <kbd>right</kbd> | Move cursor right. |
| <kbd>left</kbd> | Move cursor left. |
| <kbd>ctrl+right</kbd> | Move cursor to the beginning of a word. |
| <kbd>ctrl+left</kbd> | Move cursor to the ending of a word. |
| <kbd>ctrl+up</kbd> | Move cursor to the upper line. |
| <kbd>ctrl+down</kbd> | Move cursor to the lower line. |
| <kbd>up</kbd> | Navigate to older command in history. |
| <kbd>down</kbd> | Navigate to newer command in history. |
| <kbd>home</kbd> | Move cursor to the beginning of current command. |
| <kbd>end</kbd> | Move cursor to the ending of current command. |
| <kbd>ctrl+k</kbd> | Cut the part of the current command *after* the cursor, and add it to the internal clipboard buffer. |
| <kbd>ctrl+u</kbd> | Cut the part of the current command *before* the cursor, and add it to the internal clipboard buffer. |
| <kbd>ctrl+y</kbd> | Paste contents of the internal clipboad to the current command. |

### MacOS Mojave clipboard shortcuts

| KEY  | FUNCTION |
| ------------- | ------------- |
| <kbd>option+c</kbd> | Copy the current command into OS clipboard. |
| <kbd>option+x</kbd> | Cut the current command into OS clipboard. |
| <kbd>option+v</kbd> | Paste contents of the OS clipboad to the current command. |
