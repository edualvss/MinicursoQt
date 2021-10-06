#include "JanelaPrincipal.h"
#include "ui_JanelaPrincipal.h"

#include "Contato.h"

#include "JanelaContato.h"

#include <QMessageBox>
#include <QTranslator>

// https://iconverticons.com/ - Converter imagens para diferentes tipos de icones

JanelaPrincipal::JanelaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JanelaPrincipal) {
    ui->setupUi(this);

    tradutor = new QTranslator(this);

    connect(ui->actionAdicionar_Contato, SIGNAL(triggered(bool)),this,SLOT(janelaAdicaoContato()));
    connect(ui->inBusca, SIGNAL(textEdited(QString)),this,SIGNAL(buscar(QString)));

    connect(ui->actionEditar_contato,SIGNAL(triggered(bool)),this,SLOT(acaoContato()));
    connect(ui->actionExcluir_contato,SIGNAL(triggered(bool)),this,SLOT(acaoContato()));

    connect(ui->actionAplica_o,SIGNAL(triggered(bool)),this,SLOT(traduzirParaAplicacao()));
    connect(ui->actionDialeto,SIGNAL(triggered(bool)),this,SLOT(traduzirParaDialeto()));

    connect(ui->actionSair,SIGNAL(triggered(bool)),this,SLOT(close()));
}

void JanelaPrincipal::janelaAdicaoContato() {

    JanelaContato* j = new JanelaContato(NULL,this);

    connect(j,SIGNAL(salvar(Contato*)),this,SIGNAL(salvar(Contato*)));

    j->exec();

    delete j;

}

JanelaPrincipal::~JanelaPrincipal() {
    delete ui;
}


void JanelaPrincipal::limparListaContatos() {

    QTreeWidgetItemIterator it(ui->listaContatos);

    for( ; (*it) ; ) {
        QTreeWidgetItem* item = (*it);
        delete item;
        it++;
    }

    ui->listaContatos->clear();

}

void JanelaPrincipal::adicionarContatoALista(Contato *contato) {
    QTreeWidgetItem* cont = new QTreeWidgetItem(ui->listaContatos);
    cont->setData(0,Qt::DisplayRole,contato->getId());
    cont->setData(1,Qt::DisplayRole,contato->getNome());
    cont->setData(2,Qt::DisplayRole,contato->getTelefone());

}

void JanelaPrincipal::acaoContato() {

    QList<QTreeWidgetItem* > selecionados =  ui->listaContatos->selectedItems();
    if(selecionados.size() == 0) {
        QMessageBox::information(this,tr("Aviso"),tr("Nenhum contato selecionado"));
        return;
    }

    QObject* emissor = sender();

    QTreeWidgetItem* itemSelecionado = selecionados.at(0);
    Contato* contato = new Contato(
                itemSelecionado->data(0,Qt::DisplayRole).toInt(),
                itemSelecionado->data(1,Qt::DisplayRole).toString(),
                itemSelecionado->data(2,Qt::DisplayRole).toString());

    if( emissor == ui->actionEditar_contato ) {
        // Editar
        JanelaContato* j = new JanelaContato(contato,this);
        connect(j,SIGNAL(salvar(Contato*)),this,SIGNAL(salvar(Contato*)));
        j->exec();
        delete j;
    } else {
        // Excluir
        emit excluir(contato);
    }
}

void JanelaPrincipal::changeEvent(QEvent *event) {

    if(event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);

}

void JanelaPrincipal::traduzirParaAplicacao() {

    qApp->removeTranslator(tradutor);

}

void JanelaPrincipal::traduzirParaDialeto() {
    tradutor->load("Dialeto",qApp->applicationDirPath());
    qApp->installTranslator( tradutor );
}
