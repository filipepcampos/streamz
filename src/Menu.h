#ifndef STREAMZ_MENU_H
#define STREAMZ_MENU_H
#include "Platform.h"
#include "Admin.h"
#include <iostream>

class Menu {
    Platform platform;
    Admin admin;

    template<typename T>
    T getVar(T &var, ostream &os) const;
    void title() const;

public:
    void mainMenu();
    /*
     * Ver informacoes
     *      * topActiveStreams
     *      * topArchivedStreams
     *      * showStreams (juntamente com a contagem)
     *      * showStreamsHistory (juntamente com a contagem)
     *      * showUsers (juntamente com a contagem)
     * Registar user
     * Log in
     *      * Streamer
     *          * Criar Stream
     *          * Encerrar Stream
     *          * Apagar conta
     *      * Viewer
     *          * Juntar Stream
     *              * Like/dislike
     *              * Comentar (se privada)
     *              * Abandonar
     *
     *          * Apagar conta
     *
     * Admin
     *      * ...
     *      * ...
     *      (btw, o admin n deveria ter tambem acesso previligiado, i.e. apagar streams, users,... (por exemplo por causa de conteudo ofensivo))
     * Manual save (?) (para alem de guardar sempre ao encerrar)
     * Sair
     */

};

#endif //STREAMZ_MENU_H
