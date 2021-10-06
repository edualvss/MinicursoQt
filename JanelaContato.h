#ifndef JANELAADICIONARCONTATO_H
#define JANELAADICIONARCONTATO_H

#include <QDialog>

namespace Ui {
    class JanelaContato;
}

class Contato;

class JanelaContato : public QDialog
{
    Q_OBJECT

public:
    explicit JanelaContato(Contato* contato=0,QWidget *parent = 0);
    ~JanelaContato();

private slots:
    void botaoClicado();

signals:
    void salvar(Contato*);

private:
    Ui::JanelaContato *ui;
    Contato* contato;
};

#endif // JANELAADICIONARCONTATO_H
