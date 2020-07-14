#! /bin/bash
zsh < 42_cmds.txt > output_zsh
../21sh < 42_cmds.txt > output_21sh
diff output_zsh output_21sh
