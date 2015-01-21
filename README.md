# oneline

Simple CRLF converter


##Usage:

>oneline `<filename`> `<output-format`>  
>output-format:crlf/cr/lf (Upcase or Lowcase)


##Sample:

convert test.c(with CR or LF or even CRLF) to windows format (CRLF)  
>oneline test.c crlf

or to convert test.c(with whatever) to Linux fromat(LF)
>oneline test.c lf

done!


##Todo:

1.UTF-16(BE/LE),UTF-32 support  
(check multibyte CR LF)
