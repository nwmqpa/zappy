#!/bin/fish

for nb in (seq 1 4)
    for i in (seq 1 10)
        ./mockia.py nwmqpa.com 13333 $nb &
        echo "Adding player to name$nb"
    end
end
