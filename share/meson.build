fcitx_dir= get_option('prefix') / get_option('datadir')/ 'fcitx5'
configure_file(configuration : config_data ,input : 'addon/semaphore.conf.in', output : 'semaphore.conf',\
    install_dir : fcitx_dir / 'addon', install_mode : ['rw-r--r--',0,0])
install_data(sources :'inputmethod/semaphore.conf', install_dir : fcitx_dir / 'inputmethod',\
    install_mode :['rw-r--r--',0,0])
install_data(sources : iconp, install_dir : icondir, install_mode :['rw-r--r--', 0, 0])

