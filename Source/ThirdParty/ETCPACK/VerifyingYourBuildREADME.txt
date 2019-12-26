Windows:
========
After compiling, you can validate your build by compressing a number
of images and comparing to what you should get:

1. Start a command line prompt (Start-menu, type cmd, press enter)
2. cd the "testing" directory
3. run the program testvectors.bat (type testvectors.bat, hit enter)

The system will now compress a number of images and store them in the
"compressed" directory. Now type

validate.bat > logfile.txt

This will compare the two directories "testvectors_correct" and "testvectors". The directory "testvectors_correct" contains the correctly compressed and uncompressed versions and "testvectors" is the output from your build.

Now examine your logfile.txt. If there are no errors, all file comparisons will show "FC: no differences encountered"

If you have errors, some parts of your output will contain

000003EC: F9 CD
000003ED: DC BD
000003EE: BA AE
000003EF: 91 40
000003F2: 08 00
000003F3: 88 04
0000048C: 06 64
0000048D: 21 5C

and your build was not successful. 

If you have cygwin installed, you can replace step 4 by

4. diff -r testvectors testvectors_correct

If your build is correct there should be no output from the above command.


Cygwin
======
After compiling, you can validate your build by compressing a number
of images and comparing to what you should get:

1. Start cygwin
2. cd the "testing" directory
3. run the program testvectors_cygwin.sh (type ./testvectors_cygwin.sh, hit enter)

The system will now compress a number of images and store them in the
"compressed" directory.

4. type diff -r testvectors testvectors_correct

This will compare the two directories "testvectors_correct" and "testvectors". The directory "testvectors_correct" contains the correctly compressed and uncompressed versions and "testvectors" is the output from your build.

If there are no differences between the two directories, diff will not print anything, and your build is correct.

