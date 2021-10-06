// Controle
#include "Controle.h"

// Visão
#include "JanelaPrincipal.h"
#include <QMessageBox>

// Modelo
#include "Contato.h"
#include "ContatoDAO.h"

// SQL
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

Controle::Controle(QWidget *parent) : QObject(parent) {

    this->janela = dynamic_cast<JanelaPrincipal*>(parent);

    db = QSqlDatabase::addDatabase("QSQLITE");

    connect(janela,SIGNAL(salvar(Contato*)),this,SLOT(salvarContato(Contato*)));
    connect(janela,SIGNAL(buscar(QString)),this,SLOT(buscarContato(QString)));
    connect(janela,&JanelaPrincipal::excluir,this,&Controle::excluirContato);
}

Controle::~Controle() {

    db.close();

}

void Controle::inicializarBancoDados() {
    db.setDatabaseName("Agenda.db");

    if( !db.open() ) {
        qDebug() << "Erro na abertura";
        qCritical() << db.lastError();
    } else {
        QSqlQuery query;
        if( db.tables().indexOf("contatos") == -1 ) {
            if( !query.exec("CREATE TABLE IF NOT EXISTS contatos ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "nome VARCHAR(50) NOT NULL,"
                            "telefone VARCHAR(15) NOT NULL)") ) {
                qDebug() << "Erro na criacao";
                qCritical() << db.lastError();
            } else {
                qDebug() << "Erro na definicao da codificacao de caracteres!";
                query.exec("ALTER TABLE contatos DEFAULT CHARSET=utf8 COLLATE=utf8_bin;");
            }
        }
    }
}

void Controle::iniciarAplicacao() {

    this->inicializarBancoDados();

    this->carregarListaContatos( ContatoDAO::instance()->buscarTodos() );

    this->janela->show();

}

void Controle::carregarListaContatos(QList<Contato*>* lista) {

    this->janela->limparListaContatos();

    if( lista == NULL ) {
        if( ContatoDAO::instance()->existeAlgumContato() ) {
            QMessageBox* msg = new QMessageBox(QMessageBox::Critical,tr("Aviso"),
                                          tr("Problema ao carregar lista de contatos"),
                                          QMessageBox::Ok,this->janela);
            msg->exec();
            delete msg;
        }
    } else {
        int numRegistros = lista->size();
        for( int i = 0; i < numRegistros; i++ ) {
            Contato* c = lista->at(i);
            this->janela->adicionarContatoALista(c);
            delete c;
        }
        lista->clear();
        delete lista;
    }

}

void Controle::salvarContato(Contato *contato) {

    if(contato->getId() == -1) {
        contato = ContatoDAO::instance()->inserir(contato);
    } else {
        contato = ContatoDAO::instance()->atualizar(contato);
    }

    delete contato;

    this->carregarListaContatos( ContatoDAO::instance()->buscarTodos() );

}

void Controle::buscarContato(QString busca) {

    QList<Contato*>* contatos = ContatoDAO::instance()->buscarClientes(busca);
    if( contatos == NULL ) {
        this->carregarListaContatos( new QList<Contato*>() );
    } else {
        this->carregarListaContatos( contatos );
    }

}

void Controle::excluirContato(Contato *contato) {

    contato = ContatoDAO::instance()->apagar( contato->getId() );
    if( contato != NULL ) {
        delete contato;
    }
    this->carregarListaContatos( ContatoDAO::instance()->buscarTodos() );
}
