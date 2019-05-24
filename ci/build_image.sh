#!/bin/bash

docker build . --tag nwmqpa/zappy-ci:latest
docker push nwmqpa/zappy-ci:latest
