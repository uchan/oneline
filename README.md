# oneline

Simple CRLF converter

---------
Usage:

oneline filename output-format

output-format:crlf/cr/lf

----------
Sample:

convert test.c(with CR or LF or even CRLF) to windows format (CRLF)

oneline test.c crlf

done!

----------
Todo:

1.UTF-16(BE/LE),UTF-32 support
(check multibyte CR LF)
