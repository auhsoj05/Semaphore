project('semaphore','c','cpp')

config_data = configuration_data()
iconp= 'icons/semaphore.svg'
app_datadir=get_option('prefix') / get_option('datadir') / meson.project_name()
icondir=app_datadir / iconp
ibusdir=get_option('prefix') / get_option('datadir')+'/ibus'
componentdir=ibusdir+'/component'
config_data.set('ICONDIR',icondir)

subdir('src')
subdir('share')
