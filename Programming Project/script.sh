#!/bin/bash

if [ -z "$2" ]; then
  test_files=$(find . -name "*_test")
  make TESTS
else
  test_files="$2"
  make $test_files
fi

for test_file in $test_files; do
  if [[ "$test_file" == *"command_test"* ]]; then
    extra="command_test.txt"
  else
    extra=""
  fi

  if [[ "$test_file" == *"game_management_test"* ]]; then
    extra="anthill.dat"
  fi

  if [[ "$test_file" == *"game_test"* ]]; then
    extra="anthill.dat"
  fi

  if [[ "$test_file" == *"game_rules_test"* ]]; then
    extra="anthill.dat"
  fi

  if [ "$1" -eq 0 ]; then
    ./$test_file $extra
  elif [ "$1" -eq 1 ]; then
    valgrind --leak-check=full ./$test_file $extra
  else
    echo -e "\033[0;31mError: el primer argumento debe ser 0 o 1. Limpiando...\033[0m"
    make clean
  fi
done
