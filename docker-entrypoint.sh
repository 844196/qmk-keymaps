#!/bin/bash

(
  cd /code
  aqua i -l
)

exec "$@"
