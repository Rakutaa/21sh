#! /bin/bash
zsh < commands.txt > output_zsh
../21sh < commands.txt > output_21sh
diff output_zsh output_21sh
