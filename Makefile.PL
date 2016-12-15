use ExtUtils::MakeMaker;

WriteMakefile(
    NAME      => 'sys-toolkit',
    VERSION   => '0.1.1',
    AUTHOR    => 'zhe.chen <chenzhe07@gmail.com>',
    EXE_FILES => [ <bin/*> ],
    MAN1PODS  => {
      map {
         (my $name = $_) =~ s/^bin.//;
         $_ => "blib/man1/$name.1p";
      } <bin/*>
    },
    MAN3PODS     => {}, # man(3) pages are for C libs
    PREREQ_PM    => {
        DBI           => 1.46,
        DBD::mysql    => 3.0000_0,
        Term::ReadKey => 0,
        Net::DNS      => 0,
    },
);
