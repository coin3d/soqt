soqt.iwz:
	@perl -w $(top_srcdir)/build/geniwz.pl @VERSION@ \
            $(libdir)/soqt@SOQT_MAJOR_VERSION@.dll \
            $(libdir)/soqt@SOQT_MAJOR_VERSION@.lib \
            `find $(includedir)/Inventor/Qt -name "*.h"` > soqt.iwz

ispkg: soqt.iwz
	@IsxBuild.exe soqt.iwz -E -O
