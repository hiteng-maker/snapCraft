#!/bin/bash
set -euo pipefail
source /home/hiten/hiten_snaps/snapCraft/clientserver/server-mq/parts/server/run/environment.sh
set -x
make -j"16"
make -j"16" install DESTDIR="/home/hiten/hiten_snaps/snapCraft/clientserver/server-mq/parts/server/install"
