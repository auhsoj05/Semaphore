configure_file(input: 'config.h.in', output: 'config.h',configuration : config_data)

fcitx_dep = dependency('Fcitx5Core', method : 'cmake')
inc = include_directories('.')
call = declare_dependency(include_directories: inc, sources:files('main.h'))
ibusdep = dependency('ibus-1.0')
fcitx_libd = get_option('prefix') / get_option('libdir') / 'fcitx5'
libp=get_option('libdir') / meson.project_name()

utillib=shared_library('util','util.cpp', install_dir: libp, install: true)

engine=shared_library('semaphore' ,'semaphore.cpp',dependencies: fcitx_dep,\
    link_with: utillib,install_dir : fcitx_libd, install : true, name_prefix: 'lib', install_rpath:libp )

gtkdep = dependency('gtk4')
executable('semaphore','main.cpp','gtkui.cpp',link_with : utillib,dependencies:gtkdep)
