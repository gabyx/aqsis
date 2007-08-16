from SCons.Script.SConscript import SConsEnvironment
from SCons.Options import EnumOption, BoolOption

def PlatformOptions(opts, tempenv):
	opts.Add('bison', 'Point to the bison executable', 'bison')
	opts.Add('flex', 'Point to the flex executable', 'flex')
	opts.Add('sysconfdir', 'Directory where the configuration will reside', '$install_prefix/etc/aqsis')
	opts.Add('libdir', 'Directory into which libraries will be installed', '$install_prefix/lib')
	opts.Add('libexecdir', 'Directory into which executable subprograms will be installed', '$libdir/aqsis')
	opts.Add('destdir', 'Temporary directory to prepend to all install paths (packagers only)', '')
	opts.Add(BoolOption('no_rpath', 'Do not set the "rpath" in the executable/shared libraries', '0'))

