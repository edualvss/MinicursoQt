#include "ContatoDAO.h"
#include "Contato.h"

#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include <QPixmap>
#include <QBuffer>

ContatoDAO* ContatoDAO::dao = 0;

ContatoDAO::ContatoDAO(QObject *parent) : QObject(parent) {

}

ContatoDAO* ContatoDAO::instance() {
    if( !dao ) {
        dao = new ContatoDAO();
    }
    return dao;
}

Contato* ContatoDAO::inserir(Contato *contato) {

    QSqlQuery comando;
    QString nome = contato->getNome();
    QString telefone = contato->getTelefone();

    comando.prepare(QString("INSERT INTO `contatos` "
                    "(`nome`,`telefone`) VALUES "
                    "('%1','%2')")
                    .arg(nome).arg(telefone)
                    );

    if( !comando.exec() ) {
        return NULL;
    } else {
        contato->setId( comando.lastInsertId().toInt() );
        return contato;
    }
}

Contato* ContatoDAO::atualizar(Contato *contato) {

    QSqlQuery comando;
    comando.prepare(QString("UPDATE contatos SET nome='%1', telefone='%2' WHERE id=%4")
                    .arg(contato->getNome())
                    .arg(contato->getTelefone())
                    .arg(QString::number(contato->getId()))
                    );

    if(!comando.exec()) {
        return NULL;
    } else {
        return contato;
    }
}

Contato* ContatoDAO::buscarCliente(int id) {

    QSqlQuery comando;
    comando.prepare(QString("SELECT * FROM contatos WHERE id=%1 ORDER BY nome").arg(QString::number(id)));

    if(!comando.exec()) {
        return NULL;
    } else {
        Contato* contato = NULL;
        while(comando.next()) {
            contato = new Contato();
            contato->setId( comando.value("id").toInt() );
            contato->setNome( comando.value("nome").toString() );
            contato->setTelefone(comando.value("telefone").toString());
            break;
        }

        return contato;
    }

}


QList<Contato *>* ContatoDAO::buscarClientes(QString busca) {

    QSqlQuery comando;
    comando.prepare( QString("SELECT * FROM contatos WHERE nome LIKE ('%%1%') ORDER BY nome").arg(busca) );

    if( !comando.exec() ) {
        return NULL;
    } else {
        QList<Contato*>* contatos = new QList<Contato*>();
        int contador = 0;
        while(comando.next()) {
            Contato* c = new  Contato();
            c->setId( comando.value("id").toInt() );
            c->setNome( comando.value("nome").toString() );
            c->setTelefone( comando.value("telefone").toString() );
            contatos->insert( contador++,c );
        }

        if( contatos->size() == 0 ) {
            delete contatos;
            return NULL;
        } else {
            return contatos;
        }
    }

}

QList<Contato *>* ContatoDAO::buscarTodos() {
    QSqlQuery comando;
    comando.prepare( QString("SELECT * FROM contatos ORDER BY nome") );
    if( !comando.exec() ) {
        return NULL;
    } else {
        QList<Contato*>* contatos = new QList<Contato*>();
        int contador = 0;
        while( comando.next() ) {
            Contato* c = new Contato();
            c->setId( comando.value("id").toInt() );
            c->setNome( comando.value("nome").toString() );
            c->setTelefone( comando.value("telefone").toString() );
            contatos->insert(contador++,c);
        }

        if( contatos->size() == 0 ) {
            delete contatos;
            return NULL;
        } else {
            return contatos;
        }
    }
}

Contato* ContatoDAO::apagar(int id) {

    Contato* c = this->buscarCliente(id);
    if( c == NULL ) {
        return NULL;
    }

    QSqlQuery comando;

    comando.prepare( QString("DELETE FROM contatos WHERE id=%1").arg(QString::number(id)) );

    if( !comando.exec() ) {
        return NULL;
    } else {
        return c;
    }

}

bool ContatoDAO::existeAlgumContato() {
    QSqlQuery comando;
    comando.prepare("SELECT * FROM contatos");
    if( !comando.exec() ) {
        return false;
    } else {
        while(comando.next()) {
            return true;
        }
        return false;
    }
}
