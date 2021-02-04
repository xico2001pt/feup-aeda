README

Compilação:


    - Build através do CLion
    ou
    - Na pasta principal: "mkdir build; cd build; cmake ../tests ../; cmake --build ."
    

O programa deverá ser executado através do executável 'StreamZ_run', para carregar dados previamente criados é necessário mover os ficheiros active_streams.txt, archive.txt, user.txt para o folder onde se encontra o executável.

Nota: os dados fornecidos apresentam números de likes / dislikes / views por stream não consistentes com o número de viewers existentes, pois foram escolhidos aleatoriamente de modo a demonstrar as funcionalidades de ordenação / pesquisa de streams


A interface gráfica utiliza códigos ANSI, incluindo o código de CLEAR_SCREEN.


O código foi testado e compilado utilizando CLion com g++/Mingw64, e executado usando o terminal do CLion (não suporta CLEAR_SCREEN) e um terminal bash


Estrutura de ficheiros esperada:


main.cpp


CMakeLists.txt


/src
* Admin.cpp/h
* Archive.cpp/h
* Date.cpp/h
* Exceptions.cpp/h
* Input.cpp/h
* Menu.cpp/h
* Platform.cpp/h
* PrivateStream.cpp/h
* Stream.cpp/h
* StreamData.cpp/h
* Streamer.cpp/h
* User.cpp/h
* Viewer.cpp/h


/tests
* admin-tests.cpp
* archive-tests.cpp
* input-tests.cpp
* platform-tests.cpp
* stream-tests.cpp
* user-tests.cpp
* CMakeLists.txt


/data-set
* archive.txt
* active_streams.txt
* user.txt