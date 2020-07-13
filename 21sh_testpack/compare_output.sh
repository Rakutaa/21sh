#! /bin/bash
zsh < testifile > tulos_zsh
../21sh < testifile > tulos_21sh
diff tulos_zsh tulos_21sh
