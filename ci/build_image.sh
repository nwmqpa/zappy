#!/bin/bash

docker build . --tag nwmqpa/zappy-ci
docker push nwmqpa/zappy-cli
