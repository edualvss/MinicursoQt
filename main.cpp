#include <QApplication>
#include "JanelaPrincipal.h"
#include "Controle.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QDebug>

void inicializarBancoDados(QSqlDatabase &db) {

    db.setDatabaseName("Agenda.db");

    if( !db.open() ) {
        qCritical() << db.lastError();
    } else {
        QSqlQuery query;
        if( db.tables().indexOf("contatos") == -1 ) {
            if( !query.exec("CREATE TABLE IF NOT EXISTS contatos ("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "nome VARCHAR(50) NOT NULL,"
                            "telefone VARCHAR(15)") ) {
                qCritical() << db.lastError();
            } else {
                query.exec("ALTER TABLE contatos ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;");
            }
        }
    }
}

void carregarListaContatos() {

}

int main(int argc, char *argv[]) {

    QApplication app(argc,argv);

    qDebug() << QSqlDatabase::drivers();

    JanelaPrincipal janela;
    Controle* controle = new Controle(&janela);
    controle->iniciarAplicacao();

//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

//    inicializarBancoDados(db);

    return app.exec();
}

