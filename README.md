# chess-threat-build — автоматизация сборки: make и Gradle

Задача 2.25 (А. Г. Юркин): на шахматной доске белый король, чёрная ладья и слон —
есть ли угроза королю и от кого.

```
cpp/    C++-версия, сборка через Makefile
java/   Java-версия, сборка через Gradle, модульные тесты JUnit 5
```

## C++ и make

```bash
cd cpp
make            # release: исполняемый файл ./chess (-O2)
make debug      # ./chess_debug с отладочными символами (-g -O0)
make test       # автотесты обеих сборок
make run ARGS="e1 e8 h4"
make clean      # удалить промежуточные файлы (build/)
make distclean  # удалить и исполняемые файлы
make rebuild    # принудительная пересборка; также: make -B
make info       # значения мета-переменных
make CXX=clang++   # другой компилятор
```

## Java и Gradle

Нужна JDK 17 или новее. В каталоге `java/`:

```bash
./gradlew tasks              # список задач (Windows: gradlew.bat tasks)
./gradlew build              # компиляция + тесты + jar + дистрибутивы
./gradlew test               # модульные тесты
./gradlew run --args="e1 e8 h4"
./gradlew installDist        # скрипт запуска app/build/install/app/bin/app
./gradlew buildInfo          # где лежат jar и отчёт о тестах
./gradlew clean
```

Скомпилированная программа:

| Что | Путь | Запуск |
|---|---|---|
| исполняемый jar | `app/build/libs/app.jar` | `java -jar app/build/libs/app.jar e1 e8 h4` |
| классы | `app/build/classes/java/main` | `java -cp app/build/classes/java/main chess.App e1 e8 h4` |
| скрипт | `app/build/install/app/bin/app` | `app/build/install/app/bin/app e1 e8 h4` |

HTML-отчёт о тестах: `app/build/reports/tests/test/index.html`.

Автор: Егоров И., группа 4ИБ2, ITHub. Преподаватель: Сухов А. А.
