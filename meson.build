project('semaphore','cpp', default_options: ['cpp_std=gnu++20'],version: '0.1.0')
add_global_arguments('-std=gnu++20', language: 'cpp')

config_data = configuration_data()
iconp= 'icons/semaphore.svg'
app_datadir=get_option('prefix') / get_option('datadir') / meson.project_name()
icondir=app_datadir / iconp
ibusdir=get_option('prefix') / get_option('datadir')+'/ibus'
componentdir=ibusdir+'/component'
config_data.set('ICONDIR',icondir)
config_data.set('VERSION',meson.project_version())

subdir('src')
subdir('share')
