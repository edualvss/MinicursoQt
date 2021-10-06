#include "Contato.h"

Contato::Contato(QObject *parent) : QObject(parent) {

    this->id = -1;
    this->nome = QString();
    this->telefone = QString();

}

Contato::Contato(int id, QString nome, QString telefone,
                 QObject *parent) : QObject(parent) {

    this->id = id;
    this->nome = nome;
    this->telefone = telefone;
}
