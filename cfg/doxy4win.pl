#! /usr/bin/perl -p -i

# Note: ``perl'' is invoked with the ``-i'' option above (make
# backup file when editing inline), but without a backup extension,
# as the extra backup file screws up for ``make distcheck''.

sub cygpath {
  $path=`CYGWIN= cygpath -w "$_[0]"`;
  chop($path);
  $path;
}

s/\<PATH\>([^ ]*)/&cygpath($1)/eg;
s/^HTML_OUTPUT.*/HTML_OUTPUT = html/;
s/^MAN_OUTPUT.*/MAN_OUTPUT = man/;

