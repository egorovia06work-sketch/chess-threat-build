#!/usr/bin/env bash
# Автотесты через аргументы командной строки.
# Строка tests.txt: "король ладья слон|ожидаемый вывод"
BIN=${1:-./chess}; pass=0; fail=0
while IFS='|' read -r input expected; do
  # shellcheck disable=SC2086
  got=$("$BIN" $input 2>&1)
  if [[ "$got" == "$expected" ]]; then ((pass++)); echo "OK   $input -> $got"
  else ((fail++)); echo "FAIL $input -> $got (ожидалось: $expected)"; fi
done < tests.txt
echo "Пройдено: $pass, ошибок: $fail"; [[ $fail -eq 0 ]]
