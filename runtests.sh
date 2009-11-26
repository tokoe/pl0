#!/bin/bash

for i in tests/valid*.pl0; do
  ./pl0 $i foo.cl0 2> /dev/null;
  if [ $? -ne 0 ]; then
    echo "Test $i failed";
  fi
done

for i in tests/invalid*.pl0; do
  ./pl0 $i foo.cl0 2> /dev/null;
  if [ $? -ne 1 ]; then
    echo "Test $i failed";
  fi
done
