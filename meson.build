project('radius-auth', 'c', 'cpp',
    version : '1.0',
    meson_version: '>=0.57.0',
    default_options : [
        'buildtype=debugoptimized',
        'c_std=gnu11',
        'cpp_std=c++20'
    ]
)

# Include directories
incdir = include_directories(
    'apml',
)

# Include dependent library
#apml_dependencies = []
#cpp = meson.get_compiler('cpp')


# Include source file
apml_src = files(
    'apml/Apml_fdk.c',
    'apml/User_platform.c',
    'apml/Apml_smbus.c'
)

# Make dynamic library
shared_library( 
    'openapml', 
    apml_src ,
    #dependencies : apml_dependencies,
    include_directories : incdir,
    #name_prefix : '',
    #install : true,
    #install_dir : '/lib/security'
)

test_src = files(
    'apml/Apml_fdk.c',
    'apml/User_platform.c',
    'apml/Apml_smbus.c',
    'apml/test.c'
)
executable(
    'apml-test',
    test_src,
    include_directories : incdir
)
