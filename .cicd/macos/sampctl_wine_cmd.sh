#!/bin/sh
# use command passed as argument
# or default to bash

export 'COMMAND_MODE'='unix2003'
export 'DESTINATION'="$CROSSOVER_PATH"'/CrossOver 23.0.0.36367'
export '__CFBundleIdentifier'='com.codeweavers.CrossOver'
export 'CX_BOTTLE_PATH'="$CROSSOVER_PATH"'/Bottles'
export 'TMPDIR'='/var/folders/dk/51xhwc112b71mwg82wm_l_w00000gn/T/'
export 'XPC_FLAGS'='0x0'
export 'PYTHONPATH'='/Applications/CrossOver.app/Contents/SharedSupport/CrossOver/lib/python'
export 'SSH_AUTH_SOCK'='/private/tmp/com.apple.launchd.7qiCYcALqo/Listeners'
export 'CX_APP_BUNDLE_PATH'='/Applications/CrossOver.app'
export 'XPC_SERVICE_NAME'='application.com.codeweavers.CrossOver.16449867.16449873'
export 'SQLITE_EXEMPT_PATH_FROM_VNODE_GUARDS'=$CROSSOVER_SQLITE_EXEMPT_PATH_FROM_VNODE_GUARDS2
export CX_BOTTLE='sampctl'
export PATH='/Applications/CrossOver.app/Contents/SharedSupport/CrossOver/bin'":$PATH"
cd "$CROSSOVER_PATH"'/Bottles/sampctl/drive_c'
WINEPATH=C:\\sampctl wine cmd /c 'cd samp-server && '"$@"
cd $PROJECT_ROOT_PATH
