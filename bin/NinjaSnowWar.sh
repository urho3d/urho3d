#!/usr/bin/env bash
# To avoid cacophony of multiple background music when testing with multiple connections on the same test machine,
# start all the other non-headless connections with '-nobgm' argument.
# E.g. 1 - headless server
#   Start the server with "./NinjaSnowWar.sh -headless -server"
#   Start the first client with "./NinjaSnowWar.sh -w -address `hostname`"
#   Start the subsequent clients on the same host with "./NinjaSnowWar.sh -w -nobgm -address `hostname`"
#
# E.g. 2 - non-headless server
#   Start the server with "./NinjaSnowWar.sh -w -server"
#   Start the client on the same host with "./NinjaSnowWar.sh -w -nobgm -address `hostname`"
#
if [ -d $(dirname $0)/../share/Urho3D/Resources ]; then OPT1="-pp ../share/Urho3D/Resources"; fi
$(dirname $0)/Urho3DPlayer Scripts/NinjaSnowWar.as $OPT1 $@
