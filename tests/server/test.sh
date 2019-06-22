#!/bin/fish

for nb in (seq 1 4)
    for i in (seq 1 9)
        echo -e "name$nb\nFork" | nc localhost 2222 &
        echo "Adding player to name$nb"
    end
end
