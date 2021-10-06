#ifndef CONTROLE_H
#define CONTROLE_H

#include <QObject>
#include <QSqlDatabase>

class JanelaPrincipal;
class Contato;

class Controle : public QObject {
    Q_OBJECT

private:
    JanelaPrincipal* janela;
    QSqlDatabase db;

    void inicializarBancoDados();
    void carregarListaContatos(QList<Contato *> *lista);

public:
    explicit Controle(QWidget *parent);
    ~Controle();

    void iniciarAplicacao();

private slots:
    void salvarContato(Contato* contato);
    void buscarContato(QString busca);
    void excluirContato(Contato* contato);

};

#endif // CONTROLE_H
