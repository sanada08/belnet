#!/bin/sh
set -x
test `whoami` == root || exit 1

# this is for dns tomfoolery
scutil_query()
{
  key=$1

  scutil<<EOT
  open
  get $key
  d.show
  close
EOT
}

# get guid for service
SERVICE_GUID=`scutil_query State:/Network/Global/IPv4 \
        | grep "PrimaryService" \
        | awk '{print $3}'`

# get name of network service
SERVICE_NAME=`scutil_query Setup:/Network/Service/$SERVICE_GUID \
        | grep "UserDefinedName" \
        | awk -F': ' '{print $2}'`

# tell dns to be "empty" so that it's reset
networksetup -setdnsservers "$SERVICE_NAME" empty

 # Prevent restarting on exit
touch /var/lib/belnet/suspend-launchd-service

# shut off belnet gracefully
pgrep belnet$ && /opt/belnet/bin/belnet-vpn --kill

# kill the gui and such
killall BelnetGUI
killall belnet
# if the launch daemon is there kill it
/bin/launchctl stop network.beldex.belnet.daemon
/bin/launchctl unload /Library/LaunchDaemons/network.beldex.belnet.daemon.plist

# kill it and make sure it's dead 
killall -9 belnet

rm -rf /Library/LaunchDaemons/network.beldex.belnet.daemon.plist
rm -rf /Applications/Belnet/
rm -rf /Applications/BelnetGUI.app
rm -rf /var/lib/belnet
rm -rf /usr/local/belnet/
rm -rf /opt/belnet
rm -f /etc/newsyslog.d/belnet.conf
