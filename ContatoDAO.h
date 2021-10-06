#ifndef CONTATODAO_H
#define CONTATODAO_H

#include <QObject>

class Contato;

class ContatoDAO : public QObject {
    Q_OBJECT
private:
    static ContatoDAO* dao;
    explicit ContatoDAO(QObject *parent = 0);
public:
    static ContatoDAO* instance();

    Contato* inserir(Contato* contato);
    Contato* atualizar(Contato* contato);
    Contato* buscarCliente(int id);
    QList<Contato *> *buscarClientes(QString busca);
    QList<Contato *> *buscarTodos();
    Contato* apagar(int id);
    bool existeAlgumContato();

signals:

public slots:
};

#endif // CONTATODAO_H
