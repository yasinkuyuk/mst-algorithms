- init:
    run: rm -f q1.o q1
    blocker: true

- build:
    run: g++ -std=c++11 -Wall -Werror  q1.cpp -o q1                   # timeout: 150
    blocker: true

- case0: 
    run: ./q1
    points: 25
    script:
        - expect: "Hipp Ch1 1\r\nGP Ch2 2\r\nHp3 Bas2 3\r\nCh2 Bas3 4\r\nGP Bas2 6\r\nHipp Hp1 7\r\nGP Hp4 8\r\nHipp Hp2 10\r\nGP Hipp 12\r\nBas1 Ch2 15\r\n68\r\n"           # timeout: 2
        - expect: _EOF_                                              # timeout: 150
    return: 0
