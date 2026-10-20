// main.cpp — консольная программа: задача 2.25 с использованием
// библиотеки chessthreat (статической или динамической).
// Запуск:  chess [-h] [-v] [король ладья слон]
//          chess -k e1 -r e8 -b h4
// Без аргументов позиции запрашиваются с клавиатуры.
#include <iostream>
#include <string>
#include "chess_threat.h"
#ifdef _WIN32
#include <windows.h>
#endif

static void usage(const char* prog) {
    std::cout << "Использование: " << prog << " [КОРОЛЬ ЛАДЬЯ СЛОН]\n"
              << "               " << prog << " -k КОРОЛЬ -r ЛАДЬЯ -b СЛОН\n"
              << "  -h, --help     справка\n"
              << "  -v, --version  версия библиотеки\n"
              << "Клетки в шахматной нотации: e1, a8, h4.\n"
              << "Без аргументов позиции вводятся с клавиатуры.\n";
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::string sk, sr, sb;
    int positional = 0;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "-h" || a == "--help") { usage(argv[0]); return 0; }
        if (a == "-v" || a == "--version") {
            std::cout << "libchessthreat " << chess::libraryVersion() << "\n";
            return 0;
        }
        if (a == "-k" || a == "-r" || a == "-b") {
            if (i + 1 >= argc) {
                std::cerr << "Ошибка: после " << a << " нужна клетка.\n";
                return 2;
            }
            std::string v = argv[++i];
            (a == "-k" ? sk : a == "-r" ? sr : sb) = v;
        } else if (!a.empty() && a[0] == '-') {
            std::cerr << "Ошибка: неизвестный ключ " << a << "\n";
            usage(argv[0]);
            return 2;
        } else {
            switch (positional++) {
                case 0: sk = a; break;
                case 1: sr = a; break;
                case 2: sb = a; break;
                default:
                    std::cerr << "Ошибка: лишний аргумент " << a << "\n";
                    return 2;
            }
        }
    }

    bool interactive = (argc == 1);
    if (interactive) {
        std::cout << "Введите позицию белого короля (например, e1): ";
        std::cin >> sk;
        std::cout << "Введите позицию чёрной ладьи (например, a8): ";
        std::cin >> sr;
        std::cout << "Введите позицию чёрного слона (например, h4): ";
        std::cin >> sb;
    } else if (sk.empty() || sr.empty() || sb.empty()) {
        std::cerr << "Ошибка: нужно указать все три клетки.\n";
        usage(argv[0]);
        return 2;
    }

    chess::Square k, r, b;
    if (!chess::ThreatAnalyzer::parseSquare(sk, k) ||
        !chess::ThreatAnalyzer::parseSquare(sr, r) ||
        !chess::ThreatAnalyzer::parseSquare(sb, b)) {
        std::cout << "Ошибка: клетка задаётся буквой a-h и цифрой 1-8.\n";
        return 1;
    }

    chess::ThreatAnalyzer analyzer(k, r, b);
    if (!analyzer.isValid()) {
        std::cout << "Ошибка: фигуры не могут стоять на одной клетке.\n";
        return 1;
    }
    std::cout << analyzer.describe() << "\n";
    return 0;
}
