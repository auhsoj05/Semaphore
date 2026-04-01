configure_file(input: 'config.h.in', output: 'config.h',configuration : config_data)

cc= meson.get_compiler('c')
m_dep = cc.find_library('m',required:false)
inc = include_directories('.')
call = declare_dependency(include_directories: inc, sources:files('main.h'))
ibusdep = dependency('ibus-1.0')



gtkdep = dependency('gtk4')
executable('semaphore','main.c','gtkui.c',link_with : [engine,util],dependencies:[gtkdep,ibusdep,m_dep])
