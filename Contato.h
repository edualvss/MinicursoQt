#ifndef CONTATO_H
#define CONTATO_H

#include <QObject>

class Contato : public QObject {
    Q_OBJECT
private:
    int id;
    QString nome;
    QString telefone;

public:
    explicit Contato(QObject *parent = 0);
    Contato(int id, QString nome,QString telefone,QObject* parent=0);

    // Sets
    inline void setId(int id) { this->id = id; }
    inline void setNome(QString nome) {this->nome = nome;}
    inline void setTelefone(QString telefone) { this->telefone = telefone; }

    // Gets
    inline int getId() { return this->id; }
    inline QString getNome() { return this->nome; }
    inline QString getTelefone() { return telefone; }

signals:

public slots:


};

#endif // CONTATO_H
