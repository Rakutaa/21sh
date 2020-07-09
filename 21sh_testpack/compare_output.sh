#! /bin/bash
bash < testifile > tulos_bash
../21sh < testifile > tulos_21sh
diff tulos_bash tulos_21sh
