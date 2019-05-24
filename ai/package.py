"""Base module for zappy_ai."""

import ai.main
import sys

if __name__ == '__main__':
    try:
        ai.main.main()
    except Exception as e:
        sys.stderr.write(str(e))
        sys.exit(84)
