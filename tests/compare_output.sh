#! /bin/bash
zsh < 21_cmds.txt > output_zsh
../21sh < 21_cmds.txt > output_21sh
diff output_zsh output_21sh
