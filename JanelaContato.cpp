#include "JanelaContato.h"
#include "ui_JanelaContato.h"

#include "Contato.h"

JanelaContato::JanelaContato(Contato* contato,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JanelaContato),contato(contato)
{
    ui->setupUi(this);

    if( this->contato != NULL ) {
        ui->entradaNome->setText( contato->getNome() );
        ui->entradaTelefone->setText(contato->getTelefone());
    }

    connect( ui->botaoSalvar, SIGNAL(clicked(bool)),this,SLOT(botaoClicado()) );
    connect( ui->botaoSalvar,SIGNAL(clicked(bool)),this,SLOT(accept()) );

    this->setWindowTitle(tr("Contato"));
}

void JanelaContato::botaoClicado() {

    if(contato == NULL) {
        contato = new Contato();
    }

    contato->setNome( ui->entradaNome->text() );
    contato->setTelefone( ui->entradaTelefone->text() );

    emit salvar(contato);
}

JanelaContato::~JanelaContato()
{
    delete ui;
}
