#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H

#include <QMainWindow>

class Contato;
class QTranslator;

namespace Ui {
    class JanelaPrincipal;
}

class JanelaPrincipal : public QMainWindow {
    Q_OBJECT

public:
    explicit JanelaPrincipal(QWidget *parent = 0);
    ~JanelaPrincipal();

    void limparListaContatos();
    void adicionarContatoALista(Contato* contato);

protected:
    void changeEvent(QEvent* event);

private:
    Ui::JanelaPrincipal *ui;
    QTranslator* tradutor;

signals:
    void salvar(Contato*);
    void buscar(QString);
    void excluir(Contato*);
private slots:
    void janelaAdicaoContato();
    void acaoContato();

    void traduzirParaDialeto();
    void traduzirParaAplicacao();

};

#endif // JANELAPRINCIPAL_H
